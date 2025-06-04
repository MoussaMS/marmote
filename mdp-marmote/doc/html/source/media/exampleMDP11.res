Size :	
3
Begining MDP building
End of building MDP
printing MDP
#############################################
write MDP
MDP type (discrete,continuous): discrete
MDP rule (min,max): max
#############################################
State space size: 3
Action space size: 3
State  dimension: 1
Action dimension: 1
#############################################
Transition matrix per action:
action: 0
0.7  0.3  0  
0  1  0  
0  0  1  
action: 1
1  0  0  
0  0  1  
0  0  1  
action: 2
0.8  0.2  0  
0  1  0  
0.8  0.1  0.1  
#############################################
Reward Matrix (state,action):
7  0  0  
0  -50  -1e+10  
-1e+10  -1e+10  32  
#############################################
#############################################
#############################################
write Infinite Discounted MDP
MDP Criteria : infinite discounted
Discount factor:0.95
#############################################
Printing solution from value iteration
#-- Value Iteration -- Done with 298 iterations and final distance=2.61428e-08
#Print solution of an MDP problem 
#Size of the state space : 3

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           21.8992   0
  1           1.17982   1
  2           53.8735   2
#############################################

Checking solutions
#-- Cost policy -- Done with 5 iterations and final distance=2.45996e-08
i= 0 sol= 21.8992
i= 1 sol= 1.17982
i= 2 sol= 53.8735

Modified Policy iteration
#-- Policy Iteration Modified -- Done with 75 iterations and final distance=2.52144e-08
#Print solution of an MDP problem 
#Size of the state space : 3

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           21.8992   0
  1           1.17982   1
  2           53.8735   2
#############################################

Gauss Seidel Value Iteration
#-- Value Iteration GS -- Done with 246 iterations and final distance=2.55276e-08
#Print solution of an MDP problem 
#Size of the state space : 3

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           21.8992   0
  1           1.17982   1
  2           53.8735   2
#############################################

********************************

Destructing
Destructing 2
