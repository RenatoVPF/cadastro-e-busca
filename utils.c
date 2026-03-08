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
    salvarClientes(*clientes, *numClientes); // Chama a função para salvar os clientes no arquivo toda vez que um novo cliente for cadastrado,
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
    printf("4- atualizar cliente\n");
    printf("5- excluir cliente\n");
    printf("6- sair\n");
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

void atualizarClientes(Cliente *clientes, int numClientes){
    int idAtualizar;
    printf("digite o id do cliente que deseja atualizar:");
    scanf("%d", &idAtualizar);
    for (int i = 0; i < numClientes; i++){
        if (clientes[i].id == idAtualizar){
            int opcaoAtualizar;
            printf("dados do cliente encontrado:\n");
            printf("ID: %d\n Nome: %s\n Idade: %d\n", clientes[i].id, clientes[i].nome, clientes[i].idade);
            printf("Qual dado deseja atualizar?\n");
            printf("1- nome\n");
            printf("2- idade\n");
            scanf("%d", &opcaoAtualizar);
            if (opcaoAtualizar == 1){
                printf("Digite o novo nome do cliente: ");
                getchar();
                fgets(clientes[i].nome, 50, stdin);
                clientes[i].nome[strcspn(clientes[i].nome, "\n")] = 0;
                salvarClientes(clientes, numClientes); // Salva os clientes no arquivo após a atualização para garantir que os dados sejam persistidos
                printf("Nome atualizado com sucesso.\n");
            }
            else if (opcaoAtualizar == 2){
                printf("Digite a nova idade do cliente: ");
                scanf("%d", &clientes[i].idade);
                salvarClientes(clientes, numClientes); // Salva os clientes no arquivo após a atualização para garantir que os dados sejam persistidos
                printf("Idade atualizada com sucesso.\n");
            }
            else{
                printf("Opção inválida. Nenhum dado atualizado.\n");
            }
        }
    }
}

void excluirClientes(Cliente *clientes, int *numClientes, int idExcluir){

    for(int i =  0; i < *numClientes; i++){ // Percorre o array de clientes para encontrar o cliente com o id que o usuário deseja excluir

        if(clientes[i].id == idExcluir){

            for(int j =i; j < *numClientes - 1; j++){ // Se o cliente for encontrado, os clientes seguintes no array são movidos uma posição para trás para preencher o espaço deixado pelo cliente excluído

                clientes[j] = clientes[j + 1]; // Move o cliente seguinte para a posição atual, sobrescrevendo o cliente a ser excluído
            
            }
            (*numClientes)--; // Decrementa o número de clientes cadastrados, já que um cliente foi excluído
            salvarClientes(clientes, *numClientes); // Salva os clientes no arquivo após a exclusão para garantir que os dados sejam persistidos
            printf("Cliente excluído com sucesso.\n");
            return; // Cliente excluído, retorna da função
        }
    }
}