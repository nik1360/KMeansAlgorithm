#include "lib_const.hpp"

using namespace std;

int main(){
    CSVReader csv_reader;
    vector<DataItem> dataset;
    vector<Centroid> centroids;
    string csv_filename="prova.csv";

    bool convergence;
    int it_count;
    
    
    /*Create the dataset from CSV files*/
    csv_reader.readCsv(csv_filename, &dataset); 
    
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
        
        /*For every element of the dataset, find the centroid*/
        for(int data_index=0;data_index<dataset.size();data_index++){
            dataset.at(data_index).findNearestCentroid(&centroids);
        }

        /*Optimize the position of the centroids*/
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            centroids.at(centr_index).optimizePosition(centr_index,&dataset);
            if(centroids.at(centr_index).checkDisplacements()==false){  //check the displacement of the entroid
                convergence=false;  //if the displacement of a single centroid is > 0, then there is no convergence
            }
        }
        /*Check if there is convergence*/
        for(int centr_index=0;centr_index<NUM_CENTROIDS;centr_index++){
            if(centroids.at(centr_index).checkDisplacements()==false){  
                convergence=false;  
                break;
            }
        }

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