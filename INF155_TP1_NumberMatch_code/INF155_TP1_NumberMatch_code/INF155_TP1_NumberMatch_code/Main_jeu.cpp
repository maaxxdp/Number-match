// Main_jeu.cpp					(*** SEMAINE 4: le main() final ***)
// Auteur: Eric Th�, d�c. 2025
// 
// Programme principale du jeu "Number Match". Impl�mente le d�roulement g�n�rale du jeu. 
// Le programme saisie les entr�es du joueur et ex�cute la commande re�ue, soit : 
//  - �limination d'un couple de chiffres dans les deux cases saisies
//  - suggestion d'un couple � �liminer � partir de la liste des coups possibles
//  - ajouts de nouveaux chiffres al�atoires � la grille de jeu (reg�n�reations)
//  - quitter le jeu
//
// Le jeu se termine lorsque la grille est compl�tement vid�e OU qu'aucun coup valide existe.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>         //pour le "sprintf()" (NOTE: le "printf()" n'est PAS permis ici!)
#include<stdlib.h>
#include "gestion_jeu.h"  //va aussi inclure les modules "grille_chiffres.h, liste_couples.h"

//le nombre de reg�n�rations de nouveaux chiffres permis
#define NB_REGEN_CHIFFRES  3   

int main(void) {
	t_grille_nos grille = { 0 };			//la grille des chiffres
	t_tab_chiffres nbr_chiffres = { 0 };	//la liste des chiffres disponibles (9 au d�part)
	t_liste_couples liste = { 0 };			//la liste des coups possibles
	int score = 0;							//le pointage accumul� du joueur
	int last_lig=0;							//la derni�re ligne non-vide de la grille
	int nb_nouv_ch = NB_REGEN_CHIFFRES;		//le nombre de reg�n�rations de chiffres restants
	int regen = 0;							//indique une demande de reg�n�ration de chiffres
	int	quitter = 0;						//indique que le joueur d�sire quitter le jeu
	int caseA, caseB;						//les deux cases s�lectionn�es (eg. 24 et 34)
	char mess[60];							//chaine-tampon pour la g�n�ration de messages

	init_rand();				//appel de "srand()"
	
	afficher_instructions();	//affichage des instructions du jeu

	/* Initialisation de la grille initiale avec affichages de d�part */
	last_lig = init_grille(grille, nbr_chiffres);
	afficher_infos_jeu(nbr_chiffres, score);
	afficher_grille(grille, last_lig);
	
	/* Boucle principale du jeu: */
	do {
		/* Vider la liste des coups possibles */
		init_liste_couples(liste);
		if (generer_listes_couples(grille, liste)) {   //s'il existe au moins UN coup possible
			/* Saisie d'un couple de cases valides (caseA, caseB) OU d'un code - commande */
			if (valider_coup(liste, last_lig, &caseA, &caseB))
			    /* On ex�cute le coup et on r�cup�re les points ajout�s au score */
			    score += jouer_coup(grille, caseA, caseB, nbr_chiffres, &last_lig);
			else {  
				/* Retour de 0: nous avons re�u un code-commande (dans la variable "caseA") */
				switch (caseA) {
				case CODE_QUITTER:  //code "XX" = quitter le jeu
					                quitter = 1;   
					                break;

				case CODE_AIDE:     //code "??" = suggestion d'un coup possible
									choix_couple_alea(liste, &caseA, &caseB); 
					                afficher_choix_alea(grille, caseA, caseB);
					                break;

				case CODE_CHIFFRES: //code "++" = ajout de nouveaux chiffres alea.
									if (nb_nouv_ch > 0)  //reste't-il des reg�n�rations?
										regen = 1;
								    else 
					                    mess_erreur("Plus de regenerations disponibles!");
				}
			}
		}
		
		/* S'il y'a une demande de reg�n�ration OU plus de coups possibles dans la grille */
		if (regen || (nb_couples(liste)==0 && nb_nouv_ch > 0)) {
			//ajout de nouveaux chiffres alea. et reg�n�ration de la liste des coups possibles
			ajouter_chiffres(grille, nbr_chiffres, &last_lig);
			init_liste_couples(liste);
			generer_listes_couples(grille, liste);

			regen = 0;
			nb_nouv_ch--;   //une g�n�ration de chiffres de moins
			sprintf(mess, "Il vous reste %d regenerations de chiffres", nb_nouv_ch);
			message(mess);	//aviser le joueur du nb. de reg�n�rations restantes
		}

		/* R�-afficher le score, les chiffres dispos et la grille de jeu */
		afficher_infos_jeu(nbr_chiffres, score);
		afficher_grille(grille, last_lig);
      
	/* Tant que le joueur ne veut pas quitter, qu'il reste des chiffres et des coups � jouer */
	} while (!quitter && nb_chiffres_restants(nbr_chiffres) && nb_couples(liste));

	/* Si le joueur n'a pas abandonn� le jeu.. */
	if (!quitter) {
		sprintf(mess, "Jeu termine! Total: %d points\n\t\t\t\t\t", score);   
		message(mess);   //afficher le score final
	}

	system("pause");
	return 0;
}