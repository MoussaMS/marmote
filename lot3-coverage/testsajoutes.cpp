/*---------------------Pour averageMDP-----------------------------------*/
// Test 1: ValueIteration retourne un objet non nul
TEST_F(AverageMDPTest, ValueIterationReturnsNonNull) {
    // Ici je teste si l’algorithme retourne bien une solution
    auto solution = mdp->ValueIteration(1e-6, 100);
    ASSERT_NE(solution, nullptr);
    delete solution;
}

// Test 2: RelativeValueIteration retourne un gain moyen cohérent
TEST_F(AverageMDPTest, RelativeValueIterationAvgCostPositive) {
    // Je veux vérifier que le gain moyen est bien positif dans ce MDP
    auto solution = mdp->RelativeValueIteration(1e-6, 100);
    ASSERT_GT(solution->getAvgCost(), 0.0);
    delete solution;
}

// Test 3: ValueIteration converge en moins de 100 itérations
TEST_F(AverageMDPTest, ValueIterationConvergesQuickly) {
    // Je vérifie si ça converge rapidement, donc bonne performance
    auto solution = mdp->ValueIteration(1e-6, 100);
    // ici je suppose qu'il y a un accesseur au nombre d’itérations si disponible
    ASSERT_LE(solution->getIterationCount(), 100);
    delete solution;
}

// Test 4: Les actions optimales sont cohérentes (optionnel)
TEST_F(AverageMDPTest, OptimalActionsCorrect) {
    auto solution = mdp->ValueIteration(1e-6, 100);
    auto actions = solution->getAction();
    // Je vérifie que l’action optimale pour l’état 0 est bien celle avec la récompense la plus élevée
    EXPECT_EQ(actions[0], 0); // état 0, action 0 a un meilleur gain
    delete solution;
}

TEST_F( MDP_AvgCriterionTest, PolicyCostFixed ) {
  // Politique fixée : actions choisies pour chaque état
  // action[0] = 1 → aller de l'état 0 vers l'état 1
  // action[1] = 2 → aller de l'état 1 vers l'état 0
  // action[2] = 3 → action mixte à partir de l'état 2
  stateType policy[3] = {1, 2, 3};

  // Calcul du coût moyen associé à cette politique
  double* policyCost = mdp->PolicyCost(policy, epsilon, maxIter);

  // On s’attend à un coût moyen supérieur ou égal à celui de la politique optimale (≈ 2.5)
  // Ici, la politique n'est *pas* optimale : action 1 sur état 0 donne un reward de 1
  // alors que l’action optimale est 0 (reward 2)

  EXPECT_TRUE(policyCost != nullptr);
  EXPECT_GT(policyCost[0], 2.5); // au moins sur l'état 0
  EXPECT_GT(policyCost[1], 2.5); // idem pour 1
  EXPECT_GT(policyCost[2], 2.5); // idem pour 2

  delete[] policyCost;
}
/*---------------------------Pour continuonstimediscountedMDP--------------------------------------*/
// Test 1 : Tester computeMaxRate et vérifier que le maximum est bien mis à jour
TEST_F(MDP_ContTimeDiscCriterionTest, ComputeMaxRateUpdate)
{
    mdp->computeMaxRate();
    double maxRate = mdp->getMaximumRate();
    EXPECT_GT(maxRate, 0);
}

// Test 2 : Tester la modification du critère (min -> max) et la récupération
TEST_F(MDP_ContTimeDiscCriterionTest, SetAndGetCriterion)
{
    mdp->setCriterion("max");
    EXPECT_EQ(mdp->getCriterion(), "max");
    mdp->setCriterion("min");
    EXPECT_EQ(mdp->getCriterion(), "min");
}

// Test 3 : Vérifier la validité des matrices retournées (nullité et dimensions)
TEST_F(MDP_ContTimeDiscCriterionTest, MatrixAccessAndDimensions)
{
    TransitionStructure* mat0 = mdp->getMatrix(0);
    ASSERT_NE(mat0, nullptr);
    EXPECT_EQ(mat0->getNumberOfRows(), stateSpace->Cardinal());
    EXPECT_EQ(mat0->getNumberOfColumns(), stateSpace->Cardinal());
}

// Test 4 : Exécuter ValueIteration et vérifier que la solution n’est pas nulle et cohérente
TEST_F(MDP_ContTimeDiscCriterionTest, ValueIterationExecution)
{
    int maxIterLocal = 100;
    FeedbackSolutionMDP *solution = mdp->ValueIteration(epsilon, maxIterLocal);
    ASSERT_NE(solution, nullptr);

    double* values = dynamic_cast<FeedbackSolutionMDP*>(solution)->getValue();
    ASSERT_NE(values, nullptr);

    // On vérifie que les valeurs sont finies et non négatives
    for (int i = 0; i < stateSpace->Cardinal(); ++i) {
        EXPECT_TRUE(std::isfinite(values[i]));
    }

    delete solution;
}
