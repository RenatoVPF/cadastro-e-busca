/* 
utils.h vai servir para colocar os prototipos das funcoes que serao usadas no main.c, para deixar o codigo mais organizado e limpo.
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct{
    int id;
    char nome[50];
    int idade;
} Cliente;

void cadastraClientes(Cliente **clientes, int *numClientes, int *capacidade);

int encontrarPosicaoInsercao(Cliente *clientes, int numClientes, int id);

void buscaClientes(Cliente *clientes, int numClientes);

int upBuscaBiClientes(Cliente *clientes, int numClientes, int idBusca);

void listaClientes(Cliente *clientes, int numClientes);

void salvarClientes(Cliente *clientes, int numClientes);

void carregarClientes(Cliente **clientes, int *numClientes, int *capacidade);

void atualizarClientes(Cliente *clientes, int numClientes);

void excluirClientes(Cliente *clientes, int *numClientes, int idExcluir);

void menu();