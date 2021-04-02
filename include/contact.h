#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <stdint.h>


/*
  Un contact représente une association {nom, numéro}.
*/
struct Contact;

struct Contact *nouveau_contact(const char *nom, const char *numero, uint32_t hash);

void affche_contact( struct Contact *contact);

void contact_free( struct Contact *contact);

const char *get_nom(struct Contact *contact);

const char *get_num(struct Contact *contact);

uint32_t get_hash(struct Contact *contact);



/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */
struct CelluleContact;

struct CelluleContact *nouvelle_cellule(struct CelluleContact *suivant, struct Contact *contact);

void insere_suivant(struct CelluleContact *cellule, struct CelluleContact *n_cellule);

void supprime_suivant(struct CelluleContact *cellule);

struct Contact *get_contact(struct CelluleContact *cellule);

struct CelluleContact *get_suivant(struct CelluleContact *cellule);

void affiche_cel(struct CelluleContact *cellule);

void cellule_free(struct CelluleContact *cellule);



struct CelluleIterateur;

struct CelluleIterateur *nouvel_iterateur(struct CelluleContact *sentinelle);

struct CelluleContact *get_current(struct CelluleIterateur *iterateur);

struct CelluleContact *go_next(struct CelluleIterateur *iterateur);



#endif /* _CONTACT_H_ */
