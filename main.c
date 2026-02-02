#include <stdio.h>
#include "funcoes.h"

int main(){

    Cliente *clientes = NULL;
    Produto *produtos = NULL;

    printf("\n========== TESTE CLIENTES ==========\n");

    // CADASTRAR CLIENTES
    clientes = cadastrarCliente(clientes);
    clientes = cadastrarCliente(clientes);

    printf("\n--- LISTANDO CLIENTES ---\n");
    listarClientes(clientes);

    // BUSCAR CLIENTE
    char cpf[12];
    printf("\nDigite um CPF para buscar: ");
    scanf(" %11s", cpf);

    Cliente *c = buscarCliente(clientes, cpf);

    if(c){
        printf("\nCliente encontrado:\n");
        imprimirCliente(c);
    }
    else{
        printf("Cliente nao encontrado.\n");
    }

    // EDITAR CLIENTE
    printf("\nDigite um CPF para editar: ");
    scanf(" %11s", cpf);

    clientes = editarCliente(clientes, cpf);

    printf("\n--- CLIENTES APOS EDICAO ---\n");
    listarClientes(clientes);



    printf("\n\n========== TESTE PRODUTOS ==========\n");

    // CADASTRAR PRODUTOS
    produtos = cadastrarProduto(produtos);
    produtos = cadastrarProduto(produtos);

    // BUSCAR PRODUTO
    exibirBuscaPorCodigo(produtos);

    // BUSCAR POR NOME
    buscarProdutoPorNome(produtos);

    // EDITAR PRODUTO
    editarProduto(produtos);

    // REMOVER PRODUTO
    produtos = removerProduto(produtos);

    printf("\nTeste finalizado.\n");

    return 0;
}
