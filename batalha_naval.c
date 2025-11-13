#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5
#define AGUA '~'
#define NAVIO 'N'
#define TIRO 'X'
#define ERRO 'O'

// Inicializa tabuleiro
void inicializarTabuleiro(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = AGUA;
        }
    }
}

// Exibe tabuleiro
void exibirTabuleiro(char tab[TAM][TAM], int revelar) {
    printf("\n  0 1 2 3 4\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (!revelar && tab[i][j] == NAVIO)
                printf("%c ", AGUA);
            else
                printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

// Posicionamento automatico
void posicionarNaviosAuto(char tab[TAM][TAM]) {
    int navios = 3;
    int x, y;

    while (navios > 0) {
        x = rand() % TAM;
        y = rand() % TAM;

        if (tab[x][y] == AGUA) {
            tab[x][y] = NAVIO;
            navios--;
        }
    }
}

// Posicionamento manual
void posicionarNaviosManual(char tab[TAM][TAM]) {
    int x, y;

    for (int i = 0; i < 3; i++) {
        printf("Digite a posicao do navio %d (linha coluna): ", i + 1);
        scanf("%d %d", &x, &y);

        if (x >= 0 && x < TAM && y >= 0 && y < TAM && tab[x][y] == AGUA) {
            tab[x][y] = NAVIO;
        } else {
            printf("Posicao invalida, tente novamente.\n");
            i--;
        }
    }
}

// Jogada
int realizarAtaque(char tab[TAM][TAM], int x, int y) {
    if (tab[x][y] == NAVIO) {
        tab[x][y] = TIRO;
        return 1;
    } else if (tab[x][y] == AGUA) {
        tab[x][y] = ERRO;
        return 0;
    }
    return -1;
}

// Verifica fim de jogo
int venceu(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tab[i][j] == NAVIO)
                return 0;
    return 1;
}

// Main
int main() {
    srand(time(NULL));

    char jogador[TAM][TAM];
    char inimigo[TAM][TAM];
    int opcao, x, y;

    inicializarTabuleiro(jogador);
    inicializarTabuleiro(inimigo);

    printf("=== Jogo Batalha Naval - Versao C (Estacio) ===\n");
    printf("Escolha posicionamento dos seus navios:\n");
    printf("1) Manual\n");
    printf("2) Aleatorio (recomendado)\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1)
        posicionarNaviosManual(jogador);
    else
        posicionarNaviosAuto(jogador);

    posicionarNaviosAuto(inimigo);

    while (1) {
        printf("\nSeu tabuleiro:");
        exibirTabuleiro(jogador, 1);

        printf("\nTabuleiro inimigo:");
        exibirTabuleiro(inimigo, 0);

        printf("\nDigite coordenadas para atacar (linha coluna): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
            printf("Coordenada invalida!\n");
            continue;
        }

        if (realizarAtaque(inimigo, x, y) == 1)
            printf("Acertou um navio!\n");
        else
            printf("Errou o tiro!\n");

        if (venceu(inimigo)) {
            printf("\nPARABENS! Voce venceu o jogo!\n");
            break;
        }
    }

    printf("\nTabuleiro final inimigo:");
    exibirTabuleiro(inimigo, 1);

    return 0;
}
