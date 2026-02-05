# 🛒 Sistema de Gerenciamento de Loja (EDA1)

Este projeto consiste em um sistema completo de gerenciamento de loja via linha de comando (CLI), desenvolvido em linguagem **C**. O sistema utiliza **Listas Simplesmente Encadeadas** para gerenciar Clientes, Produtos e Carrinhos de Compras, com foco em alocação dinâmica de memória eficiente e prevenção de vazamentos (*memory leaks*).

---

## 🚀 Funcionalidades

### 👥 Gerenciamento de Clientes (CRUD)
- **Cadastrar.**
- **Listar.**
- **Buscar.**
- **Editar.**
- **Remover.**

### 📦 Gerenciamento de Produtos (CRUD)
- **Cadastrar.**
- **Listar.**
- **Buscar:**
  - Por Código Único.
  - Por Nome.
- **Editar.**
- **Remover.**

### 🛒 Carrinho de Compras (Modo Compra)
- **Login de Cliente.**
- **Adicionar Produtos no Carrinho.**
- - **Remover Produtos no Carrinho.**
- **Lista dentro de Lista:** Cada cliente possui sua própria lista encadeada de itens no carrinho.

---
# 💻 Como Compilar

gcc main.c src/*.c -I include -Wall -Wextra -o prog

# Executar
./prog #LINUX
./prog.exe # WINDOWS

---
## 📂 Estrutura de Arquivos

```text
PROJETO/
│
├── main.c              # Ponto de entrada do programa (Menu Principal)
├── README.md           # Documentação do projeto
│
├── include/            # Arquivos de Cabeçalho (.h)
│   ├── clientes.h      # Protótipos e structs de Cliente/Carrinho
│   ├── produtos.h      # Protótipos e structs de Produto
│   └── utils.h         # Funções auxiliares e validações
│
└── src/                # Implementação do Código Fonte (.c)
    ├── clientes.c      # Lógica do CRUD de Clientes
    ├── produtos.c      # Lógica do CRUD de Produtos
    ├── modoCompra.c    # Lógica do Carrinho e Vendas
    └── utils.c         # Implementação das ferramentas auxiliares
