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
    char telefone[11];
    Data nascimento;
    struct ItemNoCarrinho *carrinho;
    struct Cliente * prox;
}Cliente;

typedef struct Produto{
    char codigoUnico[10];
    char *nomeProduto;
    float preco;
    int quantidade;
    struct Produto * prox;
}Produto;

typedef struct ItemNoCarrinho{
    int codigoUnicoCarrinho;
    char nomePC[100];
    float precoPC;
    int quantidade;
    struct ItemNoCarrinho * prox;   
}ItemNoCarrinho;





#endif