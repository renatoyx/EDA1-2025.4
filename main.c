#include <stdio.h>
#include "include/clientes.h"

int main(){

    Cliente *clientes = NULL;
    Produto *produtos = NULL;

    int opcao;

    do{

        printf("\n========== SISTEMA ==========\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");

        printf("3 - Cadastrar produto\n");
        printf("4 - Buscar produto por codigo\n");

        printf("5 - Entrar no modo compra\n");

        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

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
                exibirBuscaPorCodigo(produtos);
                break;

            case 5:
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
