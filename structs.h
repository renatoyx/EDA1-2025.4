#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Data{
    int dia;
    int mes;
    int ano;
}Data;


typedef struct Cliente{
    char cpf[12];
    char *nome;
    char *email;
    char telefone[12];
    Data nascimento;
    struct ItemNoCarrinho *carrinho;
    struct Cliente * prox;
}Cliente;

typedef struct Produto{
    char codigoUnico[50];
    char *nomeProduto;
    float preco;
    int quantidade;
    struct Produto * prox;
}Produto;

typedef struct ItemNoCarrinho{
    char codigoUnicoCarrinho[50];
    char *nomeDoProdutoNoCarrinho;
    float precoProdutoNoCarrinho;
    int quantidade;
    struct ItemNoCarrinho * prox;   
}ItemNoCarrinho;





#endif