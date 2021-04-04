# Compiler et Tester
    -> Pour compiler le code, il faut se placer dans la racine (Fil-rouge) et lancer la commande 'make'

    -> Pour lancer les tests, il faut exécuter les fichiers qui seront générés dans le répértoire 'tests'.
    Depuis la racine : './tests/directory-01-test'
    Ils peuvent aussi etre lancé avec Valgrind pour plus de précision.
    Depuis la racine : 'valgrind ./tests/directory-01-test'

    -> Lancer la commande 'make clean' pour supprimer tout les fichier .o , .so et les exécutales.


# Notes sur le code

## Dans directory.c
    -> J'ai fait le choix de rajouter des 'Gets' dans le fichier directory,
    ce qui peut etre utile pour tester certaines parties précises de l'annuaire dans les tests.
    Cela rend également l'objet 'Dir' plus accéssible depuis l'extérieur.

## Fonction Init de directory.c
    -> Je choisi de placer une sentinelle au debut de chaque liste chainée pour facilité l'initialisation des pointeurs qui serviront à l'itération.
    Et pour s'assurer de l'initialisation de chaque pointeur

## Fonction Insert de directory.c
    -> J'ai fait le choix de supprimer le suivant pour ensuite faire une insertion lorsque'il faut remplacer un contact.
    Plutot que de directement changer le suivant.
    Ce changement demande quelques opérations supplémentaire,
    mais je trouve que cela rend le code plus lisible.

    -> J'ai laissé la partie qui ajuste la taille de l'annuaire à chaque insertion en commentaire,
    en décommentant? cette partie l'ajustement de taille se fera si necéssaire.
    Sinon il faut le faire manuellement (comme dans le test 9).

## Fonction Cellule_free de contact.c
    -> J'ai choisi de renvoyer le suivant de la cellule libéré,
    parceque cela permet de simplifier les réaffectations suite à la libération d'une cellule
    et donc de pouvoir itérer plus simplement.



Merci d'avance et bon courage pour la relecture et la correction/ notation de ce code.