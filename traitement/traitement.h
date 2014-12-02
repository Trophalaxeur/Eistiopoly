/*!
  \file traitement.h
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief en tete des fonctions de traitement. 
  \date 09/01/2006
  \version 1.0
*/


#ifndef __MONOPOLY_TRAITEMENT_H_
#define __MONOPOLY_TRAITEMENT_H_

#include "../header.h"

/*!
  \fn int lancer_des(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur, cases** plateau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief fonction chargée de simuler le lancement des dés

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau

  \version 1.0
  \return le nombre obtenue par les dés
*/
int lancer_des(SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur, cases** plateau);

/*!
  \fn void avancer_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, int int_nb_tire,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief  avance le jeton case par case, traite le passage par la case départ

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param int_nb_tire nombre obtenu lors du lancer des dés
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège

  \version 1.0
  \return rien
*/
void avancer_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, int int_nb_tire,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16]);

/*!
  \fn void jeu(SDL_Surface* surf_ecran, joueur* pj_joueur_encours,cases** plateau, int nombre_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief initialise le jeu

  \param surf_ecran surface de l'écran
  \param pj_joueur_encours joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau
  \param nombre_joueur nombre de joueurs qui jouent
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège

  \version 1.0
  \return rien
*/
void jeu(SDL_Surface* surf_ecran, joueur* pj_joueur_encours,cases** plateau, int nombre_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16]);

/*!
  \fn void aller_a_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, int int_position_voulue ,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16], int delai)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief avance le jeton case par case, traite le passage par la case départ

  \param surf_ecran surface de l'écran
  \param surf_centre surface du centre du plateau
  \param int_position_voulue position voulue
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège
  \param delai délai du déplacement entre deux cases

  \version 1.0
  \return rien
*/
void aller_a_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, int int_position_voulue ,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16], int delai);

/*!
  \fn void aller_en_prison_jeton (SDL_Surface* surf_ecran, joueur* pj_joueur, cases** plateau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief envoi le joueur directement en prison

  \param surf_ecran surface de l'écran
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau

  \version 1.0
  \return rien
*/
void aller_en_prison_jeton (SDL_Surface* surf_ecran, joueur* pj_joueur, cases** plateau);

/*!
  \fn void reculer_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre ,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief recule le joueur de 3 cases

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège

  \version 1.0
  \return rien
  
 */
void reculer_jeton (SDL_Surface* surf_ecran, SDL_Surface* surf_centre ,joueur* pj_joueur, cases** plateau, information* bureau_de_krystel[16], information* bureau_de_nadege[16]);

/*!
  \fn void traitement_case_depart (SDL_Surface* surf_ecran, joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief ajoute l'argent au joueur

  \param surf_ecran surface de l'écran
  \param pj_joueur joueur qui joue actuellement

  \version 1.0
  \return rien
*/
void traitement_case_depart (SDL_Surface* surf_ecran, joueur* pj_joueur);

/*!
  \fn bool traitement_rachat_hypotheque(joueur* joueur_actuel, cases* case_hypothequee)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief rachète une hypothèque

  \param joueur_actuel joueur qui joue actuellement
  \param case_hypothequee indice de la case à déshypothéquer

  \version 1.0
  \return booléen indiquant si la fonction c'est bien dérouler
*/
bool traitement_rachat_hypotheque(joueur* joueur_actuel, cases* case_hypothequee);

/*!
  \fn bool traitement_mise_en_hypotheque (joueur* joueur_actuel, cases* case_hypothequee)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief met en place une hypothèque

  \param joueur_actuel joueur qui joue actuellement
  \param case_hypothequee indice de la case à hypothéquer

  \version 1.0
  \return booléen indiquant si la fonction c'est bien dérouler
*/
bool traitement_mise_en_hypotheque (joueur* joueur_actuel, cases* case_hypothequee);

/*!
  \fn bool traitement_payer_loyer (joueur* joueur_qui_paye, joueur* joueur_paye, int int_montant)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief paye les loyer d'une salle

  \param joueur_qui_paye joueur à qui on prend les sous
  \param joueur_paye joueur à qui on donne les sous
  \param int_montant montant de la transaction

  \version 1.0
  \return booléen indiquant si la fonction c'est bien dérouler
*/
bool traitement_payer_loyer (joueur* joueur_qui_paye, joueur* joueur_paye, int int_montant);

//=============================================================================================================
/*!
  \fn int traitement_loyer_lieu_commun(joueur* pj_joueur);

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief calcul le loyer pour les lieux communs

  \param pj_joueur joueur à qui on doit les sous


  \version 1.0
  \return le montant du loyer
*/
int traitement_loyer_lieu_commun(joueur* pj_joueur);

/*!
  \fn int traitement_loyer_association(joueur* joueur_paye, int int_nb_tire);

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief calcul le loyer d'une association

  \param joueur_paye joueur à qui on doit les sous
  \param int_nb_tire nombre indiqué par le dés
  

  \version 1.0
  \return le loyer à payer
*/
int traitement_loyer_association(joueur* joueur_paye, int int_nb_tire);

/*!
  \fn bool traitement_achat (cases* case_achetee, joueur* joueur_actuel);

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief traitement l'achat d'une propriété

  \param case_achetee indice des la case achetée
  \param joueur_actuel l'acheteur

  \version 1.0
  \return booléen qui indique si la fonction s'est bbien déroulée
*/
bool traitement_achat (cases* case_achetee, joueur* joueur_actuel);

/*!
  \fn bool traitement_augmentation_niveau(cases* pcase,joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief augmente le niveau d'une case

  \param pj_joueur joueur qui joue actuellement
  \param pcase case dont on doit changer le niveau

  \version 1.0
  \return booléen indiquant si la fonction s'est bien déroulée
*/
bool traitement_augmentation_niveau(cases* pcase,joueur* pj_joueur);

/*!
  \fn void traitement_diminution_niveau(cases* pcase, joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief diminue le niveau d'une case

  \param pj_joueur joueur qui joue actuellement
  \param pcase case dont on doit changer le niveau

  \version 1.0
  \return booléen indiquant si la fonction s'est bien déroulée
*/
void traitement_diminution_niveau(cases* pcase, joueur* pj_joueur);

/*!
  \fn void traitement_arrive_case (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau,joueur* pj_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16], int int_nombre_tire)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief  effectue les action necessaire lors de l'arrivée sur une case en fonction de son type

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param int_nombre_tire nombre obtenu lors du lancer des dés
  \param plateau tableau contenant les cases du plateau
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège

  \version 1.0
  \return rien
*/
void traitement_arrive_case (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau,joueur* pj_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16], int int_nombre_tire);

/*!
  \fn void traitement_elimination_joueur (joueur* joueur_eliminer);

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief  libère les propriété et l'espace mémoire du joueur et de ses possessions

  \param joueur_eliminer le joueur à éliminer

  \version 1.0
  \return rien
*/
void traitement_elimination_joueur (joueur* joueur_eliminer);
//=============================================================================================================

/*!
  \fn void traitement_machine_a_cafe (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief donne au joueur l'argent de la machine à café
  
  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau

  \version 1.0
  \return rien
*/
void traitement_machine_a_cafe (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur);

/*!
  \fn void traitement_bureau (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur, information* le_bureau[16], information* bureau_de_krystel[16], information* bureau_de_nadege[16], int int_id_bureau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief tire une carte du bureau voulue et effectue le traitement en fonction de la carte tirée

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau
  \param le_bureau tableau des cartes bureau à utiliser
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège
  \param int_id_bureau id du bureau à utiliser

  \version 1.0
  \return rien
*/
void traitement_bureau (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur, information* le_bureau[16], information* bureau_de_krystel[16], information* bureau_de_nadege[16], int int_id_bureau);

/*!
  \fn void traitement_soiree (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur, cases** plateau)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief fait payer le joueur suivant la case soirée sur laquelle il est

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau

  \version 1.0
  \return rien
*/
void traitement_soiree (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, joueur* pj_joueur, cases** plateau);

/*!
  \fn void traitement_bureau_laurence (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <Florian.lefevre@eisti.fr>
  \brief effectue les traitement necessaire lorsqu'un joueur est dans le bureau de laurence

  \param surf_ecran surface de l'écran
  \param surf_centre surface centrale du plateau
  \param pj_joueur joueur qui joue actuellement
  \param plateau tableau contenant les cases du plateau
  \param bureau_de_krystel tableau des cartes bureau de krystel
  \param bureau_de_nadege  tableau des cartes bureau de nadège

  \version rien
*/
void traitement_bureau_laurence (SDL_Surface* surf_ecran, SDL_Surface* surf_centre, cases** plateau, joueur* pj_joueur, information* bureau_de_krystel[16], information* bureau_de_nadege[16]);

void traitement_perdu(SDL_Surface* surf_ecran, cases** plateau,joueur* pj_joueur);
void traitement_msg_propriete(cases* pcase, joueur* pj_joueur, int int_action, int int_type_action);
#endif
