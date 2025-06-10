Example MDP 21 : Average MDP and Policy handling
================================================

Description
-----------

This is an Average cost MDP


| This example assumes a single machine which has 4 states:
| — 0 = new
| — 1 = usable with minor deterioration
| — 2 = usable with major deterioration
| — 3 = unusable

| This example has 3 actions:
| — 0 = Do nothing: remain as is
|      Cost of action 0 in state 0 = 0
|      Cost of action 0 in state 1 = 1000
|      Cost of action 0 in state 2 = 3000
|      Cost of action 0 in state 3 = 3000
| — 1 = Tune-up: return to status 1. Cost in any state = 4000
| — 2 = Total repair: return to state 0. Cost in any state = 6000

This example demonstrates average MDP and policy handling using the marmote library.

The optimal policy is found using three different algorithms and several policies are evaluated and compared.

| Some policies considered and evaluated:
| — Ra = (0, 0, 0, 2) with average cost computed
| — Rc = (0, 0, 2, 2) with average cost computed  
| — Rd = (0, 2, 2, 2) with average cost computed

Tasks performed:
----------------

We create P0, P1, P2 ``SparseMatrix`` matrices that are the transition matrices associated with actions 0, 1, 2

We create Reward the matrix of the cost.

| In line with explanation above it is equal to:
| [    0  4000 6000 ]
| [ 1000  4000 6000 ]
| [ 3000  4000 6000 ]
| [ 3000  4000 6000 ]

For each of the solving methods we solve the MDP using Value Iteration, Policy Iteration Modified, and Relative Value Iteration

We consider policies Ra, Rc, Rd and we evaluate their costs by means of function ``PolicyCost()``

We perform structural analysis of the optimal solution using PropertiesValue and PropertiesPolicy classes.

Code
----

We build the spaces and transition matrices. The state space has dimension 4 and action space has dimension 3:

.. code-block:: c++
    
    int dim_SS = 4; // dimension of the state space
    int dim_AS = 3; // dimension of the action space
    
    MarmoteInterval *stateSpace = new MarmoteInterval(0,3);
    MarmoteInterval *actionSpace = new MarmoteInterval(0,2);

We create the transition matrices for each action:

.. code-block:: c++

    // matrix for action 0
    SparseMatrix *P0 = new SparseMatrix(dim_SS);
    P0->setEntry(0,1,0.875);
    P0->setEntry(0,2,0.0625);
    P0->setEntry(0,3,0.0625);
    P0->setEntry(1,1,0.75);
    P0->setEntry(1,2,0.125);
    P0->setEntry(1,3,0.125);
    P0->setEntry(2,2,0.5);
    P0->setEntry(2,3,0.5);
    P0->setEntry(3,3,1.0);
    
    // matrix for action 1
    SparseMatrix *P1 = new SparseMatrix(dim_SS);
    P1->setEntry(0,1,0.875);
    P1->setEntry(0,2,0.0625);
    P1->setEntry(0,3,0.0625);
    P1->setEntry(1,1,0.75);
    P1->setEntry(1,2,0.125);
    P1->setEntry(1,3,0.125);
    P1->setEntry(2,1,1.0);
    P1->setEntry(3,3,1.0);
    
    // matrix for action 2
    SparseMatrix *P2 = new SparseMatrix(dim_SS);
    P2->setEntry(0,1,0.875);
    P2->setEntry(0,2,0.0625);
    P2->setEntry(0,3,0.0625);
    P2->setEntry(1,0,1.0);
    P2->setEntry(2,0,1.0);
    P2->setEntry(3,0,1.0);
    
    SparseMatrix **trans = new SparseMatrix*[3];
    trans[0] = P0;
    trans[1] = P1;
    trans[2] = P2;

We create the reward matrix:

.. code-block:: c++

    FullMatrix *Reward = new FullMatrix(dim_SS, dim_AS);
    Reward->setEntry(0,0,0);
    Reward->setEntry(0,1,4000);
    Reward->setEntry(0,2,6000);
    Reward->setEntry(1,0,1000);
    Reward->setEntry(1,1,4000);
    Reward->setEntry(1,2,6000);
    Reward->setEntry(2,0,3000);
    Reward->setEntry(2,1,4000);
    Reward->setEntry(2,2,6000);
    Reward->setEntry(3,0,3000);
    Reward->setEntry(3,1,4000);
    Reward->setEntry(3,2,6000);

We build the AverageMDP. The criterion is a string equal to `"min"`:

.. code-block:: c++
    
    string criterion = "min";
    cout << "Building MDP" << std::endl;
    AverageMDP *mdp1 = new AverageMDP(criterion, stateSpace, actionSpace, trans, Reward);
    cout << "Building MDP finished" << std::endl;

Here is the code to launch ``ValueIteration(epsilon, maxIter)``: *epsilon* is the precision, *maxIter* the maximum number of allowed iterations:

.. code-block:: c++

    double epsilon = 0.00001;
    int maxIter = 500;
    
    cout << "Compute with Value Iteration" << std::endl;
    start_t = clock();
    FeedbackSolutionMDP *optimum = mdp1->ValueIteration(epsilon, maxIter);
    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    cout << "# Done : elapsing time " << total_t << " sec" << std::endl;
    optimum->WriteSolution();

Here is the code to launch ``PolicyIterationModified(epsilon, maxIter, epsilon2, maxIter2)``:

.. code-block:: c++

    cout << "Computation with Policy Iteration Modified" << std::endl;
    start_t = clock();
    FeedbackSolutionMDP *optimum2 = mdp1->PolicyIterationModified(epsilon, maxIter, 0.001, 1000);
    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    cout << "# Done : elapsing time " << total_t << " sec" << std::endl;
    optimum2->WriteSolution();

Here is the code to launch ``RelativeValueIteration(epsilon, maxIter)``:

.. code-block:: c++

    cout << "Computation with Relative Value Iteration" << std::endl;
    start_t = clock();
    FeedbackSolutionMDP *optimum3 = mdp1->RelativeValueIteration(epsilon, maxIter);
    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    cout << "# Done : elapsing time " << total_t << " sec" << std::endl;
    optimum3->WriteSolution();

| Here is the code to define a policy.
| A stationary policy is an object ``FeedbackSolutionMDP`` created with the constructor ``FeedbackSolutionMDP(dimension)``.
| We fix the value of the action with ``setActionIndex(index, value)``.
| Here the policy is *Ra=[0,0,0,2]*

.. code-block:: c++

    cout << std::endl << "Define Policy Ra" << std::endl;
    FeedbackSolutionMDP* politique = new FeedbackSolutionMDP(stateSpace->Cardinal());
    politique->setActionIndex(0,0);
    politique->setActionIndex(1,0);
    politique->setActionIndex(2,0);
    politique->setActionIndex(3,2);

| We now evaluate (or compute) the cost of a policy.
| This is done with ``PolicyCost(politique, epsilon, maxIter)``
| The method ``resetValue()`` resets the values to zero

.. code-block:: c++

    /* reset the value to zero*/
    politique->resetValue();
    /* reset the average cost to 0.0*/
    politique->setAvgCost(0.0);
    
    cout << std::endl << "Print solution Ra" << std::endl;
    double *solpol = mdp1->PolicyCost(politique, epsilon, maxIter);
    politique->setValue(solpol);
    politique->WriteSolution();

Here is the code to define and evaluate other policies:

.. code-block:: c++

    cout << "Modify the previous Policy and defining a new policy Rc" << std::endl;
    politique->setActionIndex(0,0);
    politique->setActionIndex(1,0);
    politique->setActionIndex(2,2);
    politique->setActionIndex(3,2);
    
    politique->resetValue();
    cout << "Print solution of Rc" << std::endl;
    solpol = mdp1->PolicyCost(politique, epsilon, maxIter);
    politique->setValue(solpol);
    politique->WriteSolution();
    
    cout << "Define Policy Rd" << std::endl;
    politique->setActionIndex(0,0);
    politique->setActionIndex(1,2);
    politique->setActionIndex(2,2);
    politique->setActionIndex(3,2);
    
    cout << "Print solution of Rd" << std::endl;
    solpol = mdp1->PolicyCost(politique, epsilon, maxIter);
    politique->setValue(solpol);
    politique->WriteSolution();

Here is the code for structural analysis of the value function:

.. code-block:: c++

    PropertiesValue *checkValue = new PropertiesValue(stateSpace);
    checkValue->avoidDetail();
    int monotone = checkValue->Monotonicity(optimum);
    cout << "Printing monotonicity property of value function (1 if increasing -1 if decreasing 0 otherwise) : " << monotone << std::endl;
    
    cout << "Verif convexity with details" << std::endl;
    checkValue->getDetail();
    int convex = checkValue->Convexity(optimum);
    cout << "Printing convexity property of value function (1 if convex -1 concave 0 otherwise) : " << convex << std::endl;

Here is the code for structural analysis of the policy:

.. code-block:: c++

    cout << "Checking Structural Properties of policy" << std::endl;
    PropertiesPolicy *checkPolicy = new PropertiesPolicy(stateSpace);
    
    monotone = checkPolicy->Monotonicity(optimum);
    cout << "PropertiesPolicy::MonotonicityOptimalPolicy=" << monotone << " (1 if increasing -1 if decreasing 0 otherwise) : " << std::endl;

Clean up:
~~~~~~~~~

.. code-block:: c++

    delete mdp1;
    delete stateSpace;
    delete actionSpace;
    delete P0;
    delete P1;
    delete P2;
    delete[] trans;
    delete Reward;
    delete optimum;
    delete optimum2;
    delete optimum3;
    delete politique;
    delete checkValue;
    delete checkPolicy;

Output
------

.. literalinclude:: ../media/exampleMDP21.res
    :language: text

Download
--------

The source file is :download:`here <../media/exampleMDP21.cpp>`

