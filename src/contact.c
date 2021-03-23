/* TODO! */
#include <stdlib.h>
#include <stdio.h>

struct Contact   // comment peut-on rentrer des valeurs des la contruction du type? style contact(nom, num)
{
    /* valeurs */
    char *nom;
    char *numero;

};


struct Contact *nouveau_contact(char *nom, char *numero)
{
    struct Contact *n_contact = malloc(sizeof( struct Contact));
    (*n_contact).nom = nom;
    (*n_contact).numero = numero;
    return n_contact;
}


void affiche_contact( struct Contact *contact){
    printf("(%s, %s)", *(*contact).nom, *(*contact).numero);
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
    (*n_cellule).contact = contact;
    (*n_cellule).suivant = suivant;
    return n_cellule;
}



char *insere(struct Contact *contact, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;
    struct CelluleContact *n_cellule = nouvelle_cellule(NULL, contact);

    while( (*(*(*cellule_courante).suivant).contact).nom != "zzzzzzzz"){
        if( (*(*(*cellule_courante).suivant).contact).nom == (*contact).nom){
            struct Contact *ancien_contact = (*(*cellule_courante).suivant).contact;

            (*n_cellule).suivant = (*(*cellule_courante).suivant).suivant;
            (*cellule_courante).suivant = n_cellule;

            return (*ancien_contact).numero;

        } else if( (*(*(*cellule_courante).suivant).contact).nom < (*contact).nom){
            // comparaison lexicographique?
            char *ancien_num = (*(*(*cellule_courante).suivant).contact).numero;

            (*n_cellule).suivant = (*cellule_courante).suivant;
            (*cellule_courante).suivant = n_cellule;
            return NULL;
        }
        cellule_courante = (*cellule_courante).suivant;
    }
}


char *recherche(char *nom, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;

    while ( (*(*cellule_courante).contact).nom != "zzzzzzzz"){
        if ((*(*cellule_courante).contact).nom == nom){
            return (*(*cellule_courante).contact).numero;
        }
    }
    return NULL;
}


void supprime(char *nom, struct CelluleContact *tete)
{
    struct CelluleContact *cellule_courante = tete;

    while( (*(*(*cellule_courante).suivant).contact).nom != "zzzzzzzz"){
        if( (*(*(*cellule_courante).suivant).contact).nom  == nom){
            (*cellule_courante).suivant = (*(*cellule_courante).suivant).suivant;
        }
    }
}

void affiche_cel(struct CelluleContact *tete){
    struct CelluleContact *cellule_courante = (*tete).suivant;

    while( (*(*cellule_courante).contact).nom != "zzzzzzzz"){
        affiche_contact((*cellule_courante).contact);
        printf("\n");
    }
}