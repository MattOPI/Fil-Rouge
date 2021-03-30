#include <stdlib.h>
#include <stdint.h>

uint32_t hash(const char *str)
{
    int hash = 5381;
    int indice = 0;

    while(str[indice] != '\0'){
        hash += str[indice];
        indice ++;
    }
    return hash;
}
