/*!
  \file outils.c
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief code source des outils 
  \date 09/01/2006
  \version 1.0
*/

#include "outils.h"

char* ajout_caractere(char* texte, int int_caractere)
{
	char c_caractere[2];
	char texte_temp[16];
	c_caractere[0]=(char)int_caractere;
	c_caractere[1]='\0';

	strcpy(texte_temp,texte);
	
	
	//on vérifie si la chaine est non vide
	if ((texte_temp!=NULL)) //&& (texte_temp[0]!='\0'))
	{
		//si le caractère rentré est le backspace
		if(int_caractere==8)
		{
			//la dernière case pleine de la chaine prend la valeur \0
			texte_temp[strlen(texte_temp)-1]='\0';
		}
		//s'il ne s'agit pas du backspace
		else
		{
			//la dernier case de la chaine de caractère prend pour valeur le caractère de la table ascii coorespondant
			//si la chaine n'est pas pleine et si le caractère est admissible
			if ((strlen(texte_temp)<14) 
				&& ( 
				((int_caractere>=97) && (int_caractere<=122)) //lettres minuscules
				|| ((int_caractere>=30) && (int_caractere<=39)) //chiffres
				|| (int_caractere==95) //underscore
				|| (int_caractere==45) //tiré
				|| (int_caractere==32) // espace
				|| (int_caractere==46))) //point
			{
			strcpy(texte_temp,strcat(texte_temp,c_caractere));
			}
		}
	}
	strcpy(texte,texte_temp);
	return(texte);
}

int nombre_joueur_case(joueur* pj_joueur)
{
	int int_mm_case;
	
	int_mm_case=0;
	
	joueur* pj_joueur_encours;
	
	pj_joueur_encours=pj_joueur->pjoueur_suivant;
	
	while (pj_joueur_encours != pj_joueur)
	{
		if (pj_joueur_encours->int_position==pj_joueur->int_position)
		{
			int_mm_case++;
		}
		pj_joueur_encours=pj_joueur_encours->pjoueur_suivant;
	}
	return(int_mm_case);
}

void melanger_cartes(information* cartes_a_melanger[16])
{
	for (int i=0;i<1000;i++)
	{
		swap_carte(cartes_a_melanger, rand()%16, rand()%16);
	}
}

void swap_carte(information* cartes_a_melanger[16], int position_case1, int position_case2)
{
	information* pi_tmp;
	
	pi_tmp=cartes_a_melanger[position_case1];
	cartes_a_melanger[position_case1]=cartes_a_melanger[position_case2];
	cartes_a_melanger[position_case2]=pi_tmp;
}

void joueur_possede_tout(cases** plateau, joueur* joueur_encours)
{
	int i;
	bool retour;
	
	joueur_encours->int_argent=9999999;
		
	for(i=1;i<30;i++)
	{
		//tente d'acheter toutes les cases (la fonction traitement_achat se charge de verifier si elle sont achetable ou pas)
		retour=traitement_achat(plateau[i],joueur_encours);	
	}
}

possession* insertion_bonne_place_propriete(possession* premier_maillon, cases* case_achetee)
{
	possession* nv_maillon;
	possession* maillon_encours;
	possession* maillon_precedent;
	
	nv_maillon=creation_possession(case_achetee);
	
	//si le premier maillon n'existe pas on retourne le nouveau maillon qui est alors la tete
	if (premier_maillon==NULL)
	{
		return(nv_maillon);
	}
	else
	{
		//sinon on va chercher à bien le positionner
		//si c'est une case de propriete
		if (nv_maillon->propriete->int_type==SALLE)
		{
				//le premier maillon a comparer est le premier
											
				maillon_encours=premier_maillon;

				//on avance dans la chaine jusqu'a trouver une case de la meme couleur ou à arriver au bout
				while ((maillon_encours->suivant != NULL) &&  (nv_maillon->propriete->case_salle.int_groupe != maillon_encours->propriete->case_salle.int_groupe))
				{
						maillon_precedent=maillon_encours;
						maillon_encours=maillon_encours->suivant;
				}
				//on récupère ainsi le premier maillon ayant la meme couleur que celui qu'on veut insérer
				//on insère alors le nv_maillon juste après celui ainsi trouvé
				nv_maillon->suivant=maillon_encours->suivant;
				maillon_encours->suivant=nv_maillon;
				return(premier_maillon);
		}
		else
		{
			//sinon il peut s'agir soit d'un lieu commun soit du bds/bde
			//on cherche alors de la meme manière que pour les groupe pour les cases normales les cartes de même type
			
			//si c'est le bde ou le bds
			if (nv_maillon->propriete->int_type==BDE)
			{			
					//le maillon a comparer est le premier
					maillon_encours=premier_maillon;
				
					while ((maillon_encours->suivant != NULL) &&  (maillon_encours->propriete->int_type!=BDS))
					{
							maillon_precedent=maillon_encours;
							maillon_encours=maillon_encours->suivant;
					}
					//on récupère ainsi le bds ou la fin de chaine
					//si on est en bout de chaine on l'insère au début
					if(maillon_encours->suivant==NULL)
					{
						nv_maillon->suivant=premier_maillon;
						return(nv_maillon);
					}
					//sinon on l'insere après le bds
					else
					{
					nv_maillon->suivant=maillon_encours->suivant;
					maillon_encours->suivant=nv_maillon;
					return(premier_maillon);
					}
			}
			else if (nv_maillon->propriete->int_type==BDS)
			{		
			
					//le premier maillon a comparer est le premier
					maillon_encours=premier_maillon;
				
					while ((maillon_encours->suivant != NULL) &&  (maillon_encours->propriete->int_type!=BDS))
					{
						maillon_precedent=maillon_encours;
						maillon_encours=maillon_encours->suivant;
					}
					//on récupère ainsi le bds ou la fin de chaine
					//si on est en bout de chaine on l'insère au début
					if(maillon_encours->suivant==NULL)
					{
						nv_maillon->suivant=premier_maillon;
						return(nv_maillon);
					}
					//sinon on l'insere après le bds
					else
					{
					nv_maillon->suivant=maillon_encours->suivant;
					maillon_encours->suivant=nv_maillon;
					return(premier_maillon);
					}
			}
						
			//sinon ce sont les lieux communs
			else if ((nv_maillon->propriete->int_type >= LC_WC) && (nv_maillon->propriete->int_type<=LC_PARKING))
			{				
					//le premier maillon a comparer est le second
					maillon_encours=premier_maillon;

					while ((maillon_encours->suivant != NULL) &&  ((maillon_encours->propriete->int_type < LC_WC) || (maillon_encours->propriete->int_type > LC_PARKING)))
					{
						maillon_precedent=maillon_encours;
						maillon_encours=maillon_encours->suivant;
					}
					//on récupère ainsi le premier lieu commun ou la fin de chaine
					//si on est en bout de chaine on l'insère au début
					

					if(maillon_encours->suivant==NULL)
					{
						nv_maillon->suivant=premier_maillon;
						return(nv_maillon);
					}
					//sinon on l'insere après le premier lieu commun trouvé
					else
					{
						nv_maillon->suivant=maillon_encours->suivant;
						maillon_encours->suivant=nv_maillon;
						return(premier_maillon);
					}
			}				
		}
	}
	return(false);
}

bool possession_autres_cartes(cases** plateau,joueur* pj_joueur)
{
	int i;
	int k;
	
	//on définit le groupe de la case où se trouve le joueur
	if (plateau[pj_joueur->int_position]->int_type == SALLE)
	{
		//on définit le groupe de la case où se trouve le joueur
		//pour les groupe vert ou bleu ils faut trouver une seule autre carte du groupe
		if ((plateau[pj_joueur->int_position]->case_salle.int_groupe ==VIOLET) || (plateau[pj_joueur->int_position]->case_salle.int_groupe == BLEU))
		{
			//on cherche deux cases avant et deux cases après (les cases de ces couleurs ne sont jamais éloignés de plus de deux cases)
			if (   (plateau[((pj_joueur->int_position - 2)+40)%40]->int_type == SALLE)
				&& (plateau[((pj_joueur->int_position - 2)+40)%40]->case_salle.int_groupe == plateau[pj_joueur->int_position]->case_salle.int_groupe)
				&& (plateau[((pj_joueur->int_position - 2)+40)%40]->case_salle.pjoueur_joueur == pj_joueur))
			{
				return (true);
			}
			else if (  (plateau[(pj_joueur->int_position + 2)%40]->int_type == SALLE)
					&& (plateau[(pj_joueur->int_position + 2)%40]->case_salle.int_groupe == plateau[pj_joueur->int_position]->case_salle.int_groupe)
					&& (plateau[(pj_joueur->int_position + 2)%40]->case_salle.pjoueur_joueur == pj_joueur))
			{
				return(true);
			}
		}
		//pour les autres il faut trouver forcement trouver deux autres carte du mm groupe
		else 
		{
			k=0;
			//on cherche trois cases avant et trois cases après (les cases de ces couleurs ne sont jamais éloignés de plus de trois cases)
			for (i =((pj_joueur->int_position - 3)+40)%40; i < (pj_joueur->int_position + 3)%40 ; i++)
			{
				//on ne recompte la case ou est actuellement le joueur
				if (i != pj_joueur->int_position)
				{
					if (   (plateau[i]->int_type == SALLE)
						&& (plateau[i]->case_salle.int_groupe == plateau[pj_joueur->int_position]->case_salle.int_groupe)
						&& (plateau[i]->case_salle.pjoueur_joueur == pj_joueur))
					{
						k++;
					}
					
				}
				
			}
			//on verifie si on a trouver deux cases
			if (k==2)
			{
				return(true);
			}			
		}
	}
	return(false);
}

int decoupage_string (char*** str_tab, char* str_a_diviser)
{
	int int_ligne_max;
	
	int i;
	int k; //curseur indiquant la ligne en cours de création
	int j; //curseur de déplacement dans str_a_diviser

	i=0;
	k=0;
	j=0;


	int_ligne_max=((int)(strlen(str_a_diviser)/MESSAGE_MAX_CARACTERE)+1)*2;
	
	//on alloue en mémoire un tableau de chaine de caractère de int_ligne_max lignes contenant chacune des chaine de 64 caractères
	str_tab[0]=new char*[int_ligne_max];
	
	for (i = 0 ; i < int_ligne_max ; i++)
	{
		str_tab[0][i]=new char[MESSAGE_MAX_CARACTERE];
	}
	
	//tant qu'on est pas au bout de la chaine principale
	while (strlen(str_a_diviser) >= MESSAGE_MAX_CARACTERE)
	{
		//on met le curseur à 63
		j=MESSAGE_MAX_CARACTERE - 1;
		
		//puis on cherche avant, le premier espace
		while (str_a_diviser[j] != ' ')
		{
			j--;
		}
		
		//on copie les j premiers caractères
		strncpy(str_tab[0][k],str_a_diviser,j);
		//on marque la fin de chaine
		str_tab[0][k][j]='\0';
		
		//on deplace le pointeur
		str_a_diviser=str_a_diviser+j;
		//on passe a la ligne à créer suivante
		k++;
	}
	//après il ne nous reste plus que le morceau de chaine d'une taille inférieur à MESSAGE_MAX_CARACTERE
	strcpy(str_tab[0][k],str_a_diviser);
	
	return(k+1);
}

int action_possible (cases** plateau,int int_position_cases_etudiee, joueur* pj_joueur, int int_etat, int int_nb_tire)
{
	int i;
	//on vérifie s'il s'agit l'arrivé sur une case
	if (int_etat == ARRIVE_CASE)
	{	
	//on détermine le type de la case ou il se trouve
	
		//s'il se trouve sur une salle
		if (plateau[pj_joueur->int_position]->int_type==SALLE)
		{
			//on vérifie si elle n'appartient à personne et que le joueur à l'argent et qu'elle n'est pas au premier tour
			if (!(pj_joueur->bool_debut) && (plateau[pj_joueur->int_position]->case_salle.pjoueur_joueur==NULL) && (pj_joueur->int_argent >= plateau[pj_joueur->int_position]->case_salle.int_prix))
			{
				//il peut alors l'acheter ou finir ce tour ou abandonner
				return(ACTION_ACHAT);
			}
			//sinon si elle appartient à un adversaire
			else if (plateau[pj_joueur->int_position]->case_salle.pjoueur_joueur != pj_joueur)
			{
				//si il a assez d'argent
				if (pj_joueur->int_argent >= (plateau[pj_joueur->int_position]->case_salle.int_prix/100)*plateau[pj_joueur->int_position]->case_salle.int_niveau)
				{
					//il peut alors payer
					return(ACTION_PAYER);
				}
				else
				{
					return(ACTION_PERDRE);
				}
			}
			//sinon si la case lui appartient
			else if (plateau[pj_joueur->int_position]->case_salle.pjoueur_joueur == pj_joueur)
			{
				//s'il possède toutes les autres cartes de même couleur
				if (possession_autres_cartes(plateau,pj_joueur))
				{
					//si son niveau est au maximum il ne peut que diminuer
					if (plateau[pj_joueur->int_position]->case_salle.int_niveau == 5)
					{
						return(ACTION_MOINS);
					}
					
					//si son niveau est nul il ne peut qu'augmenter s'il a de l'argent
					else if ((plateau[pj_joueur->int_position]->case_salle.int_niveau == 0) && (pj_joueur->int_argent >= plateau[pj_joueur->int_position]->case_salle.int_prix_niveau))
					{
						return(ACTION_PLUS);
					}
					
					//dans aucun des deux cas précedent s'il a assez d'argent il peut faire les deux
					else if (pj_joueur->int_argent >= plateau[pj_joueur->int_position]->case_salle.int_prix_niveau)
					{
						return(ACTION_PLUS_MOINS);
					}
					else 
					{
						return(ACTION_FINIR);
					}
					
				}
				else
				{
					//il ne peut rien faire si ce n'est finir le tour
					return(ACTION_FINIR);
				}
			}
		}
		//s'il se trouve sur une case association ou sur un lieu commun
		else if (  (plateau[pj_joueur->int_position]->int_type == LC_PARKING)
				|| (plateau[pj_joueur->int_position]->int_type == LC_RU)
				|| (plateau[pj_joueur->int_position]->int_type == LC_ASCENSEUR)
				|| (plateau[pj_joueur->int_position]->int_type == LC_WC))
		{
			//on vérifie si elle n'appartient à personne et qu'il à assez d'argent
			if (!(pj_joueur->bool_debut) && (plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur==NULL) && (pj_joueur->int_argent >= plateau[pj_joueur->int_position]->case_lieu_commun.int_prix))
			{
				//il peut alors l'acheter ou finir ce tour
				return(ACTION_ACHAT);
			}
			//sinon si elle appartient à un adversaire
			else if ((plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur != pj_joueur) && (plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur != NULL))
			{
				//si il a assez d'argent
				if (pj_joueur->int_argent >= traitement_loyer_lieu_commun(plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur))
				{
					//il peut alors payer
					return(ACTION_PAYER);
				}
				else
				{
					//sinon il perd
					return(ACTION_PERDRE);
				}
			}
			//sinon si la case lui appartient
			else if (plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur == pj_joueur)
			{
				//il le peut que finir ce tour
				return(ACTION_FINIR);
			}
		}
		else if (  (plateau[pj_joueur->int_position]->int_type == BDE)
				|| (plateau[pj_joueur->int_position]->int_type == BDS))
		{
			//on vérifie si elle n'appartient à personne et qu'il à assez d'argent
			if (!(pj_joueur->bool_debut) && (plateau[pj_joueur->int_position]->case_association.pjoueur_joueur==NULL) && (pj_joueur->int_argent >= plateau[pj_joueur->int_position]->case_association.int_prix))
			{
				//il peut alors l'acheter ou finir ce tour
				return(ACTION_ACHAT);
			}
			else if ((plateau[pj_joueur->int_position]->case_association.pjoueur_joueur != pj_joueur) && (plateau[pj_joueur->int_position]->case_association.pjoueur_joueur != NULL))
			{
				//si il a assez d'argent
				if (pj_joueur->int_argent >= traitement_loyer_association(plateau[pj_joueur->int_position]->case_lieu_commun.pjoueur_joueur, int_nb_tire))
				{
					//il peut alors payer
					return(ACTION_PAYER);
				}
				else
				{
					//sinon il perd
					return(ACTION_PERDRE);
				}
			}
			//sinon si la case lui appartient
			else if (plateau[pj_joueur->int_position]->case_association.pjoueur_joueur == pj_joueur)
			{
				//il le peut que finir ce tour
				return(ACTION_FINIR);
			}
		}
	}
	else if (int_etat == CLICK_CASE)
	{
		i=0;
		while (plateau[i]!=int_to_cases(int_position_cases_etudiee,pj_joueur)) i++;
		if (plateau[i]->int_type == SALLE)
		{
			//si le joueur est sur une case du même groupe
			if (plateau[pj_joueur->int_position]->case_salle.int_groupe == plateau[i]->case_salle.int_groupe)
			{
				//si sont niveau est nul il ne peut qu'augmenter
				if (plateau[i]->case_salle.int_niveau == 0)
				{
					return(ACTION_PLUS);
				}
				//si son niveau est au maximum il ne peut que diminuer
				else if (plateau[i]->case_salle.int_niveau == 5)
				{
					return(ACTION_MOINS);
				}
				else
				{
					return(ACTION_PLUS_MOINS);
				}
			}
		}
		else 
		{
			//il ne peut que suivre les indications spécifique à chaque case ou chaque carte
			return(ACTION_FINIR);
		}
	}
	
	return(ERREUR);
}

int nombre_propriete(joueur* pj_joueur)
{
	possession* propriete_temp;
	int i;

	i=0;
	propriete_temp=pj_joueur->propriete;
	while(propriete_temp!=NULL)
	{
		i++;
		propriete_temp=propriete_temp->suivant;
	}
	
	return(i);
	
}

cases* int_to_cases (int int_indice_case, joueur* pj_joueur)
{
	possession* propriete_en_cours;
	int i;
	
	//on assigne la propriété encours avec la première propriété du joueur pour pouvoir parcourir la chaîne
	propriete_en_cours=pj_joueur->propriete;
	
	//on se déplace dans la chaîne jusqu'à l'indice voulue
	for (i = 0; i < int_indice_case; i++)
	{
		propriete_en_cours=propriete_en_cours->suivant;
	}
	//on retourne ainsi la propriete trouvée
	return(propriete_en_cours->propriete);
}

bool verification_victoire (joueur* pj_joueur)
{
	joueur* joueur_encours;
	int i;
	
	i=0;
	
	//le joueur gagne s'il est seul
	joueur_encours=pj_joueur->pjoueur_suivant;
	
	while (joueur_encours != pj_joueur)
	{
		i++;
		joueur_encours=joueur_encours->pjoueur_suivant;
	}
	
	if (i > 0)
	{
		return(false);
	}
	else 
	{
		return(true);
	}
}

void sauvegarde(cases** plateau, joueur* pj_joueur_tete)
{
	//Joueur temporaire
	joueur* pj_joueur;
	
	//Propriété temporaire
	possession* possession_temp;
	
	//Nombre de joueur
	int int_nombre_joueur;
	int_nombre_joueur=1;
	
	//Nominateur de fin de joueur
	int int_fin;
	int_fin=-1;
	
	//Compteur de propriété
	int i;

	//On commence au premier joueur
	pj_joueur=pj_joueur_tete;
	
	//On compte le nombre de joueur
	while((pj_joueur=pj_joueur->pjoueur_suivant)!=pj_joueur_tete) int_nombre_joueur++;

	//On commence au premier joueur
	pj_joueur=pj_joueur_tete;
	
	ofstream file("sauvegarde_joueur.txt");
	
	file << int_nombre_joueur<<endl;
	
	//Tant qu'on est pas revenu au joueur de tete
	while(pj_joueur->pjoueur_suivant!=pj_joueur_tete)
	{
		file << pj_joueur->str_nom << endl;
		file << pj_joueur->int_position << endl;
		file << pj_joueur->int_argent << endl;
		file << pj_joueur->int_certificat << endl;
		file << pj_joueur->bool_debut << endl;
		file << pj_joueur->int_double_tire << endl;
		file << pj_joueur->bool_laurence << endl;
		file << pj_joueur->int_laurence << endl;
		
		possession_temp=pj_joueur->propriete;
		while(possession_temp!=NULL)
		{
			i=0;
			while (plateau[i]!=possession_temp->propriete) i++;
			file << i << endl;
			possession_temp=possession_temp->suivant;
		}
		
		file << int_fin << endl << endl;
		//On passe au joueur suivant
		pj_joueur=pj_joueur->pjoueur_suivant;
	}
	
		//Sauvegarde du dernier joueur
		file << pj_joueur->str_nom << endl;
		file << pj_joueur->int_position << endl;
		file << pj_joueur->int_argent << endl;
		file << pj_joueur->int_certificat << endl;
		file << pj_joueur->bool_debut << endl;
		file << pj_joueur->int_double_tire << endl;
		file << pj_joueur->bool_laurence << endl;
		file << pj_joueur->int_laurence << endl;
		
		possession_temp=pj_joueur->propriete;
		while(possession_temp!=NULL)
		{
			i=0;
			while (plateau[i]!=possession_temp->propriete) i++;
			file << i << endl;
			possession_temp=possession_temp->suivant;
		}
		
		file << int_fin << endl << endl;
		//On passe au joueur suivant
		pj_joueur=pj_joueur->pjoueur_suivant;
		
	//Sauvegarde du plateau
	ofstream file2("sauvegarde_plateau.txt");
	
	//On écrit le total de la cagnotte
	file2 << plateau[20]->machine_a_cafe.int_argent << endl;
	//Pour chacune des cases
	for(i=0;i<40;i++)
	{
		//S'il sagit d'une salle, on écrit son niveau
		if(plateau[i]->int_type==SALLE) file2 << plateau[i]->case_salle.int_niveau << endl;
		//Sinon on met -1
		else file2 << int_fin << endl;
	}
	
	
}

joueur* chargement(joueur* pj_joueur, cases** plateau, rvb_couleur couleurs[8], SDL_Surface* surf_ecran)
{
	
	ifstream file1("sauvegarde_joueur.txt", ios::in);
	if (!file1)
	{
		cerr << "Allocation inaboutie de sauvegarde_joueur.txt" << endl;
	}
	
	ifstream file2("sauvegarde_plateau.txt",ios::in);
	if (!file2)
	{
		cerr << "Allocation inaboutie de sauvegarde_plateau.txt" << endl;
	}
	
	int nb_joueurs;
	
	file1 >> nb_joueurs;
	
	plateau=init_plateau_chargement(&file2, plateau, couleurs,surf_ecran, pj_joueur);
	pj_joueur=init_anneau_joueur_chargement(nb_joueurs, &file1,plateau);
	
	file1.close();
	file2.close();
	
	return(pj_joueur);

}

bool is_readable( const std::string & file ) 
{ 
    std::ifstream fichier( file.c_str() ); 
    return !fichier.fail(); 
} 

int bouton_get_x(struct_bouton* btn_bouton)
{
	//On retourne l'abcisse du bouton
	return(btn_bouton->position.x);
}

int bouton_get_y(struct_bouton* btn_bouton)
{
	//On retourne l'ordonnée du bouton
	return(btn_bouton->position.y);
}

int bouton_get_w(struct_bouton* btn_bouton)
{
	//On retourne la largeur du bouton
	return(btn_bouton->surf_bouton[0]->w);
}

int bouton_get_h(struct_bouton* btn_bouton)
{
	//On retourne la hauteur du bouton
	return(btn_bouton->surf_bouton[0]->h);
}

int image_get_x(struct_image* img_image)
{
	//On retourne l'abcisse de l'image
	return(img_image->position.x);
}

int image_get_y(struct_image* img_image)
{
	//On retourne l'ordonnée de l'image
	return(img_image->position.y);
}

int image_get_w(struct_image* img_image)
{
	//On retourne la largeur de l'image
	return(img_image->surf_image->w);
}

int image_get_h(struct_image* img_image)
{
	//On retourne la hauteur de l'image
	return(img_image->surf_image->h);
}

void image_set_position(struct_image* img_image, int x, int y)
{
	//Modification de l'ordonnée
	img_image->position.y=y;
	//Modification de l'abcisse
	img_image->position.x=x;
}
