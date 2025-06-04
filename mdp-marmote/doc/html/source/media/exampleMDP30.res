Begining of building MDP
End of building MDP
Add matrices
Added matrix (action 0)
Added matrix (action 1)
Added matrix (action 2)
Added matrix (action 3)
Added matrix (action 4)
Added matrix (action 5)
Added matrix (action 6)
Added matrix (action 7)
Finishing Adding matrixes MDP
Writting MDP
#############################################
write total Reward MDP
MDP Criteria : Total reward
#############################################
#############################################
write MDP
MDP type (discrete,continuous): discrete
MDP rule (min,max): min
#############################################
State space size: 9
Action space size: 8
State  dimension: 1
Action dimension: 1
#############################################
Transition matrix per action:
action: 0
0  0.6  0.4  0  0  0  0  0  0  
0  1  0  0  0  0  0  0  0  
0  0  1  0  0  0  0  0  0  
0  0  0  1  0  0  0  0  0  
0  0  0  0  1  0  0  0  0  
0  0  0  0  0  1  0  0  0  
0  0  0  0  0  0  1  0  0  
0  0  0  0  0  0  0  1  0  
0  0  0  0  0  0  0  0  1  
action: 1
0  0  0  0.3  0.5  0.2  0  0  0  
0  1  0  0  0  0  0  0  0  
0  0  1  0  0  0  0  0  0  
0  0  0  1  0  0  0  0  0  
0  0  0  0  1  0  0  0  0  
0  0  0  0  0  1  0  0  0  
0  0  0  0  0  0  1  0  0  
0  0  0  0  0  0  0  1  0  
0  0  0  0  0  0  0  0  1  
action: 2
0  0  0  0  0  0  0.15  0.85  0  
0  1  0  0  0  0  0  0  0  
0  0  1  0  0  0  0  0  0  
0  0  0  1  0  0  0  0  0  
0  0  0  0  1  0  0  0  0  
0  0  0  0  0  1  0  0  0  
0  0  0  0  0  0  1  0  0  
0  0  0  0  0  0  0  1  0  
0  0  0  0  0  0  0  0  1  
action: 3
1  0  0  0  0  0  0  0  0  
1  0  0  0  0  0  0  0  0  
0  0  1  0  0  0  0  0  0  
0  0  0  1  0  0  0  0  0  
0  0  0  0  1  0  0  0  0  
0  0  0  0  0  1  0  0  0  
0  0  0  0  0  0  1  0  0  
1  0  0  0  0  0  0  0  0  
0  0  0  0  0  0  0  0  1  
action: 4
1  0  0  0  0  0  0  0  0  
0  0  0  0  0  0  0  0  1  
0  0  0  0  0  0  0  0  1  
0  0  0  1  0  0  0  0  0  
0  0  0  0  1  0  0  0  0  
0  0  0  0  0  1  0  0  0  
0  0  0  0  0  0  1  0  0  
0  0  0  0  0  0  0  1  0  
0  0  0  0  0  0  0  0  1  
action: 5
1  0  0  0  0  0  0  0  0  
0  1  0  0  0  0  0  0  0  
0  0  1  0  0  0  0  0  0  
0  0  0  0  0  0  0  0  1  
0  0  0  0  0  0  0  0  1  
0  0  0  0  0  0  0  0  1  
0  0  0  0  0  0  1  0  0  
0  0  0  0  0  0  0  1  0  
0  0  0  0  0  0  0  0  1  
action: 6
1  0  0  0  0  0  0  0  0  
0  1  0  0  0  0  0  0  0  
0  0  1  0  0  0  0  0  0  
0  0  0  1  0  0  0  0  0  
0  0  0  0  1  0  0  0  0  
0  0  0  0  0  1  0  0  0  
0  0  0  0  0  0  0  0  1  
0  0  0  0  0  0  0  1  0  
0  0  0  0  0  0  0  0  1  
action: 7
1  0  0  0  0  0  0  0  0  
0  1  0  0  0  0  0  0  0  
0  0  1  0  0  0  0  0  0  
0  0  0  1  0  0  0  0  0  
0  0  0  0  1  0  0  0  0  
0  0  0  0  0  1  0  0  0  
0  0  0  0  0  0  1  0  0  
0  0  0  0  0  0  1  0  0  
0  0  0  0  0  0  0  0  1  
#############################################
Reward Matrix (state,action):
15  10  5  1e+10  1e+10  1e+10  1e+10  1e+10  
1e+10  1e+10  1e+10  10  30  1e+10  1e+10  1e+10  
1e+10  1e+10  1e+10  1e+10  15  1e+10  1e+10  1e+10  
1e+10  1e+10  1e+10  1e+10  1e+10  10  1e+10  1e+10  
1e+10  1e+10  1e+10  1e+10  1e+10  20  1e+10  1e+10  
1e+10  1e+10  1e+10  1e+10  1e+10  60  1e+10  1e+10  
1e+10  1e+10  1e+10  1e+10  1e+10  1e+10  5  1e+10  
1e+10  1e+10  1e+10  5  1e+10  1e+10  1e+10  15  
1e+10  1e+10  1e+10  1e+10  1e+10  1e+10  0  1e+10  
#############################################
#############################################


###############################
Printing solution from value iteration
Done : path length  5
#-- Value Iteration -- Done with 5 iterations and final distance=4.25
Print solution
#Print solution of an MDP problem 
#Size of the state space : 9

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           22.1125   2
  1              28.5   3
  2                15   4
  3                10   5
  4                20   5
  5                60   5
  6                 5   6
  7                20   7
  8                 0   6
#############################################
Printing solution from value iteration
Done : path length  50
#-- Value Iteration -- Done with 7 iterations and final distance=0
Print solution
#Print solution of an MDP problem 
#Size of the state space : 9

#############################################
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0             22.75   2
  1                30   4
  2                15   4
  3                10   5
  4                20   5
  5                60   5
  6                 5   6
  7                20   7
  8                 0   6
#############################################


################################

********************************
Deleting
Deleting 2
Deleting 3
