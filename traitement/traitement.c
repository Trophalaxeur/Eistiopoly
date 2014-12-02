/*!
  \file traitement.c
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief code source des fonctions de traitement. 
  \date 09/01/2006
  \version 1.0
*/

#include "traitement.h"


void jeu(SDL_Surface* surf_ecran, joueur* pj_joueur_encours,cases** plateau, int nombre_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16])
{
	//variable de boucle
	int i;
	
	//Valeur de retour
	int int_retour;
	
	//Surface du centre
	SDL_Surface* surf_centre = NULL;
	
	//Chaine temporaire
	char str_temp[256];
	
    //Structure du panneau menu
    struct_pnl_menu* pnl_menu;
    
    //Structure du panneau fin de tour
    struct_pnl_fdt* pnl_fdt;
    
    //Joueur à éliminer
    joueur* joueur_a_eliminer;
    joueur_a_eliminer=NULL;
    
    //Joueur temporaire
    joueur* joueur_temp;
    
    //Initialisation de la valeur de retour
    int_retour=MSG_RUN;
    
    //Initialisation du panneau menu
    pnl_menu=initialisation_pnl_menu(surf_ecran);
    
    //Initialisation du panneau fin de tour
    pnl_fdt=initialisation_pnl_fdt(surf_ecran);
	
	//Création du centre
	surf_centre=SDL_LoadBMP("sdl/images/logo.bmp");

	//Affichage des cases du plateau
	for(i=0;i<40;i++) affich_case(surf_ecran, plateau[i]);
	
	//joueur_possede_tout(plateau, pj_joueur_encours);                         //<<<================================== POUR ESSAYER LA MODIFICATION DE NIVEAU RAPIDEMENT
	//pj_joueur_encours->int_argent=-1000;
	
	//on affiche les joueurs sur la cases depart
	affich_joueur_depart (surf_ecran,plateau,pj_joueur_encours,nombre_joueur);
	
	//Affichage du centre
	affich_centre(surf_ecran, surf_centre);

	//Affichage du panneau du menu
	affich_panneau_menu(surf_ecran, pnl_menu);
	
	//Tant que le joueur ne décide pas de quitter
	while(int_retour==MSG_RUN)
	{
		//Si il y à des joueurs à éliminer
		if(joueur_a_eliminer!=NULL)
		{
			//Le joueur est éliminé
			traitement_perdu(surf_ecran, plateau, joueur_a_eliminer);
			//Il n'y a pas d'autre joueur à éliminer
			joueur_a_eliminer=NULL;
			//Mise à jour des cases du plateau
			for(i=0;i<40;i++) affich_case(surf_ecran, plateau[i]);
			//On sauvegarde la tete de la liste des joueurs
			joueur_temp=pj_joueur_encours;
			//On réaffiche tout les joueurs
			while((joueur_temp=joueur_temp->pjoueur_suivant)!= pj_joueur_encours) affich_joueur(surf_ecran, joueur_temp, joueur_temp->int_position, plateau[joueur_temp->int_position]);
			//On réaffiche le joueur en cours
			affich_joueur(surf_ecran, pj_joueur_encours, pj_joueur_encours->int_position, plateau[pj_joueur_encours->int_position]);
			
		}
		//Affichage du panneau du nouveau joueur
		affich_panneau_joueur(surf_ecran,pj_joueur_encours);
		//Affichage du cache pour le panneau des possession
		affich_possessions_cache(surf_ecran);
		//Affichage du panneau des possessions
		affich_panneau_possessions(surf_ecran,pj_joueur_encours);
		//Affichage du panneau du bouton lancer dés
		affich_panneau_des_bouton(surf_ecran,0);
		//On affiche le panneau fin de tour
		affich_panneau_fdt(surf_ecran, pnl_fdt, false);
		//Mise à jour de l'écran
		SDL_Flip(surf_ecran);
		
		//On vérifie que le joueur suivant n'a pas gagné
		if(verification_victoire(pj_joueur_encours->pjoueur_suivant))
		{
			//Message de victoire
			affich_message(surf_ecran,surf_centre,"VICTOIRE", "Félicitations, vous avez ruiné tous vos adversaires !",MESSAGE_NORMAL);
			//Fin du jeu
			int_retour=MSG_QUITTER;
		}
		else
		{
			//On informe le joueur si il lui reste moins de 1000 Fintz
			if(pj_joueur_encours->int_argent < 1000) affich_msg_info(surf_ecran, surf_centre, NULL, "Attention, il vous reste moins de 1000 Fintz.");
				
			//Attente d'un événement souris
			int_retour=attente_clic(surf_ecran, surf_centre, pj_joueur_encours, plateau, bureau_de_krystel, bureau_de_nadege, pnl_menu, pnl_fdt);
			
			//Si le joueur souhaite quitter
			if(int_retour==0)
			{
				//Demande de confirmation d'action
				int_retour=affich_message(surf_ecran, surf_centre, NULL, "Etes vous sûr de vouloir réellement envisager l'idée de la possibilité que vous puissiez avoir envie de quitter ce programme sans avoir effleurer l'idée d'une possible sauvegarde de la partie ?", MESSAGE_QUITTER);
				//Si le joueur demande de sauvegarder
				if(int_retour==MSG_BTN_1)
				{
					//On sauvegarde
					sauvegarde(plateau, pj_joueur_encours);
					//Message de confirmation de sauvegarde
					affich_message(surf_ecran, surf_centre, "Sauvegarde", "La sauvegarde à été effectuée avec un très grand succès ! Toutes nos félicitations. (Il ne peut y avoir qu'un seul fichier de sauvegarde. Toute nouvelle sauvegarde écrase la précédente.)",MESSAGE_NORMAL);
				}
				//En cas d'annulation
				else if(int_retour==MSG_BTN_3)
				{
					//Le jeu continue
					int_retour=MSG_RUN;
				}
				//Autrement, le joueur à voulu quitter
				else
				{
					//Fin du jeu
					int_retour=MSG_QUITTER;
				}
			}
			//Si le joueur n'a pas assez d'argent
			else if(pj_joueur_encours->int_argent < 0)
			{
				//On affiche le message indiquant un double
				affich_message(surf_ecran, surf_centre, "PERDU !!", "Désolé, mais vous n'avez plus assez d'argent! Vous venez d'être viré de l'école! C'est balooo!", MESSAGE_NORMAL);
				//On sauvegarde le joueur à éliminer
				joueur_a_eliminer=pj_joueur_encours;
				//Passage au joueur suivant
				pj_joueur_encours=pj_joueur_encours->pjoueur_suivant;
				//Stockage du nom du joueur dans la chaine temporaire
				sprintf(str_temp, "L'élève %s peut continuer son tour à l'EISTI!", pj_joueur_encours->str_nom);
				//Affichage du message de changement de joueur
				affich_msg_info(surf_ecran, surf_centre, "Changement d'élève.", str_temp);
				//Le jeu continue
				int_retour=MSG_RUN;
			}
			//Autrement, si le joueur a fait un double
			else if (pj_joueur_encours->int_double_tire != 0)
			{
				//On affiche le message indiquant un double
				affich_msg_info(surf_ecran, surf_centre, "Double", "Vous avez fait un double, vous pouvez continuer votre tour à l'école!");
				//Le jeu continue
				int_retour=MSG_RUN;
			}
			//Dans tout les autres cas, on passe au joueur suivant
			else
			{
				//Passage au joueur suivant
				pj_joueur_encours=pj_joueur_encours->pjoueur_suivant;
				//Stockage du nom du joueur dans la chaine temporaire
				sprintf(str_temp, "L'élève %s peut continuer son tour à l'EISTI!", pj_joueur_encours->str_nom);
				//Affichage du message de changement de joueur
				affich_msg_info(surf_ecran, surf_centre, "Changement d'élève.", str_temp);
				//Le jeu continue
				int_retour=MSG_RUN;
			}
		}
	}
	
	//Destruction du panneau menu
	destruction_pnl_menu(pnl_menu);
	
	//Destruction du panneau fin de tour
	destruction_pnl_fdt(pnl_fdt);
}

int lancer_des(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur, cases** plateau)
{
	int int_1; //valeur du premier dé
	int int_2; //valeur du second dé
	int int_rebond1; //nb de rebonds du premier dé
	int int_rebond2; //nb de rebonds du second dé
	
	int i=0;
	
	SDL_Surface** surf_des;
	
	//calcul du nombre de rebond du premier dé
	int_rebond1=rand()%10+5;
	
	//calcul de nombre de rebond du second dé
	int_rebond2=rand()%10+5;
	
	//initialisation a 0 des deux dés
	int_1=0;
	int_2=0;
	
	surf_des=creation_des();
	
	if (int_rebond1 > int_rebond2)
	{
		while (i < int_rebond2)
		{
			int_1=(rand()%6)+1;
			int_2=(rand()%6)+1;
	
			affich_panneau_des(surf_ecran,surf_des,int_1,int_2);
			SDL_Delay(DELAY);
			i++;
		}
		for(i=0;i<(int_rebond1-int_rebond2-1);i++)
		{
			int_1=(rand()%6)+1;
		
			affich_panneau_des(surf_ecran,surf_des,int_1,int_2);
			SDL_Delay(DELAY);
		}
	}
	else
	{
		while (i < int_rebond1)
		{
			int_1=(rand()%6)+1;
			int_2=(rand()%6)+1;
	
			affich_panneau_des(surf_ecran,surf_des,int_1,int_2);	
			SDL_Delay(DELAY);
			i++;
		}
		for(i=0;i<(int_rebond1-int_rebond2-1);i++)
		{
			int_1=(rand()%6)+1;
		
			affich_panneau_des(surf_ecran,surf_des,int_1,int_2);
			SDL_Delay(DELAY);
		}
	}
	if (int_1==int_2)
	{
		pj_joueur->int_double_tire++;
	}
	else 
	{
		pj_joueur->int_double_tire=0;
	}
	
	//si le joueur a fait 3 doubles il va en prison
	if (pj_joueur->int_double_tire == 3)
	{
		affich_message(surf_ecran, surf_centre, "PRISON" , "Vous avez fait 3 doubles consécutifs.", MESSAGE_NORMAL);
		aller_en_prison_jeton(surf_ecran, pj_joueur,plateau);
		pj_joueur->int_double_tire = 0;
	}
		
	destruction_des(surf_des);
	
	return(int_1+int_2);
	//return(2);
}

void reculer_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre ,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16])
{
	int int_position;
	int int_position2;
	int i;
	
	i=0;
	
	joueur* pj_joueur_test;
	
	//on le fait avancer case par case
	for (i=0;i<3;i++)
	{
		//on réactualise la case ou se trouve le joueur afin qu'il efface le jeton
		affich_case(surf_ecran,plateau[pj_joueur->int_position]);
		//on avance le joueur de 1 en faisant attention que la position reste dans les 40 cases du plateau
		pj_joueur->int_position=(pj_joueur->int_position+39)%40;
		//on compte le nombre de personne sur la case ou doit être afficher le joueur actuel
		int_position=nombre_joueur_case(pj_joueur);
		//on affiche le joueur sur la nouvelle case
		affich_joueur(surf_ecran, pj_joueur,int_position+1, plateau[pj_joueur->int_position]);
		// on lui indique que le premier joueur test est le suivant
		pj_joueur_test=pj_joueur->pjoueur_suivant;
		int_position2=0;
		//on verifie pour chaque joueur s'il se trouvait là où était le joueur avant
		while (pj_joueur_test != pj_joueur)
		{
			if (pj_joueur_test->int_position==((pj_joueur->int_position)-1))
			{
				int_position2++;
				//on l'affiche sur la case:
				affich_joueur(surf_ecran, pj_joueur_test,int_position2, plateau[pj_joueur_test->int_position]);
			}
			pj_joueur_test=pj_joueur_test->pjoueur_suivant;
		}
		//on rafraichi l'affichage
		SDL_Flip(surf_ecran);
		//petit delay pour que l'utilisateur puisse apprécier l'affichage
		SDL_Delay(DELAY);
	}
	
	traitement_arrive_case(surf_ecran, surf_centre,plateau,pj_joueur, bureau_de_krystel, bureau_de_nadege, 0);
}
	
//faire simplement avancer le jeton du joueur
void avancer_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, int int_nb_tire ,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16])
{
	int int_position;
	int int_position2;
	
	joueur* pj_joueur_test;
	
	//on le fait avancer case par case
	for (int i=0;i<int_nb_tire;i++)
	{
		//on réactualise la case ou se trouve le joueur afin qu'il efface le jeton
		affich_case(surf_ecran,plateau[pj_joueur->int_position]);
		//on avance le joueur de 1 en faisant attention que la position reste dans les 40 cases du plateau
		pj_joueur->int_position=(pj_joueur->int_position+1)%40;
		//on compte le nombre de personne sur la case ou doit être afficher le joueur actuel
		int_position=nombre_joueur_case(pj_joueur);
		//on affiche le joueur sur la nouvelle case
		affich_joueur(surf_ecran, pj_joueur,int_position+1, plateau[pj_joueur->int_position]);
		// on lui indique que le premier joueur test est le suivant
		pj_joueur_test=pj_joueur->pjoueur_suivant;
		int_position2=0;
		//on verifie pour chaque joueur s'il se trouvait là où était le joueur avant
		while (pj_joueur_test != pj_joueur)
		{
			if (pj_joueur_test->int_position==((pj_joueur->int_position)-1))
			{
				int_position2++;
				//on l'affiche sur la case:
				affich_joueur(surf_ecran, pj_joueur_test,int_position2, plateau[pj_joueur_test->int_position]);
			}
			pj_joueur_test=pj_joueur_test->pjoueur_suivant;
		}
		//on rafraichi l'affichage
		SDL_Flip(surf_ecran);
		//petit delay pour que l'utilisateur puisse apprécier l'affichage
		SDL_Delay(DELAY);
		
		//si il se trouve sur la case départ 
		if (pj_joueur->int_position==0)
		{
			//on effectue le traitement adequat
			traitement_case_depart (surf_ecran,pj_joueur);
			//On informe le joueur qu'il a gagné 2000 Fintz
			affich_msg_info(surf_ecran, surf_centre, NULL, "Après une dure journée de labeur à bosser comme un dingue, vous rentrez chez vous et vous touchez votre argent de poche d'un montant de 2000 Fintz.");
			//Affichage du panneau avec l'argent mise à jour
			affich_panneau_joueur(surf_ecran,pj_joueur);
		}
	}	
	traitement_arrive_case(surf_ecran, surf_centre,plateau,pj_joueur, bureau_de_krystel, bureau_de_nadege, int_nb_tire);
}

void aller_a_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, int int_position_voulue ,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16], int delai)
{
	int int_position;
	int int_position2;
	joueur* pj_joueur_test;
	
	//on le fait avancer case par case	
	while (pj_joueur->int_position != int_position_voulue)
	{
		//on réactualise la case ou se trouve le joueur afin qu'il efface le jeton
		affich_case(surf_ecran,plateau[pj_joueur->int_position]);
		//on avance le joueur de 1 en faisant attention que la position reste dans les 40 cases du plateau
		pj_joueur->int_position=(pj_joueur->int_position+1)%40;
		//on compte le nombre de personne sur la case ou doit être afficher le joueur actuel
		int_position=nombre_joueur_case(pj_joueur);
		//on affiche le joueur sur la nouvelle case
		affich_joueur(surf_ecran, pj_joueur, int_position+1, plateau[pj_joueur->int_position]);
		
		// on lui indique que le premier joueur test est le suivant
		pj_joueur_test=pj_joueur->pjoueur_suivant;
		int_position2=0;
		//on verifie pour chaque joueur s'il se trouvait là où était le joueur avant
		while (pj_joueur_test != pj_joueur)
		{
			if (pj_joueur_test->int_position==((pj_joueur->int_position)-1))
			{
				int_position2++;
				//on l'affiche sur la case:
				affich_joueur(surf_ecran, pj_joueur_test,int_position2, plateau[pj_joueur_test->int_position]);
			}
			pj_joueur_test=pj_joueur_test->pjoueur_suivant;
		}
		//on rafraichi l'affichage
		SDL_Flip(surf_ecran);
		//petit delay pour que l'utilisateur puisse apprécier l'affichage
		SDL_Delay(delai);
		//si il se trouve sur la case départ 
		if (pj_joueur->int_position==0)
		{
			//On informe le joueur qu'il a gagné 2000 Fintz
			affich_msg_info(surf_ecran, surf_centre, NULL, "Après une dure journée de labeur à bosser comme un dingue, vous rentrez chez vous et vous touchez votre argent de poche d'un montant de 2000 Fintz.");
			//on effectue le traitement adequat
			traitement_case_depart (surf_ecran,pj_joueur);
		}
	}
	//on lance la fonction traitement associé à la case ou il s'arrete
	//plateau[pj_joueur->int_position]->ptraitement(pj_joueur->int_position);
	
	traitement_arrive_case(surf_ecran, surf_centre,plateau,pj_joueur, bureau_de_krystel, bureau_de_nadege, 0);
}

void aller_en_prison_jeton (SDL_Surface* surf_ecran, joueur* pj_joueur, cases** plateau)
{
	int int_position;
	int int_position2;
	
	joueur* pj_joueur_test;

	
	//on réactualise la case ou se trouve le joueur afin qu'il efface le jeton
	affich_case(surf_ecran,plateau[pj_joueur->int_position]);
	
	// on lui indique que le premier joueur test est le suivant
	pj_joueur_test=pj_joueur->pjoueur_suivant;
	int_position2=0;
	//on verifie pour chaque joueur s'il se trouvait là où était le joueur avant
	while (pj_joueur_test != pj_joueur)
	{
		if (pj_joueur_test->int_position==((pj_joueur->int_position)-1))
		{
			int_position2++;
			//on l'affiche sur la case:
			affich_joueur(surf_ecran, pj_joueur_test,int_position2, plateau[pj_joueur_test->int_position]);
		}
		pj_joueur_test=pj_joueur_test->pjoueur_suivant;
	}
	
	//on envoi le jeton directement en prison
	pj_joueur->int_position=10;
	//on indique qu'il est emprisonner
	pj_joueur->bool_laurence=true;
	
	//on compte le nombre de personne sur la case ou doit être afficher le joueur actuel
	int_position=nombre_joueur_case(pj_joueur);
	
	//on affiche le joueur sur la nouvelle case
	affich_joueur(surf_ecran, pj_joueur, int_position+1, plateau[pj_joueur->int_position]);
	
	//on rafraichi l'affichage
	SDL_Flip(surf_ecran);
}

bool traitement_achat (cases* case_achetee, joueur* joueur_actuel)
{
	//on verifie si la case n'appartient a aucun joueur

	//on détermine le type de la case
	if (case_achetee->int_type==SALLE)
	{
		//on verifie si le joueur a assez d'argent pour l'acheter et si la case n'appartient a personne
		if ((joueur_actuel->int_argent >= case_achetee->case_salle.int_prix) && (case_achetee->case_salle.pjoueur_joueur==NULL))
		{
			//on effectue la transaction
			joueur_actuel->int_argent=joueur_actuel->int_argent-case_achetee->case_salle.int_prix;
			joueur_actuel->propriete=insertion_bonne_place_propriete(joueur_actuel->propriete,case_achetee);
			case_achetee->case_salle.pjoueur_joueur=joueur_actuel;
			
			return(true);
		}
		else
		{
			return(false);
		}
	}
	else 
	{
		if((case_achetee->int_type == BDE) || (case_achetee->int_type == BDS))
		{
			//on verifie si le joueur a assez d'argent pour l'acheter
			if ((joueur_actuel->int_argent >= case_achetee->case_association.int_prix) && (case_achetee->case_association.pjoueur_joueur==NULL))
			{
				//on effectue la transaction
				joueur_actuel->int_argent=joueur_actuel->int_argent-case_achetee->case_association.int_prix;
				joueur_actuel->propriete=insertion_bonne_place_propriete(joueur_actuel->propriete,case_achetee);
				case_achetee->case_association.pjoueur_joueur=joueur_actuel;
			
				return(true);
			}
		}
		else
		{
			if(    (case_achetee->int_type == LC_WC) 
				|| (case_achetee->int_type == LC_RU)
				|| (case_achetee->int_type == LC_PARKING)
				|| (case_achetee->int_type == LC_ASCENSEUR))
				{
					//on verifie si le joueur a assez d'argent pour l'acheter
					if ((joueur_actuel->int_argent >= case_achetee->case_lieu_commun.int_prix) && (case_achetee->case_lieu_commun.pjoueur_joueur==NULL))
					{
						//on effectue la transaction
						joueur_actuel->int_argent=joueur_actuel->int_argent-case_achetee->case_lieu_commun.int_prix;
						joueur_actuel->propriete=insertion_bonne_place_propriete(joueur_actuel->propriete,case_achetee);
						case_achetee->case_lieu_commun.pjoueur_joueur=joueur_actuel;
						return(true);
					}
					else
					{
						return(false);
					}
				}
			}
		}
		return(false);
}


void traitement_case_depart (SDL_Surface* surf_ecran,joueur* pj_joueur)
{
	//on ajoute 2000 Fintz au compte du joueur
	pj_joueur->int_argent=(pj_joueur->int_argent)+2000;
	pj_joueur->bool_debut=false;
}


bool traitement_payer_loyer (joueur* joueur_qui_paye, joueur* joueur_paye, int int_montant)
{
	//si le joueur a assez d'argent
	if (joueur_qui_paye->int_argent >= int_montant)
	{
		//il paye
		joueur_qui_paye->int_argent=joueur_qui_paye->int_argent-int_montant;
		joueur_paye->int_argent=joueur_paye->int_argent+int_montant;
		return(true);
	}
	else
	{
		return(false);
	}
}

bool traitement_mise_en_hypotheque (joueur* joueur_actuel, cases* case_hypothequee)
{
	//on agit selon le type de la case
	switch (case_hypothequee->int_type)
	{
		case SALLE:
			//si la case n'est pas déja hypotheque
			if (!(case_hypothequee->case_salle.bool_hypotheque))
			{
				joueur_actuel->int_argent=joueur_actuel->int_argent + case_hypothequee->case_salle.int_valeur_hypotheque;
				case_hypothequee->case_salle.bool_hypotheque=true;
				return(case_hypothequee->case_salle.bool_hypotheque);
			}
			break;
						
		case BDS:
			if (!(case_hypothequee->case_association.bool_hypotheque))
			{
				joueur_actuel->int_argent=joueur_actuel->int_argent + case_hypothequee->case_association.int_valeur_hypotheque;
				case_hypothequee->case_association.bool_hypotheque=true;
				return(case_hypothequee->case_association.bool_hypotheque);
			}
			break;		
		
		case BDE:
			if (!(case_hypothequee->case_association.bool_hypotheque))
			{
				joueur_actuel->int_argent=joueur_actuel->int_argent + case_hypothequee->case_association.int_valeur_hypotheque;
				case_hypothequee->case_association.bool_hypotheque=true;
				return(case_hypothequee->case_association.bool_hypotheque);
			}
			break;
			
		case LC_WC:
			if (!(case_hypothequee->case_lieu_commun.bool_hypotheque))
			{
				joueur_actuel->int_argent=joueur_actuel->int_argent + case_hypothequee->case_lieu_commun.int_valeur_hypotheque;
				case_hypothequee->case_lieu_commun.bool_hypotheque=true;
				return(case_hypothequee->case_lieu_commun.bool_hypotheque);
			}
			break;
			
		case LC_ASCENSEUR:
			if (!(case_hypothequee->case_lieu_commun.bool_hypotheque))
			{
				joueur_actuel->int_argent=joueur_actuel->int_argent + case_hypothequee->case_lieu_commun.int_valeur_hypotheque;
				case_hypothequee->case_lieu_commun.bool_hypotheque=true;
				return(case_hypothequee->case_lieu_commun.bool_hypotheque);
			}
			break;
						
		case LC_RU:
			if (!(case_hypothequee->case_lieu_commun.bool_hypotheque))
			{
				joueur_actuel->int_argent=joueur_actuel->int_argent + case_hypothequee->case_lieu_commun.int_valeur_hypotheque;
				case_hypothequee->case_lieu_commun.bool_hypotheque=true;
				return(case_hypothequee->case_lieu_commun.bool_hypotheque);
			}
			break;
						
		case LC_PARKING:						
			if (!(case_hypothequee->case_lieu_commun.bool_hypotheque))
			{
				joueur_actuel->int_argent=joueur_actuel->int_argent + case_hypothequee->case_lieu_commun.int_valeur_hypotheque;
				case_hypothequee->case_lieu_commun.bool_hypotheque=true;
				return(case_hypothequee->case_lieu_commun.bool_hypotheque);
			}
			break;
			
		default:
			return(false);
			break;
	}
	return(false);
}

int traitement_loyer_association(joueur* joueur_paye, int int_nb_tire)
{
	possession* propriete_test;
	int i; //compteur
	
	i=0;
	
	propriete_test=joueur_paye->propriete;
	//on comptabilise le nombre de case association du joueur payé
	while (propriete_test != NULL)
	{
		if ((propriete_test->propriete->int_type == BDS) || (propriete_test->propriete->int_type == BDE))
		{
			i++;
		}
		
		propriete_test=propriete_test->suivant;
	}
	//on a ainsi compatibilisé le nombe d'association du joueur
	//si il n'y a qu'une on multiplie les nombre des dés par 40
	if (i == 1)
	{
		return(int_nb_tire*40);		
	}
	else 
	{
		return(int_nb_tire*100);
	}
}

int traitement_loyer_lieu_commun(joueur* pj_joueur)
{
	
	possession* propriete_temp;
	int i;
	i=0;

	propriete_temp=pj_joueur->propriete;
	
	while(propriete_temp!=NULL)
	{
		if (  (propriete_temp->propriete->int_type<=LC_PARKING)
			&& (propriete_temp->propriete->int_type>=LC_WC))
		{
			i++;
		}
		propriete_temp=propriete_temp->suivant;
	}
	
	return(i*250);
}

bool traitement_rachat_hypotheque(joueur* joueur_actuel, cases* case_hypothequee)
{
	//on agit selon le type de la case
	switch (case_hypothequee->int_type)
	{
		case SALLE:
			//si le joueur a assez d'argent
			if (joueur_actuel->int_argent >= case_hypothequee->case_salle.int_valeur_hypotheque+case_hypothequee->case_salle.int_valeur_hypotheque*0.10)
			{
			//il rachete l'hypothèque
			joueur_actuel->int_argent=(int)(joueur_actuel->int_argent - (case_hypothequee->case_salle.int_valeur_hypotheque+case_hypothequee->case_salle.int_valeur_hypotheque*0.10));
			case_hypothequee->case_salle.bool_hypotheque=false;
			}
			return(true);
			break;
						
		case BDS:
			//si le joueur a assez d'argent
			if (joueur_actuel->int_argent >= (case_hypothequee->case_association.int_valeur_hypotheque+case_hypothequee->case_association.int_valeur_hypotheque*0.10))
			{
			//il rachete l'hypothèque
			joueur_actuel->int_argent=(int)(joueur_actuel->int_argent - (case_hypothequee->case_association.int_valeur_hypotheque+case_hypothequee->case_association.int_valeur_hypotheque*0.10));
			case_hypothequee->case_association.bool_hypotheque=false;
			}
			return(true);
			break;		
		
		case BDE:
			//si le joueur a assez d'argent
			if (joueur_actuel->int_argent >= (case_hypothequee->case_association.int_valeur_hypotheque+case_hypothequee->case_association.int_valeur_hypotheque*0.10))
			{
			//il rachete l'hypothèque
			joueur_actuel->int_argent=(int)(joueur_actuel->int_argent - (case_hypothequee->case_association.int_valeur_hypotheque+case_hypothequee->case_association.int_valeur_hypotheque*0.10));
			case_hypothequee->case_association.bool_hypotheque=false;
			}
			return(true);
			break;	
			
		case LC_WC:
			//si le joueur a assez d'argent
			if (joueur_actuel->int_argent >=(case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10))
			{
			//il rachete l'hypothèque
			joueur_actuel->int_argent=(int)(joueur_actuel->int_argent - (case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10));
			case_hypothequee->case_lieu_commun.bool_hypotheque=false;
			}
			return(true);
			break;
			
		case LC_ASCENSEUR:
			//si le joueur a assez d'argent
			if (joueur_actuel->int_argent >= (case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10))
			{
			//il rachete l'hypothèque
			joueur_actuel->int_argent=(int)(joueur_actuel->int_argent - (case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10));
			case_hypothequee->case_lieu_commun.bool_hypotheque=false;
			}
			return(true);
			break;
						
		case LC_RU:
			//si le joueur a assez d'argent
			if (joueur_actuel->int_argent >= (case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10))
			{
			//il rachete l'hypothèque
			joueur_actuel->int_argent=(int)(joueur_actuel->int_argent - (case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10));
			case_hypothequee->case_lieu_commun.bool_hypotheque=false;
			}
			return(true);
			break;
						
		case LC_PARKING:						
			//si le joueur a assez d'argent
			if (joueur_actuel->int_argent >= (case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10))
			{
			//il rachete l'hypothèque
			joueur_actuel->int_argent=(int)(joueur_actuel->int_argent - (case_hypothequee->case_lieu_commun.int_valeur_hypotheque+case_hypothequee->case_lieu_commun.int_valeur_hypotheque*0.10));
			case_hypothequee->case_lieu_commun.bool_hypotheque=false;
			}
			return(true);
			break;
			
		default:
			return(false);
			break;
	}
	return(false);
}

bool traitement_augmentation_niveau(cases* pcase, joueur* pj_joueur)
{
	//on vérifie si le joueur a assez d'argent
	if (pj_joueur->int_argent >= pcase->case_salle.int_prix_niveau)
	{
		//il les achète
		pj_joueur->int_argent=(pj_joueur->int_argent) - (pcase->case_salle.int_prix_niveau);
		pcase->case_salle.int_niveau=pcase->case_salle.int_niveau + 1;
		return(true);
	}
	else
	{
		return(false);
	}	
}

void traitement_diminution_niveau(cases* pcase, joueur* pj_joueur)
{
		//il les vend
		pj_joueur->int_argent=(pj_joueur->int_argent) + ((pcase->case_salle.int_prix_niveau)/2);
		pcase->case_salle.int_niveau=pcase->case_salle.int_niveau - 1;
}

void traitement_arrive_case (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau,joueur* pj_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16],int int_nombre_tire)
{
	char message[512];
	
	int action_possible_resultat;
	
	action_possible_resultat=action_possible(plateau, 0, pj_joueur, ARRIVE_CASE, int_nombre_tire);
	
	
	if(plateau[pj_joueur->int_position]->int_type==SALLE)
	{ 
		if ((plateau[pj_joueur->int_position]->case_salle.pjoueur_joueur!=pj_joueur) && (plateau[pj_joueur->int_position]->case_salle.pjoueur_joueur != NULL))
		{
			//on lui affiche un message lui indiquant ce qu'il paye et a qui
			sprintf(message, "Vous êtes chez %s : vous payer le loyer %d Fintz.", plateau[pj_joueur->int_position]->case_salle.pjoueur_joueur->str_nom, plateau[pj_joueur->int_position]->case_salle.int_prix/10*(plateau[pj_joueur->int_position]->case_salle.int_niveau+1));
			traitement_payer_loyer(pj_joueur, plateau[pj_joueur->int_position]->case_salle.pjoueur_joueur, plateau[pj_joueur->int_position]->case_salle.int_prix/10*(plateau[pj_joueur->int_position]->case_salle.int_niveau+1));
			affich_message(surf_ecran,surf_centre,"Loyer",message,MESSAGE_NORMAL);
		}
		else 
		{
			affich_validation_propriete(surf_ecran, surf_centre, plateau[pj_joueur->int_position],pj_joueur, action_possible_resultat);
			//Affichage du panneau contenant les informations joueurs
			affich_panneau_possessions(surf_ecran,pj_joueur);

			//Affichage du panneau contenant les informations joueurs
			affich_panneau_joueur(surf_ecran,pj_joueur);
		}
	}
	else if (plateau[pj_joueur->int_position]->int_type==BUREAU_KRYSTEL)
	{
		//le joueur tire une carte et agit en fonction d'elle
		traitement_bureau(surf_ecran,surf_centre,plateau, pj_joueur,bureau_de_krystel,bureau_de_krystel, bureau_de_nadege,BUREAU_KRYSTEL);
	}
	else if (plateau[pj_joueur->int_position]->int_type==BUREAU_NADEGE)
	{
		//le joueur tire une carte et agit en fonction d'elle
		traitement_bureau(surf_ecran,surf_centre,plateau, pj_joueur,bureau_de_nadege, bureau_de_krystel, bureau_de_nadege,BUREAU_NADEGE);
	}	
	else if (plateau[pj_joueur->int_position]->int_type==SP_BUREAU_LAURENCE)
	{
		traitement_bureau_laurence(surf_ecran, surf_centre, plateau, pj_joueur, bureau_de_krystel, bureau_de_nadege);
	}
	else if (plateau[pj_joueur->int_position]->int_type == SP_TABLEAU)
	{
		//Message disant qu'il faut aller en prison
		affich_message(surf_ecran, surf_centre, "Convocation", "Vous venez d'être convoqué au bureau de Laurence. Prenez votre courage à deux mains et foncez dans son antre ! (bonne chance, les développeurs qui prient pour vous)", MESSAGE_INFO_PRISON);
		//on envoi le joueur directement en prison
		aller_en_prison_jeton(surf_ecran, pj_joueur,plateau);
	}
	else if (plateau[pj_joueur->int_position]->int_type == SP_MACHINE_CAFE)	
	{
		//le joueur récolte l'argent de la machine a café
		traitement_machine_a_cafe(surf_ecran, surf_centre, plateau, pj_joueur);
	}
	else if (plateau[pj_joueur->int_position]->int_type == SOIREE_GALA || plateau[pj_joueur->int_position]->int_type == SOIREE_AREA)	
	{
		traitement_soiree(surf_ecran, surf_centre ,pj_joueur, plateau);
	}
	else if (  (plateau[pj_joueur->int_position]->int_type == LC_WC)
			|| (plateau[pj_joueur->int_position]->int_type == LC_ASCENSEUR)
			|| (plateau[pj_joueur->int_position]->int_type == LC_RU)
			|| (plateau[pj_joueur->int_position]->int_type == LC_PARKING))
	{
		//si la case appartient a un adversaire
		if ((plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur!=pj_joueur) && (plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur != NULL))
		{
			//on prépare le message et il paye en même temps
			sprintf(message, "Vous êtes chez %s : vous payer le loyer %d Fintz.", plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur->str_nom, traitement_loyer_lieu_commun(plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur));
			//on lui fait payer le loyer en fonction du nombre de 
			traitement_payer_loyer(pj_joueur, plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur, traitement_loyer_lieu_commun(plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur));
			//on affiche le message
			affich_message(surf_ecran,surf_centre,"Loyer",message,MESSAGE_NORMAL);
		}
		else 
		{
			affich_validation_propriete(surf_ecran, surf_centre, plateau[pj_joueur->int_position],pj_joueur, action_possible_resultat);
			//Affichage du panneau contenant les informations joueurs
			affich_panneau_possessions(surf_ecran,pj_joueur);

			//Affichage du panneau contenant les informations joueurs
			affich_panneau_joueur(surf_ecran,pj_joueur);
		}
	}
	else if (  (plateau[pj_joueur->int_position]->int_type == BDE)
			|| (plateau[pj_joueur->int_position]->int_type == BDS))
	{
		//si la case appartient à un adversaire
		if ((plateau[pj_joueur->int_position]->case_association.pjoueur_joueur!=pj_joueur) && (plateau[pj_joueur->int_position]->case_association.pjoueur_joueur != NULL))
		{
			//on prépare le message
			sprintf(message, "Vous êtes chez %s : vous payer le loyer %d Fintz.", plateau[pj_joueur->int_position]->case_association.pjoueur_joueur->str_nom, traitement_loyer_association(plateau[pj_joueur->int_position]->case_association.pjoueur_joueur, int_nombre_tire));
			//il paye
			traitement_payer_loyer(pj_joueur, plateau[pj_joueur->int_position]->case_association.pjoueur_joueur,traitement_loyer_association(plateau[pj_joueur->int_position]->case_association.pjoueur_joueur, int_nombre_tire));
			
			//on affiche le message
			affich_message(surf_ecran,surf_centre,"Loyer",message,MESSAGE_NORMAL);
		}
		else 
		{
			affich_validation_propriete(surf_ecran, surf_centre, plateau[pj_joueur->int_position],pj_joueur, action_possible_resultat);
			//Affichage du panneau contenant les informations joueurs
			affich_panneau_possessions(surf_ecran,pj_joueur);

			//Affichage du panneau contenant les informations joueurs
			affich_panneau_joueur(surf_ecran,pj_joueur);
		}
		
	}
}

void traitement_soiree (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur, cases** plateau)
{
	//le joueur peut-être soit sur le gala soit sur l'area
	if (pj_joueur->int_position==38)
	{
		//le joueur se trouve à la soirée du gala
		affich_message(surf_ecran,surf_centre,"Cotisation pour le Gala","Payez 1500 Fintz.",MESSAGE_NORMAL);
	}
	else 
	{
		//le joueur se trouve sur la case area
		affich_message(surf_ecran,surf_centre,"Soirée à l'Area !","Payez 1500 Fintz.",MESSAGE_NORMAL);
	}
	//on retire au joueur l'argent
	pj_joueur->int_argent=pj_joueur->int_argent - plateau[pj_joueur->int_position]->case_soiree.int_prix;
	//on ajoute l'argent à la machine a café
	plateau[20]->machine_a_cafe.int_argent=plateau[20]->machine_a_cafe.int_argent + plateau[pj_joueur->int_position]->case_soiree.int_prix;
	
}

void traitement_machine_a_cafe (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur)
{
	char message[128];
	
	//on donne l'argent au joueur
	pj_joueur->int_argent=pj_joueur->int_argent+plateau[20]->machine_a_cafe.int_argent;
	sprintf(message,"Vous recevez %d Fintz de la machine à café!", plateau[20]->machine_a_cafe.int_argent);
	//on vide la machine a café
	plateau[20]->machine_a_cafe.int_argent=0;
	
	
	
	affich_message(surf_ecran,surf_centre,"Machine à café",message,MESSAGE_NORMAL);
	
}
void traitement_bureau_laurence (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16])
{
	int int_des;
	int int_choix;
	
	//on verifie si le joueur est emprisonner
	if (pj_joueur->bool_laurence==true)
	{
		//il lance les dés afin d'essayer de faire un double
		int_des=lancer_des(surf_ecran, surf_centre,pj_joueur, plateau);

		if (pj_joueur->int_double_tire == 1)
		{
			//le jeton est libéré
			pj_joueur->bool_laurence=false;
			pj_joueur->int_laurence=0;
			affich_msg_info(surf_ecran, surf_centre, NULL, "Vous venez de faire un double ! Vous pouvez enfin sortir du bureau de Laurence.");
			avancer_jeton(surf_ecran, surf_centre, int_des, pj_joueur,plateau,bureau_de_krystel, bureau_de_nadege);
		}
		//sinon on verifie si les trois tours de prison n'ont pas aboutis
		else if (pj_joueur->int_laurence == 3)
		{
			//on le libère
			pj_joueur->bool_laurence=false;
			pj_joueur->int_laurence=0;
			//on le fait payer les 500 Fintz
			pj_joueur->int_argent -= 500;
			affich_message(surf_ecran, surf_centre, "Libération !", "Laurence à eu pitié de vous et elle vous relache donc après 3 tours de souffrances ! Toutefois, elle en profite au passage pour vous soulager de 500 Fintz", MESSAGE_NORMAL);
			avancer_jeton(surf_ecran, surf_centre, int_des, pj_joueur,plateau,bureau_de_krystel, bureau_de_nadege);
		}
		else 
		{
			int_choix=affich_message(surf_ecran,surf_centre,"Bureau de Laurence","Que vous voulez vous faire ? Tenter vainement un double? Soudoyer Laurence avec 500 Fintz pour qu'elle vous laisse sortir? Ou juste faire genre le type qui fait vanne de faire semblant d'être malade grâce au certificat médical?",MESSAGE_PRISON);
			switch (int_choix)
			{
				//Attendre
				case MSG_BTN_1: 
					//on indique qu'il a passe un tour de plus
					affich_msg_info(surf_ecran, surf_centre, NULL, "Brave et courage, vous decidez de restez subir le couroux de Laurence dans son bureau.");
					pj_joueur->int_laurence++;
					break;
				//Payer
				case MSG_BTN_2:
					affich_msg_info(surf_ecran, surf_centre, NULL, "Vous venez de soudoyer Laurence avec 500 Fintz. Vous pourrez sortir de son bureau dès le prochain tour.");
					pj_joueur->bool_laurence=false;
					pj_joueur->int_laurence=0;
					//on lui fait payer les 500 Fintz à la machine a café
					//on retire au joueur l'argent
					pj_joueur->int_argent=pj_joueur->int_argent - 500;
					//on ajoute l'argent à la machine a café
					plateau[20]->machine_a_cafe.int_argent=plateau[20]->machine_a_cafe.int_argent + 500;
					break;
				//Certificat
				case MSG_BTN_3:
					if (pj_joueur->int_certificat > 0)
						{
							affich_msg_info(surf_ecran, surf_centre, NULL, "Vous venez d'utiliser le certificat médical. Vous pourrez sortir du bureau de Laurence dès le prochain tour.");
							pj_joueur->bool_laurence=false;
							pj_joueur->int_laurence=0;
							pj_joueur->int_certificat-=1;
						}
					else
						{
							affich_msg_info(surf_ecran, surf_centre, NULL, "Désolé mais vous n'avez plus de certificat médical ! Mais c'était bien tenté !");
							//on indique qu'il a passe un tour de plus
							pj_joueur->int_laurence++;
						}
					break;
				default: 
					break;
			}
			
		}
	}
}


void traitement_bureau(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur, information* le_bureau[16], information* bureau_de_krystel[16], information* bureau_de_nadege[16], int int_id_bureau)
{
	information* carte;
	joueur* pjoueur_encours;
	possession* propriete_encours;
	int i;
	int k;
	
	//Chaine temporaire
	char str_temp[256];
	
	k=0;
	
	//========================> TEMPORAIRE
	//strcpy(bureau_de_nadege[0]->texte,"Inspection de la CTI : versez 400 Fintz par niveau pour chacune de vos salles.");
	//bureau_de_nadege[0]->type=CTI;
	//bureau_de_nadege[0]->valeur=-400;
	//strcpy(bureau_de_nadege[0]->texte,"Un p*t*in de poteau de m*** a encore traversé la route en dehors des clous. Payez 300 Fintz de réparation.");
	//bureau_de_nadege[0]->type=ARGENT;
	//bureau_de_nadege[0]->valeur=-300;
	//cout << "TEST POUR LA CTI" << endl;
	//cout << "Joueur : " << pj_joueur->str_nom << endl;
	//========================> TEST POUR LA CARTE CTI
	
	//on traite toute cette partie avec la première carte du tableau
	
	if (int_id_bureau == BUREAU_KRYSTEL)
	{
		affich_message(surf_ecran,surf_centre,"Bureau de Krystel",le_bureau[0]->texte,MESSAGE_KRYSTEL);
	}
	else 
	{
		affich_message(surf_ecran,surf_centre,"Bureau de Nadege",le_bureau[0]->texte,MESSAGE_NADEGE);
	}
	
	//traitement selon la carte
	if (le_bureau[0]->type == ARGENT)
	{
		//ajoute ou enlève de l'argent au joueur
		pj_joueur->int_argent+=le_bureau[0]->valeur;
		//on ajoute l'argent à la machine a café si c'est le joueur qui paye
		if (le_bureau[0] < 0)
		{
			plateau[20]->machine_a_cafe.int_argent -= le_bureau[0]->valeur;
		}
	}
	else if(le_bureau[0]->type == POSITION)
	{
		if (le_bureau[0]->valeur < 0)
		{
			reculer_jeton(surf_ecran, surf_centre, pj_joueur,plateau,bureau_de_krystel, bureau_de_nadege);
		}
		else
		{
			//on avance le jeton jusqu'a la case voulue
			aller_a_jeton(surf_ecran, surf_centre, le_bureau[0]->valeur, pj_joueur,plateau,bureau_de_krystel, bureau_de_nadege,DELAY/3);
		}
	}
	else if(le_bureau[0]->type == ASTRID)
	{
		traitement_bureau(surf_ecran,surf_centre,plateau, pj_joueur,bureau_de_krystel, bureau_de_krystel, bureau_de_nadege,BUREAU_KRYSTEL);
	}
	else if(le_bureau[0]->type == ANNIVERSAIRE)
	{
		pjoueur_encours=pj_joueur->pjoueur_suivant;
		//on prend l'argent à chaque joueur et on le donne à l'actuel
		while (pjoueur_encours != pj_joueur)
		{
			pjoueur_encours->int_argent = pjoueur_encours->int_argent-le_bureau[0]->valeur;
			k++;
			pjoueur_encours=pjoueur_encours->pjoueur_suivant;
		}
		//on donne l'argent récolté au joueur
		pj_joueur->int_argent = pj_joueur->int_argent+((le_bureau[0]->valeur)*k);			
	}
	else if(le_bureau[0]->type == CTI)
	{	
		propriete_encours=pj_joueur->propriete;	
		//on regarde chaque propriété du joueur
		
		k=0;
		
		while (propriete_encours != NULL)
		{
			if (propriete_encours->propriete->int_type == SALLE)
			{
				k=k+(propriete_encours->propriete->case_salle.int_niveau);
			}
			propriete_encours=propriete_encours->suivant;
		}
		//on retire l'argent au joueur
		pj_joueur->int_argent = pj_joueur->int_argent+((le_bureau[0]->valeur)*k);		
		//on l'ajoute à la machine à café
		plateau[20]->machine_a_cafe.int_argent=plateau[20]->machine_a_cafe.int_argent+(-(le_bureau[0]->valeur)*k);
		//On enregistre la somme d'argent pour le message d'information
		sprintf(str_temp, "La CTI vient de vous prélever %d Fintz", -(le_bureau[0]->valeur)*k);
		//Message d'information de prélévement
		affich_msg_info(surf_ecran, surf_centre, "Prélévement CTI", str_temp);
	}
	else if (le_bureau[0]->type == CARTE_LAURENCE)
	{
		//on envoie le joueur directement en prison
		aller_en_prison_jeton(surf_ecran, pj_joueur, plateau);
	}
	else if(le_bureau[0]->type == CERTIFICAT)
	{
		//le joueur possède un certificat de plus
		pj_joueur->int_certificat++;
	}
	
	//puis on remet la carte à la fin du tableau

	carte=le_bureau[0];

	for (i = 0; i < 15; i++)
	{
		le_bureau[i]=le_bureau[i+1];
		le_bureau[15]=carte;
	}
}

void traitement_elimination_joueur (joueur* joueur_eliminer)
{
	possession* propriete_joueur_encours;
	possession* propriete_joueur_precedent;
	joueur* pj_joueur_precedent;
	joueur* pj_joueur_encours;
	
	propriete_joueur_encours=joueur_eliminer->propriete;
	
	//il faut libérer tous les propriétés du joueur
	//pour chaque propriété du joueur
	while (propriete_joueur_encours != NULL)
	{
		//on test le type de la case
		switch (propriete_joueur_encours->propriete->int_type)
		{
			case SALLE: 
				//la case n'a plus de propriétère
				propriete_joueur_encours->propriete->case_salle.pjoueur_joueur=NULL;
				//la case n'a plus de maison
				propriete_joueur_encours->propriete->case_salle.int_niveau=0;
				break;
			case BDE:
				//la case n'a plus de propriétère
				propriete_joueur_encours->propriete->case_association.pjoueur_joueur=NULL;
				break;
			case BDS:
				//la case n'a plus de propriétère
				propriete_joueur_encours->propriete->case_association.pjoueur_joueur=NULL;
				break;
			case LC_WC:
				//la case n'a plus de propriétère
				propriete_joueur_encours->propriete->case_lieu_commun.pjoueur_joueur=NULL;
				break;
			case LC_PARKING:
				//la case n'a plus de propriétère
				propriete_joueur_encours->propriete->case_lieu_commun.pjoueur_joueur=NULL;
				break;
			case LC_RU:
				//la case n'a plus de propriétère
				propriete_joueur_encours->propriete->case_lieu_commun.pjoueur_joueur=NULL;
				break;
			case LC_ASCENSEUR:
				//la case n'a plus de propriétère
				propriete_joueur_encours->propriete->case_lieu_commun.pjoueur_joueur=NULL;
				break;
			default:
				break;
		}
		
		propriete_joueur_precedent = propriete_joueur_encours;
		propriete_joueur_encours = propriete_joueur_encours->suivant;
		delete propriete_joueur_precedent;
	}
	//ensuite on libère la place en mémoire du joueur
	//on trouve le joueur précédent celui éliminer
	pj_joueur_precedent=joueur_eliminer;
	pj_joueur_encours=joueur_eliminer->pjoueur_suivant;
	
	while (pj_joueur_encours != joueur_eliminer)
	{
		pj_joueur_precedent=pj_joueur_encours;
		pj_joueur_encours=pj_joueur_encours->pjoueur_suivant;
	}
	pj_joueur_precedent->pjoueur_suivant=joueur_eliminer->pjoueur_suivant;
	
	delete joueur_eliminer;
}

void traitement_perdu(SDL_Surface* surf_ecran, cases** plateau,joueur* pj_joueur)
{
	//on réactualise la case où se trouvait le joueur
	affich_case(surf_ecran,plateau[pj_joueur->int_position]);
	//on l'élimine
	traitement_elimination_joueur(pj_joueur);
}

void traitement_msg_propriete(cases* pcase, joueur* pj_joueur, int int_action, int int_type_action)
{
	
	//Selon l'action à faire
	switch(int_type_action)
	{
		//Dans le cas d'un achat
		case ACTION_ACHAT:
			//Clic sur le bouton acheter
			if(int_action==MSG_BTN_1) traitement_achat(pcase,pj_joueur);
			break;
		//Augmentation de niveau
		case ACTION_PLUS:
			//Clic sur le bouton augmenter
			if(int_action==MSG_BTN_1) traitement_augmentation_niveau(pcase,pj_joueur);
			break;
		//Diminution de niveau
		case ACTION_MOINS:
			//Clic sur le bouton diminuer
			if(int_action==MSG_BTN_1) traitement_diminution_niveau(pcase,pj_joueur);
			break;
		//Dans le cas d'une déshypothèque
		case ACTION_PLUS_MOINS:
			//Clic sur le bouton augmenter
			if(int_action==MSG_BTN_1) traitement_augmentation_niveau(pcase,pj_joueur);
			//Clic sur le bouton diminuer
			else if(int_action==MSG_BTN_2) traitement_diminution_niveau(pcase,pj_joueur);
			break;
		//Dans tout les autres cas
		default:
		//On ne fait rien
			break;
	}
	
	
}
