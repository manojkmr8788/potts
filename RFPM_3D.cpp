#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "GCoptimization.h"
#include "randomc.h"
#include "mersenne.cpp"
#include "userintf.cpp"
#include "stoc1.cpp"
#include "stocc.h"
int main(void)
{
const int L=16,dim=3,num_labels = 3, J = 1;
const double delta = 1.8;

int i,j,l,L2=L*L,num_sites=L*L*L,S[num_sites];

int32 seed = (int32)time(0);
srand(seed);
StochasticLib1 sto(seed);

        //constructor for a graph with num_sites the total number of sites and num_labels the total number of labels
	GCoptimizationGeneralGraph *gc= new GCoptimizationGeneralGraph(num_sites,num_labels);
	
	//Set nearest neighbors, with edge weights Jij			
	 int nn[num_sites][dim];	
	 for (i = 0; i<num_sites; i++ ) 
	 {
	  int i0,j0,k0,i1,j1,k1;
		
   	  i0=i%L;
   	  j0=i%L2/L;
   	  k0=i/L2;
	  
   	  i1=(i0+1)%L;
   	  j1=(j0+1)%L;
   	  k1=(k0+1)%L; 

   	  nn[i][0]=i1+j0*L+k0*L2;
   	  nn[i][1]=i0+j1*L+k0*L2;
   	  nn[i][2]=i0+j0*L+k1*L2;
	  

	  gc->setNeighbors(i,nn[i][0],J);
	  gc->setNeighbors(i,nn[i][1],J);
	  gc->setNeighbors(i,nn[i][2],J);

	  }
	
	//set smoothness costs using arrays
	double interaction[num_labels*num_labels];
	for ( int l1 = 0; l1 < num_labels; l1++ )	
		for (int l2 = 0; l2 < num_labels; l2++ )
			interaction[l1+l2*num_labels] = -J*(l1==l2);
			
        gc->setSmoothCost(interaction);

	//next set up data costs 
	double hi, mean = 0, stdev=J*delta;
	for (i=0;i<num_sites;i++)
        	for(l=0;l<num_labels;l++){
            	hi = sto.Normal(mean,stdev);
                gc->setDataCost(i,l,-hi);
                }
    

	double Emin=0.0;
        int ini_con= 100; //number of initial conditions
	for(int n=1; n<=ini_con; n++){  //loop for different initial condition

	for(i=0;i<num_sites;i++){
        int label=rand()%num_labels;
        gc->setLabel(i,label);
        }

	gc->setLabelOrder(true); //set label order at random
	
	gc->expansion(10000); // run expansion for 10000 iterations

	double ener=gc->compute_energy(); // total energy after optimization

		if(ener<Emin){
		Emin=ener;
		for(i=0;i<num_sites;i++)
		S[i]=gc->whatLabel(i);    //storing minimum energy configuration among n runs 
		}
	}


	// Now compute observables from the minimum energy configuration 

	int m[num_labels];
	for(int l = 0; l<num_labels; l++)
	m[l]=0;

	for(i=0; i<num_sites; i++)
	m[S[i]]++;

    	int max = m[0];
    	for (int i = 1; i < num_labels; i++)
    	{
    	
        if (m[i]>max)
        max = m[i];
        
    	}

	double Mag=(num_labels*max/(1.0*num_sites)-1)/(num_labels-1); //magnetisation

	double tot_ej=0; //bond energy
	for(i=0;i<num_sites;i++)
 		for(j=0;j<dim;j++)
		tot_ej-=(S[i]==S[nn[i][j]]);

	double mean_ej=tot_ej/(1.0*num_sites); //bond energy per site

	cout<<ini_con<<"  "<<setprecision(15)<<Mag<<"    "<<mean_ej<<"    "<<Emin<<"\n";

	delete gc;
	
}//end of program
