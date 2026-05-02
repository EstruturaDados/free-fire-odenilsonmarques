#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================= STRUCT =================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ================= VARIÁVEIS =================

int comparacoes = 0;

// ================= FUNÇÕES =================

// Exibir componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ================= ORDENAÇÕES =================

// Bubble Sort (por nome)
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

// Insertion Sort (por tipo)
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

// Selection Sort (por prioridade)
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            Componente temp = v[i];
            v[i] = v[menor];
            v[menor] = temp;
        }
    }
}

// ================= BUSCA BINÁRIA =================

int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(v[meio].nome, nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ================= MEDIR TEMPO =================

void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio, fim;

    inicio = clock();
    algoritmo(v, n);
    fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo: %f segundos\n", tempo);
}

// ================= MAIN =================

int main() {
    Componente vetor[20];
    int total = 0;
    int op;

    // Cadastro
    printf("Quantos componentes deseja cadastrar (max 20)? ");
    scanf("%d", &total);

    for (int i = 0; i < total; i++) {
        printf("\nComponente %d\n", i+1);

        printf("Nome: ");
        scanf("%s", vetor[i].nome);

        printf("Tipo: ");
        scanf("%s", vetor[i].tipo);

        printf("Prioridade (1-10): ");
        scanf("%d", &vetor[i].prioridade);
    }

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Bubble Sort (Nome)\n");
        printf("2 - Insertion Sort (Tipo)\n");
        printf("3 - Selection Sort (Prioridade)\n");
        printf("4 - Busca Binaria (por nome)\n");
        printf("5 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                medirTempo(bubbleSortNome, vetor, total);
                break;

            case 2:
                medirTempo(insertionSortTipo, vetor, total);
                break;

            case 3:
                medirTempo(selectionSortPrioridade, vetor, total);
                break;

            case 4: {
                char nome[30];
                printf("Nome do componente-chave: ");
                scanf("%s", nome);

                int pos = buscaBinariaPorNome(vetor, total, nome);

                if (pos != -1)
                    printf("Componente encontrado na posicao %d!\n", pos);
                else
                    printf("Componente nao encontrado!\n");

                break;
            }

            case 5:
                mostrarComponentes(vetor, total);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}