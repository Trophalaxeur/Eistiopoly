#ifndef __MONOPOLY_SDL_H_
#define __MONOPOLY_SDL_H_

#include "../header.h"

/*!
  \fn SDL_Surface* init_sdl(void)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief fonction d'initialisation de sdl

  \version 1.0
  \return la surface de l'écran
*/
SDL_Surface* init_sdl(void);

/*!
  \fn SDL_Surface* init_sdl(void)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief fonction de pause pour les tests
 
  \version 1.0
  \return surface de l'écran
*/
void mapause(void);

/*!
  \fn SDL_Surface* rotation_90(SDL_Surface* Depart)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief permet de tourner une image de 90 degré

  \param Depart surface de départ

  \version 1.0
  \return la surface tournée
*/
SDL_Surface* rotation_90(SDL_Surface* Depart);

/*!
  \fn SDL_Surface* rotation_180(SDL_Surface* Depart)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
   \brief permet de tourner une image de 180 degré

  \param Depart surface de départ

  \version 1.0
  \return la surface tournée
*/
SDL_Surface* rotation_180(SDL_Surface* Depart);

/*!
  \fn SDL_Surface* rotation_270(SDL_Surface* Depart)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief permet de tourner une image de 270 degré

  \param Depart surface de départ

  \version 1.0
  \return la surface tournée
*/
SDL_Surface* rotation_270(SDL_Surface* Depart);

/*!
  \fn SDL_Surface* creation_joueur(int int_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer la surface du joueur

  \param int_joueur numéro du joueur

  \version 1.0
  \return la surface du joueur
*/
SDL_Surface* creation_joueur(int int_joueur);

/*!
  \fn SDL_Surface* creation_case(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte1, char* texte2, int int_prix, int int_position)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer une case de type salle

  \param surf_ecran surface de l'écran
  \param couleur couleur du groupe
  \param texte1 première partie du nom de la case
  \param texte2 seconde partie du nom de la case
  \param int_prix prix de la case
  \param int_position coté sur lequel se trouve la case

  \version 1.0
  \return la surface de la case
*/
SDL_Surface* creation_case(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte1, char* texte2, int int_prix, int int_position);

/*!
  \fn SDL_Surface* creation_case_bureau(SDL_Surface* ecran, int int_type, int int_position)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer une case de type bureau

  \param ecran surface de l'écran
  \param int_type type de bureau
  \param int_position côté sur lequel se trouve la case

  \version 1.0
  \return la surface de la case
*/
SDL_Surface* creation_case_bureau(SDL_Surface* ecran, int int_type, int int_position);

/*!
  \fn SDL_Surface* creation_case_lieu_commun(SDL_Surface* ecran, int int_type)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer une case de type lieu commun

  \param ecran surface de l'écran
  \param int_type type de lieu commun

  \version 1.0
  \return la surface de la case
*/
SDL_Surface* creation_case_lieu_commun(SDL_Surface* ecran, int int_type);

/*!
  \fn SDL_Surface* creation_case_association(SDL_Surface* ecran, int int_type)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer une case de type association

  \param ecran surface de l'écran
  \param int_type type de l'association

  \version 1.0
  \return la surface de la case
*/
SDL_Surface* creation_case_association(SDL_Surface* ecran, int int_type);

/*!
  \fn SDL_Surface* creation_case_soiree(SDL_Surface* ecran, int int_type)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer une case de type soirée

  \param ecran surface de l'écran
  \param int_type type de la soirée

  \version 1.0
  \return la surface de la case
*/
SDL_Surface* creation_case_soiree(SDL_Surface* ecran, int int_type);

/*!
  \fn SDL_Surface* creation_case_coin(SDL_Surface* ecran, int int_type)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer une case spécial (chacun des coins)

  \param ecran surface de l'écran
  \param int_type type de la case

  \version 1.0
  \return la surface de la case
*/
SDL_Surface* creation_case_coin(SDL_Surface* ecran, int int_type);

/*!
  \fn SDL_Surface* creation_case_detail(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte, int int_prix, int int_prix_niveau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer la surface de la case détaillé

  \param surf_ecran surface de l'écran
  \param couleur couleur du groupe de la case
  \param texte nom de la case
  \param int_prix prix de la case
  \param int_prix_niveau prix d'un niveau de la case

  \version 1.0
  \return la surface de la case détaillé
*/
SDL_Surface* creation_case_detail(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte, int int_prix, int int_prix_niveau);

/*!
  \fn SDL_Surface* creation_case_detail_lc(SDL_Surface* surf_ecran, int int_type)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer la surface de la case détaille d'une case lieu commun

  \param surf_ecran surface de l'écran
  \param int_type type de lieu commun

  \version 1.0
  \return la surface de la case détaillé
*/
SDL_Surface* creation_case_detail_lc(SDL_Surface* surf_ecran, int int_type);

/*!
  \fn creation_case_detail_assoc(SDL_Surface* surf_ecran, int int_type)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer la surface de la case détaille d'une case association

  \param surf_ecran surface de l'écran
  \param int_type type d'association

  \version 1.0
  \return la surface de la case détaillé
*/
SDL_Surface* creation_case_detail_assoc(SDL_Surface* surf_ecran, int int_type);

/*!
  \fn SDL_Surface* creation_case_propriete(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief créer la surface de la propriété qui s'affichera dans le panneau des propriétés

  \param surf_ecran surface de l'écran
  \param couleur couleur du groupe de la case
  \param texte nom de la case

  \version 1.0
  \return la surface la propriété
*/
SDL_Surface* creation_case_propriete(SDL_Surface* surf_ecran, rvb_couleur couleur, char* texte);

/*!
  \fn SDL_Surface** creation_des(void)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief renvoit un tableau de surface contenant chacune des faces du dé

  \version 1.0
  \return le tableau des surfaces des faces du dé
*/
SDL_Surface** creation_des(void);

/*!
  \fn void destruction_des(SDL_Surface** surf_des)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief détruit les surfaces des dés

  \param surf_des tableau des surfaces des faces d'un dé

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void destruction_des(SDL_Surface** surf_des);

/*!
  \fn void affich_joueur(SDL_Surface* surf_ecran, joueur* pj_joueur,int int_position, cases* pcase)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche un joueur à l'écran

  \param surf_ecran surface de l'écran
  \param pj_joueur joueur en cours
  \param int_position position du joueur sur la case
  \param pcase case sur laquelle se trouve le joueur

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_joueur(SDL_Surface* surf_ecran, joueur* pj_joueur,int int_position, cases* pcase);

/*!
  \fn void affich_case(SDL_Surface* surf_ecran, cases* pcase)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche une case à l'écran

  \param surf_ecran surface de l'écran
  \param pcase case à afficher

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_case(SDL_Surface* surf_ecran, cases* pcase);

/*!
  \fn void affich_centre(SDL_Surface* surf_ecran, SDL_Surface* surf_centre)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le centre du plateau

  \param surf_ecran surface de l'écran
  \param surf_centre surface du centre

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_centre(SDL_Surface* surf_ecran, SDL_Surface* surf_centre);

/*!
  \fn int affich_accueil(SDL_Surface* surf_ecran)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche la page d'accueil

  \param surf_ecran surface de l'écran

  \version 1.0
  \return une action demandée du joueur
*/
int affich_accueil(SDL_Surface* surf_ecran, struct_nom_joueur** page_nom_joueur);

void affich_bouton(SDL_Surface* surf_ecran, struct_bouton* btn_bouton, bool bool_etat);
void affich_image(SDL_Surface* surf_ecran, struct_image* img_image);
void affich_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* page_nbre_joueur);
void affich_apropos(SDL_Surface* surf_ecran, struct_apropos* page_apropos);
void affich_multi(SDL_Surface* surf_ecran, struct_multi* page_multi);
void affich_menu(SDL_Surface* surf_ecran, struct_menu* page_menu);
void affich_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* page_nom_joueur);
void affich_msg_info(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, char* titre, char* message);

/*!
  \fn void affich_panneau_menu(SDL_Surface* surf_ecran, int int_etat_bouton)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le panneau du menu

  \param surf_ecran surface de l'écran
  \param int_etat_bouton état des boutons

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_panneau_menu(SDL_Surface* surf_ecran, struct_pnl_menu* pnl_menu);


/*!
  \fn void affich_panneau_joueur(SDL_Surface* surf_ecran, joueur* j_anneau_joueurs)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le panneau d'information sur le joueur

  \param surf_ecran surface de l'écran
  \param j_anneau_joueurs joueur en cours

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_panneau_joueur(SDL_Surface* surf_ecran, joueur* j_anneau_joueurs);


/*!
  \fn void affich_panneau_possessions(SDL_Surface* surf_ecran, joueur* j_anneau_joueurs)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le panneau des possessions du joueur

  \param surf_ecran surface de l'écran
  \param j_anneau_joueurs joueur en cours

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_panneau_possessions(SDL_Surface* surf_ecran, joueur* j_anneau_joueurs);


/*!
  \fn void affich_possessions_cache(SDL_Surface* surf_ecran)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le cache du panneau de possesion du joueur

  \param surf_ecran surface de l'écran

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_possessions_cache(SDL_Surface* surf_ecran);


/*!
  \fn void affich_panneau_des_bouton(SDL_Surface* surf_ecran, int int_image)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le panneau contenant le bouton lancer dé

  \param surf_ecran surface de l'écran
  \param int_image score du dé

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_panneau_des_bouton(SDL_Surface* surf_ecran, int int_image);


/*!
  \fn void affich_panneau_des(SDL_Surface* surf_ecran, SDL_Surface** surf_des, int int_de1, int int_de2)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le panneau du menu

  \param surf_ecran surface de l'écran
  \param surf_des tableau des surfaces des face du dé
  \param int_de1 score du dé numéro 1
  \param int_de2 score du dé numéro 2

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_panneau_des(SDL_Surface* surf_ecran, SDL_Surface** surf_des, int int_de1, int int_de2);


/*!
  \fn void affich_panneau_fdt(SDL_Surface* surf_ecran, bool bool_etat)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le panneau du menu

  \param surf_ecran surface de l'écran
  \param bool_etat état des boutons

  \version 1.0
  \return +++++++++++++++++++++++++++++++++++++++++++++++++
*/
void affich_panneau_fdt(SDL_Surface* surf_ecran, struct_pnl_fdt* pnl_fdt, bool bool_etat);


/*!
  \fn int affich_validation_propriete(SDL_Surface* surf_ecran, SDL_Surface* surf_fond, int int_etat, int int_nombre_boutons, ...)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche le message des propriété ainsi que les boutons d'actions possibles

  \param surf_ecran surface de l'écran
  \param surf_fond surface de la propriété
  \param int_etat état des boutons
  \param int_nombre_boutons nombre de boutons à afficher
  \param ... liste des boutons à afficher

  \version 1.0
  \return un entier d'état
*/
void affich_validation_propriete(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases* pcase, joueur* pj_joueur, int int_type_action);


/*!
  \fn void affich_joueur_depart (SDL_Surface* surf_ecran, cases** plateau,joueur* j_anneau_joueurs, int nombre_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche tout les joueurs sur la case de départ

  \param surf_ecran surface de l'écran
  \param plateau plateau de jeu
  \param j_anneau_joueurs liste chaînée des joueurs
  \param nombre_joueur nombre de joueur

  \version 1.0
  \return action ud joueur
*/
void affich_joueur_depart (SDL_Surface* surf_ecran, cases** plateau,joueur* j_anneau_joueurs, int nombre_joueur);


/*!
  \fn void affich_message(SDL_Surface* surf_ecran, SDL_Surface* surf_message, int int_type_message, int int_etat)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief affiche un message à l'écran

  \param surf_ecran surface de l'écran
  \param surf_message surface du message
  \param int_type_message type du message à afficher
  \param int_etat état des boutons

  \version 1.0
  \return rien
*/
int affich_message(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, char* titre, char* message, int int_type_message);

#endif
