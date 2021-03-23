#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>
/*
  Structure de données représentant un annuaire.
  Son contenu est détaillé dans directory.c.
*/
struct dir
{
  /* taille de l"annuaire */
  uint32_t len;

  /* tableau de pointeur représentant l"annuaire */
  struct CelluleContact **T[];
};

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
  struct dir *annuaire;
  (*annuaire).len = len;
  (*annuaire).T[len] = malloc(sizeof(struct CelluleContact *) * len);

  for (int i = 0; i < len; i++)
  {
    struct CelluleContact *balise_fin = nouvelle_cellule("zzzzzzzz", NULL);
    // il y a t"il une balise de fin mieux pour l"ordre lexicographique?
    struct CelluleContact *balise_debut = nouvelle_cellule(" ", balise_fin);
    // il y a t"il une balise de debut mieux pour l"ordre lexicographique?
    (*annuaire).T[i] = balise_debut;
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
  int indice = hash(*name) % (*dir).len;
  struct Contact *n_contact = nouveau_contact(name, num);

  return insere(nouveau_contact, (*dir).T[indice]); // type imcomplet?
}

/*
  Retourne le numéro associé au nom _name_ dans l"annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
  int indice = hash(*name) % (*dir).len;    // comment j"accede à la longueur?
  return recherche(name, (*dir).T[indice]); // type imcomplet?
}

/*
  Supprime le contact de nom _name_ de l"annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
  int indice = hash(*name) % (*dir).len; // comment j"accede à la longueur?
  supprime(name, (*dir).T[indice]);      // type imcomplet?
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
  for (int i = 0; i < (*dir).len; i++)
  {                       // comment j"accede à la longueur?
    affiche((*dir).T[i]); // type imcomplet?
    printf("\n");
  }
}

void main()
{
  return EXIT_SUCCESS;
}