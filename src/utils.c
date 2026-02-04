#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

int validarDigitos(char vetorDigito[]) {
    int i, cont = 0;

    for (i = 0; vetorDigito[i] != '\0'; i++) {
        if (isdigit((unsigned char)vetorDigito[i])) cont++;
        else return 0;
    }

    return 1;
}

void copiaString(char *dest, const char *orig) {
    if (*orig == '\0') {
        *dest = '\0';
        return;
    }

    *dest = *orig;
    copiaString(dest + 1, orig + 1);
}

char* transformaMinusculo(char *original){
    char *copia = malloc(strlen(original) + 1);
    if (!copia) return NULL;

    int i;
    for (i = 0; original[i] != '\0'; i++){
        copia[i] = tolower(original[i]);
    }
    copia[i] = '\0';

    return copia;
}