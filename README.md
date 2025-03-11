# README - Pathfinding Project

## Description

Ce projet implémente un système de pathfinding basé sur l'algorithme A\* en C++. Il permet de générer une carte sous forme de nœuds de navigation et de trouver le chemin optimal entre un point de départ et un point d'arrivée. Le projet repose sur une structure modulaire avec des classes bien définies pour représenter la carte, les nœuds de navigation et les différentes fonctionnalités liées à la recherche de chemin.

## Structure du projet

Le projet est organisé autour des fichiers suivants :

### 1. `map.h`

Cette classe représente la carte et gère la recherche de chemin.

#### Méthodes principales :

- `generate_map(const glb::map::map map_size)`: Génère une carte de la taille spécifiée.
- `init_target(const glb::world::location start_coord, const glb::world::location end_coord)`: Initialise les points de départ et d'arrivée.
- `find_path()`: Implémente l'algorithme A\* pour trouver un chemin.
- `print_map()`, `print_path()`: Permettent d'afficher la carte et le chemin trouvé.

#### Attributs principaux :

- `std::vector<navigation_node*> map_`: Contient l'ensemble des nœuds de la carte.
- `navigation_node* start_node_`, `navigation_node* end_node_`: Pointeurs vers les nœuds de départ et d'arrivée.
- `std::vector<navigation_node*> open_queue_`, `closed_queue_`: Listes utilisées par l'algorithme A\* pour explorer les nœuds.

### 2. `navigation_node.h`

Cette classe représente un nœud de navigation utilisé dans la carte et contient les informations nécessaires à l'algorithme A\*.

#### Méthodes principales :

- `set_gcost(int gcost)`, `set_hcost(int hcost)`: Définissent les coûts G et H du nœud.
- `set_parent(navigation_node* parent)`: Définit le parent du nœud pour reconstruire le chemin.
- `add_neighbor(navigation_node* neighbor)`: Ajoute un voisin au nœud.
- `fcost()`, `gcost()`, `hcost()`: Renvoient les coûts utilisés dans A\*.
- `get_distance_to(const navigation_node* target)`: Calcule la distance au nœud cible.

#### Attributs principaux :

- `glb::node::s_navigation_node nav_node_`: Stocke les données du nœud (parent, coûts, type).
- `std::vector<navigation_node*> neighbors_`: Liste des nœuds voisins.
- `glb::world::location location_`: Position du nœud.

### 3. `global_var.h`

Ce fichier contient les définitions des structures et types globaux utilisés dans le projet.

#### Éléments principaux :

- `enum map`: Définit plusieurs tailles de carte prédéfinies.
- `enum node_type`: Définit les types de nœuds (`start_node`, `end_node`, `path_node`, etc.).
- `struct s_navigation_node`: Stocke les informations nécessaires à la navigation (parent, coûts, type).
- `struct location`: Représente une position dans la carte et permet de calculer la distance entre deux points.

### 4. Fonctionnalités globales (`glb` namespace)

- `find(std::vector<navigation_node*>& list, const navigation_node* node)`: Recherche un nœud dans une liste et retourne un booléen indiquant sa présence.

## Algorithme de Pathfinding (A\*)

L'algorithme A\* utilisé fonctionne comme suit :

1. Ajoute le nœud de départ à la `open_queue_`.
2. Boucle tant qu'il y a des nœuds à explorer :
   - Sélectionne le nœud avec le plus petit `fcost`.
   - Le déplace de la liste ouverte à la liste fermée.
   - Vérifie si c'est le nœud d'arrivée : si oui, reconstruit le chemin.
   - Explore ses voisins, met à jour leurs coûts et les ajoute à `open_queue_` si nécessaire.
3. Une fois le chemin trouvé, la méthode `reconstruct_path` permet de l'extraire.

## Compilation et Exécution

Le projet est une solution utilisable directement dans Visual Studio (2019 ou plus) et JetBrains Rider.

## Améliorations possibles

- Ajout d'une interface graphique pour visualiser la recherche de chemin en temps réel.
- Optimisation de l'algorithme pour améliorer les performances sur de grandes cartes.
- Support de différents types de terrains avec des coûts de déplacement variables.

## Conclusion

Ce projet constitue une implémentation modulaire et extensible de l'algorithme A\* pour la navigation dans un environnement 2D. Il peut être utilisé dans des simulations, des jeux vidéo ou d'autres applications nécessitant un pathfinding efficace.

