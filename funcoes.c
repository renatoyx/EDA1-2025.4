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

//imprimirCliente

void imprimirCliente(Cliente *cliente){
   if(cliente == NULL){
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Dados do Cliente\n"); 
    printf("--------------------------\n");
    printf("Nome: %s\n", cliente->nome); 
    printf("CPF: %s \n",cliente->cpf);
    printf("Data de nascimento: %d/%d/%d\n", cliente->nascimento.dia, cliente->nascimento.mes, cliente->nascimento.ano); 
    printf("Email: %s\n", cliente->email);
}

//EDITAR CLIENTE

Cliente* editarCliente(Cliente *lista, char cpf[]){
    
    Cliente *cliente = buscarCliente(lista, cpf);

    if(cliente == NULL){
        printf("Cliente nao encontrado.\n");
        return lista;
    }

    int opcao;

    do{
        printf("------- CLIENTE -------\n"); 
        imprimirCliente(cliente);

        printf("1 - Nome\n");
        printf("2 - Email\n");
        printf("3 - Telefone\n");
        printf("4 - Data de nascimento\n");
        printf("0 - Sair\n");
        printf("Escolha: \n");
        scanf("%d", &opcao);

        switch(opcao){

            case 1: {
                char nomeAux[100];

                printf("Novo nome: ");
                scanf(" %[^\n]", nomeAux);

                char *temp = realloc(cliente->nome, strlen(nomeAux)+1);

                if(!temp){
                    printf("Erro de memoria.\n");
                    break;
                }

                cliente->nome = temp;
                copiaString(cliente->nome, nomeAux);
                break;
            }

            case 2: {
                char emailAux[100];

                printf("Novo email: ");
                scanf(" %[^\n]", emailAux);

                char *temp2 = realloc(cliente->email, strlen(emailAux)+1);

                if(!temp2){
                    printf("Erro de memoria.\n");
                    break;
                }

                cliente->email = temp2;
                copiaString(cliente->email, emailAux);
                break;
            }

            case 3:
                printf("Novo telefone: ");
                scanf(" %11s", cliente->telefone);
                break;

            case 4:
                printf("Nova data (DD MM AAAA): ");
                scanf("%d %d %d",&cliente->nascimento.dia,&cliente->nascimento.mes,&cliente->nascimento.ano);
                break;
        }

    }while(opcao != 0);

    return lista;
}

;