#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpLib.h"
#include "OutilsLib.h"
#include "GfxLib.h"
#include <math.h>  


void element(float x,float y, DonneesImageRGB *image )
{
	float x1,y1;
	x1=x*32;
	y1=y*32;
	if (image != NULL)
				{
				ecrisImage(x1,y1,image->largeurImage,image->hauteurImage, image->donneesRGB);
				}
}


void quadrillagecarte1(int carte[23][41])
{
	FILE * matrice1=NULL;
	matrice1=fopen("matricecarte1.txt","r");
	if(matrice1 != NULL)
	{
		fseek(matrice1, 0, SEEK_SET);
		for(int i=0;i<23;i++)
		{
			for(int k=0;k<40;k++)
			{
				if(fscanf(matrice1, "%d", &carte[i][k]) == 0)
		        {
					printf("test KO \n");
				}
			}
		}
	}
	fclose(matrice1);
}


void afficherlvl1 (void)
{  	
		static DonneesImageRGB *fondniv1 = NULL; // L'image a afficher au centre de l'ecran
		static DonneesImageRGB *box = NULL; // 1er box
		static DonneesImageRGB *mur= NULL;
		static DonneesImageRGB *tubed = NULL;
		static DonneesImageRGB *tubeg = NULL;
		static DonneesImageRGB *sol = NULL;

		box = lisBMPRGB("bloc.bmp");
		mur = lisBMPRGB("mur.bmp");
		tubed = lisBMPRGB("tubedroite.bmp");
		tubeg = lisBMPRGB("tubegauche.bmp");
		fondniv1 = lisBMPRGB("fondniv1.bmp");
		sol = lisBMPRGB("sol1.bmp");
	
		element(0,0,fondniv1);
		element(9,4, box);
		element(8,4, mur);
		element(10,4, mur);
		element(15,9, mur);
		element(20,14, mur);
		element(0,2,tubed);
		element(39,2,tubeg);
		element(16,0, sol);
	
	
	
		libereDonneesImageRGB(&fondniv1); // libere la structure image
		libereDonneesImageRGB(&box);
		libereDonneesImageRGB(&mur);
		libereDonneesImageRGB(&tubed);
		libereDonneesImageRGB(&tubeg);
		libereDonneesImageRGB(&sol);
	}





int *BVR2ARVBis(int largeur, int hauteur, const unsigned char *donnees)
{
	const unsigned char *ptrDonnees;
	unsigned char *pixels = (unsigned char*)malloc(largeur*hauteur*sizeof(int));
	unsigned char *ptrPixel;
	int index;
	
	ptrPixel = pixels;
	ptrDonnees = donnees;
	for
		(index = largeur*hauteur; index != 0; --index) /* On parcourt tous les
														pixels de l'image */
	{	  
	  
		if (ptrDonnees[0]==255 && ptrDonnees[1]==255 && ptrDonnees[2]==255)
		{
			ptrPixel[0] = ptrDonnees[0];
			ptrPixel[1] = ptrDonnees[1];
			ptrPixel[2] = ptrDonnees[2];
			ptrPixel[3] = 0x0;
			ptrDonnees += 3; /* On passe a la premiere composante du pixel suivant */
			ptrPixel += 4; /* On passe au pixel suivant */
		}
		else
		{
			ptrPixel[0] = ptrDonnees[0];
			ptrPixel[1] = ptrDonnees[1];
			ptrPixel[2] = ptrDonnees[2];
			ptrPixel[3] = 0x0FF;
			ptrDonnees += 3; /* On passe a la premiere composante du pixel suivant */
			ptrPixel += 4; /* On passe au pixel suivant */
		}
	}
	return (int*)pixels;
}


int detectiondroite(float x,float y, int carte[23][41],int coldr)
{
	int xmario32,ymario32;
	ymario32=(int)(22-y/32); //a traiter
	xmario32=(int)(x/32+1);
	if (carte[ymario32][xmario32]==0 || carte[ymario32][xmario32]==6 || carte[ymario32][xmario32]==4)
	{	
		coldr=0;
	}
	if (carte[ymario32][xmario32]==1 || carte[ymario32][xmario32]==3 || carte[ymario32][xmario32]==5)
	{
		coldr=1;
	}
	if (carte[ymario32][xmario32]==2)
	{
		coldr=2;
	}
	if (carte[ymario32][xmario32]==7)
	{
		coldr=3;
	}
	return coldr;
}

int detectiongauche(float x,float y, int carte[23][41],int colga)
{
	int xmario32,ymario32;
	ymario32=(int)(22-y/32);
	xmario32=(int)(x/32-1); //a traiter
	if (carte[ymario32][xmario32]==0 || carte[ymario32][xmario32]==6 || carte[ymario32][xmario32]==4)
	{	
		colga=0;
	}
	if (carte[ymario32][xmario32]==1 || carte[ymario32][xmario32]==3 || carte[ymario32][xmario32]==5)
	{
		colga=1;
	}
	return colga;
}
	
int detectionbas(float x, float y, int carte[23][41], int colba)
{
	int xmario32,ymario32, y2mario32;
	ymario32= (int)(22-y/32+1);
	xmario32=(int)(x/32);
	y2mario32= (int)(22-y/32+2);
	if (carte[ymario32][xmario32]==0 || carte[ymario32][xmario32]==6 || carte[ymario32][xmario32]==4)
	{
		if (carte[y2mario32][xmario32]==0 || carte[y2mario32][xmario32]==6 || carte[y2mario32][xmario32]==4){
		colba=0;}
		if (carte[y2mario32][xmario32]==1 || carte[y2mario32][xmario32]==3 || carte[y2mario32][xmario32]==5 || carte[y2mario32][xmario32]==2){
		colba=2;}
	}
	if (carte[ymario32][xmario32]==1 || carte[ymario32][xmario32]==3 || carte[ymario32][xmario32]==5 || carte[ymario32][xmario32]==2)
	{
		colba=1;
	}
	return colba;
}

int detectionhaut(float x, float y, int carte[23][41], int colha)
{
	int xmario32,ymario32,y2mario32;
	xmario32=(int)(x/32);
	ymario32= (int)(22-y/32);
	y2mario32= (int)(22-y/32-1);
	
	if (carte[ymario32][xmario32]==0 || carte[ymario32][xmario32]==6 || carte[ymario32][xmario32]==4)
	{
		colha=0;
	}
	if (carte[ymario32][xmario32]==1 || carte[ymario32][xmario32]==5)
	{
		colha=1;
	}
	if (carte[ymario32][xmario32]==0 || carte[ymario32][xmario32]==6 || carte[ymario32][xmario32]==4)
	{
		if (carte[y2mario32][xmario32]==1 || carte[y2mario32][xmario32]==5 || (carte[y2mario32][xmario32]==3))
		{
			colha=2;
		}
	}
	if (carte[ymario32][xmario32]==3)
	{
		colha=3;
	}
	return colha;
}

void deplacementmariopetitdroite(float x, float y, int a, int easter)
{
	if (easter==0)
	{
		static DonneesImageRGB *mariostaticdr = NULL; 
		static DonneesImageRGB *mariorundr = NULL;
		mariostaticdr = lisBMPRGB("mariostaticdr.bmp");
		mariorundr = lisBMPRGB("mariorundr.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32, 32, mariorundr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&mariorundr);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, mariostaticdr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&mariostaticdr);
		}
		libereDonneesImageRGB(&mariorundr);
		libereDonneesImageRGB(&mariostaticdr);
		
	}
	else
	{
		static DonneesImageRGB *marionoirstaticdr = NULL; 
		static DonneesImageRGB *marionoirrundr = NULL;
		marionoirstaticdr = lisBMPRGB("marionoirstaticdr.bmp");
		marionoirrundr = lisBMPRGB("marionoirrundr.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32, 32, marionoirrundr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&marionoirrundr);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, marionoirstaticdr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&marionoirstaticdr);
		}
		libereDonneesImageRGB(&marionoirrundr);
		libereDonneesImageRGB(&marionoirstaticdr);
	}		
}

void deplacementmariopetitgauche(float x, float y, int a, int easter)
{
	if (easter==0)
	{	
		static DonneesImageRGB *mariostaticga = NULL; 
		static DonneesImageRGB *mariorunga = NULL;
		mariostaticga = lisBMPRGB("mariostaticga.bmp");
		mariorunga = lisBMPRGB("mariorunga.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32, 32, mariorunga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&mariorunga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, mariostaticga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&mariostaticga);
		}	
	}
	if (easter==1)
	{	
		static DonneesImageRGB *marionoirstaticga = NULL; 
		static DonneesImageRGB *marionoirrunga = NULL;
		marionoirstaticga = lisBMPRGB("marionoirstaticga.bmp");
		marionoirrunga = lisBMPRGB("marionoirrunga.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32, 32, marionoirrunga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&marionoirrunga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, marionoirstaticga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&marionoirstaticga);
		}	
	}			
}
void sautmariopetit(float x,float y,int deplacement,int easter)
{
	if (easter==0)
	{
		static DonneesImageRGB *mariojumpdr = NULL; 
		static DonneesImageRGB *mariojumpga = NULL;
		mariojumpdr = lisBMPRGB("mariojumpdr.bmp");
		mariojumpga = lisBMPRGB("mariojumpga.bmp");
		
		if (deplacement!=1)
		{
			int *pixels2 = BVR2ARVBis(32, 32, mariojumpga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&mariojumpga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, mariojumpdr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&mariojumpdr);
		}
	}
	if (easter==1)
	{
		static DonneesImageRGB *marionoirjumpdr = NULL; 
		static DonneesImageRGB *marionoirjumpga = NULL;
		marionoirjumpdr = lisBMPRGB("marionoirjumpdr.bmp");
		marionoirjumpga = lisBMPRGB("marionoirjumpga.bmp");
		
		if (deplacement!=1)
		{
			int *pixels2 = BVR2ARVBis(32, 32, marionoirjumpga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&marionoirjumpga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, marionoirjumpdr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&marionoirjumpdr);
		}
	}			
}
void deplacementmariogranddroite(float x, float y, int a,int easter)
{
	if (easter==0)
	{
		static DonneesImageRGB *mariograndstaticdr = NULL; 
		static DonneesImageRGB *mariogranrundr = NULL;
		mariograndstaticdr = lisBMPRGB("mariograndstaticdr.bmp");
		mariogranrundr = lisBMPRGB("mariogranrundr.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32, 64, mariogranrundr->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels2);
			libereDonneesImageRGB(&mariogranrundr);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 64, mariograndstaticdr->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels);	
			libereDonneesImageRGB(&mariograndstaticdr);
		}		
	}
	if (easter==1)
	{
		static DonneesImageRGB *marionoirgrandstaticdr = NULL; 
		static DonneesImageRGB *marionoirgranrundr = NULL;
		marionoirgrandstaticdr = lisBMPRGB("marionoirgrandstaticdr.bmp");
		marionoirgranrundr = lisBMPRGB("marionoirgranrundr.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32, 64, marionoirgranrundr->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels2);
			libereDonneesImageRGB(&marionoirgranrundr);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 64, marionoirgrandstaticdr->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels);	
			libereDonneesImageRGB(&marionoirgrandstaticdr);
		}		
	}		
}

void deplacementmariograndgauche(float x, float y, int a, int easter)
{
	if (easter==0)
	{
		static DonneesImageRGB *mariograndstaticga = NULL; 
		static DonneesImageRGB *mariogranrunga = NULL;
		mariograndstaticga = lisBMPRGB("mariograndstaticga.bmp");
		mariogranrunga = lisBMPRGB("mariogranrunga.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32,64, mariogranrunga->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels2);
			libereDonneesImageRGB(&mariogranrunga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 64, mariograndstaticga->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels);	
			libereDonneesImageRGB(&mariograndstaticga);
		}	
	}
	if (easter==1)
	{
		static DonneesImageRGB *marionoirgrandstaticga = NULL; 
		static DonneesImageRGB *marionoirgranrunga = NULL;
		marionoirgrandstaticga = lisBMPRGB("marionoirgrandstaticga.bmp");
		marionoirgranrunga = lisBMPRGB("marionoirgranrunga.bmp");

		if (a%2!=0)
		{
			int *pixels2 = BVR2ARVBis(32,64, marionoirgranrunga->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels2);
			libereDonneesImageRGB(&marionoirgranrunga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 64, marionoirgrandstaticga->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels);	
			libereDonneesImageRGB(&marionoirgrandstaticga);
		}	
	}			
}
void sautmariogrand(float x,float y,int deplacement,int easter)
{
	if (easter==0)
	{
		static DonneesImageRGB *mariograndjumpdr = NULL; 
		static DonneesImageRGB *mariograndjumpga = NULL;
		mariograndjumpdr = lisBMPRGB("mariograndjumpdr.bmp");
		mariograndjumpga = lisBMPRGB("mariograndjumpga.bmp");
		
		if (deplacement!=1)
		{
			int *pixels2 = BVR2ARVBis(32, 64, mariograndjumpga->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels2);
			libereDonneesImageRGB(&mariograndjumpga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 64, mariograndjumpdr->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels);	
			libereDonneesImageRGB(&mariograndjumpdr);
		}	
	}
	if (easter==1)
	{
		static DonneesImageRGB *marionoirgrandjumpdr = NULL; 
		static DonneesImageRGB *marionoirgrandjumpga = NULL;
		marionoirgrandjumpdr = lisBMPRGB("marionoirgrandjumpdr.bmp");
		marionoirgrandjumpga = lisBMPRGB("marionoirgrandjumpga.bmp");
		
		if (deplacement!=1)
		{
			int *pixels2 = BVR2ARVBis(32, 64, marionoirgrandjumpga->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels2);
			libereDonneesImageRGB(&marionoirgrandjumpga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 64, marionoirgrandjumpdr->donneesRGB);
			ecrisImageARVB(x,y,32,64, pixels);	
			libereDonneesImageRGB(&marionoirgrandjumpdr);
		}	
	}		
}

void grandmariobaisser(float x,float y,int deplacement,int easter)
{
	if (easter==0)
	{
		static DonneesImageRGB *mariograndaccrdr = NULL; //// voir si le static est utile
		static DonneesImageRGB *mariograndaccrga = NULL;
		mariograndaccrdr = lisBMPRGB("mariograndaccrdr.bmp");
		mariograndaccrga = lisBMPRGB("mariograndaccrga.bmp");
		
		if (deplacement!=1)
		{
			int *pixels2 = BVR2ARVBis(32, 32, mariograndaccrga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&mariograndaccrga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, mariograndaccrdr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&mariograndaccrdr);
		}
	}
	if (easter==1)
	{
		static DonneesImageRGB *marionoirgrandaccrdr = NULL; //// voir si le static est utile
		static DonneesImageRGB *marionoirgrandaccrga = NULL;
		marionoirgrandaccrdr = lisBMPRGB("marionoirgrandaccrdr.bmp");
		marionoirgrandaccrga = lisBMPRGB("marionoirgrandaccrga.bmp");
		
		if (deplacement!=1)
		{
			int *pixels2 = BVR2ARVBis(32, 32, marionoirgrandaccrga->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels2);
			libereDonneesImageRGB(&marionoirgrandaccrga);
		}
		else
		{
			int *pixels = BVR2ARVBis(32, 32, marionoirgrandaccrdr->donneesRGB);
			ecrisImageARVB(x,y,32,32, pixels);	
			libereDonneesImageRGB(&marionoirgrandaccrdr);
		}
	}		
}

int colision(float xMario,float yMario,float x,float y, int etatMario)
{
	int colision=0;
	if (etatMario<9)//mario petit
	{
		//(xMario+32>=x && xMario<=x && yMario+32>=y && yMario<=y+32 )//detection colision droite et haut
		//(x+32>=xMario && x<=xMario && y<=yMario+32 && y>=yMario)//detection colision grauche et bas
		if((xMario+32>=x && xMario<=x && yMario+32>=y && yMario<=y+32 ) || (x+32>=xMario && x<=xMario && y<=yMario+32 && y>=yMario))
			colision= 1;
		else
			colision=0;
	} 

	if (etatMario>=9)//mario grand
	{
		if((xMario+32>=x && xMario<=x && yMario+32>=y && yMario<=y+32 ) || (x+32>=xMario && x<=xMario && y<=yMario+32 && y>=yMario))
			colision= 1;
		else
			colision=0;
	} 
	return colision;
}


int bot(int couleur,int BorneA,int BorneB,int x,int y,int b, float xMario, float yMario,int etatMario,int toucher) //si couleur=1 alors rouge, vert si couleur=2 // si toucher=1 alors carapace
{
	static int i=0;
	static int sens=1;
	int detection=0;
	
	if (toucher==0)
	{	
		if (i<BorneB && i>BorneA && sens==1)
			i=i+1;
		if (i<BorneB && i>BorneA && sens==-1)
			i=i-1;
		if (i==BorneB)
		{
			i=i-1;
			sens=-1;
		}
		if (i==BorneA)
		{
			i=i+1;
			sens=1;
		}
	
		if(couleur==1)//tortue rouge
		{
			if (sens==1)
			{
				static DonneesImageRGB *TRMD = NULL; 
				static DonneesImageRGB *TRD = NULL;
				TRMD = lisBMPRGB("TRMD.bmp");
				TRD = lisBMPRGB("TRD.bmp");

				if (b%2!=0)
				{
					int *pixels2 = BVR2ARVBis(32,32, TRD->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels2);
					libereDonneesImageRGB(&TRD);
				}
				else
				{
					int *pixels = BVR2ARVBis(32,32, TRMD->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels);	
					libereDonneesImageRGB(&TRMD);
				}
			}
			else
			{
				static DonneesImageRGB *TRMG = NULL; 
				static DonneesImageRGB *TRG = NULL;
				TRMG = lisBMPRGB("TRMG.bmp");
				TRG = lisBMPRGB("TRG.bmp");

				if (b%2!=0)
				{
					int *pixels2 = BVR2ARVBis(32,32, TRG->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels2);
					libereDonneesImageRGB(&TRG);
				}
				else
				{
					int *pixels = BVR2ARVBis(32,32, TRMG->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels);	
					libereDonneesImageRGB(&TRMG);
				}
			}
		}
		if(couleur==2) // tortue verte
		{
			if (sens==1)
			{
				static DonneesImageRGB *TVMD = NULL; 
				static DonneesImageRGB *TVD = NULL;
				TVMD = lisBMPRGB("TVMD.bmp");
				TVD = lisBMPRGB("TVD.bmp");

				if (b%2!=0)
				{
					int *pixels2 = BVR2ARVBis(32,32, TVD->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels2);
					libereDonneesImageRGB(&TVD);
				}
				else
				{
					int *pixels = BVR2ARVBis(32,32, TVMD->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels);	
					libereDonneesImageRGB(&TVMD);
				}
			}
			else
			{
				static DonneesImageRGB *TVMG = NULL; 
				static DonneesImageRGB *TVG = NULL;
				TVMG = lisBMPRGB("TVMG.bmp");
				TVG = lisBMPRGB("TVG.bmp");

				if (b%2!=0)
				{
					int *pixels2 = BVR2ARVBis(32,32, TVG->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels2);
					libereDonneesImageRGB(&TVG);
				}
				else
				{
					int *pixels = BVR2ARVBis(32,32, TVMG->donneesRGB);
					ecrisImageARVB(x+i,y,32,32, pixels);	
					libereDonneesImageRGB(&TVMG);
				}
			}
		}
		detection=colision(xMario,yMario,x+i,y,etatMario);
		return detection;
	}
	else
	{
		printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		return detection;
	}
}	

void plateforme(float x,float y, int carte[23][41])
{
	int xmario32, ymario32;
	ymario32= (int)(22-y/32);
	xmario32=(int)(x/32);
	if (carte[ymario32][xmario32]==6)
	{
		static DonneesImageRGB *sol2 = NULL;
		sol2 = lisBMPRGB("sol2.bmp");
		element(16,0, sol2);
		libereDonneesImageRGB(&sol2);
	}
}

int pics(float x,float y, int carte[23][41])
{
	int xmario32, ymario32;
	ymario32= (int)(22-y/32);
	xmario32=(int)(x/32);
	if (carte[ymario32][xmario32]==4)
	{
		static DonneesImageRGB *pics = NULL;
		pics = lisBMPRGB("pics.bmp");
		int*pixel=BVR2ARVBis(32, 32, pics->donneesRGB);
		ecrisImageARVB(xmario32*32,736-(ymario32+1)*32,32,32,pixel);
		libereDonneesImageRGB(&pics);
		return 1;
	}
	return 0;
}

float blocagemario(float y)  //pour empecher que mario sort du cadre en y
{
	if (y<0){
		y=0;}
	return y;
}		

int morttomber(float y) //incremente variable mort + return valeur qui remet a mario a son origine si =1
{
	if (y==0){
		return 1;
		}
	else{return 0;}
}

int champignon(int BorneA,int BorneB,int x,int y,int b, float xMario, float yMario, int carte[23][41],int etatMario,int champiSorti)
{
	static int i=0;
	static int sens=1;
	int detection=0;
	static int A=0;	
	static int colba;
	colba=detectionbas(x+i,y-A,carte,colba);  //detection collision en dessous mario si collision colba=1
	if (champiSorti == 0) // reinitialisation des compteurs
	 {
	 	i=0;
	 	A=0;
	 	champiSorti=1;
	 	detection=champignon(-260,440,288,160,b,xMario,yMario,carte,etatMario,champiSorti);
	 	
	 }
	if ((colba==0 && y-A>=65) || (colba==2 && y-A>=65))//pas de colision avec le sol
	{	
		A=A+8;
	}
	if (colba==1 || y-A<65) //si colision avec le sol
	{
		if (i<BorneB && i>BorneA && sens==1)
			i=i+5;
		if (i<BorneB && i>BorneA && sens==-1)
			i=i-5;
		if (i==BorneB)
		{
			i=i-5;
			sens=-1;
		}
		if (i==BorneA)
		{
			i=i+5;
			sens=1;
		}
	}
	static DonneesImageRGB *SpriteChampignon = NULL; 
	SpriteChampignon = lisBMPRGB("SpriteChampignon.bmp");
	int *pixels2 = BVR2ARVBis(32,32, SpriteChampignon->donneesRGB);
	ecrisImageARVB(x+i,y-A,32,32, pixels2);
		
	detection=colision(xMario,yMario,x+i,y-A,etatMario);
	libereDonneesImageRGB(&SpriteChampignon);
	return detection;
}

void ecranfin(int mort)
{
	static DonneesImageRGB *ecranfin = NULL;
	ecranfin = lisBMPRGB("ecranfin.bmp");
	element(0,0,ecranfin);
	libereDonneesImageRGB(&ecranfin);
	char chainemort[1000];
	sprintf(chainemort,"%d",mort);
	afficheChaine(chainemort,100,1100,50);
}

void affichemort(int mort) //parametre compteur et niveau a rajouter et fin du jeu
{
	static DonneesImageRGB *mariotriste1 = NULL; 
	mariotriste1 = lisBMPRGB("mariotriste1.bmp");
	int *pixels = BVR2ARVBis(70,70, mariotriste1->donneesRGB);
	ecrisImageARVB(1020,635,70,70, pixels);
	libereDonneesImageRGB(&mariotriste1);	
	char chainemort[1000];
	sprintf(chainemort,"MORTS: %d",mort);
   	afficheChaine(chainemort,30,1100,660);

	
}

void quadrillagecarte2(int carte[23][41])
{
	FILE * matrice2=NULL;
	matrice2=fopen("matricecarte2.txt","r");
	if(matrice2 != NULL)
	{
		fseek(matrice2, 0, SEEK_SET);
		for(int i=0;i<23;i++)
		{
			for(int k=0;k<40;k++)
			{
				if(fscanf(matrice2, "%d", &carte[i][k]) == 0)
		        {
					printf("test KO \n");
				}
			}
		}
	}
	fclose(matrice2);
}

void afficherlvl2(void)
{
		static DonneesImageRGB *fondniv2 = NULL; // L'image a afficher au centre de l'ecran
		static DonneesImageRGB *box = NULL; // 1er box
		static DonneesImageRGB *mur= NULL;
		static DonneesImageRGB *tubed = NULL;
		static DonneesImageRGB *tubeg = NULL;
		static DonneesImageRGB *sol = NULL;

		box = lisBMPRGB("bloc.bmp");
		mur = lisBMPRGB("mur.bmp");
		tubed = lisBMPRGB("tubedroite.bmp");
		tubeg = lisBMPRGB("tubegauche.bmp");
		fondniv2 = lisBMPRGB("fondniv2.bmp");
		sol = lisBMPRGB("sol1.bmp");
	
		element(0,0,fondniv2);
		element(9,4, box);
		element(0,2,tubed);
		element(39,2,tubeg);
		element(0,0, sol);
		element(8,0, sol);
		element(16,0, sol);
		element(32,0, sol);
		element(14,2, mur);
		element(14,3, mur);
		element(14,4, mur);
		element(14,5, mur);
		element(14,6, mur);
		element(14,7, mur);
		element(14,8, mur);
		element(14,9, mur);
		element(14,10, mur);
		element(14,11, mur);
		element(14,12, mur);
		element(15,12, mur);
		element(17,12, mur);
		element(16,12, mur);
		element(4,9, mur);
		element(5,9, mur);
		
	
	
		libereDonneesImageRGB(&fondniv2); // libere la structure image
		libereDonneesImageRGB(&box);
		libereDonneesImageRGB(&mur);
		libereDonneesImageRGB(&tubed);
		libereDonneesImageRGB(&tubeg);
		libereDonneesImageRGB(&sol);
		
}

int spawnmonstre(int BorneA,int BorneB,int x,int y,int b, float xMario, float yMario, int carte[23][41],int etatMario)
{
	static int i=0;
	static int sens=1;
	int detection=0;
	static int A=0;	
	static int colba;
	colba=detectionbas(x+i,y-A,carte,colba);  //detection collision en dessous mario si collision colba=1
	
	if ((colba==0 && y-A>=65) || (colba==2 && y-A>=65))//pas de colision avec le sol
	{	
		A=A+8;
		printf("%d\n",y-A);
	}
	if (colba==1 || y-A<65) //si colision avec le sol
	{
		if (i<BorneB && i>BorneA && sens==1)
			i=i+5;
		if (i<BorneB && i>BorneA && sens==-1)
			i=i-5;
		if (i==BorneB)
		{
			i=i-5;
			sens=-1;
		}
		if (i==BorneA)
		{
			i=i+5;
			sens=1;
		}
	}
	static DonneesImageRGB *SpriteMonstre = NULL; 
	SpriteMonstre = lisBMPRGB("SpriteMonstre.bmp");
	int *pixels2 = BVR2ARVBis(32,32, SpriteMonstre->donneesRGB);
	ecrisImageARVB(x+i,y-A,32,32, pixels2);
		
	detection=colision(xMario,yMario,x+i,y-A,etatMario);
	libereDonneesImageRGB(&SpriteMonstre);
	return detection;
}


