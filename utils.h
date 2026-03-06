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

void cadastraClientes(Cliente *clientes, int *numClientes);

void buscaClientes(Cliente *clientes, int numClientes);

void listaClientes(Cliente *clientes, int numClientes);

void salvarClientes(Cliente *clientes, int numClientes);

void carregarClientes(Cliente *clientes, int *numClientes);

void menu();