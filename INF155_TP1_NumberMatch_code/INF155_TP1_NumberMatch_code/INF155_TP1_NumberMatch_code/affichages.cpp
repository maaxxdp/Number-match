// affichages.cpp			     *** SEM. 2: afficher_infos_jeu() et afficher_grille()
// Auteur: Eric Th�, d�c. 2025   *** SEM. 4: afficher_couple() et afficher_instructions()
// 
// Module qui g�re toutes les fonctions d'affichages du programme.
// IMPORTANT: ce module est le SEUL � utiliser la librairie "WinConsole" et les "printf()" !!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "WinConsole.h"     //NOTE: ne doit PAS �tre inclus nullepart ailleurs dans le projet!
#include "affichages.h"

#define CH_MAX  9           //le chiffre maximal � afficher

/********** � FAIRE: les 4 premi�res fonctions (jusqu'� la lig. 100) *********/
/*****************************************************************************/
//Affichage des instructions de d�part
void afficher_instructions() {
    gotoxy(COL_GRILLE + 8, 1);       //on se positionne � l'�cran avant chaque "printf()"
    printf("NUMBER MATCH");
    gotoxy(18, 3);
    printf("Elimier 2 cases dans la grille contenant 2 chiffres identiques");
    gotoxy(18, 4);
    printf("     OU 2 chiffres qui donnent une somme de 10 (eg. 6 et 4).");
    gotoxy(18, 5);
    printf("Les chiffres doivent etre dans des cases voisines (dans les 8 directions, 1 pt)");
    gotoxy(18, 6);
    printf("     OU separees par des cases VIDES (dans une des 8 directions, 4 pts)");
    gotoxy(18, 7);
    printf("NOTE: la direction EST (vers la droite) peut continuer a la ligne suivante!");
    gotoxy(18, 8);
    printf("Si une ligne se vide suite au retrait de chiffres la ligne est effacee (10 pts)");
    gotoxy(18, 10);
    printf("Commandes speciales durant la saisie de la premiere case:");
    gotoxy(18, 11);
    printf("  ?? - obtenir une suggestion d'un couple possible a jouer dans la grille");
    gotoxy(18, 12);
    printf("  ++ - obtenir une nouvelles serie de chiffres aleatoires au bas de la grille");
    gotoxy(18, 13);
    printf("       NOTE: seulement 3 regenerations de chiffres sont possibles durant le jeu");
    gotoxy(18, 14);
    printf("  XX - quitter le jeu");
    gotoxy(18, 16);
    system("pause");      //pause-�cran avant d'effacer les instructions et d�marrer le jeu
}

/*****************************************************************************/
//Permet d'afficher la liste des chiffres dispo (sur la ligne 0) et du score (sur la ligne 1).
void afficher_infos_jeu(const t_tab_chiffres nbr_chiffres, int pts) {
    clrscr();       //effacer l'�cran

    /* afficher le score � date */
    gotoxy(COL_GRILLE + 8, LIG_POINTS);  printf("Score: %d", pts);

    /* affichage des chiffres dispos */
    gotoxy(COL_GRILLE, LIG_CHIFFRES);    printf("Chiffres: ");
    for (int i = 1; i <= CH_MAX; i++)
        printf("%c ", nbr_chiffres[i] ? ('0' + i) : ' ');  //vide si le chiffre est absent
}

/*****************************************************************************/
//Permet d'afficher la grille des chiffres
    void afficher_grille(const t_grille_nos grille, int dern_lig) {
        int lig = 0, col;   //la position actuelle

        /* les en-t�tes des colonnes */
        textcolor(YELLOW);
        gotoxy(COL_GRILLE + 4, LIG_GRILLE);
        for (col = 0; col < NB_COL - 1; col++)
            printf(" %c", 'A' + col);    //'A', 'B', 'C', ...etc.

        /* affichage de la grille tant que les lignes ont des chiffres */
        for (lig = 0; lig <= dern_lig; lig++) {
            textcolor(YELLOW);
            gotoxy(COL_GRILLE, LIG_GRILLE + lig + 1);
            printf(" %2d ", lig + 1);           //le no. de la ligne � la gauche des chiffres
            textcolor(WHITE);

            //afficher tous les chiffres de cette ligne (colonnes [1] � [9])
            for (col = 1; col < NB_COL; col++)
                if (grille[lig][col])
                    printf(" %d", grille[lig][col]);  //chaque case occuppe 2 ESPACES-�cran!
                else printf("  ");                     //ne pas afficher les cases vides (= 0)
        }
    }


/*****************************************************************************/
//Permet d'afficher la suggestion de deux chiffres � choisir en BLEU pendant 5 secondes.
void afficher_couple(int colA, int ligA, int chA, int colB, int ligB, int chB) {
    /* Mettre ces deux chiffres en �vidence (en bleu) pour 5 secondes � l'�cran */
    textcolor(LIGHTBLUE);

    /* Le d�calage-colonne doit �tre un multiple de 2 (car c'est 2 char par case) */
    gotoxy(COL_GRILLE + (colA * 2) + 3, LIG_GRILLE + ligA + 1);
    printf("%d", chA);
    gotoxy(COL_GRILLE + (colB * 2) + 3, LIG_GRILLE + ligB + 1);
    printf("%d", chB);

    delay(5000);        //= 5 secondes
}

/******************* LES FONCTIONS SUIVANTES SONT DONN�ES ********************/

/*****************************************************************************/
//Affiche le message de demande d'une saisie de case ou commande (sur la ligne 3).
void demander_saisie(int no_saisie) {
    gotoxy(COL_GRILLE, LIG_SAISIE);             //saisie sur la ligne 2 de l'�cran
    printf("Entrer la case %d (eg. A1): ", no_saisie);
    clreol();           //effacer reste de cette ligne
}

/*****************************************************************************/
//Les 3 fonctions suivantes servent � afficher diff�rents messages durant le jeu :
void message(const char* mess) {
    /* affiche un message d'information � la ligne 3 pendant 3 secondes */
    textcolor(WHITE);   //remise � la couleur BLANC
    gotoxy(COL_GRILLE, LIG_MESSAGES);
    printf("%s", mess);   
    clreol();           //effacer le reste de l'ancien message affich� sur cette ligne
    delay(2000);        //= 3 secondes
}

/*****************************************************************************/
void mess_erreur(const char* mess) {
    /* affiche un message d'erreur � la ligne 3 en ROUGE avec clignotements! */
    for (int i = 0; i < 5; i++) {   //faire clignoter 5 fois
        gotoxy(COL_GRILLE, LIG_MESSAGES);
        textcolor(LIGHTRED);
        printf("%s", mess);         //afficher
        delay(500);
        gotoxy(COL_GRILLE, LIG_MESSAGES);
        clreol();                   //effacer
        delay(200);
    }
    textcolor(WHITE);  //remise � la couleur BLANC
}

/*****************************************************************************/
void mess_points(int pts) {
    /* affiche les points obtenus � la ligne 1 en VERT avec clignotements! */
    for (int i = 0; i < 3; i++) {    //faire clignoter 3 fois
        gotoxy(COL_GRILLE + 20, LIG_POINTS);
        textcolor(LIGHTGREEN);
        printf("+%d points!!", pts); //afficher
        delay(300);
        gotoxy(COL_GRILLE + 20, LIG_POINTS);
        clreol();                    //effacer
        delay(100);
    }
    textcolor(WHITE);  //remise � la couleur BLANC
}
