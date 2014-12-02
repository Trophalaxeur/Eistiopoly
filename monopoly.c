/*!
  \file monopoly.c
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief code source du main
  \date 09/01/2006
  \version 1.0
*/

#include "monopoly.h"

int main(int argc, char *argv[])
{
	//Structure information du bureau de Krystel
	information* bureau_de_krystel[16];
	//Structure information du bureau de Nadège
	information* bureau_de_nadege[16];
	
	//Page des noms de joueur contenant les informations des joueurs
	struct_nom_joueur* page_nom_joueur;
	//Initialisation de la page des noms de joueur
	page_nom_joueur=NULL;
	
	//Anneau de joueurs
	joueur* j_anneau_joueurs;
	j_anneau_joueurs=NULL;
	
	//Anneau de joueurs temporaire
	joueur* pj_joueurs;
	pj_joueurs=NULL;
	
	//Surface de l'écran
	SDL_Surface* surf_ecran = NULL;
	
	//Valeur de retour de la page d'accueil
	int int_retour;
	
	//Variable de boucle
	int i;

	//Tableau de couleur
	rvb_couleur couleurs[8];
	
	//Plateau de jeu
	cases** plateau;
	
	//Initialisation du random
	srand(time(NULL));
	
	//Le plateau de jeu est composé de 40 pointeurs vers des instances de la structure cases
	plateau=new cases*[40];
	
	//Chaque cases est un pointeur vers une instance de la structure case
	for(i=0;i<40;i++)
	{
		plateau[i]=new cases;
	}
	
	//Initialisation des couleurs
	init_tab_rvb_couleur(couleurs);
	
	//Initialisation de sdl
	surf_ecran=init_sdl();
	
	//Affichage de l'écran d'accueil
	int_retour=affich_accueil(surf_ecran, &page_nom_joueur);
	//Si le joueur n'a pas souhaité quitté
	if(int_retour!=MSG_QUITTER)
	{
		//S'il s'agit d'un chargement
		if(int_retour==MSG_LOAD)
		{
			//Nombre de joueur initial
			i=1;
			//Chargement des joueurs
			j_anneau_joueurs=chargement(j_anneau_joueurs, plateau, couleurs, surf_ecran);
			//Sauvegarde de la tete de l'anneau des joueurs
			pj_joueurs=j_anneau_joueurs;
			//On compte le nombre de joueur
			while((pj_joueurs=pj_joueurs->pjoueur_suivant)!=j_anneau_joueurs)
			{
				//On augmente le nombre de joueur
				i++;
			}
		}
		//Autrement on initialise les nouveaux joueurs
		else
		{
			//Initialisation du plateau
			init_plateau(surf_ecran, couleurs, plateau);
			//Initialisation des nouveaux joueurs
			j_anneau_joueurs=init_anneau_joueur(page_nom_joueur->int_nbre_joueur, page_nom_joueur->str_noms);
			//Stockage temporaire du nombre de joueur
			i=page_nom_joueur->int_nbre_joueur;
			//Destruction de la page des noms des joueurs
			destruction_nom_joueur(page_nom_joueur);
		}
		//Initialisation du bureau de Krystel
		init_bureau_krystel(bureau_de_krystel);
		//Initialisation du bureau de Nadège
		init_bureau_nadege(bureau_de_nadege);
		//Lancement du jeu
		jeu(surf_ecran, j_anneau_joueurs,plateau, i, bureau_de_krystel, bureau_de_nadege);
	}

	//On quitte le module SDL
	SDL_Quit();
	//On quitte le module TTF
	TTF_Quit();
	//Libération des cases du tableau
	for(i=0;i<40;i++) delete(plateau[i]);
	//Libération du plateau
	delete(plateau);

	//Fin du programme
	return (0);
}

