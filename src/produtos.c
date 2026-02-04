#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "produtos.h"
#include "utils.h"

Produto* buscarProdutoPorCodigo(Produto *lista, char codigo[]){

    while(lista){
        if(strcmp(lista->codigoUnico, codigo) == 0)
            return lista;

        lista = lista->prox;
    }

    return NULL;
}

//////////////////////////////////////////////////

Produto* cadastrarProduto(Produto *lista){

    Produto *novo = malloc(sizeof(Produto));
    if(!novo){
        printf("Erro de memoria!\n");
        return lista;
    }
    

    int codigoJaExiste = 0;
    do{
        printf("Codigo do produto: ");
        scanf(" %49[^\n]", novo->codigoUnico);
        
        if(buscarProdutoPorCodigo(lista, novo->codigoUnico) != NULL){
            printf("Produto com esse código já existe. Tente novamente");
            codigoJaExiste = 1;
        } else{
            codigoJaExiste = 0;
        }
    } while (codigoJaExiste);
    

    char nomeAux[100];
    printf("Nome do produto: ");
    scanf(" %99[^\n]", nomeAux);

    novo->nomeProduto = malloc(strlen(nomeAux)+1);
    copiaString(novo->nomeProduto, nomeAux);

    do{
        printf("Preco: ");
        scanf("%f", &novo->preco);
    }while(novo->preco < 0);

    do{
        printf("Quantidade: ");
        scanf("%d", &novo->quantidade);
    }while(novo->quantidade <= 0);

    novo->prox = lista;

    return novo;
}

//////////////////////////////////////////////////

void exibirBuscaPorCodigo(Produto *lista){

    char codigo[50];
    printf("Codigo: ");
    scanf(" %49s", codigo);

    Produto *p = buscarProdutoPorCodigo(lista, codigo);

    if(!p){
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("\nProduto: %s\nPreco: %.2f\nEstoque: %d\n",
           p->nomeProduto, p->preco, p->quantidade);
}

//////////////////////////////////////////////////

void buscarProdutoPorNome(Produto* lista){

    char nome[100];
    printf("DIgite o nome do produto para buscar: ");
    scanf(" %99[^\n]", nome);

    char *busca = transformaMinusculo(nome);

    int achou = 0;

    while(lista){

        char *temp = transformaMinusculo(lista->nomeProduto);
        printf("///////////////////////////////\n");
        printf("//     RESULTADO DA BUSCA    //");
        printf("///////////////////////////////\n");
        if(temp && strstr(temp, busca)){
            printf("-------------------------------\n");
            printf("|  CODIGO  |  NOME  |  PRECO  |\n");
            printf("|  %s      |  %s    | R$ %.2f |\n",lista->codigoUnico,lista->nomeProduto, lista->preco);
            printf("-------------------------------\n");
            achou = 1;
        }

        free(temp);
        lista = lista->prox;
    }

    if(!achou)
        printf("Nenhum produto encontrado.\n");

    free(busca);
}

//////////////////////////////////////////////////

void listarProdutos(Produto *lista){
    if(!lista){
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto *aux = lista;

    while(aux){
        imprimirProdutos(aux);
        aux = aux->prox;
    }
}

void imprimirProdutos(Produto *lista){

    if(!lista) return;

    
    
    printf("|------------------------|------------------------------------------------------|--------------------------|------------------------|\n");
    printf("| %-22s | %-52s | R$ %-21.2f | %-22d |\n",lista->codigoUnico,lista->nomeProduto, lista->preco,lista->quantidade);
    printf("|------------------------|------------------------------------------------------|--------------------------|------------------------|\n");
}

//////////////////////////////////////////////////

void editarProduto(Produto *lista){

    char codigo[50];
    printf("Codigo do produto: ");
    scanf(" %49s", codigo);

    Produto *p = buscarProdutoPorCodigo(lista, codigo);

    if(!p){
        printf("Produto nao encontrado.\n");
        return;
    }

    int op;
    printf("1-Nome\n2-Preco\n3-Estoque\nEscolha: ");
    scanf("%d",&op);

    switch(op){

    case 1:{
        char aux[100];
        printf("Novo nome: ");
        scanf(" %99[^\n]", aux);

        char *temp = realloc(p->nomeProduto, strlen(aux)+1);
        p->nomeProduto = temp;
        copiaString(p->nomeProduto, aux);
        break;
    }

    case 2:
        printf("Novo preco: ");
        scanf("%f",&p->preco);
        break;

    case 3:
        printf("Novo estoque: ");
        scanf("%d",&p->quantidade);
        break;
    }
}

//////////////////////////////////////////////////

Produto* removerProduto(Produto *lista){

    char codigo[20];
    printf("Codigo para remover: ");
    scanf(" %s", codigo);

    Produto *atual = lista;
    Produto *ant = NULL;

    while(atual && strcmp(atual->codigoUnico, codigo) != 0){
        ant = atual;
        atual = atual->prox;
    }

    if(!atual){
        printf("Produto nao encontrado.\n");
        return lista;
    }

    if(!ant)
        lista = atual->prox;
    else
        ant->prox = atual->prox;

    free(atual->nomeProduto);
    free(atual);

    printf("Produto removido!\n");

    return lista;
}

//////////////////////////////////////////////////

void liberarProdutos(Produto *lista){

    Produto *temp;

    while(lista){

        temp = lista;
        lista = lista->prox;

        free(temp->nomeProduto);
        free(temp);
    }

    printf("Memoria dos produtos liberada.\n");
}
