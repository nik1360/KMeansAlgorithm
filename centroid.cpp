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
  
    double new_variables[NUM_VARIABLES]={0};
    double diff,diff2,tmp_displacement;
    int tmp_associated_data;
    int i,j;


    /*Look for the data items associated to the centroid*/
    
    tmp_associated_data=0;
    #pragma omp parallel for shared(centroid_index) private(j) reduction(+:tmp_associated_data) reduction(+:new_variables[:NUM_VARIABLES])
    for(i=0;i<dataset.size();i++){
        
        if((dataset[i].getNearestIndex())==(centroid_index)){       
            /*the data is associated to the centroid*/
            tmp_associated_data++;
            /*sum the variables that are associated to the centroid*/
            for(j=0;j<NUM_VARIABLES;j++){
                new_variables[j]+=dataset[i].getVariables()[j];   
            }
        }
    }
    associatedData=tmp_associated_data;
    
    tmp_displacement=0;

    cout<<"VARIABLES:"<<endl;
    for(int j=0;j<NUM_VARIABLES;j++){
        cout<<" "<<variables[j];   
    }
    cout<<endl;

    if(associatedData>=1){
        #pragma omp aprallel for reduction(+:tmp_displacement)
        for(i=0;i<NUM_VARIABLES;i++){
            /*finish to compute the new coordinate*/
            new_variables[i]=new_variables[i]/associatedData;   
            /*compute the distance between the old centroid and the new centroid*/
            diff=variables[i] - new_variables[i];
            diff2=diff*diff;

            if(fabs(diff2)>0.00000000001){
                tmp_displacement+=diff2;
            }
            /*update the variable of the centroid*/
            variables[i]=new_variables[i];

        }

    }
    
    displacement=tmp_displacement;
    
    cout<<"NEW_VARIABLES"<<endl;
    for(int j=0;j<NUM_VARIABLES;j++){
        cout<<" "<<new_variables[j];   
    }
    cout<<endl;
    cout<<displacement<<endl;
    
    //cout<<displacement<<" ";
    
}
