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
    int public_associated_data;
    int c_index;

    c_index=centroid_index;
   




    /*Look for the data items associated to the centroid*/
    public_associated_data=0;
    #pragma omp parallel shared(centroid_index)
    {   
        double private_new_variables[NUM_VARIABLES]={0};
        int private_associated_data=0, d_index;

        #pragma omp for ordered
        for(int i=0;i<dataset.size();i++){
            d_index=dataset[i].getNearestIndex();
            if(d_index == c_index){       
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

    /*
    #pragma omp parallel for shared(centroid_index) reduction(+:tmp_associated_data) reduction(+:new_variables[:NUM_VARIABLES])
    for(int i=0;i<dataset.size();i++){
        if((dataset[i].getNearestIndex())==(centroid_index)){       
            
            tmp_associated_data++;
            
            double val;
            for(int j=0;j<NUM_VARIABLES;j++){
                val=dataset[i].getVariables()[j];
                new_variables[j]+=val;   
            }
        }
    }
    */
    associatedData=public_associated_data;
    tmp_displacement=0;

    if(associatedData>=1){
        for(int i=0;i<NUM_VARIABLES;i++){
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
    
    /*cout<<"NEW_VARIABLES"<<endl;
    for(int j=0;j<NUM_VARIABLES;j++){
        cout<<" "<<new_variables[j];   
    }*/
    //cout<<endl;
    cout<<displacement<<endl;
    
}
