#include "lib_const.hpp"

using namespace std;

Centroid::Centroid(){
    associatedData=0;
    displacement=0;
    /*initilize the variables at random*/
    for(int j=0; j<NUM_VARIABLES;j++){
        variables.push_back((rand()%RAND_MAX));
    }
}

void Centroid::optimizePosition(int centroid_index, vector<DataItem> &dataset){
  
    int public_associated_data;
    double new_variables[NUM_VARIABLES]={0};
    double diff,diff2,tmp_displacement;
    
    /*Look for the data items associated to the centroid, sum the variables and count the item associated to the centroid*/
    public_associated_data=0;
    #pragma omp parallel shared(centroid_index)
    {   
        double private_new_variables[NUM_VARIABLES]={0};
        int private_associated_data=0, d_index;

        #pragma omp for schedule (static,1)
        for(int i=0;i<dataset.size();i++){
            d_index=dataset[i].getNearestIndex();
            if(d_index == centroid_index){       
                /*the data is associated to the centroid*/
                private_associated_data++;
                /*sum the variables that are associated to the centroid*/
                double val;
                for(int j=0;j<NUM_VARIABLES;j++){
                    val=dataset[i].getVariables()[j];
                    private_new_variables[j]+=val;   
                }
            }
        }
        #pragma omp critical
        {
            public_associated_data+=private_associated_data;
            for(int j=0;j<NUM_VARIABLES;j++){
                new_variables[j]+=private_new_variables[j];  
            }
        }

    }

    associatedData=public_associated_data;
    tmp_displacement=0;

    if(associatedData>=1){
        for(int i=0;i<NUM_VARIABLES;i++){
            /*finish to compute the new coordinate*/
            new_variables[i]=new_variables[i]/associatedData;   
            /*compute the distance between the old centroid and the new centroid*/
            diff=variables[i] - new_variables[i];
            
            /*if the difference is below 0,00001%, it is not considered for the displacement*/
            /*this is to avoid problems related to the floating point approximations*/
            if(fabs(diff)>fabs(variables[i]/100000)){
                diff2=diff*diff;
                tmp_displacement+=diff2;
            }

            /*update the variable of the centroid*/
            variables[i]=new_variables[i];

        }

    }
    
    if(fabs(tmp_displacement>0.000000001)){
        displacement=sqrt(tmp_displacement);
    }else{
        displacement=0;
    }
    
}
