#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct Contact;

struct Contact *nouveau_contact(char *nom, char *numero);

void affche_contact( struct Contact *contact);

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */
struct CelluleContact;

struct CelluleContact *nouvelle_cellule(struct CelluleContact *suivant, struct Contact *contact);

char *insere(struct Contact *, struct CelluleContact *);

char *recherche(char *nom, struct CelluleContact *tete);

void supprime(char *nom, struct CelluleContact *tete);

void affiche_cel(struct CelluleContact *tete);

#endif /* _CONTACT_H_ */



