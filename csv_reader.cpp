#include "lib_const.hpp"

void CSVReader::readCsv(string filename, vector<DataItem> &dataset){
    int line_index=0,var_index;
    double val;
    string line,feature;
    ifstream in(filename);
    
    line_index=0;
    if(!in.fail()){
        while(getline(in,line)){
        
            if(line_index>0){
                dataset.push_back(DataItem());
                istringstream features(line);
                var_index=0;
                while(getline(features,feature,',')){
                    istringstream f(feature);
                    f>>val;
                    
                    dataset[line_index-1].setVariable(var_index,val);
                    var_index++;
                    
                }
            }
            line_index++;
        }
    }else{
        cout<<"ERROR:Cannot open "<<filename<<"!"<<endl;
    }    
}