/*
Module: utilitaires.h   (*** MODULE DONN� AUX �L�VES ***)

Description: Module de fonctions utilitaires : 
             Offre une fonction de g�n�ration d'un r�el al�atoire entre un "min" et "max".
             Offre une fonction de g�n�ration d'un entier al�atoire entre un "min" et "max".
             
Auteur: Anis Boubaker et Eric Th�
*/

#ifndef UTILITAIRES_H
#define UTILITAIRES_H
#include <time.h>
#include <stdlib.h>

/*
Fonction: init_rand
Description: Initialise le g�n�rateur al�atoire "rand()" selon l'heure de l'ordi.
             Cette fonction doit �tre appell�e une fois avant d'uiliser "rand()".

Param�tres: aucun
Retour: aucun
*/
void init_rand(void);



/*
Fonction: reel_aleatoire
Description: Fonction qui retourne un r�el al�atoire entre min et max.

Param�tres:
        min (r�el): borne minimale de l'intervale du nombre al�atoire
        max (r�el): borne maximale de l'intervale du nombre al�atoire
Retour: (r�el) nombre al�atoire entre min et max.
Sp�cifications: on pr�sume que la fonction "init_rand()" � �t� appell�e une fois
                avant d'utiliser cette fonction.
*/
double reel_aleatoire(double min, double max);


/*
Fonction: entier_aleatoire
Description: Fonction qui retourne un entier al�atoire entre min et max.

Param�tres:
        min (entier): borne minimale de l'intervale du nombre al�atoire
        max (entier): borne maximale de l'intervale du nombre al�atoire
Retour: (entier) nombre al�atoire entre min et max.
Sp�cifications: on pr�sume que la fonction "init_rand()" � �t� appell�e une fois
                avant d'utiliser cette fonction.
*/
int entier_aleatoire(int min, int max) {
}

#endif   //#if !UTILITAIRES_H