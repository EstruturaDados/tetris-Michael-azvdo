#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // capacidade máxima da fila

// -----------------------------------------------------------
// Struct que representa uma peça do Tetris Stack
// -----------------------------------------------------------
typedef struct {
    char nome;   // tipo da peça: I, O, T, L
    int id;      // identificador único
} Peca;


// Variáveis da fila circular
Peca fila[MAX_FILA];
int frente = 0;
int tras = 0;
int quantidade = 0;

// Contador global para IDs das peças
int contadorID = 0;


// -----------------------------------------------------------
// Função: gerarPeca()
// Cria automaticamente uma nova peça com nome aleatório.
// -----------------------------------------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorID++;
    return p;
}


// -----------------------------------------------------------
// Função: enqueue()
// Insere uma peça no final da fila circular.
// -----------------------------------------------------------
void enqueue(Peca p) {
    if (quantidade == MAX_FILA) {
        printf("\nA fila está cheia! Não é possível inserir mais peças.\n");
        return;
    }

    fila[tras] = p;
    tras = (tras + 1) % MAX_FILA;
    quantidade++;

    printf("\nPeça inserida: [%c %d]\n", p.nome, p.id);
}


// -----------------------------------------------------------
// Função: dequeue()
// Remove a peça da frente da fila circular.
// -----------------------------------------------------------
void dequeue() {
    if (quantidade == 0) {
        printf("\nA fila está vazia! Não há peça para jogar.\n");
        return;
    }

    Peca p = fila[frente];
    frente = (frente + 1) % MAX_FILA;
    quantidade--;

    printf("\nPeça jogada (removida): [%c %d]\n", p.nome, p.id);
}


// -----------------------------------------------------------
// Função: exibirFila()
// Mostra todas as peças atuais na fila.
// -----------------------------------------------------------
void exibirFila() {
    printf("\n===== FILA DE PEÇAS =====\n");

    if (quantidade == 0) {
        printf("A fila está vazia.\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}


// -----------------------------------------------------------
// Função principal: menu e interação
// -----------------------------------------------------------
int main() {
    srand(time(NULL));

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao;

    do {
        exibirFila();

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;

            case 2:
                enqueue(gerarPeca());
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
