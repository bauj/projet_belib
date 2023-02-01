# Projet Formation AJC : Traitement de données Belib'

URL dataset : [Statut des bornes Belib' parisiennes](https://parisdata.opendatasoft.com/explore/dataset/belib-points-de-recharge-pour-vehicules-electriques-disponibilite-temps-reel/information/?disjunctive.statut_pdc&disjunctive.arrondissement)


### Récupération des données  <!-- :heavy_check_mark: -->

+ Création d'une base de données SQLite3 `belib_data.db` comprenant 3 tables :
    + **Table Bornes** : contient l'ensemble des données des bornes Belib. 
Cette table est mise à jour quotidiennement à 17h20. Il s'agit d'une **table 
temporaire**, sauvegardée dans le cas où l'on souhaite exploiter plus de 
données dans la suite du projet. Elle n'est pas mise à jour sur la carte.
    + **Table General** : contient le nombre total de bornes associées à chaque
statut : disponible, occupé, en maintenance, etc ... Cette table est utilisée 
pour un affichage qui permet un aperçu global du service.
    + **Table Stations_fav** : contient les données de stations Belib 
enregistrées autour d'un lieu favori inséré dans l'application. Les données 
sont récupérées 3x par jour (9h40, 12h, 17h20) et permettent de tracer une 
évolution temporelle du statut de ces bornes pour ces 3 moments de la journée.
*[Perspectives] Ajout de la possibilite d'ajouter des favoris* 
*[Perspectives] On pourrait penser à inclure la possibilite de modifier les 
horaires de recuperation.*
    + **Table Stations_live** : contient les données de stations Belib 
trouvées suite à la requête d'un utilisateur. Elle est nettoyée au lancement 
d'une requête pour ne garder que les résultats voulus.
*[Perspectives] Tracer l'historique des bornes trouvées ? est-ce utile ?*

+ Récupération des données dans l'ensemble des Tables de la base de données 
`belib_data.db`à l'aide du script python `recuperation_data_belib.py`.  
Quatre options de récupération possibles en fonction de la table de la de BDD 
(Base De Données) visée :
    + `-b`, `--bornes` : récupération des données de l'ensemble des bornes et 
injection  dans la table `Bornes`.
    + `-g`, `--general` : récupération des données de l'ensemble des bornes 
groupées par statut et injection  dans la table `General`.
    + `-f`, `--favori` : récupération des données des stations en favori et 
injection  dans la table `Stations_fav`.
    + `-l`, `--live` : récupération des données des stations situées dans un 
rayon `<distance>` de l'adresse entrée `<adresse>`
        + `-a`, `--adresse` <adresse>   : permet d'entrer une `<adresse>` sous 
la forme d'une chaine de caractères. 
        + `-d`, `--distance` <distance> : permet d'entrer une `<distance>` sous
 la forme d'une chaine de caractères (de type "0.5km").

+ Deux fichiers de données au format `JSON` sont récupérés quotidiennement :
    + `raw_data_tot_belib_<DDJ>.json` : L'ensemble des données (/exports) obtenu à l'aide de de la fonction : `Get_all_data()`.
L'API limite les requetes à 100 records seulement. Le téléchargement de l'ensemble des données est nécessaire si on souhaite exploiter plus de données par la suite.
Taille du fichier : ~1.3Mo.

    + `raw_data_nb_bornes_belib_<DDJ>.json` : Données obtenues à l'aide de de la fonction : `Get_grouped_by_status_data()`.
Fichier contenant les résultats de base qui seront exploités pour le moment. Taille du fichier : ~1.5Ko.

    + ** AJOUTER MODELE JSON ** 

+ Les données seront récupérées tous les jours à 9h40, 12h30, 17h20 (**crontab**)


### Traitement des données brutes et bdd sqlite <!-- :heavy_check_mark: -->

+ **En C** : parsing du fichier `.json` du jour à l'aide d'une bibliothèque faite pour (voir [librairie JSMN](https://github.com/zserge/jsmn)). 

+ Traitement des données : Lecture et parsing du fichier `raw_data_nb_bornes_belib_<DDJ>.json`. Le champ `nb_bornes` associé à chaque type de `statut_pdc` est récupéré et stocké dans une bdd SQLite. 

+ Construction / Insertion bdd sqlite. Liste des noms de colonnes :
    + `DATERECOLTE`  |  `DISPONIBLE`  | `OCCUPE`  | `MAINTENANCE`  |  `INCONNU` ....

+ *INFO* -- Statuts points de charge :  
    + Disponible
    + Pas implémenté
    + Occupé (en charge)
    + En cours de mise en service
    + En maintenance
    + Mise en service planifiée
    + Supprimé
    + Réservé
    + Inconnu

+ Passer un coup de Valgrind + ElectricFence <!-- :heavy_check_mark: -->

### Lecture bdd sqlite et plotting      :soon:
 
+ **En Python** : lecture de la bdd via bibliothèque python sqlite3
+ Plot de deux figures (*pour l'instant*) en utilisant la bibliothèque matplotlib
    + Fig 1 : Evolution temporelle (quotidienne) du nombre de points de charge en maintenance, disponibles et occupés
    + Fig 2 : Evolution temporelle (quotidienne) du taux d'occupation, taux de maintenance, etc ... 
    + Fig 3 : Répartition des statuts des points de charge du jour.
+ Fichiers figures enregistrés au format PNG.

### Update page HTML et CSS      :soon:

+ Un peu d'HTML et de CSS pour mettre en valeur les résultats, décrire le projet, etc ...

### Mise en place de l'ensemble du projet sur la carte embarquée (voir Overlay_BR)     :soon:

+ Prendre en compte la compilation des librairies si non déjà disponibles dans buildroot.
+ Bibliotheques utilisees : matplotlib, sqlite3 (PYTHON), jsmn, sqlite3 (C).

