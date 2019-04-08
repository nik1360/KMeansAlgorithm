#include "constants.hpp"
#include "data_item.hpp"

DataItem::DataItem(){
    variables=(double*)malloc(NUM_VARIABLES*sizeof(double));
}