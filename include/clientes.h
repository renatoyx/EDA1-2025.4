#ifndef CLIENTES_H
#define CLIENTES_H

#include "utils.h"
#include "produtos.h"


typedef struct Cliente{
    char cpf[12];
    char *nome;
    char *email;
    char telefone[12];
    Data nascimento;
    struct ItemNoCarrinho *carrinho;
    struct Cliente * prox;
}Cliente;

typedef struct ItemNoCarrinho{
    char codigoUnicoCarrinho[50];
    char *nomeDoProdutoNoCarrinho;
    float precoProdutoNoCarrinho;
    int quantidade;
    struct ItemNoCarrinho * prox;   
}ItemNoCarrinho;

//CRUD CLIENTES
Cliente* cadastrarCliente(Cliente *lista);
Cliente* editarCliente(Cliente *lista, char cpf[]);
Cliente* removerCliente(Cliente *lista, char cpf[]);
void liberarClientes(Cliente *lista);
void listarClientes(Cliente *lista);
Cliente* buscarCliente(Cliente *lista, char cpf[]);
void imprimirCliente(Cliente *cliente);


// MODO COMPRA
void chamarModoCompra(Cliente *clientes, Produto *produtos);
void modoCompra(Cliente *cliente, Produto *produtos);
void adicionarItemNoCarrinho(Cliente *cliente, Produto *produtos);
void removerItemDoCarrinho(Cliente *cliente);
void listarCarrinho(Cliente *cliente);
void liberarCarrinho(ItemNoCarrinho *carrinho);



#endif