#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicação da struct Item
struct Item
{
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Vetor global de itens (mochila)
struct Item mochila[10];
int totalItens = 0;

// Função para adicionar um item à mochila
void inserirItem()
{
    if (totalItens >= 10)
    {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Cadastro de Item:\n");
    printf("Nome do item: ");
    scanf("%s", mochila[totalItens].nome);
    printf("Tipo do item: ");
    scanf("%s", mochila[totalItens].tipo);
    printf("Quantidade do item: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;

    printf("Item adicionado com sucesso!\n");
}

// Função para exibir os itens da mochila
void exibirMochila()
{
    if (totalItens == 0)
    {
        printf("Mochila vazia!\n");
        return;
    }
    printf("Itens na Mochila:\n");
    for (int i = 0; i < totalItens; i++)
    {
        printf("Item %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// Função para buscar (Busca linear)
int buscarItem(char nome[])
{
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nome) == 0)
        {
            return i; // Retorna o índice do item encontrado
        }
    }
    return -1; // Retorna -1 se o item não for encontrado
}

// função para remover um item da mochila
void removerItem()
{
    char nome[30];
    printf("Nome do item a ser removido: ");
    scanf("%s", nome);

    int indice = buscarItem(nome);

    if (indice == -1 )
    {
        printf("Item não encontrado na mochila!\n");
        return;
    }

    // Preenchendo o espaço do item removido
    for (int i = indice; i < totalItens - 1; i++)
    {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;

    printf("Item removido com sucesso!\n");
}

// Função para buscar e exibir
void buscarEExibirItem()
{
    char nome[30];
    printf("Nome do item a ser buscado: ");
    scanf("%s", nome);

    int indice = buscarItem(nome);

    if (indice == -1)
    {
        printf("Item não encontrado na mochila!\n");
        return;
    }

    printf("Item encontrado:\n");
    printf("Nome: %s\n", mochila[indice].nome);
    printf("Tipo: %s\n", mochila[indice].tipo);
    printf("Quantidade: %d\n", mochila[indice].quantidade);
}

// Função principal
int main()
{
    int opcao;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir item na mochila\n");
        printf("2. Exibir itens da mochila\n");
        printf("3. Buscar e exibir item\n");
        printf("4. Remover item da mochila\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserirItem();
            break;
        case 2:
            exibirMochila();
            break;
        case 3:
            buscarEExibirItem();
            break;
        case 4:
            removerItem();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}