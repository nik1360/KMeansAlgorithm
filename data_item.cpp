#include "lib_const.hpp"

DataItem::DataItem(vector<double> var){
    variables=var;    
}

void DataItem::findNearestCentroid(vector<Centroid> &centroids){
    double squared_distances[NUM_CENTROIDS],diff;
    
    /*Compute the squared distances from the centroids*/
    for(int i=0;i<NUM_CENTROIDS;i++){   
        squared_distances[i]=0;
        for(int j=0;j<NUM_VARIABLES;j++){
            diff=getVariables()[j]-centroids[i].getVariables()[j];    
            diff=diff*diff;

            squared_distances[i]+=diff;
        }
    }
    /*Find the nearest centroid*/
    nearestDistance=squared_distances[0];
    nearestIndex=0;
    for(int i=1;i<NUM_CENTROIDS;i++){
        if(squared_distances[i]<nearestDistance){
            nearestDistance=squared_distances[i];
            nearestIndex=i;
        }
    }
    /*Update*/
    nearestDistance=sqrt(nearestDistance);
    
}

