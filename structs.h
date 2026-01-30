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
    struct Cliente * prox;
}Cliente;

typedef struct Produto{
    char codigo_unico[10];
    char nomeP[100];
    float preco;
    int quantidade;
    struct Produto * prox;
}Produto;

typedef struct ItemNoCarrinho{
    int coigoUnico;
    char nomePC[100];
    float precoPC;
    int quantidade;
    struct ItemNoCarrinho * prox;   
}ItemNoCarrinho;





#endif