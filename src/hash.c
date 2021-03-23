#include <stdlib.h>
#include <stdint.h>

uint32_t hash(const char *str)
{
    int hash = 5381;
    int *indice = 0;
    char c = (*str)[indice];

    while(c != '\0'){
        hash += c; // a modifier, pour avoir ascci(c), commande ?
        indice ++;
        c = (*str)[indice];
    }
    return hash;
}
