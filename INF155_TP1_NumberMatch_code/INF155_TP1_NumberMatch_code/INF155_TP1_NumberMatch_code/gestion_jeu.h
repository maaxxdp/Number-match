// gestion_jeu.h				*** � FAIRE : SEMAINES 3 & 4 ***
// Auteur: Eric Th�, d�c. 2025
// 
// Module qui g�re les saisies, commandes et les points du jeu.
#ifndef CODE_QUITTER
#include "affichages.h"   //va aussi inclure les modules "grille_chiffres.h, liste_couples.h"

/********************** LES CONSTANTES *************************/
//les 3 valeurs de codes-commandes (peuvent aussi �tre d�clar�es dans une liste "enum")
#define CODE_QUITTER  0			//pour quitter le jeu
#define CODE_AIDE     -1		//demander une suggestion de coup � jouer
#define CODE_CHIFFRES -2		//demander une reg�n�ration de nouveaux chiffres

//les valeurs des points attribu�s durant le jeu
#define PTS_COUPLE_VOISIN  1	//�limination d'un couple de chiffres voisins (distance de 1)
#define PTS_COUPLE_SEPARE  4	//�limination d'un couple de chiffres s�par�s par des espaces
#define PTS_LIGNE_RETIREE  10	//�limination d'une ligne vide suite � un retrait de chiffres

/***************** D�CLARATIONS DES FONCTIONS ******************/

//Effectue la saisie du coup valide (deux cases) OU d'un code-commande (dans "caseA").
//PARAM.: la grille des chiffres, l'indice de la derni�re ligne et deux r�f�rences aux 2 cases
//RETOUR: retour de 1 si un coup valide (deux cases) a �t� saisi, 0 sinon ("caseB" est vide)
int  valider_coup(t_liste_couples liste, int dern_lig, int * caseA, int * caseB);

//Permet de jouer un coup, la fonction va effacer les deux cases re�ues dans la grille.  
//Si une (ou deux) lignes sont vid�es, on va les retirer et l'indice de la derni�re ligne avec 
//au moins un chiffre sera d�cr�ment�.
//PARAM.: la grille des chiffres, les deux cases � vider, la liste de chiffres dispos
//        et une r�f�rence sur la derni�re ligne active de la grille.
//RETOUR: le nombre de points suppl�mentaires obtenus avec le coup (la *dern_lig peut changer)
int  jouer_coup(t_grille_nos grille, int caseA, int caseB, t_tab_chiffres nbr_chiffres,
	            int * dern_lig);

//Affiche les 2 cases d'un coup valide choisi al�atoirement par le programme (commande "??")
//PARAM.: la grille des chiffres et les deux cases choisies
//RETOUR: Aucun
void afficher_choix_alea(const t_grille_nos grille, int caseA, int caseB);

#endif