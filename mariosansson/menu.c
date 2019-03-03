#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpLib.h"
#include "OutilsLib.h"
#include "GfxLib.h"
#include "fonction.h"
#include "menu.h"

void Panneau (void)
{
	static DonneesImageRGB *panneau = NULL;
	panneau = lisBMPRGB("Panneau.bmp");
	element(0,0,panneau);
	libereDonneesImageRGB(&panneau);
}

void AnimationPanneau(int a)
{
	if (a==1)  // Cas où on appuie sur haut
	{
		static DonneesImageRGB *haut = NULL;
		haut = lisBMPRGB("Panneauhaut.bmp");
		element(0,0,haut);
		libereDonneesImageRGB(&haut);
	}
	if (a==2)   // Cas où on appuie sur bas
	{
		static DonneesImageRGB *bas = NULL;
		bas = lisBMPRGB("Panneaubas.bmp");
		element(0,0,bas);
		libereDonneesImageRGB(&bas);				
	}
	if (a==3)   // Cas où on appuie sur gauche
	{
		static DonneesImageRGB *gauche = NULL;
		gauche = lisBMPRGB("Panneaugauche.bmp");
		element(0,0,gauche);
		libereDonneesImageRGB(&gauche);				
	}
	if (a==4)   // Cas où on appuie sur droite
	{
		static DonneesImageRGB *droite = NULL;
		droite = lisBMPRGB("Panneaudroite.bmp");
		element(0,0,droite);
		libereDonneesImageRGB(&droite);				
	}
	if (a==5)   // Cas où on appuie sur la touche cachée "!"
	{
		static DonneesImageRGB *easter = NULL;
		easter = lisBMPRGB("Panneaueaster.bmp");
		element(0,0,easter);
		libereDonneesImageRGB(&easter);
	}
}

void menu (void)  // fleche à gauche
{
	static DonneesImageRGB *fleche = NULL;
	static DonneesImageRGB *menu = NULL;
	fleche = lisBMPRGB("fleche.bmp");                 // Fleche avec fond blanc
	menu = lisBMPRGB("menu.bmp"); 
	element(0,0,menu);
	int *a = BVR2ARVBis(80, 69, fleche->donneesRGB);  // Retire fond blanc fleche
	ecrisImageARVB(123,203,80,69, a);                 // Création de la fleche sans fond blanc
	libereDonneesImageRGB(&menu);                     
	libereDonneesImageRGB(&fleche);
}

void menu2 (void)  // fleche à droite
{
	static DonneesImageRGB *fleche = NULL;
	static DonneesImageRGB *menu = NULL;
	fleche = lisBMPRGB("fleche.bmp");                 // Fleche avec fond blanc
	menu = lisBMPRGB("menu.bmp"); 
	element(0,0,menu);
	int *a = BVR2ARVBis(80, 69, fleche->donneesRGB);  // Retire fond blanc fleche
	ecrisImageARVB(559,202,80,69, a);                 // Création de la fleche sans fond blanc
	libereDonneesImageRGB(&menu);                     
	libereDonneesImageRGB(&fleche);
}

void changementmenu(int me) //Passage du menu1 au menu2
{
	if (me==0)
		{
			menu();
		}
	if (me==1)
		{
			menu2();
		}
}

int entrer(int me)  // Récupération de la commande pour entrer dans le jeu ou le panneau
{
int commande = 0;
	if (me==1)
	{
		commande = 2;
	}
	if (me==0)
	{
		commande = 1;
	}
  return commande;
}
