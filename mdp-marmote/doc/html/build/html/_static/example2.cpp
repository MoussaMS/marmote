// Example that constructs a 3x3 discrete-time Markov chain
// then computes the transient distribution for a number of steps and an initial distribution
// given as parameters to the application.
//
// Usage: example2 <n> <p1> <p2> <p3>
//

// Include necessary header files to use marmoteCore and other functonalities.
#include <marmoteMarkovChain/marmoteMarkovChain.h>
#include <marmoteCore/marmoteDiscreteDistribution.h>
#include <marmoteCore/marmotePolicy.h>
#include <marmoteCore/marmoteSparseMatrix.h>
#include <iostream>
#include <limits.h>
#include <string.h>

// Forward declaration of utility
bool parseParameters( int, char**, long int*, double*, double*, double* );

// The application code 

int main( int argc, char** argv ) 
{
	// variables used in the program
	long int var; 
	double prob1;
  	double prob2;
  	double prob3;

	// get values from command line
    bool test = parseParameters( argc, argv, &var, &prob1, &prob2, &prob3 );

	if (test)  
	{
        // Fixing the number of iterations
        unsigned int n = unsigned(var);
        // Creating the state space with an array.
        // Alternately: use the dedicated structure of marmoteCore.
        double states[3]={0,1,2};

        //Creating the initial distribution vector of size 3.
        double probas[3];

        // defining the initial seed
        //srand(time(nullptr));
        marmote::random::setSeed(0);

        // Filling the initial distribution vector according to the initial
		// probabilities passed in the arguments.
	  	probas[0] = prob1;
	  	probas[1] = prob2;
	  	probas[2] = prob3;  

	  	// Create a discrete distribution for the three states.
	  	DiscreteDistribution* initial = new DiscreteDistribution(3,states,probas);
	  
	  	// Create a discrete-time Markov chain of size 3.
	  	MarkovChain* c1 = new MarkovChain((stateType)3,DISCRETE);

	  	// assigning the created distribution to the chain.
	  	c1->set_init_distribution(initial);

	  	// Creating the transition matrix with size 3*3 using sparseMatrix object.
	  	SparseMatrix *P = new SparseMatrix(3);
        // Definition of the type of the transition structure
        // the type is not defined by default for a sparse matrix.
        // However defining the type or not has no impact here.
        P->set_type(DISCRETE);

	  	// Add entries to the transition matrix.
	  	P->addToEntry(0,0,0.25);
	  	P->addToEntry(0,1,0.5);
	  	P->addToEntry(0,2,0.25);
	  	P->addToEntry(1,0,0.4);
	  	P->addToEntry(1,1,0.2);
	  	P->addToEntry(1,2,0.4);
	  	P->addToEntry(2,0,0.4);
	  	P->addToEntry(2,1,0.3);
	  	P->addToEntry(2,2,0.3);

	  	// Assign the transition matrix to the chain. 
	  	c1->set_generator(P);

        // Print chain information to the standard output.
        c1->Write( &std::cout );

		/////////////////////////////////////////////////////////////////////////
        // Computing the transient distribution after n steps.
        Distribution* trDis1 = c1->TransientDistributionDT( 0, n );
        /////////////////////////////////////////////////////////////////////////

        // Write the final distribution to the standard output.
        trDis1->Write( &std::cout, FORMAT_MARMOTE );
        printf("\n");

        // Destroy the chain in order to free the allocated memory.
		delete c1;
		// NB the object P does not need to be deleted:
		// this is done during the destruction of c1.
        // Destroy the distribution object
		delete trDis1;
        // Destroy what remains
        delete initial;

    }
	else
	{
		printf("Input format is not valid !!\n");
        printf("Usage: %s <n> <p1> <p2> <p3>\n", argv[0] );
	}

	// Exit with OK code
  	return 0;
}

// Procedure for reading the command line data and storing it in variables.
// Returns true if everything is OK.
// The input is: 
// (number of steps n) 
// (initial distribution p1 p2 p3)
//
bool parseParameters( int argc, char** argv, long int* var,
					double* prob1, double* prob2, double* prob3 )
{
	bool test = true;
	char *endptr1, *endptr2, *endptr3, *endptr4;

	if (argc==5){
		*var = strtol(argv[1], &endptr1, 10);
		*prob1 = strtod(argv[2], &endptr2);
		*prob2 = strtod(argv[3], &endptr3);
		*prob3 = strtod(argv[4], &endptr4);
	}
	else{
		test = false;
	}

	// Check if the format of the entered arguments is valid:
	// not exceeding limits, no unallowed characters.
    test = test && ( (*var > 0) && (*var < INT_MAX) && (strlen(endptr1) == 0) );
	test = test && ( (strlen(endptr2) == 0) && (*prob1 <=1) && (*prob1>=0) );
	test = test && ( (strlen(endptr3) == 0) && (*prob2 <=1) && (*prob2>=0) );
	test = test && ( (strlen(endptr4) == 0) && (*prob3 <=1) && (*prob3>=0) );

	return test;
}
