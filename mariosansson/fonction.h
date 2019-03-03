#include <stdbool.h>
#include "GfxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpLib.h"
#include "OutilsLib.h"
#include <math.h>  


void element(float x, float y, DonneesImageRGB *image );

void afficherlvl1 (void);

void afficherlvl2(void);

void quadrillagecarte1(int carte[23][41]);

void quadrillagecarte2(int carte[23][41]);

int *BVR2ARVBis(int largeur, int hauteur, const unsigned char *donnees);

int detectionbas(float x, float y, int carte[23][41], int colba);

int detectionhaut(float x, float y, int carte[23][41], int colha);

int detectiondroite(float x,float y, int carte[23][41],int coldr);

int detectiongauche(float x,float y, int carte[23][41],int colga);

void deplacementmariopetitdroite(float x, float y, int a,int easter);

void deplacementmariopetitgauche(float x, float y, int a,int easter);

void sautmariopetit(float x,float y, int deplacement,int easter);

void deplacementmariogranddroite(float x, float y, int a, int easter);

void deplacementmariograndgauche(float x, float y, int a,int easter);

void sautmariogrand(float x,float y, int deplacement,int easter);

void grandmariobaisser(float x,float y,int deplacement,int easter);

void plateforme(float x,float y, int carte[23][41]);

int pics(float x,float y, int carte[23][41]);

float blocagemario(float y);

int morttomber(float y);

int bot(int couleur,int BorneA,int BorneB,int x,int y,int b, float xMario, float yMario,int etatMario, int toucher);

int colision(float xMario,float yMario,float x,float y,int etatMario);

int champignon(int BorneA,int BorneB,int x,int y,int b, float xMario, float yMario, int carte[23][41],int etatMario,int champiSorti);

void ecranfin(int mort);

void affichemort(int mort);

int spawnmonstre(int BorneA,int BorneB,int x,int y,int b, float xMario, float yMario, int carte[23][41],int etatMario);
