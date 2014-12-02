

/*!
  \file structure.h
  \author Franck.trey <franck.trey@eisti.fr>
  \brief toutes les structures necessaires pour le monopoly
  \date 03/12/2007
  \version 1.0
*/

#ifndef __MONOPOLY_STRUCTURE_H_

#define __MONOPOLY_STRUCTURE_H_


typedef struct cases;



typedef struct {
	int rouge;
	int vert;
	int bleu;

}rvb_couleur;

typedef struct {
	char texte[512]; ///> contient le texte d'information
	int type; ///> indique le type d'information dont il s'agit
					  ///> correspondant à l'information
	int valeur; ///> valeur utilisée pour le traitement (prix, position ou certificat)
}information;

typedef struct possession
{
	struct possession* suivant;
	cases* propriete;
};


typedef struct joueur{
	int int_argent; ///> argent total du joueur
	int int_certificat; ///> nb de certificats médicaux du joueurs
	int int_position; ///> numéro de la case actuelle du joueur
	int bool_debut; ///> indique si le joueur est à son premier tour
	char str_nom[64]; ///> le nom du joueur
	joueur* pjoueur_suivant; ///> pointe vers le joueur suivant
	SDL_Surface* surf_image; ///> image du jeton du joueur
	int int_double_tire; ///> nombre de doubles effectués par le joueur
	bool bool_laurence; ///> permet de savoir si le joueur est en prison ou pas
	int int_laurence; ///> nombre de tours passés dans le bureau de laurence
	possession* propriete; ///> liste chainée des propriete du joueur
}joueur;


//Structure d'une image
typedef struct
{
	SDL_Rect position; ///> Position de l'image
	SDL_Surface* surf_image; ///> Surface de l'image
}struct_image;

typedef struct cases
{
	int int_type; ///> indique le type de la structure
	
	union
	{

		struct
		{
			char str_nom[16]; ///> nom de la case
			int int_prix; ///> prix de la salle
			int int_prix_niveau; ///> prix pour augnmenter d'un niveau
			joueur* pjoueur_joueur; ///> joueur possedant la case
			int int_niveau; ///> indique le niveau de la salle
			int int_groupe; ///> indique à quel groupe appartient la salle
			struct_image* img_detail; ///> Image de la case détaillée
			SDL_Surface* surf_propriete; ///> surface de la propriété à afficher
			int bool_etat; ///> indique si la case est hypothéquée ou non
			bool bool_hypotheque; ///>indique si la case est hypothequee
			int int_valeur_hypotheque; ///>valeur de l'hypothèque
		}case_salle;

		struct
		{
			char str_nom[16]; ///> nom de la salle
		}case_administration;

		struct 
		{
			char str_nom[16]; ///> nom du lieu commun
			int int_prix; ///> prix de la salle
			joueur* pjoueur_joueur; ///> joueur possedant la salle
			int int_suivant; ///> entier du lieu commun suivant sur le plateau
			struct_image* img_detail; ///> Image de la case détaillé
			SDL_Surface* surf_propriete;
			bool bool_hypotheque; ///>indique si la case est hypothequee
			int int_valeur_hypotheque; ///>valeur de l'hypothèque
		}case_lieu_commun;

		struct 
		{
			char str_nom[16]; ///> nom de l'association
			int int_prix; ///> prix de la salle
			joueur* pjoueur_joueur; ///> joueur possedant la salle
			int int_autre_bureau; ///> position de l'aurtre association sur le plateau
			struct_image* img_detail; ///> Image de la case détaillé
			SDL_Surface* surf_propriete;
			bool bool_hypotheque; ///>indique si la case est hypothequee
			int int_valeur_hypotheque; ///>valeur de l'hypothèque			
		}case_association;
							  
		struct 
		{
			char str_nom[16]; ///> nom de l'association
			int int_prix; ///> prix de la salle		
		}case_soiree;
		
		struct
		{
			char str_nom[16]; ///> nom de la case spéciale
			int int_argent; ///> argent de la machine a café
		}machine_a_cafe;
		
		struct 
		{
			char str_nom[16]; ///> nom de la case spéciale
		}case_special;

	};
	
	SDL_Surface* surf_image; ///> surface de la case
	int int_position; ///> indique la position de la case sur le plateau
	SDL_Rect rect_coordonnees; ///> coordonnées en pixel de la case
}cases;

//Structure d'un bouton
typedef struct
{
	SDL_Rect position; ///> Position du bouton
	SDL_Surface* surf_bouton[2]; ///> Surfaces du bouton
	
}struct_bouton;

//Structure de la page de selection du nombre de joueur
typedef struct
{
	struct_image* img_titre; ///> Titre de la page	
	struct_image* img_nombres[6]; ///> Images des nombres
	struct_image* img_nbre_cache; ///> Cache de l'image du nombre
	struct_bouton* btn_fleche_gauche; ///> Image de la fleche gauche
	struct_bouton* btn_fleche_droite; ///> Image de la fleche droite
	struct_bouton* btn_valider; ///> Bouton valider
	struct_bouton* btn_retour; ///> Bouton retour
	int int_select; ///> Numéro du bouton survolé
}struct_nbre_joueur;

//Structure de la page menu principal
typedef struct
{
	struct_image* img_titre; ///> Titre de la page
	struct_bouton* btn_items[5]; ///> Items du menu
	int int_select; ///> Numéro de l'item sélectionné
}struct_menu;

//Structure de la page des noms des joueurs
typedef struct
{
	int int_nbre_joueur; ///> Nombre de joueur
	int int_select; ///> Numéro du champ en cours de saisie
	struct_image* img_titre; ///> Titre de la page
	struct_bouton* btn_jouer; ///> Bouton jouer
	struct_bouton* btn_retour; ///> Bouton retour
	struct_image** img_texte_noms; ///> Images des titres des champs noms des joueurs
	struct_image* img_champ; ///> Champ pour les noms
	struct_image* img_curseur; ///> Image du curseur de position
	struct_image* img_curseur_cache; ///> Image du cache du curseur de position
	char** str_noms; ///> Chaine de caractères contenant les noms des joueurs
}struct_nom_joueur;

//Structure du menu apropos
typedef struct
{
	struct_image* img_titre; ///> Titre de la page
	struct_image* img_apropos; ///> Image de fond du menu apropos
	struct_bouton* btn_retour; ///> Bouton retour
}struct_apropos;

//Structure du menu multi
typedef struct
{
	struct_image* img_titre; ///> Titre de la page
	struct_image* img_multi; ///> Image de fond du menu multi
	struct_bouton* btn_retour; ///> Bouton retour
}struct_multi;

//Structure des messages à afficher
typedef struct
{
	int int_nbre_bouton; ///> Nombre de bouton
	int int_nbre_ligne; ///> Nombre de ligne contenu dans le texte
	struct_image* img_message; ///> Image de fond du message
	struct_bouton** btn_boutons; ///> Tableaux des boutons
}struct_message;

//Structure du panneau menu
typedef struct
{
	struct_image* img_panneau; ///> Image du panneau
	struct_bouton* btn_quitter; ///> Bouton quitter
	struct_bouton* btn_sauvegarder; ///> Bouton sauvegarder
}struct_pnl_menu;

//Structure du panneau fdt
typedef struct
{
	struct_image* img_panneau; ///> Image du panneau
	struct_bouton* btn_finir; ///> Bouton finir votre tour
	struct_image* img_message; ///>Image du message à votre tour de jouer
}struct_pnl_fdt;

//Structure des messages de propriétés
typedef struct
{
	int int_nbre_bouton; ///> Nombre de bouton
	struct_image* img_propriete; ///> Image de fond du messagede propriété
	struct_bouton** btn_boutons; ///> Tableaux des boutons
}struct_msg_propriete;

#endif
