#pragma once

#include "data_item.hpp"
#include <vector>

using namespace std;

class DataItem;
class Centroid{
    private:
        vector<double> variables;
        double displacement;    //distance between the old centroid and the new centroid
        int associatedData; //number of data items associated to the centroid
    public:
        Centroid();
        vector<double> getVariables(){return variables;};
        double getDisplacement(){return displacement;};
        void optimizePosition(int centroid_index,vector<DataItem> &dataset);
};