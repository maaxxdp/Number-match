/*
Titre: utilitaires.cpp    (*** MODULE DONN� AUX �L�VES ***)
Description: Fonctions du module d'utilitaires, comprenant des fonctions diverses 
             de g�n�ration de nombre al�atoires.
Auteur: Anis Boubaker et Eric Th�
*/

/************ COMMANDES DE PR�PROCESSEUR **************/
#include <stdlib.h>
#include <time.h>
#include "utilitaires.h"

/********* IMPL�MENTATIONS DES FONCTIONS **************/

/*---------------------- init_rand() -------------------------------*/
//initialise le g�n�rateur al�atoire "rand()" selon l'heure de l'ordi.
void init_rand(void){
	srand(time(NULL));
}

/*--------------------- reel_aleatoire() ------------------------------*/
/* Fonction al�atoire qui renvoie un r�el inclu entre [min..max]. */
double reel_aleatoire(double min, double max)
{
	/*	Posons que x vaut rand() / (RAND_MAX + 0.0000001), alors
		x                              E  [0, 1[
		x * (max - min)                E  [0, max - min
		min + x * (max - min)          E  [min, max[
	*/
	return min + (double)rand() / (RAND_MAX * (max - min));
}

/*--------------------- entier_aleatoire() ------------------------------*/
/* Fonction al�atoire qui renvoie un entier inclu entre [min..max]. */
int entier_aleatoire(int min, int max) {
	return rand() % max + min;
}
