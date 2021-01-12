# Consignes Rapports

2 pages peuvent suffire

Il faut présenter à la fois la création de la structure (choix, performance)

Et les performances obtenus en calcul d'intersection :

- temps total
- temps / intersection
- espace mémoire ?



Explication : 

* *Features* présentes + ce que je pourrai apporter de plus
* Choix de la structure
* Implémentation de la structure
* Limites observés (notamment grands objets)
* Paramètres de calculs invariants et variants (profondeur de rebonds, supersampling / antialliasing, sphères générés)
* Méthodologie
* Résultats obtenus (voir ci-dessous)
* Faire un exemple avec 3 cas : sans structure, uniquement avec structure, sans structure pour GROS objets et structure pour le reste et expliquer le résultat

Ce que je peux calculer :

* temps création de la structure
* temps total de calcul
* comparaison ratio <u>temps / intersection</u> pour un pixel avec OU sans structure
* nombre de rayons
* nombre de tests d'intersections effectuées (par SceneObject ET par AABB)
* Memory usage ?



# Raytracer

This project is a small raytracer in C++.
It features :

- Orthographic and Perspective cameras
- 