3
Begining MDP building
End of building MDP
printing MDP
#############################################
write MDP
MDP type (discrete,continuous): discrete
MDP rule (min,max): max
#############################################
State space size: 2
Action space size: 2
State  dimension: 1
Action dimension: 1
#############################################
Transition matrix per action:
action: 0
0.2  0.8  
0.4  0.6  
action: 1
0.5  0.5  
0.7  0.3  
#############################################
Reward Matrix (state,action):
0.725  4.025  
3.125  2.025  
#############################################
#############################################
#############################################
write Infinite Discounted MDP
MDP Criteria : infinite discounted
Discount factor:0.7
#############################################
Printing solution from value iteration
#-- Value Iteration -- Done with 42 iterations and final distance=1.57101e-06
#Print solution of an MDP problem 
#Size of the state space : 2

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           12.2876   1
  1           11.3199   0
#############################################

Checking solutions
#-- Cost policy -- Done with 2 iterations and final distance=9.85337e-07
i= 0 sol= 12.2876
i= 1 sol= 11.3199
Printing solution from modified value iteration
#-- Policy Iteration Modified -- Done with 10 iterations and final distance=1.24789e-06
#Print solution of an MDP problem 
#Size of the state space : 2

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           12.2876   1
  1           11.3199   0
#############################################

********************************

Building second MDP
#############################################
write MDP
MDP type (discrete,continuous): discrete
MDP rule (min,max): max
#############################################
State space size: 2
Action space size: 2
State  dimension: 1
Action dimension: 1
#############################################
Transition matrix per action:
action: 0
0.2  0.8  
0.4  0.6  
action: 1
0.5  0.5  
0.7  0.3  
#############################################
Reward Matrix (state,action):
0.725  4.025  
3.125  2.025  
#############################################
#############################################
#############################################
write Infinite Discounted MDP
MDP Criteria : infinite discounted
Discount factor:0.7
#############################################
Second MDP built and printed
Printing solution from value iteration (second MDP)
#-- Value Iteration -- Done with 42 iterations and final distance=1.57101e-06
#Print solution of an MDP problem 
#Size of the state space : 2

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           12.2876   1
  1           11.3199   0
#############################################

Checking solutions
#-- Cost policy -- Done with 2 iterations and final distance=9.85337e-07
i= 0 sol= 12.2876
i= 1 sol= 11.3199
Printing solution from modified value iteration
#-- Policy Iteration Modified -- Done with 10 iterations and final distance=1.24789e-06
#Print solution of an MDP problem 
#Size of the state space : 2

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           12.2876   1
  1           11.3199   0
#############################################
Destructing
Destructing 2
Destructing 3
