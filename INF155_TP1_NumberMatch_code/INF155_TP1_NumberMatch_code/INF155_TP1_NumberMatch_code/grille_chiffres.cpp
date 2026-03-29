// grille_chiffres.cpp		   *** SEM. 1: fonctions init_grille(), verifier_8_voisins()
// Auteur: Eric Th�, d�c. 2025 *** SEM. 2: tout SAUF trouver_fin_chiffres(), ajouter_chiffres() 
//                             *** SEM. 3: trouver_fin_chiffres(), ajouter_chiffres()
// 
// Module qui g�re la grille des chiffres ainsi que la liste des chiffres encore disponibles.
#include <assert.h>
#include "grille_chiffres.h"

/********************** CONSTANTES PRIV�ES *************************/
//les d�placements pour NORD,    NORD_E,  EST,    SUD_E,  SUD,    SUD_O,  OUEST,  NORD_O
const int dep[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1,-1}, {0,-1}, {-1,-1} };

/************************* MACROS PRIV�ES **************************/
//permet d'incr�menter une position-colonne avec retour � la ligne suivante si c'est le cas
#define INC_POS(lig, col)  ((((col) + 1) == NB_COL) ? ((lig)++, (col) = 1) : (col)++)

/**************** D�FINITION DES FONCTIONS PRIV�ES *****************/

//Fonction pour trouver la premi�re case vide suite au DERNIER chiffre pr�sent dans la grille.
//Cette fonction est utile pour la reg�n�ration de nouveaux chiffre � la fin de la grille.
//PARAM.: la grille de jeu et deux r�f�rences � la position de fin de grille
//RETOUR: aucun, mais la position de reg�n�ration de chiffres est retourn� dans les r�f�rences
static void trouver_fin_chiffres(const t_grille_nos grille, int * lig, int * col) { 
	
}

/*****************************************************************************/
//Sous-fonction pour le cas sp�cial de la recherche vers la droite (EST).
//Permet de continuer la recherche d'un couple � la ligne suivante de la grille.
//Cette fonction sera appel�e par "verifier_huit_dir()" (pour le sens EST seulement).
//PARAM.: la grille de jeu, la position actuelle [lig][col] et la listes des coups possibles
//RETOUR: Aucun
static void verifier_sens_est(const t_grille_nos grille, int lig, int col,
	                          t_liste_couples liste) {						//*** SEM. 2

}

/*****************************************************************************/
//V�rifie les couples possibles � partir de [lig, col] dans les 8 directions possibles.
//  i.e. NORD, NORD_E, EST, SUD_E, SUD, SUD_O, OUEST, NORD_O
//PARAM.: Re�oit la grille, la position actuelle [lig, col] et la liste de couples � date.
//RETOUR: Aucun, mais la liste des coups possibles sera potentiellement augment�e
static void verifier_huit_dir(const t_grille_nos grille, int lig, int col,
	                          t_liste_couples liste) {						//*** SEM. 2

}

/*****************************************************************************/
//Sous-fonction qui v�rifie la pr�sence du chiffre "ch" dans les 8 cases voisines � [lig][col]
//La fonction est utilis�e lors de l'initialisation de la grille pour ne pas des chiffres.
//PARAM.: Re�oit la grille, la position actuelle [lig, col] et le chiffre � v�rifier
//RETOUR: 1 si le chiffre "ch" se trouve dans une cases voisine � [lig][col], 0 sinon.
static int verifier_ch_voisins(t_grille_nos grille, int lig, int col, int ch) {
	//*** SEM. 1

	for (int i = -1 ; i <= 1 ; i++) {
		for (int j = -1 ; j <= 1 ; j++) {
			if (i == 0 && j == 0)
				continue;
			int nbcol = col + j;

			if (nbcol == 0)//permet d'ignorer la colone [0] car elle ne fait pas partie des valeurs a vérifier
				continue;

			if (grille [lig + i][col + j] == ch)
				return 0; // retourne 0 si trouve
		}
	}
	return 1;  //retourne 1 si pas trouve
}

/**************** D�FINITION DES FONCTIONS PUBLIQUES *****************/

//re�oit une grille vide et g�n�re les premieres lignes de chiffres alea.
int init_grille(t_grille_nos grille, t_tab_chiffres nbr_chiffres) {       //*** SEM. 1

	double facteur = 4 + ((double)rand() /RAND_MAX);
	int nb_chiffre_genere = (int)(facteur * 9);
	int ligne = 0;
	int colone = 1;
	int chiffre;

	if (nb_chiffre_genere % 2 != 0) { //si numero impair, ajoute 1 a ce dernier
		nb_chiffre_genere++;
	}
	for (int i = nb_chiffre_genere ; i > 0 ; i--) {//assure de generer le bon nombre de numeros
		do {
			chiffre = entier_aleatoire(1,9);//genere un numero aleatoire entre 1 et 9
		} while (verifier_ch_voisins(grille, ligne, colone,chiffre) == 0);

		if (nbr_chiffres[chiffre] == 0) {
			nbr_chiffres[POS_NB]++;
		}

		nbr_chiffres[chiffre]++;

		grille [ligne][colone] = chiffre;
		grille [ligne][POS_NB]++;

		INC_POS(ligne,colone);

	for (int i = 1; 1 <= 9 ; i++) {
		if (nbr_chiffres[i] == 0) {// si le chiffre i n'a pas ete genere
			nbr_chiffres[POS_NB]++;
			nbr_chiffres[i]++;
			grille [ligne][colone] = i;//ajoute le numero i dans la case
			grille [ligne][POS_NB]++;//augment compte numero sur la ligne
			INC_POS(ligne,colone);


		}
	}

	return ligne;
}

/*****************************************************************************/
//permet de g�n�rer la liste de tous les coups (couples) possibles � jouer.
int generer_listes_couples(const t_grille_nos grille, t_liste_couples liste) {   //*** SEM. 2


	return 0;   //le nb. de couples g�n�r�s
}

/*****************************************************************************/
//permet de g�n�rer de nouveau chiffres alea. qui seront ajout�s � la suite des
//chiffre restants dans la "grille".
void ajouter_chiffres(t_grille_nos grille, t_tab_chiffres nbr_chiffres, int* dern_lig) {
	double facteur = reel_aleatoire(MIN_NB_NEW, MAX_NB_NEW);   //facteur entre [1.0, 5.0]
	int nb_ch = (int)(facteur * nbr_chiffres[POS_NB]);     //le nb. de chiffres � g�n�rer
	int lig = *dern_lig, col;		//la ligne et colonne d'ajout
	int i = 0;						//compteur du nb. de chiffres g�n�r�s � date		
	int chiffre, prec = 0;			//le chiffre aleatoire et le chiffre pr�c�dent g�n�r�

	/* localisation de la premi�re case vide suite aux chiffres pr�sents dans la grille */
	trouver_fin_chiffres(grille, &lig, &col);

	/* Boucle pour le nb. de chiffres d�sir�s */
	if (nb_ch % 2) nb_ch++;         //ce nombre doit absolument �tre PAIR!
	while (i < nb_ch) {
		//on g�n�re un chiffre aleatoire tant qu'il n'est PLUS disponible dans le jeu
		//OU que c'est le m�me que le chiffre pr�c�dent (pour �viter les doublons!)
		do {
			chiffre = entier_aleatoire(1, 9);
		} while (nbr_chiffres[chiffre] == 0 || chiffre == prec);
			    
		nbr_chiffres[chiffre]++;	//incr�menter le nb. de pr�sences de ce chiffre
		grille[lig][col] = chiffre; //ajout du "chiffre" dans cette case
		grille[lig][POS_NB]++;      //le nb. de chiffres sur cette ligne est incr�ment�

		if (nbr_chiffres[POS_NB] > 1)  //si il existe au moins 2 chiffres restants dans le jeu
			prec = chiffre;			//copier le chiffre actuel dans le chiffre pr�c�dent

		//incr�ment de la position lin�aire avec retour � la ligne suivante si n�cessaire
		if (++i < nb_ch)  INC_POS(lig, col);

		if (lig == MAX_LIG) {   //plus de lignes disponibles dans la grille??
			lig--;				//on recule � la derniere ligne [MAX_LIG - 1] et on quitte!
			break;
		}
	}

	*dern_lig = lig;   //on r�cup�re l'indice de la derni�re ligne avec au moins un chiffre
}

/*****************************************************************************/
//permet de retirer la ligne vide [no_lig] de la grille des chiffres.
//Les lignes suivantes seront toutes recopiée UNE ligne plus haut pour
//remplir l'espace vide.
void retirer_ligne(t_grille_nos grille, int no_lig) {						
	int lig = no_lig;	//la ligne à retirer

	do {
		for (int col = 0; col < NB_COL; col++)
			//copie de la ligne suivante si elle existe (copie de 0 sinon)
			grille[lig][col] = ((lig + 1) < MAX_LIG) ? grille[lig + 1][col] : 0;

		lig++;
	} while (lig < MAX_LIG && grille[lig][POS_NB]);   //tant que les lignes sont NON-vides
}

/*****************************************************************************/
//Permet d'effacer (mettre à zéro) la case "pos" de la grille de jeu.
void effacer_chiffre(t_grille_nos grille, int pos) {						
	grille[pos / 10][pos % 10] = 0; //avec conversions de la position-linéaire
	grille[pos / 10][POS_NB]--;     //un chiffre de moins sur cette ligne
}

/*****************************************************************************/
//Permet de retirer (mettre à zéro) le chiffre "ch" de la liste des chiffres dispos.
int retirer_chiffre(int ch, t_tab_chiffres nbr_chiffres) {					
	/* on compte un chiffre de moins pour 'ch' dans la liste */
	nbr_chiffres[ch]--;

	/* si ce compteur tombe à zéro le chiffre est éliminé du jeu */
	if (!nbr_chiffres[ch]) {
		nbr_chiffres[POS_NB]--;   //un chiffre d'éliminé!
		return ch;                //on retourne le chiffre qui vient d'être éliminé
	}
	return 0;   //aucun chiffre a été éliminé
}

/*****************************************************************************/
//Accesseur au chiffre se trouvant à la case "no_case" de la grille.
int get_chiffre_case(const t_grille_nos grille, int no_case) {				
	return grille[no_case / 10][no_case % 10];   //avec conversions de la position-linéaire
}

/*****************************************************************************/
//Accesseur au nb. de chiffres restants dans le jeu (la case [0] du tableau).
int nb_chiffres_restants(const t_tab_chiffres nbr_chiffres) {				
	return nbr_chiffres[POS_NB];
}
