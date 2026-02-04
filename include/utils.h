#ifndef ULTIS_H
#define UTILS_H

typedef struct Data{
    int dia;
    int mes;
    int ano;
}Data;

void copiaString(char *dest, const char *orig);
int validarDigitos(char vetorDigito[]);
char* transformaMinusculo(char *original);

#endif