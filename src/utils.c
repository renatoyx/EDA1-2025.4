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

int validarDataDeNascimento(int dia, int mes, int ano) {
    if (ano < 1850 || ano > 2026) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return 0;

    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        if (dia > (28 + bissexto)) return 0;
    }

    return 1;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}