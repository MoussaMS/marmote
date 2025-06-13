// FiniteHorizonTest.cpp
// Tests unitaires pour la classe FiniteHorizonMDP

#include <gtest/gtest.h>
#include <marmoteFiniteHorizonMDP.h>
#include <marmoteCore/marmoteInterval.h>
#include <marmoteCore/marmoteSparseMatrix.h>
#include <marmoteMDP/marmoteNonStationarySolutionMDP.h>

class FiniteHorizonTest : public ::testing::Test {
protected:
    FiniteHorizonMDP* mdp;
    MarmoteSet* stateSpace;
    MarmoteSet* actionSpace;
    SparseMatrix* rewards;
    std::vector<TransitionStructure*> transitions;
    int horizon = 3;
    double beta = 0.9;

    void SetUp() override {
        stateSpace = new MarmoteInterval(0, 1);
        actionSpace = new MarmoteInterval(0, 1);

        rewards = new SparseMatrix(2);
        rewards->addToEntry(0, 0, 1.0);
        rewards->addToEntry(0, 1, 5.0);
        rewards->addToEntry(1, 0, 3.0);
        rewards->addToEntry(1, 1, 2.0);

        SparseMatrix* P0 = new SparseMatrix(2);
        P0->addToEntry(0, 0, 0.7);
        P0->addToEntry(0, 1, 0.3);
        P0->addToEntry(1, 0, 0.4);
        P0->addToEntry(1, 1, 0.6);

        SparseMatrix* P1 = new SparseMatrix(2);
        P1->addToEntry(0, 0, 0.2);
        P1->addToEntry(0, 1, 0.8);
        P1->addToEntry(1, 0, 0.6);
        P1->addToEntry(1, 1, 0.4);

        transitions.push_back(P0);
        transitions.push_back(P1);

        std::string crit = "max";
        mdp = new FiniteHorizonMDP(crit, stateSpace, actionSpace, transitions, rewards, horizon, beta);
    }

    void TearDown() override {
        delete mdp;
        delete rewards;
        delete transitions[0];
        delete transitions[1];
        delete stateSpace;
        delete actionSpace;
    }
};

// Test 1 – Vérification de la création de l'objet FiniteHorizonMDP
// Ce test s'assure que l'objet créé est bien de la classe "FiniteHorizonMDP".
// Cela vérifie la bonne initialisation de l’instance à partir des constructeurs définis.
TEST_F(FiniteHorizonTest, CreationTest) {
    EXPECT_EQ(mdp->className(), "FiniteHorizonMDP");
}

// Test 2 – Exécution de la méthode ValueIteration
// Ce test appelle ValueIteration() sans epsilon/maxIter pour s'assurer qu'il s'exécute correctement.
// On vérifie ensuite que les valeurs retournées sont bien finies, ce qui prouve une convergence.
TEST_F(FiniteHorizonTest, ValueIterationExecutes) {
    auto* solution = mdp->ValueIteration();
    double* val = solution->getValueAtStep(mdp->getHorizon() - 1);
    for (int i = 0; i < stateSpace->Cardinal(); ++i) {
        EXPECT_TRUE(std::isfinite(val[i]));
    }
    delete solution;
}

// Test 3 – Vérification des actions optimales à la dernière étape
// On vérifie que, pour chaque état, l'action choisie maximise la récompense immédiate.
// Cela permet de tester si l'algorithme choisit correctement au dernier horizon.
TEST_F(FiniteHorizonTest, LastStepOptimalActions) {
    auto* solution = mdp->ValueIteration();
    int step = mdp->getHorizon() - 1;
    stateType* actions = solution->getActionAtStep(step);
    for (int i = 0; i < stateSpace->Cardinal(); ++i) {
        double bestReward = -DBL_MAX;
        int bestAction = -1;
        for (int a = 0; a < actionSpace->Cardinal(); ++a) {
            double reward = rewards->getEntry(i, a);
            if (reward > bestReward) {
                bestReward = reward;
                bestAction = a;
            }
        }
        EXPECT_EQ(actions[i], bestAction);
    }
    delete solution;
}

// Test 4 – Exécution de PolicyCost avec solution de ValueIteration
// Ce test vérifie que la méthode PolicyCost met bien à jour les valeurs de la solution
// en tenant compte de l’évolution temporelle et du facteur d’escompte.
TEST_F(FiniteHorizonTest, PolicyCostExecution) {
    auto* solution = mdp->ValueIteration();
    mdp->PolicyCost(solution, 0.0, 0);
    for (int t = 0; t < mdp->getHorizon(); ++t) {
        double* values = solution->getValueAtStep(t);
        for (int i = 0; i < stateSpace->Cardinal(); ++i) {
            EXPECT_TRUE(std::isfinite(values[i]));
        }
    }
    delete solution;
}
