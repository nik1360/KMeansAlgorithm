#include "lib_const.hpp"

using namespace std;

Centroid::Centroid(){
    associatedData=0;
    displacement=0;
    /*initilize the variables at random*/
    for(int j=0; j<NUM_VARIABLES;j++){
        variables.push_back((rand()%RAND_MAX));
    }
}

void Centroid::optimizePosition(int centroid_index, vector<DataItem> &dataset){
    vector<double> new_variables;
    double tmp_new_variable,diff;
    
    associatedData=0;
    displacement=0;
    
    /*Look for the data items associated to the centroid*/
    for(int i=0;i<dataset.size();i++){
        if((dataset[i].getNearestIndex())==(centroid_index)){       
            /*the data is associated to the centroid*/
            associatedData++;
            tmp_new_variable=0;
            /*sum the variables that are associated to the centroid*/
            for(int j=0;j<NUM_VARIABLES;j++){
                tmp_new_variable+=dataset[i].getVariables()[j];   
            }
            new_variables.push_back(tmp_new_variable);
        }
    }
    

    if(associatedData>0){
        for(int i=0;i<NUM_VARIABLES;i++){
            /*finish to compute the new coordinate*/
            new_variables[i]=new_variables[i]/associatedData;   
            /*compute the distance between the old centroid and th new centroid*/
            diff=new_variables[i]-variables[i]; 
            displacement+=diff*diff;
            /*update the variable of the centroid*/
            variables[i]=new_variables[i];
        }
        displacement=sqrt(displacement);
    }
}
