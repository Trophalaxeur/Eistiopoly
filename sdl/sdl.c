#include "sdl.h"


void mapause(void)
{
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					default:
					break;
				}
				break;
			default:
			break;
        }
    }
}

SDL_Surface* rotation_90(SDL_Surface* Depart)
{
	//La surface d'arrivee
	SDL_Surface* arrivee;
	arrivee = SDL_CreateRGBSurface(SDL_HWSURFACE,Depart->h,Depart->w, Depart->format->BitsPerPixel,0,0,0,0);
	
	int x;
	int y;

	for(y=0;y<Depart->h;y+=1)
	{
		for(x=0;x<Depart->w;x+=1)
		{
			((Uint32*)arrivee->pixels)[y+(((arrivee->h)-1)-x)*(arrivee->w)]=((Uint32*)Depart->pixels)[x+y*(Depart->w)];
		}
	}
	return(arrivee);
}

SDL_Surface* rotation_180(SDL_Surface* Depart)
{
	// La surface d'arrivee
	SDL_Surface* arrivee;
	arrivee = SDL_CreateRGBSurface(SDL_HWSURFACE,Depart->w,Depart->h,Depart->format->BitsPerPixel,0,0,0,0);
	
	int x;
	int y;
	for(y=0;y<Depart->h;y+=1)
	{
		for(x=0;x<Depart->w;x+=1)
		{
			((Uint32*)arrivee->pixels)[((arrivee->w-1)-x)+((arrivee->h-1)-y)*arrivee->w]=((Uint32*)Depart->pixels)[x+y*Depart->w];
		}
	}
	return(arrivee);
}

SDL_Surface* rotation_270(SDL_Surface* Depart)
{
	// La surface d'arrivee
	SDL_Surface* arrivee;
	arrivee = SDL_CreateRGBSurface(SDL_HWSURFACE,Depart->h,Depart->w,Depart->format->BitsPerPixel,0,0,0,0);
	
	int x;
	int y;
	for(y=0;y<Depart->h;y+=1)
	{
		for(x=0;x<Depart->w;x+=1)
		{
			((Uint32*)arrivee->pixels)[(((arrivee->w)-1)-y)+x*(arrivee->w)]=((Uint32*)Depart->pixels)[x+y*(Depart->w)];
		}
	}
	return(arrivee);
}

SDL_Surface* init_sdl(void)
{
	//Surface de l'ecran
	SDL_Surface *ecran=NULL;

	//Initialisation en mode video de sdl
	SDL_Init(SDL_INIT_VIDEO);
	
	//Répétition des touches
	SDL_EnableKeyRepeat(40,40);

	//Initialisation du mode TTF (Pour l'ecriture)
	TTF_Init();
	
	//Chargement du mode video en resolution 800*600 et 32 couleur, plein ecran.
	//if((ecran = SDL_SetVideoMode(1280, 1024, 32, SDL_HWSURFACE))==NULL)
	if((ecran = SDL_SetVideoMode(1280, 1024, 32, SDL_HWSURFACE|SDL_FULLSCREEN))==NULL)
	{
		cout << "Erreur ! Le programme ne peut fonctionner qu'en 1280 par 1024. Si votre écran ne peut pas supporter cette résolution, veuillez contactez le développeur." <<endl;
		exit(0);
	}
	
	//Chargement du titre de la fenetre
	SDL_WM_SetCaption("Monopoly", NULL);
	
	//On remplit le fond de noir
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 25, 25, 75));
	
	//On retourne la surface de l'écran
	return(ecran);
}

SDL_Surface* creation_joueur(int int_joueur)
{
	//Surface du joueur
	SDL_Surface* surf_joueur;
	surf_joueur=NULL;
	//Chemin d'accès à l'image
	char chemin[256];
	
	//Stockage du chemin vers l'image du joueur en fonction de son numéro
	sprintf(chemin,"sdl/images/joueur%d.png",int_joueur);
	
	//Chargement de l'image
	surf_joueur=IMG_Load(chemin);
	
	//On retourne l'image du joueur
	return(surf_joueur);
	
}

void affich_joueur(SDL_Surface* surf_ecran, joueur* pj_joueur,int int_position, cases* pcase)
{
	//Position du joueur
	SDL_Rect position;
	
	//Selon la position de la case
	switch((*pcase).int_position)
	{
		//On calcul les coordonnées de l'image du joueur
		case POSITION_GAUCHE:
			position.x=(*pcase).rect_coordonnees.x+25+30*(int_position%2);
			position.y=(*pcase).rect_coordonnees.y+5+25*(int_position%3);
			break;
		case POSITION_DROITE:
			position.x=(*pcase).rect_coordonnees.x+35+30*(int_position%2);
			position.y=(*pcase).rect_coordonnees.y+5+25*(int_position%3);
			break;
		case POSITION_HAUT:
			position.x=(*pcase).rect_coordonnees.x+5+25*(int_position%3);
			position.y=(*pcase).rect_coordonnees.y+25+30*(int_position%2);
			break;
		default:
			position.x=(*pcase).rect_coordonnees.x+5+25*(int_position%3);
			position.y=(*pcase).rect_coordonnees.y+35+30*(int_position%2);
			break;
	}
	//On colle l'image du joueur sur le fond
	SDL_BlitSurface(pj_joueur->surf_image, NULL, surf_ecran, &position);
	//On met à jour l'écran
	SDL_Flip(surf_ecran);
}

SDL_Surface* creation_case(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte1, char* texte2, int int_prix, int int_position)
{
	//Chaine de caractere du prix
	char texte_prix[255];

	//Surface de la case
	SDL_Surface* surf_case;
	surf_case=NULL;

	//Surface du fond de la case
	SDL_Surface* surf_fond;
	surf_fond=NULL;

	//Surface de la couleur du groupe
	SDL_Surface* surf_groupe;
	surf_groupe=NULL;

	//Surface du fond du groupe
	SDL_Surface* surf_fond_groupe;
	surf_fond_groupe=NULL;

	//Surface du texte partie 1
	SDL_Surface* surf_texte1;
	surf_texte1=NULL;

	//Surface du texte partie 2
	SDL_Surface* surf_texte2;
	surf_texte2=NULL;

	//Surface du texte partie 2
	SDL_Surface* surf_texte_prix;
	surf_texte_prix=NULL;

	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {16, 246, 128};

	//Position
	SDL_Rect position;
	
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 14);

	//Ecriture de la première partie du texte
	surf_texte1 = TTF_RenderText_Shaded(police, texte1, couleur_texte, couleur_fond_texte);
	//Ecriture de la seconde partie du texte
	surf_texte2 = TTF_RenderText_Shaded(police, texte2, couleur_texte, couleur_fond_texte);
	//Enregistrement du prix
	sprintf(texte_prix,"%d Fintz",int_prix);
	//Ecriture du prix
	surf_texte_prix = TTF_RenderText_Shaded(police, texte_prix, couleur_texte, couleur_fond_texte);

	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR-2*CASE_EPAISSEUR, CASE_HAUTEUR-2*CASE_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 16, 246, 128));

	//Création de la surface du groupe
	surf_groupe=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR, CASE_GROUPE_HAUTEUR+2*CASE_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_groupe, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface de fond du groupe
	surf_fond_groupe=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR-2*CASE_EPAISSEUR, CASE_GROUPE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de la couleur de fond du groupe
	SDL_FillRect(surf_fond_groupe, NULL, SDL_MapRGB(surf_ecran->format, couleur.rouge, couleur.vert, couleur.bleu));

	//On modifie la position du fond du groupe
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le fond du groupe sur ce dernier
	SDL_BlitSurface(surf_fond_groupe, NULL, surf_groupe, &position);

	//On modifie la position du fond
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//On modifie la position du groupe
	position.x=0;
	position.y=0;
	//On colle le groupe sur la case
	SDL_BlitSurface(surf_groupe, NULL, surf_case, &position);

	//On centre la position de la premiere partie texte
	position.x=(CASE_LARGEUR-(*surf_texte1).w)/2;
	position.y=30;
	//On colle la première partie du texte
	SDL_BlitSurface(surf_texte1, NULL, surf_case, &position);

	//On centre la position de la deuxieme partie du texte
	position.x=(CASE_LARGEUR-(*surf_texte2).w)/2;
	position.y=50;
	//On colle la deuxième partie du texte
	SDL_BlitSurface(surf_texte2, NULL, surf_case, &position);

	//On centre la position du prix
	position.x=(CASE_LARGEUR-(*surf_texte_prix).w)/2;
	position.y=CASE_HAUTEUR-CASE_EPAISSEUR-20;
	//On colle le prix
	SDL_BlitSurface(surf_texte_prix, NULL, surf_case, &position);
	
	//Selon la position
	switch(int_position)
	{
		//Si la case est à droite
		case POSITION_DROITE:
			//Rotation de l'image de 90°
			surf_case = rotation_90(surf_case);
			break;
		//Si la case est en haut
		case POSITION_HAUT:
			//Rotation de l'image de 180°
			surf_case = rotation_180(surf_case);
			break;
		//Si la case est à gauche
		case POSITION_GAUCHE:
			//Rotation de l'image de 270°
			surf_case = rotation_270(surf_case);
			break;
		//Par défaut, la case est en bas
		default:
		break;
	}
	
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_fond_groupe);
	SDL_FreeSurface(surf_groupe);
	SDL_FreeSurface(surf_texte1);
	SDL_FreeSurface(surf_texte2);
	SDL_FreeSurface(surf_texte_prix);

	//On retourne la surface de la case
	return(surf_case);
}

SDL_Surface* creation_case_bureau(SDL_Surface* ecran, int int_type, int int_position)
{
	//Surface du logo
	SDL_Surface* surf_logo;
	surf_logo=NULL;
	//Surface du fond de la case
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	//Surface de la case
	SDL_Surface* surf_case;
	surf_case=NULL;
	//Surface de la première partie du texte
	SDL_Surface* surf_texte1;
	surf_texte1=NULL;
	//Surface de la deuxième partie du texte
	SDL_Surface* surf_texte2;
	surf_texte2=NULL;
	//Position des images
	SDL_Rect position;

	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {16, 246, 128};

	//Ouvertue de la police d'écriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 14);
	
	//Ecriture du premier texte
	surf_texte1 = TTF_RenderText_Shaded(police, "Bureau de", couleur_texte, couleur_fond_texte);
	//Ecriture du second texte
	if(int_type==BUREAU_KRYSTEL) surf_texte2 = TTF_RenderText_Shaded(police, "Krystel", couleur_texte, couleur_fond_texte);
	else surf_texte2 = TTF_RenderText_Shaded(police, "Nadege", couleur_texte, couleur_fond_texte);

	//Fermeture de la police d'écriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR-2*CASE_EPAISSEUR, CASE_HAUTEUR-2*CASE_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(ecran->format, 16, 246, 128));

	//Chargelent de l'image du logo
	if(int_type==BUREAU_KRYSTEL) surf_logo = IMG_Load("sdl/images/eisti_logo.png");
	else surf_logo = IMG_Load("sdl/images/eisti_logo2.png");

	//On modifie la position du fond
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//On centre la position de la première partie texte
	position.x=(CASE_LARGEUR-(*surf_texte1).w)/2;
	position.y=5;
	//On colle la première partie du texte
	SDL_BlitSurface(surf_texte1, NULL, surf_case, &position);

	//On centre la position de la deuxième partie du texte
	position.x=(CASE_LARGEUR-(*surf_texte2).w)/2;
	position.y=25;
	//On colle la deuxième partie du texte
	SDL_BlitSurface(surf_texte2, NULL, surf_case, &position);

	//On positione le logo
	position.x=16;
	position.y=45;
	//On colle le logo sur la case
	SDL_BlitSurface(surf_logo, NULL, surf_case, &position);

	//Selon la position
	switch(int_position)
	{
		//Si la case est à droite
		case POSITION_DROITE:
			//Rotation de l'image de 90°
			surf_case = rotation_90(surf_case);
			break;
		//Si la case est en haut
		case POSITION_HAUT:
			//Rotation de l'image de 180°
			surf_case = rotation_180(surf_case);
			break;
		//Si la case est à gauche
		case POSITION_GAUCHE:
			//Rotation de l'image de 270°
			surf_case = rotation_270(surf_case);
			break;
		//Par défaut, la case est en bas
		default:
		break;
	}

	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_logo);
	SDL_FreeSurface(surf_texte1);
	SDL_FreeSurface(surf_texte2);
	//On retourne la case que l'on vient de créer
	return(surf_case);
}

SDL_Surface* creation_case_lieu_commun(SDL_Surface* ecran, int int_type)
{
	//Surface de l'image
	SDL_Surface* surf_image;
	surf_image=NULL;
	//Surface du fond de la case
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	//Surface de la case
	SDL_Surface* surf_case;
	surf_case=NULL;
	//Surface du prix
	SDL_Surface* surf_prix;
	surf_prix=NULL;

	//Position des images
	SDL_Rect position;

	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {16, 246, 128};

	//Ouvertue de la police d'écriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 14);
	
	//Ecriture du premier texte
	surf_prix = TTF_RenderText_Shaded(police, "2000 Fintz", couleur_texte, couleur_fond_texte);

	//Fermeture de la police d'écriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR-2*CASE_EPAISSEUR, CASE_HAUTEUR-2*CASE_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(ecran->format, 16, 246, 128));

	//Chargement de l'image
	//if(int_type==BDE) surf_image = IMG_Load("sdl/images/bureau_bde.png");
	switch(int_type)
	{
		case LC_WC:
			surf_image = IMG_Load("sdl/images/wc.png");
			break;
		case LC_ASCENSEUR:
			surf_image = IMG_Load("sdl/images/ascenseur.png");
			break;
		case LC_RU:
			surf_image = IMG_Load("sdl/images/ru.png");
			break;
		case LC_PARKING:
			surf_image = IMG_Load("sdl/images/parking.png");
			break;
		default:
			break;
	}
	//On modifie la position du fond
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//On positionne le prix
	position.x=(CASE_LARGEUR-(*surf_prix).w)/2;
	position.y=CASE_HAUTEUR-CASE_EPAISSEUR-20;
	//On colle le prix sur la case
	SDL_BlitSurface(surf_prix, NULL, surf_case, &position);

	//On positione le logo
	position.x=10;
	position.y=8;
	//On colle le logo sur la case
	SDL_BlitSurface(surf_image, NULL, surf_case, &position);

	//Selon la position
	switch(int_type)
	{
		//Si la case est à droite
		case LC_PARKING:
			//Rotation de l'image de 90°
			surf_case = rotation_90(surf_case);
			break;
		//Si la case est en haut
		case LC_RU:
			//Rotation de l'image de 180°
			surf_case = rotation_180(surf_case);
			break;
		//Si la case est à gauche
		case LC_ASCENSEUR:
			//Rotation de l'image de 270°
			surf_case = rotation_270(surf_case);
			break;
		//Par défaut, la case est en bas
		default:
		break;
	}

	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_image);
	SDL_FreeSurface(surf_prix);

	//On retourne la case que l'on vient de créer
	return(surf_case);
}
SDL_Surface* creation_case_association(SDL_Surface* ecran, int int_type)
{
	//Surface du logo
	SDL_Surface* surf_logo;
	surf_logo=NULL;
	//Surface du fond de la case
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	//Surface de la case
	SDL_Surface* surf_case;
	surf_case=NULL;
	//Surface du prix
	SDL_Surface* surf_prix;
	surf_prix=NULL;

	//Position des images
	SDL_Rect position;

	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {16, 246, 128};

	//Ouvertue de la police d'écriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 14);
	
	//Ecriture du premier texte
	surf_prix = TTF_RenderText_Shaded(police, "1500 Fintz", couleur_texte, couleur_fond_texte);

	//Fermeture de la police d'écriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR-2*CASE_EPAISSEUR, CASE_HAUTEUR-2*CASE_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(ecran->format, 16, 246, 128));

	//Chargelent de l'image du logo
	if(int_type==BDE) surf_logo = IMG_Load("sdl/images/bureau_bde.png");
	else surf_logo = IMG_Load("sdl/images/bureau_bds.png");

	//On modifie la position du fond
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//On positionne le prix
	position.x=(CASE_LARGEUR-(*surf_prix).w)/2;
	position.y=CASE_HAUTEUR-CASE_EPAISSEUR-20;
	//On colle le prix sur la case
	SDL_BlitSurface(surf_prix, NULL, surf_case, &position);

	//On positione le logo
	position.x=10;
	position.y=8;
	//On colle le logo sur la case
	SDL_BlitSurface(surf_logo, NULL, surf_case, &position);

	//Selon le type de bureau d'association
	switch(int_type)
	{
		//S'il s'agit du bde
		case BDE:
			//Rotation de l'image de 180
			surf_case = rotation_180(surf_case);
			break;
		//Par défaut, il s'agit du bds
		default:
			//Rotation de l'image de 270°
			surf_case = rotation_270(surf_case);
			break;
		break;
	}

	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_logo);
	SDL_FreeSurface(surf_prix);

	//On retourne la case que l'on vient de créer
	return(surf_case);
}

SDL_Surface* creation_case_soiree(SDL_Surface* ecran, int int_type)
{
	//Surface du logo
	SDL_Surface* surf_logo;
	surf_logo=NULL;
	//Surface du fond de la case
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	//Surface de la case
	SDL_Surface* surf_case;
	surf_case=NULL;
	//Surface du prix
	SDL_Surface* surf_prix;
	surf_prix=NULL;
	SDL_Surface* surf_texte;
	surf_texte=NULL;

	//Position des images
	SDL_Rect position;

	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {16, 246, 128};

	//Ouvertue de la police d'écriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 14);
	
	//Ecriture du premier texte
	if(int_type==SOIREE_AREA) surf_texte = TTF_RenderText_Shaded(police, "Area club", couleur_texte, couleur_fond_texte);
	else surf_texte = TTF_RenderText_Shaded(police, "Gala", couleur_texte, couleur_fond_texte);
	//Ecriture du premier texte
	surf_prix = TTF_RenderText_Shaded(police, "1500 Fintz", couleur_texte, couleur_fond_texte);

	//Fermeture de la police d'écriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR-2*CASE_EPAISSEUR, CASE_HAUTEUR-2*CASE_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(ecran->format, 16, 246, 128));

	//Chargelent de l'image du logo
	if(int_type==SOIREE_AREA) surf_logo = IMG_Load("sdl/images/soiree_area.png");
	else surf_logo = IMG_Load("sdl/images/soiree_gala.png");

	//On modifie la position du fond
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//On positionne le prix
	position.x=(CASE_LARGEUR-(*surf_texte).w)/2;
	position.y=CASE_HAUTEUR-CASE_EPAISSEUR-40;
	//On colle le prix sur la case
	SDL_BlitSurface(surf_texte, NULL, surf_case, &position);

	//On positionne le prix
	position.x=(CASE_LARGEUR-(*surf_prix).w)/2;
	position.y=CASE_HAUTEUR-CASE_EPAISSEUR-20;
	//On colle le prix sur la case
	SDL_BlitSurface(surf_prix, NULL, surf_case, &position);

	//On positione le logo
	position.x=10;
	position.y=8;
	//On colle le logo sur la case
	SDL_BlitSurface(surf_logo, NULL, surf_case, &position);

	//S'il s'agit du gala
	if(int_type==SOIREE_GALA)
	{
		//Rotation de l'image de 90°
		surf_case = rotation_90(surf_case);
	}

	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_logo);
	SDL_FreeSurface(surf_prix);
	SDL_FreeSurface(surf_texte);

	//On retourne la case que l'on vient de créer
	return(surf_case);
}

SDL_Surface* creation_case_coin(SDL_Surface* ecran, int int_type)
{
	//Surface de l'image
	SDL_Surface* surf_image;
	surf_image=NULL;
	//Surface du fond de la case
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	//Surface de la case
	SDL_Surface* surf_case;
	surf_case=NULL;

	//Position des images
	SDL_Rect position;

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_HAUTEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_HAUTEUR-2*CASE_EPAISSEUR, CASE_HAUTEUR-2*CASE_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(ecran->format, 16, 246, 128));

	//Chargelent de l'image du logo
	switch(int_type)
	{
		case SP_APPARTEMENT:
			surf_image = IMG_Load("sdl/images/case_depart.png");
			break;
		case SP_BUREAU_LAURENCE:
			surf_image = IMG_Load("sdl/images/bureau_laurence.png");
			break;
		case SP_MACHINE_CAFE:
			surf_image = IMG_Load("sdl/images/machine_cafe.png");
			break;
		case SP_TABLEAU:
			surf_image = IMG_Load("sdl/images/go_to_prison.png");
			break;
	}

	//On modifie la position du fond
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//On positionne l'image sur le fond
	position.x=CASE_EPAISSEUR;
	position.y=CASE_EPAISSEUR;
	//On colle le logo sur la case
	SDL_BlitSurface(surf_image, NULL, surf_case, &position);

	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_image);

	//On retourne la case que l'on vient de créer
	return(surf_case);
}

SDL_Surface* creation_case_detail(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte, int int_prix, int int_prix_niveau)
{
	SDL_Surface* surf_case;
	surf_case=NULL;
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	SDL_Surface* surf_groupe;
	surf_groupe=NULL;
	SDL_Surface* surf_groupe_fond;
	surf_groupe_fond=NULL;
	SDL_Surface* surf_sep;
	surf_sep=NULL;
	SDL_Surface* surf_texte[22];
	char texte_temp[256];
	int i;
	
	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {225, 255, 225};
	//Couleur du groupe
	SDL_Color couleur_groupe = {couleur.rouge, couleur.vert, couleur.bleu};

	//Position
	SDL_Rect position;
	
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 28);

	//Tire de la carte de propriété
	surf_texte[1] = TTF_RenderText_Shaded(police, texte, couleur_texte, couleur_groupe);

	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);
		
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 20);
	
	//Ecriture des informations contenus dans le groupe
	surf_texte[0] = TTF_RenderText_Shaded(police, "Titre de propriété", couleur_texte, couleur_groupe);
	
	//Ecriture des textes sur les informations sur les loyers
	surf_texte[2] = TTF_RenderText_Shaded(police, "LOYER Salle vide", couleur_texte, couleur_fond_texte);
	surf_texte[3] = TTF_RenderText_Shaded(police, "Niveau CPI 1", couleur_texte, couleur_fond_texte);
	surf_texte[4] = TTF_RenderText_Shaded(police, "Niveau CPI 2", couleur_texte, couleur_fond_texte);
	surf_texte[5] = TTF_RenderText_Shaded(police, "Niveau ING 1", couleur_texte, couleur_fond_texte);
	surf_texte[6] = TTF_RenderText_Shaded(police, "Niveau ING 2", couleur_texte, couleur_fond_texte);
	surf_texte[7] = TTF_RenderText_Shaded(police, "Niveau ING 3", couleur_texte, couleur_fond_texte);
	
	//Ecriture de la monnaie utilisé
	surf_texte[8] = TTF_RenderText_Shaded(police, "Fintz", couleur_texte, couleur_fond_texte);
	
	//Ecriture des différents prix
	for(i=0;i<6;i++)
	{
		sprintf(texte_temp,"%d",int_prix*(i+1));
		surf_texte[9+i] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);
	}
	
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);
	
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 17);
	
	//Ecriture des informations sur les loyers
	surf_texte[15] = TTF_RenderText_Shaded(police, "Si un élève possède toutes les salles", couleur_texte, couleur_fond_texte);
	surf_texte[16] = TTF_RenderText_Shaded(police, "d'un groupe de couleur, le loyer des", couleur_texte, couleur_fond_texte);
	surf_texte[17] = TTF_RenderText_Shaded(police, "salles vides de ce groupe est doublé.", couleur_texte, couleur_fond_texte);
	
	//Ecriture des informations sur l'achat d'un niveau et l'hypothèque
	sprintf(texte_temp,"Prix d'un niveau                    %d Fintz",int_prix_niveau);
	surf_texte[18] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);
	surf_texte[19] = TTF_RenderText_Shaded(police, "chacun", couleur_texte, couleur_fond_texte);
	surf_texte[20] = TTF_RenderText_Shaded(police, "Valeur Hypothécaire de la salle", couleur_texte, couleur_fond_texte);
	sprintf(texte_temp,"%d Fintz",int_prix);
	surf_texte[21] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);
	
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR, DETAIL_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR-2*DETAIL_EPAISSEUR, DETAIL_HAUTEUR-2*DETAIL_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 225, 255, 225));

	//Création de la surface du groupe
	surf_groupe=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR, DETAIL_GROUPE_HAUTEUR+2*DETAIL_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_groupe, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface du groupe
	surf_groupe_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR-2*DETAIL_EPAISSEUR, DETAIL_GROUPE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de la couleur du groupe
	SDL_FillRect(surf_groupe_fond, NULL, SDL_MapRGB(surf_ecran->format, couleur.rouge, couleur.vert, couleur.bleu));

	//Création de la surface de séparation
	surf_sep=SDL_CreateRGBSurface(SDL_HWSURFACE, (DETAIL_LARGEUR*9)/10, 3, 32, 0, 0, 0, 0);
	//Remplissage de noir
	SDL_FillRect(surf_sep, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//On modifie la position du fond
	position.x=DETAIL_EPAISSEUR;
	position.y=DETAIL_EPAISSEUR;
	//On colle le fond du groupe sur ce dernier
	SDL_BlitSurface(surf_groupe_fond, NULL, surf_groupe, &position);

	//On modifie la position du fond
	position.x=DETAIL_EPAISSEUR;
	position.y=DETAIL_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//On modifie la position du fond
	position.x=0;
	position.y=0;
	//On colle le groupe sur la case
	SDL_BlitSurface(surf_groupe, NULL, surf_case, &position);

	//Pour le texte contenu dans la coulerur du groupe
	for(i=0;i<2;i++)
	{
		//On centre la position du texte
		position.x=(DETAIL_LARGEUR-(*surf_texte[i]).w)/2;
		position.y=10+25*i;
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}

	//Modification de la position du texte pour le loyer du terrain nu
	position.x=20;
	position.y=105;
	//Affichage du loyer du terrain nu
	SDL_BlitSurface(surf_texte[2], NULL, surf_case, &position);
	
	//Pour les autres informations de la carte
	for(i=3;i<8;i++)
	{
		//On centre la position du texte
		position.x=95;
		position.y=55+25*i;
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}

	//Pour les informations sur les prix
	for(i=8;i<15;i++)
	{
		//On centre la position du texte
		position.x=DETAIL_LARGEUR-15-(surf_texte[i]->w);
		position.y=55+25*(i-7);
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}

	//Position du séparateur de texte
	position.x=DETAIL_LARGEUR/20;
	position.y=262;
	//Affichage du séparateur de texte
	SDL_BlitSurface(surf_sep, NULL, surf_case, &position);
	
	for(i=15;i<18;i++)
	{
		//On centre la position du texte
		position.x=(DETAIL_LARGEUR-(*surf_texte[i]).w)/2;
		position.y=90+20*(i-6);
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}

	//Position du séparateur de texte
	position.x=DETAIL_LARGEUR/20;
	position.y=337;
	//Affichage du séparateur de texte
	SDL_BlitSurface(surf_sep, NULL, surf_case, &position);

	//Position du texte
	position.x=10;
	position.y=345;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[18], NULL, surf_case, &position);
	
	//Position du texte
	position.x=(DETAIL_LARGEUR-10-(*surf_texte[19]).w);
	position.y=365;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[19], NULL, surf_case, &position);
	
	//Position du texte
	position.x=(DETAIL_LARGEUR-(*surf_texte[20]).w)/2;
	position.y=390;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[20], NULL, surf_case, &position);
	
	//Position du texte
	position.x=(DETAIL_LARGEUR-(*surf_texte[21]).w)/2;
	position.y=410;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[21], NULL, surf_case, &position);
			
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_groupe_fond);
	SDL_FreeSurface(surf_groupe);
	for(i=0;i<22;i++) SDL_FreeSurface(surf_texte[i]);
	
	return(surf_case);
}

SDL_Surface* creation_case_detail_lc(SDL_Surface* surf_ecran, int int_type)
{
	SDL_Surface* surf_case;
	surf_case=NULL;
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	SDL_Surface* surf_image;
	surf_image=NULL;
	SDL_Surface* surf_sep;
	surf_sep=NULL;
	SDL_Surface* surf_texte[14];
	char texte_temp[256];
	int i;
	
	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {225, 255, 225};

	//Position
	SDL_Rect position;
	
	switch(int_type)
	{
		case LC_WC:
			surf_image = IMG_Load("sdl/images/wc.png");
			strcpy(texte_temp,"W.C.");
			break;
		case LC_ASCENSEUR:
			surf_image = IMG_Load("sdl/images/ascenseur.png");
			strcpy(texte_temp,"Ascenseur");
			break;
		case LC_RU:
			surf_image = IMG_Load("sdl/images/ru.png");
			strcpy(texte_temp,"R.U.");
			break;
		case LC_PARKING:
			surf_image = IMG_Load("sdl/images/parking.png");
			strcpy(texte_temp,"Parking");
			break;
		default:
			break;
	}

	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 28);

	//Tire de la carte de propriété
	surf_texte[1] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);

	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);
		
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 20);
	
	//Ecriture des informations contenus dans le groupe
	surf_texte[0] = TTF_RenderText_Shaded(police, "Titre de propriété", couleur_texte, couleur_fond_texte);
	
	//Ecriture des textes sur les informations sur les loyers
	surf_texte[2] = TTF_RenderText_Shaded(police, "LOYER si vous avez :", couleur_texte, couleur_fond_texte);
	surf_texte[3] = TTF_RenderText_Shaded(police, "1 lieu commun", couleur_texte, couleur_fond_texte);
	surf_texte[4] = TTF_RenderText_Shaded(police, "2 lieux commun", couleur_texte, couleur_fond_texte);
	surf_texte[5] = TTF_RenderText_Shaded(police, "3 lieux commun", couleur_texte, couleur_fond_texte);
	surf_texte[6] = TTF_RenderText_Shaded(police, "4 lieux commun", couleur_texte, couleur_fond_texte);
	
	//Ecriture de la monnaie utilisé
	surf_texte[7] = TTF_RenderText_Shaded(police, "Fintz", couleur_texte, couleur_fond_texte);
	
	//Ecriture des différents prix
	for(i=0;i<4;i++)
	{
		sprintf(texte_temp,"%d",250*(i+1));
		surf_texte[8+i] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);
	}
	
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);
	
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 17);
	
	//Ecriture des informations sur l'achat d'un niveau et l'hypothèque
	surf_texte[12] = TTF_RenderText_Shaded(police, "Valeur Hypothécaire de la salle", couleur_texte, couleur_fond_texte);
	sprintf(texte_temp,"%d Fintz",1000);
	surf_texte[13] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);
	
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR, DETAIL_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR-2*DETAIL_EPAISSEUR, DETAIL_HAUTEUR-2*DETAIL_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 225, 255, 225));

	//Création de la surface de séparation
	surf_sep=SDL_CreateRGBSurface(SDL_HWSURFACE, (DETAIL_LARGEUR*9)/10, 3, 32, 0, 0, 0, 0);
	//Remplissage de noir
	SDL_FillRect(surf_sep, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));


	//On modifie la position du fond
	position.x=DETAIL_EPAISSEUR;
	position.y=DETAIL_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//Pour le titre
	for(i=0;i<2;i++)
	{
		//On centre la position du texte
		position.x=(DETAIL_LARGEUR-(*surf_texte[i]).w)/2;
		position.y=10+25*i;
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}

	//On centre la position de l'image
	position.x=(DETAIL_LARGEUR-(surf_image->w))/2;
	position.y=85;
	//On colle l'image sur la surface
	SDL_BlitSurface(surf_image, NULL, surf_case, &position);
		
	for(i=2;i<7;i++)
	{
		//Modification de la position du texte pour le loyer du terrain nu
		position.x=20;
		position.y=145+25*i;
		//Affichage du loyer du terrain nu
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}

	//Pour les informations sur les prix
	for(i=7;i<12;i++)
	{
		//On centre la position du texte
		position.x=DETAIL_LARGEUR-15-(surf_texte[i]->w);
		position.y=145+25*(i-5);
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}
	
	//Position du séparateur de texte
	position.x=DETAIL_LARGEUR/20;
	position.y=360;
	//Affichage du séparateur de texte
	SDL_BlitSurface(surf_sep, NULL, surf_case, &position);
	
	//Position du texte
	position.x=(DETAIL_LARGEUR-(*surf_texte[12]).w)/2;
	position.y=390;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[12], NULL, surf_case, &position);
	
	//Position du texte
	position.x=(DETAIL_LARGEUR-(*surf_texte[13]).w)/2;
	position.y=410;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[13], NULL, surf_case, &position);
			
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_image);
	for(i=0;i<14;i++) SDL_FreeSurface(surf_texte[i]);
	
	return(surf_case);
}

SDL_Surface* creation_case_detail_assoc(SDL_Surface* surf_ecran, int int_type)
{
	SDL_Surface* surf_case;
	surf_case=NULL;
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	SDL_Surface* surf_image;
	surf_image=NULL;
	SDL_Surface* surf_sep;
	surf_sep=NULL;
	SDL_Surface* surf_texte[10];
	char texte_temp[256];
	int i;
	
	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du fond du texte
	SDL_Color couleur_fond_texte = {225, 255, 225};

	//Position
	SDL_Rect position;
	
	switch(int_type)
	{
		case BDE:
			surf_image = IMG_Load("sdl/images/bureau_bde.png");
			strcpy(texte_temp,"B.D.E.");
			break;
		case BDS:
			surf_image = IMG_Load("sdl/images/bureau_bds.png");
			strcpy(texte_temp,"B.D.S.");
			break;
		default:
			break;
	}

	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 28);

	//Tire de la carte de propriété
	surf_texte[1] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);

	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);
		
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 20);
	
	//Ecriture des informations contenus dans le groupe
	surf_texte[0] = TTF_RenderText_Shaded(police, "Titre de propriété", couleur_texte, couleur_fond_texte);
			
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);
	
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 17);
	
	//Ecriture des textes sur les informations sur les loyers
	surf_texte[2] = TTF_RenderText_Shaded(police, "Si l'élève possède UN seul bureau", couleur_texte, couleur_fond_texte);
	surf_texte[3] = TTF_RenderText_Shaded(police, "d'association, le droit de passage est", couleur_texte, couleur_fond_texte);
	surf_texte[4] = TTF_RenderText_Shaded(police, "40 fois le montant indiqué par les dés", couleur_texte, couleur_fond_texte);
	
	//Ecriture des textes sur les informations sur les loyers
	surf_texte[5] = TTF_RenderText_Shaded(police, "Si l'élève possède les DEUX bureaux", couleur_texte, couleur_fond_texte);
	surf_texte[6] = TTF_RenderText_Shaded(police, "d'association, le droit de passage est", couleur_texte, couleur_fond_texte);
	surf_texte[7] = TTF_RenderText_Shaded(police, "100 fois le montant indiqué par les dés", couleur_texte, couleur_fond_texte);
	
	//Ecriture des informations sur l'achat d'un niveau et l'hypothèque
	surf_texte[8] = TTF_RenderText_Shaded(police, "Valeur Hypothécaire de la salle", couleur_texte, couleur_fond_texte);
	sprintf(texte_temp,"%d Fintz",750);
	surf_texte[9] = TTF_RenderText_Shaded(police, texte_temp, couleur_texte, couleur_fond_texte);
	
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR, DETAIL_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, DETAIL_LARGEUR-2*DETAIL_EPAISSEUR, DETAIL_HAUTEUR-2*DETAIL_EPAISSEUR, 32, 0, 0, 0, 0);
	//Remplissage de vert tapis
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 225, 255, 225));

	//Création de la surface de séparation
	surf_sep=SDL_CreateRGBSurface(SDL_HWSURFACE, (DETAIL_LARGEUR*9)/10, 3, 32, 0, 0, 0, 0);
	//Remplissage de noir
	SDL_FillRect(surf_sep, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));


	//On modifie la position du fond
	position.x=DETAIL_EPAISSEUR;
	position.y=DETAIL_EPAISSEUR;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//Pour le titre
	for(i=0;i<2;i++)
	{
		//On centre la position du texte
		position.x=(DETAIL_LARGEUR-(*surf_texte[i]).w)/2;
		position.y=10+25*i;
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}

	//On centre la position de l'image
	position.x=(DETAIL_LARGEUR-(surf_image->w))/2;
	position.y=85;
	//On colle l'image sur la surface
	SDL_BlitSurface(surf_image, NULL, surf_case, &position);
		
	for(i=2;i<5;i++)
	{
		//Modification de la position du texte pour le loyer du terrain nu
		position.x=(DETAIL_LARGEUR-(*surf_texte[i]).w)/2;
		position.y=140+20*i;
		//Affichage du loyer du terrain nu
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}
	
	//Position du séparateur de texte
	position.x=DETAIL_LARGEUR/20;
	position.y=260;
	//Affichage du séparateur de texte
	SDL_BlitSurface(surf_sep, NULL, surf_case, &position);

	//Pour les informations sur les prix
	for(i=5;i<8;i++)
	{
		//On centre la position du texte
		position.x=(DETAIL_LARGEUR-(*surf_texte[i]).w)/2;
		position.y=180+20*i;
		//On colle le texte sur la surface
		SDL_BlitSurface(surf_texte[i], NULL, surf_case, &position);
	}
	
	//Position du séparateur de texte
	position.x=DETAIL_LARGEUR/20;
	position.y=360;
	//Affichage du séparateur de texte
	SDL_BlitSurface(surf_sep, NULL, surf_case, &position);
	
	//Position du texte
	position.x=(DETAIL_LARGEUR-(*surf_texte[8]).w)/2;
	position.y=390;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[8], NULL, surf_case, &position);
	
	//Position du texte
	position.x=(DETAIL_LARGEUR-(*surf_texte[9]).w)/2;
	position.y=410;
	//On colle le texte sur la surface
	SDL_BlitSurface(surf_texte[9], NULL, surf_case, &position);
			
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_image);
	for(i=0;i<10;i++) SDL_FreeSurface(surf_texte[i]);
	
	return(surf_case);
}

SDL_Surface* creation_case_propriete(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte)
{
	//Surface de la case
	SDL_Surface* surf_case;
	surf_case=NULL;
	//Surface du fond
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	//Surface du texte
	SDL_Surface* surf_texte;
	surf_texte=NULL;
	
	//Image de la propriété
	struct_image* img_propriete;
	
	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {0, 0, 0};
	//Couleur du groupe
	SDL_Color couleur_groupe = {couleur.rouge,couleur.vert,couleur.bleu};

	//Position
	SDL_Rect position;
	
	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 17);

	//Ecriture du texte
	surf_texte = TTF_RenderText_Shaded(police, texte, couleur_texte, couleur_groupe);
	
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);

	//Création de la surface de la case
	surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, PROPRIETE_LARGEUR, PROPRIETE_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_case, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface de fond
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, PROPRIETE_LARGEUR-6, PROPRIETE_HAUTEUR-6, 32, 0, 0, 0, 0);
	//Remplissage de la couleur du groupe
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, couleur.rouge,couleur.vert,couleur.bleu));


	//On modifie la position du fond
	position.x=3;
	position.y=3;
	//On colle le fond sur la case
	SDL_BlitSurface(surf_fond, NULL, surf_case, &position);

	//Position du texte
	position.x=(PROPRIETE_LARGEUR-(surf_texte->w))/2;
	position.y=5;
	//Collage du texte sur la case
	SDL_BlitSurface(surf_texte, NULL, surf_case, &position);
			
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_texte);
	//On retourne la case
	return(surf_case);
}

void affich_image(SDL_Surface* surf_ecran, struct_image* img_image)
{
	//Affichage de l'image
	SDL_BlitSurface(img_image->surf_image, NULL, surf_ecran, &(img_image->position));
	
}

void affich_bouton(SDL_Surface* surf_ecran, struct_bouton* btn_bouton, bool bool_etat)
{
	//Si le bouton n'est pas survolé, il ne sera pas afficher avec la surbrillance
	if(bool_etat==false) SDL_BlitSurface(btn_bouton->surf_bouton[0], NULL, surf_ecran, &(btn_bouton->position));
	//Autrement il doit être en surbrillance
	else SDL_BlitSurface(btn_bouton->surf_bouton[1], NULL, surf_ecran, &(btn_bouton->position));
}

int affich_accueil(SDL_Surface* surf_ecran, struct_nom_joueur** page_nom_joueur)
{
	//Structure de l'image du logo
	struct_image* img_logo;
	
	//Structure du bouton quitter
	struct_bouton* btn_quitter;
	
	//Image du cache pour les pages
	struct_image* img_cache;
	
	//Valeur retourné indiquant l'action du joueur
	int int_retour;
	
	//Création du chache
	img_cache=creation_surface(surf_ecran,(ECRAN_LARGEUR-700)/2, ACCUEIL_TITRE_POS_Y, 700, ECRAN_HAUTEUR-ACCUEIL_TITRE_POS_Y-50, init_rvb_couleur(0, 0, 0));

	//Initialisation du logo
	img_logo=creation_image("eistiopoly_logo.png", (ECRAN_LARGEUR-900)/2, ACCUEIL_LOGO_POS_Y);
	
	//Initialisation du bouton quitter
	btn_quitter=creation_bouton("quitter.gif","quitter2.gif",ECRAN_LARGEUR-55,10);

	//Remplissage de noir pour faire le fond
	SDL_FillRect(surf_ecran, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));
	
	//Affichage du logo
	affich_image(surf_ecran, img_logo);
	
	//Affichage du bouton
	affich_bouton(surf_ecran, btn_quitter, false);

	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Attente d'action sur l'écran d'accueil
	int_retour=attente_action_accueil(surf_ecran, btn_quitter, img_cache, page_nom_joueur);
	
	//Destruction du bouton quitter
	destruction_bouton(btn_quitter);
	
	//Destruction de l'image du logo
	destruction_image(img_logo);
	
	//Destruction de l'image du cache
	destruction_image(img_cache);
	
	//Remplissage de noir pour faire le fond
	SDL_FillRect(surf_ecran, NULL, SDL_MapRGB(surf_ecran->format, 25, 25, 75));
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//On retourne la page des noms de joueurs contenant toutes les informations utiles au lancement du jeu
	return(int_retour);
}

void affich_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* page_nbre_joueur)
{
	//Affichage du titre de la page
	affich_image(surf_ecran, page_nbre_joueur->img_titre);
	//Affichage de la fleche droite
	affich_bouton(surf_ecran, page_nbre_joueur->btn_fleche_droite, false);
	//Affichage de la fleche gauche
	affich_bouton(surf_ecran, page_nbre_joueur->btn_fleche_gauche, false);
	//Affichage du nombre de joueur initial
	affich_image(surf_ecran, page_nbre_joueur->img_nombres[0]);
	//Affichage du bouton retour
	affich_bouton(surf_ecran, page_nbre_joueur->btn_retour, false);
	//Affichage du bouton valider
	affich_bouton(surf_ecran, page_nbre_joueur->btn_valider, false);
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
}

void affich_apropos(SDL_Surface* surf_ecran, struct_apropos* page_apropos)
{
	//Affichage du titre de la page
	affich_image(surf_ecran, page_apropos->img_titre);
	//Affichage du texte de l'apropos
	affich_image(surf_ecran, page_apropos->img_apropos);
	//Affichage du bouton retour
	affich_bouton(surf_ecran, page_apropos->btn_retour, false);
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
}

void affich_multi(SDL_Surface* surf_ecran, struct_multi* page_multi)
{
	//Affichage du titre de la page
	affich_image(surf_ecran, page_multi->img_titre);
	//Affichage du texte de l'multi
	affich_image(surf_ecran, page_multi->img_multi);
	//Affichage du bouton retour
	affich_bouton(surf_ecran, page_multi->btn_retour, false);
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
}

void affich_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* page_nom_joueur)
{
	//Variable de boucle
	int i;
	//Affichage du titre de la page
	affich_image(surf_ecran, page_nom_joueur->img_titre);
	//Affichage du curseur
	affich_image(surf_ecran, page_nom_joueur->img_curseur);
	cout << page_nom_joueur->int_nbre_joueur << endl;
	//Pour chacun des joueurs
	for(i=0;i<(page_nom_joueur->int_nbre_joueur);i++)
	{
		//Affichage des titres des champs
		affich_image(surf_ecran, page_nom_joueur->img_texte_noms[i]);
		//Modification de la position du champ
		image_set_position(page_nom_joueur->img_champ, CHAMP_POS_X, CHAMP_POS_Y+i*2*CHAMP_HAUTEUR);
		//Affichage du champ
		affich_image(surf_ecran, page_nom_joueur->img_champ);
	}
	//Affichage des champs de saisie
	affich_image(surf_ecran, page_nom_joueur->img_champ);
	//Affichage du bouton retour
	affich_bouton(surf_ecran, page_nom_joueur->btn_retour, false);
	//Affichage du bouton jouer
	affich_bouton(surf_ecran, page_nom_joueur->btn_jouer, false);
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
}

void affich_menu(SDL_Surface* surf_ecran, struct_menu* page_menu)
{
	//Variable de boucle
	int i;
	//Affichage du titre de la page
	affich_image(surf_ecran, page_menu->img_titre);
	//Affichage du premier item en surbrillance
	affich_bouton(surf_ecran, page_menu->btn_items[0], true);
	//Affichage de chacun des items du menu en normal
	for(i=1;i<5;i++) affich_bouton(surf_ecran, page_menu->btn_items[i], false);
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
}

void affich_case(SDL_Surface* surf_ecran, cases* pcase)
{
	//Surface de l'image cpi
	SDL_Surface* surf_image_cpi;
	surf_image_cpi=NULL;
	
	//Surface de l'image ingé
	SDL_Surface* surf_image_inge;
	surf_image_inge=NULL;
	
	//Couleur du groupe pour les cases salles
	rvb_couleur groupe_couleur[8];
	
	//Surface temporaire
	SDL_Surface* surf_temp=NULL;
	
	//Surface de la case temporaire
	SDL_Surface* surf_case;
	surf_case=NULL;

	//Position
	SDL_Rect position;
	
	//Niveau de la salle
	int int_niveau;
	
	//S'il s'agit d'une case salle
	if(pcase->int_type==SALLE && pcase->case_salle.int_niveau!=0)
	{
		//Initialisation du tableau des couleurs du groupe
		init_tab_rvb_couleur(groupe_couleur);
		//Initialisation des positions
		position.x=0;
		position.y=0;
		//Chargement de l'image cpi sur la surface temporaire
		surf_temp=IMG_Load("sdl/images/cpi.png");
		//Création de la surface du niveau cpi
		surf_image_cpi=SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 0);
		//Remplissage avec la couleur de fond du groupe
		SDL_FillRect(surf_image_cpi, NULL, SDL_MapRGB(surf_ecran->format, groupe_couleur[(pcase->case_salle.int_groupe)].rouge, groupe_couleur[(pcase->case_salle.int_groupe)].vert, groupe_couleur[(pcase->case_salle.int_groupe)].bleu));
		//Collage de l'image du niveau cpi
		SDL_BlitSurface(surf_temp, NULL, surf_image_cpi, &position);
		
		//Chargement de l'image ingé sur la surface temporaire
		surf_temp=IMG_Load("sdl/images/inge.png");
		//Création de la surface du niveau ingé
		surf_image_inge=SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 0);
		//Remplissage avec la couleur de fond du groupe
		SDL_FillRect(surf_image_inge, NULL, SDL_MapRGB(surf_ecran->format, groupe_couleur[(pcase->case_salle.int_groupe)].rouge, groupe_couleur[(pcase->case_salle.int_groupe)].vert, groupe_couleur[(pcase->case_salle.int_groupe)].bleu));
		//Collage de l'image du niveau ingé
		SDL_BlitSurface(surf_temp, NULL, surf_image_inge, &position);
	}
	
	
	//Création de la surface temporaire de la case en fonction de la position de la case
	if(pcase->int_type>=SP_APPARTEMENT && pcase->int_type<=SP_TABLEAU) surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_HAUTEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	else if(pcase->int_position==POSITION_GAUCHE || pcase->int_position==POSITION_DROITE) surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_HAUTEUR, CASE_LARGEUR, 32, 0, 0, 0, 0);
	else surf_case=SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_LARGEUR, CASE_HAUTEUR, 32, 0, 0, 0, 0);
	
	//Position à 0, 0
	position.x=0;
	position.y=0;
	//Collage de la case sur la surface case temporaire
	SDL_BlitSurface((*pcase).surf_image, NULL, surf_case, &position);
	
	//S'il s'agit d'une case salle qui a un niveau supérieur à zéro
	if(pcase->int_type==SALLE && pcase->case_salle.int_niveau!=0)
	{
	
		//On initalisation le niveau à 0
		int_niveau=1;
		
		if(pcase->case_salle.int_niveau<=2)
		{
			//Selon la position de la case
			switch(pcase->int_position)
			{
				case POSITION_HAUT:
					//On tourne l'image de 180 degré
					surf_image_cpi=rotation_180(surf_image_cpi);
					break;
				case POSITION_DROITE:
					//On tourne l'image de 90 degré
					surf_image_cpi=rotation_90(surf_image_cpi);
					break;
				case POSITION_GAUCHE:
					//On tourne l'image de 270 degré
					surf_image_cpi=rotation_270(surf_image_cpi);
					break;
				default:
					//On ne fait rien
					break;
			}
				
			//Tant que l'image à afficher fait partit du groupe cpi et tant que l'on a pas atteint le niveau de la salle
			while(int_niveau<=2 && int_niveau<=(pcase->case_salle.int_niveau))
			{
				switch(pcase->int_position)
				{
					case POSITION_HAUT:
						//On modifie la position du fond
						position.x=(CASE_EPAISSEUR+20*(int_niveau-1));
						position.y=CASE_HAUTEUR-CASE_EPAISSEUR-20;
						break;
					case POSITION_DROITE:
						//On modifie la position du fond
						position.x=CASE_EPAISSEUR;
						position.y=CASE_EPAISSEUR+20*(int_niveau-1);
						break;
					case POSITION_GAUCHE:
						//On modifie la position du fond
						position.x=CASE_HAUTEUR-CASE_EPAISSEUR-20;
						position.y=(CASE_EPAISSEUR+20*(int_niveau-1));
						break;
					default:
						//On modifie la position du fond
						position.x=CASE_EPAISSEUR+20*(int_niveau-1);
						position.y=CASE_EPAISSEUR;
						break;
				}
				//On colle le fond sur la case
				SDL_BlitSurface(surf_image_cpi, NULL, surf_case, &position);
				int_niveau++;
			}
		}
		else
		{
			//Selon la position de la case
			switch(pcase->int_position)
			{
				case POSITION_HAUT:
					//On tourne l'image de 180 degré
					surf_image_inge=rotation_180(surf_image_inge);
					break;
				case POSITION_DROITE:
					//On tourne l'image de 90 degré
					surf_image_inge=rotation_90(surf_image_inge);
					break;
				case POSITION_GAUCHE:
					//On tourne l'image de 270 degré
					surf_image_inge=rotation_270(surf_image_inge);
					break;
				default:
					//On ne fait rien
					break;
			}
			
			//Tant que l'image à afficher fait partit du groupe cpi et tant que l'on a pas atteint le niveau de la salle
			while(int_niveau<=3 && int_niveau<=(pcase->case_salle.int_niveau)-2)
			{
				switch(pcase->int_position)
				{
					case POSITION_HAUT:
						//On modifie la position du fond
						position.x=(CASE_EPAISSEUR+20*(int_niveau-1));
						position.y=CASE_HAUTEUR-CASE_EPAISSEUR-20;
						break;
					case POSITION_DROITE:
						//On modifie la position du fond
						position.x=CASE_EPAISSEUR;
						position.y=CASE_EPAISSEUR+20*(int_niveau-1);
						break;
					case POSITION_GAUCHE:
						//On modifie la position du fond
						position.x=CASE_HAUTEUR-CASE_EPAISSEUR-20;
						position.y=(CASE_EPAISSEUR+20*(int_niveau-1));
						break;
					default:
						//On modifie la position du fond
						position.x=CASE_EPAISSEUR+20*(int_niveau-1);
						position.y=CASE_EPAISSEUR;
						break;
				}
				//On colle le fond sur la case
				SDL_BlitSurface(surf_image_inge, NULL, surf_case, &position);
				int_niveau++;
			}
		}
	}

	//Position de la case sur l'écran
	position.x=(*pcase).rect_coordonnees.x;
	position.y=(*pcase).rect_coordonnees.y;
	
	//Affichage de la case
	SDL_BlitSurface(surf_case, NULL, surf_ecran, &position);
	
	//Libération des surfaces temporaire
	SDL_FreeSurface(surf_image_inge);
	SDL_FreeSurface(surf_image_cpi);
	SDL_FreeSurface(surf_case);
	SDL_FreeSurface(surf_temp);
}

/*void affich_case_detail(SDL_Surface* surf_ecran, cases* pcase)
{
	SDL_Rect position;
	position.x=POS_X_PLATEAU+CASE_HAUTEUR+(TAILLE_CENTRE-DETAIL_LARGEUR)/2;
	position.y=POS_Y_PLATEAU+CASE_HAUTEUR+(TAILLE_CENTRE-DETAIL_HAUTEUR)/2;
	SDL_BlitSurface(pcase->case_salle.img_detail, NULL, surf_ecran, &position); // Collage de la surface sur l'écran	
}*/

void affich_centre(SDL_Surface* surf_ecran, SDL_Surface* surf_centre)
{
	SDL_Rect position;
	position.x=POS_X_PLATEAU+CASE_HAUTEUR;
	position.y=POS_Y_PLATEAU+CASE_HAUTEUR;
	SDL_BlitSurface(surf_centre, NULL, surf_ecran, &position); // Collage de la surface sur l'écran	
}

void affich_panneau_menu(SDL_Surface* surf_ecran, struct_pnl_menu* pnl_menu)
{
	//Affichage du panneau
	affich_image(surf_ecran, pnl_menu->img_panneau);
	//Affichage du bouton quitter en mode normal
	affich_bouton(surf_ecran, pnl_menu->btn_quitter, false);
	//Affichage du bouton sauvegarder en mode normal
	affich_bouton(surf_ecran, pnl_menu->btn_sauvegarder, false);
}

void affich_panneau_joueur(SDL_Surface* surf_ecran, joueur* j_anneau_joueurs)
{
	SDL_Surface* surf_menu;
	SDL_Surface* surf_fond;
	SDL_Surface* surf_texte[5];
	
	SDL_Rect position_jeton;
	
	char str_temp[256];
	int i;

	SDL_Rect position;

	//Police d'écriture
	TTF_Font* police;
	police=NULL;

	//Couleur du texte
	SDL_Color couleur_texte = {86, 255, 86};
	SDL_Color couleur_valeur = {125, 225, 125};

	//Création de la surface du menu
	surf_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_JOUEUR_LARGEUR, PANNEAU_JOUEUR_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_menu, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface du fond du menu
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_JOUEUR_LARGEUR-6, PANNEAU_JOUEUR_HAUTEUR-6, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 125));

	//Ouverture de la police d'ecriture
	police = TTF_OpenFont("sdl/police/police2-bold.ttf", 17);

	//Ecriture du texte "nom du joueur"
	surf_texte[0] = TTF_RenderText_Blended(police, "Nom du joueur :", couleur_texte);

	//Ecriture du nom du joueur
	surf_texte[1] = TTF_RenderText_Blended(police, j_anneau_joueurs->str_nom, couleur_valeur);

	sprintf(str_temp,"%d Fintz",j_anneau_joueurs->int_argent);
	//Ecriture du texte "argent"
	surf_texte[2] = TTF_RenderText_Blended(police, "Argent :", couleur_texte);

	//Ecriture de la quantité d'argent du joueur
	surf_texte[3] = TTF_RenderText_Blended(police, str_temp, couleur_valeur);

	sprintf(str_temp,"Nombre de certificats : %d",j_anneau_joueurs->int_certificat);
	//Ecriture du nombre de certficat
	surf_texte[4] = TTF_RenderText_Blended(police, str_temp, couleur_texte);

	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);

	//on affiche l'image du jeton
	position_jeton.x=130;
	position_jeton.y=25;
	SDL_BlitSurface(j_anneau_joueurs->surf_image, NULL, surf_fond, &position_jeton);

	position.x=3;
	position.y=3;
	SDL_BlitSurface(surf_fond, NULL, surf_menu, &position);

	for(i=0;i<5;i++)
	{
		position.x=PANNEAU_JOUEUR_POS_X+5+(15*(i%2));
		position.y=PANNEAU_JOUEUR_POS_Y-95+25*i-5*(i%2);
		SDL_BlitSurface(surf_texte[i], NULL, surf_menu, &position);
	}

	position.x=PANNEAU_JOUEUR_POS_X;
	position.y=PANNEAU_JOUEUR_POS_Y;
	SDL_BlitSurface(surf_menu, NULL, surf_ecran, &position);
	
	SDL_Flip(surf_ecran);
	SDL_FreeSurface(surf_menu);
	SDL_FreeSurface(surf_fond);
	for(i=0;i<3;i++) SDL_FreeSurface(surf_texte[i]);
}

void affich_panneau_possessions(SDL_Surface* surf_ecran, joueur* j_anneau_joueurs)
{
	//Surface du panneau
	SDL_Surface* surf_menu;
	surf_menu=NULL;
	SDL_Surface* surf_fond;
	surf_fond=NULL;
	SDL_Surface* surf_texte;
	surf_texte=NULL;
	SDL_Rect position;
	SDL_Surface* surf_propriete;
	surf_propriete=NULL;
	//Police d'écriture
	TTF_Font* police;
	police=NULL;
	possession* propriete;
	int nombre_propriete;
	int propriete_actuel;
	SDL_Color couleur_texte = {86, 255, 86};
	propriete=j_anneau_joueurs->propriete;
	propriete_actuel=0;
	nombre_propriete=0;
	
	if(!propriete)
	{
		//Création de la surface du menu
		surf_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_POSSESSION_LARGEUR, PANNEAU_POSSESSION_HAUTEUR, 32, 0, 0, 0, 0);
		//Remplissage de noir pour faire le cadre
		SDL_FillRect(surf_menu, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

		//Création de la surface du fond du menu
		surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_POSSESSION_LARGEUR-6, PANNEAU_POSSESSION_HAUTEUR-6, 32, 0, 0, 0, 0);
		//Remplissage de noir pour faire le cadre
		SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 125));

		//Ouverture de la police d'ecriture
		police = TTF_OpenFont("sdl/police/police2-bold.ttf", 17);

		//Ecriture du texte "nom du joueur"
		surf_texte = TTF_RenderText_Blended(police, "Aucun titre de propriété.", couleur_texte);

		//Fermeture de la police d'ecriture
		TTF_CloseFont(police);
		
		position.x=3;
		position.y=3;
		SDL_BlitSurface(surf_fond, NULL, surf_menu, &position);
	
	}
	else
	{
		//Pour chaque propriete
		while(propriete)
		{
			//On ajoute 1 au nombre de propriété
			nombre_propriete++;
			//On passe à la propriété suivante
			propriete=propriete->suivant;
		}
		//Création de la surface du panneau
		surf_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_POSSESSION_LARGEUR, 40+((PROPRIETE_HAUTEUR+5)*nombre_propriete), 32, 0, 0, 0, 0);
		//Remplissage de noir pour faire le cadre
		SDL_FillRect(surf_menu, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

		//Création de la surface du fond du panneau
		surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_POSSESSION_LARGEUR-6, 40+((PROPRIETE_HAUTEUR+5)*nombre_propriete)-6, 32, 0, 0, 0, 0);
		//Remplissage de noir pour faire le cadre
		SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 125));

		//Ouverture de la police d'ecriture
		police = TTF_OpenFont("sdl/police/police2-bold.ttf", 17);

		//Ecriture du texte
		surf_texte = TTF_RenderText_Blended(police, "Propriété de l'élève :", couleur_texte);

		//Fermeture de la police d'ecriture
		TTF_CloseFont(police);
		
		//Position du fond sur le menu
		position.x=3;
		position.y=3;
		//Collage du fond sur le menu
		SDL_BlitSurface(surf_fond, NULL, surf_menu, &position);
	
		//Retour à l'entete de la liste des propriétés du joueur
		propriete=j_anneau_joueurs->propriete;
		
		//tant qu'on a des propriétés
		while(propriete)
		{
			//Chargement de la surface en fonction de la propriété
			if(propriete->propriete->int_type==SALLE) surf_propriete=propriete->propriete->case_salle.surf_propriete;
			else if(propriete->propriete->int_type==BDE || propriete->propriete->int_type==BDS) surf_propriete=propriete->propriete->case_association.surf_propriete;
			else surf_propriete=propriete->propriete->case_lieu_commun.surf_propriete;

			//Position de la propriété dans le menu
			position.x=10;
			position.y=35+propriete_actuel*(PROPRIETE_HAUTEUR+5);

			//Affichage de la propriété
			SDL_BlitSurface(surf_propriete, NULL, surf_menu, &position);
			//Passage à la propriété suivante
			propriete=propriete->suivant;
			//Incrémentation du nombre de propriété actuel
			propriete_actuel++;
		}
	}

	//Position du texte sur le menu
	position.x=20;
	position.y=10;
	//Collage du texte sur le menu
	SDL_BlitSurface(surf_texte, NULL, surf_menu, &position);
	
	//Position du panneau à l'écran
	position.x=PANNEAU_POSSESSION_POS_X;
	position.y=PANNEAU_POSSESSION_POS_Y;
	//Affichage du panneau à l'écran
	SDL_BlitSurface(surf_menu, NULL, surf_ecran, &position);
		
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_menu);
	SDL_FreeSurface(surf_fond);
	SDL_FreeSurface(surf_texte);
}

void affich_possessions_cache(SDL_Surface* surf_ecran)
{
	//Surface du cache
	SDL_Surface* surf_cache;
	surf_cache=NULL;
	
	//Position
	SDL_Rect position;
	
	//Création de la surface du menu
	surf_cache=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_POSSESSION_LARGEUR, ECRAN_HAUTEUR-PANNEAU_POSSESSION_POS_Y, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_cache, NULL, SDL_MapRGB(surf_ecran->format, 25, 25, 75));
	
	//Position du cache
	position.x=PANNEAU_POSSESSION_POS_X;
	position.y=PANNEAU_POSSESSION_POS_Y;
	
	//Collage du cache sur l'écran
	SDL_BlitSurface(surf_cache, NULL, surf_ecran, &position);
	
}

void affich_panneau_des_bouton(SDL_Surface* surf_ecran, int int_image)
{
	//Surface du panneau
	SDL_Surface* surf_menu;
	//Surface du fond
	SDL_Surface* surf_fond;
	//Surface des boutons lancer dés
	SDL_Surface* surf_bouton[2];
	//Position
	SDL_Rect position;
	
	int i;

	//Création de la surface du menu
	surf_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_DES_LARGEUR, PANNEAU_DES_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_menu, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface du fond du menu
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_DES_LARGEUR-6, PANNEAU_DES_HAUTEUR-6, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 125));

	//Chargement des images bes boutons
	surf_bouton[0]=IMG_Load("sdl/images/lancer.gif");
	surf_bouton[1]=IMG_Load("sdl/images/lancer2.gif");

	//Position du fond sur le panneau
	position.x=3;
	position.y=3;
	//Collage du fond sur le panneau
	SDL_BlitSurface(surf_fond, NULL, surf_menu, &position);

	//Position du bouton sur le panneau
	position.x=(PANNEAU_DES_LARGEUR-surf_bouton[0]->w)/2;
	position.y=(PANNEAU_DES_HAUTEUR-surf_bouton[0]->h)/2;
	//Collage du bouton sur le panneau
	SDL_BlitSurface(surf_bouton[int_image], NULL, surf_menu, &position);

	//Position du panneau sur l'écran
	position.x=PANNEAU_DES_POS_X;
	position.y=PANNEAU_DES_POS_Y;
	//Affichage du panneau
	SDL_BlitSurface(surf_menu, NULL, surf_ecran, &position);
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_menu);
	SDL_FreeSurface(surf_fond);
	for(i=0;i<2;i++) SDL_FreeSurface(surf_bouton[i]);
}

SDL_Surface** creation_des(void)
{
	//Surface du dé
	SDL_Surface** surf_des;
	if((surf_des= new SDL_Surface*[6])==NULL) cout<<"Fesse en boite"<<endl;
	//Création de la surface de l'objet n°1
	surf_des[0]=IMG_Load("sdl/images/un.png");
	surf_des[1]=IMG_Load("sdl/images/deux.png");
	surf_des[2]=IMG_Load("sdl/images/trois.png");
	surf_des[3]=IMG_Load("sdl/images/quatre.png");
	surf_des[4]=IMG_Load("sdl/images/cinq.png");
	surf_des[5]=IMG_Load("sdl/images/six.png");
	//On retourne la surface du dé
	return(surf_des);
}

void destruction_des(SDL_Surface** surf_des)
{
	int i;
	//Libération des surfaces des dés
	for(i=0;i<5;i++) SDL_FreeSurface(surf_des[i]);
	//Libération de la mémoire
	delete(surf_des);
}

void affich_panneau_fdt(SDL_Surface* surf_ecran, struct_pnl_fdt* pnl_fdt, bool bool_etat)
{
	//Affichage du fond du panneau
	affich_image(surf_ecran, pnl_fdt->img_panneau);
	//Selon l'état (true-> bouton, false-> texte)
	if(bool_etat) affich_bouton(surf_ecran, pnl_fdt->btn_finir, false);
	else affich_image(surf_ecran, pnl_fdt->img_message);
}

void affich_panneau_des(SDL_Surface* surf_ecran, SDL_Surface** surf_des, int int_de1, int int_de2)
{
	//Surface du menu
	SDL_Surface* surf_menu;
	//Surface du fond
	SDL_Surface* surf_fond;

	//Position
	SDL_Rect position;

	//Création de la surface du menu
	surf_menu=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_DES_LARGEUR, PANNEAU_DES_HAUTEUR, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_menu, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 0));

	//Création de la surface du fond du menu
	surf_fond=SDL_CreateRGBSurface(SDL_HWSURFACE, PANNEAU_DES_LARGEUR-6, PANNEAU_DES_HAUTEUR-6, 32, 0, 0, 0, 0);
	//Remplissage de noir pour faire le cadre
	SDL_FillRect(surf_fond, NULL, SDL_MapRGB(surf_ecran->format, 0, 0, 125));

	//Position du fond
	position.x=3;
	position.y=3;
	//Affichage du fond
	SDL_BlitSurface(surf_fond, NULL, surf_menu, &position);

	//Position du premier dé
	position.x=40;
	position.y=(PANNEAU_DES_HAUTEUR-surf_des[0]->h)/2;
	//Affichage du premier dé
	SDL_BlitSurface(surf_des[int_de1-1], NULL, surf_menu, &position);
	
	//Position du second dé
	position.x=130;
	position.y=(PANNEAU_DES_HAUTEUR-surf_des[0]->h)/2;
	//Affichage du second dé
	SDL_BlitSurface(surf_des[int_de2-1], NULL, surf_menu, &position);

	//Position du menu
	position.x=PANNEAU_DES_POS_X;
	position.y=PANNEAU_DES_POS_Y;
	//Affichage du menu
	SDL_BlitSurface(surf_menu, NULL, surf_ecran, &position);
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Libération des surfaces temporaires
	SDL_FreeSurface(surf_menu);
	SDL_FreeSurface(surf_fond);
}

void affich_joueur_depart (SDL_Surface* surf_ecran, cases** plateau,joueur* j_anneau_joueurs, int nombre_joueur)
{
	//pour chaque joueurs
	for (int i=0;i<nombre_joueur;i++)
	{
		//on l'affiche sur la case
		affich_joueur(surf_ecran,j_anneau_joueurs,i, plateau[j_anneau_joueurs->int_position]);
		
		//on passe au joueur suivant
		j_anneau_joueurs=j_anneau_joueurs->pjoueur_suivant;
	}
	//on depart au premier joueur pour que le jeu puisse commencer avec
	j_anneau_joueurs=j_anneau_joueurs->pjoueur_suivant;
}

void affich_validation_propriete(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases* pcase, joueur* pj_joueur, int int_type_action)
{
	//Variable de boucle
	int i;

	//Retour de la fonction d'attente d'action sur le message
	int int_retour;
	
	//Structure du message de propriété
	struct_msg_propriete* msg_propriete;
	
	//Initialisation du message de propriété
	msg_propriete=initialisation_msg_propriete(surf_ecran, pcase, int_type_action);

	//Affichage du message de propriété
	affich_image(surf_ecran, msg_propriete->img_propriete);
	
	//Affichage des boutons
	for(i=0;i<(msg_propriete->int_nbre_bouton);i++) affich_bouton(surf_ecran, msg_propriete->btn_boutons[i], false);
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Attente d'action de la part de l'utilisateur
	int_retour=attente_action_msg_propriete(surf_ecran, msg_propriete);
	
	//Traitement de l'action de l'utilisateur
	traitement_msg_propriete(pcase, pj_joueur, int_retour, int_type_action);
	
	//Réaffichage du centre
	affich_centre(surf_ecran,surf_centre);
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Destruction du message
	destruction_msg_propriete(msg_propriete);
}


int affich_message(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, char* titre, char* message, int int_type_message)
{
	//Variable de boucle
	int i;
	//Structure du message
	struct_message* msg_message;
	//Retour de la fonction d'attente d'action sur le message
	int int_retour;
	//Initialisation du message
	msg_message=initialisation_message(surf_ecran, titre, message, int_type_message);
	
	//Affichage du message
	affich_image(surf_ecran, msg_message->img_message);
	
	//Affichage des boutons
	for(i=0;i<(msg_message->int_nbre_bouton);i++) affich_bouton(surf_ecran, msg_message->btn_boutons[i], false);
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Attente d'action de la part de l'utilisateur
	int_retour=attente_action_message(surf_ecran, msg_message);
	
	//Réaffichage du centre
	affich_centre(surf_ecran,surf_centre);
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Destruction du message
	destruction_message(msg_message);
	
	//On retourne l'action effectuer par l'utilisateur
	return(int_retour);
}

void affich_msg_info(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, char* titre, char* message)
{
	//Structure du message
	struct_image* img_info;

	//Initialisation du message
	img_info=initialisation_msg_info(surf_ecran, titre, message);
	
	//Affichage du message
	affich_image(surf_ecran, img_info);
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Timer d'attente
	usleep(MSG_INFO_TIME);
	
	//Réaffichage du centre
	affich_centre(surf_ecran,surf_centre);
	
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	
	//Destruction de l'image du message d'information
	destruction_image(img_info);
}
