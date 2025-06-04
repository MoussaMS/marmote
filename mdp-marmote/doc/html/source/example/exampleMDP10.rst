MDP Lesson 1: discounted MDP
============================

This lesson shows how to create and solve an infinite-horizon Markov Decision Process (MDP) with discounted criteria.

Using the library
-----------------

The header files to include for using a discounted MDP are:

.. code-block:: c++

    #include <list>
    #include <vector>
    #include <string>

    #include <marmoteCore/marmoteSparseMatrix.h>
    #include <marmoteCore/marmoteFullMatrix.h>
    #include <marmoteCore/marmoteInterval.h>
    #include <marmoteCore/marmoteSet.h>

    #include <marmoteMDP/marmoteDiscountedMDP.h>
    #include <marmoteMDP/marmoteFeedbackSolutionMDP.h>
    #include <marmoteMDP/marmoteSolutionMDP.h>

These includes allow using the basic objects from the MarmoteCore library (especially Sets, distributions, matrices...) as well as objects specific to Markov Decision Processes.

Build a simple MDP
------------------

Reminders about MDP
~~~~~~~~~~~~~~~~~~~

Formally, an MDP is a tuple *(S,A,P_a,R)* where:

* *S* is the state space
* *A* is the action space
* *P_a* is a collection of transition matrices, one matrix per action
* *R* is a reward (or cost) matrix

Description of the example implemented here
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We consider a simple model with two states x1=0 and x2=1 and in each state: two actions a1=0 and a2=1.

The reward matrix is:
::

        |  4.5 |  2   |
        | -1.5 |  3.0 |

where r(x,a) is the entry with row coordinate x and column coordinate a.
The entry r(x,a) represents the reward when in state x, action a is executed.

The transition matrices are:

Transition matrix for action 0:
::
        |  0.6 |  0.4 |
        |  0.5 |  0.5 |

Transition matrix for action 1:
::
    
        |  0.2 |  0.8 |
        |  0.7 |  0.3 |


Elements of a MDP object
~~~~~~~~~~~~~~~~~~~~~~~~

Attributes of the object
""""""""""""""""""""""""

An MDP in Marmote is an object that receives (at least) four important attributes:

1. The state space which is a ``MarmoteSet`` object (an object to handle sets).
   The simplest ``MarmoteSet`` object is the ``MarmoteInterval``. Here we use a ``MarmoteInterval`` for the state space.
2. The action space which is also a ``MarmoteSet`` object.
   In our case, it's also a ``MarmoteInterval`` object.
3. A vector of transition structures.
   Each entry in the vector corresponds to a ``TransitionStructure`` associated with a given action.

   - The ``TransitionStructure`` at the *a*-th entry of the list is the ``TransitionStructure`` associated with the action whose index is *a*.
   - A ``TransitionStructure`` describes the transition probability from state *i* to state *j*.
   - The ``TransitionStructure`` can be a ``FullMatrix`` or a ``SparseMatrix``. Here the *(i,j)* entry of a matrix gives the probability to move from state with index *i* to state with index *j*.

4. A reward (or cost).
   This is a ``TransitionStructure`` (preferably a ``FullMatrix``) in which the cost of action *a* in state *x* is defined.
   Rows are used for state indexes and columns for action indexes. Thus, the entry with indexes *(x,a)* represents the cost of action with index *a* in state with index *x*.

How to build the DiscountedMDP object
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Create state space and action space
"""""""""""""""""""""""""""""""""""

Here we create two MarmoteInterval objects for the state space and action space. The following two lines define two intervals ranging from 0 to 1.

.. code-block:: c++

    MarmoteSet* actionSpace = new MarmoteInterval(0, 1);
    MarmoteSet* stateSpace = new MarmoteInterval(0, 1);

Storing matrices
""""""""""""""""

A vector is used to store all transition matrices.
The number of matrices should match the size of the action space.

.. code-block:: c++

    vector<TransitionStructure*> trans(actionSpace->Cardinal());


Build transition matrices
"""""""""""""""""""""""""

We now create P0, a SparseMatrix object of size 2x2. The P0 matrix is a transition matrix.

.. code-block:: c++

    SparseMatrix* P0 = new SparseMatrix(2);

The command to initialize an entry is setEntry with the syntax setEntry(row, column, value).
Thus, the command P0->setEntry(0, 0, 0.6) assigns the value 0.6 to the entry with index (0, 0) of P0.

Now we define 4 non-zero entries for the P0 matrix.

.. code-block:: c++

    P0->setEntry(0, 0, 0.6);
    P0->setEntry(0, 1, 0.4);
    P0->setEntry(1, 0, 0.5);
    P0->setEntry(1, 1, 0.5);

    trans[0] = P0;

We now add a new SparseMatrix. Note that a SparseMatrix is an object from marmote.core.

.. code-block:: c++

    SparseMatrix* P1 = new SparseMatrix(2);
    P1->setEntry(0, 0, 0.2);
    P1->setEntry(0, 1, 0.8);
    P1->setEntry(1, 0, 0.7);
    P1->setEntry(1, 1, 0.3);

    trans[1] = P1;

Build reward matrix
"""""""""""""""""""

We create a FullMatrix object of size 2x2. This matrix is used to store the rewards associated with each (state, action) pair.

.. code-block:: c++

    FullMatrix* Reward = new FullMatrix(2, 2);

The following lines add non-zero values to the Reward matrix. More precisely:

- The first line adds the value 4.5 at position (0, 0) in the matrix.
- The second line adds the value 2 at position (0, 1) in the matrix.
- The third line adds the value -1.5 at position (1, 0) in the matrix.
- The fourth line adds the value 3 at position (1, 1) in the matrix.

.. code-block:: c++

    Reward->setEntry(0, 0, 4.5);
    Reward->setEntry(0, 1, 2);
    Reward->setEntry(1, 0, -1.5);
    Reward->setEntry(1, 1, 3);

Additional parameters of the discounted MDP
"""""""""""""""""""""""""""""""""""""""""""

Two additional parameters must be entered: beta and criterion

- beta is the discount factor for incorporating future values.
- criterion indicates the optimization criterion, which is either maximization ("max") or minimization ("min").

.. code-block:: c++

    double beta = 0.95;
    string criterion = "max";

Build a discounted MDP
""""""""""""""""""""""

We now build a DiscountedMDP object using the constructor, to which we pass the parameters defined in this page. The parameters of a DiscountedMDP are:

- criterion either min or max
- an object encoding the state space
- an object encoding the action space
- a vector of TransitionStructure
- a reward
- the discount factor

.. code-block:: c++

    DiscountedMDP* mdp = new DiscountedMDP(criterion, stateSpace, actionSpace, trans, Reward, beta);
    mdp->Write();

Solving the MDP
--------------

List of solution methods
~~~~~~~~~~~~~~~~~~~~~~~

We list here the different methods implemented to solve discounted Markov Decision Processes. Details of the methods can be found in the literature. All these methods return a ``FeedbackSolutionMDP`` object.

1. *Value Iteration* method named ``ValueIteration``
2. *Value Iteration using Gauss Seidel* method named ``ValueIterationGS``
3. Value Iteration with a given value function to initiate the process named ``ValueIterationInit``
4. Modified Policy Iteration method named ``PolicyIterationModified``
5. Modified Policy Iteration with Gauss Seidel method named ``PolicyIterationModifiedGS``

Running a solution method
~~~~~~~~~~~~~~~~~~~~~~~~

Parameters:

- epsilon: a precision threshold used to determine the convergence of the algorithm. The algorithm continues to iterate as long as the maximal difference between the new values and the old values in a state is greater than epsilon.
- maxIter: gives the maximum number of allowed iterations.

.. code-block:: c++

    double epsilon = 0.00001;
    int maxIter = 700;

Value-iteration
"""""""""""""""

To run a resolution by iterating the value. In order to find both the optimal policy and the optimal value in each of the states. The method returns a stationary solution.
The function returns a FeedbackSolutionMDP object.

.. code-block:: c++

    FeedbackSolutionMDP* optimum = mdp->ValueIteration(epsilon, maxIter);
    optimum->Write();

Gauss Seidel Value Iteration
""""""""""""""""""""""""""""

The following line performs ten value iterations on the MDP to find the optimal policy and the optimal state values, but now using the Gauss-Seidel improvement to evaluate the value in a state.

.. code-block:: c++

    FeedbackSolutionMDP* optimum2 = mdp->ValueIterationGS(epsilon, 10);
    optimum2->Write();

Value Iteration Init
""""""""""""""""""""

It is also possible to choose which value function will be used to start the value iteration process. To do this, a third parameter must be entered, which is a FeedbackSolution object whose value attribute will be used (see later for details on FeedbackSolution) to initiate the process.

.. code-block:: c++

    FeedbackSolutionMDP* optimum3 = mdp->ValueIterationInit(epsilon, 200, optimum2);
    cout << "Optimum 3" << endl;
    optimum3->Write();

Policy Iteration Modified
"""""""""""""""""""""""""

In a policy-based approach, it is possible to evaluate a policy with a given precision that is not the same as the precision used to stop the process.
Please note that there is no implementation of the Policy Iteration algorithm. Instead, the variant called Policy Iteration Modified in Puterman's book has been implemented.
Thus, for Policy Iteration Modified, the third and fourth parameters will be the precision with which a policy will be evaluated and the maximum number of iterations allowed to approximate the value.

.. code-block:: c++

    FeedbackSolutionMDP* optimum4 = mdp->PolicyIterationModified(epsilon, maxIter, 0.001, 100);
    cout << "optimum4" << endl;
    optimum4->Write();

Printing Information during the solving process
""""""""""""""""""""""""""""""""""""""""""""""

The following instruction modifies the display of internal information during the solving methods, such as the number of iterations performed and the achieved precision.

.. code-block:: c++

    mdp->changeVerbosity(true);

Policy Iteration Modified with Gauss Seidel
""""""""""""""""""""""""""""""""""""""""""

The Policy Iteration method can use (as described in Puterman's book) a Gauss Seidel evaluation. Please note that Policy Iteration Modified With Gauss Seidel Evaluation is not proven for all criteria (but it is for discounted criteria).

.. code-block:: c++

    FeedbackSolutionMDP* optimum5 = mdp->PolicyIterationModifiedGS(epsilon, maxIter, 0.001, 100);
    cout << "last test" << endl;
    optimum5->Write();

About the SolutionMDP object
----------------------------

The solution is stored with a ``FeedbackSolutionMDP`` object. This object has attributes that store a value and an action for each state.
Printing a ``FeedbackSolutionMDP`` first displays information about the policy. The information for all states in the state space is then displayed. All information for a state is displayed on one line, starting with the state index, the state value and the action associated with the value.

Clean up
~~~~~~~~

Memory cleanup: first ``ClearRew`` to clean up the reward (and thus the `Reward` matrix) then delete the `mdp`.

.. code-block:: c++

    mdp->ClearRew();

    delete mdp;
    delete optimum;
    delete optimum2;
    delete optimum3;
    delete optimum4;
    delete optimum5;
    delete actionSpace;
    delete stateSpace;
    delete P0;
    delete P1;


Download
--------

The source file can be downloaded :download:`here <../media/exampleMDP10.cpp>`.

Output
------

.. literalinclude:: ../media/exampleMDP10.res
    :language: text