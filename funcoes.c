#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include <ctype.h>



//VERIFICA CPF
int cpfValido(char cpf[]) {
    int i, cont = 0;

    for (i = 0; cpf[i] != '\0'; i++) {
        if (isdigit(cpf[i])) {
            cont++;
        } else {
            return 0;
        }
    }

    return cont == 11;
}
//COPIA STRING AUX PARA DEFINITIVA COM ALOCAÇÃO DE MEMÓRIA
void copiaString(char *dest, const char *orig) {
    if (*orig == '\0') {
        *dest = '\0';
        return;
    }

    *dest = *orig;
    copiaString(dest + 1, orig + 1);
}

//CRUD CLIENTES

//CADASTRO CLIENTES
Cliente* cadastrarCliente(Cliente *lista){
    Cliente *novo = malloc(sizeof(Cliente)); 
    if (novo == NULL){
        printf("Memória não alocada."); 
        return lista; 
    }
    do {
    printf("Digite o CPF: \n No formato: 12345678912\n"); 
    scanf(" %11s", novo->cpf);

    if (!cpfValido(novo->cpf)) {
        printf("CPF invalido! Digite novamente.\n");
    }
    } while (!cpfValido(novo->cpf));
    
    char nomeAux[100]; 
    printf("Digite seu nome: \n");
    scanf(" %[^\n]", nomeAux); 

    novo->nome = malloc(strlen(nomeAux) + 1);
    if (novo->nome == NULL) {
        printf("Erro de memoria!\n");
        free(novo);
        return lista;
    }

    copiaString(novo->nome, nomeAux);

    char emailAux[100]; 
    printf("Digite seu email: \n");
    scanf(" %[^\n]", emailAux); 

    novo->email = malloc(strlen(emailAux) + 1);
    if (novo->email == NULL) {
        printf("Erro de memoria!\n");            
        free(novo);
        return lista;
    }

    copiaString(novo->email, emailAux);

    printf("Digite seu telefone: \nNo formato: ddd+numero \nexemplo: 61987654321 \n");
    scanf("%s", novo->telefone); 

    printf("Data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d",&novo->nascimento.dia,&novo->nascimento.mes,&novo->nascimento.ano);

    printf("%s, %s, %s \n",novo->cpf, novo->email, novo->nome);
    novo->prox = lista;
    return novo;
    
}

//LISTAR CLIENTES

void listarClientes(Cliente *lista){
    Cliente *aux = lista;

    while(aux != NULL){
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
}

//BUSCAR CLEINTE POR CPF

Cliente* buscarCliente(Cliente *lista, char cpf[]){
    while(lista){
        if(strcmp(lista->cpf, cpf) == 0)
            return lista;

        lista = lista->prox;
    }
    return NULL;
}

;