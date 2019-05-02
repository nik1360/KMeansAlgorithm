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
  
    double new_variables[NUM_VARIABLES]={0};
    double diff;
    int tmp_associated_data=0;
    
    associatedData=0;
    
    
    /*Look for the data items associated to the centroid*/
    
    #pragma omp parallel for reduction(+:tmp_associated_data) reduction(+:new_variables[:NUM_VARIABLES])
    for(int i=0;i<dataset.size();i++){
        if((dataset[i].getNearestIndex())==(centroid_index)){       
            /*the data is associated to the centroid*/
            tmp_associated_data++;
            /*sum the variables that are associated to the centroid*/
            for(int j=0;j<NUM_VARIABLES;j++){
                new_variables[j]+=dataset[i].getVariables()[j];   
            }
        }
    }
    
    
    associatedData=tmp_associated_data;
    displacement=0;
    
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

    }
    /*for(int j=0;j<NUM_VARIABLES;j++){
        cout<<" "<<new_variables[j];   
    }
    cout<<endl;
    */
    cout<<displacement<<" ";
    
}
