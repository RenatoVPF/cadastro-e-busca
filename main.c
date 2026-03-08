/*
     sistema de cadastro de cliente e busca de cliente.
     no cadastro tem que ser informado o nome, idade e id do cliente
     quando for fazer a busca deve iforma o id do cliente e o sistema deve mostra o nome e a idade do clinte
     esse dados vai ser salvos em um arquivo de texto
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"



int main(){
    
    int opcao;
    int numClientes = 0;
    int capacidade = 2;
    
    Cliente *clientes;
    clientes = malloc( capacidade * sizeof(Cliente) );
    if (clientes == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        return 1;
    }
    
    
    carregarClientes(&clientes, &numClientes, &capacidade); // Carrega os clientes do arquivo ao iniciar o programa, garantindo que os dados persistam entre as execuções

    while(1){
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} // limpa buffer
            continue;
        }

        if (opcao == 6){
            printf("Saindo do programa...\n");
            break;
        }
        else if (opcao == 1){
            cadastraClientes(&clientes, &numClientes, &capacidade);       //aqui é passado o endereço de memoria do numClientes para a função passar o valor atualizado
                                                            // o numero de clientes cadastrados é atualizado dentro da função cadastraClientes, e como estamos passando o endereço de memoria, a variavel numClientes no main.c também é atualizada com o novo valor
        }
        else if (opcao == 2){
            buscaClientes(clientes, numClientes);
        }
        else if (opcao == 3){
            listaClientes(clientes, numClientes);
        }
        else if (opcao == 4){
            atualizarClientes(clientes, numClientes);
        }
        else if (opcao == 5){
            int idExcluir;
            printf("Digite o id do cliente que deseja excluir:\n");
            scanf("%d", &idExcluir);
            excluirClientes(clientes, &numClientes, idExcluir);
        }
        else{
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    //sempre que alocar memoria dinamicamente, tem que liberar a memoria alocada no final do prgrama para evitar vazamento de memoria

    free (clientes);
    return 0;
}