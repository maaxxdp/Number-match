// liste_couples.h			(*** FICHIER DONN� AUX �L�VES ***)
// Auteur: Eric Th�, d�c. 2025
// 
// Module qui g�re la liste des coups possibles � jouer.
// Les coups sont repr�sent�s par deux entiers qui repr�sentent 2 cases de la grille de jeu.
// Format : chiffre des unit�s = no. de colonne (1 � 9), 2i�me et 3i�me chiffres = no. ligne.
//          Ex. 24 - 34 == case [2][4] et case [3][4] == "D3" - "D4" (pour le joueur)
// 
// La ligne [LIG_INFOS] (ligne 0) contient la taille totale dans la colonne [COL_TAILLE] (= 0)
// ainsi que le nb. d'�l�ments actuels dans la colonne [COL_NB_ELEM] (= 1).
#ifndef MAX_COUPLES
#include "utilitaires.h"	//pour les fonctions al�atoires

/********************** LES CONSTANTES *************************/
#define MAX_COUPLES 200		//taille maximale de la liste
#define LIG_INFOS   0		//position-ligne pour les infos de la liste
#define COL_TAILLE  0		//position-colonne de la taille totale (� la ligne [0])
#define COL_NBELEM  1		//position-colonne du nb. d'�l�ments (� la ligne [0])

/******************* D�CLARATION DES TYPES *********************/
//Type-tableau pour la liste. Contient 2 colonnes pour les deux cases � jouer.
typedef int t_liste_couples[MAX_COUPLES + 1][2];   //eg. 24 - 34 (== "D3" - "D4")

/***************** D�CLARATIONS DES FONCTIONS ******************/

//remise � z�ro de la liste des couples (les coups possibles)
//PARAM.: la liste des coups possibles
void init_liste_couples(t_liste_couples liste);

//accesseur au nb. d'�l�ments dans la liste
//PARAM.: la liste des coups possibles
//RETOUR: (entier) le nb. d'�l�mengts actuels
int  nb_couples(const t_liste_couples liste);

//permet d'ajouter un nouveau couple � la liste des coups possibles.
//PARAM.: la liste des coups possibles et les deux cases � jouer
//RETOUR: (entier) 1 si le couple a pu �tre ajout�, 0 sinon (liste pleine)
int  ajouter_couple(t_liste_couples liste, int caseA, int caseB);

//v�rifie si la liste des coups contient d�j� [caseA, caseB].
//PARAM.: la liste des coups possibles et les deux cases � jouer
//RETOUR: 1 si ce couple est pr�sent dans la liste, 0 sinon.
int  liste_contient(t_liste_couples liste, int caseA, int caseB);

//permet de choisir un des coups possibles al�atoirement (pour la commande "??")
//PARAM.: la liste des coups possibles et deux r�f�rences aux 2 cases � jouer
//RETOUR: aucun, mais le couple choisi al�atoirement est retourn� via les r�f�rences
void choix_couple_alea(const t_liste_couples liste, int *caseA, int *caseB);

#endif