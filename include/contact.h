#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <stdint.h>


/*
  Un contact représente une association {nom, numéro, hash(nom)}
*/
struct Contact;

// Init
struct Contact *nouveau_contact(const char *nom, const char *numero, uint32_t hash);

// Gets
const char *get_nom(struct Contact *contact);

const char *get_num(struct Contact *contact);

uint32_t get_hash(struct Contact *contact);

// Fonctions

// Retours
void affiche_contact( struct Contact *contact);

void contact_free( struct Contact *contact);


/*
  Une Cellule est caractérisé par un contact et une cellule suivante
*/
struct CelluleContact;

// Init
struct CelluleContact *nouvelle_cellule(struct CelluleContact *suivant, struct Contact *contact);

// Gets
struct Contact *get_contact(struct CelluleContact *cellule);

struct CelluleContact *get_suivant(struct CelluleContact *cellule);

// Fonctions
void insere_suivant(struct CelluleContact *cellule, struct CelluleContact *n_cellule);

void supprime_suivant(struct CelluleContact *cellule);

// Retours
void affiche_cel(struct CelluleContact *cellule);

void cellule_free(struct CelluleContact *cellule);



/*
  Un itérateur est caractérisé par une référence vers une cellule et vers son suivant
*/
struct CelluleIterateur;

// Init
struct CelluleIterateur *nouvel_iterateur(struct CelluleContact *sentinelle);

// Gets
struct CelluleContact *get_current(struct CelluleIterateur *iterateur);

// Fonctions
struct CelluleContact *go_next(struct CelluleIterateur *iterateur);

// Retour
void iterateur_free(struct CelluleIterateur *iterateur);


#endif /* _CONTACT_H_ */
