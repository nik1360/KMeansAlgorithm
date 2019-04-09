#pragma once

#include "data_item.hpp"
#include <vector>

class Centroid{
    private:
        double *variables;
        int associatedData; //number of data items associated to the centroid
    public:
        Centroid();
        void deallocateVariables();
        double getVariable(int index){return variables[index];};
        void setVariable(int index, double value){variables[index]=value;};
        void randomInit();
        void optimizePosition(int centroid_index, vector<DataItem> *dataset);
};