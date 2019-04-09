#include "lib_const.hpp"

Centroid::Centroid(){
    variables=(double*)malloc(NUM_VARIABLES*sizeof(double));
}

void Centroid::randomInit(){
    for(int j=0; j<NUM_VARIABLES;j++){
        setVariable(j,rand()%RAND_MAX);
    }
}