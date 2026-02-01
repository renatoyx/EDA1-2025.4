#include <stdio.h> 
#include "funcoes.h"


int main(){
    Cliente *clientes = NULL;
    Produto *produtos = NULL; 
    
    produtos = cadastrarProduto(produtos);
    produtos = cadastrarProduto(produtos);
    produtos = cadastrarProduto(produtos);
    exibirBuscaPorCodigo(produtos);
    exibirBuscaPorCodigo(produtos);
    exibirBuscaPorCodigo(produtos);
    buscarProdutoPorNome(produtos);

}