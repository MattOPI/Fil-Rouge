/* TODO! */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <hash.h>

struct Contact   // comment peut-on rentrer des valeurs des la contruction du type? style contact(nom, num)
{
    /* valeurs */
    const char *nom;
    const char *numero;
    uint32_t hash;

};


struct Contact *nouveau_contact(const char *nom, const char *numero, uint32_t hash)
{
    struct Contact *n_contact = calloc(1, sizeof( struct Contact));
    n_contact->nom = nom;
    n_contact->hash = hash;
    n_contact->numero = numero;

    return n_contact;
}


void affiche_contact( struct Contact *contact){
    printf("(%s, %s)", contact->nom, contact->numero);
}

void contact_free( struct Contact *contact){
    free(contact);
}

struct CelluleContact
{
    /* valeur*/
    struct Contact *contact;

    /* suivant */
    struct CelluleContact *suivant;
};


struct CelluleContact *nouvelle_cellule(struct CelluleContact *suivant, struct Contact *contact)
{
    struct CelluleContact *n_cellule = calloc(1, sizeof( struct CelluleContact));
    n_cellule->contact = contact;
    n_cellule->suivant = suivant;
    return n_cellule;
}

const char *get_nom(struct CelluleContact *cellule){
    return cellule->contact->nom;
}

const char *get_num(struct CelluleContact *cellule){
    return cellule->contact->numero;
}


const char *insere(struct Contact *contact, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;
    struct CelluleContact *n_cellule = nouvelle_cellule(NULL, contact);
    const char *res = NULL;

    while( cellule_courante->suivant != NULL){
        if( cellule_courante->suivant->contact->hash == contact->hash){
            struct Contact *ancien_contact = cellule_courante->suivant->contact;

            n_cellule->suivant = cellule_courante->suivant->suivant;
            cellule_courante->suivant = n_cellule;

            res = ancien_contact->numero;
            free(ancien_contact);
        }
        cellule_courante = cellule_courante->suivant;
    }

    cellule_courante->suivant = n_cellule;

    return res;
}


const char *recherche(const char *nom, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete->suivant;
    uint32_t h_nom = hash(nom);

    while ( cellule_courante != NULL){
        if (cellule_courante->contact->hash == h_nom){
            return cellule_courante->contact->numero;
        }
        cellule_courante = cellule_courante->suivant;
    }
    return NULL;
}


void supprime(const char *nom, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;
    uint32_t h_nom = hash(nom);

    while( cellule_courante->suivant != NULL){
        if (cellule_courante->suivant->contact->hash  == h_nom){
            struct CelluleContact *cellule_suppr = cellule_courante->suivant;
            cellule_courante->suivant = cellule_courante->suivant->suivant;
            free(cellule_suppr);
        }
    }
}

void affiche_cel(struct CelluleContact *tete){
    struct CelluleContact *cellule_courante = tete->suivant;

    while( cellule_courante != NULL){
        affiche_contact(cellule_courante->contact);
        printf("\n");

        cellule_courante = cellule_courante->suivant;
    }
}

void cellule_free(struct CelluleContact *tete){
    struct CelluleContact *cellule_courante = tete->suivant;
    while(cellule_courante != NULL){
        struct CelluleContact *cellule_suppr= cellule_courante;
        cellule_courante = cellule_courante->suivant;

        contact_free(cellule_suppr->contact);
        free(cellule_suppr);
    }
    free(tete);
}

struct CelluleIterateur
{
    struct CelluleContact *curr_cell;
};

struct CelluleIterateur *nouvel_iterateur(struct CelluleContact *sentinelle)
{
    struct CelluleIterateur *iterateur = calloc(1, sizeof(struct CelluleIterateur));
    iterateur->curr_cell = sentinelle;

    return iterateur;
}

struct CelluleContact *get_iterateur(struct CelluleIterateur *iterateur){
    iterateur->curr_cell = iterateur->curr_cell->suivant;
    return iterateur->curr_cell;
}
