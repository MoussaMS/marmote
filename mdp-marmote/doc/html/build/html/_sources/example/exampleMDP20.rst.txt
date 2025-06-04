Example MDP 20
===============

Description
-----------

We want to implement a model of MDP proposed by Puterman. 

This is exemple 8.5.3 comes from Puterman book 
*Markov Decision Processes: Discrete Stochastic Dynamic Programming* (1994). 

It is an averageMDP.
The state space has dimension 3 and the action space has dimension 3.

| The results:   
| We should have 2.5 as expected cost 
| The span has to be equal to 0.147 after 5 iterations 
| The span has to be equal to 0.005 after 12 iterations.


Tasks performed:
----------------

    
#. Create three ``SparseMatrix`` objects interval
#. Create one ``SparseMatrix`` for reward with the addings of penalizations to have the same action space by state
#. Create an ``AverageMDP`` objects
#. Using *value iteration*

   *  Writing the solution of value iteration after 5 iterates
   *  Writing the solution of value iteration after 12 iterates
   *  Writing the solution of value iteration 

#. Using *relative value iteration* with different state on which we compute the average cost  
   
Code
----


We create an Average criteria MDP

.. code-block:: c++

    AverageMDP *mdp = new AverageMDP(critere, stateSpace, actionSpace, trans, Reward);

We run the value iteration with 5 iterations (epsilon is the precision above

.. code-block:: c++

    SolutionMDP *optimum = mdp->ValueIteration(epsilon, 5);
    optimum->WriteSolution();
    delete optimum; /* we delete   the solution (since we will reuse the same object) */


We select the state whose index is 1 with ``ChangeIndex`` and we run the ``relativeValueIteration``

.. code-block:: c++

    mdp->ChangeIndex(1);
    optimum = mdp->RelativeValueIteration(epsilon, maxIter);
    optimum->WriteSolution();


Output
------

We illustrate here the output of a feedbackpolicy for average model

.. code-block:: bash

    Average Cost (only for average models) :          2.51852
    Solution of the entered problem model:
    - column 1: index of the state
    - column 2: Value function 
    - column 3: Optimal action 
    
    0           12.3704   0
    1           11.7778   2
    2           12.8272   3

    
Now, the global output of the program is given

.. literalinclude:: ../media/exampleMDP20.res
    :language: text

Download
--------

The source file is :download:`here <../media/exampleMDP20.cpp>`

