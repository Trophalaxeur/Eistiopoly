/*!
  \file initialisation.h
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief en tete des fonctions necessaires à l'initialisation du monopoly
  \date 09/01/2006
  \version 0.0.1
*/

#ifndef __MONOPOLY_INIT_H_
#define __MONOPOLY_INIT_H_

#include "../header.h"


/*!
  \fn rvb_couleur init_rvb_couleur(int rouge, int vert, int bleu)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise une structure joueur en fonction des paramètre

  \param rouge valeur pour la valeur rouge
  \param vert valeur pour la valeur vert
  \param bleu valeur pour la valeur bleu

  \version 0.0.1
  \return  la couleur
*/
rvb_couleur init_rvb_couleur(int rouge, int vert, int bleu);

/*!
  \fn void init_tab_rvb_couleur(rvb_couleur couleur[8]);

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise le tableau de couleur

  \param couleur tableau de couleur

  \version 0.0.1
  \return  rien
*/
void init_tab_rvb_couleur(rvb_couleur couleur[8]);

/*!
  \fn void init_case_salle(SDL_Surface* surf_ecran, rvb_couleur couleurs[8], cases* pcase, int int_type, int int_numero, int int_prix, char* str_nom1, char* str_nom2, int int_groupe, int int_prix_niveau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cases salles

  \param surf_ecran surface de l'écran
  \param couleurs tableau de couleur
  \param pcase case en cours de création
  \param int_type le type de case
  \param int_numero numero de la case
  \param int_prix prix de la case
  \param str_nom1 nom de la case
  \param str_nom2 nom de la case
  \param int_groupe groupe de la case
  \param int_prix_niveau prix pour augmenter d'un niveau

  \version 0.0.1
  \return  rien
*/
void init_case_salle(SDL_Surface* surf_ecran, rvb_couleur couleurs[8], cases* pcase, int int_type, int int_numero, int int_prix, char* str_nom1, char* str_nom2, int int_groupe, int int_prix_niveau);

/*!
  \fn void init_case_association(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero);

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cases associations

  \param surf_ecran surface de l'écran
  \param pcase case en cours de création
  \param int_type type de la case
  \param int_numero numéro de la case

  \version 0.0.1
  \return  rien
*/
void init_case_association(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero);

/*!
  \fn void init_case_lieu_commun(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cases lieu commun

  \param surf_ecran surface de l'écran
  \param pcase case en cours de création
  \param int_type type de la case
  \param int_numero numéro de la case

  \version 0.0.1
  \return  rien
*/
void init_case_lieu_commun(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero);

/*!
  \fn void init_case_soiree(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero);

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cases soirée

  \param surf_ecran surface de l'écran
  \param pcase case en cours de création
  \param int_type type de la case
  \param int_numero numéro de la case

  \version 0.0.1
  \return  rien
*/
void init_case_soiree(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero);

/*!
  \fn void init_case_special(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)
  
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cases spéciales

  \param surf_ecran surface de l'écran
  \param pcase case en cours de création
  \param int_type type de la case
  \param int_numero numéro de la case

  \version 0.0.1
  \return  rien
*/
void init_case_special(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero);

/*!
  \fn void init_case_administration(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cases adimnistration

  \param surf_ecran surface de l'écran
  \param pcase case en cours de création
  \param int_type type de la case
  \param int_numero numéro de la case

  \version 0.0.1
  \return  rien
*/
void init_case_administration(SDL_Surface* surf_ecran, cases* pcase, int int_type, int int_numero);

/*!
  \fn possession* init_anneau_possesions()

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise l'anneau des possesions du joueur

  \version 0.0.1
  \return  NULL
*/
possession* init_anneau_possesions();

/*!
  \fn possession* creation_possession(cases* propriete)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief ajoute de façon ordonnée une propriété dans la liste

  \param propriete propriété a ajouter

  \version 0.0.1
  \return  la tète de la chaine
*/
possession* creation_possession(cases* propriete);

/*!
  \fn joueur* init_joueur(char* nom, int numero_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise le joueur

  \param nom le nom du joueur
  \param numero_joueur le numéro du joueur

  \version 0.0.1
  \return  le joueur ainsi créé
*/
joueur* init_joueur(char* nom, int numero_joueur);

/*!
  \fn void init_bureau_krystel(information* bureau_de_krystel[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cartes bureau de krystel

  \param bureau_de_krystel tableau des cartes bureau de krystel

  \version 0.0.1
  \return  rien
*/
void init_bureau_krystel(information* bureau_de_krystel[16]);

/*!
  \fn void init_bureau_nadege(information* bureau_de_nadege[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise les cartes bureau de nadège

  \param bureau_de_nadege tableau des cartes bureau de nadege

  \version 0.0.1
  \return  rien
*/
void init_bureau_nadege(information* bureau_de_nadege[16]);

/*!
  \fn void init_bureau_nadege(information* bureau_de_nadege[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise le plateau et toutes ses cases

  \param surf_ecran surface de l'écran
  \param couleur tableau des couleur des cases
  \param plateau le plateau de jeu

  \version 0.0.1
  \return  rien
*/
void init_plateau(SDL_Surface* surf_ecran,rvb_couleur couleurs[8], cases** plateau);

/*!
  \fn joueur* init_anneau_joueur(int nombre_joueur,char** str_nom_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise le ring des joueurs

  \param nombre_joueur nombre de joueurs
  \param str_nom_joueur tableau du nom des joueurs

  \version 0.0.1
  \return  un des joueurs de l'anneau
*/
joueur* init_anneau_joueur(int nombre_joueur,char** str_nom_joueur);

/*!
  \fn cases** init_plateau_chargement(ifstream* file, cases** plateau, rvb_couleur couleurs[8], SDL_Surface* surf_ecran)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief charge les données du plateau

  \param file fichier de sauvegarde
  \param plateau plateau de jeu
  \param couleurs tableau de couleurs
  \param surf_ecran surface de l'écran

  \version 0.0.1
  \return  le plateau
*/
cases** init_plateau_chargement(ifstream* file, cases** plateau, rvb_couleur couleurs[8], SDL_Surface* surf_ecran, joueur* pj_joueur);
/*!
  \fn cases** joueur* init_anneau_joueur_chargement(int nombre_joueur, ifstream* file, cases** plateau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief créer la liste des joueurs

  \param file fichier de sauvegarde
  \param plateau plateau de jeu
  \param nombre_joueur nombre de joueur

  \version 0.0.1
  \return  le premier joueur à joué
*/
joueur* init_anneau_joueur_chargement(int nombre_joueur, ifstream* file, cases** plateau);

/*!
  \fn joueur* init_joueur_chargement(int numero_joueur, ifstream* file, cases** plateau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief créer un joueur à partir de la sauvegarde

  \param file fichier de sauvegarde
  \param plateau plateau de jeu
  \param numero_joueur numéro du joueur

  \version 0.0.1
  \return  le premier joueur à joué
*/
joueur* init_joueur_chargement(int numero_joueur, ifstream* file, cases** plateau);


struct_image* creation_image(char* nom, int pos_x, int pos_y);
struct_image* creation_surface(SDL_Surface* surf_ecran, int pos_x, int pos_y, int largeur, int hauteur, rvb_couleur couleur);
struct_image* creation_texte(char* texte, rvb_couleur couleur, int int_size, int pos_x, int pos_y, int int_police);
void destruction_image(struct_image* img_image);
struct_bouton* creation_bouton(char* nom1, char* nom2, int pos_x, int pos_y);
void destruction_bouton(struct_bouton* btn_bouton);
struct_nbre_joueur* init_struct_nbre_joueur(SDL_Surface* surf_ecran);
void destruction_nbre_joueur(struct_nbre_joueur* nbre_joueur);
struct_menu* init_struct_menu(SDL_Surface* surf_ecran);
void destruction_menu(struct_menu* menu);
struct_nom_joueur* init_struct_nom_joueur(SDL_Surface* surf_ecran, int int_nbre_joueur);
void destruction_nom_joueur(struct_nom_joueur* nom_joueur);
struct_message* initialisation_message(SDL_Surface* surf_ecran, char* titre, char* str_contenu, int int_type_message);
void destruction_message(struct_message* message);
struct_image* initialisation_msg_info(SDL_Surface* surf_ecran, char* titre, char* str_contenu);
struct_pnl_menu* initialisation_pnl_menu(SDL_Surface* surf_ecran);
void destruction_pnl_menu(struct_pnl_menu* pnl_menu);
struct_msg_propriete* initialisation_msg_propriete(SDL_Surface* surf_ecran, cases* pcase, int int_type_action);
void destruction_msg_propriete(struct_msg_propriete* msg_propriete);
struct_apropos* initialisation_apropos(SDL_Surface* surf_ecran);
void destruction_apropos(struct_apropos* apropos);
struct_multi* initialisation_multi(SDL_Surface* surf_ecran);
void destruction_multi(struct_multi* multi);
struct_pnl_fdt* initialisation_pnl_fdt(SDL_Surface* surf_ecran);
void destruction_pnl_fdt(struct_pnl_fdt* pnl_fdt);
#endif
