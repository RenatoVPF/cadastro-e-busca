#pragma once
#include "utils.h"


int buscarIdsClientes(Cliente *clientes, int numClientes, int idBusca);

int encontrarPosicaoInsercao(Cliente *clientes, int numClientes, int idNovo);

void listarClientesService(Cliente *clientes, int numClientes);

int buscarClienteService(Cliente *clientes, int numClientes, int idBusca);

int cadastrarClienteService(Cliente **clientes, int *numClientes, int *capacidade, Cliente novoCliente);

int atualizarClienteService(Cliente *clientes, int numClientes, int idAtualizar, char novoNome[], int novaIdade);

int excluirClienteService(Cliente *clientes, int *numClientes, int idExcluir);