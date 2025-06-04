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


#include "marmoteCore/marmoteInterval.h"
#include "marmoteCore/marmoteSparseMatrix.h"
#include "marmoteCore/marmoteFullMatrix.h"
#include "marmoteMDP/marmoteAverageMDP.h"
#include "marmoteMDP/marmoteFeedbackSolutionMDP.h"
#include "marmoteMDP/marmoteSolutionMDP.h"

#include <list>
#include <vector>
#include <string>

using namespace std;
/**
 * @brief class to implement an example of an average MDP
 * @author Hyon, Lip6.
 * @version 0.3
 * @date Marc 2024
 * 
 * 
 * Problem Description 
 * 
 * This is exemple 8.5.3 of Puterman book
 * 
 * We expect 
 * 
 * 2.5 as expected cost 
 * 
 * span has to be equal to 0.147 after 5 iterations and span has to be equal to 0.005 after 12 iterations
 * 
 */
int main( int argc, char** argv )
{
    
    string critere("max");
        
    //create and initialize epsilon.
    double epsilon = 0.000001;

    //create and initialize the maximum number of iterations allowed.
    int maxIter = 150;
    
    //==================Test new features==================//

    //Create the MDP object to test 1-dimension example and fill all its fields.
    int dimPB=3;
    MarmoteSet *stateSpace = new MarmoteInterval(1,3);
    MarmoteSet *actionSpace = new MarmoteInterval(0,3);    
    
    // use an iterator on the action space
    MarmoteState actionbuffer = actionSpace->StateBuffer();
    
    vector<TransitionStructure*> trans(actionSpace->Cardinal());
    
    // first state
    actionSpace->FirstState(actionbuffer);
    SparseMatrix *P0 = new SparseMatrix(dimPB); /* matrix for the a_11 action*/
    P0->setEntry(0,2,1.0);
    trans.at(actionSpace->Index(actionbuffer)) = P0;

    actionSpace->NextState(actionbuffer);
    SparseMatrix *P1 = new SparseMatrix(dimPB);
    P1->setEntry(0,1,1.0);
    trans.at(actionSpace->Index(actionbuffer)) = P1;
    
    actionSpace->NextState(actionbuffer);
    SparseMatrix *P2 = new SparseMatrix(dimPB);
    P2->setEntry(1,0,1.0);
    trans.at(actionSpace->Index(actionbuffer)) = P2;
    
    actionSpace->NextState(actionbuffer);
    SparseMatrix *P3 = new SparseMatrix(dimPB);
    P3->setEntry(2,0,0.333333);
    P3->setEntry(2,1,0.333333);
    P3->setEntry(2,2,0.333334);
    trans.at(actionSpace->Index(actionbuffer)) = P3;
    
    FullMatrix *Reward  = new FullMatrix(dimPB,actionSpace->Cardinal());
    Reward->setEntry(0,0,2);
    Reward->setEntry(0,1,1);
    Reward->setEntry(0,2,-1000);
    Reward->setEntry(0,3,-1000);
    
    Reward->setEntry(1,0,-1000);
    Reward->setEntry(1,1,-1000);
    Reward->setEntry(1,2,2);
    Reward->setEntry(1,3,-1000);
    
    Reward->setEntry(2,0,-1000);
    Reward->setEntry(2,1,-1000);
    Reward->setEntry(2,2,-1000);
    Reward->setEntry(2,3,3);
        
    cout << "Begining building of MDP" << std::endl;
    AverageMDP *mdp = new AverageMDP(critere, stateSpace, actionSpace, trans,Reward);
    cout << "End of building MDP" << std::endl;

    cout << "Writing MDP" << endl;
    mdp->Write();
    mdp->changeVerbosity(true);
        
    cout << std::endl << "Writing the solution of value iteration after 5 iterates" << endl;
    //call the function to solve the MDP.
    FeedbackSolutionMDP *optimum = mdp->ValueIteration(epsilon,5);
    optimum->Write();
    delete optimum;
    
    cout << std::endl << "Writing the solution of value iteration after 12 iterates" << endl;
    //call the function to solve the MDP.
    optimum = mdp->ValueIteration(epsilon,12);
    optimum->Write();
    delete optimum;
    
    cout << std::endl << "Writing the solution of value iteration" << endl;
    //call the function to solve the MDP.
    optimum = mdp->ValueIteration(epsilon, maxIter);
    optimum->Write();
    
    cout <<endl << endl << "Checking solutions" << endl ;
    mdp->PolicyCost(optimum,epsilon, maxIter);
    for(int i=0;i<stateSpace->Cardinal();i++){
           cout << "i= " << i << " sol= " << optimum->getValueIndex(i) << endl;
    }
    delete optimum;
    
    cout <<endl << endl << "Writing solution of relative value iteration  with special state 0" << endl ;
    //call the function to solve the MDP.
    optimum = mdp->RelativeValueIteration(epsilon, maxIter);
    optimum->Write();
    delete optimum;
    
    
    cout << endl << "Writing solution relative value iteration with special state 1" << endl ;
    //call the function to solve the MDP.
    mdp->ChangeIndex(1);
    optimum = mdp->RelativeValueIteration(epsilon, maxIter);
    optimum->Write();
    delete optimum;
    
    cout << endl << "Writing solution relative value iteration with special state 2" << endl ;
    //call the function to solve the MDP.
    mdp->ChangeIndex(2);
    optimum = mdp->RelativeValueIteration(epsilon, maxIter);
    optimum->Write();
        
    cout <<endl << endl << "Checking solutions" << endl ;
    mdp->PolicyCost(optimum,epsilon, maxIter);
    for(int i=0;i<stateSpace->Cardinal();i++){
        cout <<"i= " << i << "  sol= " << optimum->getValueIndex(i) << endl;
    }
    delete optimum;
    
    cout << endl << "Writing solution modified policy iteration" << endl ;
    //call the function to solve the MDP.
    optimum = mdp->PolicyIterationModified(epsilon, maxIter,0.01,150);
    optimum->Write();
        
    cout <<endl << endl << "Checking solutions" << endl ;
    mdp->PolicyCost(optimum,epsilon, maxIter);
    for(int i=0;i<stateSpace->Cardinal();i++){
           cout <<"i= " << i << "  sol= " << optimum->getValueIndex(i) << endl;
    }
    cout<< endl << endl << "********************************" << endl ;
        
    cout << "Destruction"<< endl;
    mdp->ClearRew();
    delete mdp;
    delete optimum;
        
    cout << "Destruction 2" << endl;        
    // delete actionSpace;
    // delete stateSpace;
    
    cout << "Destruction 3" << endl;
    delete P0;
    delete P1;
    delete P2;
    delete P3;

    delete[] actionbuffer;

    delete stateSpace;
    delete actionSpace;

    return 0;
}


