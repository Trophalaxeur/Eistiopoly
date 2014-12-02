/*!
  \file initialisation.c
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief code source des fonctions necessaires à l'initialisation du monopoly
  \date 09/01/2006
  \version 0.0.1
*/

#include "initialisation.h"

rvb_couleur init_rvb_couleur(int rouge, int vert, int bleu)
{
	rvb_couleur couleur;
	couleur.rouge=rouge;
	couleur.vert=vert;
	couleur.bleu=bleu;
	return(couleur);
}

void init_tab_rvb_couleur(rvb_couleur couleur[8])
{
	couleur[VIOLET]=init_rvb_couleur(205,14,207);
	couleur[BLEU_CIEL]=init_rvb_couleur(101,232,215);
	couleur[ROSE]=init_rvb_couleur(251,138,244);
	couleur[ORANGE]=init_rvb_couleur(255,130,8);
	couleur[ROUGE]=init_rvb_couleur(255,0,0);
	couleur[JAUNE]=init_rvb_couleur(255,255,0);
	couleur[VERT]=init_rvb_couleur(0,255,0);
	couleur[BLEU]=init_rvb_couleur(0,0,255);
}

void init_case_salle(SDL_Surface* surf_ecran, rvb_couleur couleurs[8], cases* pcase, int int_type, int int_numero, int int_prix, char* str_nom1, char* str_nom2, int int_groupe, int int_prix_niveau)
{
	int position;
	char* str_nom;
	position=int_numero/10;
	(*pcase).int_type=int_type;	
	(*pcase).surf_image=creation_case(surf_ecran, couleurs[int_groupe], str_nom1, str_nom2, int_prix, position);
	(*pcase).int_position=position;
	switch(position)
	{
		case POSITION_BAS:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			break;
		case POSITION_GAUCHE:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			break;
		case POSITION_HAUT:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU;
			break;
		case POSITION_DROITE:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			break;
		default:
			cerr << "Erreur de position pour la case numéro" << int_numero << endl;
			break;
	}
	((*pcase).case_salle).bool_hypotheque=false;
	((*pcase).case_salle).int_valeur_hypotheque=0;
	((*pcase).case_salle).int_prix=int_prix;
	((*pcase).case_salle).int_prix_niveau=int_prix_niveau;
	((*pcase).case_salle).pjoueur_joueur=NULL;
	((*pcase).case_salle).int_niveau=0;
	((*pcase).case_salle).int_groupe=int_groupe;
	 
	str_nom = new char[strlen(str_nom1)+strlen(str_nom2)+2];
	sprintf(str_nom, "%s %s",str_nom1, str_nom2);
	
	//Création de l'image
	pcase->case_salle.img_detail=new struct_image;
	//Création de l'image de la salle
	pcase->case_salle.img_detail->surf_image=creation_case_detail(surf_ecran, couleurs[int_groupe], str_nom, int_prix/10, int_prix_niveau);
	//Initialisation de la position de la salle
	image_set_position(pcase->case_salle.img_detail, DETAIL_MESSAGE_EPAISSEUR, DETAIL_MESSAGE_EPAISSEUR);
	
	pcase->case_salle.surf_propriete=creation_case_propriete(surf_ecran, couleurs[int_groupe], str_nom);
	delete[] str_nom;
	((*pcase).case_salle).bool_etat=1;
}

void init_case_association(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)
{
	rvb_couleur couleur;
	couleur.rouge=255;
	couleur.bleu=100;
	couleur.vert=255;
	int position;
	position=int_numero/10;
	(*pcase).int_type=int_type;	
	(*pcase).surf_image=creation_case_association(surf_ecran, int_type);
	(*pcase).int_position=position;
	switch(position)
	{
		case POSITION_BAS:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			break;
		case POSITION_GAUCHE:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			break;
		case POSITION_HAUT:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU;
			break;
		case POSITION_DROITE:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			break;
		default:
			cerr << "Erreur de position pour la case numéro" << int_numero << endl;
			break;
	}
	((*pcase).case_association).bool_hypotheque=false;
	((*pcase).case_association).int_valeur_hypotheque=750;
	((*pcase).case_association).int_prix=1500;
	((*pcase).case_association).pjoueur_joueur=NULL;
	((*pcase).case_association).int_autre_bureau=0;
	
	//Création de l'image
	pcase->case_association.img_detail=new struct_image;
	//Création de l'image de la salle
	pcase->case_association.img_detail->surf_image=creation_case_detail_assoc(surf_ecran, int_type);
	//Initialisation de la position de la salle
	image_set_position(pcase->case_association.img_detail, DETAIL_MESSAGE_EPAISSEUR, DETAIL_MESSAGE_EPAISSEUR);
	
	if(int_type==BDE) ((*pcase).case_association).surf_propriete=creation_case_propriete(surf_ecran, couleur, "B.D.E.");
	else ((*pcase).case_association).surf_propriete=creation_case_propriete(surf_ecran, couleur, "B.D.S.");
	 
}

void init_case_lieu_commun(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)
{
	rvb_couleur couleur;
	couleur.rouge=255;
	couleur.bleu=255;
	couleur.vert=100;
	int position;
	position=int_numero/10;
	(*pcase).int_type=int_type;	
	(*pcase).surf_image=creation_case_lieu_commun(surf_ecran, int_type);
	(*pcase).int_position=position;
	switch(int_type)
	{
		case LC_WC:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-5*CASE_LARGEUR;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			break;
		case LC_ASCENSEUR:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-5*CASE_LARGEUR;
			break;
		case LC_RU:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU+CASE_HAUTEUR+(4*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU;
			break;
		case LC_PARKING:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU+CASE_HAUTEUR+(4*CASE_LARGEUR);
			break;
		default:
			cerr << "Erreur de position pour la case numéro" << int_numero << endl;
			break;
	}
	((*pcase).case_lieu_commun).bool_hypotheque=false;
	((*pcase).case_lieu_commun).int_valeur_hypotheque=750;
	((*pcase).case_lieu_commun).int_prix=2000;
	((*pcase).case_lieu_commun).pjoueur_joueur=NULL;
	((*pcase).case_lieu_commun).int_suivant=0;
	
	//Création de l'image
	pcase->case_lieu_commun.img_detail=new struct_image;
	//Création de l'image de la salle
	pcase->case_lieu_commun.img_detail->surf_image=creation_case_detail_lc(surf_ecran, int_type);
	//Initialisation de la position de la salle
	image_set_position(pcase->case_lieu_commun.img_detail, DETAIL_MESSAGE_EPAISSEUR, DETAIL_MESSAGE_EPAISSEUR);
	
	switch(int_type)
	{
		case LC_WC:
			((*pcase).case_lieu_commun).surf_propriete=creation_case_propriete(surf_ecran, couleur, "W.C.");
			break;
		case LC_PARKING:
			((*pcase).case_lieu_commun).surf_propriete=creation_case_propriete(surf_ecran, couleur, "Parking");
			break;
		case LC_ASCENSEUR:
			((*pcase).case_lieu_commun).surf_propriete=creation_case_propriete(surf_ecran, couleur, "Ascenseur");
			break;
		case LC_RU:
			((*pcase).case_lieu_commun).surf_propriete=creation_case_propriete(surf_ecran, couleur, "R.U.");
			break;
		default:
			break;
	}
}

void init_case_administration(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)
{
	int position;
	position=int_numero/10;
	(*pcase).int_type=int_type;	
	(*pcase).surf_image=creation_case_bureau(surf_ecran, int_type, position);
	(*pcase).int_position=position;
	switch(position)
	{
		case POSITION_BAS:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			break;
		case POSITION_GAUCHE:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			break;
		case POSITION_HAUT:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU;
			break;
		case POSITION_DROITE:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			break;
		default:
			cerr << "Erreur de position pour la case numéro" << int_numero << endl;
			break;
	}
}

void init_case_soiree(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)
{
	int position;
	position=int_numero/10;
	(*pcase).int_type=int_type;	
	(*pcase).surf_image=creation_case_soiree(surf_ecran, int_type);
	(*pcase).int_position=position;
	switch(position)
	{
		case POSITION_BAS:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			break;
		case POSITION_GAUCHE:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR-(int_numero%10*CASE_LARGEUR);
			break;
		case POSITION_HAUT:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU;
			break;
		case POSITION_DROITE:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU+CASE_HAUTEUR+((int_numero%10-1)*CASE_LARGEUR);
			break;
		default:
			cerr << "Erreur de position pour la case numéro" << int_numero << endl;
			break;
	}

	((*pcase).case_soiree).int_prix=1500;
}

void init_case_special(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)
{
	int position;
	position=int_numero/10;
	(*pcase).int_type=int_type;	
	(*pcase).surf_image=creation_case_coin(surf_ecran, int_type);
	(*pcase).int_position=position;
	switch(int_type)
	{
		case SP_APPARTEMENT:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			break;
		case SP_BUREAU_LAURENCE:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU;
			(*pcase).rect_coordonnees.y=(POS_Y_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			break;
		case SP_MACHINE_CAFE:
			(*pcase).rect_coordonnees.x=POS_X_PLATEAU;
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU;
			
			//il n'y a pas d'argent dans la machine à café pour le début
			pcase->machine_a_cafe.int_argent=0;
			
			break;
		case SP_TABLEAU:
			(*pcase).rect_coordonnees.x=(POS_X_PLATEAU+TAILLE_PLATEAU)-CASE_HAUTEUR;
			(*pcase).rect_coordonnees.y=POS_Y_PLATEAU;
			break;
		default:
			cerr << "Erreur de position pour la case numéro" << int_numero << endl;
			break;
		}
	 
}

void init_plateau(SDL_Surface* surf_ecran,rvb_couleur couleurs[8], cases** plateau)
{
	init_case_special(surf_ecran, plateau[0], SP_APPARTEMENT, 0);
	init_case_salle(surf_ecran, couleurs, plateau[1], SALLE, 1, 600, "Salle", "107", VIOLET, PRIX_NIVEAU_MIN);
	init_case_administration(surf_ecran, plateau[2], BUREAU_NADEGE, 2);
	init_case_salle(surf_ecran, couleurs, plateau[3], SALLE, 3, 600, "Salle", "109", VIOLET, PRIX_NIVEAU_MIN);
	init_case_soiree(surf_ecran, plateau[4], SOIREE_AREA, 4);
	init_case_lieu_commun(surf_ecran, plateau[5], LC_WC, 5);
	init_case_salle(surf_ecran, couleurs, plateau[6], SALLE, 6, 1000, "Bureau de", "Arianne", BLEU_CIEL, PRIX_NIVEAU_MIN);
	init_case_administration(surf_ecran, plateau[7], BUREAU_KRYSTEL, 7);
	init_case_salle(surf_ecran, couleurs, plateau[8], SALLE, 8, 1000, "Bureau de", "Muriel E.", BLEU_CIEL, PRIX_NIVEAU_MIN);
	init_case_salle(surf_ecran, couleurs, plateau[9], SALLE, 9, 1200, "Bureau de", "Anne-Marie", BLEU_CIEL, PRIX_NIVEAU_MIN);
	init_case_special(surf_ecran, plateau[10], SP_BUREAU_LAURENCE, 10);
	init_case_salle(surf_ecran, couleurs, plateau[11], SALLE, 11, 1400, "Bureau de", "Mathias", ROSE, PRIX_NIVEAU_MIN*2);
	init_case_association(surf_ecran, plateau[12], BDS, 12);
	init_case_salle(surf_ecran, couleurs, plateau[13], SALLE, 13, 1400, "Bureau de", "Muriel D.", ROSE, PRIX_NIVEAU_MIN*2);
	init_case_salle(surf_ecran, couleurs, plateau[14], SALLE, 14, 1600, "Bureau de", "Alex", ROSE, PRIX_NIVEAU_MIN*2);
	init_case_lieu_commun(surf_ecran, plateau[15], LC_ASCENSEUR, 15);
	init_case_salle(surf_ecran, couleurs, plateau[16], SALLE, 16, 1800, "Salle", "304", ORANGE, PRIX_NIVEAU_MIN*2);
	init_case_administration(surf_ecran, plateau[17], BUREAU_NADEGE, 17);
	init_case_salle(surf_ecran, couleurs, plateau[18], SALLE, 18, 1800, "Salle", "305", ORANGE, PRIX_NIVEAU_MIN*2);
	init_case_salle(surf_ecran, couleurs, plateau[19], SALLE, 19, 2000, "Salle", "308", ORANGE, PRIX_NIVEAU_MIN*2);
	init_case_special(surf_ecran, plateau[20], SP_MACHINE_CAFE, 20);
	init_case_salle(surf_ecran, couleurs, plateau[21], SALLE, 21, 2200, "Salle", "306", ROUGE, PRIX_NIVEAU_MIN*3);
	init_case_administration(surf_ecran, plateau[22], BUREAU_KRYSTEL, 22);
	init_case_salle(surf_ecran, couleurs, plateau[23], SALLE, 23, 2200, "Salle", "307", ROUGE, PRIX_NIVEAU_MIN*3);
	init_case_salle(surf_ecran, couleurs, plateau[24], SALLE, 24, 2400, "Salle", "309", ROUGE, PRIX_NIVEAU_MIN*3);
	init_case_lieu_commun(surf_ecran, plateau[25], LC_RU, 25);
	init_case_salle(surf_ecran, couleurs, plateau[26], SALLE, 26, 2600, "Bureau de", "Yannick", JAUNE, PRIX_NIVEAU_MIN*3);
	init_case_salle(surf_ecran, couleurs, plateau[27], SALLE, 27, 2600, "Bureau de", "Nisrine", JAUNE, PRIX_NIVEAU_MIN*3);
	init_case_association(surf_ecran, plateau[28], BDE, 28);
	init_case_salle(surf_ecran, couleurs, plateau[29], SALLE, 29, 2800, "Bureau de", "Astrid", JAUNE, PRIX_NIVEAU_MIN*3);
	init_case_special(surf_ecran, plateau[30], SP_TABLEAU, 30);
	init_case_salle(surf_ecran, couleurs, plateau[31], SALLE, 31, 3000, "Cafeteria", " ", VERT, PRIX_NIVEAU_MIN*4);
	init_case_salle(surf_ecran, couleurs, plateau[32], SALLE, 32, 3000, "Amphi", " ", VERT, PRIX_NIVEAU_MIN*4);
	init_case_administration(surf_ecran, plateau[33], BUREAU_NADEGE, 33);
	init_case_salle(surf_ecran, couleurs, plateau[34], SALLE, 34, 3200, "Bureau de", "Florent", VERT, PRIX_NIVEAU_MIN*4);
	init_case_lieu_commun(surf_ecran, plateau[35], LC_PARKING, 35);
	init_case_administration(surf_ecran, plateau[36], BUREAU_KRYSTEL, 36);
	init_case_salle(surf_ecran, couleurs, plateau[37], SALLE, 37, 3500, "Bureau de", "Pierre", BLEU, PRIX_NIVEAU_MIN*4);
	init_case_soiree(surf_ecran, plateau[38], SOIREE_GALA, 38);
	init_case_salle(surf_ecran, couleurs, plateau[39], SALLE, 39, 4000, "Bureau de", "Nesim", BLEU, PRIX_NIVEAU_MIN*4);

}

joueur* init_joueur(char* nom,int numero_joueur)
{
	joueur* pjoueur;
	
	pjoueur=new joueur;
	
	strcpy(pjoueur->str_nom, nom);
	pjoueur->int_laurence=0;
	pjoueur->bool_laurence=false;
	pjoueur->int_position=0;
	pjoueur->int_argent=15000;
	pjoueur->int_certificat=0;
	pjoueur->int_double_tire=0;
	//true, le joueur est à son premier tour
	pjoueur->bool_debut=true;
	pjoueur->pjoueur_suivant=NULL;
	pjoueur->surf_image=creation_joueur(numero_joueur+1);
	pjoueur->propriete=init_anneau_possesions();
	
	return(pjoueur);
}

void init_bureau_krystel(information* bureau_de_krystel[16])
{
	//pour chaque case du tableau
	for(int i=0;i<16;i++)
	{
		//on allou en mémoire un espace pour une information
		bureau_de_krystel[i]=new information;
		//on test si l'allocation c'est bien déroulée
		if (bureau_de_krystel[i]==NULL)
		{
			//cerr << "Erreur d'allocation" << endl;
			exit(-1);
		}
	}
	//on initialise le tableau d'information
	strcpy(bureau_de_krystel[0]->texte,"Vous êtes convoqué au bureau de Nesim. Allez-y sans plus tarder. Si vous devez passer par chez vous, touchez votre argent de poche.");
	bureau_de_krystel[0]->type=POSITION;
	bureau_de_krystel[0]->valeur=39;
	
	strcpy(bureau_de_krystel[1]->texte,"Vous avez été convoqué au bureau de Laurence. Ne passez pas par chez vous, ne touchez pas votre argent de poche!");
	bureau_de_krystel[1]->type=CARTE_LAURENCE;
	bureau_de_krystel[1]->valeur=10;
	
	strcpy(bureau_de_krystel[2]->texte,"Vous avez raté votre DS d'info. Allez voir Florent! Si vous devez passer par chez vous, touchez votre argent de poche.");
	bureau_de_krystel[2]->type=POSITION;
	bureau_de_krystel[2]->valeur=34;
	
	strcpy(bureau_de_krystel[3]->texte,"3 en colle de physique! Allez voir Pierre dans son bureau! Si vous devez passer par chez vous, touchez votre argent de poche.");
	bureau_de_krystel[3]->type=POSITION;
	bureau_de_krystel[3]->valeur=37;
	
	strcpy(bureau_de_krystel[4]->texte,"Vous devez payer vos frais de scolarité : 1500 Fintz.");
	bureau_de_krystel[4]->type=ARGENT;
	bureau_de_krystel[4]->valeur=-1500;
	
	strcpy(bureau_de_krystel[5]->texte,"Vous avez laissé votre session ouverte : reculez de 3 cases.");
	bureau_de_krystel[5]->type=POSITION;
	bureau_de_krystel[5]->valeur=-3;
	
	strcpy(bureau_de_krystel[6]->texte,"Il est 12 heures 14 minutes et 45 secondes, il vous reste 15 secondes pour plier vos affaires et allez manger au R.U.. Si vous devez passer par chez vous, touchez votre argent de poche.");
	bureau_de_krystel[6]->type=POSITION;
	bureau_de_krystel[6]->valeur=25;
	
	strcpy(bureau_de_krystel[7]->texte,"Krystel a fait une erreur dans ses comptes : elle vous reverse 50 Fintz.");
	bureau_de_krystel[7]->type=ARGENT;
	bureau_de_krystel[7]->valeur=50;
	
	strcpy(bureau_de_krystel[8]->texte,"Inspection de la CTI : versez 400 Fintz par niveau pour chacune de vos salles.");
	bureau_de_krystel[8]->type=ARGENT;
	bureau_de_krystel[8]->valeur=-400;
	
	strcpy(bureau_de_krystel[9]->texte,"Allez en salle 309. DS d'analyse ! Si vous devez passer par chez vous, touchez votre argent de poche.");
	bureau_de_krystel[9]->type=POSITION;
	bureau_de_krystel[9]->valeur=24;

	strcpy(bureau_de_krystel[10]->texte,"Dure journée de cours. Rentrez chez vous geeker un petit peu. N'oubliez pas votre argent de poche.");
	bureau_de_krystel[10]->type=POSITION;
	bureau_de_krystel[10]->valeur=0;
	
	strcpy(bureau_de_krystel[11]->texte,"Certificat médical : ce certificat vous permet de sortir du bureau de Laurence.");
	bureau_de_krystel[11]->type=CERTIFICAT;
	bureau_de_krystel[11]->valeur=1;
	
	strcpy(bureau_de_krystel[12]->texte,"Vous avez réussi votre DS de Math! Vos parents vous donnent une petite récompense : vous touchez 200 Fintz.");
	bureau_de_krystel[12]->type=ARGENT;
	bureau_de_krystel[12]->valeur=200;
	
	strcpy(bureau_de_krystel[13]->texte,"Vous avez loupé 2H de math! Saleté de réveil ! Vous versez 100 Fintz");
	bureau_de_krystel[13]->type=ARGENT;
	bureau_de_krystel[13]->valeur=-100;
	
	strcpy(bureau_de_krystel[14]->texte,"Félicitation! Votre prospection à Totoville vous rapporte 50 Fintz");
	bureau_de_krystel[14]->type=ARGENT;
	bureau_de_krystel[14]->valeur=50;
	
	strcpy(bureau_de_krystel[15]->texte,"Après avoir pris une déroutée monumentale au ping-pong vous avez brisé la raquette en deux. Versez 50 Fintz de cotisation");
	bureau_de_krystel[15]->type=ARGENT;
	bureau_de_krystel[15]->valeur=-50;
	
	melanger_cartes(bureau_de_krystel);
}				 

void init_bureau_nadege(information* bureau_de_nadege[16])
{
	//pour chaque case du tableau
	for(int i=0;i<16;i++)
	{
		//on allou en mémoire un espace pour une information
		bureau_de_nadege[i]=new information;
		//on test si l'allocation c'est bien déroulée
		if (bureau_de_nadege[i]==NULL)
		{
			//cerr << "Erreur d'allocation" << endl;
			exit(-1);
		}
	}
	//on initialise le tableau d'information
	strcpy(bureau_de_nadege[0]->texte,"Vous venez de planter le serveur de l'école. Allez voir Alex! Si vous devez passer par chez vous, touchez votre argent de poche.");
	bureau_de_nadege[0]->type=POSITION;
	bureau_de_nadege[0]->valeur=14;
	
	strcpy(bureau_de_nadege[1]->texte,"Vous avez fait sauter les plombs de l'école. Payez le montant des réparations : 100 Fintz.");
	bureau_de_nadege[1]->type=ARGENT;
	bureau_de_nadege[1]->valeur=-100;
	
	strcpy(bureau_de_nadege[2]->texte,"Votre assiduité en cours vous oblige à racheter des cahiers pour prendre en note. La facture s'élève à 50 Fintz.");
	bureau_de_nadege[2]->type=ARGENT;
	bureau_de_nadege[2]->valeur=-50;
	
	strcpy(bureau_de_nadege[3]->texte,"Vous venez de prendre -0.5 au dernier DS d'analyse. Allez illico presto voir Krystel.");
	bureau_de_nadege[3]->type=ASTRID;
	bureau_de_nadege[3]->valeur=-50;
	
	strcpy(bureau_de_nadege[4]->texte,"Votre taux d'absentéisme est inconcevable. Vous êtes convoqué dans le bureau de Laurence immédiatement. Ne passez pas par chez vous, ne touchez pas votre argent de poche.");
	bureau_de_nadege[4]->type=CARTE_LAURENCE;
	bureau_de_nadege[4]->valeur=10;
	
	strcpy(bureau_de_nadege[5]->texte,"Certificat médical : ce certificat vous permet de sortir du bureau de Laurence.");
	bureau_de_nadege[5]->type=CERTIFICAT;
	bureau_de_nadege[5]->valeur=3;
	
	strcpy(bureau_de_nadege[6]->texte,"Le dernier cours de la journée est annulé. Vous rentrez tranquillement chez vous.");
	bureau_de_nadege[6]->type=POSITION;
	bureau_de_nadege[6]->valeur=0;
	
	strcpy(bureau_de_nadege[7]->texte,"Inspection du comité des grandes écoles. Payez 500 Fintz par niveau pour nettoyer vos salles.");
	bureau_de_nadege[7]->type=CTI;
	bureau_de_nadege[7]->valeur=-500;
	
	strcpy(bureau_de_nadege[8]->texte,"Inspection de la CTI : versez 400 Fintz par niveau pour chacune de vos salles.");
	bureau_de_nadege[8]->type=CTI;
	bureau_de_nadege[8]->valeur=-400;
	
	strcpy(bureau_de_nadege[9]->texte,"La machine à café a encore eu des ratées. Vous gagnez 50 Fintz.");
	bureau_de_nadege[9]->type=ARGENT;
	bureau_de_nadege[9]->valeur=50;
	
	strcpy(bureau_de_nadege[10]->texte,"Un p*t*in de poteau de m*** a encore traversé la route en dehors des clous. Payez 300 Fintz de réparation.");
	bureau_de_nadege[10]->type=ARGENT;
	bureau_de_nadege[10]->valeur=-300;
	
	strcpy(bureau_de_nadege[11]->texte,"C'est votre anniversaire! Chacun de vos adversaires vous donne 100 Fintz.");
	bureau_de_nadege[11]->type=ANNIVERSAIRE;
	bureau_de_nadege[11]->valeur=100;
	
	strcpy(bureau_de_nadege[12]->texte,"Contrôle d'alcoolémie! Vous avez été contrôlé positif avec 3.5 g/L après avoir pris un rond-point à 80 km/h en contre-sens tous phares éteints en plein milieu de la nuit. Félicitations de la police, vous gagnez 1000 Fintz.");
	bureau_de_nadege[12]->type=ARGENT;
	bureau_de_nadege[12]->valeur=1000;
	
	strcpy(bureau_de_nadege[13]->texte,"Vous organisez une visite guidée de la maison de Forky. Chacun des élèves doit payer 150 Fintz pour se poiler.");
	bureau_de_nadege[13]->type=ANNIVERSAIRE;
	bureau_de_nadege[13]->valeur=150;
	
	strcpy(bureau_de_nadege[14]->texte,"Félicitations ! Votre prospection à Totoland vous rapporte 150 Fintz.");
	bureau_de_nadege[14]->type=ARGENT;
	bureau_de_nadege[14]->valeur=150;
	
	strcpy(bureau_de_nadege[15]->texte,"Vous participez à une LAN et après 20h de jeu consécutives, dans un élan de courage vous vous levez entrainant avec vous votre casque qui fait tomber votre ordinateur. Le montant des réparations s'élève à 200 Fintz.");
	bureau_de_nadege[15]->type=ARGENT;
	bureau_de_nadege[15]->valeur=-200;
	
	melanger_cartes(bureau_de_nadege);
}

possession* init_anneau_possesions()
{
		return(NULL);
}

possession* creation_possession(cases* propriete)
{
	possession* nv_possession;
	
	nv_possession=new possession;
	
	if (nv_possession==NULL)
	{
		cerr << "Erreur d'allocation mémoire" << endl;
		exit(-1);
	}
	else
	{
		nv_possession->propriete=propriete;
		nv_possession->suivant=NULL;
	}
	return(nv_possession);
	
}

joueur* init_anneau_joueur(int nombre_joueur,char** str_nom_joueur)
{
	joueur* p_joueur_premier;
	
	joueur* p_joueur_precedent;
	joueur* p_joueur_encours;
	
	//on crée le premier joueur
	p_joueur_premier=init_joueur(str_nom_joueur[0],0);
	p_joueur_precedent=p_joueur_premier;
	
	for(int i=1;i<nombre_joueur;i++)
	{
		p_joueur_encours=init_joueur(str_nom_joueur[i], i);
		p_joueur_precedent->pjoueur_suivant=p_joueur_encours;
		p_joueur_precedent=p_joueur_encours;
	}
	p_joueur_precedent->pjoueur_suivant=p_joueur_premier;
	return(p_joueur_premier);
}

joueur* init_anneau_joueur_chargement(int nombre_joueur, ifstream* file, cases** plateau)
{
	joueur* p_joueur_premier;
	
	joueur* p_joueur_precedent;
	joueur* p_joueur_encours;
	
	//on crée le premier joueur
	p_joueur_premier=init_joueur_chargement(0, file,plateau);
	p_joueur_precedent=p_joueur_premier;
	
	for(int i=1;i<nombre_joueur;i++)
	{
		p_joueur_encours=init_joueur_chargement(i,file,plateau);
		p_joueur_precedent->pjoueur_suivant=p_joueur_encours;
		p_joueur_precedent=p_joueur_encours;
	}
	p_joueur_precedent->pjoueur_suivant=p_joueur_premier;
	
	return(p_joueur_premier);
}

joueur* init_joueur_chargement(int numero_joueur, ifstream* file, cases** plateau)
{
	joueur* pjoueur;
	int int_propriete_tmp;
	
	int temp;
	
	pjoueur=new joueur;
	
	*file >> pjoueur->str_nom; 
	*file >> pjoueur->int_position;
	*file >> pjoueur->int_argent;
	*file >> pjoueur->int_certificat;
	*file >> pjoueur->bool_debut;
	*file >> pjoueur->int_double_tire;
	*file >> pjoueur->bool_laurence;
	*file >> pjoueur->int_laurence;
	
	pjoueur->pjoueur_suivant=NULL;
	pjoueur->surf_image=creation_joueur(numero_joueur+1);
	pjoueur->propriete=init_anneau_possesions();

	*file >> int_propriete_tmp;
	
	while (int_propriete_tmp != -1)
	{
		pjoueur->propriete=insertion_bonne_place_propriete(pjoueur->propriete,plateau[int_propriete_tmp]);
		if(plateau[int_propriete_tmp]->int_type==SALLE) plateau[int_propriete_tmp]->case_salle.pjoueur_joueur=pjoueur;
		else if(plateau[int_propriete_tmp]->int_type==BDE || plateau[int_propriete_tmp]->int_type==BDS) plateau[int_propriete_tmp]->case_association.pjoueur_joueur=pjoueur;
		else plateau[int_propriete_tmp]->case_lieu_commun.pjoueur_joueur=pjoueur;
		*file >> int_propriete_tmp;
	}
	return(pjoueur);
}

cases** init_plateau_chargement(ifstream* file, cases** plateau, rvb_couleur couleurs[8], SDL_Surface* surf_ecran, joueur* pj_joueur)
{
	int tmp;
	int i;
	
	i=0;
	
	//on allou d'abord le prix du parc gratuit
	*file >> plateau[20]->machine_a_cafe.int_argent;
	
	init_plateau(surf_ecran, couleurs, plateau);
	for (i = 0; i < 40; i++)
	{
		*file >> tmp;
		if (tmp!=-1)
		{
			plateau[i]->case_salle.int_niveau=tmp;
			//plateau[i]->case_salle.pjoueur_joueur=pj_joueur;
		}
	}
	
	return(plateau);
	
}

struct_image* creation_image(char* nom, int pos_x, int pos_y)
{
	//Chemin d'acces temporaire
	char temp_path[64];
	//Structure de l'image
	struct_image* img_image;
	//Création de l'image
	img_image=new struct_image;
	
	//Création du chemin d'acces total
	snprintf(temp_path, sizeof(char)*(strlen("sdl/images/")+strlen(nom)+1),"sdl/images/%s",nom);
	
	//Chargement de l'image
	img_image->surf_image=IMG_Load(temp_path);
	
	//Chargement des coordonnées
	img_image->position.x=pos_x;
	img_image->position.y=pos_y;
	
	//On retourne la structure image
	return(img_image);
}

struct_image* creation_surface(SDL_Surface* surf_ecran, int pos_x, int pos_y, int largeur, int hauteur, rvb_couleur couleur)
{
	//Structure de l'image
	struct_image* img_image;
	//Création de l'image
	img_image=new struct_image;
	
	//Création de la surface
	img_image->surf_image=SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
	//Remplissage avec la couleur
	SDL_FillRect(img_image->surf_image, NULL, SDL_MapRGB(surf_ecran->format, couleur.rouge, couleur.vert, couleur.bleu));
	
	//Chargement des coordonnées
	img_image->position.x=pos_x;
	img_image->position.y=pos_y;
	
	//On retourne la structure image
	return(img_image);
}

struct_image* creation_texte(char* texte, rvb_couleur couleur, int int_size, int pos_x, int pos_y, int int_police)
{
	//Structure de l'image
	struct_image* img_image;
	
	//Couleur du texte
	SDL_Color couleur_texte = {couleur.rouge, couleur.vert, couleur.bleu};
	
	//Police d'écriture
	TTF_Font* police;
	police=NULL;
	
	//Création de l'image
	img_image=new struct_image;
	//Ouverture de la police d'ecriture
	if(int_police==POLICE_2) police = TTF_OpenFont("sdl/police/police2-bold.ttf", int_size);
	else police = TTF_OpenFont("sdl/police/police.ttf", int_size);
	
	//Ecriture du texte sur la surface de texte
	img_image->surf_image = TTF_RenderText_Blended(police, texte, couleur_texte);
	
	//Fermeture de la police d'ecriture
	TTF_CloseFont(police);
	
	//Chargement des coordonnées
	if(pos_x==TEXTE_CENTERED) img_image->position.x=(ECRAN_LARGEUR-(img_image->surf_image->w))/2;
	else if(pos_x==MESSAGE_CENTERED) img_image->position.x=(MESSAGE_LARGEUR-(img_image->surf_image->w))/2;
	else img_image->position.x=pos_x;
	img_image->position.y=pos_y;
	
	return(img_image);
}

void destruction_image(struct_image* img_image)
{
	//Libération de l'image de la surface
	SDL_FreeSurface(img_image->surf_image);
	//Suppression de l'image
	delete img_image;
}

struct_bouton* creation_bouton(char* nom1, char* nom2, int pos_x, int pos_y)
{
	//Chemin d'acces temporaire
	char temp_path[64];
	//Structure du bouton
	struct_bouton* btn_bouton;
	
	//Création du bouton
	btn_bouton=new struct_bouton;
	
	//Création du chemin d'acces de l'image normale
	snprintf(temp_path, sizeof(char)*(strlen("sdl/images/")+strlen(nom1)+1),"sdl/images/%s",nom1);
	//Chargement de l'image normale du bouton
	btn_bouton->surf_bouton[0]=IMG_Load(temp_path);
	//Création du chemin d'acces de l'image du bouton en surbrillance
	snprintf(temp_path, sizeof(char)*(strlen("sdl/images/")+strlen(nom2)+1),"sdl/images/%s",nom2);
	//Chargement de l'image du bouton en surbrillance
	btn_bouton->surf_bouton[1]=IMG_Load(temp_path);
	
	//Chargement des coordonnées du bouton
	if(pos_x==TEXTE_CENTERED) btn_bouton->position.x=(ECRAN_LARGEUR-(btn_bouton->surf_bouton[0]->w))/2;
	else btn_bouton->position.x=pos_x;
	btn_bouton->position.y=pos_y;
	
	return(btn_bouton);
}

void destruction_bouton(struct_bouton* btn_bouton)
{
	//Libération des images du bouton
	SDL_FreeSurface(btn_bouton->surf_bouton[0]);
	SDL_FreeSurface(btn_bouton->surf_bouton[1]);
	//Suppression du bouton
	delete btn_bouton;
}

struct_nbre_joueur* init_struct_nbre_joueur(SDL_Surface* surf_ecran)
{
	//Chaine contenant les caractères représentant le chiffre à afficher
	char chiffre[8];
	//Variable de boucle
	int i;
	//Structure de la page du nombre de joueur
	struct_nbre_joueur* nbre_joueur;
	//Création de la page du nombre de joueur
	nbre_joueur= new struct_nbre_joueur;
	
	//Aucun bouton survolé
	nbre_joueur->int_select=0;
	//Création du titre de la page
	nbre_joueur->img_titre=creation_texte("Nombre de joueurs", init_rvb_couleur(255,200,0), 60, TEXTE_CENTERED, ACCUEIL_TITRE_POS_Y, POLICE_1);
	//Initialisation de l'image de la fleche droite
	nbre_joueur->btn_fleche_droite=creation_bouton("fleche_droite.png","fleche_droite2.png",POS_X_FLECHES+200, POS_Y_FLECHES);
	//Initialisation de l'image de la fleche gauche
	nbre_joueur->btn_fleche_gauche=creation_bouton("fleche_gauche.png","fleche_gauche2.png",POS_X_FLECHES, POS_Y_FLECHES);
	//Initialisation du bouton valider
	nbre_joueur->btn_valider=creation_bouton("suivant.gif", "suivant2.gif",(ECRAN_LARGEUR-BTN_ACCUEIL_LARGEUR)/2, BTN_ACCUEIL_POS_Y);
	//Initialisation du bouton retour
	nbre_joueur->btn_retour=creation_bouton("retour.gif", "retour2.gif",(ECRAN_LARGEUR-BTN_ACCUEIL_LARGEUR)/2, BTN_ACCUEIL_POS_Y+1.5*BTN_ACCUEIL_HAUTEUR);
	
	//Pour chacun des chiffres
	for(i=0;i<6;i++)
	{
		//Initialisation de la chaine temporaire contenant le chiffre
		sprintf(chiffre,"%d", i+2);
		//Création de l'image du chiffre
		nbre_joueur->img_nombres[i]=creation_texte(chiffre, init_rvb_couleur(255,50,0), 100, TEXTE_CENTERED, TEXTE_POS_Y, POLICE_1);
	}
	
	//Initialisation du cache des nombres
	nbre_joueur->img_nbre_cache=creation_surface(surf_ecran, nbre_joueur->img_nombres[5]->position.x-20, nbre_joueur->img_nombres[5]->position.y+75, 80, 150, init_rvb_couleur(0, 0, 0));
	
	//On retourne la structure nombre joueur
	return(nbre_joueur);
}

void destruction_nbre_joueur(struct_nbre_joueur* nbre_joueur)
{
	//Variable de boucle
	int i;
	//Destruction de l'image du titre
	destruction_image(nbre_joueur->img_titre);
	//Destruction du bouton retour
	destruction_bouton(nbre_joueur->btn_retour);
	//Destruction du bouton valider
	destruction_bouton(nbre_joueur->btn_valider);
	//Destruction de la fleche droite
	destruction_bouton(nbre_joueur->btn_fleche_droite);
	//Destruction de la fleche gauche
	destruction_bouton(nbre_joueur->btn_fleche_gauche);
	//Destruction du cache des nombres
	destruction_image(nbre_joueur->img_nbre_cache);
	//Destruction de chacune des images des chiffres
	for(i=0;i<6;i++) destruction_image(nbre_joueur->img_nombres[i]);
	
	//Destruction de la page du nombre de joueur
	delete nbre_joueur;
}

struct_menu* init_struct_menu(SDL_Surface* surf_ecran)
{
	//Structure de la page du nombre de joueur
	struct_menu* menu;
	//Création de la page du nombre de joueur
	menu= new struct_menu;
	
	//Le premier item est toujours selectionné
	menu->int_select=0;
	//Création du titre de la page
	menu->img_titre=creation_texte("Menu Principal", init_rvb_couleur(255,200,0), 60, TEXTE_CENTERED, ACCUEIL_TITRE_POS_Y, POLICE_1);
	
	menu->btn_items[0]=creation_bouton("mnu_newgame.png", "mnu_newgame2.png", TEXTE_CENTERED, ECRAN_HAUTEUR-6*90);
	menu->btn_items[1]=creation_bouton("mnu_loadgame.png", "mnu_loadgame2.png", TEXTE_CENTERED, ECRAN_HAUTEUR-5*90);
	menu->btn_items[2]=creation_bouton("mnu_multi.png", "mnu_multi2.png", TEXTE_CENTERED, ECRAN_HAUTEUR-4*90);
	menu->btn_items[3]=creation_bouton("mnu_apropos.png", "mnu_apropos2.png", TEXTE_CENTERED, ECRAN_HAUTEUR-3*90);
	menu->btn_items[4]=creation_bouton("mnu_quit.png", "mnu_quit2.png", TEXTE_CENTERED, ECRAN_HAUTEUR-2*90);
	
	//On retourne la structure nombre joueur
	return(menu);
}

void destruction_menu(struct_menu* menu)
{
	//Variable de boucle
	int i;
	//Destruction de l'image du titre
	destruction_image(menu->img_titre);

	//Destruction de chacun des boutons des items
	for(i=0;i<5;i++) destruction_bouton(menu->btn_items[i]);
	
	//Destruction de la page du nombre de joueur
	delete menu;
}

struct_nom_joueur* init_struct_nom_joueur(SDL_Surface* surf_ecran, int int_nbre_joueur)
{
	//Variable de boucle
	int i;
	//Structure de la page du nombre de joueur
	struct_nom_joueur* nom_joueur;
	//Création de la page du nombre de joueur
	nom_joueur= new struct_nom_joueur;
	//Chaine temporaire qui contient le titre des champs
	char str_temp[32];
	
	//Le premier champ est celui par défault
	nom_joueur->int_select=0;
	//Stockage du nbre de joueur
	nom_joueur->int_nbre_joueur=int_nbre_joueur;
	//Création du titre de la page
	nom_joueur->img_titre=creation_texte("Noms des joueurs", init_rvb_couleur(255,200,0), 60, TEXTE_CENTERED, ACCUEIL_TITRE_POS_Y, POLICE_1);
	//Initialisation du bouton valider
	nom_joueur->btn_jouer=creation_bouton("jouer.gif", "jouer2.gif",(ECRAN_LARGEUR-BTN_ACCUEIL_LARGEUR)/2, BTN_ACCUEIL_POS_Y);
	//Initialisation du bouton retour
	nom_joueur->btn_retour=creation_bouton("retour.gif", "retour2.gif",(ECRAN_LARGEUR-BTN_ACCUEIL_LARGEUR)/2, BTN_ACCUEIL_POS_Y+1.5*BTN_ACCUEIL_HAUTEUR);
	//Initialisation du pion du curseur
	nom_joueur->img_curseur=creation_image("pion.png", CHAMP_POS_X-30, CHAMP_POS_Y+5);
	//Initialisation du cache du pion du curseur
	nom_joueur->img_curseur_cache=creation_surface(surf_ecran, CHAMP_POS_X-30, CHAMP_POS_Y+5, 20, 20, init_rvb_couleur(0, 0, 0));
	
	//Allocation des titres des champs en fonction du nombre de joueur
	nom_joueur->img_texte_noms= new struct_image*[int_nbre_joueur];
	
	//Allocation du tableau des noms des joueurs
	nom_joueur->str_noms=new char*[int_nbre_joueur];
	
	//Pour chacun des joueurs
	for(i=0;i<int_nbre_joueur;i++)
	{
		//Enregistrement du numéro
		sprintf(str_temp,"Joueur %d :",i+1);
		//Création de l'image du texte associé
		nom_joueur->img_texte_noms[i]=creation_texte(str_temp, init_rvb_couleur(255, 0, 0), 30, NOM_CHAMP_POS_X, NOM_CHAMP_POS_Y+i*2*CHAMP_HAUTEUR, POLICE_1);
		//Allocation des noms des joueurs
		nom_joueur->str_noms[i]=new char[16];
		//Remplissage de la ligne avec des fins de ligne
		memset(nom_joueur->str_noms[i],(int)'\0',1);
		
	}
	//Initialisation des champs
	nom_joueur->img_champ=creation_surface(surf_ecran, CHAMP_POS_X, CHAMP_POS_Y, CHAMP_LARGEUR, CHAMP_HAUTEUR, init_rvb_couleur(204, 204, 204));
	//On retourne la structure nombre joueur
	return(nom_joueur);
}

void destruction_nom_joueur(struct_nom_joueur* nom_joueur)
{
	//Variable de boucle
	int i;
	//Destruction de l'image du titre
	destruction_image(nom_joueur->img_titre);
	//Destruction du bouton retour
	destruction_bouton(nom_joueur->btn_retour);
	//Destruction du bouton valider
	destruction_bouton(nom_joueur->btn_jouer);
	//Destruction de l'image du curseur
	destruction_image(nom_joueur->img_curseur);
	//Destruction du cache du curseur
	destruction_image(nom_joueur->img_curseur_cache);
	//Pour chacun des joueurs
	for(i=0;i<nom_joueur->int_nbre_joueur;i++)
	{
		//Destruction de l'image du titre du champ
		destruction_image(nom_joueur->img_texte_noms[i]);
		//Libération des chaines de caractères des noms des joueurs
		delete nom_joueur->str_noms[i];
	}
	//Destruction de l'image du champ
	destruction_image(nom_joueur->img_champ);
	//Destruction de la liste des titres de champ
	delete nom_joueur->img_texte_noms;
	//Libération du tableau des noms des joueurs
	delete nom_joueur->str_noms;
	//Destruction de la page du nombre de joueur
	delete nom_joueur;
}

struct_apropos* initialisation_apropos(SDL_Surface* surf_ecran)
{
	//Variable de boucle
	int i;
	//Structure du menu apropos
	struct_apropos* apropos;
	//Création du menu apropos
	apropos= new struct_apropos;
	
	//Image du cadre
	struct_image* img_cadre;
	//Image du texte
	struct_image* img_texte;
	
	//Création du titre de la page
	apropos->img_titre=creation_texte("A propos de", init_rvb_couleur(255,200,0), 60, TEXTE_CENTERED, ACCUEIL_TITRE_POS_Y, POLICE_1);
	//Création de l'image du menu apropos
	apropos->img_apropos=creation_surface(surf_ecran,(ECRAN_LARGEUR-APROPOS_LARGEUR)/2, ACCUEIL_TITRE_POS_Y+125, APROPOS_LARGEUR, APROPOS_HAUTEUR, init_rvb_couleur(50, 125, 15));
	//Création du cadre
	img_cadre=creation_surface(surf_ecran, 10, 10, APROPOS_LARGEUR-20, APROPOS_HAUTEUR-20, init_rvb_couleur(225, 100, 15));
	//Affichage du cadre
	affich_image(apropos->img_apropos->surf_image, img_cadre);
	//Création et affichage des images des lignes du texte du menu apropos
	img_texte=creation_texte("Nom du jeu : EISTIOPOLY", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("Version : 1.0b", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*1, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("Développeurs : Franck Trey & Florian Lefevre", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*2, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("Ecole : EISTI", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*3, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("Année : CPI2", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*4, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("EISTIOPOLY est un jeu monopoly version EISTI", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*6, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("développé dans le cadre d'un projet informatique.", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*7, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("Béta-Testeurs : Jérémy Bertrand, Matthieu Bonneli", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*9, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	img_texte=creation_texte("Testeur Béta : Alix Mayoux", init_rvb_couleur(0, 75, 0), APROPOS_POLICE, APROPOS_TEXTE_POS_X, APROPOS_TEXTE_POS_Y+APROPOS_POLICE*10, POLICE_2);
	affich_image(apropos->img_apropos->surf_image, img_texte);
	
	//Initialisation du bouton retour
	apropos->btn_retour=creation_bouton("retour.gif", "retour2.gif",(ECRAN_LARGEUR-BTN_ACCUEIL_LARGEUR)/2, BTN_ACCUEIL_POS_Y+2*BTN_ACCUEIL_HAUTEUR);
	
	return(apropos);
}

void destruction_apropos(struct_apropos* apropos)
{
	//Destruction de l'image du texte du me nu apropos
	destruction_image(apropos->img_apropos);
	//Destruction du bouton retour
	destruction_bouton(apropos->btn_retour);
	//Destruction de l'image du titre
	destruction_image(apropos->img_titre);
	//Destruction du menu apropos
	delete apropos;
	
}

struct_multi* initialisation_multi(SDL_Surface* surf_ecran)
{
	//Variable de boucle
	int i;
	//Structure du menu multi
	struct_multi* multi;
	//Création du menu multi
	multi= new struct_multi;
	
	//Image du cadre
	struct_image* img_cadre;
	//Image du texte
	struct_image* img_texte;
	
	//Création du titre de la page
	multi->img_titre=creation_texte("Multijoueur", init_rvb_couleur(255,200,0), 60, TEXTE_CENTERED, ACCUEIL_TITRE_POS_Y, POLICE_1);
	//Création de l'image du menu multi
	multi->img_multi=creation_surface(surf_ecran,(ECRAN_LARGEUR-MULTI_LARGEUR)/2, ACCUEIL_TITRE_POS_Y+200, MULTI_LARGEUR, MULTI_HAUTEUR, init_rvb_couleur(0, 15, 75));
	//Création du cadre
	img_cadre=creation_surface(surf_ecran, 5, 5, MULTI_LARGEUR-10, MULTI_HAUTEUR-10, init_rvb_couleur(50, 150, 150));
	//Affichage du cadre
	affich_image(multi->img_multi->surf_image, img_cadre);
	//Création et affichage des images des lignes du texte du menu multi
	img_texte=creation_texte("Désolé mais le mode multijoueur n'est", init_rvb_couleur(0, 0, 50), 30, MESSAGE_CENTERED, MULTI_TEXTE_POS_Y, POLICE_2);
	affich_image(multi->img_multi->surf_image, img_texte);
	img_texte=creation_texte("pas disponible dans la version", init_rvb_couleur(0, 0, 50), 30, MESSAGE_CENTERED, MULTI_TEXTE_POS_Y+30, POLICE_2);
	affich_image(multi->img_multi->surf_image, img_texte);
	img_texte=creation_texte("de présentation.", init_rvb_couleur(0, 0, 50), 30, MESSAGE_CENTERED, MULTI_TEXTE_POS_Y+60, POLICE_2);
	affich_image(multi->img_multi->surf_image, img_texte);

	
	//Initialisation du bouton retour
	multi->btn_retour=creation_bouton("retour.gif", "retour2.gif",(ECRAN_LARGEUR-BTN_ACCUEIL_LARGEUR)/2, BTN_ACCUEIL_POS_Y+2*BTN_ACCUEIL_HAUTEUR);
	
	//On retourne la structure du menu multi
	return(multi);
}

void destruction_multi(struct_multi* multi)
{
	//Destruction de l'image du texte du menu multi
	destruction_image(multi->img_multi);
	//Destruction du bouton retour
	destruction_bouton(multi->btn_retour);
	//Destruction de l'image du titre
	destruction_image(multi->img_titre);
	//Destruction du menu multi
	delete multi;
	
}

struct_message* initialisation_message(SDL_Surface* surf_ecran, char* titre, char* str_contenu, int int_type_message)
{
	//Variable de boucle
	int i;
	//Structure du message
	struct_message* message;
	//Création du message
	message= new struct_message;
	
	//Image temporaire du cadre du message
	struct_image* img_cadre;
	//Image temporaire du titre
	struct_image* img_titre;
	//Image temporaire d'une ligne du texte
	struct_image* img_texte;
	//Texte du message
	char ** str_texte;
	
	//Découpage du message
	message->int_nbre_ligne=decoupage_string(&str_texte, str_contenu);
	
	//Création de l'image du message
	message->img_message=creation_surface(surf_ecran, POS_X_PLATEAU+CASE_HAUTEUR+(TAILLE_CENTRE-MESSAGE_LARGEUR)/2, POS_Y_PLATEAU+CASE_HAUTEUR+(TAILLE_CENTRE-MESSAGE_HAUTEUR)/2, MESSAGE_LARGEUR, 180+((message->int_nbre_ligne)*20), init_rvb_couleur(0, 0, 0));
	
	//Selon le type de message, on change la couleur de fond du message
	switch(int_type_message)
	{
		//Dans le cas d'un message de Krystel
		case MESSAGE_KRYSTEL:
			//Création du fond du message
			img_cadre=creation_surface(surf_ecran, 3, 3, MESSAGE_LARGEUR-6, 180+((message->int_nbre_ligne)*20)-6, init_rvb_couleur(85, 115, 215));
			break;
		//Dans le cas d'un message de Nadège
		case MESSAGE_NADEGE:
			//Création du fond du message
			img_cadre=creation_surface(surf_ecran, 3, 3, MESSAGE_LARGEUR-6, 180+((message->int_nbre_ligne)*20)-6, init_rvb_couleur(215, 85, 45));
			break;
		//Dans le cas d'un message de prison
		case MESSAGE_INFO_PRISON:
			//Création du fond du message
			img_cadre=creation_surface(surf_ecran, 3, 3, MESSAGE_LARGEUR-6, 180+((message->int_nbre_ligne)*20)-6, init_rvb_couleur(215, 85, 45));
			break;
		//Dans tout les autres cas
		default:
			//Création du fond du message
			img_cadre=creation_surface(surf_ecran, 3, 3, MESSAGE_LARGEUR-6, 180+((message->int_nbre_ligne)*20)-6, init_rvb_couleur(185, 235, 140));
			break;
	}
	
	//Affichage du cadre sur l'image du message
	affich_image(message->img_message->surf_image, img_cadre);
	
	//Si il y à un titre
	if(titre)
	{
		//Création de l'image du titre
		img_titre=creation_texte(titre, init_rvb_couleur(0, 0, 0), 30, MESSAGE_CENTERED, 5, POLICE_2);
		//Affichage du titre dans le message
		affich_image(message->img_message->surf_image, img_titre);
		//Destruction de l'image du titre
		destruction_image(img_titre);
	}
	
	//Pour chaque ligne du texte
	for(i=0;i<(message->int_nbre_ligne);i++)
	{
		//Création de l'image de la ligne
		img_texte=creation_texte(str_texte[i], init_rvb_couleur(0, 0, 0), 20, MESSAGE_CENTERED, 60+20*i, POLICE_2);
		//Affichage de la ligne de texte dans le message
		affich_image(message->img_message->surf_image, img_texte);
	}
	
	//Selon le type de message
	switch(int_type_message)
	{
		//Dans le cas d'un message pour quitter le programme
		case MESSAGE_QUITTER:
			//Il y a 2 boutons à afficher
			message->int_nbre_bouton=3;
			//Allocation du tableau de bouton
			message->btn_boutons=new struct_bouton*[message->int_nbre_bouton];
			//Création du bouton sauvegarder
			message->btn_boutons[0]=creation_bouton("sauvegarder.gif", "sauvegarder2.gif", image_get_x(message->img_message)+(MESSAGE_LARGEUR-3*165)/4, image_get_y(message->img_message)+image_get_h(message->img_message)-65);
			//Création du bouton quitter
			message->btn_boutons[1]=creation_bouton("exit.gif", "exit2.gif", image_get_x(message->img_message)+2*(MESSAGE_LARGEUR-3*165)/4+165, image_get_y(message->img_message)+image_get_h(message->img_message)-65);
			//Création du bouton annuler
			message->btn_boutons[2]=creation_bouton("annuler.gif", "annuler2.gif", image_get_x(message->img_message)+3*(MESSAGE_LARGEUR-3*165)/4+2*165, image_get_y(message->img_message)+image_get_h(message->img_message)-65);
			break;
		//Dans le cas d'un message de demande d'action pour la prison
		case MESSAGE_PRISON:
			//Il y a 3 boutons à afficher
			message->int_nbre_bouton=3;
			//Allocation du tableau de bouton
			message->btn_boutons=new struct_bouton*[message->int_nbre_bouton];
			//Création du bouton attendre
			message->btn_boutons[0]=creation_bouton("attendre.gif", "attendre2.gif", image_get_x(message->img_message)+(MESSAGE_LARGEUR-3*165)/4, image_get_y(message->img_message)+image_get_h(message->img_message)-65);
			//Création du bouton payer
			message->btn_boutons[1]=creation_bouton("payer.gif", "payer2.gif", image_get_x(message->img_message)+2*(MESSAGE_LARGEUR-3*165)/4+165, image_get_y(message->img_message)+image_get_h(message->img_message)-65);
			//Création du bouton certificat
			message->btn_boutons[2]=creation_bouton("certificat.gif", "certificat2.gif", image_get_x(message->img_message)+3*(MESSAGE_LARGEUR-3*165)/4+2*165, image_get_y(message->img_message)+image_get_h(message->img_message)-65);
			break;
		//Dans tout les autres cas
		default:
			//Il n'y a qu'un seul bouton
			message->int_nbre_bouton=1;
			//Allocation du tableau de bouton
			message->btn_boutons=new struct_bouton*[message->int_nbre_bouton];
			//Création du bouton valider
			message->btn_boutons[0]=creation_bouton("valider.gif", "valider2.gif", image_get_x(message->img_message)+(MESSAGE_LARGEUR-165)/2, image_get_y(message->img_message)+image_get_h(message->img_message)-65);
			break;
	}
	
	//Destruction de l'image des lignes du texte
	destruction_image(img_texte);
	
	//Destruction de l'image du cadre
	destruction_image(img_cadre);
	
	//Désallocatiion de chacune des lignes du texte
	for(i=0; i<(message->int_nbre_ligne); i++) delete str_texte[i];
	
	//Désallocation du texte
	delete str_texte;

	//On retourne le message
	return(message);
}

void destruction_message(struct_message* message)
{
	//Variable de boucle
	int i;
	
	//On désalloue chaque bouton
	for(i=0; i<(message->int_nbre_bouton); i++)
	{
		//Destruction du bouton
		destruction_bouton(message->btn_boutons[i]);
	}
	//Destruction du tableau de bouton
	delete message->btn_boutons;
	//Destruction de l'image du message
	destruction_image(message->img_message);
}

struct_image* initialisation_msg_info(SDL_Surface* surf_ecran, char* titre, char* str_contenu)
{
	//Variable de boucle
	int i;
	//Image du message d'information
	struct_image* img_info;	
	//Image temporaire du cadre du message
	struct_image* img_cadre;
	//Image temporaire du titre
	struct_image* img_titre;
	//Image temporaire d'une ligne du texte
	struct_image* img_texte;
	//Texte du message
	char ** str_texte;
	//Nombre de ligne du message
	int int_nbre_ligne;
	
	//Découpage du message
	int_nbre_ligne=decoupage_string(&str_texte, str_contenu);
	
	//Création de l'image du message
	img_info=creation_surface(surf_ecran, POS_X_PLATEAU+CASE_HAUTEUR+(TAILLE_CENTRE-MESSAGE_LARGEUR)/2, POS_Y_PLATEAU+CASE_HAUTEUR+(TAILLE_CENTRE-MESSAGE_HAUTEUR)/2, MESSAGE_LARGEUR, 100+(int_nbre_ligne*20), init_rvb_couleur(0, 0, 0));
	
	//Création du fond du message
	img_cadre=creation_surface(surf_ecran, 3, 3, MESSAGE_LARGEUR-6, 100+(int_nbre_ligne*20)-6, init_rvb_couleur(185, 235, 140));
	
	//Affichage du cadre sur l'image du message
	affich_image(img_info->surf_image, img_cadre);
	
	//Si il y à un titre
	if(titre)
	{
		//Création de l'image du titre
		img_titre=creation_texte(titre, init_rvb_couleur(0, 0, 0), 30, MESSAGE_CENTERED, 5, POLICE_2);
		//Affichage du titre dans le message
		affich_image(img_info->surf_image, img_titre);
		//Destruction de l'image du titre
		destruction_image(img_titre);
	}
	
	//Pour chaque ligne du texte
	for(i=0;i<int_nbre_ligne;i++)
	{
		//Création de l'image de la ligne
		img_texte=creation_texte(str_texte[i], init_rvb_couleur(0, 0, 0), 20, MESSAGE_CENTERED, 60+20*i, POLICE_2);
		//Affichage de la ligne de texte dans le message
		affich_image(img_info->surf_image, img_texte);
	}

	
	//Destruction de l'image des lignes du texte
	destruction_image(img_texte);
	
	//Destruction de l'image du cadre
	destruction_image(img_cadre);
	
	//Désallocatiion de chacune des lignes du texte
	for(i=0; i<int_nbre_ligne; i++) delete str_texte[i];
	
	//Désallocation du texte
	delete str_texte;
	//On retourne l'image du message d'information
	return(img_info);
}

struct_pnl_menu* initialisation_pnl_menu(SDL_Surface* surf_ecran)
{
	//Variable de boucle
	int i;
	//Structure du panneau
	struct_pnl_menu* pnl_menu;
	//Création du panneau
	pnl_menu= new struct_pnl_menu;
	//Image temporaire du fond du panneau
	struct_image* img_fond_panneau;

	//Création de l'image du panneau
	pnl_menu->img_panneau=creation_surface(surf_ecran, PANNEAU_MENU_POS_X, PANNEAU_MENU_POS_Y, PANNEAU_MENU_LARGEUR, PANNEAU_MENU_HAUTEUR, init_rvb_couleur(0, 0, 0));
	//Création de l'image de fond du panneau
	img_fond_panneau=creation_surface(surf_ecran, 3, 3, PANNEAU_MENU_LARGEUR-6, PANNEAU_MENU_HAUTEUR-6, init_rvb_couleur(0, 0, 125));
	
	//Affichage du fond sur le panneau
	affich_image(pnl_menu->img_panneau->surf_image, img_fond_panneau);
	
	//Création du bouton quitter
	pnl_menu->btn_quitter=creation_bouton("quitter.gif", "quitter2.gif", PANNEAU_MENU_POS_X+2*(PANNEAU_MENU_LARGEUR-2*PANNEAU_OBJET_TAILLE)/3+PANNEAU_OBJET_TAILLE, PANNEAU_MENU_POS_Y+10);
	
	//Création du bouton sauvegarder
	pnl_menu->btn_sauvegarder=creation_bouton("sauvegarder.png", "sauvegarder2.png", PANNEAU_MENU_POS_X+(PANNEAU_MENU_LARGEUR-2*PANNEAU_OBJET_TAILLE)/3, PANNEAU_MENU_POS_Y+10);
	
	//Destruction de l'image temporaire du fond du panneau
	destruction_image(img_fond_panneau);
	
	//On retourne la structure du panneau menu
	return(pnl_menu);
}

void destruction_pnl_menu(struct_pnl_menu* pnl_menu)
{
	//Destruction du bouton quitter
	destruction_bouton(pnl_menu->btn_quitter);
	//Destruction du bouton sauvegarder
	destruction_bouton(pnl_menu->btn_sauvegarder);
	//Destruction de l'image du panneau
	destruction_image(pnl_menu->img_panneau);
	//Destruction du panneau
	delete pnl_menu;
}

struct_pnl_fdt* initialisation_pnl_fdt(SDL_Surface* surf_ecran)
{
	//Variable de boucle
	int i;
	//Structure du panneau
	struct_pnl_fdt* pnl_fdt;
	//Création du panneau
	pnl_fdt= new struct_pnl_fdt;
	//Image temporaire du fond du panneau
	struct_image* img_fond_panneau;

	//Création de l'image du panneau
	pnl_fdt->img_panneau=creation_surface(surf_ecran, PANNEAU_FDT_POS_X, PANNEAU_FDT_POS_Y, PANNEAU_FDT_LARGEUR, PANNEAU_FDT_HAUTEUR, init_rvb_couleur(0, 0, 0));
	//Création de l'image de fond du panneau
	img_fond_panneau=creation_surface(surf_ecran, 3, 3, PANNEAU_FDT_LARGEUR-6, PANNEAU_FDT_HAUTEUR-6, init_rvb_couleur(0, 0, 125));
	
	//Affichage du fond sur le panneau
	affich_image(pnl_fdt->img_panneau->surf_image, img_fond_panneau);
	
	//Création du bouton finir
	pnl_fdt->btn_finir=creation_bouton("finir.gif", "finir2.gif",PANNEAU_FDT_POS_X+(PANNEAU_FDT_LARGEUR-160)/2, PANNEAU_FDT_POS_Y+10);
	
	//Création du texte "à vous de jouer"
	pnl_fdt->img_message=creation_texte("A vous de jouer...", init_rvb_couleur(225, 25, 25), 25, PANNEAU_FDT_POS_X+20, PANNEAU_FDT_POS_Y+15, POLICE_2);

	//Destruction de l'image temporaire du fond du panneau
	destruction_image(img_fond_panneau);
	
	//On retourne la structure du panneau fdt
	return(pnl_fdt);
}

void destruction_pnl_fdt(struct_pnl_fdt* pnl_fdt)
{
	//Destruction du bouton finir
	destruction_bouton(pnl_fdt->btn_finir);
	//Destruction de l'image du message
	destruction_image(pnl_fdt->img_message);
	//Destruction de l'image du panneau
	destruction_image(pnl_fdt->img_panneau);
	//Destruction du panneau
	delete pnl_fdt;
}

struct_msg_propriete* initialisation_msg_propriete(SDL_Surface* surf_ecran, cases* pcase, int int_type_action)
{
	//Structure du message de la propriété
	struct_msg_propriete* msg_propriete;
	//Création de du message de la propriété
	msg_propriete= new struct_msg_propriete;
	
	//Image de fond du message de propriété
	struct_image* img_fond;
		
	//Selon l'action à faire
	switch(int_type_action)
	{
		//Dans la cas d'un achat
		case ACTION_ACHAT:
			//Initialisation du nombre de boutons
			msg_propriete->int_nbre_bouton=2;
			//Création du tableau de boutons
			msg_propriete->btn_boutons= new struct_bouton*[msg_propriete->int_nbre_bouton];
			//Initialisation du bouton acheter
			msg_propriete->btn_boutons[0]=creation_bouton("acheter.gif", "acheter2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+2*DETAIL_MESSAGE_EPAISSEUR);
			//Initialisation du bouton annuler
			msg_propriete->btn_boutons[1]=creation_bouton("annuler.gif", "annuler2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+3*DETAIL_MESSAGE_EPAISSEUR+45);
			break;
		//Dans le cas d'une deshypothèque
		case  ACTION_UNHYPOTHEQUE:
			//Initialisation du nombre de boutons
			msg_propriete->int_nbre_bouton=2;
			//Création du tableau de boutons
			msg_propriete->btn_boutons= new struct_bouton*[msg_propriete->int_nbre_bouton];
			//Initialisation du bouton deshypothequer
			msg_propriete->btn_boutons[0]=creation_bouton("deshypotheque.gif", "deshypotheque2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+2*DETAIL_MESSAGE_EPAISSEUR);
			//Initialisation du bouton annuler
			msg_propriete->btn_boutons[1]=creation_bouton("annuler.gif", "annuler2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+3*DETAIL_MESSAGE_EPAISSEUR+45);
			break;
		//Dans le cas d'une hypothèque
		case  ACTION_HYPOTHEQUE:
			//Initialisation du nombre de boutons
			msg_propriete->int_nbre_bouton=2;
			//Création du tableau de boutons
			msg_propriete->btn_boutons= new struct_bouton*[msg_propriete->int_nbre_bouton];
			//Initialisation du bouton hypothequer
			msg_propriete->btn_boutons[0]=creation_bouton("hypotheque.gif", "hypotheque2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+2*DETAIL_MESSAGE_EPAISSEUR);
			//Initialisation du bouton annuler
			msg_propriete->btn_boutons[1]=creation_bouton("annuler.gif", "annuler2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+3*DETAIL_MESSAGE_EPAISSEUR+45);
			break;
		//Pour augmenter le niveau d'une salle
		case  ACTION_PLUS:
			//Initialisation du nombre de boutons
			msg_propriete->int_nbre_bouton=2;
			//Création du tableau de boutons
			msg_propriete->btn_boutons= new struct_bouton*[msg_propriete->int_nbre_bouton];
			//Initialisation du bouton augmenter
			msg_propriete->btn_boutons[0]=creation_bouton("plus.gif", "plus2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+2*DETAIL_MESSAGE_EPAISSEUR);
			//Initialisation du bouton annuler
			msg_propriete->btn_boutons[1]=creation_bouton("annuler.gif", "annuler2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+3*DETAIL_MESSAGE_EPAISSEUR+45);
			break;
		//Pour diminuer le niveau d'une salle
		case  ACTION_MOINS:
			//Initialisation du nombre de boutons
			msg_propriete->int_nbre_bouton=2;
			//Création du tableau de boutons
			msg_propriete->btn_boutons= new struct_bouton*[msg_propriete->int_nbre_bouton];
			//Initialisation du bouton diminuer
			msg_propriete->btn_boutons[0]=creation_bouton("moins.gif", "moins2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+2*DETAIL_MESSAGE_EPAISSEUR);
			//Initialisation du bouton annuler
			msg_propriete->btn_boutons[1]=creation_bouton("annuler.gif", "annuler2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+3*DETAIL_MESSAGE_EPAISSEUR+45);
			break;
		//Pour augmenter ou diminuer le niveau d'une salle
		case  ACTION_PLUS_MOINS:
			//Initialisation du nombre de boutons
			msg_propriete->int_nbre_bouton=3;
			//Création du tableau de boutons
			msg_propriete->btn_boutons= new struct_bouton*[msg_propriete->int_nbre_bouton];
			//Initialisation du bouton augmenter
			msg_propriete->btn_boutons[0]=creation_bouton("plus.gif", "plus2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+2*DETAIL_MESSAGE_EPAISSEUR);
			//Initialisation du bouton diminuer
			msg_propriete->btn_boutons[1]=creation_bouton("moins.gif", "moins2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+3*DETAIL_MESSAGE_EPAISSEUR+45);
			//Initialisation du bouton annuler
			msg_propriete->btn_boutons[2]=creation_bouton("annuler.gif", "annuler2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+4*DETAIL_MESSAGE_EPAISSEUR+90);
			break;
		//Dans tout les autres cas
		default:
			//Initialisation du nombre de boutons
			msg_propriete->int_nbre_bouton=1;
			//Création du tableau de boutons
			msg_propriete->btn_boutons= new struct_bouton*[msg_propriete->int_nbre_bouton];
			//Initialisation du bouton annuler
			msg_propriete->btn_boutons[0]=creation_bouton("annuler.gif", "annuler2.gif", DETAIL_MESSAGE_POS_X+(DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-160)/2, DETAIL_MESSAGE_POS_Y+DETAIL_HAUTEUR+DETAIL_MESSAGE_EPAISSEUR*2);
			break;
	}
	
	//Création de la surface de fond de l'image de la propriété
	msg_propriete->img_propriete=creation_surface(surf_ecran, DETAIL_MESSAGE_POS_X, DETAIL_MESSAGE_POS_Y, DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2, DETAIL_HAUTEUR+DETAIL_MESSAGE_EPAISSEUR*2+(DETAIL_MESSAGE_EPAISSEUR+45)*(msg_propriete->int_nbre_bouton), init_rvb_couleur(0, 0, 0));
	
	//Création du fond du message
	img_fond=creation_surface(surf_ecran, 3, 3, DETAIL_LARGEUR+DETAIL_MESSAGE_EPAISSEUR*2-6, DETAIL_HAUTEUR+DETAIL_MESSAGE_EPAISSEUR*2+(DETAIL_MESSAGE_EPAISSEUR+45)*(msg_propriete->int_nbre_bouton)-6, init_rvb_couleur(0, 125, 0));
	
	//Affichage du message de fond sur l'image de la propriété
	affich_image(msg_propriete->img_propriete->surf_image, img_fond);
	//Affichage de l'image détaillé de la case salle
	if(pcase->int_type==SALLE) affich_image(msg_propriete->img_propriete->surf_image, pcase->case_salle.img_detail);
	//Affichage de l'image détaillé de la case BDE et BDS
	else if(pcase->int_type==BDE || pcase->int_type==BDS) affich_image(msg_propriete->img_propriete->surf_image, pcase->case_association.img_detail);
	//Affichage de l'image détaillé de la case lieu commun
	else if(pcase->int_type>=LC_WC && pcase->int_type<=LC_PARKING) affich_image(msg_propriete->img_propriete->surf_image, pcase->case_lieu_commun.img_detail);
	//Dans tout les autres cas, il s'agit d'une erreur
	else cerr << "ERREUR !!" << endl;
	
	//On retourne le message de la propriété
	return(msg_propriete);
}

void destruction_msg_propriete(struct_msg_propriete* msg_propriete)
{
	//Variable de boucle
	int i;
	
	//On désalloue chaque bouton
	for(i=0; i<(msg_propriete->int_nbre_bouton); i++)
	{
		//Destruction du bouton
		destruction_bouton(msg_propriete->btn_boutons[i]);
	}
	//Destruction du tableau de bouton
	delete msg_propriete->btn_boutons;
	//Destruction de l'image du message
	destruction_image(msg_propriete->img_propriete);
}
