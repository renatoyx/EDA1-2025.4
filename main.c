#include <stdio.h>
#include "clientes.h"
#include "produtos.h"

int main(){

    Cliente *clientes = NULL;
    Produto *produtos = NULL;

    int opcao;

    do{

        printf("\n========== SISTEMA ==========\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Cadastrar produto\n");
        printf("4 - listar produtos\n");
        printf("5 - Editar um produto\n");
        printf("6 - Buscar produto por codigo\n");
        printf("7 - Entrar no modo compra\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao){

            case 1:
                clientes = cadastrarCliente(clientes);
                break;

            case 2:
                listarClientes(clientes);
                break;

            case 3:
                produtos = cadastrarProduto(produtos);
                break;

            case 4:
                listarProdutos(produtos);
                break;

            case 5:
                editarProduto(produtos);
                break;

            case 6:
                exibirBuscaPorCodigo(produtos);
                break;
            
            case 7:
                chamarModoCompra(clientes, produtos);
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    }while(opcao != 0);

    liberarClientes(clientes);
    liberarProdutos(produtos);
    
    return 0;
}
