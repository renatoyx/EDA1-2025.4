#include <stdio.h>
#include <stdlib.h>
#include "clientes.h" 
#include "produtos.h" 
#include "utils.h"  

int main(){

    Cliente *clientes = NULL;
    Produto *produtos = NULL;

    int opcao;
    char cpfAux[15]; 

    do{
        printf("\n------- SISTEMA ----------n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Buscar cliente por CPF\n");
        printf("4 - Editar cliente\n");
        printf("5 - Remover cliente\n");
        printf("6 - Cadastrar produto\n");
        printf("7 - Listar produtos\n");
        printf("8 - Buscar produto por codigo\n");
        printf("9 - Editar produto\n");
        printf("10 - Remover produto\n");
        printf("11 - Entrar no modo compra\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            //  GERENCIAR CLIENTES
            case 1:
                clientes = cadastrarCliente(clientes);
                break;

            case 2:
                listarClientes(clientes);
                break;

            case 3:
                printf("Digite o CPF para buscar: ");
                scanf(" %14s", cpfAux);
                
                Cliente *buscado = buscarCliente(clientes, cpfAux);
                if(buscado){
                    imprimirCliente(buscado);
                } else {
                    printf("Cliente nao encontrado.\n");
                }
                break;

            case 4:
                printf("Digite o CPF do cliente a ser editado: ");
                scanf(" %14s", cpfAux);
                clientes = editarCliente(clientes, cpfAux);
                break;

            case 5:
                clientes = removerCliente(clientes, cpfAux);
                break;

            case 6:
                produtos = cadastrarProduto(produtos);
                break;

            case 7:
                listarProdutos(produtos);
                break;

            case 8:
                exibirBuscaPorCodigo(produtos);
                break;

            case 9:
                editarProduto(produtos);
                break;

            case 10:
                produtos = removerProduto(produtos);
                break;
            
            //  MODO COMPRA 
            case 11:
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