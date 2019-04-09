#pragma once

#include "centroid.hpp"
#include <vector>

using namespace std;

class DataItem{
    private:
        double *variables;
        double nearestDistance; //distance from the nearest centroid
        double nearestIndex;    //index of the nearest centroid
    public:
        DataItem();
        void deallocateVariables();
        double getVariable(int index){return variables[index];};
        void setVariable(int index, double value){variables[index]=value;};
        void findNearestCentroid(vector<Centroid> *centroids);
        int getNearestIndex(){return nearestIndex;};
       
};