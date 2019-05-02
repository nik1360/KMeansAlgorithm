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
    time_t start_search, stop_search, start_opt, stop_opt, start_read, stop_read;
    double t_search, t_opt, t_read, threshold=0.00000001;    

    omp_set_num_threads(8);
    
    /*Create the dataset from CSV files*/

    start_read=clock();
    csv_reader.readCsv(csv_filename, dataset); 
    stop_read=clock();
    t_read=(double)(stop_read-start_read)/CLOCKS_PER_SEC;
    
    cout <<"dataset size: "<<dataset.size()<<endl;
    cout <<"data item size: "<<NUM_VARIABLES<<endl;
    cout<< "number of centroids: "<<NUM_CENTROIDS<<endl;
    cout<<"t_read: "<<t_read<<" s"<<endl;
    
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
        
        start_search=clock();
        //For every element of the dataset, find the centroid
        #pragma omp parallel for
        for(int data_index=0;data_index<dataset.size();data_index++){
            dataset[data_index].findNearestCentroid(centroids);
        }
        stop_search=clock();
        t_search=(double)(stop_search-start_search)/CLOCKS_PER_SEC;
        start_opt=clock();
        //Optimize the position of the centroids
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            centroids[centr_index].optimizePosition(centr_index,dataset);
        }
        cout<<endl;
        stop_opt=clock();
        t_opt=(double)(stop_opt-start_opt)/CLOCKS_PER_SEC;
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
        cout<<"it: "<<it_count<<" -> t_search: "<<t_search<<"   t_opt:"<<t_opt<<endl;
    }
    if(it_count<MAX_ITERATIONS)
        cout<<"Convergence in "<<it_count<<" iterations!"<<endl;
    else
        cout<<"MAX NUMBER OF ITERATIONS ("<<MAX_ITERATIONS<<") reached!"<<endl;
    
    return 0;
}