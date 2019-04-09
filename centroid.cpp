#include "lib_const.hpp"

Centroid::Centroid(){
    associatedData=0;
    variables=(double*)malloc(NUM_VARIABLES*sizeof(double));
}

void Centroid::randomInit(){
    for(int j=0; j<NUM_VARIABLES;j++){
        setVariable(j,rand()%RAND_MAX);
    }
}

void Centroid::deallocateVariables(){
    free(variables);
}

void Centroid::optimizePosition(int centroid_index, vector<DataItem> *dataset){
    double *new_variables;
    new_variables=(double*)malloc(NUM_VARIABLES*sizeof(double));
    
    associatedData=0;

    for(int i=0;i<NUM_VARIABLES;i++){
        new_variables[i]=0;
    }
    
    /*Compute the new values of the variables of the centroid*/
    for(int i=0;i<dataset->size();i++){
        if((dataset->at(i).getNearestIndex())==(centroid_index)){       //Look for all the DataItems associated to the centroid
            associatedData++;
            for(int j=0;j<NUM_VARIABLES;j++){
                new_variables[j]+=dataset->at(i).getVariable(j);    //Sum the values of a paricular variable for every DataItem associated to the centroid
            }
        }
    }

    /*Update the values of the variables*/
    if(associatedData>0){
        for(int i=0;i<NUM_VARIABLES;i++){
            variables[i]=new_variables[i]/associatedData;
        }
    }
    
    free(new_variables);
}