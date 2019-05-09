#pragma once

#include<fstream>
#include <vector>
#include "data_item.hpp"

using namespace std;

class CSVReader{
    private:
        fstream fin;
    public:
        bool readCsv(string filename, vector<DataItem> &dataset);
};