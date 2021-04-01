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
    struct Contact *n_contact = malloc(sizeof( struct Contact));
    n_contact->nom = nom;
    n_contact->hash = hash;
    n_contact->numero = numero;

    return n_contact;
}

void affiche_contact( struct Contact *contact)
{
    printf("(%s, %s)", contact->nom, contact->numero);
}

void contact_free( struct Contact *contact)
{
    free(contact);
}

const char *get_nom(struct Contact *contact)
{
    return contact->nom;
}

const char *get_num(struct Contact *contact)
{
    return contact->numero;
}

uint32_t get_hash(struct Contact *contact)
{
    return contact->hash;
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
    struct CelluleContact *n_cellule = malloc(sizeof( struct CelluleContact));
    n_cellule->contact = contact;
    n_cellule->suivant = suivant;
    return n_cellule;
}

void insere_suivant(struct CelluleContact *cellule, struct CelluleContact *n_cellule )
{
    n_cellule->suivant = cellule->suivant;
    cellule->suivant = n_cellule;
}

/*
    supprime la cellule suivante et renvoie la nouvelle cellule suivante
*/
struct CelluleContact *supprime_suivant(struct CelluleContact *cellule)
{
    struct CelluleContact *cellule_suppr = cellule->suivant;
    cellule->suivant = cellule->suivant->suivant;

    cellule_free(cellule_suppr);
    return cellule->suivant;
}

struct Contact *get_contact(struct CelluleContact *cellule)
{
    return cellule->contact;
}

struct CelluleContact *get_suivant(struct CelluleContact *cellule)
{
    return cellule->suivant;
}

void affiche_cel(struct CelluleContact *cellule){
        if (cellule->contact != NULL){
            affiche_contact(cellule->contact);
        }
        printf("\n");
}

void cellule_free(struct CelluleContact *cellule){
    if (cellule->contact != NULL){
        free(cellule->contact);
    }
    free(cellule);
}


/*
    Structure d'itérateur et fonctions associées
*/


struct CelluleIterateur
{
    struct CelluleContact *cellule_courante;

    struct CelluleContact *cellule_suivante;
};

struct CelluleIterateur *nouvel_iterateur(struct CelluleContact *tete)
{
    struct CelluleIterateur *iterateur = malloc(sizeof(struct CelluleIterateur));
    iterateur->cellule_courante = tete;

    if (tete != NULL){
        iterateur->cellule_suivante = tete->suivant;
    }

    return iterateur;
}

struct CelluleContact *get_current(struct CelluleIterateur *iterateur)
{
    return iterateur->cellule_courante;
}

struct CelluleContact *go_next(struct CelluleIterateur *iterateur)
{
    iterateur->cellule_courante = iterateur->cellule_suivante;

    if (iterateur->cellule_suivante != NULL){
        iterateur->cellule_suivante = iterateur->cellule_suivante->suivant;
    }
    return  iterateur->cellule_courante;
}