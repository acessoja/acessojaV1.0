#include <string.h>
//entrada e saida
#include<stdio.h>
//inporta as opera�oes matematicas
#include<math.h>
//para poder usar assentua�ao
#include<locale.h>
#include<stdlib.h>
#define MAX_ESTABELECIMENTOS 100
#define CRITERIOS_ACESSIBILIDADE 5

// Vetor de estabelecimentos
char estabelecimentos[MAX_ESTABELECIMENTOS][100];

// Matriz de acessibilidade (0 = n�o dispon�vel, 1 = dispon�vel)
int acessibilidade[MAX_ESTABELECIMENTOS][CRITERIOS_ACESSIBILIDADE];

int n = 0; // N�mero atual de estabelecimentos

// Fun��o para trocar posi��es (usada na ordena��o)
void troca(char est1[], char est2[]) {
    char temp[100];
    strcpy(temp, est1);
    strcpy(est1, est2);
    strcpy(est2, temp);
}

void limparTela() {
	system("cls");
	}

// Fun��o para ordenar os estabelecimentos em ordem alfab�tica
void ordenarEstabelecimentos() {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (strcmp(estabelecimentos[i], estabelecimentos[j]) > 0) {
                troca(estabelecimentos[i], estabelecimentos[j]);
                // Troca acessibilidade correspondente
                for (int k = 0; k < CRITERIOS_ACESSIBILIDADE; k++) {
                    int temp = acessibilidade[i][k];
                    acessibilidade[i][k] = acessibilidade[j][k];
                    acessibilidade[j][k] = temp;
                }
            }
        }
    }
}

// Fun��o de busca bin�ria por nome do estabelecimento
int buscarEstabelecimento(char nome[]) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int comp = strcmp(nome, estabelecimentos[meio]);
        if (comp == 0) {
            return meio; // Estabelecimento encontrado
        } else if (comp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1; // N�o encontrado
}

// Fun��o para imprimir informa��es de um estabelecimento
void imprimirAcessibilidade(int indice) {
    printf("Acessibilidade de %s:\n", estabelecimentos[indice]);
    printf("Mesa Acess�vel: %s\n", acessibilidade[indice][0] ? "Dispon�vel" : "N�o dispon�vel");
    printf("Permiss�o de Entrada para C�o Guia: %s\n", acessibilidade[indice][1] ? "Dispon�vel" : "N�o dispon�vel");
    printf("Banheiros Especiais: %s\n", acessibilidade[indice][2] ? "Dispon�vel" : "N�o dispon�vel");
    printf("Rampas de Acesso: %s\n", acessibilidade[indice][3] ? "Dispon�vel" : "N�o dispon�vel");
    printf("Card�pio em Braille: %s\n", acessibilidade[indice][4] ? "Dispon�vel" : "N�o dispon�vel");
}

// Fun��o para cadastrar um novo estabelecimento
void cadastrarEstabelecimento() {
    if (n < MAX_ESTABELECIMENTOS) {
        printf("Digite o nome do estabelecimento: ");
        getchar(); // Limpar o buffer do teclado
        fgets(estabelecimentos[n], 100, stdin);
        estabelecimentos[n][strcspn(estabelecimentos[n], "\n")] = 0; // Remover nova linha

        printf("Informe a acessibilidade (0 = N�o Dispon�vel, 1 = Dispon�vel):\n");
        printf("Mesa Acess�vel: ");
        scanf("%d", &acessibilidade[n][0]);
        printf("Permiss�o de Entrada para C�o Guia: ");
        scanf("%d", &acessibilidade[n][1]);
        printf("Banheiros Especiais: ");
        scanf("%d", &acessibilidade[n][2]);
        printf("Rampas de Acesso: ");
        scanf("%d", &acessibilidade[n][3]);
        printf("Card�pio em Braille: ");
        scanf("%d", &acessibilidade[n][4]);

        n++; // Incrementa o n�mero de estabelecimentos
        printf("Estabelecimento cadastrado com sucesso!\n");
    } else {
        printf("Limite de estabelecimentos atingido.\n");
    }
}

// Fun��o para exibir todos os estabelecimentos cadastrados
void exibirEstabelecimentos() {
    if (n == 0) {
        printf("Nenhum estabelecimento cadastrado ainda.\n");
    } else {
        printf("Estabelecimentos cadastrados:\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", estabelecimentos[i]);
        }
    }
}

// Fun��o para exibir o menu e processar as op��es
void exibirMenu() {
    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Cadastrar Estabelecimento\n");
        printf("2. Exibir Estabelecimentos\n");
        printf("3. Ordenar Estabelecimentos\n");
        printf("4. Buscar Estabelecimento\n");
        printf("5. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            	limparTela();
                cadastrarEstabelecimento();
                break;
            case 2:
            	limparTela();
                exibirEstabelecimentos();
                break;
            case 3:
            	limparTela();
                ordenarEstabelecimentos();
                printf("Estabelecimentos ordenados com sucesso!\n");
                break;
            case 4:
				limparTela(); {
                char nomeBusca[100];
                printf("Digite o nome do estabelecimento para busca: ");
                getchar(); // Limpar o buffer do teclado
                fgets(nomeBusca, 100, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remover nova linha

                int indice = buscarEstabelecimento(nomeBusca);
                if (indice != -1) {
                    imprimirAcessibilidade(indice);
                } else {
                    printf("Estabelecimento n�o encontrado.\n");
                }
                break;
            }
            case 5:
            	limparTela();
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    // Executa o menu interativo
    exibirMenu();
    return 0;
}

