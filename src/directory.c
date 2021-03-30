#include <stdlib.h>
#include <stdio.h>

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
  struct CelluleContact *T[];
};

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    struct dir *annuaire;
    annuaire->len = len;
    annuaire->occ = 0;
    annuaire->T[len] = calloc(len, sizeof(struct  CelluleContact *));

    uint32_t i;
    for (i = 0 ; i < len; i++){
      annuaire->T[i] = NULL;
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
    int indice = hash(name) % dir->len;
    struct Contact *n_contact = nouveau_contact(name, num, hash(name));
    char *res = insere(n_contact, dir->T[indice]);

    if (res == NULL){
      dir->occ += 1;
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
      printf("\n");
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

      while (dir->T[i] != NULL)
      {
        dir_insere(n_annuaire, dir->T[i]->contact->nom, dir->T[i]->contact->num);
      }
    }

}
