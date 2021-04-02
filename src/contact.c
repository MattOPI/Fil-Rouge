#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <hash.h>


/*
    Un contact représente une association {nom, numéro, hash(nom)}
*/
struct Contact
{
    /* valeurs */
    const char *nom;
    const char *numero;
    uint32_t hash;

};


/*
    -----------------Init---------------------
*/
struct Contact *nouveau_contact(const char *nom, const char *numero, uint32_t hash)
{
    struct Contact *n_contact = malloc(sizeof( struct Contact));
    n_contact->nom = nom;
    n_contact->hash = hash;
    n_contact->numero = numero;

    return n_contact;
}


/*
    -----------------Gets----------------------
*/
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


/*
    -----------------Retours-------------------
*/
void affiche_contact( struct Contact *contact)
{
    printf("(%s, %s)", contact->nom, contact->numero);
}

void contact_free( struct Contact *contact)
{
    free(contact);
}


/*
    -----------------Fonctions-----------------
*/
char *str_copy(const char *chaine)
{
    char *ch = (char *) malloc(strlen(chaine));

    uint32_t i;
    for ( i = 0; i<strlen(chaine); i++){
        ch[i] = chaine[i];
    }
    return ch;
}







/*
    Une Cellule est caractérisé par un contact et une cellule suivante
*/
struct CelluleContact
{
    /* valeur*/
    struct Contact *contact;

    /* suivant */
    struct CelluleContact *suivant;
};


/*
    -----------------Init---------------------
*/
struct CelluleContact *nouvelle_cellule(struct CelluleContact *suivant, struct Contact *contact)
{
    struct CelluleContact *n_cellule = malloc(sizeof( struct CelluleContact));
    n_cellule->contact = contact;
    n_cellule->suivant = suivant;
    return n_cellule;
}


/*
    -----------------Gets----------------------
*/
struct Contact *get_contact(struct CelluleContact *cellule)
{
    return cellule->contact;
}

struct CelluleContact *get_suivant(struct CelluleContact *cellule)
{
    return cellule->suivant;
}


/*
    -----------------Retours-------------------
*/
void affiche_cel(struct CelluleContact *cellule){
        if (cellule->contact != NULL){
            affiche_contact(cellule->contact);
        }
        printf("\n");
}

void cellule_free(struct CelluleContact *cellule){
    if (cellule->contact != NULL){
        contact_free(cellule->contact);
    }
    free(cellule);
}

void cellule_array_free(struct CelluleContact **T, uint32_t len)
{
    uint32_t i;
    for(i= 0; i < len; i++ ){
        struct CelluleContact *cellule_courante = T[i];

        while (cellule_courante != NULL){
            struct CelluleContact *cellule_suppr = cellule_courante;
            cellule_courante = cellule_courante->suivant;
            cellule_free(cellule_suppr);
        }
    }
    free(T);
}


/*
    -----------------Fonctions-----------------
*/
void insere_suivant(struct CelluleContact *cellule, struct CelluleContact *n_cellule )
{
    n_cellule->suivant = cellule->suivant;
    cellule->suivant = n_cellule;
}

void supprime_suivant(struct CelluleContact *cellule)
{
    struct CelluleContact *cellule_suppr = cellule->suivant;
    cellule->suivant = cellule->suivant->suivant;

    cellule_free(cellule_suppr);
}


/*
    Un itérateur est caractérisé par une référence vers une cellule et vers son suivant
*/
struct CelluleIterateur
{
    struct CelluleContact *cellule_courante;

    struct CelluleContact *cellule_suivante;
};


/*
    -----------------Init---------------------
*/
struct CelluleIterateur *nouvel_iterateur(struct CelluleContact *tete)
{
    struct CelluleIterateur *iterateur = malloc(sizeof(struct CelluleIterateur));
    iterateur->cellule_courante = tete;

    if (tete != NULL){
        iterateur->cellule_suivante = tete->suivant;
    }

    return iterateur;
}


/*
    -----------------Gets----------------------
*/
struct CelluleContact *get_current(struct CelluleIterateur *iterateur)
{
    return iterateur->cellule_courante;
}


/*
    -----------------Retours-------------------
*/
void iterateur_free(struct CelluleIterateur *iterateur)
{
    free(iterateur);
}


/*
    -----------------Fonctions-----------------
*/
struct CelluleContact *go_next(struct CelluleIterateur *iterateur)
{
    iterateur->cellule_courante = iterateur->cellule_suivante;

    if (iterateur->cellule_suivante != NULL){
        iterateur->cellule_suivante = iterateur->cellule_suivante->suivant;
    }
    return  iterateur->cellule_courante;
}
