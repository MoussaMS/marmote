/* Marmote and MarmoteMDP are free softwares: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Marmote is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Marmote. If not, see <http://www.gnu.org/licenses/>.

Copyright 2022 Emmanuel Hyon, Alain Jean-Marie*/


#include <marmoteCore/marmoteSparseMatrix.h>
#include <marmoteCore/marmoteInterval.h>
#include <marmoteMDP/marmoteAverageMDP.h>
#include <marmoteMDP/marmoteFeedbackSolutionMDP.h>
#include <marmoteMDP/marmoteSolutionMDP.h>

#include <list>
#include <vector>
#include <string>
#include <time.h>


using namespace std;

/**
 * @brief class to implement the average MDP described by the model of Howard for the car replacement model
 * @author Hyon, lip6
 * @date Apr 2023
 * @version 1.0
 *
 * 
 * The MDP comes from the monograph of Howard. It is the car replacement model with sparsity matrix but a large number of actions
 * This example create an example of an Average MDP 
 * 
 * Note that, in the Puterman book this Howard model (initially built for average criteria) is used for benchmarking with a discounted criteria.
 * 
 * In the monograph of Howard the computations are given for average criteria
 * 
 * special point : this code uses the constructor without transition vector
 * matrices are added one by one after building of the MDP.
 * 
*/


int main( int argc, char** argv )
{
    /* variable for storing values */
    double cost;
    int action;
    double proba;
    
    /* for time measuring */
    clock_t end_t, start_t;
    double total_t;
    
    /* create and initialize the MDP parameter criteria. */
    string critere("min");
     
    /*create and initialize the maximum number of iterations allowed end the precision.*/  
    /* create and initialize epsilon. */
    double epsilon = 0.000001;

    /*create and initialize the maximum number of iterations allowed.*/
    int maxIter = 700;

    /*Matrix for the actions */
    SparseMatrix *P0;
    
    /*Create the MDP object to test 1-dimension example and fill all its fields.*/
    MarmoteSet *actionSpace = new MarmoteInterval(0,40);
    MarmoteSet *stateSpace = new MarmoteInterval(1,40);
     
    /* create the array of values given by Howard */
    int T[41] ={1600,1460,1340,1230,1050,980,910,840,710,650,600,550,480,430,390,360,330,310,290,270,255,
        240,225,210,200,190,180,170,160,150,145,140,135,130,120,115,110,105,95,87,80 }; 
    int C[41] ={2000,1840,1680,1560,1300,1220,1150,1080,900,840,780,730,600,560,520,480,440,420,400,
        380,360,345,330,315,300,290,280,265,250,240,230,220,210,200,190,180,170,160,150,140,130};
    int E[41] ={50,53,56,59,62,65,68,71,75,78,81,84,87,90,93,96,100,103,106,109,112,115,118,121,125,129,133,137,141,145,150,155,160,167,175,182,190,205,220,235,250};
    
    double p[41]={1.0, 0.999, 0.998, 0.997, 0.996, 0.994, 0.991, 0.988, 0.985, 0.983, 0.98,
        0.975, 0.970, 0.965, 0.96, 0.955, 0.95, 0.945, 0.94, 0.935, 0.93, 0.925, 0.919, 0.91, 0.9, 0.89, 0.88, 0.865, 0.85, 0.82, 0.79, 0.76, 0.73, 0.66, 0.59, 0.51, 0.43, 0.3, 0.2, 0.1, 0.0 };
    
    /* fill in cost matrix */ 
    SparseMatrix *Reward  = new SparseMatrix(40,41);
    
    for(int i=0;i<40;i++){
        /* fill in action of keeping the car */
        /* the age varies from 1 to 40 so the index varies from 0 to 39 */
        cost=E[i+1]; /* state age 1 has index 0 */
        /* the action with index 0 is to do nothing */
        Reward->addToEntry(i,0,cost);
        /* fill in the other actions */
        /* action j is bying a car with age j-1 */
        for(int j=1;j<41;j++){
            cost=-T[i+1]+C[j-1]+E[j-1];
            Reward->addToEntry(i,j,cost);
        }
    }
    

    std::cout<< "Begining MDP building" <<  std::endl ;
    AverageMDP *mdp = new AverageMDP(critere, stateSpace, actionSpace, Reward);
    std::cout<<"End of building MDP" << std::endl ;

    /* entering the transitions matrices */
    /* Action 0 */
    P0 = new SparseMatrix(40); 
    for(int i=0;i<38;i++){
        proba=p[i+1];
        P0->addToEntry(i,i+1,proba);
        P0->addToEntry(i,39,1-proba);
    }
    P0->addToEntry(38,39,1);
    P0->addToEntry(39,39,1);
    mdp->AddMatrix(0,P0);
    
    /* others action */
    for(action=1;action<40;action++){
        /* Action buying a car of age action-1 */
        P0 = new SparseMatrix(40);
        for(int i=0;i<40;i++){
            proba=p[action-1];
            P0->addToEntry(i,action-1,proba);
            P0->addToEntry(i,39,1-proba);
        }
        mdp->AddMatrix(action,P0);
    }
    /* action 40*/
    action=40;
    P0 = new SparseMatrix(40);
    for(int i=0;i<40;i++){
        P0->addToEntry(i,39,1);
    }
    mdp->AddMatrix(action,P0);
    
    std::cout<<"printing MDP" << std::endl ;
    mdp->Write();
    
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Printing solution from value iteration" << std::endl ;
    /* call the function to solve the MDP with value iteration. */
    start_t =clock();
    SolutionMDP *sol = mdp->ValueIteration(epsilon,225);
    end_t= clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    cout <<"#---- Elapsing time " << total_t << " sec" << std::endl;
    sol->Write();
        
    std::cout<<"Printing solution from modified iteration" << std::endl ;
    /* call the function to solve the MDP with policy iteration modified. */
    start_t =clock();
    SolutionMDP *optimum = mdp->PolicyIterationModified(epsilon*0.1,35,epsilon*0.01,maxIter);
    end_t= clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    cout <<"#---- Elapsing time " << total_t << " sec" << std::endl;
    optimum->Write();
    
    std::cout<<"Printing solution from relative value iteration" << std::endl ;
    /* call the function to solve the MDP with relative value iteration. */
    start_t =clock();
    SolutionMDP *sol2 = mdp->RelativeValueIteration(epsilon,225);
    end_t= clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    cout <<"#---- Elapsing time " << total_t << " sec" << std::endl;
    sol2->Write();
    
       
    
        
    std::cout << std::endl <<"********************************\n" << std::endl ;
        
    cout << "Destructing" << endl;
    mdp->ClearRew();
    
    /* Now we delete all the transition matrices */
    
    for(action=0;action<41;action++){
        mdp->DeleMatrix(action);
    }
    
    delete mdp;
    delete optimum;
    delete sol;
    delete sol2;

    delete actionSpace;
    delete stateSpace;
	
    return 0;
}


