Added transition matrix 0 to vector
Added transition matrix 1 to vector
Added transition matrix 2 to vector
Added transition matrix 3 to vector
Begining building MDP
MDP built
print MDP
##############################################
write Finite Horizon MDP with (potentially) Discounted Costs
MDP Criteria : finiteHorizonDiscounted
Horizon: 3
Discount Factor: 1

#############################################
write MDP
MDP type (discrete,continuous): discrete
MDP rule (min,max): max
#############################################
State space size: 4
Action space size: 4
State  dimension: 1
Action dimension: 1
#############################################
Transition matrix per action:
action: 0
1  0  0  0  
0.75  0.25  0  0  
0.25  0.5  0.25  0  
0  0.25  0.5  0.25  
action: 1
0.75  0.25  0  0  
0.25  0.5  0.25  0  
0  0.25  0.5  0.25  
0  0.25  0.5  0.25  
action: 2
0.25  0.5  0.25  0  
0  0.25  0.5  0.25  
0  0.25  0.5  0.25  
0  0.25  0.5  0.25  
action: 3
0  0.25  0.5  0.25  
0  0.25  0.5  0.25  
0  0.25  0.5  0.25  
0  0.25  0.5  0.25  
#############################################
Reward Matrix (state,action):
0  -1  -2  -5  
5  0  -3  -1000  
6  -1  -1000  -1000  
5  -1000  -1000  -1000  
#############################################
#############################################
Print solution after value iteration
#Print solution of an MDP problem 
#Size of the state space : 4

#############################################
# Solution of the entered problem model:
# - column 1: index of the state 
# - column 2: Value function 
# - column 3: Optimal action 
#
Step 0
   0   4.1875   3
   1   8.0625   0
   2   12.125   0
   3   14.188   0
####
Step 1
   0   2   2
   1   6.25   0
   2   10   0
   3   10.5   0
####
Step 2
   0   0   0
   1   5   0
   2   6   0
   3   5   0
####
#############################################

Checking solutions
i=0 solution= 4.1875
i=1 solution= 8.0625
i=2 solution= 12.125
i=3 solution= 14.188

********************************
Destroying
Destroying 2
