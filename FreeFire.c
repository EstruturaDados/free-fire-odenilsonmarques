#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= STRUCTS =================

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

struct No {
    struct Item dados;
    struct No* proximo;
};

// ================= VARIÁVEIS =================

struct Item mochila[10];
int totalItens = 0;

struct No* mochilaLista = NULL;

// ================= VETOR =================

// Inserir no vetor
void inserirItem() {
    if (totalItens >= 10) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome: ");
    scanf("%s", mochila[totalItens].nome);

    printf("Tipo: ");
    scanf("%s", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;
}

// Listar vetor
void exibirMochila() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d\n", i+1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// Busca sequencial com contador
int buscarItem(char nome[], int* comparacoes) {
    *comparacoes = 0;

    for (int i = 0; i < totalItens; i++) {
        (*comparacoes)++;

        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

// Remover vetor
void removerItem() {
    char nome[30];
    printf("Nome para remover: ");
    scanf("%s", nome);

    int comp;
    int indice = buscarItem(nome, &comp);

    if (indice == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = indice; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    printf("Removido!\n");
}

// Ordenar vetor (Bubble Sort)
void ordenarMochila() {
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                struct Item temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }

    printf("Ordenado!\n");
}

// Busca binária
int buscaBinaria(char nome[], int* comparacoes) {
    int inicio = 0;
    int fim = totalItens - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;

        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ================= LISTA =================

// Inserir lista
void inserirLista() {
    struct No* novo = (struct No*) malloc(sizeof(struct No));

    printf("Nome: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;
}

// Listar lista
void listarLista() {
    struct No* atual = mochilaLista;

    if (atual == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    while (atual != NULL) {
        printf("\nNome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);

        atual = atual->proximo;
    }
}

// Remover lista
void removerLista() {
    char nome[30];
    printf("Nome para remover: ");
    scanf("%s", nome);

    struct No* atual = mochilaLista;
    struct No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item não encontrado!\n");
        return;
    }

    if (anterior == NULL)
        mochilaLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Removido da lista!\n");
}

// ================= COMPARAÇÃO =================

void compararBuscas() {
    char nome[30];
    int compSeq, compBin;

    printf("Nome: ");
    scanf("%s", nome);

    int idxSeq = buscarItem(nome, &compSeq);

    ordenarMochila(); // necessário

    int idxBin = buscaBinaria(nome, &compBin);

    printf("\nSequencial: %d comparações\n", compSeq);
    printf("Binária: %d comparações\n", compBin);

    if (idxSeq != -1)
        printf("Item encontrado!\n");
    else
        printf("Item não encontrado!\n");
}

// ================= MAIN =================

int main() {
    int op;

    do {
        printf("\n===== MENU =====\n");
        printf("1 Inserir (vetor)\n");
        printf("2 Listar (vetor)\n");
        printf("3 Remover (vetor)\n");
        printf("4 Ordenar vetor\n");
        printf("5 Busca binária\n");
        printf("6 Inserir (lista)\n");
        printf("7 Listar (lista)\n");
        printf("8 Remover (lista)\n");
        printf("9 Comparar buscas\n");
        printf("0 Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItem(); break;
            case 2: exibirMochila(); break;
            case 3: removerItem(); break;
            case 4: ordenarMochila(); break;

            case 5: {
                char nome[30];
                int comp;
                printf("Nome: ");
                scanf("%s", nome);

                int idx = buscaBinaria(nome, &comp);

                printf("Comparacoes: %d\n", comp);

                if (idx != -1)
                    printf("Encontrado!\n");
                else
                    printf("Nao encontrado!\n");
                break;
            }

            case 6: inserirLista(); break;
            case 7: listarLista(); break;
            case 8: removerLista(); break;
            case 9: compararBuscas(); break;

            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}