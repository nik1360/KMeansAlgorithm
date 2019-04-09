#include "lib_const.hpp"

using namespace std;

int main(){
    CSVReader csv_reader;
    vector<DataItem> dataset;
    vector<Centroid> centroids;
    string csv_filename="prova.csv";
    
    
    /*Create the dataset from CSV files*/
    csv_reader.readCsv(csv_filename, &dataset); 
    
    /*Initialize centroids at random*/
    srand(time(NULL));
    for(int i=0; i<NUM_CENTROIDS;i++){      
        centroids.push_back(Centroid());
        centroids.at(i).randomInit();
    }

    for(int i=0;i<dataset.size();i++){
        dataset.at(i).findNearestCentroid(&centroids);
    }
    
    cout<<dataset.size()<<endl;

    return 0;
}