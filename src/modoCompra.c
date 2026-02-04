#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clientes.h"
#include "produtos.h"
#include "utils.h"

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

//////////////////////////////////////////////////

void adicionarItemNoCarrinho(Cliente *cliente, Produto *listaProduto){
    buscarProdutoPorNome(listaProduto);
    char codigoDigitado[50];
    Produto *produtoSelecionado = NULL;
    int tentarNovamente = 1;
    
    while (tentarNovamente == 1 && produtoSelecionado == NULL){

        printf("Digite o codigo do produto que quer adicionar ao carrinho: ");
        scanf(" %49[^\n]", codigoDigitado);

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

    itemAdicionado->prox = cliente->carrinho;
    cliente->carrinho= itemAdicionado;

    produtoSelecionado->quantidade = produtoSelecionado->quantidade - quantidadeSelecionada;

}

//////////////////////////////////////////////////

void liberarCarrinho(ItemNoCarrinho *carrinho){

    ItemNoCarrinho *temp;

    while(carrinho){

        temp = carrinho;
        carrinho = carrinho->prox;

        free(temp->nomeDoProdutoNoCarrinho);
        free(temp);
    }
}

//////////////////////////////////////////////////

void removerItemDoCarrinho(Cliente *cliente, Produto *produto){

    if(!cliente->carrinho){
        printf("Carrinho vazio.\n");
        return;
    }

    char codigo[50];
    printf("Digite o codigo do produto para remover do carrinho: ");
    scanf(" %s", codigo);

    ItemNoCarrinho *atual = cliente->carrinho;
    ItemNoCarrinho *anterior = NULL;

    while(atual && strcmp(atual->codigoUnicoCarrinho, codigo) != 0){
        anterior = atual;
        atual = atual->prox;
    }

    if(!atual){
        printf("Produto nao encontrado no carrinho.\n");
        return;
    }

    if (produto) {
        Produto *prodOriginal = buscarProdutoPorCodigo(produto, codigo);
        if (prodOriginal) {
            prodOriginal->quantidade = prodOriginal->quantidade + atual->quantidade;
            printf("Estoque devolvido (+%d).\n", atual->quantidade);
        }
    }

    // reconectar lista
    if(!anterior){
        cliente->carrinho = atual->prox;
    }
    else{
        anterior->prox = atual->prox;
    }

    free(atual->nomeDoProdutoNoCarrinho);
    free(atual);

    printf("Item removido do carrinho com sucesso!\n");
}

//////////////////////////////////////////////////

void listarCarrinho(Cliente *cliente){

    if(!cliente->carrinho){
        printf("\nCarrinho vazio.\n");
        return;
    }

    ItemNoCarrinho *aux = cliente->carrinho;
    float total = 0;

    printf("CARRINHO \n");

    while(aux){

        float subtotal = aux->precoProdutoNoCarrinho * aux->quantidade;

        printf("Produto: %s\n", aux->nomeDoProdutoNoCarrinho);
        printf("Preco: %.2f\n", aux->precoProdutoNoCarrinho);
        printf("Quantidade: %d\n", aux->quantidade);
        printf("Subtotal: %.2f\n", subtotal);
        printf("----------------------\n");

        total += subtotal;
        aux = aux->prox;
    }

    printf("TOTAL DA COMPRA: %.2f\n", total);
}

//////////////////////////////////////////////////

void modoCompra(Cliente *cliente, Produto *produtos){
    int opcao = 0;
    
    do{
        printf("MODO COMPRA\n \n");
        printf("1. Adicionar item ao carrinho\n");
        printf("2. Listar itens no carrinho\n");
        printf("3. Excluir item no carrinho\n\n");
        printf("0. Sair\n");
        printf("Selecione uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao){
            case 1: 
                adicionarItemNoCarrinho(cliente, produtos); 
                break;
            case 2: 
                listarCarrinho(cliente); 
                break;
            case 3: 
                removerItemDoCarrinho(cliente, produtos); 
                break;
            case 0: 
                printf("Saindo do modo compra...\n"); 
                break;
            default: 
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    
}


