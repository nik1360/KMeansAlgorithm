#include "lib_const.hpp"

void CSVReader::readCsv(string filename, vector<DataItem> *dataset){
    int line_index=0,var_index;
    double val;

    string entry,line;
    fin.open(filename);
    
    if(!fin.fail()){
        line_index=0;
        while(getline(fin, line)){  //reading a line of the CSV
            if(line_index>0){    //the first line does not contain values
                istringstream s(line);
                dataset->push_back(DataItem()); //create a new DataItem in the dataset 
                
                var_index=0;
                while(getline(s,entry,';'))
                {
                    istringstream ss(entry);
                    ss >> val;
                    dataset->at(line_index-1).setVariable(var_index,val);    //insert values of the variables in the DataItem
                    var_index++;
                }
            }
            line_index++;
        }
        for(int i =0;i< dataset->size();i++){
            for (int j=0;j< NUM_VARIABLES;j++){
                cout<<dataset->at(i).getVariable(j)<<" ";
            }
            cout<<endl;
        }

        fin.close();
    }else{
        cout<<"ERROR:Cannot open "<<filename<<"!"<<endl;
    }
    
}