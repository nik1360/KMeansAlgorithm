#include "lib_const.hpp"

using namespace std;

int main(){
    CSVReader csv_reader;
    vector<DataItem> dataset;
    vector<Centroid> centroids;
    string csv_filename="dataset_babymonitor_iot/gafgyt/scan.csv";  //uses ',' as parameter separator
    //string csv_filename="prova.csv";  //uses ';' as parameter separator

    bool convergence;
    int it_count,conv_count;
    double start_search, stop_search, start_opt, stop_opt, start_read, stop_read;
    double t_search, t_opt, t_read, threshold=0.00000001;    

    omp_set_num_threads(4);
    
    /*Create the dataset from CSV files*/

    start_read=omp_get_wtime();
    csv_reader.readCsv(csv_filename, dataset); 
    stop_read=omp_get_wtime();
    t_read=stop_read-start_read;
    
    cout <<"DATASET SIZE "<<dataset.size()<<endl;
    cout <<"NUMBER OF VARIABLES: "<<NUM_VARIABLES<<endl;
    cout<< "NUMBER OF CENTROIDS: "<<NUM_CENTROIDS<<endl;
    cout<<"TIME TO READ THE DATABASE: "<<t_read<<" s"<<endl;
    
    /*Initialize centroids at random*/
    for(int i=0; i<NUM_CENTROIDS;i++){  
        srand(i);    
        centroids.push_back(Centroid());
    }
    
    convergence=false;
    it_count=0;
    
    while((convergence==false)&&(it_count<MAX_ITERATIONS)){
        it_count++;
        convergence=true;
        conv_count=0;
        
        start_search=omp_get_wtime();
        //For every element of the dataset, find the centroid
        #pragma omp parallel for
        for(int data_index=0;data_index<dataset.size();data_index++){
            dataset[data_index].findNearestCentroid(centroids);
        }
        stop_search=omp_get_wtime();
        t_search=stop_search-start_search;
        start_opt=omp_get_wtime();
        //Optimize the position of the centroids
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            centroids[centr_index].optimizePosition(centr_index,dataset);
        }
        stop_opt=omp_get_wtime();
        t_opt=stop_opt-start_opt;
        //Check the displacements
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            if(fabs(centroids[centr_index].getDisplacement())<threshold){  
               conv_count++;  
            }
        }
        //if all the centroids has zero displacement, there is convergence
        if(conv_count < NUM_CENTROIDS){
            convergence=false;
        }

        /*Print iterations details*/
        cout<<"IT: "<<it_count<<" -> T_SEARCH: "<<t_search<<"   T_OPT:"<<t_opt<<endl;
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            cout<<"displ c"<<centr_index<<" -> "<<centroids[centr_index].getDisplacement()<<endl;
        }

    }
    if(it_count<MAX_ITERATIONS)
        cout<<"CONVERGENCE IN "<<it_count<<" ITERATIONS!"<<endl;
    else
        cout<<"MAX NUMBER OF ITERATIONS ("<<MAX_ITERATIONS<<") REACHED!"<<endl;
    
    return 0;
}