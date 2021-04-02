#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>


/*
    Structure de données représentant un annuaire.
    Son contenu est détaillé dans directory.c. rien changé
*/
struct dir
{
    /* taille de l"annuaire */
    uint32_t len;

    /* remplissage */
    uint32_t occ;

    /* tableau de pointeur représentant l'annuaire */
    struct CelluleContact **T;
};

/*
    -----------------Init---------------------
*/

/*
    Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    struct dir *annuaire = malloc(sizeof(struct dir));
    annuaire->len = len;
    annuaire->occ = 0;
    annuaire->T = malloc(len*sizeof(struct  CelluleContact *));

    uint32_t i;
    for (i = 0 ; i < len; i++){
        struct CelluleContact *sentinelle = nouvelle_cellule(NULL, NULL);
        annuaire->T[i] = sentinelle;
    }
    return annuaire;
}

/*
    -----------------Gets----------------------
*/

uint32_t get_length(struct dir *annuaire)
{
    return annuaire->len;
}

uint32_t get_occupation(struct dir *annuaire)
{
    return annuaire->occ;
}

struct CelluleContact **get_array(struct dir *annuaire)
{
    return annuaire->T;
}

/*
    -----------------Retours-------------------
*/

/*
    Libère la mémoire associée à l"annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    cellule_array_free(dir->T, dir->len);
    free(dir);
}

/*
    Affiche sur la sortie standard le contenu de l"annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    uint32_t i;
    for(i= 0; i < dir->len; i++ ){

        struct CelluleContact *cellule_courante = dir->T[i];
        cellule_courante = get_suivant(cellule_courante);  /*saut de la sentinelle*/

        while (cellule_courante != NULL){
            affiche_cel(cellule_courante);
            cellule_courante = get_suivant(cellule_courante);
        }
    }
}



/*
    -----------------Fonctions-----------------
*/

/*
    Insère un nouveau contact dans l"annuaire _dir_, construit à partir des nom et
    numéro passés en paramètre. Si il existait déjà un contact du même nom, son
    numéro est remplacé et la fonction retourne une copie de l"ancien numéro.
    Sinon, la fonction retourne NULL.
    ATTENTION : comme indiqué le numéro est une copie et
    a donc un espace mémoire réservé qu'il convient éventuellement de libérer
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    uint32_t h = hash(name);
    uint32_t indice = h % dir->len;
    uint32_t non_present = 1;   /* 'booléen' donnant l'incrémentation de l'occupation */
    char *numero = NULL;

    struct Contact *n_contact = nouveau_contact(name, num, h);
    struct CelluleContact *n_cellule = nouvelle_cellule(NULL, n_contact);

    struct CelluleContact *cellule_courante = dir->T[indice];

    while (get_suivant(cellule_courante) != NULL){
        if (get_hash(get_contact(get_suivant(cellule_courante))) == h){

            numero = str_copy(get_num(get_contact(get_suivant(cellule_courante))));
            supprime_suivant(cellule_courante);

            non_present = 0;
            break;
        }
        cellule_courante = get_suivant(cellule_courante);
    }
    insere_suivant(cellule_courante, n_cellule);
    dir->occ += non_present;
    /* dir_adjust_size(dir);*/     /* à ajouter ici ou à faire manuellement*/

    return numero;
}

/*
    Retourne le numéro associé au nom _name_ dans l"annuaire _dir_. Si aucun contact
    ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t h = hash(name);
    uint32_t i =  h % dir->len;
    const char *num = NULL;

    struct CelluleContact *cellule_courante = dir->T[i];
    cellule_courante = get_suivant(cellule_courante);  /*saut de la sentinelle*/

    while (cellule_courante != NULL){
        if (get_hash(get_contact(cellule_courante)) == h){
            num = get_num(get_contact(cellule_courante));
            break;
        }
        cellule_courante = get_suivant(cellule_courante);
    }
    return num;
}

/*
    Supprime le contact de nom _name_ de l"annuaire _dir_. Si aucun contact ne
    correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    uint32_t i = hash(name) % dir->len;

    struct CelluleContact *cellule_courante = dir->T[i];

    while (get_suivant(cellule_courante) != NULL){
        if (get_nom(get_contact(get_suivant(cellule_courante))) == name){
            supprime_suivant(cellule_courante);
            break;
        }
        cellule_courante = get_suivant(cellule_courante);
    }
}


/*
    Ajuste la taille de la table
*/
void dir_adjust_size(struct dir *dir)
{
    if (dir->occ > 75/100 * dir->len){
        dir_resize(dir, (dir->len)*2 );
    } else if ( (dir->occ < 15/100*(dir->len)) && (dir->len > 20)){
        dir_resize(dir, (dir->len)/2 );
    }
}


/*
    Redimensionne la table de l'annuaire _dir_.
*/
void dir_resize(struct dir *dir, uint32_t size)
{
    struct dir *n_dir = dir_create(size);
    uint32_t i;
    for(i= 0; i < dir->len; i++ ){

        struct CelluleContact *cellule_courante = dir->T[i];
        cellule_courante = cellule_free(cellule_courante); /*sentinelle*/

        while ( cellule_courante != NULL){

            struct Contact *contact = get_contact(cellule_courante);
            dir_insert(n_dir,  get_nom(contact), get_num(contact));

            cellule_courante = cellule_free(cellule_courante);
        }
    }
    free(dir->T);
    dir->len = size;
    dir->T = n_dir->T;
    free(n_dir);
}
