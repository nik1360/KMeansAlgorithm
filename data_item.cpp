#include "lib_const.hpp"

DataItem::DataItem(){
    variables=(double*)malloc(NUM_VARIABLES*sizeof(double));
}