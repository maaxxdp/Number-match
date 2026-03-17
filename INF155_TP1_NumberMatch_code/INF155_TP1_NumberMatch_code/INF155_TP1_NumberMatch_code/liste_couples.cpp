// liste_couples.cpp		   (*** A FAIRE: SEMAINE 1 avec des tests unitaires ***)
// Auteur: Eric The, dec. 2025
// Module qui gere la liste des coups possibles a jouer.
#include "liste_couples.h"

/************ Module LISTE_COUPLES ***************/

//remise a zero de la liste des couples possibles (NOTE: fonction donnee aux eleves!)
void init_liste_couples(t_liste_couples liste) {
	liste[LIG_INFOS][COL_TAILLE] = MAX_COUPLES;
	liste[LIG_INFOS][COL_NBELEM] = 0;
}

/*****************************************************************************/
//permet d'ajouter un nouveau couple a la liste des coups possibles.
int  ajouter_couple(t_liste_couples liste, int caseA, int caseB) {
	//On crée un entier sur l'objet pour cree la condition du prochain tour
	int utilisateur_tab = liste[LIG_INFOS][COL_NBELEM]+1;

	//La condition indique si notre liste est inferieur ou egal au maximum de coup on ajoute dans notre tableau, sinon c'est plein
	if (utilisateur_tab <= MAX_COUPLES) {
		liste[utilisateur_tab][LIG_INFOS]= caseA;
		liste[utilisateur_tab][COL_TAILLE]= caseB;
		liste [LIG_INFOS][COL_NBELEM] = utilisateur_tab; // on l'ajoute dans notre liste de coup
		return 1; // A ajouter avec success le coup
	}
	return 0; // La liste est pleine.
}

/*****************************************************************************/
//accesseur au nb. d'elements dans la liste
int nb_couples(const t_liste_couples liste) {
	// On retourne le nombre la liste d'element
	return liste [LIG_INFOS][COL_NBELEM];
}

/*****************************************************************************/
//verifie si la liste des coups contient deja [caseA, caseB] (OU [caseB, caseA]).
int liste_contient(t_liste_couples liste, int caseA, int caseB) {
	for (int i = 0; i < MAX_COUPLES; i++) {
			if (liste[i][0] == caseA && liste[i][1] == caseB || liste[i][0] == caseB && liste[i][1] == caseA ) {
				return 1;// Le coup [caseA][caseB] est dans la liste
			}
	}
	return 0;// ce n'est pas dans la liste
}
/*****************************************************************************/
//permet de choisir un des coups possibles aleatoirement (pour la commande "??")
void choix_couple_alea(const t_liste_couples liste, int * caseA, int * caseB) {
	int random = entier_aleatoire(1, liste[LIG_INFOS][COL_NBELEM]);

	*caseA = liste[random][0];
	*caseB = liste[random][1];
}