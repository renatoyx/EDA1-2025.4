#include <stdio.h>
#include "funcoes.h"

int main(){

    Cliente *clientes = NULL;

    clientes = cadastrarCliente(clientes);

    listarClientes(clientes);

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

    printf("\nDigite o CPF para editar: ");

    clientes = editarCliente(clientes, cpf);

    printf("\n--- LISTA ATUALIZADA ---\n");
    listarClientes(clientes);

    return 0;
}
