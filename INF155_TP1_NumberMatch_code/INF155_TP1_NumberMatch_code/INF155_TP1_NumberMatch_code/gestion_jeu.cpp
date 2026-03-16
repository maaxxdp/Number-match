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
static int saisie_case(int dern_lig, int no) {
   
    return 0;       //on retourne le num�ro de case ainsi form�
}

/******************** D�FINITION DES FONCTIONS PUBLIQUES *********************/
/*****************************************************************************/
//Effectue la saisie du coup valide (deux cases) OU d'un code-commande (dans "caseA").
int valider_coup(t_liste_couples liste, int dern_lig, int* caseA, int* caseB) {
   
    return 1;   //le coup (caseA, caseB) est valide
}

/*****************************************************************************/
//Permet de jouer un coup, la fonction va effacer les deux cases re�ues dans la grille.  
//Si une (ou deux) lignes sont vid�es, on va les retirer et l'indice de la derni�re ligne avec 
//au moins un chiffre sera d�cr�ment�.
int jouer_coup(t_grille_nos grille, int caseA, int caseB, t_tab_chiffres nbr_chiffres,
               int * dern_lig) {
   

    return 0;     //on retourne les points obtenus
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
