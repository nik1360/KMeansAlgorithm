#pragma once
class DataItem{
    private:
        double *variables;
    public:
        double getVariable(int index){return variables[index];};
        void setVariable(int index, double value){variables[index]=value;};
        DataItem();
};