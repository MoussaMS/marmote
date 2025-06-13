/* Marmote and MarmoteMDP are free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Marmote is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Marmote. If not, see <http://www.gnu.org/licenses/>.

Copyright 2019 Emmanuel Hyon, Alain Jean-Marie
*/

/**
 * @brief class to implement an example of an average MDP
 * @author Hyon, Lip6.
 * @version 0.2
 * @date MAy
 *
 *
 * Problem Description
 *
 * This is exemple 8.5.3 of Puterman book
 *
 * We expect
 *
 * 2.5 as expecetd cost
 *
 * span equals 0.147 after 5 iterations span equals 0.005 after 12 iterations
 *
 */
#include <marmoteMarkovChain/marmoteMarkovChain.h>
#include <marmoteCore/marmoteSparseMatrix.h>
#include <marmoteCore/marmoteSet.h>
#include <marmoteCore/marmoteInterval.h>
#include <marmoteMDP/marmoteAverageMDP.h>
#include <marmoteMDP/marmoteFeedbackSolutionMDP.h>
#include <marmoteMDP/marmoteSolutionMDP.h>

#include <gtest/gtest.h>

using namespace std;

class MDP_AvgCriterionTest : public :: testing::Test {

protected:
  double epsilon = 0.000001; // the precision tolerance
  int maxIter = 150;         // limit on iterations
  MarmoteSet *stateSpace;
  MarmoteSet *actionSpace;
  SparseMatrix *P0, *P1, *P2, *P3;
  AverageMDP *mdp;

  virtual void SetUp() {
    string criterion("max");

    /* Create the MDP object to test 1-dimension example and fill all its fields. */
    int dimPB = 3;
    stateSpace = new MarmoteInterval(1,3);
    actionSpace = new MarmoteInterval(0,3);

    // use an iterator on the action space
    MarmoteState actionbuffer = actionSpace->StateBuffer();

    vector<TransitionStructure*> trans(actionSpace->Cardinal());

    // first state
    actionSpace->FirstState(actionbuffer);
    P0 = new SparseMatrix(dimPB); /* matrix for the a_11 action*/
    P0->addToEntry(0,2,1.0);
    trans.at(actionSpace->Index(actionbuffer)) = P0;

    actionSpace->NextState(actionbuffer);
    P1 = new SparseMatrix(dimPB);
    P1->addToEntry(0,1,1.0);
    trans.at(actionSpace->Index(actionbuffer)) = P1;

    actionSpace->NextState(actionbuffer);
    P2 = new SparseMatrix(dimPB);
    P2->addToEntry(1,0,1.0);
    trans.at(actionSpace->Index(actionbuffer)) = P2;

    actionSpace->NextState(actionbuffer);
    P3 = new SparseMatrix(dimPB);
    P3->addToEntry(2,0,0.333333);
    P3->addToEntry(2,1,0.333333);
    P3->addToEntry(2,2,0.333334);
    trans.at(actionSpace->Index(actionbuffer)) = P3;

    SparseMatrix *Reward  = new SparseMatrix(dimPB,actionSpace->Cardinal());
    Reward->addToEntry(0,0,2);
    Reward->addToEntry(0,1,1);
    Reward->addToEntry(0,2,-1000);
    Reward->addToEntry(0,3,-1000);

    Reward->addToEntry(1,0,-1000);
    Reward->addToEntry(1,1,-1000);
    Reward->addToEntry(1,2,2);
    Reward->addToEntry(1,3,-1000);

    Reward->addToEntry(2,0,-1000);
    Reward->addToEntry(2,1,-1000);
    Reward->addToEntry(2,2,-1000);
    Reward->addToEntry(2,3,3);

    //    cout << "Size :\t" << stateSpace->Cardinal() << std::endl;
    //    cout << "Begining building of MDP" << std::endl;
    mdp = new AverageMDP(criterion, stateSpace, actionSpace, trans,Reward);
    //    cout << "End of building MDP" << std::endl;

    delete[] actionbuffer;
  }

  virtual void TearDown() {
    //    cout << "Destruction"<< endl;
    mdp->ClearRew();
    delete mdp;
    //    cout << "Destruction 2" << endl;
    delete actionSpace; // moved to destructor of mdp
    delete stateSpace;  // moved to destructor of mdp

  }

};

TEST_F( MDP_AvgCriterionTest, ValueIteration5 ) {

  //    cout << std::endl << "Writing the solution of value iteration after 5 iterates" << endl;
  //    //call the function to solve the MDP.
  FeedbackSolutionMDP *optimum = dynamic_cast<FeedbackSolutionMDP*>( mdp->ValueIteration(epsilon, 5) );
  // optimum->WriteSolution();
  double* value = optimum->getValue();
  stateType* action = optimum->getAction();

  EXPECT_NEAR( value[0], 12.3704, 1e-4 );
  EXPECT_NEAR( value[1], 11.7778, 1e-4 );
  EXPECT_NEAR( value[2], 12.8272, 1e-4 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.51852, 1e-5 );

  delete optimum;

}

TEST_F( MDP_AvgCriterionTest, ValueIteration12 ) {

  //    cout << std::endl << "Writing the solution of value iteration after 12 iterates" << endl;
  //    //call the function to solve the MDP.
  FeedbackSolutionMDP *optimum = dynamic_cast<FeedbackSolutionMDP*>( mdp->ValueIteration(epsilon, 12) );
  // optimum->WriteSolution();
  double* value = optimum->getValue();
  stateType* action = optimum->getAction();

  EXPECT_NEAR( value[0], 29.8327, 1e-4 );
  EXPECT_NEAR( value[1], 29.3348, 1e-4 );
  EXPECT_NEAR( value[2], 30.3333, 1e-4 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.50019, 1e-5 );

  delete optimum;

}

TEST_F( MDP_AvgCriterionTest, ValueIteration ) {

  FeedbackSolutionMDP *optimum = dynamic_cast<FeedbackSolutionMDP*>( mdp->ValueIteration(epsilon, maxIter) );
  // optimum->WriteSolution();
  double* value = optimum->getValue();
  stateType* action = optimum->getAction();

  EXPECT_NEAR( value[0], 67.3333, 1e-4 );
  EXPECT_NEAR( value[1], 66.8333, 1e-4 );
  EXPECT_NEAR( value[2], 67.8333, 1e-4 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.5, 1e-5 );

  delete optimum;

}

TEST_F( MDP_AvgCriterionTest, RelativeValueIteration ) {

  // cout <<endl << endl << "Writing solution of relative value iteration  with special state 0" << endl ;
  FeedbackSolutionMDP *optimum =
      dynamic_cast<FeedbackSolutionMDP*>( mdp->RelativeValueIteration(epsilon, maxIter) );
  // optimum->WriteSolution();
  double* value = optimum->getValue();
  stateType* action = optimum->getAction();

  EXPECT_NEAR( value[0], -1000, 1e-4 );
  EXPECT_NEAR( value[1], -1000, 1e-4 );
  EXPECT_NEAR( value[2], 3, 1e-4 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.5, 1e-5 );

  delete optimum;

  // cout << endl << "Writing solution relative value iteration with special state 1" << endl ;
  mdp->ChangeIndex(1);
  optimum = dynamic_cast<FeedbackSolutionMDP*>( mdp->RelativeValueIteration(epsilon, maxIter) );
  value = optimum->getValue();
  action = optimum->getAction();

  EXPECT_NEAR( value[0], -1000, 1e-4 );
  EXPECT_NEAR( value[1], -1000, 1e-4 );
  EXPECT_NEAR( value[2], 3.5, 1e-4 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.5, 1e-5 );

  delete optimum;

  // cout << endl << "Writing solution relative value iteration with special state 2" << endl ;
  mdp->ChangeIndex(2);
  optimum = dynamic_cast<FeedbackSolutionMDP*>( mdp->RelativeValueIteration(epsilon, maxIter) );
  value = optimum->getValue();
  action = optimum->getAction();

  EXPECT_NEAR( value[0], -1000, 1e-4 );
  EXPECT_NEAR( value[1], -1000, 1e-4 );
  EXPECT_NEAR( value[2], 2.5, 1e-4 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.5, 1e-5 );

  delete optimum;

}

TEST_F( MDP_AvgCriterionTest, ModifiedPolicyIteration ) {

  //    cout << endl << "Writing solution modified policy iteration" << endl ;
  FeedbackSolutionMDP *optimum =mdp->PolicyIterationModified(epsilon, maxIter, 0.01, 150);
  //optimum->Write();

  double* value = optimum->getValue();
  stateType* action = optimum->getAction();

  EXPECT_NEAR( value[0], 69.8333, 1e-4 );
  EXPECT_NEAR( value[1], 69.3333, 1e-4 );
  EXPECT_NEAR( value[2], 70.3333, 1e-4 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.5, 1e-5 );

  delete optimum;
}


TEST_F( MDP_AvgCriterionTest, ModifiedPolicyIterationGS ) {

  //    cout << endl << "Writing solution modified policy iteration" << endl ;
  FeedbackSolutionMDP *optimum =mdp->PolicyIterationModifiedGS(epsilon, maxIter, 0.01, 150);
  //optimum->Write();

  double* value = optimum->getValue();
  stateType* action = optimum->getAction();

  EXPECT_NEAR( value[0], 111997, 1 );
  EXPECT_NEAR( value[1], 111999, 1 );
  EXPECT_NEAR( value[2], 112000, 1 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.5, 1e-5 );

  delete optimum;
}

TEST_F( MDP_AvgCriterionTest, ModifiedPolicyIterationGS5 ) {

  //    cout << endl << "Writing solution modified policy iteration" << endl ;
  FeedbackSolutionMDP *optimum = mdp->PolicyIterationModifiedGS(epsilon,5, 0.01, 150);
  //optimum->Write();

  double* value = optimum->getValue();
  stateType* action = optimum->getAction();


  EXPECT_NEAR( value[0], 3005, 1e-2 );
  EXPECT_NEAR( value[1], 3007, 1e-2 );
  EXPECT_NEAR( value[2], 3008, 1e-2 );
  EXPECT_EQ( action[0], 0 );
  EXPECT_EQ( action[1], 2 );
  EXPECT_EQ( action[2], 3 );
  EXPECT_NEAR( optimum->getAvgCost(), 2.5, 1e-3 );

  delete optimum;
}

// Original source code of marmoteMDPBasicExample20/main20.cpp copied 31/05/2022 18:23

//#include "marmoteCore/marmoteInterval.h"
//#include "marmoteCore/marmoteSet.h"
//#include "marmoteCore/marmoteSparseMatrix.h"
//#include "marmoteMDP/marmoteAverageMDP.h"
//#include "marmoteMDP/marmoteFeedbackSolutionMDP.h"
//#include "marmoteMDP/marmoteSolutionMDP.h"


//#include <iostream>
////#include <sstream>
//#include <stdlib.h>
////#include <stdio.h>
////#include <values.h>
////#include <time.h>

//#include <list>
//#include <vector>
//#include <string>

//using namespace std;
///**
// * @brief class to implement an example of an average MDP
// * @author Hyon, Lip6.
// * @version 0.2
// * @date MAy
// *
// *
// * Problem Description
// *
// * This is exemple 8.5.3 of Puterman book
// *
// * We expect
// *
// * 2.5 as expecetd cost
// *
// * span equals 0.147 after 5 iterations span equals 0.005 after 12 iterations
// *
// */
//int main( int argc, char** argv )
//{

//    string critere("max");

//    //create and initialize epsilon.
//    double epsilon = 0.000001;

//    //create and initialize the maximum number of iterations allowed.
//    int maxIter = 150;

//    //==================Test new features==================//

//    //Create the MDP object to test 1-dimension example and fill all its fields.
//    int dimPB=3;
//    MarmoteSet *stateSpace = new MarmoteInterval(1,3);
//    MarmoteSet *actionSpace = new MarmoteInterval(0,3);

//    // use an iterator on the action space
//    MarmoteState actionbuffer = actionSpace->StateBuffer();

//    vector<TransitionStructure*> trans(actionSpace->Cardinal());

//    // first state
//    actionSpace->FirstState(actionbuffer);
//    SparseMatrix *P0 = new SparseMatrix(dimPB); /* matrix for the a_11 action*/
//    P0->addToEntry(0,2,1.0);
//    trans.at(actionSpace->Index(actionbuffer)) = P0;

//    actionSpace->NextState(actionbuffer);
//    SparseMatrix *P1 = new SparseMatrix(dimPB);
//    P1->addToEntry(0,1,1.0);
//    trans.at(actionSpace->Index(actionbuffer)) = P1;

//    actionSpace->NextState(actionbuffer);
//    SparseMatrix *P2 = new SparseMatrix(dimPB);
//    P2->addToEntry(1,0,1.0);
//    trans.at(actionSpace->Index(actionbuffer)) = P2;

//    actionSpace->NextState(actionbuffer);
//    SparseMatrix *P3 = new SparseMatrix(dimPB);
//    P3->addToEntry(2,0,0.333333);
//    P3->addToEntry(2,1,0.333333);
//    P3->addToEntry(2,2,0.333334);
//    trans.at(actionSpace->Index(actionbuffer)) = P3;

//    SparseMatrix *Reward  = new SparseMatrix(dimPB,actionSpace->Cardinal());
//    Reward->addToEntry(0,0,2);
//    Reward->addToEntry(0,1,1);
//    Reward->addToEntry(0,2,-1000);
//    Reward->addToEntry(0,3,-1000);

//    Reward->addToEntry(1,0,-1000);
//    Reward->addToEntry(1,1,-1000);
//    Reward->addToEntry(1,2,2);
//    Reward->addToEntry(1,3,-1000);

//    Reward->addToEntry(2,0,-1000);
//    Reward->addToEntry(2,1,-1000);
//    Reward->addToEntry(2,2,-1000);
//    Reward->addToEntry(2,3,3);

//    //test of the  object to test 1-dimension example.
//    cout << "Enumerate State Space:"<< std::endl;
//    //stateSpace->Enumerate(std::cout);
//    cout << std::endl;

//    cout << "Enumerate action Set:"<< std::endl;
//    // pb avec la fonction enumerate
//    //actionSpace->Enumerate(std::cout);
//    cout << std::endl;

//    cout << "Enumerate action Set by index:"<< std::endl;
//    actionSpace->FirstState(actionbuffer);
//    for(int i=0;i<actionSpace->Cardinal();i++){
//        cout << " Action " << i << " index of Action : " << actionSpace->Index(actionbuffer) << std::endl;
//        actionSpace->NextState(actionbuffer);
//    }
//    cout << std::endl;

//    cout << "Size :\t" << stateSpace->Cardinal() << std::endl;
//    cout << "Begining building of MDP" << std::endl;
//    AverageMDP *mdp = new AverageMDP(critere, stateSpace, actionSpace, trans,Reward);
//    cout << "End of building MDP" << std::endl;

//    cout << "Writing MDP" << endl;
//    mdp->WriteMDP();


//    cout << std::endl << "Writing the solution of value iteration after 5 iterates" << endl;
//    //call the function to solve the MDP.
//    SolutionMDP *optimum = mdp->ValueIteration(epsilon, 5);
//    optimum->WriteSolution();
//    delete optimum;

//    cout << std::endl << "Writing the solution of value iteration after 12 iterates" << endl;
//    //call the function to solve the MDP.
//    optimum = mdp->ValueIteration(epsilon, 12);
//    optimum->WriteSolution();
//    delete optimum;

//    cout << std::endl << "Writing the solution of value iteration" << endl;
//    //call the function to solve the MDP.
//    optimum = mdp->ValueIteration(epsilon, maxIter);
//    optimum->WriteSolution();

//    cout <<endl << endl << "Checking solutions" << endl ;
//    double *sol = mdp->PolicyCost(optimum,epsilon, maxIter);
//    for(int i=0;i<stateSpace->Cardinal();i++){
//           cout << "i= " << i << " sol= " << sol[i] << endl;
//    }
//    free(sol);
//    delete optimum;

//    cout <<endl << endl << "Writing solution of relative value iteration  with special state 0" << endl ;
//    //call the function to solve the MDP.
//    optimum = mdp->RelativeValueIteration(epsilon, maxIter);
//    optimum->WriteSolution();
//    delete optimum;


//    cout << endl << "Writing solution relative value iteration with special state 1" << endl ;
//    //call the function to solve the MDP.
//    mdp->ChangeIndex(1);
//    optimum = mdp->RelativeValueIteration(epsilon, maxIter);
//    optimum->WriteSolution();
//    delete optimum;

//    cout << endl << "Writing solution relative value iteration with special state 2" << endl ;
//    //call the function to solve the MDP.
//    mdp->ChangeIndex(2);
//    optimum = mdp->RelativeValueIteration(epsilon, maxIter);
//    optimum->WriteSolution();

//    cout <<endl << endl << "Checking solutions" << endl ;
//    sol = mdp->PolicyCost(optimum,epsilon, maxIter);
//    for(int i=0;i<stateSpace->Cardinal();i++){
//        cout <<"i= " << i << "  sol= " << sol[i] << endl;
//    }
//    free(sol);
//    delete optimum;

//    cout << endl << "Writing solution modified value iteration" << endl ;
//    //call the function to solve the MDP.
//    optimum = mdp->PolicyIterationModified(epsilon, maxIter,0.01,150);
//    optimum->WriteSolution();

//    cout <<endl << endl << "Checking solutions" << endl ;
//    sol = mdp->PolicyCost(optimum,epsilon, maxIter);
//    for(int i=0;i<stateSpace->Cardinal();i++){
//           cout <<"i= " << i << "  sol= " << sol[i] << endl;
//    }

//    cout<< endl << endl << "********************************" << endl ;

//    cout << "Destruction"<< endl;
//    mdp->ClearRew();
//    delete mdp;
//    delete optimum;

//    cout << "Destruction 2" << endl;
//    delete actionSpace;
//    delete stateSpace;

//    cout << "Destruction 3" << endl;
//    delete P0;
//    delete P1;
//    delete P2;
//    delete P3;

//    delete[] sol;

//    return 0;
//}
