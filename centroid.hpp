#pragma once

#include "data_item.hpp"

#include <vector>

using namespace std;

class DataItem;
class Centroid{
    private:
        double *variables;
        double *displacements;
        int associatedData; //number of data items associated to the centroid
    public:
        Centroid();
        void deallocate();
        double getVariable(int index){return variables[index];};
        void setVariable(int index, double value){variables[index]=value;};
        void randomInit();
        void optimizePosition(int centroid_index,vector<DataItem> *dataset);
        bool checkDisplacements();
};