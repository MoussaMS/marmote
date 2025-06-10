# 📘 Guide d'installation – Plateforme WordPress (Lot 1 – MIAGE)

Ce guide vous permet d’installer et d’accéder à la plateforme locale développée sous WordPress pour la préparation aux entretiens techniques (Lot 1).

---

## 🚀 Étapes d'installation

### 1. Installer WampServer
- Télécharger depuis : https://www.wampserver.com/

### 2. Cloner le dépôt GitHub
```bash
git clone https://github.com/votre-utilisateur/lot1_wordpress.git
```

### 3. Copier le dossier WordPress
- Copier le dossier :
```
lot1_wordpress/wordpress
```
dans :
```
C:/wamp64/www/wordpress
```

### 4. Lancer WampServer
- Vérifier que les services Apache et MySQL sont actifs (icône verte dans la barre des tâches)

### 5. Créer la base de données
- Ouvrir : http://localhost/phpmyadmin
- Créer une base de données appelée **miage_entretien**
- Importer le fichier `miage_entretien.sql` s’il est fourni dans `/docs/`

### 6. Accéder à la plateforme
- Aller sur : http://localhost/wordpress

---

## 🔐 Connexion administrateur

- **URL** : http://localhost/wordpress/wp-admin  
- **Identifiant** : `admin_miage`  
- **Mot de passe** : Voir le fichier `docs/identifiants.txt` ou à définir à l’installation

---

## ✍️ Modifier ou ajouter des questions

1. Se connecter à l’administration WordPress
2. Aller dans **QSM > Quizzes/Surveys**
3. Modifier un quiz existant ou en créer un nouveau
4. Ajouter des questions QCM avec réponses et correction
5. Sauvegarder et tester

---

## 👥 Auteurs

Projet réalisé par :
- Moussa SAKHO
- Grégory MENEUS
- Bada DIOP

Supervisé par **Emmanuel HYON**

---

## 🧩 Conseils

- Cette plateforme fonctionne **hors ligne**
- L'accès est protégé par mot de passe
- Elle est conçue pour être **réutilisable et évolutive**
