#include "utils.h"

void cadastraClientes(Cliente *clientes, int *numClientes) {
    
    if (*numClientes >= 10) {
        printf("Limite de clientes atingido (10).\n");
        return;
    }
    printf("Digite o id do cliente: ");
    scanf("%d", &clientes[*numClientes].id);
    printf("Digite o nome do cliente: ");
    scanf(" %s", clientes[*numClientes].nome); // Lê o nome
    printf("Digite a idade do cliente: ");
    scanf("%d", &clientes[*numClientes].idade);
    (*numClientes)++; // Incrementa o número de clientes cadastrados
}

void buscaClientes(Cliente *clientes, int numClientes) {
    
    int numBusca;

    printf("Digite o id do cliente que dejeja buscar:\n");
    scanf("%d", &numBusca);

    for (int i = 0; i < numClientes; i++){      //sistema simples de busca, onde vais comparar todos os ids cadastrados com o id que o usuario deseja buscar
        if(clientes[i].id == numBusca){         // Se o cliente for encontrado, exibe as informações do cliente e retorna da função
            printf("ID: %d\n Nome: %s\n Idade: %d\n", clientes[i].id, clientes[i].nome, clientes[i].idade);
            return; // Cliente encontrado, retorna da função
        }
    }
    printf("Cliente não encontrado.\n");

}

void listaClientes(Cliente *clientes, int numClientes) {
    
    for(int i = 0; i < numClientes; i++) {
        printf("ID: %d\n Nome: %s\n Idade: %d\n", clientes[i].id, clientes[i].nome, clientes[i].idade);
    }
}

void menu() {
    
    printf("######## MENU ########\n");
    printf("1- cadastrar cliente\n");
    printf("2- buscar cliente\n");
    printf("3- lista com os clientes\n");
    printf("4- sair\n");
    printf("Digite a opcao desejada:\n ");

}