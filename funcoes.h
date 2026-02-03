#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"

//CRUD CLIENTES
Cliente* cadastrarCliente(Cliente *lista);
Cliente* editarCliente(Cliente *lista, char cpf[]);
Cliente* removerCliente(Cliente *lista, char cpf[]);
void liberarClientes(Cliente *lista);
void listarClientes(Cliente *lista);
Cliente* buscarCliente(Cliente *lista, char cpf[]);
void imprimirCliente(Cliente *cliente);

//CRUD PRODUTOS
Produto* cadastrarProduto(Produto *lista);
Produto * buscarProdutoPorCodigo(Produto *lista, char codigo[]);
void exibirBuscaPorCodigo(Produto *lista);
void buscarProdutoPorNome(Produto *lista);
void editarProduto(Produto *lista);
Produto* removerProduto(Produto *lista);
void liberarProdutos(Produto *lista); 


#endif
