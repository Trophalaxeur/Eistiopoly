/*!
  \file interaction.c
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief code source des fonctions gérant l'interaction avec le joueur
  \date 09/01/2006
  \version 1.0
*/

#include "interaction.h"

int attente_clic(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur,cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16], struct_pnl_menu* pnl_menu, struct_pnl_fdt* pnl_fdt)
{
	//Variable de boucle
	int continuer;
	//-1 fonctionnement normal, 0 quitter le jeu, 1 tour du joueur terminé
	continuer=-1;
	//Postion du clic
	SDL_Rect position_clic;
	//Etat des boutons (false = normal et true =  surbrillance)
	bool bool_bouton_etat;
	//Mode par défaut
	bool_bouton_etat=false;
	//Variable d'état des dés
	int int_lancer;
	//1 si lancé, 0 autrement
	int_lancer=0;
	//Evénement sdl
    SDL_Event event;
    //Nombre tiré par les dés
    int int_nb_tire;
    //Nombre de propriété du joueur
    int int_nombre_propriete;
    //Action possible
    int int_action;
    //Case temporaire
    cases* pcase;
    //Position du joueur
    int int_position;
    
    //Calcul du nombre de propriété du joueur
	int_nombre_propriete=nombre_propriete(pj_joueur);
	
    //Tant que le joueur n'a pas quitter ou que le tour du joueur n'est pas terminé
    while (continuer==-1)
    {
    	//On attend un événement
        SDL_WaitEvent(&event);
        //Selon l'événement
        switch(event.type)
        {
			//S'il s'agit d'un appui sur une touche
			case SDL_KEYDOWN:
				//Selon la touche
				switch(event.key.keysym.sym)
				{
					//Echap
					case SDLK_ESCAPE:
						//On quitte le prgm
						continuer = 0;
						break;
					//Barre d'espace
					case SDLK_SPACE:
						//Si le joueur a lancé les dés
						if(int_lancer==1)
						{
							//Il s'agit d'une fin de tour
							continuer=1;
						}
						//Sinon, on lance les dés
						else
						{
							//on verifie que le joueur ne soit pas en prison
							if (pj_joueur->bool_laurence)
							{
								traitement_bureau_laurence(surf_ecran, surf_centre, plateau, pj_joueur, bureau_de_krystel, bureau_de_nadege);
							}
							else
							{
								//On lance les dés
								int_nb_tire=lancer_des(surf_ecran,surf_centre,pj_joueur, plateau);
								//On appelle la fonction traitement s'il n'a pas était envoyé en prison
								if (!pj_joueur->bool_laurence)
								{
									avancer_jeton (surf_ecran, surf_centre, int_nb_tire,pj_joueur,plateau,bureau_de_krystel,bureau_de_nadege);
								}
								
								//Affichage du panneau contenant les informations joueurs
								affich_panneau_possessions(surf_ecran,pj_joueur);
							}
							//Affichage du panneau contenant les informations joueurs
							affich_panneau_joueur(surf_ecran,pj_joueur);
							//Le joueur a lancé les dés
							int_lancer=1;
							//On affiche le panneau fin de tour
							affich_panneau_fdt(surf_ecran, pnl_fdt, true);
							//Mise à jour de l'écran
							SDL_Flip(surf_ecran);
						}
						break;
					//Pour toutes les autres touches
					default:
						//On fait rien...
						break;
				}
				break;
			//En cas de mouvement de la souris
			case SDL_MOUSEMOTION:
				//On sauvegarde les nouvelles coordonnées de la souris
				position_clic.x=event.button.x;
				position_clic.y=event.button.y;
				//Si la souris passe sur le bouton de fin de tour
				if(int_lancer==1 && event.motion.x>(bouton_get_x(pnl_fdt->btn_finir)) && event.motion.x<(bouton_get_x(pnl_fdt->btn_finir)+bouton_get_w(pnl_fdt->btn_finir))
				&& event.motion.y>(bouton_get_y(pnl_fdt->btn_finir)) && event.motion.y<(bouton_get_y(pnl_fdt->btn_finir)+bouton_get_h(pnl_fdt->btn_finir)))
				{
					//On réaffiche le bouton fin de tour en surbrillance
					affich_bouton(surf_ecran, pnl_fdt->btn_finir, true);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le bouton est en surbrillance
					bool_bouton_etat=true;
				}
				//Si le joueur passe la souris sur le bouton lancer dés
				else if(position_clic.x>PANNEAU_DES_POS_X && position_clic.x<(PANNEAU_DES_POS_X+PANNEAU_DES_LARGEUR)
				&& position_clic.y>PANNEAU_DES_POS_Y && position_clic.y<(PANNEAU_DES_POS_Y+PANNEAU_DES_HAUTEUR) && int_lancer==0)
				{
					//On affiche le bouton fin de tour en normal (si le joueur à déjà lancé)
					if(int_lancer==1) affich_bouton(surf_ecran, pnl_fdt->btn_finir, false);
					//On réaffiche le panneau avec le bouton lancer dés en surbrillance
					if(bool_bouton_etat==false) affich_panneau_des_bouton(surf_ecran,1);
					//L'un des boutons est en surbrillance
					bool_bouton_etat=true;
				}
				//Si le joueur survole sur l'un des  boutons de commande (coin supérieur gauche)
				else if(position_clic.x>PANNEAU_MENU_POS_X && position_clic.x<(PANNEAU_MENU_POS_X+PANNEAU_MENU_LARGEUR)
				&& position_clic.y>PANNEAU_MENU_POS_Y && position_clic.y<(PANNEAU_MENU_POS_Y+PANNEAU_MENU_HAUTEUR))
				{
					//On affiche le bouton fin de tour en normal (si le joueur a déjà lancé)
					if(int_lancer==1) affich_bouton(surf_ecran, pnl_fdt->btn_finir, false);
					
					//S'il s'agit du bouton quitter
					if(position_clic.x>(bouton_get_x(pnl_menu->btn_quitter)) && position_clic.x<(bouton_get_x(pnl_menu->btn_quitter)+bouton_get_w(pnl_menu->btn_quitter))
					&& position_clic.y>(bouton_get_y(pnl_menu->btn_quitter)) && position_clic.y<(bouton_get_y(pnl_menu->btn_quitter)+bouton_get_h(pnl_menu->btn_quitter)))
					{
						//Affichage du bouton quitter en surbrillance
						affich_bouton(surf_ecran, pnl_menu->btn_quitter, true);
						//Affichage du bouton sauvegarder en normal
						affich_bouton(surf_ecran, pnl_menu->btn_sauvegarder, false);
						//Mise à jour de l'écran
						SDL_Flip(surf_ecran);
					}
					//S'il s'agit du bouton sauvegarder
					else if(position_clic.x>(bouton_get_x(pnl_menu->btn_sauvegarder)) && position_clic.x<(bouton_get_x(pnl_menu->btn_sauvegarder)+bouton_get_w(pnl_menu->btn_sauvegarder))
					&& position_clic.y>(bouton_get_y(pnl_menu->btn_sauvegarder)) && position_clic.y<(bouton_get_y(pnl_menu->btn_sauvegarder)+bouton_get_h(pnl_menu->btn_sauvegarder)))
					{
						//Affichage du bouton sauvegarder en surbrillance
						affich_bouton(surf_ecran, pnl_menu->btn_sauvegarder, true);
						//Affichage du bouton quitter en normal
						affich_bouton(surf_ecran, pnl_menu->btn_quitter, false);
						//Mise à jour de l'écran
						SDL_Flip(surf_ecran);
					}
					else
					{
						//Affichage du bouton sauvegarder en normal
						affich_bouton(surf_ecran, pnl_menu->btn_sauvegarder, false);
						//Affichage du bouton quitter en normal
						affich_bouton(surf_ecran, pnl_menu->btn_quitter, false);
						//Mise à jour de l'écran
						SDL_Flip(surf_ecran);
					}
				}
				//Autrement, si l'un des boutons est en surbrillance
				else if(bool_bouton_etat==true)
				{
					//Affichage du bouton finir le tour en normal si le joueur à déjà lancé
					if(int_lancer==1) affich_bouton(surf_ecran, pnl_fdt->btn_finir, false);
					//Affichage du bouton quitter du panneau menu en normal
					affich_bouton(surf_ecran, pnl_menu->btn_quitter, false);
					//Affichage du bouton sauvegarder du panneau menu en normal
					affich_bouton(surf_ecran, pnl_menu->btn_sauvegarder, false);
					//On réaffiche le panneau avec le bouton lancer dés par défaut
					if(int_lancer==0) affich_panneau_des_bouton(surf_ecran,0);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Tout les boutons ne sont plus en surbrillance
					bool_bouton_etat=false;
				}
				
				break;
			//En cas de clic
			case SDL_MOUSEBUTTONUP:
				//Sauvegarde des coordonnées du clic
				position_clic.x=event.button.x;
				position_clic.y=event.button.y;
				//Si le joueur a cliqué sur le bouton lancer dés
				if(position_clic.x>PANNEAU_DES_POS_X && position_clic.x<(PANNEAU_DES_POS_X+PANNEAU_DES_LARGEUR)
				&& position_clic.y>PANNEAU_DES_POS_Y && position_clic.y<(PANNEAU_DES_POS_Y+PANNEAU_DES_HAUTEUR) && int_lancer==0)
				{
					//on verifie que le joueur ne soit pas en prison
					if (pj_joueur->bool_laurence)
					{
						traitement_bureau_laurence(surf_ecran, surf_centre, plateau, pj_joueur, bureau_de_krystel, bureau_de_nadege);
					}
					else
					{
						//On lance les dés
						int_nb_tire=lancer_des(surf_ecran,surf_centre,pj_joueur, plateau);
						//On appelle la fonction traitement s'il n'a pas était envoyé en prison
						if (!pj_joueur->bool_laurence)
						{
							avancer_jeton (surf_ecran, surf_centre, int_nb_tire,pj_joueur,plateau,bureau_de_krystel,bureau_de_nadege);
						}
						
						//Affichage du panneau contenant les informations joueurs
						affich_panneau_possessions(surf_ecran,pj_joueur);
					}
					//Affichage du panneau contenant les informations joueurs
					affich_panneau_joueur(surf_ecran,pj_joueur);
					//Le joueur a lancé les dés
					int_lancer=1;
					//On affiche le panneau fin de tour
					affich_panneau_fdt(surf_ecran, pnl_fdt, true);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);

				}
				//Si le joueur clic sur l'un des  boutons de commande (coin supérieur gauche)
				else if(position_clic.x>PANNEAU_MENU_POS_X && position_clic.x<(PANNEAU_MENU_POS_X+PANNEAU_MENU_LARGEUR)
				&& position_clic.y>PANNEAU_MENU_POS_Y && position_clic.y<(PANNEAU_MENU_POS_Y+PANNEAU_MENU_HAUTEUR))
				{
					//S'il s'agit du bouton quitter
					if(position_clic.x>(bouton_get_x(pnl_menu->btn_quitter)) && position_clic.x<(bouton_get_x(pnl_menu->btn_quitter)+bouton_get_w(pnl_menu->btn_quitter))
					&& position_clic.y>(bouton_get_y(pnl_menu->btn_quitter)) && position_clic.y<(bouton_get_y(pnl_menu->btn_quitter)+bouton_get_h(pnl_menu->btn_quitter)))
					{
						//On quitte le prgm
						continuer = 0;
					}
					//S'il s'agit du bouton sauvegarder
					else if(position_clic.x>(bouton_get_x(pnl_menu->btn_sauvegarder)) && position_clic.x<(bouton_get_x(pnl_menu->btn_sauvegarder)+bouton_get_w(pnl_menu->btn_sauvegarder))
					&& position_clic.y>(bouton_get_y(pnl_menu->btn_sauvegarder)) && position_clic.y<(bouton_get_y(pnl_menu->btn_sauvegarder)+bouton_get_h(pnl_menu->btn_sauvegarder)))
					{
						sauvegarde(plateau, pj_joueur);
						affich_message(surf_ecran, surf_centre, "Sauvegarde", "La sauvegarde à été effectuée avec un très grand succès ! Toutes nos félicitations. (Il ne peut y avoir qu'un seul fichier de sauvegarde. Toute nouvelle sauvegarde écrase la précédente.)",MESSAGE_NORMAL);
					}
				}
				//Si le joueur a cliqué sur le bouton de fin de tour
				else if(int_lancer==1 && event.motion.x>(bouton_get_x(pnl_fdt->btn_finir)) && event.motion.x<(bouton_get_x(pnl_fdt->btn_finir)+bouton_get_w(pnl_fdt->btn_finir))
				&& event.motion.y>(bouton_get_y(pnl_fdt->btn_finir)) && event.motion.y<(bouton_get_y(pnl_fdt->btn_finir)+bouton_get_h(pnl_fdt->btn_finir)))
				{
					//On arrete la boucle et on passe au joueur suivant
					continuer=1;
					//Affiche du bouton finir en normal
					affich_bouton(surf_ecran, pnl_fdt->btn_finir, false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
				}
				//Si le joueur a cliqué sur le panneau d'affichage des propriétés
				else if(pj_joueur->propriete!=NULL && position_clic.x>PANNEAU_POSSESSION_POS_X && position_clic.x<(PANNEAU_POSSESSION_POS_X+PANNEAU_POSSESSION_LARGEUR)
				&& position_clic.y>PANNEAU_POSSESSION_POS_Y && position_clic.y<(PANNEAU_POSSESSION_POS_Y+(40+((PROPRIETE_HAUTEUR+5)*int_nombre_propriete))))// && int_lancer==1)
				{
					int_action=action_possible(plateau,(position_clic.y-PANNEAU_POSSESSION_POS_Y-40)/(PROPRIETE_HAUTEUR+5), pj_joueur, CLICK_CASE, 0);
					//On affiche la propriété sur laquelle il a cliqué
					affich_validation_propriete(surf_ecran, surf_centre, pcase=int_to_cases((position_clic.y-PANNEAU_POSSESSION_POS_Y-40)/(PROPRIETE_HAUTEUR+5), pj_joueur), pj_joueur, int_action);
					//Affichage du panneau contenant les informations joueurs
					affich_panneau_possessions(surf_ecran,pj_joueur);
					//Affichage du panneau contenant les informations joueurs
					affich_panneau_joueur(surf_ecran,pj_joueur);
					//on réactualise la case ou se trouve le joueur afin qu'il efface le jeton
					affich_case(surf_ecran,pcase);
					//on compte le nombre de personne sur la case ou doit être afficher le joueur actuel
					int_position=nombre_joueur_case(pj_joueur);
					//on affiche le joueur sur la case s'il se trouve dessus
					if(plateau[pj_joueur->int_position]==pcase) affich_joueur(surf_ecran, pj_joueur,int_position+1, pcase);
					//Calcul du nouveau nombre de propriété du joueur
					int_nombre_propriete=nombre_propriete(pj_joueur);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
				}
				break;
			//Pour tout les autres événements
			default:
				//On ne fait rien...
				break;
        }
        //On vide la liste des événements en attente
		while(SDL_PollEvent(&event));
    }
    
    //Renvoit de la dernière action du joueur
	return(continuer);
}

int attente_action_accueil(SDL_Surface* surf_ecran, struct_bouton* btn_quitter, struct_image* img_cache, struct_nom_joueur** info_nom_joueur)
{
	//Structure de la page du nombre de joueur
	struct_nbre_joueur* page_nbre_joueur;
	
	//Structure de la page du menu principal
	struct_menu* page_menu;
	
	//Structure de la page des noms des joueurs
	struct_nom_joueur* page_nom_joueur;
	
	//Structure de la page apropos
	struct_apropos* page_apropos;
	
	//Structure de la page multijoueur
	struct_multi* page_multi;
	
	//Page en cours de visualisation
	int page_actuel;
	page_actuel=PAGE_MENU;
	
	//Valeur de retour des fonctions
	int int_retour;
	
	//Variable de boucle
	int continuer;
	continuer=MSG_RUN;
	
	//Booléen d'état des boutons
	bool bool_bouton_etat;
	//Par défault aucun bouton n'est en surbrillance
	bool_bouton_etat=false;
	
	//Booléen d'état du bouton quitter
	bool bool_btn_quit_etat;
	//Par défault le bouton quitter n'est en surbrillance
	bool_btn_quit_etat=false;
	
	//Booléen d'état des fichiers de sauvegarde
	bool bool_etat_fichier;
	//Par défault, il ne sont pas lisible par le programme
	bool_etat_fichier=false;
		
	//Evenement sdl
	SDL_Event event;
	
	//Création de la page du nombre de joueur
	page_nbre_joueur=init_struct_nbre_joueur(surf_ecran);
	
	//Création de la page du menu
	page_menu=init_struct_menu(surf_ecran);
	
	//Création de la page apropos
	page_apropos=initialisation_apropos(surf_ecran);
	
	//Création de la page multijoueur
	page_multi=initialisation_multi(surf_ecran);
	
	//Test de l'existence des fichiers de sauvegarde
	if(is_readable("sauvegarde_joueur.txt") && is_readable("sauvegarde_plateau.txt")) bool_etat_fichier=1;
	
	//On affiche la première page
	affich_menu(surf_ecran, page_menu);
	
	//Tant que le joueur n'a pas quitté ou configurer complétement la partie
	while(continuer==MSG_RUN)
	{
		//On vide la liste des événements en attente
		while(SDL_PollEvent(&event));
		
		//On attend un événement
		SDL_WaitEvent(&event);
		//Selon l'événement
		switch(event.type)
		{
			//En cas de pression sur une touche
			case SDL_KEYDOWN:
					//Selon la page en cours de visualisation
					switch(page_actuel)
					{
						//Dans le cas du menu principal
						case PAGE_MENU:
							if((int_retour=gestion_clavier_menu(surf_ecran, page_menu, event.key.keysym.sym))!=MSG_NULL)
							{
								switch(page_menu->int_select)
								{
									//Pour quitter
									case 4:
										continuer=MSG_QUITTER;
										break;
									//Pour une nouvelle partie
									case 0:
										//On change la page actuelle
										page_actuel=PAGE_NBRE_JOUEUR;
										//Initialisation du nombre de joueur par défault
										page_nbre_joueur->int_select=0;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//On affiche la page du nombre de joueur
										affich_nbre_joueur(surf_ecran, page_nbre_joueur);
										break;
									//Pour voir l'apropos
									case 3:
										//On change la page actuelle
										page_actuel=PAGE_APROPOS;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//On affiche la page de l'apropos
										affich_apropos(surf_ecran, page_apropos);
										break;
									//Pour charger une partie
									case 1:
										//Si les fichiers de sauvegarde sont valides alors on sort de la boucle
										if(bool_etat_fichier) continuer=MSG_LOAD;
										break;
									//Partie Multijoueur
									case 2:
										//On change la page actuelle
										page_actuel=PAGE_MULTI;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//On affiche la page de l'apropos
										affich_multi(surf_ecran, page_multi);
										break;
									//Dans tout les autres cas
									default:
										//On ne fait rien
										break;
								}
							}
							break;
						//Dans le cas du choix du nombre de joueur
						case PAGE_NBRE_JOUEUR:
							//Appel de la fonction de gestion du clavier pour la page nombre de joueur
							if((int_retour=gestion_clavier_nbre_joueur(surf_ecran, page_nbre_joueur, event.key.keysym.sym))!=MSG_NULL)
							{
								//Selon le message retourné
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On change la page actuelle
										page_actuel=PAGE_MENU;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Aucun item du menu n'est selectionné
										page_menu->int_select=0;
										//On affiche la page du menu principal
										affich_menu(surf_ecran, page_menu);
										break;
									//En cas de validation
									case MSG_OK:
										//On change la page actuelle
										page_actuel=PAGE_NOM_JOUEUR;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Initialisation de la structure des noms de joueur
										page_nom_joueur=init_struct_nom_joueur(surf_ecran, page_nbre_joueur->int_select+2);
										//On affiche la page du menu principal
										affich_nom_joueur(surf_ecran, page_nom_joueur);
										break;
									//Dans tout les autres cas
									default:
										//On ne fait rien
										break;
								}
							}
							break;
						//Dans le cas du choix du nombre de joueur
						case PAGE_APROPOS:
							//Appel de la fonction de gestion du clavier pour la page nombre de joueur
							if((int_retour=gestion_clavier_apropos(surf_ecran, page_apropos, event.key.keysym.sym))!=MSG_NULL)
							{
								//Selon le message retourné
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On change la page actuelle
										page_actuel=PAGE_MENU;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Aucun item du menu n'est selectionné
										page_menu->int_select=0;
										//On affiche la page du menu principal
										affich_menu(surf_ecran, page_menu);
										break;
									//Pour tout les autres cas
									default:
										//On ne fait rien...
										break;
								}
							}
							break;
						//Dans le cas du choix du nombre de joueur
						case PAGE_MULTI:
							//Appel de la fonction de gestion du clavier pour la page nombre de joueur
							if((int_retour=gestion_clavier_multi(surf_ecran, page_multi, event.key.keysym.sym))!=MSG_NULL)
							{
								//Selon le message retourné
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On change la page actuelle
										page_actuel=PAGE_MENU;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Aucun item du menu n'est selectionné
										page_menu->int_select=0;
										//On affiche la page du menu principal
										affich_menu(surf_ecran, page_menu);
										break;
									//Pour tout les autres cas
									default:
										//On ne fait rien...
										break;
								}
							}
							break;
						//Dans le cas de la saisie du nombre de joueur
						case PAGE_NOM_JOUEUR:
							//Appelle de la fonction de gestion du clavier pour la page des noms des joueurs
							if((int_retour=gestion_clavier_nom_joueur(surf_ecran, page_nom_joueur, event.key.keysym.sym))!=MSG_NULL)
							{
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On détruit la page des noms des joueurs
										destruction_nom_joueur(page_nom_joueur);
										//On change la page actuelle
										page_actuel=PAGE_NBRE_JOUEUR;
										//Initialisation du nombre de joueur par défault
										page_nbre_joueur->int_select=0;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//On affiche la page du nombre de joueur
										affich_nbre_joueur(surf_ecran, page_nbre_joueur);
										break;
									//En cas de validation
									case MSG_OK:
										//Sortit de la boucle
										continuer=MSG_OK;
										break;
									default:
										break;
								}
							}
							break;
						//Dans tout les autres cas
						default:
							break;
					}
					break;
			//En cas de déplacement de la souris
			case SDL_MOUSEMOTION:
				//S'il s'agit du bouton quitter
				if(event.motion.x>(bouton_get_x(btn_quitter)) && event.motion.x<(bouton_get_x(btn_quitter)+bouton_get_w(btn_quitter))
				&& event.motion.y>(bouton_get_y(btn_quitter)) && event.motion.y<(bouton_get_y(btn_quitter)+bouton_get_h(btn_quitter)) && !bool_btn_quit_etat)
				{
					//On met le bouton quitter en surbrillance
					affich_bouton(surf_ecran, btn_quitter, true);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le bouton quitter est en surbrillance
					bool_btn_quit_etat=true;
				}
				//En cas de passage dans le contenu de la page
				else if(event.motion.x>(img_cache->position.x) && event.motion.x<(img_cache->surf_image->w)+(img_cache->position.x)
				&& event.motion.y>(img_cache->position.y) && event.motion.y<(img_cache->surf_image->h)+(img_cache->position.y))
				{
					//Mise en mode normal du bouton quitter
					affich_bouton(surf_ecran, btn_quitter, false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					
					//On effectue l'action en fonction de la page
					switch(page_actuel)
					{
						//Dans le cas du menu principal
						case PAGE_MENU:
							break;
						//Dans le cas du choix du nombre de joueur
						case PAGE_NBRE_JOUEUR:
							bool_bouton_etat=gestion_survol_nbre_joueur(surf_ecran, page_nbre_joueur, event.motion.x, event.motion.y, bool_bouton_etat);
							break;
						//Dans le cas de l'apropos
						case PAGE_APROPOS:
							bool_bouton_etat=gestion_survol_apropos(surf_ecran, page_apropos, event.motion.x, event.motion.y, bool_bouton_etat);
							break;
						//Dans le cas du menu multijoueur
						case PAGE_MULTI:
							bool_bouton_etat=gestion_survol_multi(surf_ecran, page_multi, event.motion.x, event.motion.y, bool_bouton_etat);
							break;
						//Dans le cas de la saisie du nombre de joueur
						case PAGE_NOM_JOUEUR:
							bool_bouton_etat=gestion_survol_nom_joueur(surf_ecran, page_nom_joueur, event.motion.x, event.motion.y, bool_bouton_etat);
							break;
						//Dans tout les autres cas
						default:
							break;
					}
				}
				else if(bool_btn_quit_etat)
				{
					//Mise en mode normal du bouton quitter
					affich_bouton(surf_ecran, btn_quitter, false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//La bouton quitter est redevenu normal
					bool_btn_quit_etat=false;
				}
				break;
			//En cas de clic sur un bouton
			case SDL_MOUSEBUTTONUP:
				//S'il s'agit du bouton quitter
				if(event.button.x>(bouton_get_x(btn_quitter)) && event.button.x<(bouton_get_x(btn_quitter)+bouton_get_w(btn_quitter))
				&& event.button.y>(bouton_get_y(btn_quitter)) && event.button.y<(bouton_get_y(btn_quitter)+bouton_get_h(btn_quitter)))
				{
					continuer=MSG_QUITTER;
				}
				//En cas de clic dans le contenu de la page
				else if(event.button.x>(img_cache->position.x) && event.button.x<(img_cache->surf_image->w)+(img_cache->position.x)
				&& event.button.y>(img_cache->position.y) && event.button.y<(img_cache->surf_image->h)+(img_cache->position.y))
				{
					//On effectue l'action en fonction de la page
					switch(page_actuel)
					{
						//Dans le cas du choix du nombre de joueur
						case PAGE_NBRE_JOUEUR:
							//Fonction de gestion des clics de souris pour la page du nombre de joueur
							if((int_retour=gestion_clic_nbre_joueur(surf_ecran, page_nbre_joueur, event.button.x, event.button.y))!=MSG_NULL)
							{
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On change la page actuelle
										page_actuel=PAGE_MENU;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Aucun item du menu n'est selectionné
										page_menu->int_select=0;
										//On affiche la page du menu principal
										affich_menu(surf_ecran, page_menu);
										break;
									//En cas de validation
									case MSG_OK:
										//On change la page actuelle
										page_actuel=PAGE_NOM_JOUEUR;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Initialisation de la structure du nombre de joueur
										page_nom_joueur=init_struct_nom_joueur(surf_ecran, page_nbre_joueur->int_select+2);
										//On affiche la page du menu principal
										affich_nom_joueur(surf_ecran, page_nom_joueur);
										break;
									default:
										break;
								}
							}
							break;
						//Dans le cas de la page apropos
						case PAGE_APROPOS:
							//Fonction de gestion des clics de souris pour la page apropos
							if((int_retour=gestion_clic_apropos(surf_ecran, page_apropos, event.button.x, event.button.y))!=MSG_NULL)
							{
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On change la page actuelle
										page_actuel=PAGE_MENU;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Aucun item du menu n'est selectionné
										page_menu->int_select=0;
										//On affiche la page du menu principal
										affich_menu(surf_ecran, page_menu);
										break;
									//Pour tout les autres cas
									default:
										//On ne fait rien
										break;
								}
							}
							break;
						//Dans le cas de la page multi
						case PAGE_MULTI:
							//Fonction de gestion des clics de souris pour la page multi
							if((int_retour=gestion_clic_multi(surf_ecran, page_multi, event.button.x, event.button.y))!=MSG_NULL)
							{
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On change la page actuelle
										page_actuel=PAGE_MENU;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//Aucun item du menu n'est selectionné
										page_menu->int_select=0;
										//On affiche la page du menu principal
										affich_menu(surf_ecran, page_menu);
										break;
									//Pour tout les autres cas
									default:
										//On ne fait rien
										break;
								}
							}
							break;
						//Dans le cas de la saisie des noms des joueurs
						case PAGE_NOM_JOUEUR:
							//Fonction de gestion des clics de souris pour la page des noms des joueurs
							if((int_retour=gestion_clic_nom_joueur(surf_ecran, page_nom_joueur, event.button.x, event.button.y))!=MSG_NULL)
							{
								switch(int_retour)
								{
									//En cas de retour
									case MSG_BACK:
										//On détruit la page des noms des joueurs
										destruction_nom_joueur(page_nom_joueur);
										//On change la page actuelle
										page_actuel=PAGE_NBRE_JOUEUR;
										//Initialisation du nombre de joueur par défault
										page_nbre_joueur->int_select=0;
										//On affiche le cache
										affich_image(surf_ecran, img_cache);
										//On affiche la page du nombre de joueur
										affich_nbre_joueur(surf_ecran, page_nbre_joueur);
										break;
									case MSG_OK:
										//Sortit de la boucle
										continuer=MSG_OK;
										break;
									default:
										break;
								}
							}
							break;
						//Dans tout les autres cas
						default:
							//On ne fait rien
							break;
					}
				}
				break;
			//En cas d'autre événement
			default:
				//On ne fait rien...
				break;
		}
    }
	
	//Destruction de la page des nombres de joueur
	destruction_nbre_joueur(page_nbre_joueur);
	
	//Destruction de la page du menu principal
	destruction_menu(page_menu);
	
	//Destruction de la page apropos
	destruction_apropos(page_apropos);
	
	//Destruction de la page multijoueur
	destruction_multi(page_multi);
	
	//Sauvegarde des informations sur la page nom des joueurs
	*info_nom_joueur=page_nom_joueur;

	//On retourne le message de contition de sortit de la boucle d'attente
	return(continuer);
}

int gestion_clavier_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* nom_joueur, int int_key)
{
	//Variables de boucle
	int i;
	int j;
	
	//Structure de l'image du nom du joueur selectionné
	struct_image* img_nom_joueur;
	
	//Selon la touche préssé
	switch(int_key)
	{
		//En cas de tabulation
		case SDLK_TAB:
			//Affichage du cache du curseur
			affich_image(surf_ecran, nom_joueur->img_curseur_cache);
			//Passage au champ suivant
			(nom_joueur->int_select)=((nom_joueur->int_select)+1)%(nom_joueur->int_nbre_joueur);
			//Modification de la position du curseur
			image_set_position(nom_joueur->img_curseur, image_get_x(nom_joueur->img_curseur), (nom_joueur->int_select)*CHAMP_HAUTEUR*2+CHAMP_POS_Y+5);
			//Modification de la position du cache du curseur
			image_set_position(nom_joueur->img_curseur_cache, image_get_x(nom_joueur->img_curseur_cache), (nom_joueur->int_select)*CHAMP_HAUTEUR*2+CHAMP_POS_Y+5);
			//Affichage du curseur
			affich_image(surf_ecran, nom_joueur->img_curseur);
			//Mise à jour de l'écran
			SDL_Flip(surf_ecran);
			return(MSG_NULL);
			break;
		//En cas de validation
		case SDLK_RETURN:
			//Pour chacun des joueurs
			for(i=0;i<nom_joueur->int_nbre_joueur;i++)
			{
				//Vérification de l'existence des noms
				if (nom_joueur->str_noms[i][0]=='\0')
				{
					//Si c'est pas bon, on renvoit rien
					return(MSG_NULL);
				}
				//Si les noms ne sont pas vide
				else
				{
					//Pour chacun des autres noms					
					for (j=i+1;j<nom_joueur->int_nbre_joueur;j++)
					{
						//On vérifie l'unicité du nom
						if (strcmp(nom_joueur->str_noms[i],nom_joueur->str_noms[j])==0)
						{
							//Si le nom est en double, on renvoit rien
							return(MSG_NULL);
						}
					}
				}
			}
			//Si tout c'est bien, passer, on renvoit le message OK
			return(MSG_OK);
			break;
		//Touche ECHAP
		case SDLK_ESCAPE:
			//Message de retour arriere
			return(MSG_BACK);
			break;
		//Pour toutes les autres touches
		default:
			//Modification de la position du champ
			image_set_position(nom_joueur->img_champ, CHAMP_POS_X, CHAMP_POS_Y+(nom_joueur->int_select)*2*CHAMP_HAUTEUR);
			//Affichage du champ
			affich_image(surf_ecran, nom_joueur->img_champ);
			//Sauvegarde du nom du joueur
			strcpy(nom_joueur->str_noms[(nom_joueur->int_select)],ajout_caractere(nom_joueur->str_noms[(nom_joueur->int_select)], int_key));
			//Création de l'image du nom du joueur
			img_nom_joueur=creation_texte(nom_joueur->str_noms[(nom_joueur->int_select)], init_rvb_couleur(0, 0, 0), 17, CHAMP_POS_X+5, CHAMP_POS_Y+(nom_joueur->int_select)*2*CHAMP_HAUTEUR-10, POLICE_1);
			//Affichage du nom du joueur
			affich_image(surf_ecran, img_nom_joueur);
			//Mise à jour de l'écran
			SDL_Flip(surf_ecran);
			//Destruction de l'image du nom du joueur
			destruction_image(img_nom_joueur);
			return(MSG_NULL);
			break;
	}
	return(MSG_NULL);
}

int gestion_clic_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* nom_joueur, int x, int y)
{
	//Variables de boucle
	int i;
	int j;
	
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(nom_joueur->btn_retour)) && x<(bouton_get_x(nom_joueur->btn_retour)+bouton_get_w(nom_joueur->btn_retour))
	&& y>(bouton_get_y(nom_joueur->btn_retour)) && y<(bouton_get_y(nom_joueur->btn_retour)+bouton_get_h(nom_joueur->btn_retour)))
	{
		return(MSG_BACK);
	}
	//S'il s'agit du bouton jouer
	else if(x>(bouton_get_x(nom_joueur->btn_jouer)) && x<(bouton_get_x(nom_joueur->btn_jouer)+bouton_get_w(nom_joueur->btn_jouer))
	&& y>(bouton_get_y(nom_joueur->btn_jouer)) && y<(bouton_get_y(nom_joueur->btn_jouer)+bouton_get_h(nom_joueur->btn_jouer)))
	{
		//Pour chacun des joueurs
		for(i=0;i<nom_joueur->int_nbre_joueur;i++)
		{
			//Vérification de l'existence des noms
			if (nom_joueur->str_noms[i][0]=='\0')
			{
				//Si c'est pas bon, on renvoit rien
				return(MSG_NULL);
			}
			//Si les noms ne sont pas vide
			else
			{
				//Pour chacun des autres noms					
				for (j=i+1;j<nom_joueur->int_nbre_joueur;j++)
				{
					//On vérifie l'unicité du nom
					if (strcmp(nom_joueur->str_noms[i],nom_joueur->str_noms[j])==0)
					{
						//Si le nom est en double, on renvoit rien
						return(MSG_NULL);
					}
				}
			}
		}
		//Si tout c'est bien, passer, on renvoit le message OK
		return(MSG_OK);
	}
	return(MSG_NULL);
}

bool gestion_survol_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* nom_joueur, int x, int y, bool bool_need_maj)
{
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(nom_joueur->btn_retour)) && x<(bouton_get_x(nom_joueur->btn_retour)+bouton_get_w(nom_joueur->btn_retour))
	&& y>(bouton_get_y(nom_joueur->btn_retour)) && y<(bouton_get_y(nom_joueur->btn_retour)+bouton_get_h(nom_joueur->btn_retour)))
	{
		//Affichage du bouton jouer en normal
		affich_bouton(surf_ecran, nom_joueur->btn_jouer, false);
		//Affichage du bouton retour en surbrillance
		affich_bouton(surf_ecran, nom_joueur->btn_retour, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Un bouton est en surbrillance
		return(true);
	}
	//S'il s'agit du bouton jouer
	else if(x>(bouton_get_x(nom_joueur->btn_jouer)) && x<(bouton_get_x(nom_joueur->btn_jouer)+bouton_get_w(nom_joueur->btn_jouer))
	&& y>(bouton_get_y(nom_joueur->btn_jouer)) && y<(bouton_get_y(nom_joueur->btn_jouer)+bouton_get_h(nom_joueur->btn_jouer)))
	{
		//Affichage du bouton retour en normal
		affich_bouton(surf_ecran, nom_joueur->btn_retour, false);
		//Affichage du bouton jouer en surbrillance
		affich_bouton(surf_ecran, nom_joueur->btn_jouer, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Un bouton est en surbrillance
		return(true);
	}
	//Dans tout les autres cas, si l'un des boutons est en surbrillance et que l'on est pas dans sa zone
	else if(bool_need_maj)
	{
		//Affichage du bouton retour en normal
		affich_bouton(surf_ecran, nom_joueur->btn_retour, false);
		//Affichage du bouton jouer en normal
		affich_bouton(surf_ecran, nom_joueur->btn_jouer, false);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Aucun bouton n'est en surbrillance
		return(false);
	}
	//Aucun bouton n'est en surbrillance
	return(false);
}

int gestion_clavier_menu(SDL_Surface* surf_ecran, struct_menu* menu, int int_key)
{
	//Selon la touche préssé
	switch(int_key)
	{
		//Touche directionnelle droite
		case SDLK_DOWN:
			//Réaffichage de l'ancien item en mode normal
			affich_bouton(surf_ecran, menu->btn_items[(menu->int_select)], false);
			//Mise à jour de l'item sélectionné
			(menu->int_select)=((menu->int_select)+1)%5;
			//Réaffichage du nouvel item selectionné en surbrillance
			affich_bouton(surf_ecran, menu->btn_items[(menu->int_select)], true);
			//Mise à jour de l'écran
			SDL_Flip(surf_ecran);
			return(MSG_NULL);
			break;
		//Touche directionnelle gauche
		case SDLK_UP:
			//Réaffichage de l'ancien item en mode normal
			affich_bouton(surf_ecran, menu->btn_items[(menu->int_select)], false);
			//Mise à jour de l'item selectionné
			(menu->int_select)=((menu->int_select)+4)%5;
			cout << "Nouvel item : " << (menu->int_select) << endl;
			//On réaffiche le nouveau nombre
			affich_bouton(surf_ecran, menu->btn_items[(menu->int_select)], true);
			//Mise à jour de l'écran
			SDL_Flip(surf_ecran);
			return(MSG_NULL);
			break;
		//Touche entrer
		case SDLK_RETURN:
			//Message d'information indiquant que la joueur à validé l'item selectionné
			return(MSG_OK);
			break;
		//Pour toutes les autres touches
		default:
			//On ne fait rien
			break;
	}
	return(MSG_NULL);
}

bool gestion_survol_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* nbre_joueur, int x, int y, bool bool_need_maj)
{
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(nbre_joueur->btn_retour)) && x<(bouton_get_x(nbre_joueur->btn_retour)+bouton_get_w(nbre_joueur->btn_retour))
	&& y>(bouton_get_y(nbre_joueur->btn_retour)) && y<(bouton_get_y(nbre_joueur->btn_retour)+bouton_get_h(nbre_joueur->btn_retour)))
	{
		//Affichage du bouton valider en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_valider, false);
		//Affichage du bouton retour en surbrillance
		affich_bouton(surf_ecran, nbre_joueur->btn_retour, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Une fleche est en surbrillance
		return(true);
	}
	//S'il s'agit du bouton valider
	else if(x>(bouton_get_x(nbre_joueur->btn_valider)) && x<(bouton_get_x(nbre_joueur->btn_valider)+bouton_get_w(nbre_joueur->btn_valider))
	&& y>(bouton_get_y(nbre_joueur->btn_valider)) && y<(bouton_get_y(nbre_joueur->btn_valider)+bouton_get_h(nbre_joueur->btn_valider)))
	{
		//Affichage du bouton retour en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_retour, false);
		//Affichage du bouton valider en surbrillance
		affich_bouton(surf_ecran, nbre_joueur->btn_valider, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Une fleche est en surbrillance
		return(true);
	}
	//S'il s'agit du bouton de la fleche gauche
	else if(x>(bouton_get_x(nbre_joueur->btn_fleche_gauche)) && x<(bouton_get_x(nbre_joueur->btn_fleche_gauche)+bouton_get_w(nbre_joueur->btn_fleche_gauche))
	&& y>(bouton_get_y(nbre_joueur->btn_fleche_gauche)) && y<(bouton_get_y(nbre_joueur->btn_fleche_gauche)+bouton_get_h(nbre_joueur->btn_fleche_gauche)))
	{
		//Affichage du bouton fleche droite en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_fleche_droite, false);
		//Affichage du bouton fleche gauche en surbrillance
		affich_bouton(surf_ecran, nbre_joueur->btn_fleche_gauche, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Une fleche est en surbrillance
		return(true);
	}
	//S'il s'agit du bouton de la fleche droite
	else if(x>(bouton_get_x(nbre_joueur->btn_fleche_droite)) && x<(bouton_get_x(nbre_joueur->btn_fleche_droite)+bouton_get_w(nbre_joueur->btn_fleche_droite))
	&& y>(bouton_get_y(nbre_joueur->btn_fleche_droite)) && y<(bouton_get_y(nbre_joueur->btn_fleche_droite)+bouton_get_h(nbre_joueur->btn_fleche_droite)))
	{
		//Affichage du bouton fleche gauche en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_fleche_gauche, false);
		//Affichage du bouton fleche droite en surbrillance
		affich_bouton(surf_ecran, nbre_joueur->btn_fleche_droite, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Une fleche est en surbrillance
		return(true);
	}
	//Dans tout les autres cas, si l'une des fleche est en surbrillance et que l'on est pas dans sa zone
	else if(bool_need_maj)
	{
		//Affichage du bouton retour en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_retour, false);
		//Affichage du bouton valider en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_valider, false);
		//Affichage du bouton fleche droite en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_fleche_droite, false);
		//Affichage du bouton fleche gauche en normal
		affich_bouton(surf_ecran, nbre_joueur->btn_fleche_gauche, false);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Aucune fleche n'est en surbrillance
		return(false);
	}
	//Mise à jour de l'écran
	SDL_Flip(surf_ecran);
	//Aucune fleche n'est en surbrillance
	return(false);
}

int gestion_clavier_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* nbre_joueur, int int_key)
{
	//Selon la touche préssé
	switch(int_key)
	{
		//Touche entrer
		case SDLK_RETURN:
			return(MSG_OK);
			break;
		//Touche directionnelle droite
		case SDLK_RIGHT:
			if((nbre_joueur->int_select)<4)
			{
				//Mise à jour du nombre de joueur
				(nbre_joueur->int_select)=((nbre_joueur->int_select)+1)%5;
				//Affichage du cache du nombre
				affich_image(surf_ecran, nbre_joueur->img_nbre_cache);
				//On réaffiche le nouveau nombre
				affich_image(surf_ecran, nbre_joueur->img_nombres[nbre_joueur->int_select]);
				//Mise à jour de l'écran
				SDL_Flip(surf_ecran);
				return(MSG_NULL);
			}
			break;
		//Touche directionnelle gauche
		case SDLK_LEFT:
			if((nbre_joueur->int_select)>0)
			{
				//Mise à jour du nombre de joueur
				(nbre_joueur->int_select)=((nbre_joueur->int_select)-1)%5;
				//Affichage du cache du nombre
				affich_image(surf_ecran, nbre_joueur->img_nbre_cache);
				//On réaffiche le nouveau nombre
				affich_image(surf_ecran, nbre_joueur->img_nombres[nbre_joueur->int_select]);
				//Mise à jour de l'écran
				SDL_Flip(surf_ecran);
				return(MSG_NULL);
			}
			break;
		//Touche ECHAP
		case SDLK_ESCAPE:
			//Message de retour arriere
			return(MSG_BACK);
			break;
		default:
			break;
	}
	return(MSG_NULL);
}

int gestion_clic_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* nbre_joueur, int x, int y)
{
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(nbre_joueur->btn_retour)) && x<(bouton_get_x(nbre_joueur->btn_retour)+bouton_get_w(nbre_joueur->btn_retour))
	&& y>(bouton_get_y(nbre_joueur->btn_retour)) && y<(bouton_get_y(nbre_joueur->btn_retour)+bouton_get_h(nbre_joueur->btn_retour)))
	{
		return(MSG_BACK);
	}
	//S'il s'agit du bouton valider
	else if(x>(bouton_get_x(nbre_joueur->btn_valider)) && x<(bouton_get_x(nbre_joueur->btn_valider)+bouton_get_w(nbre_joueur->btn_valider))
	&& y>(bouton_get_y(nbre_joueur->btn_valider)) && y<(bouton_get_y(nbre_joueur->btn_valider)+bouton_get_h(nbre_joueur->btn_valider)))
	{
		return(MSG_OK);
	}
	//S'il s'agit du bouton de la fleche gauche
	else if(x>(bouton_get_x(nbre_joueur->btn_fleche_gauche)) && x<(bouton_get_x(nbre_joueur->btn_fleche_gauche)+bouton_get_w(nbre_joueur->btn_fleche_gauche))
	&& y>(bouton_get_y(nbre_joueur->btn_fleche_gauche)) && y<(bouton_get_y(nbre_joueur->btn_fleche_gauche)+bouton_get_h(nbre_joueur->btn_fleche_gauche)))
	{
		if((nbre_joueur->int_select)>0)
		{
			//Mise à jour du nombre de joueur
			(nbre_joueur->int_select)=((nbre_joueur->int_select)-1)%5;
			//Affichage du cache du nombre
			affich_image(surf_ecran, nbre_joueur->img_nbre_cache);
			//On réaffiche le nouveau nombre
			affich_image(surf_ecran, nbre_joueur->img_nombres[nbre_joueur->int_select]);
			//Mise à jour de l'écran
			SDL_Flip(surf_ecran);
			return(MSG_NULL);
		}
	}
	//S'il s'agit du bouton de la fleche droite
	else if(x>(bouton_get_x(nbre_joueur->btn_fleche_droite)) && x<(bouton_get_x(nbre_joueur->btn_fleche_droite)+bouton_get_w(nbre_joueur->btn_fleche_droite))
	&& y>(bouton_get_y(nbre_joueur->btn_fleche_droite)) && y<(bouton_get_y(nbre_joueur->btn_fleche_droite)+bouton_get_h(nbre_joueur->btn_fleche_droite)))
	{
		if((nbre_joueur->int_select)<4)
		{
			//Mise à jour du nombre de joueur
			(nbre_joueur->int_select)=((nbre_joueur->int_select)+1)%5;
			//Affichage du cache du nombre
			affich_image(surf_ecran, nbre_joueur->img_nbre_cache);
			//On réaffiche le nouveau nombre
			affich_image(surf_ecran, nbre_joueur->img_nombres[nbre_joueur->int_select]);
			//Mise à jour de l'écran
			SDL_Flip(surf_ecran);
			return(MSG_NULL);
		}
	}
	//Dans tout les autres cas, on ne fait rien
	return(MSG_NULL);
}

bool gestion_survol_apropos(SDL_Surface* surf_ecran, struct_apropos* apropos, int x, int y, bool bool_need_maj)
{
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(apropos->btn_retour)) && x<(bouton_get_x(apropos->btn_retour)+bouton_get_w(apropos->btn_retour))
	&& y>(bouton_get_y(apropos->btn_retour)) && y<(bouton_get_y(apropos->btn_retour)+bouton_get_h(apropos->btn_retour)))
	{
		//Affichage du bouton retour en surbrillance
		affich_bouton(surf_ecran, apropos->btn_retour, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Une fleche est en surbrillance
		return(true);
	}
	//Dans tout les autres cas, si l'une des fleche est en surbrillance et que l'on est pas dans sa zone
	else if(bool_need_maj)
	{
		//Affichage du bouton retour en normal
		affich_bouton(surf_ecran, apropos->btn_retour, false);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Aucune fleche n'est en surbrillance
		return(false);
	}
	//Aucune fleche n'est en surbrillance
	return(false);
}

int gestion_clavier_apropos(SDL_Surface* surf_ecran, struct_apropos* apropos, int int_key)
{
	//Selon la touche préssé
	switch(int_key)
	{
		//Touche entrer
		case SDLK_RETURN:
			//Message de retour arrière
			return(MSG_BACK);
			break;
		//Touche ECHAP
		case SDLK_ESCAPE:
			//Message de retour arriere
			return(MSG_BACK);
			break;
		//Pour toutes les autres touches
		default:
			//On ne fait rien
			break;
	}
	return(MSG_NULL);
}

int gestion_clic_apropos(SDL_Surface* surf_ecran, struct_apropos* apropos, int x, int y)
{
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(apropos->btn_retour)) && x<(bouton_get_x(apropos->btn_retour)+bouton_get_w(apropos->btn_retour))
	&& y>(bouton_get_y(apropos->btn_retour)) && y<(bouton_get_y(apropos->btn_retour)+bouton_get_h(apropos->btn_retour)))
	{
		return(MSG_BACK);
	}

	//Dans tout les autres cas, on ne fait rien
	return(MSG_NULL);
}



bool gestion_survol_multi(SDL_Surface* surf_ecran, struct_multi* multi, int x, int y, bool bool_need_maj)
{
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(multi->btn_retour)) && x<(bouton_get_x(multi->btn_retour)+bouton_get_w(multi->btn_retour))
	&& y>(bouton_get_y(multi->btn_retour)) && y<(bouton_get_y(multi->btn_retour)+bouton_get_h(multi->btn_retour)))
	{
		//Affichage du bouton retour en surbrillance
		affich_bouton(surf_ecran, multi->btn_retour, true);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Une fleche est en surbrillance
		return(true);
	}
	//Dans tout les autres cas, si l'une des fleche est en surbrillance et que l'on est pas dans sa zone
	else if(bool_need_maj)
	{
		//Affichage du bouton retour en normal
		affich_bouton(surf_ecran, multi->btn_retour, false);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		//Aucune fleche n'est en surbrillance
		return(false);
	}
	//Aucune fleche n'est en surbrillance
	return(false);
}

int gestion_clavier_multi(SDL_Surface* surf_ecran, struct_multi* multi, int int_key)
{
	//Selon la touche préssé
	switch(int_key)
	{
		//Touche entrer
		case SDLK_RETURN:
			//Message de retour arrière
			return(MSG_BACK);
			break;
		//Touche ECHAP
		case SDLK_ESCAPE:
			//Message de retour arriere
			return(MSG_BACK);
			break;
		//Pour toutes les autres touches
		default:
			//On ne fait rien
			break;
	}
	return(MSG_NULL);
}

int gestion_clic_multi(SDL_Surface* surf_ecran, struct_multi* multi, int x, int y)
{
	//S'il s'agit du bouton retour
	if(x>(bouton_get_x(multi->btn_retour)) && x<(bouton_get_x(multi->btn_retour)+bouton_get_w(multi->btn_retour))
	&& y>(bouton_get_y(multi->btn_retour)) && y<(bouton_get_y(multi->btn_retour)+bouton_get_h(multi->btn_retour)))
	{
		return(MSG_BACK);
	}

	//Dans tout les autres cas, on ne fait rien
	return(MSG_NULL);
}

int attente_action_message(SDL_Surface* surf_ecran, struct_message* msg_message)
{
	//Variable de boucle
	int continuer;
	continuer=MSG_RUN;
	
	//Evenement sdl
	SDL_Event event;
	
	//Etat des boutons
	bool bool_btn_etat;
	
	while(continuer==MSG_RUN)
	{
		//On attend un événement
		SDL_WaitEvent(&event);
		//Selon l'événement
		switch(event.type)
		{
			//En cas de déplacement de la souris
			case SDL_MOUSEMOTION:
				//S'il s'agit du premier bouton
				if(event.motion.x>(bouton_get_x(msg_message->btn_boutons[0])) && event.motion.x<(bouton_get_x(msg_message->btn_boutons[0])+bouton_get_w(msg_message->btn_boutons[0]))
				&& event.motion.y>(bouton_get_y(msg_message->btn_boutons[0])) && event.motion.y<(bouton_get_y(msg_message->btn_boutons[0])+bouton_get_h(msg_message->btn_boutons[0])))
				{
					//On met le premier bouton en surbrillance
					affich_bouton(surf_ecran, msg_message->btn_boutons[0], true);
					//Affichage du second bouton en mode normal
					if(msg_message->int_nbre_bouton>1) affich_bouton(surf_ecran, msg_message->btn_boutons[1], false);
					//Affichage du troisième bouton en mode normal
					if(msg_message->int_nbre_bouton>2) affich_bouton(surf_ecran, msg_message->btn_boutons[2], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le premier bouton est en surbrillance
					bool_btn_etat=true;
				}
				//S'il s'agit du second bouton
				else if(msg_message->int_nbre_bouton>1 && event.motion.x>(bouton_get_x(msg_message->btn_boutons[1])) && event.motion.x<(bouton_get_x(msg_message->btn_boutons[1])+bouton_get_w(msg_message->btn_boutons[1]))
				&& event.motion.y>(bouton_get_y(msg_message->btn_boutons[1])) && event.motion.y<(bouton_get_y(msg_message->btn_boutons[1])+bouton_get_h(msg_message->btn_boutons[1])))
				{
					//On met le premier bouton en surbrillance
					affich_bouton(surf_ecran, msg_message->btn_boutons[1], true);
					//Affichage du premier bouton en mode normal
					affich_bouton(surf_ecran, msg_message->btn_boutons[0], false);
					//Affichage du second bouton en mode normal
					if(msg_message->int_nbre_bouton>2) affich_bouton(surf_ecran, msg_message->btn_boutons[2], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le premier bouton est en surbrillance
					bool_btn_etat=true;
				}
				//S'il s'agit du troisième bouton
				else if(msg_message->int_nbre_bouton>2 && event.motion.x>(bouton_get_x(msg_message->btn_boutons[2])) && event.motion.x<(bouton_get_x(msg_message->btn_boutons[2])+bouton_get_w(msg_message->btn_boutons[2]))
				&& event.motion.y>(bouton_get_y(msg_message->btn_boutons[2])) && event.motion.y<(bouton_get_y(msg_message->btn_boutons[2])+bouton_get_h(msg_message->btn_boutons[2])))
				{
					//On met le premier bouton en surbrillance
					affich_bouton(surf_ecran, msg_message->btn_boutons[2], true);
					//Affichage du premier bouton en mode normal
					affich_bouton(surf_ecran, msg_message->btn_boutons[0], false);
					//Affichage du second bouton en mode normal
					affich_bouton(surf_ecran, msg_message->btn_boutons[1], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le premier bouton est en surbrillance
					bool_btn_etat=true;
				}
				else if(bool_btn_etat)
				{
					//Affichage du premier bouton en mode normal
					affich_bouton(surf_ecran, msg_message->btn_boutons[0], false);
					//Affichage du second bouton en mode normal
					if(msg_message->int_nbre_bouton>1) affich_bouton(surf_ecran, msg_message->btn_boutons[1], false);
					//Affichage du troisième bouton en mode normal
					if(msg_message->int_nbre_bouton>2) affich_bouton(surf_ecran, msg_message->btn_boutons[2], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//La bouton quitter est redevenu normal
					bool_btn_etat=false;
				}
				break;
			//En cas de clic du joueur
			case SDL_MOUSEBUTTONUP:
				//S'il s'agit du premier bouton
				if(event.motion.x>(bouton_get_x(msg_message->btn_boutons[0])) && event.motion.x<(bouton_get_x(msg_message->btn_boutons[0])+bouton_get_w(msg_message->btn_boutons[0]))
				&& event.motion.y>(bouton_get_y(msg_message->btn_boutons[0])) && event.motion.y<(bouton_get_y(msg_message->btn_boutons[0])+bouton_get_h(msg_message->btn_boutons[0])))
				{
					//Action :  clic sur le premier bouton
					continuer=MSG_BTN_1;
				}
				//S'il s'agit du second bouton
				else if(msg_message->int_nbre_bouton>1 && event.motion.x>(bouton_get_x(msg_message->btn_boutons[1])) && event.motion.x<(bouton_get_x(msg_message->btn_boutons[1])+bouton_get_w(msg_message->btn_boutons[1]))
				&& event.motion.y>(bouton_get_y(msg_message->btn_boutons[1])) && event.motion.y<(bouton_get_y(msg_message->btn_boutons[1])+bouton_get_h(msg_message->btn_boutons[1])))
				{
					//Action :  clic sur le second bouton
					continuer=MSG_BTN_2;
				}
				//S'il s'agit du troisième bouton
				else if(msg_message->int_nbre_bouton>2 && event.motion.x>(bouton_get_x(msg_message->btn_boutons[2])) && event.motion.x<(bouton_get_x(msg_message->btn_boutons[2])+bouton_get_w(msg_message->btn_boutons[2]))
				&& event.motion.y>(bouton_get_y(msg_message->btn_boutons[2])) && event.motion.y<(bouton_get_y(msg_message->btn_boutons[2])+bouton_get_h(msg_message->btn_boutons[2])))
				{
					//Action :  clic sur le troisième bouton
					continuer=MSG_BTN_3;
				}
				break;
			//Dans tout les autres cas
			default:
				//On ne fait rien
				break;
		}
		//On vide la liste des événements en attente
		while(SDL_PollEvent(&event));
	}
	//On retourne l'action du joueur
	return(continuer);
}

int attente_action_msg_propriete(SDL_Surface* surf_ecran, struct_msg_propriete* msg_propriete)
{
	//Variable de boucle
	int continuer;
	continuer=MSG_RUN;
	
	//Evenement sdl
	SDL_Event event;
	
	//Etat des boutons
	bool bool_btn_etat;
	
	while(continuer==MSG_RUN)
	{
		//On attend un événement
		SDL_WaitEvent(&event);
		//Selon l'événement
		switch(event.type)
		{
			//S'il s'agit d'un appui sur une touche
			case SDL_KEYDOWN:
				//Selon la touche
				switch(event.key.keysym.sym)
				{
					//Echap
					case SDLK_ESCAPE:
						continuer = MSG_OK;
						break;
					//Touche entrer
					case SDLK_RETURN:
						continuer = MSG_OK;
						break;
					//Pour toutes les autres touches
					default:
						//On fait rien...
						break;
				}
				break;
			//En cas de déplacement de la souris
			case SDL_MOUSEMOTION:
				//S'il s'agit du premier bouton
				if(event.motion.x>(bouton_get_x(msg_propriete->btn_boutons[0])) && event.motion.x<(bouton_get_x(msg_propriete->btn_boutons[0])+bouton_get_w(msg_propriete->btn_boutons[0]))
				&& event.motion.y>(bouton_get_y(msg_propriete->btn_boutons[0])) && event.motion.y<(bouton_get_y(msg_propriete->btn_boutons[0])+bouton_get_h(msg_propriete->btn_boutons[0])))
				{
					//On met le premier bouton en surbrillance
					affich_bouton(surf_ecran, msg_propriete->btn_boutons[0], true);
					//Affichage du second bouton en mode normal
					if(msg_propriete->int_nbre_bouton>1) affich_bouton(surf_ecran, msg_propriete->btn_boutons[1], false);
					//Affichage du troisième bouton en mode normal
					if(msg_propriete->int_nbre_bouton>2) affich_bouton(surf_ecran, msg_propriete->btn_boutons[2], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le premier bouton est en surbrillance
					bool_btn_etat=true;
				}
				//S'il s'agit du second bouton
				else if(msg_propriete->int_nbre_bouton>1 && event.motion.x>(bouton_get_x(msg_propriete->btn_boutons[1])) && event.motion.x<(bouton_get_x(msg_propriete->btn_boutons[1])+bouton_get_w(msg_propriete->btn_boutons[1]))
				&& event.motion.y>(bouton_get_y(msg_propriete->btn_boutons[1])) && event.motion.y<(bouton_get_y(msg_propriete->btn_boutons[1])+bouton_get_h(msg_propriete->btn_boutons[1])))
				{
					//On met le premier bouton en surbrillance
					affich_bouton(surf_ecran, msg_propriete->btn_boutons[1], true);
					//Affichage du premier bouton en mode normal
					affich_bouton(surf_ecran, msg_propriete->btn_boutons[0], false);
					//Affichage du second bouton en mode normal
					if(msg_propriete->int_nbre_bouton>2) affich_bouton(surf_ecran, msg_propriete->btn_boutons[2], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le premier bouton est en surbrillance
					bool_btn_etat=true;
				}
				//S'il s'agit du troisième bouton
				else if(msg_propriete->int_nbre_bouton>2 && event.motion.x>(bouton_get_x(msg_propriete->btn_boutons[2])) && event.motion.x<(bouton_get_x(msg_propriete->btn_boutons[2])+bouton_get_w(msg_propriete->btn_boutons[2]))
				&& event.motion.y>(bouton_get_y(msg_propriete->btn_boutons[2])) && event.motion.y<(bouton_get_y(msg_propriete->btn_boutons[2])+bouton_get_h(msg_propriete->btn_boutons[2])))
				{
					//On met le premier bouton en surbrillance
					affich_bouton(surf_ecran, msg_propriete->btn_boutons[2], true);
					//Affichage du premier bouton en mode normal
					affich_bouton(surf_ecran, msg_propriete->btn_boutons[0], false);
					//Affichage du second bouton en mode normal
					affich_bouton(surf_ecran, msg_propriete->btn_boutons[1], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//Le premier bouton est en surbrillance
					bool_btn_etat=true;
				}
				else if(bool_btn_etat)
				{
					//Affichage du premier bouton en mode normal
					affich_bouton(surf_ecran, msg_propriete->btn_boutons[0], false);
					//Affichage du second bouton en mode normal
					if(msg_propriete->int_nbre_bouton>1) affich_bouton(surf_ecran, msg_propriete->btn_boutons[1], false);
					//Affichage du troisième bouton en mode normal
					if(msg_propriete->int_nbre_bouton>2) affich_bouton(surf_ecran, msg_propriete->btn_boutons[2], false);
					//Mise à jour de l'écran
					SDL_Flip(surf_ecran);
					//La bouton quitter est redevenu normal
					bool_btn_etat=false;
				}
				break;
			//En cas de clic du joueur
			case SDL_MOUSEBUTTONUP:
				//S'il s'agit du premier bouton
				if(event.motion.x>(bouton_get_x(msg_propriete->btn_boutons[0])) && event.motion.x<(bouton_get_x(msg_propriete->btn_boutons[0])+bouton_get_w(msg_propriete->btn_boutons[0]))
				&& event.motion.y>(bouton_get_y(msg_propriete->btn_boutons[0])) && event.motion.y<(bouton_get_y(msg_propriete->btn_boutons[0])+bouton_get_h(msg_propriete->btn_boutons[0])))
				{
					//Action :  clic sur le premier bouton
					continuer=MSG_BTN_1;
				}
				//S'il s'agit du second bouton
				else if(msg_propriete->int_nbre_bouton>1 && event.motion.x>(bouton_get_x(msg_propriete->btn_boutons[1])) && event.motion.x<(bouton_get_x(msg_propriete->btn_boutons[1])+bouton_get_w(msg_propriete->btn_boutons[1]))
				&& event.motion.y>(bouton_get_y(msg_propriete->btn_boutons[1])) && event.motion.y<(bouton_get_y(msg_propriete->btn_boutons[1])+bouton_get_h(msg_propriete->btn_boutons[1])))
				{
					//Action :  clic sur le second bouton
					continuer=MSG_BTN_2;
				}
				//S'il s'agit du troisième bouton
				else if(msg_propriete->int_nbre_bouton>2 && event.motion.x>(bouton_get_x(msg_propriete->btn_boutons[2])) && event.motion.x<(bouton_get_x(msg_propriete->btn_boutons[2])+bouton_get_w(msg_propriete->btn_boutons[2]))
				&& event.motion.y>(bouton_get_y(msg_propriete->btn_boutons[2])) && event.motion.y<(bouton_get_y(msg_propriete->btn_boutons[2])+bouton_get_h(msg_propriete->btn_boutons[2])))
				{
					//Action :  clic sur le troisième bouton
					continuer=MSG_BTN_3;
				}
				break;
			//Dans tout les autres cas
			default:
				//On ne fait rien
				break;
		}
		//On vide la liste des événements en attente
		while(SDL_PollEvent(&event));
	}
	//On retourne l'action du joueur
	return(continuer);
}
