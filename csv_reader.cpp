#include "lib_const.hpp"

void CSVReader::readCsv(string filename, vector<DataItem> &dataset){
    int line_index;
    double val;
    string line,entry;
    ifstream in(filename);
    vector<double> tmp;
    
    line_index=0;
    if(!in.fail()){
        while(getline(in,line)){
            if(line_index>0){
                istringstream entries(line);
                while(getline(entries,entry,',')){
                    istringstream s(entry);
                    s>>val;
                    tmp.push_back(val);
                }
                dataset.push_back(DataItem(tmp));
                tmp.clear();
            }
            line_index++;
        }
    }else{
        cout<<"ERROR:Cannot open "<<filename<<"!"<<endl;
    }    
}