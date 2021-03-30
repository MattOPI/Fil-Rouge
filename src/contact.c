/* TODO! */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct Contact   // comment peut-on rentrer des valeurs des la contruction du type? style contact(nom, num)
{
    /* valeurs */
    const char *nom;
    const char *numero;
    const int *hash;

};


struct Contact *nouveau_contact(const char *nom, const char *numero, const int *hash)
{
    struct Contact *n_contact = malloc(sizeof( struct Contact));
    n_contact->nom = nom;
    n_contact->hash = hash;
    n_contact->numero = numero;

    return n_contact;
}


void affiche_contact( struct Contact *contact){
    printf("(%s, %s)", contact->nom, contact->numero);
}


struct CelluleContact
{
        /* valeur*/
    struct Contact *contact;

    /* suivant */
    struct CelluleContact *suivant; // voir pour la valeur par default
};


struct CelluleContact *nouvelle_cellule(struct CelluleContact *suivant, struct Contact *contact)
{
    struct CelluleContact *n_cellule = malloc(sizeof( struct CelluleContact));
    n_cellule->contact = contact;
    n_cellule->suivant = suivant;
    return n_cellule;
}



const char *insere(struct Contact *contact, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;
    struct CelluleContact *n_cellule = nouvelle_cellule(NULL, contact);

    while( cellule_courante->suivant != NULL){
        if( cellule_courante->suivant->contact->hash == contact->hash){
            struct Contact *ancien_contact = cellule_courante->suivant->contact;

            n_cellule->suivant = cellule_courante->suivant->suivant;
            cellule_courante->suivant = n_cellule;

            return ancien_contact->numero;

        }
        cellule_courante = cellule_courante->suivant;
    }
<<<<<<< HEAD
=======

    n_cellule->suivant = cellule_courante->suivant;
    cellule_courante->suivant = n_cellule;
>>>>>>> 7532a9324169475b25663126d2f16182d3947ede
    return NULL;
}


const char *recherche(const char *nom, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;
    uint32_t *h_nom = hash(nom);

    while ( cellule_courante != NULL){
        if (cellule_courante->contact->hash == h_nom){
            return cellule_courante->contact->numero;
        }
    }
    return NULL;
}


void supprime(const char *nom, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;
    uint32_t *h_nom = hash(nom);

    while( cellule_courante->suivant != NULL){
        if( cellule_courante->suivant->contact->hash  == h_nom){
            cellule_courante->suivant = cellule_courante->suivant->suivant;
        }
    }
}

void affiche_cel(struct CelluleContact *tete){
    struct CelluleContact *cellule_courante = tete->suivant;

    while( cellule_courante != NULL){
        affiche_contact(cellule_courante->contact);
        printf("\n");
    }
}
