#pragma once

class Centroid{
    private:
        double *variables;
    public:
        Centroid();
        double getVariable(int index){return variables[index];};
        void setVariable(int index, double value){variables[index]=value;};
        void randomInit();
};