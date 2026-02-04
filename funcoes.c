#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

////////////////////////////////////////////////////
// FUNÇÕES AUXILIARES
////////////////////////////////////////////////

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
    int cpfValido = 0;
    do{
        printf("Digite o CPF (11 digitos): ");
        scanf(" %s", controleDeCPF);
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
    scanf(" %[^\n]", nomeAux);

    novo->nome = malloc(strlen(nomeAux)+1);
    copiaString(novo->nome, nomeAux);

    char emailAux[100];
    printf("Email: ");
    scanf(" %[^\n]", emailAux);

    novo->email = malloc(strlen(emailAux)+1);
    copiaString(novo->email, emailAux);

    char controleNumeroDeTelefone[50];
    int telefoneValido = 0;
    do{
        printf("Telefone (Apenas numeros com DDD). Ex: 61998765432: ");
        scanf(" %s", controleNumeroDeTelefone);
        int tamanhoTelefoneDigitado = strlen(controleNumeroDeTelefone);
        if(tamanhoTelefoneDigitado > 11 || tamanhoTelefoneDigitado < 10 || !validarDigitos(controleNumeroDeTelefone)){
            printf("Telefone invalido!\n");
            telefoneValido = 0;
        } else{
            copiaString(novo->telefone, controleNumeroDeTelefone);
            telefoneValido = 1;
        }
    }while(telefoneValido == 0);
    
    

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
    if(!novo){
        printf("Erro de memoria!\n");
        return lista;
    }

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
    printf("DIgite o nome do produto para buscar: ");
    scanf(" %[^\n]", nome);

    char *busca = transformaMinusculo(nome);

    int achou = 0;

    while(lista){

        char *temp = transformaMinusculo(lista->nomeProduto);
        //Revisar para adaptar a tela
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

//////////////////////////////////////////////////
// MODO COMPRA
//////////////////////////////////////////////////

void chamarModoCompra(Cliente *clientes, Produto *produtos){

    char cpf[12];

    printf("------- MODO COMPRA ------- \n");
    printf("Digite o CPF do cliente: \n");
    scanf(" %11s", cpf);

    Cliente *cliente = buscarCliente(clientes, cpf);

    if(!cliente){
        printf("Cliente nao encontrado. Cadastre o cliente antes de comprar.\n");
        return;
    }

    printf("Cliente validado com sucesso!\n");
    imprimirCliente(cliente);

    printf("Entrando no modo compra...\n");

    modoCompra(cliente, produtos);
}

void adicionarItemNoCarrinho(Cliente *listaCliente,Produto *listaProduto){
    buscarProdutoPorNome(listaProduto);
    char codigoDigitado[50];
    Produto *produtoSelecionado = NULL;
    int tentarNovamente = 1;
    
    while (tentarNovamente == 1 && produtoSelecionado == NULL){

        printf("Digite o codigo do produto que quer adicionar ao carrinho: ");
        scanf(" %[^\n]", &codigoDigitado);

        produtoSelecionado = buscarProdutoPorCodigo(listaProduto, codigoDigitado);
        if (produtoSelecionado == NULL){
            printf("Codigo errado ou produto nao encontrado.\n");
            printf("tentar novamente?\n");
            printf("1. Sim\n");
            printf("2. Nao (voltar pra tela de inicio)\n");
            printf("Selecione uma das opcoes acima: ");
            scanf("%d", &tentarNovamente);

            if(tentarNovamente < 1 || tentarNovamente > 2){
                printf("Opcao invalida. Tente novamente.\n");
                tentarNovamente = 0;
            }
        }
    }
    if(produtoSelecionado == NULL) return;

    int quantidadeSelecionada;
    do{
        printf("Quantidade em estoque: %d", produtoSelecionado->quantidade);
        printf("Quantas unidade de '%s'?", produtoSelecionado->nomeProduto);
        scanf("%d", &quantidadeSelecionada);

        if (quantidadeSelecionada > produtoSelecionado->quantidade || quantidadeSelecionada <= 0){
            printf("Estoque insuficiente ou quantidade digitada errada. Tente novamente\n\n");
        }
    }while(quantidadeSelecionada > produtoSelecionado->quantidade || quantidadeSelecionada <= 0);

    ItemNoCarrinho *itemAdicionado = malloc(sizeof(ItemNoCarrinho));
    if(!itemAdicionado){
        printf("Erro de memoria!\n");
        return;
    }

    copiaString(itemAdicionado->codigoUnicoCarrinho, produtoSelecionado->codigoUnico);

    itemAdicionado->nomeDoProdutoNoCarrinho = malloc(strlen(produtoSelecionado->nomeProduto) + 1);
    copiaString(itemAdicionado->nomeDoProdutoNoCarrinho, produtoSelecionado->nomeProduto);

    itemAdicionado->precoProdutoNoCarrinho = produtoSelecionado->preco;

    itemAdicionado->quantidade = quantidadeSelecionada;

    itemAdicionado->prox = listaCliente->carrinho;
    listaCliente->carrinho = itemAdicionado;

    produtoSelecionado->quantidade = produtoSelecionado->quantidade - quantidadeSelecionada;

}



void modoCompra(Cliente *cliente, Produto *produtos){
    int opcao = 0;
    printf("MODO COMPRA\n \n");
    printf("1. Adicionar item ao carrinho\n");
    printf("2. Listar itens no carrinho\n");
    printf("3. Excluir item no carrinho\n\n");
    scanf("Selecione uma opcao: %d", &opcao);
    do{
        if (opcao < 0 || opcao > 3){
            printf("opcao inválida");
        } else{
            switch (opcao){
                case 1:
                adicionarItemNoCarrinho(cliente,produtos);
                case 2:

                case 3:

            }
        }
    }while (opcao < 0 || opcao > 3);
}
