Building MDP
Building MDP finished
Printing MDP
#############################################
write MDP
MDP type (discrete,continuous): discrete
MDP rule (min,max): min
#############################################
State space size: 4
Action space size: 3
State  dimension: 1
Action dimension: 1
#############################################
Transition matrix per action:
action: 0
0  0.875  0.0625  0.0625  
0  0.75  0.125  0.125  
0  0  0.5  0.5  
0  0  0  1  
action: 1
0  0.875  0.0625  0.0625  
0  0.75  0.125  0.125  
0  1  0  0  
0  0  0  1  
action: 2
0  0.875  0.0625  0.0625  
1  0  0  0  
1  0  0  0  
1  0  0  0  
#############################################
Reward Matrix (state,action):
0  4000  6000  
1000  4000  6000  
3000  4000  6000  
3000  4000  6000  
#############################################
#############################################
#############################################
write Average Discounted MDP
MDP Criteria : average
#############################################


###############################
Printing solution of value iteration 
#-- Value Iteration -- Done with 16 iterations and final distance=7.45058e-06
# Done : elapsing time 5.2e-05 sec
#Print solution of an MDP problem 
#Size of the state space : 4

#############################################
# Average Cost (only for average models) :          1666.67
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           24571.4   0
  1           25904.8   0
  2           28238.1   1
  3           28904.8   2
#############################################


Checking solutions
# Power method Done. With 1 iterations and  final distance: 2.79397e-06
i= 0 sol1= 26238.1
i= 1 sol1= 27571.4
i= 2 sol1= 29904.8
i= 3 sol1= 30571.4


###############################

Computation with Policy Iteration modified
#-- Policy Iteration Modified  -- Done with 3 iterations and final distance=8.14907e-07
# Done : elapsing time 5.2e-05 sec
#Print solution of an MDP problem 
#Size of the state space : 4

#############################################
# Average Cost (only for average models) :          1666.67
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0            225619   0
  1            226952   0
  2            229286   1
  3            229952   2
#############################################


Checking solutions
# Power method Done. With 1 iterations and  final distance: 2.03727e-07
i= 0 sol1= 26238.1
i= 1 sol1= 27571.4
i= 2 sol1= 29904.8
i= 3 sol1= 30571.4


###############################

Computation with relative value Iteration
#-- Relative Value Iteration -- Done with 16 iterations and final distance=7.45058e-06
# Done : elapsing time 4.8e-05 sec
#Print solution of an MDP problem 
#Size of the state space : 4

#############################################
# Average Cost (only for average models) :          1666.67
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           7666.67   0
  1              6000   0
  2              6000   1
  3              6000   2
#############################################

Checking solutions
# Power method Done. With 17 iterations and  final distance: 3.60887e-06
i= 0 sol1= 26238.1
i= 1 sol1= 27571.4
i= 2 sol1= 29904.8
i= 3 sol1= 30571.4


###############################


###############################
Checking Average Cost

Politicy Ra

Checking solutions
# Power method Done. With 16 iterations and  final distance: 6.51926e-06
#Print solution of an MDP problem 
#Size of the state space : 4

#############################################
# Average Cost (only for average models) :          1923.08
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           28396.4   0
  1             29858   0
  2           34627.2   0
  3           32473.4   2
#############################################

Politicy Rc

Checking solutions
# Power method Done. With 18 iterations and  final distance: 8.49385e-06
#Print solution of an MDP problem 
#Size of the state space : 4

#############################################
# Average Cost (only for average models) :          1727.27
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           59709.9   0
  1           61073.5   0
  2           63982.6   2
  3           63982.6   2
#############################################

Policy Rd

Solution checking
# Power method Done. With 500 iterations and  final distance: 6000
#Print solution of an MDP problem 
#Size of the state space : 4

#############################################
# Average Cost (only for average models) :             3000
# Solution of the entered problem model:
# - column 1: index of the state
# - column 2: Value function 
# - column 3: Optimal action 
#
  0           1.5e+06   0
  1           1.5e+06   2
  2           1.5e+06   2
  3           1.5e+06   2
#############################################


********************************
Deleting
Deleting 2
