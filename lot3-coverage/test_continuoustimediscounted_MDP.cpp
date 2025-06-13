/* Marmote and MarmoteMDP are free softwares: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Marmote is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Marmote. If not, see <http://www.gnu.org/licenses/>.

Copyright 2019 Emmanuel Hyon, Alain Jean-Marie
*/

/**
 * @brief file marmoteContinuousTimeDiscountedMDP
 * @author Hyon, lip6
 * @date May 2024
 * @version 0.1
 *
 *
 * 
*/
#include <marmoteCore/marmoteSparseMatrix.h>
#include <marmoteCore/marmoteFullMatrix.h>
#include <marmoteCore/marmoteSet.h>
#include <marmoteCore/marmoteInterval.h>
#include <marmoteMDP/marmoteContinuousTimeDiscountedMDP.h>
#include <marmoteMDP/marmoteDiscountedMDP.h>
#include <marmoteMDP/marmoteFeedbackSolutionMDP.h>

#include <gtest/gtest.h>

/* Existing c++ includes: check if needed
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <values.h>
#include <time.h>
#include <list>
#include <vector>
#include <string>
*/

using namespace std;

class MDP_ContTimeDiscCriterionTest : public :: testing::Test
{
protected:
    double beta = 1;        // the discount factor
    double epsilon = 0.001; // the precison tolerance
    ContinuousTimeDiscountedMDP *mdp;

    FullMatrix *R1 = nullptr;
    SparseMatrix *P1 = nullptr;
    SparseMatrix *P0 = nullptr;
    int maxIter = 700; // limit on iterations
    MarmoteSet *actionSpace = nullptr;
    MarmoteSet *stateSpace = nullptr;

    double lambdap=1;
    double mup=2;

    double crp=5;
    double chp=2;

    virtual void SetUp() {
        string criterion("min");
    
        /* Create the MDP object to test 1-dimension example and fill all its fields.*/
        int min = 0;
        int max = 2;
    
        /* Creation des espaces */
        actionSpace = new MarmoteInterval(0,1);
        stateSpace = new MarmoteInterval(min,max);

        /*Creation du vecteur des matrices de transitions */
        vector<TransitionStructure*> trans(actionSpace->Cardinal());
    
        /*creation des matrices de transitions */
        P0 = new SparseMatrix(3);
        P0->setEntry(0,1,lambdap);
        P0->setEntry(1,0,mup);
        P0->setEntry(1,2,lambdap);
        P0->setEntry(2,1,mup);
        P0->setEntry(2,2,lambdap);
        trans.at(0) = P0;

        /* accept the customer */
        P1 = new SparseMatrix(3);
        P1->setEntry(0,0,mup);
        P1->setEntry(0,2,lambdap);
        P1->setEntry(1,1,mup);
        P1->setEntry(1,2,lambdap);
        P1->setEntry(2,1,mup);
        P1->setEntry(2,2,lambdap);
        /* ajout a la collection */
        trans.at(1) = P1;


        /* entree de la matrice des gains
         * on rappelle que l'entree de la matrice de gain est
         * r(x,a)  x l'etat codee sur ligne et a l'action codee sur colonne
         */
        R1  = new FullMatrix(3,2);
        R1->setEntry(0,0,(crp));
        R1->setEntry(1,0,(crp+chp));
        R1->setEntry(2,0,(crp+2*chp));
        R1->setEntry(0,1,chp);
        R1->setEntry(1,1,2*chp);
        R1->setEntry(2,1,(100*crp+2*chp));
    
        //std::cout << "Debut de la construction MDP"<< std::endl;
        /* Creation de l'objet MDP */
        mdp = new ContinuousTimeDiscountedMDP(criterion, stateSpace, actionSpace,
                trans, R1, beta);
        //std::cout << "Fin de la construction MDP"<< std::endl;

    }

    virtual void TearDown() {
        mdp->ClearRew();
        delete mdp;
        delete actionSpace;
        delete stateSpace;
    }

};

TEST_F( MDP_ContTimeDiscCriterionTest, className )
{
    std::string class_name = "ContinuousTimeDiscountedMDP";
    EXPECT_EQ(class_name, mdp->className());
}

TEST_F( MDP_ContTimeDiscCriterionTest, Uniformize )
{
    //mdp->Write();
    mdp->UniformizeMDP();
    //mdp->Write();

    //test
    double taux =mdp->getMaximumRate();
    EXPECT_NEAR(taux,3,1e-2);

    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(0,0),0.66667, 1e-3 );
    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(0,1),0.33334, 1e-3 );

    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(1,0),0.666667, 1e-3 );
    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(1,2),0.333334, 1e-3 );

    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(1,1),0.666667, 1e-3 );
    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(1,2),0.333334, 1e-3 );

    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(2,1),0.66667, 1e-3 );
    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(2,2),0.33334, 1e-3 );

    EXPECT_NEAR(R1->getEntry(0,0),2.5, 1e-3 );
    EXPECT_NEAR(R1->getEntry(2,1), 504, 1e-3 );

}

TEST_F( MDP_ContTimeDiscCriterionTest, Uniformize_two )
{
    //mdp->Write();
    mdp->computeMaxRate();
    double taux =mdp->getMaximumRate();
    taux= taux+1;
    mdp->setMaximumRate(taux);
    mdp->UniformizeMDP();
    //mdp->Write();

    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(0,0),0.75, 1e-2 );
    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(0,1),0.25, 1e-2 );

    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(1,0),0.5, 1e-2 );
    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(1,1),0.25, 1e-2 );
    EXPECT_NEAR(mdp->getMatrix(0)->getEntry(1,2),0.25, 1e-2 );


    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(2,1),0.5, 1e-2 );
    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(2,2),0.5, 1e-2 );

    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(1,1),0.75, 1e-2 );
    EXPECT_NEAR(mdp->getMatrix(1)->getEntry(1,2),0.25, 1e-2 );

    EXPECT_NEAR(R1->getEntry(0,0),1.6, 1e-1 );
    EXPECT_NEAR(R1->getEntry(0,1),0.64, 1e-1 );
    EXPECT_NEAR(R1->getEntry(2,0),5.76, 1e-1 );
    EXPECT_NEAR(R1->getEntry(2,1), 322.5, 1 );

}



class MDP_ContTimeDiscCriterionFullTest : public :: testing::Test
{
protected:
    double beta = 1;        // the discount factor
    double epsilon = 0.001; // the precison tolerance
    ContinuousTimeDiscountedMDP *mdp2;

    FullMatrix *R_1 = nullptr;
    FullMatrix *P_1 = nullptr;
    FullMatrix *P_0 = nullptr;
    int maxIter = 700; // limit on iterations
    MarmoteSet *actionSpace = nullptr;
    MarmoteSet *stateSpace = nullptr;

    double lambdap=1;
    double mup=2;

    double crp=5;
    double chp=2;

    virtual void SetUp() {
        string criterion("min");

        /* Create the MDP object to test 1-dimension example and fill all its fields.*/
        int min = 0;
        int max = 2;

        /* Creation des espaces */
        actionSpace = new MarmoteInterval(0,1);
        stateSpace = new MarmoteInterval(min,max);

        /*Creation du vecteur des matrices de transitions */
        vector<TransitionStructure*> transbis(actionSpace->Cardinal());

        /*creation des matrices de transitions */
        P_0 = new FullMatrix(3);
        P_0->setEntry(0,0,0.0);
        P_0->setEntry(0,1,lambdap);
        P_0->setEntry(0,2,0.0);
        P_0->setEntry(1,0,mup);
        P_0->setEntry(1,1,0.0);
        P_0->setEntry(1,2,lambdap);
        P_0->setEntry(2,0,0.0);
        P_0->setEntry(2,1,mup);
        P_0->setEntry(2,2,lambdap);
        transbis.at(0) = P_0;

        /* accept the customer */
        P_1 = new FullMatrix(3);
        P_1->setEntry(0,0,mup);
        P_1->setEntry(0,1,0.0);
        P_1->setEntry(0,2,lambdap);
        P_1->setEntry(1,0,0.0);
        P_1->setEntry(1,1,mup);
        P_1->setEntry(1,2,lambdap);
        P_1->setEntry(2,0,0.0);
        P_1->setEntry(2,1,mup);
        P_1->setEntry(2,2,lambdap);
        /* ajout a la collection */
        transbis.at(1) = P_1;


        /* entree de la matrice des gains
         * on rappelle que l'entree de la matrice de gain est
         * r(x,a)  x l'etat codee sur ligne et a l'action codee sur colonne
         */
        R_1  = new FullMatrix(3,2);
        R_1->setEntry(0,0,(crp));
        R_1->setEntry(1,0,(crp+chp));
        R_1->setEntry(2,0,(crp+2*chp));
        R_1->setEntry(0,1,chp);
        R_1->setEntry(1,1,2*chp);
        R_1->setEntry(2,1,(10*crp+2*chp));

        //std::cout << "Debut de la construction MDP"<< std::endl;
        /* Creation de l'objet MDP */
        mdp2 = new ContinuousTimeDiscountedMDP(criterion, stateSpace, actionSpace,
                transbis, R_1, beta);
        //std::cout << "Fin de la construction MDP"<< std::endl;

    }

    virtual void TearDown() {
        mdp2->ClearRew();
        delete mdp2;
        delete actionSpace;
        delete stateSpace;
    }

};



TEST_F( MDP_ContTimeDiscCriterionFullTest, Uniformize )
{
    mdp2->UniformizeMDP();

    EXPECT_NEAR(mdp2->getMatrix(0)->getEntry(0,0),0.66667, 1e-3 );
    EXPECT_NEAR(mdp2->getMatrix(0)->getEntry(0,1),0.33334, 1e-3 );

    EXPECT_NEAR(mdp2->getMatrix(1)->getEntry(2,1),0.66667, 1e-3 );
    EXPECT_NEAR(mdp2->getMatrix(1)->getEntry(2,2),0.33334, 1e-3 );
}

/*
TEST_F( MDP_ContTimeDiscCriterionFullTest, ValueIteration )
{
    // fprintf(stdout,"Affichage solution iteration valeur\n");
    FeedbackSolutionMDP *optimum = mdp2->ValueIteration(epsilon, maxIter);
    optimum->Write();

    double *sol = (dynamic_cast<FeedbackSolutionMDP*>(optimum))->getValue();

    EXPECT_NEAR( sol[0],0 , 1e-5 );
    EXPECT_NEAR( sol[1], 1, 1e-5 );


    delete optimum;
    //delete[] sol;
}
*/
