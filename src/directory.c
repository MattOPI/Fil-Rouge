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
Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    struct dir *annuaire = calloc(1, sizeof(struct dir));
    annuaire->len = len;
    annuaire->occ = 0;
    annuaire->T = calloc(1, len*sizeof(struct  CelluleContact *));

    uint32_t i;
    for (i = 0 ; i < len; i++){
        struct Contact *c_sentinelle = nouveau_contact("sentinelle", "sentinelle", -1);
        struct CelluleContact *sentinelle = nouvelle_cellule(NULL, c_sentinelle);
        annuaire->T[i] = sentinelle;
    }
    return annuaire;
}

/*
  Insère un nouveau contact dans l"annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l"ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    uint32_t h = hash(name);
    uint32_t indice = h % (dir->len);
    struct Contact *n_contact = nouveau_contact(name, num, h);
    const char *res = insere(n_contact, dir->T[indice]);
    /*
    char *res;
    strcpy(res, c_res);*/

    if (res == NULL){
        dir->occ += 1;
        //dir_adjust_size(dir);
        return NULL;

    } else {
      return res;
    }
}

/*
  Retourne le numéro associé au nom _name_ dans l"annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    int indice = hash(name) % dir->len;
    return recherche(name, dir->T[indice]);
}

/*
  Supprime le contact de nom _name_ de l"annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    int indice = hash(name) % dir->len;
    supprime(name, dir->T[indice]);
}

/*
  Libère la mémoire associée à l"annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for(i= 0; i < dir->len; i++ ){

        struct CelluleIterateur *iterateur_courant = nouvel_iterateur(dir->T[i]);
        get_iterateur(iterateur_courant); //sentinelle
        struct CelluleContact *cellule_courante = get_iterateur(iterateur_courant);

        while (cellule_courante != NULL){
            struct CelluleContact *cellule_suppr = cellule_courante;
            cellule_courante = get_iterateur(iterateur_courant);

            cellule_free(cellule_suppr);
        }
    free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l"annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    uint32_t i;
    for(i= 0; i < dir->len; i++ ){
        affiche_cel(dir->T[i]);
        // printf("\n");
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
    struct dir *n_annuaire = dir_create(size);
    uint32_t i;
    for(i= 0; i < dir->len; i++ ){

        struct CelluleIterateur *iterateur_courant = nouvel_iterateur(dir->T[i]);
        struct CelluleContact *cellule_courante = get_iterateur(iterateur_courant);

        while (cellule_courante != NULL){
            const char *nom = get_nom(cellule_courante);
            const char *num = get_num(cellule_courante);
            dir_insert(n_annuaire, nom, num);

            struct CelluleContact *cellule_suppr = cellule_courante;
            cellule_courante = get_iterateur(iterateur_courant);

            cellule_free(cellule_suppr);
        }
    }
    dir_free(dir);
    dir = n_annuaire;
}
