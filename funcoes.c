#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

////////////////////////////////////////////////////
// FUNÇÕES AUXILIARES
////////////////////////////////////////////////

int cpfValido(char cpf[]) {
    int i, cont = 0;

    for (i = 0; cpf[i] != '\0'; i++) {
        if (isdigit((unsigned char)cpf[i])) cont++;
        else return 0;
    }

    return cont == 11;
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

//////////////////////////////////////////////////
// CRUD CLIENTES
//////////////////////////////////////////////////

Cliente* cadastrarCliente(Cliente *lista){

    Cliente *novo = malloc(sizeof(Cliente));
    if (!novo){
        printf("Erro de memoria!\n");
        return lista;
    }

    char controleDeCPF[50];
    int valido = 0;
    do{
        printf("Digite o CPF (11 digitos): ");
        scanf(" %s", controleDeCPF);

        if (!cpfValido(controleDeCPF)){
            printf("CPF invalido!\n");
        }else{
            copiaString(novo->cpf, controleDeCPF);
        }

    }while(!cpfValido(controleDeCPF));

    char nomeAux[100];
    printf("Nome: ");
    scanf(" %[^\n]", nomeAux);

    novo->nome = malloc(strlen(nomeAux)+1);
    copiaString(novo->nome, nomeAux);

    char emailAux[100];
    printf("Email: ");
    scanf(" %[^\n]", emailAux);

    novo->email = malloc(strlen(emailAux)+1);
    copiaString(novo->email, emailAux);

    printf("Telefone (DDD+numero): ");
    scanf(" %11s", novo->telefone);

    printf("Nascimento (DD MM AAAA): ");
    scanf("%d %d %d",
        &novo->nascimento.dia,
        &novo->nascimento.mes,
        &novo->nascimento.ano);

    novo->prox = lista;
    return novo;
}

//////////////////////////////////////////////////

void listarClientes(Cliente *lista){

    if(!lista){
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    Cliente *aux = lista;

    while(aux){
        imprimirCliente(aux);
        aux = aux->prox;
    }
}

//////////////////////////////////////////////////

Cliente* buscarCliente(Cliente *lista, char cpf[]){

    while(lista){
        if(strcmp(lista->cpf, cpf) == 0)
            return lista;

        lista = lista->prox;
    }

    return NULL;
}

//////////////////////////////////////////////////

void imprimirCliente(Cliente *cliente){

    if(!cliente) return;

    printf("\n----- CLIENTE -----\n");
    printf("Nome: %s\n", cliente->nome);
    printf("CPF: %s\n", cliente->cpf);
    printf("Nascimento: %02d/%02d/%04d\n",
           cliente->nascimento.dia,
           cliente->nascimento.mes,
           cliente->nascimento.ano);
    printf("Email: %s\n", cliente->email);
    printf("Telefone: %s\n", cliente->telefone);
}

//////////////////////////////////////////////////

Cliente* editarCliente(Cliente *lista, char cpf[]){

    Cliente *cliente = buscarCliente(lista, cpf);

    if(!cliente){
        printf("Cliente nao encontrado.\n");
        return lista;
    }

    int opcao;

    do{

        imprimirCliente(cliente);

        printf("\n1-Nome\n2-Email\n3-Telefone\n4-Nascimento\n0-Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao){

        case 1:{
            char aux[100];
            printf("Novo nome: ");
            scanf(" %[^\n]", aux);

            char *temp = realloc(cliente->nome, strlen(aux)+1);
            cliente->nome = temp;
            copiaString(cliente->nome, aux);
            break;
        }

        case 2:{
            char aux[100];
            printf("Novo email: ");
            scanf(" %[^\n]", aux);

            char *temp = realloc(cliente->email, strlen(aux)+1);
            cliente->email = temp;
            copiaString(cliente->email, aux);
            break;
        }

        case 3:
            printf("Novo telefone: ");
            scanf(" %11s", cliente->telefone);
            break;

        case 4:
            printf("Nova data: ");
            scanf("%d %d %d",
                &cliente->nascimento.dia,
                &cliente->nascimento.mes,
                &cliente->nascimento.ano);
            break;
        }

    }while(opcao != 0);

    return lista;
}

//////////////////////////////////////////////////

Cliente* removerCliente(Cliente *lista, char cpf[]){

    printf("CPF para remover: ");
    scanf(" %11s", cpf);

    Cliente *remover = buscarCliente(lista, cpf);

    if(!remover){
        printf("Cliente nao encontrado.\n");
        return lista;
    }

    Cliente *atual = lista;
    Cliente *anterior = NULL;

    while(atual != remover){
        anterior = atual;
        atual = atual->prox;
    }

    if(!anterior){
        lista = atual->prox;
    }
    else{
        anterior->prox = atual->prox;
    }

    free(atual->nome);
    free(atual->email);
    free(atual);

    printf("Cliente removido com sucesso!\n");

    return lista;
}


//////////////////////////////////////////////////

void liberarClientes(Cliente *lista){

    Cliente *temp;

    while(lista){

        temp = lista;
        lista = lista->prox;

        free(temp->nome);
        free(temp->email);
        free(temp);
    }

    printf("Memoria dos clientes liberada.\n");
}



//////////////////////////////////////////////////
// CRUD PRODUTOS
//////////////////////////////////////////////////


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
    if(!novo) return lista;


    int codigoJaExiste = 0;
    do{
        printf("Codigo do produto: ");
        scanf(" %s", novo->codigoUnico);
        
        if(buscarProdutoPorCodigo(lista, novo->codigoUnico) != NULL){
            printf("Produto com esse código já existe. Tente novamente");
            codigoJaExiste = 1;
        } else{
            codigoJaExiste = 0;
        }
    } while (codigoJaExiste);
    

    char nomeAux[100];
    printf("Nome do produto: ");
    scanf(" %[^\n]", nomeAux);

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

    char codigo[20];
    printf("Codigo: ");
    scanf(" %s", codigo);

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
    printf("Nome do produto: ");
    scanf(" %[^\n]", nome);

    char *busca = transformaMinusculo(nome);

    int achou = 0;

    while(lista){

        char *temp = transformaMinusculo(lista->nomeProduto);

        if(temp && strstr(temp, busca)){
            printf("%s - R$ %.2f\n",
                lista->nomeProduto, lista->preco);
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

void editarProduto(Produto *lista){

    char codigo[20];
    printf("Codigo do produto: ");
    scanf(" %s", codigo);

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
        scanf(" %[^\n]", aux);

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
