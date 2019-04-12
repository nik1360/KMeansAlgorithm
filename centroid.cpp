#include "lib_const.hpp"

using namespace std;

Centroid::Centroid(){
    associatedData=0;
    variables=(double*)malloc(NUM_VARIABLES*sizeof(double));
    displacements=(double*)malloc(NUM_VARIABLES*sizeof(double));
}

void Centroid::randomInit(){
    for(int j=0; j<NUM_VARIABLES;j++){
        setVariable(j,rand()%RAND_MAX);
    }
}

void Centroid::deallocate(){
    free(variables);
    free(displacements);
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
            displacements[i]=(new_variables[i]/associatedData)-variables[i]; //compute the difference between the new and the old variables
            variables[i]=variables[i]+displacements[i];
        }
    }
    
    free(new_variables);
}

bool Centroid::checkDisplacements(){
    int converged_count;
    double threshold;

    threshold=0.000001;
    converged_count=0;
    for(int i=0;i<NUM_VARIABLES;i++){
        if(fabs(displacements[i])<threshold){
            converged_count++;
        }
    }
    if(converged_count==NUM_VARIABLES)
        return true;
    else
        return false;
}