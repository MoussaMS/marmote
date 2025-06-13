#include <string>
#include <iostream>

using namespace std;

#include "marmoteCore/marmoteInterval.h"
#include "marmoteCore/marmoteSparseMatrix.h"
#include "marmoteMDP/marmoteTotalRewardMDP.h"
#include "marmoteMDP/marmoteSolutionMDP.h"

int main()
{
    // Valeur très grande pour pénaliser les actions interdites ou non définies
    double peno = 1e10;

    // Définition des espaces d'état (0 à 8) et d'action (0 à 7)
    MarmoteInterval *stateSpace = new MarmoteInterval(0,8);
    MarmoteInterval *actionSpace = new MarmoteInterval(0,7);

    // Taille des espaces (nombre d'états et d'actions)
    int dim_SS = stateSpace->Cardinal();  
    int dim_AS = actionSpace->Cardinal();

    // Création de la matrice des coûts (dimensions états x actions)
    SparseMatrix *Cost  = new SparseMatrix(dim_SS, dim_AS);

    // --- Remplissage des coûts ---
    // On définit les coûts pour chaque couple état-action valide
    // Les autres actions interdites recoivent la pénalité "peno"
    Cost->setEntry(0,0,15);
    Cost->setEntry(0,1,10);
    Cost->setEntry(0,2,5);
    for (int a=3; a<dim_AS; a++) Cost->setEntry(0,a,peno);

    // On continue pour chaque état, en ajoutant les coûts connus
    // Ici, on remplit uniquement les actions valides, et pénalise les autres
    for (int a=0; a<3; a++) Cost->setEntry(1,a,peno);
    Cost->setEntry(1,3,10);
    Cost->setEntry(1,4,30);
    for (int a=5; a<dim_AS; a++) Cost->setEntry(1,a,peno);

    // … on fait pareil pour les autres états
    for (int a=0; a<4; a++) Cost->setEntry(2,a,peno);
    Cost->setEntry(2,4,15);
    for (int a=5; a<dim_AS; a++) Cost->setEntry(2,a,peno);

    for (int a=0; a<5; a++) Cost->setEntry(3,a,peno);
    Cost->setEntry(3,5,10);
    for (int a=6; a<dim_AS; a++) Cost->setEntry(3,a,peno);

    for (int a=0; a<5; a++) Cost->setEntry(4,a,peno);
    Cost->setEntry(4,5,20);
    for (int a=6; a<dim_AS; a++) Cost->setEntry(4,a,peno);

    for (int a=0; a<5; a++) Cost->setEntry(5,a,peno);
    Cost->setEntry(5,5,60);
    for (int a=6; a<dim_AS; a++) Cost->setEntry(5,a,peno);

    for (int a=0; a<6; a++) Cost->setEntry(6,a,peno);
    Cost->setEntry(6,6,5);
    Cost->setEntry(6,7,peno);

    for (int a=0; a<3; a++) Cost->setEntry(7,a,peno);
    Cost->setEntry(7,3,5);
    for (int a=4; a<dim_AS; a++) Cost->setEntry(7,a,peno);

    for (int a=0; a<6; a++) Cost->setEntry(8,a,peno);
    Cost->setEntry(8,6,0);
    Cost->setEntry(8,7,peno);

    // --- Fin remplissage des coûts ---

    // Critère d'optimisation : on veut minimiser la somme totale des coûts
    string critere("min");

    // Précision pour convergence de l'algorithme
    double epsilon = 1e-5;

    // Nombre max d'itérations pour l'algorithme de Value Iteration
    int maxIter = 20;

    cout << "Création de l'objet MDP avec total reward..." << endl;

    // Création du MDP total reward avec les espaces et la matrice des coûts
    TotalRewardMDP *mdp = new TotalRewardMDP(critere, stateSpace, actionSpace, Cost);

    cout << "MDP construit avec succès." << endl;

    // --- Construction des matrices de transition ---
    // On crée les probabilités de transition pour chaque action
    // Chaque matrice est carrée (nombre d'états x nombre d'états)

    // Action 0 : transition de l'état 0 vers états 1 et 2 avec probabilités 0.6 et 0.4
    SparseMatrix *P = new SparseMatrix(dim_SS);
    P->setEntry(0,1,0.6);
    P->setEntry(0,2,0.4);
    // Les autres états restent inchangés (auto-transition)
    for(int s=1; s<dim_SS; s++) P->setEntry(s,s,1.0);
    mdp->AddMatrix(0, P);

    // Action 1 : état 0 vers états 3, 4, 5
    P = new SparseMatrix(dim_SS);
    P->setEntry(0,3,0.3);
    P->setEntry(0,4,0.5);
    P->setEntry(0,5,0.2);
    for(int s=1; s<dim_SS; s++) P->setEntry(s,s,1.0);
    mdp->AddMatrix(1, P);

    // Action 2 : état 0 vers états 6 et 7
    P = new SparseMatrix(dim_SS);
    P->setEntry(0,6,0.15);
    P->setEntry(0,7,0.85);
    for(int s=1; s<dim_SS; s++) P->setEntry(s,s,1.0);
    mdp->AddMatrix(2, P);

    // Action 3 : transitions pour états 1, 7, 0
    P = new SparseMatrix(dim_SS);
    P->setEntry(1,0,1);
    P->setEntry(7,0,1);
    P->setEntry(0,0,1);
    for (int s : {2,3,4,5,6,8}) P->setEntry(s,s,1.0);
    mdp->AddMatrix(3, P);

    // Action 4 : états 1 et 2 vers état 8, autres auto-transitions
    P = new SparseMatrix(dim_SS);
    P->setEntry(1,8,1);
    P->setEntry(2,8,1);
    P->setEntry(0,0,1);
    for (int s : {3,4,5,6,7,8}) P->setEntry(s,s,1.0);
    mdp->AddMatrix(4, P);

    // Action 5 : états 3,4,5 vers état 8, autres auto-transitions
    P = new SparseMatrix(dim_SS);
    P->setEntry(3,8,1);
    P->setEntry(4,8,1);
    P->setEntry(5,8,1);
    P->setEntry(1,1,1);
    for (int s : {0,2,6,7,8}) P->setEntry(s,s,1.0);
    mdp->AddMatrix(5, P);

    // Action 6 : états 6 et 8 restent ou vont vers 8, autres auto-transitions
    P = new SparseMatrix(dim_SS);
    P->setEntry(6,8,1);
    P->setEntry(8,8,1);
    for (int s : {0,1,2,3,4,5,7}) P->setEntry(s,s,1.0);
    mdp->AddMatrix(6, P);

    // Action 7 : état 7 vers 6, autres auto-transitions
    P = new SparseMatrix(dim_SS);
    P->setEntry(7,6,1);
    for (int s : {0,1,2,3,4,5,6,8}) P->setEntry(s,s,1.0);
    mdp->AddMatrix(7, P);

    cout << "Matrices de transition ajoutées." << endl;

    // --- TEST : affichage des caractéristiques du MDP ---
    mdp->Write();

    // --- TEST 1 : exécution de Value Iteration avec peu d'itérations (5) ---
    maxIter = 5;
    cout << "Démarrage de Value Iteration (maxIter = " << maxIter << ") ..." << endl;
    SolutionMDP *solution = mdp->ValueIteration(epsilon, maxIter);
    // Affichage de la solution (politique optimale estimée)
    solution->Write();
    delete solution;  // Libération mémoire

    // --- TEST 2 : exécution plus longue de Value Iteration (50 itérations) pour meilleure précision ---
    maxIter = 50;
    mdp->changeVerbosity(true);  // active affichage détaillé durant l'algorithme
    cout << "Démarrage de Value Iteration (maxIter = " << maxIter << ") ..." << endl;
    solution = mdp->ValueIteration(epsilon, maxIter);
    solution->Write();

    // Nettoyage final : suppression des objets et libération mémoire
    delete solution;
    mdp->ClearRew();
    for(int i = dim_AS-1; i >= 0; i--)
    {
        mdp->DeleMatrix(i);
    }
    delete mdp;
    delete stateSpace;
    delete actionSpace;

    return 0;
}
