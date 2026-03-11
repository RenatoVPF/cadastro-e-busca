# Sistema de Cadastro de Clientes em C

Projeto desenvolvido para estudo de programação em C.

O sistema implementa um CRUD completo de clientes utilizando:

- vetor dinâmico
- alocação de memória com `malloc` e `realloc`
- busca binária
- inserção ordenada
- persistência em arquivo `.txt`
- separação modular do código

---

# Funcionalidades

O sistema permite:

- cadastrar clientes
- buscar cliente por ID
- listar todos os clientes
- atualizar dados de cliente
- excluir cliente

Os dados são armazenados em arquivo (`dadosClientes.txt`).

---

# Estrutura do Projeto

main.c
dadosClientes.txt

Bibliotecas/
utils.h
clientes_service.h

Principais/
utils.c
clientes_service.c

---

# Tecnologias utilizadas

- Linguagem C
- Manipulação de arquivos
- Estruturas (`struct`)
- Ponteiros
- Alocação dinâmica de memória

---

# Como compilar

Use o gcc: gcc -Ibibliotecas main.c Principal/utils.c Principal/clientes_service.c -o sistema


---

# Como executar

./sistema


---

# Objetivos do projeto

Este projeto foi desenvolvido para praticar:

- manipulação de memória em C
- organização modular de código
- implementação de algoritmos como busca binária
- persistência de dados em arquivos

---

# Autor

Renato Veloso Pires Filho