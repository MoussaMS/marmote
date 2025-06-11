# LOT 2 : Développement et amélioration du site Marmote

**Projet Open Source Marmote - Licence MIAGE Paris Nanterre**

**Auteurs :** Moussa SAKHO, Bada DIOP, Gregory MENEUS  
**Tuteur et responsable de formation :** Monsieur Emmanuel HYON

## 📌 Objectifs

Ce lot vise à améliorer l'écosystème Marmote en se concentrant sur trois axes principaux :

1. **Configurer l'environnement Marmote** pour une utilisation locale et pédagogique optimale
2. **Améliorer les notebooks Jupyter** avec une gestion efficace des images et une restructuration des contenus
3. **Garantir la cohérence entre Python et C++** en synchronisant les exemples dans la documentation

## 🔧 Installation et Configuration

### Environnement Conda

Pour installer et configurer l'environnement Marmote :

```bash
# Création de l'environnement
conda create -n marmote-use python=3.11

# Activation de l'environnement
conda activate marmote-use

# Installation des dépendances
conda install -c marmote -c conda-forge marmote jupyter sphinx
```

### Génération de la documentation

```bash
# Génération de la documentation HTML
make html
```

**📝 Note importante :** Lors de la génération de la documentation avec Sphinx, toutes les images sont automatiquement copiées dans le répertoire `_build/html/_images/`.

## 🖼️ Gestion des images dans les notebooks

### Différentes méthodes d'insertion d'images

Pour assurer la compatibilité entre **Jupyter local**, **Google Colab** et **Sphinx**, plusieurs approches ont été évaluées :

| Méthode | Compatibilité Jupyter | Compatibilité Colab | Compatibilité Sphinx |
|---------|----------------------|---------------------|----------------------|
| **Balise HTML avec chemin relatif**<br>`<img src="./image.png">` | ✅ Oui | ❌ Non | ✅ Oui (copie dans `_images/`) |
| **Lien URL absolu**<br>`<img src="https://.../image.png">` | ✅ Oui | ✅ Oui | ✅ Oui (si URL accessible) |
| **Attachement Jupyter**<br>`![image](attachment:image.png)` | ✅ Oui | ❌ Non | ❌ Non |

### Solution retenue

- **Pour Jupyter/Sphinx** : Utilisation de chemins relatifs (`./image.png`)
- **Pour Colab** : Remplacement automatique des chemins par des URLs absolues via la fonction `replace_images_for_colab()`

### Script de conversion pour Colab

```python
def replace_images_for_colab(notebook_path, image_mappings):
    """
    Remplace les chemins locaux par des URLs dans les notebooks Colab.
    
    Args:
        notebook_path: Chemin vers le notebook
        image_mappings: Dictionnaire de correspondance chemin local -> URL
    """
    # Exemple de dictionnaire de correspondance
    IMAGE_MAPPINGS = {
        "Mitrani_chain.png": "https://marmote.gitlabpages.inria.fr/_images/Mitrani_chain.png"
    }
    # Implementation complète disponible dans le code source doc_generateArchives.py
```

## 📚 Restructuration du Notebook `MDP_Lesson2.ipynb`

### 

Le notebook a été restructuré avec :

- **Ajout d'une table des matières** avec liens internes pour une navigation facilitée
- **Segmentation en 5 parties distinctes** :
  1. Modèle
  2. Constructeur 1  
  3. Constructeur 2
  4. Constructeur 3
  5. QValue

#### Exemple de navigation interne

```html
Build the MDP - Constructor 1

[Back to Table of Contents](#table-of-contents)
```

## 🔄 Synchronisation Python/C++

### Correspondance des exemples

Pour maintenir la cohérence entre les implémentations Python et C++, une correspondance stricte a été établie :

| Notebook Python | Exemple C++ |
|-----------------|-------------|
| `MDP_Lesson1` | `Example10` |
| `MDP_Lesson2` | `Example11` |
| `MDP_Lesson3` | `Example21` |
| `MDP_Lesson4` | `Example31` |

### Optimisation

- **Suppression des exemples** : `Example20`, `Example22`, `Example30`
- **Harmonisation des structures de code** entre Python et C++

## 🚀 Script `doc_generateArchive.py`

### Fonctionnalités principales

1. **Création d'archive** : Génère `notebooks.zip` incluant les notebooks et leurs images associées
2. **Conversion automatique** : Adapte les chemins d'images pour la compatibilité Colab
3. **Documentation HTML** : Génère automatiquement la documentation via Sphinx

### Utilisation

```bash
python3 doc_generateArchive.py
```

## ⚠️ Points d'attention et bonnes pratiques

### Sphinx et gestion des images

- Lors de la génération avec `make html`, Sphinx copie automatiquement toutes les images référencées dans `_build/html/_images/`
- **Important** : Vérifiez que les chemins relatifs sont corrects (format recommandé : `./image.png`)

### Compatibilité Colab

- Les images sont hébergées en ligne (GitHub, site Marmote officiel)
- Utilisez le script de conversion automatique pour adapter les notebooks

### Recommandation

1. Développement local avec chemins relatifs
2. Test de la génération Sphinx
3. Conversion automatique pour Colab si nécessaire
4. Validation sur les trois plateformes (Jupyter, Sphinx, Colab)

## 📄 Documentation complète

Le rapport détaillé du projet est disponible à l'adresse suivante :
[Rapport LOT 2 - Développement Marmote](https://drive.google.com/file/d/1MLOjsQHPQPMQxEvm_PtTJlogY3Fa6v3p/view?usp=sharing)

## 🤝 Contribution

Ce projet s'inscrit dans le cadre du développement collaboratif de l'écosystème Marmote. Les améliorations apportées visent à faciliter l'utilisation pédagogique et le développement futur du projet.
