#include "utils.h"

void cadastraClientes(Cliente **clientes, int *numClientes, int *capacidade) {
    int idUnico;
    
    if (*numClientes >= *capacidade) {
      *capacidade = (*capacidade) * 2;
      Cliente *temp = realloc(*clientes, (*capacidade) * sizeof(Cliente));
      if (temp == NULL) {
        printf("Erro: falha ao realocar memoria.\n");
        return;
      }
      *clientes = temp;
    }
   
    printf("Digite o id do cliente: ");
    scanf("%d", &idUnico);

    for(int i = 0; i < *numClientes; i++){
        if((*clientes)[i].id == idUnico){
            printf("ERRO: ID ja cadastrado. tente novamente.\n");
            return;
        }
    }

    (*clientes)[*numClientes].id = idUnico; // Isso corrige o problema de o id do clinte ser 0. 

    printf("Digite o nome do cliente: ");
    getchar();
    fgets((*clientes)[*numClientes].nome, 50, stdin);
    (*clientes)[*numClientes].nome[strcspn((*clientes)[*numClientes].nome, "\n")] = 0;

    printf("Digite a idade do cliente: ");
    scanf("%d", &(*clientes)[*numClientes].idade);

    (*numClientes)++; // Incrementa o número de clientes cadastrados
    salvarClientes(clientes, *numClientes); // Chama a função para salvar os clientes no arquivo toda vez que um novo cliente for cadastrado,
                                            // Garantindo que os dados sejam persistidos mesmo após o programa ser encerrado
}

void buscaClientes(Cliente *clientes, int numClientes) {
    
    int numBusca;

    printf("Digite o id do cliente que dejeja buscar:\n");
    scanf("%d", &numBusca);

    for (int i = 0; i < numClientes; i++){      //Sistema simples de busca, onde vais comparar todos os ids cadastrados com o id que o usuario deseja buscar
        if(clientes[i].id == numBusca){         // Se o cliente for encontrado, exibe as informações do cliente e retorna da função
            printf("ID: %d\n Nome: %s\n Idade: %d\n", clientes[i].id, clientes[i].nome, clientes[i].idade);
            return; // Cliente encontrado, retorna da função
        }
    }
    printf("Cliente não encontrado.\n");

}

void listaClientes(Cliente *clientes, int numClientes) {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    
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
    printf("Digite a opcao desejada: ");

}


void salvarClientes(Cliente *clientes, int numClientes){
   
    FILE *arquivoClie = fopen("dadosClientes.txt", "w");

    if (arquivoClie == NULL){
        printf("ERRO: não encotramos o arquivo.\n");  // Verifica se o arquivo foi aberto corretamente
        return;
    }
    
    for(int i = 0; i < numClientes; i++){
        fprintf(arquivoClie, "%d;%s;%d\n", clientes[i].id, clientes[i].nome, clientes[i].idade); // Escreve os dados do cliente no arquivo
    }

    fclose(arquivoClie);  // Sempre fecha o arquivo apos a utilização para evitar perda de dados ou corrupção do arquivo ou vazamento de memória.
}

void carregarClientes(Cliente **clientes, int *numClientes, int *capacidade){
   
    FILE *arquivoClie = fopen("dadosClientes.txt", "r");
    if (arquivoClie == NULL){
        printf("ERRO: não encotramos o arquivo.\n");
        return; 
    }
    
    while(fscanf(arquivoClie, "%d;%49[^;];%d\n", &(*clientes)[*numClientes].id, (*clientes)[*numClientes].nome, &(*clientes)[*numClientes].idade) == 3){// Lê os dados do arquivo e armazena no array de clientes
        
        (*numClientes)++; // Incrementa o número de clientes carregados do arquivo
        if (*numClientes >= *capacidade) {
            printf("Limite de clientes atingido (%d).\n", *capacidade);
            break;
        }
    }
    
    fclose(arquivoClie);
}