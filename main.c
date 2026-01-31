#include <stdio.h> 
#include "funcoes.h"


int main(){
    Cliente *clientes = NULL;
    Produto *produtos = NULL; 
    
    cadastrarCliente(clientes);
    printf("\n");
    cadastrarProduto(produtos);

}