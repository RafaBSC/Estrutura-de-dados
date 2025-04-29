#include "cinema.h"
#include <stdio.h>

int main() {
    Cinema cinema = {.totalFilmes = 0, .totalBilhetes = 0};
    inicializarSala(&cinema);
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar Filme\n");
        printf("2. Gerar Bilhete\n");
        printf("3. Imprimir Bilhete\n");
        printf("4. Relatorio de Bilhetes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarFilme(&cinema);
                ordenarFilmes(&cinema);
                break;
            case 2:
                gerarBilhete(&cinema);
                break;
            case 3:
                imprimirBilhete(&cinema);
                break;
            case 4:
                relatorio(&cinema);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}