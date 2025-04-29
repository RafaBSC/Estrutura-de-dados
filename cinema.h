#ifndef CINEMA_H
#define CINEMA_H

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

void adicionarFilme(Cinema *c);
void ordenarFilmes(Cinema *c);
void gerarBilhete(Cinema *c);
void exibirSala(Cinema *c);
void imprimirBilhete(Cinema *c);
void relatorio(Cinema *c);
void inicializarSala(Cinema *c);

#endif