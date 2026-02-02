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



#endif
