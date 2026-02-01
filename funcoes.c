#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include <ctype.h>


//CRUD CLIENTES

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


Cliente* cadastrarCliente(Cliente *lista){
    Cliente *novo = malloc(sizeof(Cliente)); 
    if (novo == NULL){
        printf("Memória não alocada."); 
        return lista; 
    }
    do {
    printf("Digite o CPF: \n No formato: 12345678912\n"); 
    scanf(" %s[^\n]", novo->cpf);

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
        return lista;
    }

    copiaString(novo->nome, nomeAux);

    char emailAux[100]; 
    printf("Digite seu email: \n");
    scanf(" %[^\n]", emailAux); 

    novo->email = malloc(strlen(emailAux) + 1);
    if (novo->email == NULL) {
        printf("Erro de memoria!\n");
        return lista;
    }

    copiaString(novo->email, emailAux);

    printf("Digite seu telefone: \n No formato: ddd+numero \n exemplo: 61987654321 \n");
    scanf("%s", novo->telefone); 

    printf("Data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d",&novo->nascimento.dia,&novo->nascimento.mes,&novo->nascimento.ano);

    printf("%s, %s, %s",novo->cpf, novo->email, novo->nome);
    novo->prox = lista;
    return novo;
    
}

//CRUD PRODUTOS

//CADASTRO
Produto* cadastrarProduto(Produto *lista) {
    Produto *novo = malloc(sizeof(Produto));

    if (novo == NULL){
        printf("Memória não alocada.");
        return lista;
    }

    printf("Digite o codigo do produto: ");
    scanf("%s", novo->codigoUnico);
    printf("\n");

    
    char nomeProdutoAux[100]; 
    printf("Digite o nome do produto: \n");
    scanf(" %[^\n]", nomeProdutoAux); 

    novo->nomeProduto = malloc(strlen(nomeProdutoAux) + 1);
    if (novo->nomeProduto == NULL) {
        printf("Erro de memoria!\n");
        return lista;
    }

    copiaString(novo->nomeProduto, nomeProdutoAux);


    do{
        printf("Digite o preco do produto: ");
        scanf("%f", &novo->preco);
        if (novo->preco<0){
            printf("preco não pode ser menor que 0, tente novamente:\n");
        }
    } while (novo->preco < 0);
    printf("\n");

    do{
        printf("Digite a quantidade do produto no estoque: ");
        scanf("%d", &novo->quantidade);
        if(novo->quantidade <= 0){
            printf("qunatidade não pode ser menor ou igual a 0, tente novamente:\n");
        }
    } while (novo->quantidade <= 0);
    
    printf("\n");

    novo->prox = lista;

    return novo;

}

//TRANSFORMA STRING EM MINÚSCULO PARA AJUDAR NA BUSCA
char* transformaMinusculo(char *original){
    char *copia = (char*) malloc(strlen(original) + 1);

    if (copia == NULL) return NULL;

    int i;
    for (i = 0; original[i] != '\0'; i++){
        copia[i] = tolower(original[i]);
    }
    copia[i] = '\0';

    return copia;
}

//BUSCAR
Produto* buscarProdutoPorCodigo(Produto *lista, char codigo[]){
    Produto *atual = lista;
    while (atual != NULL){
        if (strcmp(atual->codigoUnico, codigo) == 0){
            return atual;
        }
        atual = atual -> prox;
    }
    return NULL;
}

void exibirBuscaPorCodigo(Produto *lista){
        char codigoBusca[10];

        printf("Digite o codigo: ");
        scanf(" %s", codigoBusca);
        Produto *encontrou = buscarProdutoPorCodigo(lista, codigoBusca);

        if (encontrou != NULL){
            printf("\nProduto Encontrado");
            printf("\nCodigo: %s", encontrou->codigoUnico);
            printf("\nNome: %s", encontrou->nomeProduto);
            printf("\nPreco: %.2f", encontrou->preco);
            printf("\nEstoque: %d\n", encontrou->quantidade);
        } else{
            printf("Produto nao encontrado.");
        }
}

void buscarProdutoPorNome(Produto* lista){
    char nomeTemp[100];

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nomeTemp);

    char *buscaNome = (char*) malloc(strlen(nomeTemp) + 1);

    if (buscaNome == NULL){
        printf("Erro de memoria!\n");
        return;
    }
    copiaString(buscaNome, nomeTemp);

    char *buscaNomeMinusculo = transformaMinusculo(buscaNome);

    Produto* atual = lista;
    int encontrou = 0;

    printf("Buscando por %s \n", buscaNome);
    printf("Resultados: \n");

    while (atual != NULL){
        char *nomeProdutoMinusculo = transformaMinusculo(atual->nomeProduto);

        if(nomeProdutoMinusculo != NULL && strstr(nomeProdutoMinusculo, buscaNomeMinusculo) != NULL){

            printf("Produto: %s \n Preco: R$ %2.f \n", atual->nomeProduto, atual->preco);
            encontrou = 1;
        }

        if (nomeProdutoMinusculo != NULL){
        free(nomeProdutoMinusculo);
        }

        atual = atual->prox;
    }

    if(!encontrou){
        printf("Nenhum produto '%s' encontrado.\n", buscaNome);
    }

    free(buscaNomeMinusculo);
    
}