#include "lib_const.hpp"

using namespace std;

int main(){
    CSVReader csv_reader;
    vector<DataItem> dataset;
    vector<Centroid> centroids;
    string csv_filename="prova.csv";
    
    srand(time(NULL));
    csv_reader.readCsv(csv_filename, &dataset); //create the dataset from the csv
    
    for(int i=0; i<NUM_CENTROIDS;i++){      //initialize centroids at random
        centroids.push_back(Centroid());
        centroids.at(i).randomInit();
    }

    

    return 0;
}