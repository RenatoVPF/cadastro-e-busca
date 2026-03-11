#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../bibliotecas/clientes_service.h"



int buscarIdsClientes(Cliente *clientes, int numClientes, int idBusca){

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

int encontrarPosicaoInsercao(Cliente *clientes, int numClientes, int idNovo){
    int i = 0;

    while(i < numClientes && clientes[i].id < idNovo){
        i++;
    }

    return i;
}

void listarClientesService(Cliente *clientes, int numClientes){
    if(numClientes == 0){
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for(int i = 0; i < numClientes; i++){
        printf("ID: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Idade: %d\n\n", clientes[i].idade);
    }
}

int buscarClienteService(Cliente *clientes, int numClientes, int idBusca){
    int posicaoCli = buscarIdsClientes(clientes, numClientes, idBusca); // Chama a função de busca binária para encontrar a posição do cliente com o id especificado

    if(posicaoCli == -1){ // Se a função retornar -1, significa que o cliente não foi encontrado
        printf("Cliente não encontrado.\n");
        return -1;
    }
    // exibe os dados do cliente encontrado
    /*printf("Cliente encontrado:\n");
    printf("ID: %d\n Nome: %s\n Idade: %d\n", clientes[posicaoCli].id, clientes[posicaoCli].nome, clientes[posicaoCli].idade);*/
    return posicaoCli; // Retorna a posição do cliente encontrado
}

int cadastrarClienteService(Cliente **clientes, int *numClientes, int *capacidade, Cliente novoCliente){
    if(buscarIdsClientes(*clientes, *numClientes, novoCliente.id) != -1){
        return 0;
    }

    if(*numClientes >= *capacidade){
        *capacidade = (*capacidade) * 2;

        Cliente *temp = realloc(*clientes, (*capacidade) * sizeof(Cliente));
        if(temp == NULL){
            printf("Erro ao aumentar memoria.\n");
            return 0;
        }

        *clientes = temp;
    }

    int pos = encontrarPosicaoInsercao(*clientes, *numClientes, novoCliente.id);

    for(int i = *numClientes; i > pos; i--){
        (*clientes)[i] = (*clientes)[i - 1];
    }

    (*clientes)[pos] = novoCliente;
    (*numClientes)++;

    return 1;
}

int atualizarClienteService(Cliente *clientes, int numClientes, int idAtualizar, char novoNome[], int novaIdade){
    int pos = buscaBinariaClientes(clientes, numClientes, idAtualizar);

    if(pos == -1){
        return 0;
    }

    strcpy(clientes[pos].nome, novoNome);
    clientes[pos].idade = novaIdade;

    return 1;
}

int excluirClienteService(Cliente *clientes, int *numClientes, int idExcluir){

    int pos = buscarIdsClientes(clientes, *numClientes, idExcluir);

    if(pos == -1){
        return 0;
    }

    for(int j = pos; j < *numClientes - 1; j++){
        clientes[j] = clientes[j + 1];
    }

    (*numClientes)--;

    return 1;
}
