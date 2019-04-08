#include "constants.hpp"


using namespace std;

int main(){

    vector<DataItem> dataset;
    int line_index=0,var_index;
    double val;

    fstream fin;
    string entry,line,filename="prova.csv";
    fin.open(filename);
    
    line_index=0;
    while(getline(fin, line)){  //reading a line of the CSV
        if(line_index>0){    //the first line does not contain values
            istringstream s(line);
            dataset.push_back(DataItem()); //create a new DataItem in the dataset 
            
            var_index=0;
            while(getline(s,entry,';'))
            {
                istringstream ss(entry);
                ss >> val;
                dataset.at(line_index-1).setVariable(var_index,val);    //insert values of the variables in the DataItem
                var_index++;
            }
        }
        line_index++;
    }

    return 0;
}