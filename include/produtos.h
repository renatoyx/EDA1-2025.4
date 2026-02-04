#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct Produto{
    char codigoUnico[50];
    char *nomeProduto;
    float preco;
    int quantidade;
    struct Produto * prox;
}Produto;

//CRUD PRODUTOS
Produto* cadastrarProduto(Produto *lista);
Produto * buscarProdutoPorCodigo(Produto *lista, char codigo[]);
void exibirBuscaPorCodigo(Produto *lista);
void buscarProdutoPorNome(Produto *lista);
void editarProduto(Produto *lista);
Produto* removerProduto(Produto *lista);
void liberarProdutos(Produto *lista); 

#endif