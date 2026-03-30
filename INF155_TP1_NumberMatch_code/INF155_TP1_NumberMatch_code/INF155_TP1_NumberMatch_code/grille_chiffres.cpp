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
	int nb = 0;		//compteur du nb. de chiffres pr�sents � la derni�re lignes de la grille

	*col = 1;		//la colonne [0] n'est pas un chiffre de la grille!

	while (nb < grille[*lig][POS_NB]) {   //tant que l'on a pas vu tous les chiffres de la lig
		if (grille[*lig][*col])  nb++;	  //on compte les chiffres rencontr�s

		(*col)++;   //avancer la colonne pour trouver la case vide apr�s le dernier chiffre
	}

	//cas sp�cial: le dernier chiffre se trouve dans la derni�re colonne de cette ligne
	if (*col == NB_COL) {
		(*lig)++;  *col = 1;   //passer � la premi�re case de la ligne suivante!
	}
}

/*****************************************************************************/
//Sous-fonction pour le cas sp�cial de la recherche vers la droite (EST).
//Permet de continuer la recherche d'un couple � la ligne suivante de la grille.
//Cette fonction sera appel�e par "verifier_huit_dir()" (pour le sens EST seulement).
//PARAM.: la grille de jeu, la position actuelle [lig][col] et la listes des coups possibles
//RETOUR: Aucun
static void verifier_sens_est(const t_grille_nos grille, int lig, int col,
	                          t_liste_couples liste) {						//*** SEM. 2
	int val1 = grille[lig][col];	//le chiffre dans cette case
	int	val2 = 0;					//le prochain chiffre
	int lig2 = lig, col2 = col;		//copies de la position actuelle (pour les d�placements)

	do {
		//avancer vers la droite avec potentiel changement de ligne lorsque rendu au bout
		INC_POS(lig2, col2);

	  //tant que l'on est dans la grille et que les cases rencontr�es sont VIDES (= 0)
	} while (lig2 < MAX_LIG && !grille[lig2][col2]);

	if (lig2 < MAX_LIG)
	   val2 = grille[lig2][col2];	//le chiffre de la premi�re case non-vide rencontr�e

	//est-ce un couple valide qui n'est pas d�j� dans la liste?
	if ((val1 == val2 || (val1 + val2 == 10)) &&
		!liste_contient(liste, lig * 10 + col, lig2 * 10 + col2)){   //avec conversion de pos.
		   assert(ajouter_couple(liste, lig * 10 + col, lig2 * 10 + col2));  //ajout du couple
	}
}

/*****************************************************************************/
//V�rifie les couples possibles � partir de [lig, col] dans les 8 directions possibles.
//  i.e. NORD, NORD_E, EST, SUD_E, SUD, SUD_O, OUEST, NORD_O
//PARAM.: Re�oit la grille, la position actuelle [lig, col] et la liste de couples � date.
//RETOUR: Aucun, mais la liste des coups possibles sera potentiellement augment�e
static void verifier_huit_dir(const t_grille_nos grille, int lig, int col,
	                          t_liste_couples liste) {						//*** SEM. 2
	int lig2, col2;  //copies de la position actuelle (pour les d�placements)
	int val1, val2;  //valeurs des deux cases � comparer

	val1 = grille[lig][col];	//chiffre de la case actuelle

	/* pour les 8 directions possibles.. */
	for (int dir = 0; dir < 8; dir++) {
		//Cas sp�cial: aller vers la droite (avec possible retour � la ligne suivante)
		if (dir == 2)
			verifier_sens_est(grille, lig, col, liste);
		else {
			//Pour toutes les autres directions..
			lig2 = lig;  col2 = col;		//reprendre une copie de la position actuelle
			do {
				//appliquer le d�placement dans la direction "dir" (avec le tableau "dep[][]")
				lig2 += dep[dir][0];		//le delta-y
				col2 += dep[dir][1];		//le delta-x

			  //tant que l'on est toujours dans la grille de jeu (avec col >= 1)
			} while (lig2 >= 0 && grille[lig2][POS_NB] && col2 >= 1 && col2 < NB_COL
				     && !grille[lig2][col2]);   //..et que les cases rencontr�es sont VIDES

			//si nous avons atteint une deuxi�me case valide et non-vide..
			if (lig2 >= 0 && grille[lig2][POS_NB] && col2 >= 1 && col2 < NB_COL) {
				val2 = grille[lig2][col2];	//le deuxi�me chiffre

				//est-ce un couple valide qui n'est pas d�j� dans la liste?
				if ((val1 == val2 || (val1 + val2 == 10))
					&& !liste_contient(liste, lig * 10 + col, lig2 * 10 + col2)) {
					   assert(ajouter_couple(liste, lig * 10 + col, lig2 * 10 + col2));
				}
			}
		}
	}
}

/*****************************************************************************/
//Sous-fonction qui v�rifie la pr�sence du chiffre "ch" dans les 8 cases voisines � [lig][col]
//La fonction est utilis�e lors de l'initialisation de la grille pour ne pas des chiffres.
//PARAM.: Re�oit la grille, la position actuelle [lig, col] et le chiffre � v�rifier
//RETOUR: 1 si le chiffre "ch" se trouve dans une cases voisine � [lig][col], 0 sinon.
static int verifier_8_voisins(t_grille_nos grille, int lig, int col, int ch) {   //*** SEM. 1
	int lig2, col2;		//copies de la position actuelle (pour les d�placements)

	/* pour les 8 directions possibles.. */
	for (int dir = 0; dir < 8; dir++) {
		//appliquer le d�placement dans la direction "dir" (avec le tableau "dep[][]")
		lig2 = lig + dep[dir][0];
		col2 = col + dep[dir][1];

		//si on est toujours dans la grille de jeu (avec col >= 1) et que le chiffre est l�
		if (lig2 >= 0 && lig2 < MAX_LIG && col2 >= 1 && col2 < NB_COL
			&& grille[lig2][col2] == ch)
			   return 1;		//le chiffre "ch" est pr�sent
	}

	return 0;    //ce chiffre ne se trouve pas autour de la case [lig][col]
}

/**************** D�FINITION DES FONCTIONS PUBLIQUES *****************/

//re�oit une grille vide et g�n�re les premieres lignes de chiffres alea.
int init_grille(t_grille_nos grille, t_tab_chiffres nbr_chiffres) {       //*** SEM. 1
	double facteur = reel_aleatoire(MAX_NB_NEW-1, MAX_NB_NEW);   //facteur entre [4.0, 5.0]
	int nb_ch = (int)(facteur * 9); //le nb. de chiffres � g�n�rer selon le facteur choisi
	int chiffre;
	int lig = 0, col = 1;			//la position actuelle (avec col >= 1)
	int i = 0;						//compteur du nb. de chiffres g�n�r�s � date

	/* Boucle pour le nb. de chiffres d�sir�s */
	if (nb_ch % 2) nb_ch++;         //ce nombre doit absolument �tre PAIR!
	while (i < nb_ch) {
		//on g�n�re un chiffre alea. tant qu'il est pr�sent autour de la case [lig][col]
		do {
			chiffre = entier_aleatoire(1, 9);
		} while (verifier_8_voisins(grille, lig, col, chiffre));

		//si c'est la premi�re fois que l'on rencontre ce chiffre..
		if (nbr_chiffres[chiffre] == 0)
			nbr_chiffres[POS_NB]++;      //compter le nombre de chiffres distincts

		nbr_chiffres[chiffre]++;	//incr�menter le nb. de pr�sences de "chiffre" dans le jeu
		grille[lig][col] = chiffre; //ajout du "chiffre" dans cette case
		grille[lig][POS_NB]++;      //le nb. de chiffres sur cette ligne est incr�ment�

		//incr�ment de la position lin�aire avec retour � la ligne suivante si n�cessaire
		if (++i < nb_ch)  INC_POS(lig, col);
	}

	//reste-t'il des chiffres non-choisi (ils doivent tous �tre g�n�r� au moins UNE fois)?
	if (nbr_chiffres[0] < 9) {
		//trouver le(s) chiffre(s) non-g�n�r�(s)
		for (int ch = 1; ch < 9; ch++)
			if (nbr_chiffres[ch] == 0) {
				nbr_chiffres[POS_NB]++; //incr�menter le nombre de chiffres distincts
				nbr_chiffres[ch]++;		//incr�menter le nb. de pr�sences de ce chiffre
				grille[lig][col] = ch;  //ajout du chiffre "ch" dans cette case
				grille[lig][0]++;       //le nb. de chiffres sur cette ligne est incr�ment�

				INC_POS(lig, col);      //incr�ment de la position lin�aire
			}
	}

	return lig;	  //on retourne l'indice de la derni�re ligne avec au moins un chiffre
}

/*****************************************************************************/
//permet de g�n�rer la liste de tous les coups (couples) possibles � jouer.
int generer_listes_couples(const t_grille_nos grille, t_liste_couples liste) {   //*** SEM. 2
	int lig = 0, col;   //la position actuelle dans la grille

	/* On boucle tant que les lignes sont non-vides */
	while (grille[lig][POS_NB]) {
		//Pour les 9 colonnes de chiffres de cette ligne ([1] � [9])
		for (col = 1; col < NB_COL; col++) {
			//Si la case n'est pas vide, ajouter tous les couples possibles
			if (grille[lig][col])
				verifier_huit_dir(grille, lig, col, liste);
		}

		lig++;   //passer � la ligne suivante
	}

	return nb_couples(liste);   //le nb. de couples g�n�r�s
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
//Les lignes suivantes seront toutes recopi�e UNE ligne plus haut pour
//remplir l'espace vide.
void retirer_ligne(t_grille_nos grille, int no_lig) {						//*** SEM. 2
	int lig = no_lig;	//la ligne � retirer

	do {
		for (int col = 0; col < NB_COL; col++)
			//copie de la ligne suivante si elle existe (copie de 0 sinon)
			grille[lig][col] = ((lig + 1) < MAX_LIG) ? grille[lig + 1][col] : 0;

		lig++;
	} while (lig < MAX_LIG && grille[lig][POS_NB]);   //tant que les lignes sont NON-vides
}

/*****************************************************************************/
//Permet d'effacer (mettre � z�ro) la case "pos" de la grille de jeu.
void effacer_chiffre(t_grille_nos grille, int pos) {						//*** SEM. 2
	grille[pos / 10][pos % 10] = 0; //avec conversions de la position-lin�aire
	grille[pos / 10][POS_NB]--;     //un chiffre de moins sur cette ligne
}

/*****************************************************************************/
//Permet de retirer (mettre � z�ro) le chiffre "ch" de la liste des chiffres dispos.
int retirer_chiffre(int ch, t_tab_chiffres nbr_chiffres) {					//*** SEM. 2
	/* on compte un chiffre de moins pour 'ch' dans la liste */
	nbr_chiffres[ch]--;

	/* si ce compteur tombe � z�ro le chiffre est �limin� du jeu */
	if (!nbr_chiffres[ch]) {
		nbr_chiffres[POS_NB]--;   //un chiffre d'�limin�!
		return ch;                //on retourne le chiffre qui vient d'�tre �limin�
	}
	return 0;   //aucun chiffre a �t� �limin�
}

/*****************************************************************************/
//Accesseur au chiffre se trouvant � la case "no_case" de la grille.
int get_chiffre_case(const t_grille_nos grille, int no_case) {				//*** SEM. 2
	return grille[no_case / 10][no_case % 10];   //avec conversions de la position-lin�aire
}

/*****************************************************************************/
//Accesseur au nb. de chiffres restants dans le jeu (la case [0] du tableau).
int nb_chiffres_restants(const t_tab_chiffres nbr_chiffres) {				//*** SEM. 2
	return nbr_chiffres[POS_NB];
}