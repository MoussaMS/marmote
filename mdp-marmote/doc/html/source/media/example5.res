# Initial probability
discrete values { <0> <1> <2> } probas {  0.08966   0.4513   0.4591 } 
# Markov chain
discrete sparse
3
         0          0   2.5000e-01
         0          1   5.0000e-01
         0          2   2.5000e-01
         1          0   4.0000e-01
         1          1   2.0000e-01
         1          2   4.0000e-01
         2          0   4.0000e-01
         2          1   3.0000e-01
         2          2   3.0000e-01
stop
# Stationary distribution #1 with iterative method
discrete values { <0> <1> <2> } probas { 3.4783e-01 3.3597e-01 3.1621e-01 } 
# Stationary distribution #2 with power method
discrete values { <0> <1> <2> } probas { 3.4783e-01 3.3597e-01 3.1621e-01 } 
# Stationary distribution RLGL method
discrete values { <0> <1> <2> } probas { 3.4783e-01 3.3597e-01 3.1621e-01 } 

Distance between the Power and the RLGL methods = Computing a distance between a discreteDistribution and a discreteDistribution
... L1 distance is 3.3455e-06
3.3455e-06

# Checking invariance of distribution #2: one-step transition is:
discrete values { <0> <1> <2> } probas { 3.4783e-01 3.3597e-01 3.1621e-01 } 
# L1 distance with distribution #2:
d = Computing a distance between a discreteDistribution and a discreteDistribution
... L1 distance is 3.8564e-06
3.8564e-06

# Transient distribution after 100 steps
 from the random initial distribution
discrete values { <0> <1> <2> } probas { 3.4783e-01 3.3597e-01 3.1621e-01 } 
# L1 distance with distribution #2:
Computing a distance between a discreteDistribution and a discreteDistribution
... L1 distance is 3.3454e-06
3.3454e-06
