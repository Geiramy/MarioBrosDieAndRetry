#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()
#include "fonction.h"//Nos fonctions qu'on a creer pour le logiciel
#include "menu.h" //affichage menu
//#include <SDL/SDL.h>           //musique
//#include <SDL/SDL_mixer.h>	//musique


// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1280
#define HauteurFenetre 736


void gestionEvenement(EvenementGfx evenement);



int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);
	/*if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_AllocateChannels(20); //Allouer 32 canaux
   Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
   Mix_Chunk *son;
   son= Mix_LoadWAV("MariOverworld.wav");
   Mix_VolumeChunk(son, MIX_MAX_VOLUME);	
   Mix_PlayChannel(1, son, 20);
   
	lanceBoucleEvenements();
	return 0;
}
Mix_Chunk *Musique(const char *musique,int channel1, int channel2, int nbr, Mix_Chunk *son)
{
	Mix_HaltChannel(channel2);//pour arreter le canal qui est en marche
	son=Mix_LoadWAV(musique);
	Mix_VolumeChunk(son, MIX_MAX_VOLUME*2);
	Mix_PlayChannel(channel1,son,nbr);
	return son;
}*/ //musique

	lanceBoucleEvenements(); //a enlever si musique
	return 0;}  //a enlever si musique




/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static int anim = 0;
	static int blocage = 0; //empêche la "commande" d'obtenir une valeur lorsqu'on est sur le Panneau ou dans le jeu.
    static int me = 0;
	static int commande=0;
	static int carte[23][41];
	static int a=0; //variable de test pour mvt de mario (fluidité)
	static float xMario=32;
	static float yMario=64;
	static int coldr=0; //detection collision droite
	static int colga=0;
	static int colha=0;
	static int colba=1;
	static int deplacement=1;
	static float vyMario = -0;
	static int etatMario=0;
	static int Mariobaisser=0;	
	static int b =0;//pour mvts des bots
	static int captchute=0;
	static int captpics=0;
	static int saut=0;
	static int mort=0;
	static int colision=0;
	static int colision2=0;
	static int toucher=0;
	static int champi=0;
	static int champiSorti=0;
	static int easter=0;
	static int niveau=1;
	static int sponmontre=0;
	
	/*char *musicsaut="saut.wav";
	char *musicgameover="game-over.wav";
	char *musicnivtermine="niveau-termine.wav";
	char *musicmariogrand="power-up.wav";
	char *musictuyau="tuyau.wav";
	char *musicontinu="MariOverworld.wav";
	
	Mix_Chunk *son;*/ //musique

	
	switch (evenement)
	{
		case Initialisation:
                                                                                                                                                                                                                                                   
		demandeTemporisation(20);
			break;
		
		case Temporisation:
			//pseudo pfd
			yMario += vyMario*0.002;
			if (colba==0 && colha==0) {
				vyMario -= 100;//gravité
				saut=0;
				}
			if (colba==2 && vyMario<-1400 && saut==0 && vyMario>-3000) {
				vyMario = vyMario+200;//gravité
				}
			if (colba==2 && vyMario<-3000 && saut==0 && vyMario>-15000) {
				vyMario = -1500;//gravité
				}
			if ((colba==1 && saut==0) || (colha==1 && saut==1 && etatMario==0) ||(colha==2 && saut==1 && etatMario==1)|| (colha==3 && saut==1 && etatMario==0)) {
				vyMario = 0;
				saut=0;
				}
			if ((colba==0 && saut==0) || (colha==2 && saut==0 && etatMario==1) || (colha==1 && saut==0 && etatMario==0)|| (colha==3 && saut==0 && etatMario==0)){
				vyMario -=100;
				}
			
			rafraichisFenetre();
			break;
			
		case Affichage:
			changementmenu(me);
			switch (commande)
			{
				case 1 :
					if (niveau==1)
					{
						afficherlvl1();
						quadrillagecarte1(carte);
						blocage = 1;
						if(caractereClavier()==27)
							{
								blocage = 0;
								xMario=32;
								yMario=64;
								niveau=1;
								etatMario=0;
								changementmenu(me);
							}
						affichemort(mort); //quadrillage carte sous forme de tableau a 2 dimensions
						colba=detectionbas(xMario,yMario,carte,colba);  //detection collision en dessous mario si collision colba=1
						coldr=detectiondroite(xMario,yMario,carte,coldr);
						colga=detectiongauche(xMario,yMario,carte,colga);
						colha=detectionhaut(xMario,yMario,carte,colha);
						plateforme(xMario,yMario,carte);
						yMario=blocagemario(yMario);
						captchute=morttomber(yMario);
						captpics=pics(xMario,yMario,carte);
						if (etatMario==0)
						{
							if (deplacement==1 && vyMario==0)
								deplacementmariopetitdroite(xMario, yMario, a,easter); //changement d'image au deplacement
							if (deplacement==-1 && vyMario==0)
								deplacementmariopetitgauche(xMario, yMario, a,easter); //changement d'image au deplacement
							if (vyMario!=0)
								sautmariopetit(xMario,yMario,deplacement,easter);					
						}
						else
						{
							if (deplacement==1 && Mariobaisser!=1 && vyMario==0)
								deplacementmariogranddroite(xMario, yMario, a,easter); //changement d'image auq deplacement
							if (deplacement==-1 && Mariobaisser!=1 && vyMario==0)
								deplacementmariograndgauche(xMario, yMario, a,easter); //changement d'image au deplacement
							if (vyMario!=0 && Mariobaisser!=1 )
							{
								sautmariogrand(xMario,yMario,deplacement,easter);	
							}
								
							if (Mariobaisser==1)// baisser mario
							{
								grandmariobaisser(xMario,yMario,deplacement,easter);
							}						
						}
						if (captpics==1 && etatMario==1)
						{
							//Musique(musicmariogrand,5,8,0,son);
							etatMario=0;
							champiSorti=0;
						}
						
						if ((colision==1 && etatMario==0) || captchute==1) //MORT
						{
							//Musique(musicgameover,4,1,0,son);
							//Musique(musicontinu,1,8,0,son);
							xMario=32;
							yMario=64;
							vyMario=0;
							mort++;
							captchute=0;
							etatMario=0;
							colision=0;
							toucher=0;
							champi=0;
							champiSorti=0;
						}
						if (colision==1 && etatMario==1)
						{
							etatMario=0;
							colision=0;
							toucher=1;
							champiSorti=0;
							champi=0;
							//bot(
						}
						if (colision!=1)
						{
							colision=bot(1,0,60,64,64,b,xMario,yMario,etatMario,toucher);
							//colision2=bot(2,0,40,258,160,b,xMario,yMario,etatMario,toucher); 				//si on veut mettre nouveau BOT (couleur, Borne..)
							if ((etatMario==0 && champi==0 && colha==3) || (champiSorti==1 && etatMario==0))
							{
							//Musique(musicmariogrand,6,8,0,son);
								etatMario=champignon(-260,440,288,160,b,xMario,yMario,carte,etatMario,champiSorti);
								champiSorti=1;
							}
							if (etatMario==1)
								champi=1;
							b++;
							//printf("nb de morts = %d\n",mort);
						}
						if(xMario>1200 && etatMario==0 && blocage == 1)
						{
							niveau=2;
							xMario=32;
							yMario=64;
						}
					
					}
					
					if(niveau==2)
					{
						afficherlvl2();
						quadrillagecarte2(carte);
						blocage=1;
						if(caractereClavier()==27)
						{
							blocage = 0;
							xMario=32;
							yMario=64;
							niveau=2;
							etatMario=0;
							changementmenu(me);
						}
						affichemort(mort); //quadrillage carte sous forme de tableau a 2 dimensions
						colba=detectionbas(xMario,yMario,carte,colba);  //detection collision en dessous mario si collision colba=1
						coldr=detectiondroite(xMario,yMario,carte,coldr);
						colga=detectiongauche(xMario,yMario,carte,colga);
						colha=detectionhaut(xMario,yMario,carte,colha);
						yMario=blocagemario(yMario);
						captchute=morttomber(yMario);
						captpics=pics(xMario,yMario,carte);
						if (etatMario==0)
						{
							if (deplacement==1 && vyMario==0)
								deplacementmariopetitdroite(xMario, yMario, a,easter); //changement d'image au deplacement
							if (deplacement==-1 && vyMario==0)
								deplacementmariopetitgauche(xMario, yMario, a,easter); //changement d'image au deplacement
							if (vyMario!=0)
								sautmariopetit(xMario,yMario,deplacement,easter);					
						}
						else
						{
							if (deplacement==1 && Mariobaisser!=1 && vyMario==0)
								deplacementmariogranddroite(xMario, yMario, a,easter); //changement d'image auq deplacement
							if (deplacement==-1 && Mariobaisser!=1 && vyMario==0)
								deplacementmariograndgauche(xMario, yMario, a,easter); //changement d'image au deplacement
							if (vyMario!=0 && Mariobaisser!=1 )
							{
								sautmariogrand(xMario,yMario,deplacement,easter);	
							}
								
							if (Mariobaisser==1)// baisser mario
							{
								grandmariobaisser(xMario,yMario,deplacement,easter);
							}						
						}
						if (captpics==1 && etatMario==1)
						{
							//Musique(musicmariogrand,5,8,0,son);
							etatMario=0;
							champiSorti=0;
						}
						
						if ((colision2==1 && etatMario==0) || captchute==1) //MORT
						{
							//Musique(musicgameover,4,1,0,son);
							//Musique(musicontinu,1,8,0,son);
							xMario=32;
							yMario=64;
							vyMario=0;
							mort++;
							captchute=0;
							etatMario=0;
							colision2=0;
							toucher=0;
							champi=0;
							champiSorti=0;
						}
						if (colision2==1 && etatMario==1)
						{
							etatMario=0;
							colision2=0;
							toucher=1;
							champiSorti=0;
							champi=0;
							//bot(
						}
						if (colision2!=1)
						{
							//colision=bot(1,0,60,64,64,b,xMario,yMario,etatMario,toucher);
							//colision2=bot(2,0,40,258,160,b,xMario,yMario,etatMario,toucher); 				//si on veut mettre nouveau BOT (couleur, Borne..)
							if ((etatMario==0 && colha==3) || (champiSorti==1 && etatMario==0))
							{
							//Musique(musicmariogrand,6,8,0,son);
								etatMario=champignon(-260,100,288,160,b,xMario,yMario,carte,etatMario,champiSorti);
								champiSorti=1;
							}
							if (coldr==3 && sponmontre==0)
							{
								colision2=spawnmonstre(-50,100,608,704,b,xMario,yMario,carte,etatMario);
								sponmontre=1;
							}
							if (etatMario==1)
								champi=1;
							b++;
						}
						if(xMario>1200 && etatMario==0 && blocage == 1)
						{
							niveau=0;
							champi=0;
							champiSorti=0;
							xMario=32;
							yMario=32;
						}
					
					}	

					if(niveau==0)
					{
						ecranfin(mort);
						if(caractereClavier()==27)
						{
							blocage = 0;
							xMario=32;
							yMario=64;
							niveau=1;
							etatMario=0;
							mort=0;
							changementmenu(me);
						}
						
					} 
					rafraichisFenetre();
				break;
				
				case 2:
						Panneau();
						blocage = 2;
						AnimationPanneau(anim);     //animation au cas ou on appuie sur droite,gauche...
						if(caractereClavier()==27)
						{
							blocage = 0;
							changementmenu(me);
						}
						rafraichisFenetre();
				break;
				
			}
			
				
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
			if(caractereClavier()==13 && blocage==0)
			{
				anim = 0;
				commande = entrer(me);
				//Musique(musictuyau,3,8,0,son);  // Quand on appuie sur "entrer" dans le menu
			}
			switch (caractereClavier())
			{
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
					termineBoucleEvenements(); 
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			if (toucheClavier()==13) //cas ou on appuie sur haut
				{
					//Musique(musicsaut,2,8,0,son);
					anim = 1;
				}
			if (toucheClavier()==14) //cas ou on appuie sur bas
				{
					anim = 2;
				}
			if (toucheClavier()==15)
				{
					anim = 3;
					me=0;
					if(colga==0 && xMario>8 && blocage==1)
					{
						xMario=xMario-8;
						deplacement=-1;
						a++;
					}
				}
			if (toucheClavier()==16)
				{
					anim = 4;
					me=1;
					if((coldr==0 && blocage==1) || (coldr==3 && blocage==1))
					{
						xMario=xMario+8;
						deplacement=1;
						a--;
					}
					if(xMario>1200 && etatMario==1 && blocage == 1){
					}
				}
			if (toucheClavier()==17) //cas ou on appuie sur haut
				{
					anim = 5;
				}
			/*if (toucheClavier()==17 && easter==1 && blocage==1)
				easter=0;
			if (toucheClavier()==17 && easter==0 && blocage==1)
				easter=1;*/
			if ((toucheClavier()==13 && colha==0 && vyMario==0 && Mariobaisser==0 && etatMario==0 && blocage==1)) // saut fleche du haut
			{
				vyMario = 4000;//saut du petit mario
				saut=1;
			}
			if (toucheClavier()==13 && colha==0 && vyMario==0 && Mariobaisser==0 && etatMario==1 && blocage==1) // saut fleche du haut
			{
				vyMario = 5500;//saut du grand mario
				saut=1;
			}
			if (toucheClavier()==13 && vyMario == 0 && Mariobaisser==1)//lever Mario
					Mariobaisser=0;
			if (toucheClavier()==14 && etatMario ==1  && vyMario==0) //bas
					Mariobaisser=1;

			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());

			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			break;
	}
}
