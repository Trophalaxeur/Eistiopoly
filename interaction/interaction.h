/*!
  \file interaction.h
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief en tete des fonctions gérant l'interaction avec le joueur
  \date 09/01/2006
  \version 1.0
*/

#ifndef __MONOPOLY_INTERACTION_H_
#define __MONOPOLY_INTERACTION_H_

#include "../header.h"

/*!
  \fn int attente_clic(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur,cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief détermine l'action à entreprendre en fonction du clic du joueur pendant le jeu

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège

  \version 1.0
  \return -1 fonctionnement normal, 0 quitter le jeu, 1 tour du joueur terminé ce qui correspond à la dernière action du joueur
*/
int attente_clic(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur,cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16], struct_pnl_menu* pnl_menu, struct_pnl_fdt* pnl_fdt);

/*!
  \fn int attente_action_accueil(SDL_Surface* surf_ecran, SDL_Surface* surf_boutons[4], SDL_Surface* surf_nombre[6], SDL_Surface* surf_fleche_gauche, SDL_Surface* surf_fleche_droite)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief détermine l'action à entreprendre en fonction du clic du joueur sur la page d'accueil

  \param surf_ecran surface de l'écran
  \param surf_boutons tableau des surfaces des boutons de l'accueil
  \param surf_nombre tableau des surfaces des chiffres
  \param surf_fleche_gauche surface de la flèche de gauche
  \param surf_fleche_droite surface de la flèche de droite

  \version 1.0
  \return le nombre de joueur si ça c'est bien passé sinon -1
*/
int attente_action_accueil(SDL_Surface* surf_ecran, struct_bouton* btn_quitter, struct_image* img_cache, struct_nom_joueur** info_nom_joueur);

int gestion_clavier_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* nom_joueur, int int_key);
bool gestion_survol_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* nom_joueur, int x, int y, bool bool_need_maj);
int gestion_clic_nom_joueur(SDL_Surface* surf_ecran, struct_nom_joueur* nom_joueur, int x, int y);
int gestion_clavier_menu(SDL_Surface* surf_ecran, struct_menu* menu, int int_key);
int attente_action_message(SDL_Surface* surf_ecran, struct_message* msg_message);
bool gestion_survol_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* nbre_joueur, int x, int y, bool bool_need_maj);
int gestion_clavier_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* nbre_joueur, int int_key);
int gestion_clic_nbre_joueur(SDL_Surface* surf_ecran, struct_nbre_joueur* nbre_joueur, int x, int y);
int attente_action_msg_propriete(SDL_Surface* surf_ecran, struct_msg_propriete* msg_propriete);

bool gestion_survol_apropos(SDL_Surface* surf_ecran, struct_apropos* apropos, int x, int y, bool bool_need_maj);
int gestion_clavier_apropos(SDL_Surface* surf_ecran, struct_apropos* apropos, int int_key);
int gestion_clic_apropos(SDL_Surface* surf_ecran, struct_apropos* apropos, int x, int y);

bool gestion_survol_multi(SDL_Surface* surf_ecran, struct_multi* multi, int x, int y, bool bool_need_maj);
int gestion_clavier_multi(SDL_Surface* surf_ecran, struct_multi* multi, int int_key);
int gestion_clic_multi(SDL_Surface* surf_ecran, struct_multi* multi, int x, int y);
#endif
