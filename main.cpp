#include "lib_const.hpp"

using namespace std;

int main(){
    CSVReader csv_reader;
    vector<DataItem> dataset;
    vector<Centroid> centroids;
    string csv_filename="dataset_babymonitor_iot/gafgyt/scan.csv";
    //string csv_filename="prova.csv";

    bool convergence;
    int it_count;
    time_t start_search, stop_search, start_opt, stop_opt;
    double t_search, t_opt;    
    
    /*Create the dataset from CSV files*/
    csv_reader.readCsv(csv_filename, dataset); 
    for(int data_index=0;data_index<dataset.size();data_index++){
            
        for(int i=0;i<NUM_VARIABLES;i++){
            cout<<dataset.at(data_index).getVariable(i)<<" ";
        }
        cout<<endl;
    }
    
    cout<<dataset.size()<<endl;
    /*Initialize centroids at random*/
    srand(time(NULL));
    for(int i=0; i<NUM_CENTROIDS;i++){      
        centroids.push_back(Centroid());
        centroids.at(i).randomInit();
    }

    convergence=false;
    it_count=0;
    while((convergence==false)&&(it_count<MAX_ITERATIONS)){
        it_count++;
        convergence=true;
        
        start_search=clock();
        /*For every element of the dataset, find the centroid*/
        for(int data_index=0;data_index<dataset.size();data_index++){
            dataset.at(data_index).findNearestCentroid(&centroids);
        }
        stop_search=clock();
        t_search=(double)(stop_search-start_search)/CLOCKS_PER_SEC;

        start_opt=clock();
        /*Optimize the position of the centroids*/
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            centroids.at(centr_index).optimizePosition(centr_index,&dataset);
            /*cout<<"CENTROID: "<<centr_index<<"-> ";
            for(int i=0;i<NUM_VARIABLES;i++){
                cout<<centroids.at(centr_index).getDisplacement(i)<<" ";
            }
            cout<<endl;
            */
        }
        stop_opt=clock();
        t_opt=(double)(stop_opt-start_opt)/CLOCKS_PER_SEC;
        /*Check if there is convergence*/
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            if(centroids.at(centr_index).checkDisplacements()==false){  
                convergence=false;  
                break;
            }
        }
        cout<<"it: "<<it_count<<" -> t_search: "<<t_search<<"   t_opt:"<<t_opt<<endl;
    }
    if(it_count<MAX_ITERATIONS)
        cout<<"Convergence in "<<it_count<<" iterations!"<<endl;
    else
        cout<<"MAX NUMBER OF ITERATIONS ("<<MAX_ITERATIONS<<") reached!"<<endl;
    
    /*Deallocate the arrays inside the data items and the centroids*/
    for(int data_index=0;data_index<dataset.size();data_index++){
        dataset.at(data_index).deallocate();
    }
    for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
        centroids.at(centr_index).deallocate();
    }

    return 0;
}