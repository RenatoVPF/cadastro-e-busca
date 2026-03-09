#include "../bibliotecas/utils.h"

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
    int posicaoInsercao = encontrarPosicaoInsercao(*clientes, *numClientes, idUnico); // Encontra a posição correta de inserção do novo cliente para manter o array ordenado por id

    for(int i = *numClientes; i > posicaoInsercao; i--){
        (*clientes)[i] = (*clientes)[i - 1]; // Move os clientes para a direita a partir da posição de inserção para abrir espaço para o novo cliente
    }
    (*clientes)[posicaoInsercao].id = idUnico; 
    
    

    printf("Digite o nome do cliente: ");
    getchar();
    fgets((*clientes)[posicaoInsercao].nome, 50, stdin);
    (*clientes)[posicaoInsercao].nome[strcspn((*clientes)[posicaoInsercao].nome, "\n")] = 0;

    printf("Digite a idade do cliente: ");
    scanf("%d", &(*clientes)[posicaoInsercao].idade);

    (*numClientes)++; // Incrementa o número de clientes cadastrados
    salvarClientes(*clientes, *numClientes); // Chama a função para salvar os clientes no arquivo toda vez que um novo cliente for cadastrado,
                                            // Garantindo que os dados sejam persistidos mesmo após o programa ser encerrado
}

int encontrarPosicaoInsercao(Cliente *clientes, int numClientes, int id) {
    // Essa função é usada para encontrar a posição correta de inserção de um novo cliente no array de clientes, garantindo que o array permaneça ordenado por id.
    // Ela percorre o array de clientes e retorna a posição onde o novo cliente deve ser inserido com base no seu id. 
    // Se o id do novo cliente for menor que o id do cliente atual, a função retorna a posição atual, indicando que o novo cliente deve ser inserido antes do cliente atual. 
    // Se o id do novo cliente for maior que todos os ids dos clientes existentes, a função retorna a posição após o último cliente, indicando que o novo cliente deve ser inserido no final do array.

    int i = 0;

    while(i < numClientes && clientes[i].id < id){
        i++;
    }

    return i;

}


void buscaClientes(Cliente *clientes, int numClientes) {
    
    int numBusca;

    printf("Digite o id do cliente que dejeja buscar:\n");
    scanf("%d", &numBusca);

    int posicaoCli = upBuscaBiClientes(clientes, numClientes, numBusca); // Chama a função de busca binária para encontrar a posição do cliente com o id especificado

    if(posicaoCli == -1){ // Se a função retornar -1, significa que o cliente não foi encontrado
        printf("Cliente não encontrado.\n");
        return;
    }
    // exibe os dados do cliente encontrado
    printf("Cliente encontrado:\n");
    printf("ID: %d\n Nome: %s\n Idade: %d\n", clientes[posicaoCli].id, clientes[posicaoCli].nome, clientes[posicaoCli].idade);
    
}

int upBuscaBiClientes(Cliente *clientes, int numClientes, int idBusca){ 
        // Essa função é um upgrade para a função de busca, onde vai ser implementada a busca binaria
        // Anteriomente a busca pecoria a lista inteira para encomtra o cliente, o que é ineficiente para lista muito grandes
        // A busca binaria vai funcinar dividindo lista no meio  e fazendo uma comparação com o id e o id do valor do meio
        // Se o id do meio for igual ao id, vai retornar a posição do id, se o id do meio for menor que o id, a busca vai continuar na metade superior da lista 
        // Se o id do meio for maior que o id, a busca vai continuar na metade inferior da lista, e sempre vai dividir a lista no meio até encontrar o id ou até a lista acabar, o que torna a busca muito mais eficiente para listas grandes
        // com complexidade logaritmica O(log n) 

    int inicioListaCli = 0;
    int fimListaCli = numClientes - 1;

    while(inicioListaCli<= fimListaCli){
        
        int meioListaCli = (inicioListaCli + fimListaCli) / 2;

        if(clientes[meioListaCli].id == idBusca){
            return meioListaCli;
        }
        else if(idBusca > clientes[meioListaCli].id){
            inicioListaCli = meioListaCli + 1;
        }
        else{
            fimListaCli = meioListaCli - 1;
        }
    }
    
    return -1; // Retorna -1 se o cliente não for encontrado
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

void atualizarClientes(Cliente *clientes, int numClientes){
    int idAtualizar;
    printf("digite o id do cliente que deseja atualizar:");
    scanf("%d", &idAtualizar);
    int pos = upBuscaBiClientes(clientes, numClientes, idAtualizar); // Usa a função de busca binária para encontrar a posição do cliente com o id especificado
    if(pos == -1){ // Se a função retornar -1, significa que o cliente não foi encontrado
        printf("Cliente não encontrado.\n");
        return ; 
    }
    
    
    int opcaoAtualizar;
    printf("dados do cliente encontrado:\n");
    printf("ID: %d\n Nome: %s\n Idade: %d\n", clientes[pos].id, clientes[pos].nome, clientes[pos].idade);
    printf("Qual dado deseja atualizar?\n");
    printf("1- nome\n");
    printf("2- idade\n");
    scanf("%d", &opcaoAtualizar);
    if (opcaoAtualizar == 1){
        printf("Digite o novo nome do cliente: ");
        getchar();
        fgets(clientes[pos].nome, 50, stdin);
        clientes[pos].nome[strcspn(clientes[pos].nome, "\n")] = 0;
        salvarClientes(clientes, numClientes); // Salva os clientes no arquivo após a atualização para garantir que os dados sejam persistidos
        printf("Nome atualizado com sucesso.\n");
    }
    else if (opcaoAtualizar == 2){
        printf("Digite a nova idade do cliente: ");
        scanf("%d", &clientes[pos].idade);
        salvarClientes(clientes, numClientes); // Salva os clientes no arquivo após a atualização para garantir que os dados sejam persistidos
        printf("Idade atualizada com sucesso.\n");
    }
    else{
        printf("Opção inválida. Nenhum dado atualizado.\n");
    }
    
    
}

void excluirClientes(Cliente *clientes, int *numClientes, int idExcluir){

    int posExcluir = upBuscaBiClientes(clientes, *numClientes, idExcluir); // Usa a função de busca binária para encontrar a posição do cliente com o id especificado para exclusão
    if(posExcluir == -1){ // Se a função retornar -1, significa que o cliente não foi encontrado
        printf("Cliente não encontrado.\n");
        return;
    }

    for(int j =posExcluir; j < *numClientes - 1; j++){ // Se o cliente for encontrado, os clientes seguintes no array são movidos uma posição para trás para preencher o espaço deixado pelo cliente excluído
        clientes[j] = clientes[j + 1]; // Move o cliente seguinte para a posição atual, sobrescrevendo o cliente a ser excluído
    }
    (*numClientes)--;// Decrementa o número de clientes cadastrados, já que um cliente foi excluído
     
    salvarClientes(clientes, *numClientes); // Salva os clientes no arquivo após a exclusão para garantir que os dados sejam persistidos
    printf("Cliente excluído com sucesso.\n");
    return; // Cliente excluído, retorna da função   
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