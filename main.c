/*
     sistema de cadastro de cliente e busca de cliente.
     no cadastro tem que ser informado o nome, idade e id do cliente
     quando for fazer a busca deve iforma o id do cliente e o sistema deve mostra o nome e a idade do clinte
     esse dados vai ser salvos em um arquivo de texto
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/clientes_service.h"


int main(){

    int opcao;
    int numClientes = 0;
    int capacidade = 2;

    Cliente *clientes = malloc(capacidade * sizeof(Cliente));

    if(clientes == NULL){
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    carregarClientes(&clientes, &numClientes, &capacidade);

    while(1){

        menu();

        if(scanf("%d", &opcao) != 1){
            printf("Entrada invalida.\n");
            while(getchar() != '\n');
            continue;
        }

        if(opcao == 1){

            Cliente novoCliente;

            printf("Digite o ID do cliente: ");
            scanf("%d", &novoCliente.id);

            printf("Digite o nome do cliente: ");
            getchar();
            fgets(novoCliente.nome, 50, stdin);
            novoCliente.nome[strcspn(novoCliente.nome, "\n")] = 0;

            printf("Digite a idade do cliente: ");
            scanf("%d", &novoCliente.idade);

            if(cadastrarClienteService(&clientes, &numClientes, &capacidade, novoCliente)){
                salvarClientes(clientes, numClientes);
                printf("Cliente cadastrado com sucesso.\n");
            }
            else{
                printf("Erro: ID ja cadastrado ou falha de memoria.\n");
            }
        }

        else if(opcao == 2){

            int idBusca;
            printf("Digite o ID do cliente: ");
            scanf("%d", &idBusca);

            int pos = buscarClienteService(clientes, numClientes, idBusca);

            if(pos == -1){
                printf("Cliente nao encontrado.\n");
            }
            else{
                printf("Cliente encontrado:\n");
                printf("ID: %d\n", clientes[pos].id);
                printf("Nome: %s\n", clientes[pos].nome);
                printf("Idade: %d\n", clientes[pos].idade);
            }
        }

        else if(opcao == 3){
            listarClientesService(clientes, numClientes);
        }

        else if(opcao == 4){

            int idAtualizar;
            char novoNome[50];
            int novaIdade;

            printf("Digite o ID do cliente que deseja atualizar: ");
            scanf("%d", &idAtualizar);

            printf("Digite o novo nome: ");
            getchar();
            fgets(novoNome, 50, stdin);
            novoNome[strcspn(novoNome, "\n")] = 0;

            printf("Digite a nova idade: ");
            scanf("%d", &novaIdade);

            if(atualizarClienteService(clientes, numClientes, idAtualizar, novoNome, novaIdade)){
                salvarClientes(clientes, numClientes);
                printf("Cliente atualizado com sucesso.\n");
            }
            else{
                printf("Cliente nao encontrado.\n");
            }
        }

        else if(opcao == 5){

            int idExcluir;
            printf("Digite o ID do cliente que deseja excluir: ");
            scanf("%d", &idExcluir);

            if(excluirClienteService(clientes, &numClientes, idExcluir)){
                salvarClientes(clientes, numClientes);
                printf("Cliente excluido com sucesso.\n");
            }
            else{
                printf("Cliente nao encontrado.\n");
            }
        }

        else if(opcao == 6){
            printf("Saindo do programa.\n");
            break;
        }

        else{
            printf("Opcao invalida.\n");
        }
    }

    free(clientes);
    return 0;
}