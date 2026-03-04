/*
     sistema de cadastro de cliente e busca de cliente.
     no cadastro tem que ser informado o nome, idade e id do cliente
     quando for fazer a busca deve iforma o id do cliente e o sistema deve mostra o nome e a idade do clinte
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"



int main(){
    Cliente *clientes;
    clientes = malloc( 10 * sizeof(Cliente) );
    if (clientes == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        return 1;
    }

    int opcao;
    int numClientes = 0;

    while(1){
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} // limpa buffer
            continue;
        }

        if (opcao == 4){
            printf("Saindo do programa...\n");
            break;
        }
        else if (opcao == 1){
            cadastraClientes(clientes, &numClientes);       //aqui é passado o endereço de memoria do numClientes para a função passar o valor atualizado
                                                            // o numero de clientes cadastrados é atualizado dentro da função cadastraClientes, e como estamos passando o endereço de memoria, a variavel numClientes no main.c também é atualizada com o novo valor
        }
        else if (opcao == 2){
            buscaClientes(clientes, numClientes);
        }
        else if (opcao == 3){
            listaClientes(clientes, numClientes);
        }
        else{
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    //sempre que alocar memoria dinamicamente, tem que liberar a memoria alocada no final do prgrama para evitar vazamento de memoria

    free (clientes);
    return 0;
}