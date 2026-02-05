#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clientes.h"
#include "utils.h"

Cliente* cadastrarCliente(Cliente *lista){

    Cliente *novo = malloc(sizeof(Cliente));
    if (!novo){
        printf("Erro de memoria!\n");
        return lista;
    }
    novo->carrinho = NULL;

    char controleDeCPF[50];
    int cpfValido = 0;

    do{
        printf("Digite o CPF (11 digitos): ");
        scanf(" %49s", controleDeCPF);
        int tamanhoCpf = strlen(controleDeCPF);
        if(tamanhoCpf != 11 || !validarDigitos(controleDeCPF)){
            printf("CPF invalido!\n");
            cpfValido = 0;
        } else{
            copiaString(novo->cpf, controleDeCPF);
            cpfValido = 1;
        }
    }while(cpfValido == 0);

    char nomeAux[100];
    printf("Nome: ");
    scanf(" %99[^\n]", nomeAux);

    novo->nome = malloc(strlen(nomeAux)+1);
    copiaString(novo->nome, nomeAux);

    char emailAux[100];
    printf("Email: ");
    scanf(" %99[^\n]", emailAux);

    novo->email = malloc(strlen(emailAux)+1);
    copiaString(novo->email, emailAux);

    char controleNumeroDeTelefone[50];
    int telefoneValido = 0;
    do{
        printf("Telefone (Apenas numeros com DDD). Ex: 61998765432: ");
        scanf(" %49s", controleNumeroDeTelefone);
        int tamanhoTelefoneDigitado = strlen(controleNumeroDeTelefone);
        if(tamanhoTelefoneDigitado > 11 || tamanhoTelefoneDigitado < 10 || !validarDigitos(controleNumeroDeTelefone)){
            printf("Telefone invalido!\n");
            telefoneValido = 0;
        } else{
            copiaString(novo->telefone, controleNumeroDeTelefone);
            telefoneValido = 1;
        }
    }while(telefoneValido == 0);
    
    int dia, mes, ano;
    int dataValidaFlag = 0;
    do {
        printf("Nascimento (DD MM AAAA): ");
        if (scanf("%d %d %d", &dia, &mes, &ano) != 3) {
             printf("Entrada invalida. Digite apenas numeros.\n");
             continue;
        }

        if (validarDataDeNascimento(dia, mes, ano)) {
            novo->nascimento.dia = dia;
            novo->nascimento.mes = mes;
            novo->nascimento.ano = ano;
            dataValidaFlag = 1;
        } else {
            printf("Data invalida! Verifique dia, mes e ano.\n");
        }
    } while (!dataValidaFlag);

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
            if(temp) {
                cliente->nome = temp;
                copiaString(cliente->nome, aux);
            } else {
                printf("Erro na memoria.\n");
                free(temp);
            }
            break;
        }

        case 2:{
            char aux[100];
            printf("Novo email: ");
            scanf(" %[^\n]", aux);

            char *temp = realloc(cliente->email, strlen(aux)+1);
            if(temp) {
                cliente->email = temp;
                copiaString(cliente->email, aux);
            } else {
                printf("Erro na memoria.\n");
                free(temp);
            }
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

    liberarCarrinho(atual->carrinho);
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

    liberarCarrinho(temp->carrinho);
    free(temp->nome);
    free(temp->email);
    free(temp);

    }

    printf("Memoria dos clientes liberada.\n");
}
