#include "../bibliotecas/utils.h"



void salvarClientes(Cliente *clientes, int numClientes){
   
    FILE *arquivoClie = fopen("dadosClientes.txt", "w");

    if (arquivoClie == NULL){
        printf("ERRO: não encotramos o arquivo.\n");  // Verifica se o arquivo foi aberto corretamente
        return;
    }

    fprintf(arquivoClie, "id;nome;idade\n");
    
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

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), arquivoClie);
    
    while(1){

        if(*numClientes >= *capacidade){
            *capacidade = (*capacidade) * 2;
            Cliente *temp = realloc(*clientes, (*capacidade)* sizeof(Cliente));
            if(temp == NULL){
                printf("ERRO: falha ao realocar memoria.\n");
                fclose(arquivoClie);
                return;
            }
            *clientes = temp;
        }
        int lidos = fscanf(arquivoClie, "%d;%49[^;];%d\n", &(*clientes)[*numClientes].id, (*clientes)[*numClientes].nome, &(*clientes)[*numClientes].idade); // Lê os dados do cliente do arquivo, usando o formato especificado para garantir que os campos sejam lidos corretamente. O %49[^;] é usado para ler o nome do cliente, garantindo que não ultrapasse o limite de 50 caracteres (incluindo o caractere nulo).
        if (lidos != 3){
            break; // Se não conseguir ler os 3 campos, significa que chegou ao final do arquivo ou ocorreu um erro, então sai do loop
        }
        (*numClientes)++; // Incrementa o número de clientes carregados do arquivo
    }
    
    fclose(arquivoClie);
}

void menu() {
    
    printf("######## MENU ########\n");
    printf("1- cadastrar cliente\n");
    printf("2- buscar cliente\n");
    printf("3- lista com os clientes\n");
    printf("4- atualizar cliente\n");
    printf("5- excluir cliente\n");
    printf("6- sair\n");
    printf("Digite a opcao desejada: ");

    

}