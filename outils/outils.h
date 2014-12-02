/*!
  \file outils.h
  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief en tete des outils
  \date 09/01/2006
  \version 1.0
*/

#ifndef __MONOPOLY_OUTILS_H_
#define __MONOPOLY_OUTILS_H_

#include "../header.h"

void joueur_possede_tout(cases** plateau, joueur* joueur_encours);



/*!
  \fn char* ajout_caractere(char* texte, int int_caractere)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief ajoute un caractere (en code UTF-8) en fin de chaine

  \param texte texte initial
  \param int_caractere entier correspondant � une lettre

  \version 1.0
  \return la chaine initiale avec le caract�re � la fin
*/
char* ajout_caractere(char* texte, int int_caractere);

/*!
  \fn int nombre_joueur_case(joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief calcule le nombre de joueur sur une case

  \param pj_joueur le joueur actuellement en train de jouer son tour

  \version 1.0
  \return le nombre de joueur sur la case
*/
int nombre_joueur_case(joueur* pj_joueur);

/*!
  \fn void swap_carte(information* cartes_a_melanger[16], int position_case1, int position_case2)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief �change de cartes dans un tableau d'un bureau

  \param cartes_a_melanger tableau des cartes � m�langer
  \param position_case1 position de la premi�re carte � �changer dans le tableau
  \param position_case2 position de la seconde carte � �changer dans le tableau

  \version 1.0
  \return rien
*/
void swap_carte(information* cartes_a_melanger[16], int position_case1, int position_case2);

/*!
  \fn void melanger_cartes(information* cartes_a_melanger[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief m�lange les cartes du bureau en effectuant une suite al�atoire d'�changes

  \param cartes_a_melanger tableau des cartes � m�langer
  
  \version 1.0
  \return rien
*/
void melanger_cartes(information* cartes_a_melanger[16]);

/*!
  \fn void melanger_cartes(information* cartes_a_melanger[16])

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief insert une propri�t� dans une liste de propri�t�s tri� par type � la place qu'il faut

  \param premier_maillon t�te de la liste cha�n�e de propri�t�
  \param case_achetee propri�t� � ajouter � la liste
  
  \version 1.0
  \return la t�te de la liste de propri�t�s
*/
possession* insertion_bonne_place_propriete(possession* premier_maillon, cases* case_achetee);

/*!
  \fn bool possession_autres_cartes(cases** plateau,joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief verifie si le joueur poss�de les autres cartes de la m�me couleur que celle ou il se trouve

  \param plateau tableau contenant les cases du plateau
  \param pj_joueur joueur qui joue actuellement
  
  \version 1.0
  \return vrai s'il les poss�de sinon faux
*/
bool possession_autres_cartes(cases** plateau,joueur* pj_joueur);

/*!
  \fn int action_possible (cases** plateau,int int_position_cases_etudiee, joueur* pj_joueur, int int_etat, int int_nb_tire)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief analyse toutes les actions possibles pour un joueur pour une case donn�e

  \param plateau tableau contenant les cases du plateau
  \param int_position_cases_etudiee cases � partir de laquelle on doit faire le traitement
  \param pj_joueur joueur qui joue actuellement
  \param int_etat indique si le joueur demande a modifier le niveau d'une salle ou s'il demande une hypoth�que ou s'il est seulement arriver sur une salle
  \param int_nb_tire nombre indiqu� par les d�s
  
  \version 1.0
  \return ACTION_ACHAT s'il peut acheter, ACTION_HUNHYPOTHEQUE s'il peut d�shypot�quer, ACTION_PLUS s'il peut augmenter le niveau de la salle, ACTION_MOINS s'il peut diminuer le niveau de la salle, ACTION_PLUS_MOINS s'il peut augmenter ou diminuer le niveau de la salle, ACTION_FINIR s'il ne peut que finir le tour, ACTION_PAYER s'il doit payer le loyer
*/
int action_possible (cases** plateau,int int_position_cases_etudiee, joueur* pj_joueur, int int_etat, int int_nb_tire);

/*!
  \fn int decoupage_string (char*** str_tab, char* str_a_diviser)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief divise une chaine en caract�re en tableau de cha�ne caract�re

  \param str_tab tableau de chaine de caract�re pour le retour de la chaine une fois divis�
  \param str_a_diviser la chaine de caract�re � diviser
  
  \version 1.0
  \return le nombre de lignes
*/
int decoupage_string (char*** str_tab, char* str_a_diviser);

/*!
  \fn cases* int_to_cases (int int_indice_case, joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief � partir de l'indice de chaine des propri�t� elle trouve la case correspondante

  \param pj_joueur joueur qui joue actuellement
  \param int_indice_case indice de la case recherch� fourni a partir de la liste de propri�t� du panneau gauche
  
  \version 1.0
  \return la case voulue
*/
cases* int_to_cases (int int_indice_case, joueur* pj_joueur);

/*!
  \fn int nombre_propriete(joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief compte le nombre de propri�t�s du joueur

  \param pj_joueur joueur qui joue actuellement
  
  \version 1.0
  \return le nombre de propri�t� du joueur
*/
int nombre_propriete(joueur* pj_joueur);

/*!
  \fn bool verification_victoire (joueur* pj_joueur)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief compte le nombre de propri�t�s du joueur

  \param pj_joueur joueur qui joue actuellement
  
  \version 1.0
  \return true si le joueur � gagnersinon false
*/
bool verification_victoire (joueur* pj_joueur);

/*!
  \fn void sauvegarde(cases** plateau, joueur* pj_joueur_tete)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief sauvegarde de la partie

  \param plateau plateau du jeu
  \param pj_joueur_tete joueur en cours
  
  \version 1.0
  \return nothing
*/
void sauvegarde(cases** plateau, joueur* pj_joueur_tete);

/*!
  \fn joueur* chargement(joueur* pj_joueur, cases** plateau, rvb_couleur couleurs[8], SDL_Surface* surf_ecran)

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief chargement de la partie

  \param plateau plateau du jeu
  \param pj_joueur joueur en cours
  \param couleurs tableau de couleur
  \param surf_ecran surface de l'�cran
  
  \version 1.0
  \return un joueur de la liste de joueur
*/
joueur* chargement(joueur* pj_joueur, cases** plateau, rvb_couleur couleurs[8], SDL_Surface* surf_ecran);

/*!
  \fn joueur* bool is_readable( const std::string & file )

  \author Franck Trey <franck.trey@eisti.fr>, Florian Lefevre <florian.lefevre@eisti.fr>
  \brief test si un fichier existe

  \param file le fichier � tester
  
  \version 1.0
  \return si le fichier existe ou non
*/
bool is_readable( const std::string & file );

int bouton_get_x(struct_bouton* btn_bouton);
int bouton_get_y(struct_bouton* btn_bouton);
int bouton_get_w(struct_bouton* btn_bouton);
int bouton_get_h(struct_bouton* btn_bouton);
int image_get_x(struct_image* img_image);
int image_get_y(struct_image* img_image);
int image_get_w(struct_image* img_image);
int image_get_h(struct_image* img_image);
void image_set_position(struct_image* img_image, int x, int y);

#endif
