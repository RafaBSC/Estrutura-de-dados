#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_BILHETES 100
#define MAX_FILMES 50
#define MAX_LINHAS 10
#define MAX_COLUNAS 10

typedef enum { INTEIRA, MEIA } TipoIngresso;

typedef struct {
    char nome[MAX_NOME];
    char dataLancamento[20];
} Filme;

typedef struct {
    int numero;
    char nomeCliente[MAX_NOME];
    char nomeFilme[MAX_NOME];
    int linha, coluna;
    TipoIngresso tipo;
} Bilhete;

typedef struct {
    Filme filmes[MAX_FILMES];
    int totalFilmes;

    Bilhete bilhetes[MAX_BILHETES];
    int totalBilhetes;

    char sala[MAX_LINHAS][MAX_COLUNAS];
} Cinema;

void adicionarFilme(Cinema *c) {
    if (c->totalFilmes >= MAX_FILMES) {
        printf("Limite de filmes atingido.\n");
        return;
    }

    printf("Nome do filme: ");
    getchar();
    fgets(c->filmes[c->totalFilmes].nome, MAX_NOME, stdin);
    c->filmes[c->totalFilmes].nome[strcspn(c->filmes[c->totalFilmes].nome, "\n")] = '\0';

    printf("Data de lancamento (DD-MM-AAAA): ");
    fgets(c->filmes[c->totalFilmes].dataLancamento, 20, stdin);
    c->filmes[c->totalFilmes].dataLancamento[strcspn(c->filmes[c->totalFilmes].dataLancamento, "\n")] = '\0';

    c->totalFilmes++;
    printf("Filme adicionado com sucesso!\n");
}

int compararDatas(const void *a, const void *b) {
    return strcmp(((Filme*)a)->dataLancamento, ((Filme*)b)->dataLancamento);
}

void ordenarFilmes(Cinema *c) {
    qsort(c->filmes, c->totalFilmes, sizeof(Filme), compararDatas);
    printf("Filmes ordenados por data de lancamento.\n");
}

int verificarFilmeExistente(Cinema *c, const char *nomeFilme) {
    for (int i = 0; i < c->totalFilmes; i++) {
        if (strcmp(c->filmes[i].nome, nomeFilme) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void inicializarSala(Cinema *c) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            c->sala[i][j] = 'D';
        }
    }
}

void exibirSala(Cinema *c) {
    printf("\nSala de Cinema:\n");
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            printf("%c ", c->sala[i][j]);
        }
        printf("\n");
    }
}

void gerarBilhete(Cinema *c) {
    if (c->totalBilhetes >= MAX_BILHETES) {
        printf("Limite de bilhetes atingido.\n");
        return;
    }

    Bilhete *b = &c->bilhetes[c->totalBilhetes];
    b->numero = c->totalBilhetes + 1;

    printf("Nome do cliente: ");
    getchar();
    fgets(b->nomeCliente, MAX_NOME, stdin);
    b->nomeCliente[strcspn(b->nomeCliente, "\n")] = '\0';

    printf("\nFilmes disponiveis (ordenados por data de lancamento):\n");
    for (int i = 0; i < c->totalFilmes; i++) {
        printf("%d. %s (Lancamento: %s)\n", i + 1, c->filmes[i].nome, c->filmes[i].dataLancamento);
    }

    printf("Digite o nome do filme desejado: ");
    fgets(b->nomeFilme, MAX_NOME, stdin);
    b->nomeFilme[strcspn(b->nomeFilme, "\n")] = '\0';

    if (!verificarFilmeExistente(c, b->nomeFilme)) {
        printf("Filme inexistente.\n");
        return;
    }

    exibirSala(c);
    printf("\nEscolha o lugar (linha e coluna): ");
    scanf("%d %d", &b->linha, &b->coluna);

    if (c->sala[b->linha][b->coluna] == 'X') {
        printf("Esse lugar ja esta reservado. Escolha outro.\n");
        return;
    }

    c->sala[b->linha][b->coluna] = 'X';

    int tipo;
    printf("Tipo de ingresso (0 - Inteira, 1 - Meia-entrada): ");
    scanf("%d", &tipo);
    b->tipo = (tipo == 1) ? MEIA : INTEIRA;

    c->totalBilhetes++;
    printf("Bilhete gerado com sucesso!\n");
}

int compararBilhetesPorNumeroCrescente(const void *a, const void *b) {
    Bilhete *bilheteA = (Bilhete *)a;
    Bilhete *bilheteB = (Bilhete *)b;
    return bilheteA->numero - bilheteB->numero;
}

int compararBilhetesPorNumeroDecrescente(const void *a, const void *b) {
    return ((Bilhete*)b)->numero - ((Bilhete*)a)->numero;
}

int compararBilhetesPorTipoCrescente(const void *a, const void *b) {
    return ((Bilhete*)a)->tipo - ((Bilhete*)b)->tipo;
}

int compararBilhetesPorTipoDecrescente(const void *a, const void *b) {
    return ((Bilhete*)b)->tipo - ((Bilhete*)a)->tipo;
}

void ordenarBilhetes(Cinema *c, int criterio, int ordem) {
    if (criterio == 1) {
        if (ordem == 1) {
            qsort(c->bilhetes, c->totalBilhetes, sizeof(Bilhete), compararBilhetesPorNumeroCrescente);
        } else {
            qsort(c->bilhetes, c->totalBilhetes, sizeof(Bilhete), compararBilhetesPorNumeroDecrescente);
        }
    } else if (criterio == 2) {
        if (ordem == 1) {
            qsort(c->bilhetes, c->totalBilhetes, sizeof(Bilhete), compararBilhetesPorTipoCrescente);
        } else {
            qsort(c->bilhetes, c->totalBilhetes, sizeof(Bilhete), compararBilhetesPorTipoDecrescente);
        }
    }

    printf("Bilhetes ordenados com sucesso.\n");
}

void imprimirBilhete(Cinema *c) {
    if (c->totalBilhetes == 0) {
        printf("Nenhum bilhete cadastrado.\n");
        return;
    }

    qsort(c->bilhetes, c->totalBilhetes, sizeof(Bilhete), compararBilhetesPorNumeroCrescente);

    int numeroBilhete;
    printf("\nInforme o numero do bilhete a ser impresso: ");
    scanf("%d", &numeroBilhete);

    Bilhete chave;
    chave.numero = numeroBilhete;

    Bilhete *resultado = bsearch(&chave, c->bilhetes, c->totalBilhetes, sizeof(Bilhete), compararBilhetesPorNumeroCrescente);

    if (resultado == NULL) {
        printf("Bilhete nao encontrado.\n");
        return;
    }

    printf("\n--- Bilhete ---\n");
    printf("Numero do Bilhete: %d\n", resultado->numero);
    printf("Cliente: %s\n", resultado->nomeCliente);
    printf("Filme: %s\n", resultado->nomeFilme);
    printf("Tipo de ingresso: %s\n", resultado->tipo == INTEIRA ? "Inteira" : "Meia-entrada");
    printf("Lugar: Linha %d, Coluna %d\n", resultado->linha, resultado->coluna);
    printf("----------------\n");
}

void relatorio(Cinema *c) {
    int escolha, ordem;
    printf("\nEscolha o criterio de ordenacao:\n");
    printf("1 - Numero do bilhete\n");
    printf("2 - Tipo de ingresso (Meia/Inteira)\n");
    printf("Opcao: ");
    scanf("%d", &escolha);
    printf("Escolha a ordem de ordenacao:\n");
    printf("1 - Crescente\n");
    printf("2 - Decrescente\n");
    printf("Opcao: ");
    scanf("%d", &ordem);

    if ((escolha == 1 || escolha == 2) && (ordem == 1 || ordem == 2)) {
        ordenarBilhetes(c, escolha, ordem);
    } else {
        printf("Opcao invalida. Mostrando relatorio sem ordenacao.\n");
    }

    printf("\nRelatorio de Bilhetes:\n");
    for (int i = 0; i < c->totalBilhetes; i++) {
        Bilhete *b = &c->bilhetes[i];
        printf("Numero: %d | Cliente: %s | Filme: %s | Tipo: %s | Lugar: (%d, %d)\n",
               b->numero, b->nomeCliente, b->nomeFilme,
               b->tipo == INTEIRA ? "Inteira" : "Meia-entrada", b->linha, b->coluna);
    }
}

