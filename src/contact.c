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

            n_cellule->suivant = cellule_courante->suivant->suivant;
            res = cellule_courante->suivant->contact->numero;

            cellule_free(cellule_courante->suivant);

            cellule_courante->suivant = n_cellule;
            break;
        }
        cellule_courante = cellule_courante->suivant;
    }
    if (res == NULL){
        cellule_courante->suivant = n_cellule;
    }

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

            cellule_free(cellule_suppr);
            break;
        }
        cellule_courante = cellule_courante->suivant;
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

void cellule_free(struct CelluleContact *cellule){
    if (cellule->contact != NULL){
        contact_free(cellule->contact);
    }
    free(cellule);
}

struct CelluleIterateur
{
    struct CelluleContact *curr_cellule;
};

struct CelluleIterateur *nouvel_iterateur(struct CelluleContact *sentinelle)
{
    struct CelluleIterateur *iterateur = calloc(1, sizeof(struct CelluleIterateur));
    iterateur->curr_cellule = sentinelle;

    return iterateur;
}

struct CelluleContact *get_iterateur(struct CelluleIterateur *iterateur){
    struct CelluleContact *cellule_res = iterateur->curr_cellule;
    if (iterateur->curr_cellule != NULL){
        iterateur->curr_cellule = iterateur->curr_cellule->suivant;
    }

    return cellule_res;
}
