#include <stdio.h> 
#include "funcoes.h"


int main(){
    Cliente *clientes = NULL; 
    
    clientes = cadastrarCliente(clientes);
    
    listarClientes(clientes);
    
    Cliente *c = buscarCliente(clientes, "12345678912");
    printf("Cliente encontrado: %s", c->nome); 
}