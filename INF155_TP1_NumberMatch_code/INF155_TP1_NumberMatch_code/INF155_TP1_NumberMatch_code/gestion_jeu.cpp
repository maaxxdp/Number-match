// gestion_jeu.cpp                *** SEM. 3: saisie_case(), valider_coup() et jouer_coup()
// Auteur: Eric Th�, d�c. 2025    *** SEM. 4: afficher_choix_alea()
//                                
// Module qui g�re les saisies, commandes et les points du jeu.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "affichages.h"     //ne doit PAS �tre inclus nullepart ailleurs dans le projet!
#include "gestion_jeu.h"

/*********************** LES MACROS PRIV�ES ************************/
//Trois macros de conversions: entier � caract�re et caract�re � entier
#define CHIFFRE_A_VAL(ch)  ((ch) - '0')         //conversion '0' (char) -> 0 (int)
#define LETTRE_A_COL(let)  ((let) - 'A' + 1)    //conversion 'A' (char) -> 1 (int)
#define COL_A_LETTRE(col)  ((col) - 1 + 'A')    //conversion  1  (int)  -> 'A' (char)

//MACRO pour obtenir la valeur absolue d'une diff�rence enti�re
#define ABS(diff)          ((diff) < 0 ? -(diff) : (diff))

/**************** D�FINITION DES FONCTIONS PRIV�ES *****************/

//Effectue la saisie ET validation d'une case valide OU d'un code-commande.
//PARAM.: l'indice de la derni�re ligne active et le num�ro de la saisie (eg. 1 ou 2)
//RETOUR: un num�ro de case valide (eg. 24) OU un des 3 codes-commandes (0, -1, -2)
static int saisie_case(int dern_lig, int no){
	
    char saisie[10];
    int ligne;
    int colonne;
    int position_finale = 0;

// Tant que la saisie n'est pas valide, on reste dans la boucle
    while (position_finale == 0){

       // Demander la saisie d'une case a l'utilisateur
        demander_saisie(no);
        scanf("%s", saisie);

       // Si la chaine est soit "XX", "??" ou "++", on retourne les codes qui leur sont associes.
        if (strcmp(saisie, "XX") == 0 || strcmp(saisie, "xx") == 0)
            return CODE_QUITTER;

        if (strcmp(saisie, "??") == 0)
            return CODE_AIDE;

        if (strcmp(saisie, "++") == 0)
            return CODE_CHIFFRES;

       // Verifier que la longueur de la saisie est soit de 2 caracteres soit 3 caracteres.
        if (strlen(saisie) != 2 && strlen(saisie) != 3) {       	
            mess_erreur("Saisie invalide");
        }
        else {	
            colonne = toupper(saisie[0]); // S'assurer que la lettre saisie est en majuscule
           
           // Verifier que la colonne entree est entre "A" et "I"
            if (colonne < 'A' || colonne > 'I') {        
                mess_erreur("Colonne invalide");
            }
            else {
               // Verifier que le deuxieme caractere saisi est un chiffre
                if (saisie[1] < '0' || saisie[1] > '9') {
                    mess_erreur("Ligne invalide");
                }
                else {                	
                    ligne = CHIFFRE_A_VAL(saisie[1]);
                    
	                 // Si on a 3 caracteres saisis
                    if (strlen(saisie) == 3) {
                    	
                    	// Verifier que le troisieme caractere saisi est un chiffre
                      if (saisie[2] < '0' || saisie[2] > '9') {
                      	
                         mess_erreur("Ligne invalide");
                      } 
	                   else {
                            // Construit le nombre complet : 1 et 2 -> 12
                            ligne = ligne * 10 + CHIFFRE_A_VAL(saisie[2]);
                            ligne = ligne - 1; // ligne - 1 car l'index commence a 0 et non 1
		
                           // Verifier que la ligne existe dans la grille
                            if (ligne < 0 || ligne > dern_lig) {
                                mess_erreur("Numero de ligne invalide");
                            } 
		                      else {
                                // Trouve la position finale: ligne + colonne
                                position_finale = ligne * 10 + LETTRE_A_COL(colonne);
                            }
                        }
                    }
                    // Cas d'une ligne a un seul chiffre
                    else {
                         ligne = ligne - 1;
                       
		               // Verifier que la ligne existe dans la grille
                        if (ligne < 0 || ligne > dern_lig) {
                            mess_erreur("Numero de ligne invalide");
                        }
                        else {
                            // Trouver la position finale: ligne + colonne                        	
                            position_finale = ligne * 10 + LETTRE_A_COL(colonne);
                        }
                    }
                }
            }
        }
    }
    return position_finale;
}

/******************** D�FINITION DES FONCTIONS PUBLIQUES *********************/
/*****************************************************************************/
//Effectue la saisie du coup valide (deux cases) OU d'un code-commande (dans "caseA").
int valider_coup(t_liste_couples liste, int dern_lig, int* caseA, int* caseB) {
   
    int valide = 0;
    int nb;

    do {
        // Demander la saisie de la premiere case.
        *caseA = saisie_case(dern_lig, 1);

        // Si un code recu, quitter la fonction.
        if (*caseA == CODE_QUITTER || *caseA == CODE_AIDE || *caseA == CODE_CHIFFRES)
            return 0;

        // Demander la saisie de la deuxieme case
        *caseB = saisie_case(dern_lig, 2);

        // Verifier si couple existe dans la liste
        valide = 0;
        nb = liste[LIG_INFOS][COL_NBELEM];

        for (int i = 1; i <= nb; i++) {
            if (liste[i][0] == *caseA && liste[i][1] == *caseB) {           	
                valide = 1;
                break;
            }
        }
        
        // Message d'erreur si le couple n'est pas dans la liste
        if (!valide) {        	
            mess_erreur("Coup non valide !");
        }
    } while (!valide);
    
    return 1;   //le coup (caseA, caseB) est valide
}

/*****************************************************************************/
//Permet de jouer un coup, la fonction va effacer les deux cases re�ues dans la grille.  
//Si une (ou deux) lignes sont vid�es, on va les retirer et l'indice de la derni�re ligne avec 
//au moins un chiffre sera d�cr�ment�.
int jouer_coup(t_grille_nos grille, int caseA, int caseB, t_tab_chiffres nbr_chiffres,
               int * dern_lig) {
   
    int points = 0;
    int pts_lignes = 0;
    int ch, elimine;

    // Vérifier si les deux cases sont collees pour +1pts ou separee pour +4pts
    if (abs(caseA - caseB) == 1) {
        points += PTS_COUPLE_VOISIN;
        mess_points(PTS_COUPLE_VOISIN);
    } else {
        points += PTS_COUPLE_SEPARE;
        mess_points(PTS_COUPLE_SEPARE);
    }

    // Retirer le chiffre de la case A dans la liste des chiffres disponibles
        ch = get_chiffre_case(grille, caseA);
        elimine = retirer_chiffre(ch, nbr_chiffres);     
        if (elimine != 0) {
            mess_points(1);
        }        
        effacer_chiffre(grille, caseA);

    // Retirer le chiffre de la case B dans la liste des chiffres disponibles
        ch = get_chiffre_case(grille, caseB);
        elimine = retirer_chiffre(ch, nbr_chiffres);       
        if (elimine != 0) {
         int a;
        }      
        effacer_chiffre(grille, caseB);
    
    // Arranger les cases A et B en ordre decroissant
    if (caseA < caseB) {    	
        int tmp = caseA;
        caseA = caseB;
        caseB = tmp;        
    }

    // Verifier si la ligne de la case A est vide   
    int ligA = caseA / 10;
   
    if (grille[ligA][0] == 0) {    	
        retirer_ligne(grille, ligA);
        pts_lignes += PTS_LIGNE_RETIREE;
        (*dern_lig)--;       
    }

    // Verifier si la ligne de la case B est vide et différente de la case A 
    int ligB = caseB / 10;
   
    if (ligB != ligA && grille[ligB][0] == 0) {
        retirer_ligne(grille, ligB);
        pts_lignes += PTS_LIGNE_RETIREE;
        (*dern_lig)--;   
    }

    // Si des lignes ont ete retiree, on affiche un message.
    if (pts_lignes > 0) {
        mess_points(PTS_LIGNE_RETIREE);
    }
    return points + pts_lignes; //on retourne les points obtenus
}

/*****************************************************************************/
//Affiche les 2 cases d'un coup valide choisi al�atoirement par le programme (commande "??")
void afficher_indice(const t_grille_nos grille, int caseA, int caseB) {
    int chA = get_chiffre_case(grille, caseA);     //le chiffre de la "caseA"
    int chB = get_chiffre_case(grille, caseB);     //le chiffre de la "caseB"
    int ligA = caseA / 10, colA = caseA % 10;      //la ligne et colonne de la "caseA" 
    int ligB = caseB / 10, colB = caseB % 10;      //la ligne et colonne de la "caseB" 
    char mess[40];                          //tampon-string pour le message � afficher

    /* Affichage en texte du couple en dessous de la ligne des saisies */
    sprintf(mess, "Jouez les cases %c%d et %c%d",
                  COL_A_LETTRE(colA), ligA + 1,    //avec conversion 24 --> "D3"
                  COL_A_LETTRE(colB), ligB + 1);
    message(mess);

    /* Mettre ces deux chiffres en �vidence (en bleu) pour 5 secondes � l'�cran */
    afficher_couple(colA, ligA, chA, colB, ligB, chB);
}
