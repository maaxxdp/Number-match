// affichages.h			  (*** soit DONN� au complet OU �CRIRE les 4 premi�res fonctions ***)
// Auteur: Eric Th�, d�c. 2025   
// 
// Module qui g�re toutes les fonctions d'affichages du programme pour la grille, 
// les num�ros dispos, le score et messages.  Tous les affichages-�cran sont d�finies ici.
#ifndef LIG_GRILLE

#include "grille_chiffres.h"    //va aussi inclure le module "liste_couples.h"

//les d�calages pour le coin sup. gauche de l'affichage de la grille
#define LIG_GRILLE  5
#define COL_GRILLE  40

//les autres d�calages-lignes pour les diff�rents messages � afficher
#define LIG_POINTS   0
#define LIG_CHIFFRES 1
#define LIG_SAISIE   LIG_GRILLE - 3
#define LIG_MESSAGES LIG_GRILLE - 2


//Permet d'afficher les r�gles du jeu
void afficher_instructions();

//Permet d'afficher la liste des chiffres dispo (sur la ligne 0) et du score (sur la ligne 1).
//PARAM.: la liste des chiffres encore disponibles et le score � date
//RETOUR: Aucun
void afficher_infos_jeu(const t_tab_chiffres nbr_chiffres, int pts);

//Permet d'afficher la grille des chiffres.
//PARAM.: la grille des chiffres et l'indice de la derni�re ligne non-vide
//RETOUR: Aucun
void afficher_grille(const t_grille_nos grille, int dern_lig);

//Permet d'afficher la suggestion de deux chiffres � choisir en BLEU pendant 5 secondes.
//PARAM.: la colonne, ligne et chiffre de la premi�re case.
//        la colonne, ligne et chiffre de la deuxi�me case.
//RETOUR: Aucun
void afficher_couple(int colA, int ligA, int chA, int colB, int ligB, int chB);

//Affiche le message de demande d'une saisie de case ou commande (sur la ligne 3).
//PARAM.: le num�ro de la case � saisir (soit 1 ou 2)
//RETOUR: Aucun
void demander_saisie(int no_saisie);

//Les 3 fonctions suivantes servent � afficher diff�rents messages durant le jeu
void message(const char* mess);		 //affiche un message d'information (sur la ligne 3) 
void mess_points(int pts);			 //affiche le nb. de points ajout�s (sur la ligne 1)
void mess_erreur(const char* mess);  //affiche un message d'erreur en ROUGE (sur la ligne 3)

#endif