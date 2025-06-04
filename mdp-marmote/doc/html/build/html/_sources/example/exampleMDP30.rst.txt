Example MDP 30
===============

**Infinite Horizon Total reward example.**

Description
-----------

This example is based on the Stochastic Shortest Path defined in the journal  `Tangente: <https://www.tangente-mag.com/numero.php?id=189>`_ number 75 about Operationnel Research (in french). It represents the choices of a schoolboy from house to highschool and the traveling times.

The MDP can be represented by (in french)

.. image:: ../_images/PlusCourtChemin2.jpg
    :scale: 60
    :align: center
    :alt: picture of the SSP MDP

|
| The *state space* is the set of *blue circles*.
| The *action space* is the set of *brown squares*.
|
| There are 9 states and 8 actions 

In this way we *build an MDP object without the vector of transition matrices*. The transition matrices are added after the building of the `TotalRewardMDP`.



Tasks performed:
----------------

1. We create a `totalRewardMDP` object by

.. code-block:: c++
    
     TotalRewardMDP *mdpSSP = new TotalRewardMDP(critere, stateSpace, actionSpace, Cost);
     /* where critere is the criteria, stateSpace the state space, actionSpace the action Sace and Cost the cost matrix */

2. We run `valueIteration` for 5 steps

.. code-block:: c++
    
    maxIter=5;
    cout<<"Printing solution from value iteration"<<endl;
    cout<<"Done : path length  "<<maxIter<<endl;
    SolutionMDP *optimum = mdpSSP->ValueIteration(epsilon, maxIter);
    cout<<"Print solution"<<endl;
    optimum->WriteSolution();

3. We run `valueIteration` for 50 steps, but only *7 steps* are required to compute the optimal solution.

.. code-block:: c++
    
     maxIter=50;
     cout<<"Printing solution from value iteration"<<endl;
     cout<<"Done : path length  "<< maxIter <<endl;
     SolutionMDP *optimum2 = mdpSSP->ValueIteration(epsilon, maxIter);
     cout<<"Print solution"<< endl;
     optimum2->WriteSolution();


Code
----

The whole code is 

.. code-block:: c++
 
    #include <list>
    #include <vector>
    #include <string>

    using namespace std;

    #include "marmoteCore/marmoteInterval.h"
    #include "marmoteCore/marmoteSparseMatrix.h"
    #include "marmoteMDP/marmoteTotalRewardMDP.h"
    #include "marmoteMDP/marmoteFeedbackSolutionMDP.h"
    #include "marmoteMDP/marmoteSolutionMDP.h"

    int main( int argc, char** argv )
    {
    /*Create the MDP object to test 1-dimension example and fill all its fields. */
    
    // create a penalties for non avaiable action (we should use the limit values but we do not this).
    double peno = +10000000000;

    
    int dim_SS; /* define dimension of the state space */
    int dim_AS; /* define dimension of the action space */
    
    // create the state space as an interval between 0 and 8
    MarmoteInterval *stateSpace = new MarmoteInterval(0,8);     
    // create the action space as an interval between 0 and 7
    MarmoteInterval *actionSpace = new MarmoteInterval(0,7);               
          
    // compute the size of the cardinal and store it in variable dim_SS
    dim_SS = stateSpace->Cardinal();
    dim_AS =actionSpace->Cardinal();
    
    /* create the matrix for the Cost. This is a dim_SS * dim_AS matrix */
    SparseMatrix *Cost  = new SparseMatrix(dim_SS, dim_AS);
    /* fill in the cost matrix */
    // this gives to the entrie (0,0) the value 15
    Cost->setEntry(0,0,15);
    Cost->setEntry(0,1,10);
    Cost->setEntry(0,2,5);
    Cost->setEntry(0,3,peno);
    Cost->setEntry(0,4,peno);
    Cost->setEntry(0,5,peno);
    Cost->setEntry(0,6,peno);
    Cost->setEntry(0,7,peno);

    Cost->setEntry(1,0,peno);
    Cost->setEntry(1,1,peno);
    Cost->setEntry(1,2,peno);
    Cost->setEntry(1,3,10);
    Cost->setEntry(1,4,30);
    Cost->setEntry(1,5,peno);
    Cost->setEntry(1,6,peno);
    Cost->setEntry(1,7,peno);
    
    Cost->setEntry(2,0,peno);
    Cost->setEntry(2,1,peno);
    Cost->setEntry(2,2,peno);
    Cost->setEntry(2,3,peno);
    Cost->setEntry(2,4,15);
    Cost->setEntry(2,5,peno);
    Cost->setEntry(2,6,peno);
    Cost->setEntry(2,7,peno);
    
    Cost->setEntry(3,0,peno);
    Cost->setEntry(3,1,peno);
    Cost->setEntry(3,2,peno);
    Cost->setEntry(3,3,peno);
    Cost->setEntry(3,4,peno);
    Cost->setEntry(3,5,10);
    Cost->setEntry(3,6,peno);
    Cost->setEntry(3,7,peno);
    
    Cost->setEntry(4,0,peno);
    Cost->setEntry(4,1,peno);
    Cost->setEntry(4,2,peno);
    Cost->setEntry(4,3,peno);
    Cost->setEntry(4,4,peno);
    Cost->setEntry(4,5,20);
    Cost->setEntry(4,6,peno);
    Cost->setEntry(4,7,peno);
    
    Cost->setEntry(5,0,peno);
    Cost->setEntry(5,1,peno);
    Cost->setEntry(5,2,peno);
    Cost->setEntry(5,3,peno);
    Cost->setEntry(5,4,peno);
    Cost->setEntry(5,5,60);
    Cost->setEntry(5,6,peno);
    Cost->setEntry(5,7,peno);
    
    Cost->setEntry(6,0,peno);
    Cost->setEntry(6,1,peno);
    Cost->setEntry(6,2,peno);
    Cost->setEntry(6,3,peno);
    Cost->setEntry(6,4,peno);
    Cost->setEntry(6,5,peno);
    Cost->setEntry(6,6,5);
    Cost->setEntry(6,7,peno);
    
    Cost->setEntry(7,0,peno);
    Cost->setEntry(7,1,peno);
    Cost->setEntry(7,2,peno);
    Cost->setEntry(7,3,5);
    Cost->setEntry(7,4,peno);
    Cost->setEntry(7,5,peno);
    Cost->setEntry(7,6,peno);
    Cost->setEntry(7,7,15);
    
    Cost->setEntry(8,0,peno);
    Cost->setEntry(8,1,peno);
    Cost->setEntry(8,2,peno);
    Cost->setEntry(8,3,peno);
    Cost->setEntry(8,4,peno);
    Cost->setEntry(8,5,peno);
    Cost->setEntry(8,6,0);
    Cost->setEntry(8,7,peno);
    
    
    /*initialize the criteria */
    string critere("min");

    //create and initialize epsilon.
    double epsilon = 0.00001;

    //create and initialize the maximum number of iterations allowed.
    int maxIter = 20;
    
    
    cout<<"Begining of building MDP"<<endl;
    // I create the MDP
    TotalRewardMDP *mdpSSP = new TotalRewardMDP(critere, stateSpace, actionSpace, Cost);
    cout << "End of building MDP" <<endl;

    cout<<"Add matrices"<<endl;
    /* create and fill matrix for the 0 action*/
    SparseMatrix *P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(0,1,0.6);
    P0->setEntry(0,2,0.4);
    P0->setEntry(1,1,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(2,2,1);
    P0->setEntry(3,3,1);
    P0->setEntry(4,4,1);
    P0->setEntry(5,5,1);
    P0->setEntry(6,6,1);
    P0->setEntry(7,7,1);
    P0->setEntry(8,8,1);
    mdpSSP->AddMatrix(0,P0);
    cout<<"Added matrix (action 0)"<< endl;
    
    /* Create matrix for the action 1*/
    P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(0,3,0.3);
    P0->setEntry(0,4,0.5);
    P0->setEntry(0,5,0.2);
    P0->setEntry(1,1,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(2,2,1);
    P0->setEntry(3,3,1);
    P0->setEntry(4,4,1);
    P0->setEntry(5,5,1);
    P0->setEntry(6,6,1);
    P0->setEntry(7,7,1);
    P0->setEntry(8,8,1);
    mdpSSP->AddMatrix(1,P0);
    cout<<"Added matrix (action 1)"<< endl;
    
    /* matrix for the action 2*/
    P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(0,6,0.15);
    P0->setEntry(0,7,0.85);
    P0->setEntry(1,1,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(2,2,1);
    P0->setEntry(3,3,1);
    P0->setEntry(4,4,1);
    P0->setEntry(5,5,1);
    P0->setEntry(6,6,1);
    P0->setEntry(7,7,1);
    P0->setEntry(8,8,1);
    mdpSSP->AddMatrix(2,P0);
    cout<<"Added matrix (action 2)"<< endl;
    
    /* matrix for the action 3*/
    P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(1,0,1);
    P0->setEntry(7,0,1);
    P0->setEntry(0,0,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(2,2,1);
    P0->setEntry(3,3,1);
    P0->setEntry(4,4,1);
    P0->setEntry(5,5,1);
    P0->setEntry(6,6,1);
    P0->setEntry(8,8,1);
    mdpSSP->AddMatrix(3,P0);
    cout<<"Added matrix (action 3)"<< endl;
    
    /* matrix for the  action 4*/
    P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(1,8,1);
    P0->setEntry(2,8,1);
    P0->setEntry(0,0,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(3,3,1);
    P0->setEntry(4,4,1);
    P0->setEntry(5,5,1);
    P0->setEntry(6,6,1);
    P0->setEntry(7,7,1);
    P0->setEntry(8,8,1);
    mdpSSP->AddMatrix(4,P0);
    cout<<"Added matrix (action 4)"<< endl;
    
    /* matrix for the action 5*/
    P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(3,8,1);
    P0->setEntry(4,8,1);
    P0->setEntry(5,8,1);
    P0->setEntry(1,1,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(0,0,1);
    P0->setEntry(2,2,1);
    P0->setEntry(6,6,1);
    P0->setEntry(7,7,1);
    P0->setEntry(8,8,1);
    mdpSSP->AddMatrix(5,P0);
    cout<<"Added matrix (action 5)"<< endl;
    
    /* matrix for the action 6*/
    P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(6,8,1);
    P0->setEntry(8,8,1);   
    P0->setEntry(2,2,1);
    P0->setEntry(0,0,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(3,3,1);
    P0->setEntry(4,4,1);
    P0->setEntry(5,5,1);
    P0->setEntry(1,1,1);
    P0->setEntry(7,7,1);
    mdpSSP->AddMatrix(6,P0);
    cout<<"Added matrix (action 6)"<< endl;
    
    /* matrix for the action 7*/
    P0 = new SparseMatrix(dim_SS); 
    P0->setEntry(7,6,1);
    P0->setEntry(0,0,1);  /* fill in the other transitions to have a stochastic matrix */    
    P0->setEntry(3,3,1);
    P0->setEntry(4,4,1);
    P0->setEntry(5,5,1);
    P0->setEntry(6,6,1);
    P0->setEntry(1,1,1);
    P0->setEntry(8,8,1);
    P0->setEntry(2,2,1);
    mdpSSP->AddMatrix(7,P0);
    cout<<"Added matrix (action 7)"<< endl;
    
    cout<<"Finishing Adding matrixes MDP"<< endl;

    cout<<"Writting MDP"<<endl;
    mdpSSP->WriteMDP();
    
     
    
    cout<<endl<<endl<<"###############################"<<endl;
    maxIter=5;
    cout<<"Printing solution from value iteration"<<endl;
    cout<<"Done : path length  "<<maxIter<<endl;
    SolutionMDP *optimum = mdpSSP->ValueIteration(epsilon, maxIter);
    cout<<"Print solution"<<endl;
    optimum->WriteSolution();

    maxIter=50;
    cout<<"Printing solution from value iteration"<<endl;
    cout<<"Done : path length  "<< maxIter <<endl;
    SolutionMDP *optimum2 = mdpSSP->ValueIteration(epsilon, maxIter);
    cout<<"Print solution"<< endl;
    optimum2->WriteSolution();

    cout<<endl<<endl<<"################################"<<endl;
    
    cout<<endl<<"********************************"<<endl;

    cout<<"Deleting"<<endl;
    delete optimum;
    delete optimum2;    
    
    cout<<"Deleting 2"<<endl;
    mdpSSP->ClearRew();
    for(int i=7;i>=0;i--){
       mdpSSP->DeleMatrix(i); 
    }
    

    cout<<"Deleting 3"<<endl;
    delete mdpSSP;


    return 0;
    }


Download
--------

The source file is :download:`here <../media/exampleMDP30.cpp>`


Output
------

.. literalinclude:: ../media/exampleMDP30.res
    :language: text
