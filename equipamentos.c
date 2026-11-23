#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "equipamentos.h"

void exibirMenu(void) {
    printf("\nCONTROLE DE EQUIPAMENTOS\n");
    printf("=======\n");
    printf("1 - Cadastrar equipamentos\n");
    printf("2 - Listar equipamentos\n");
    printf("3 - Contar equipamentos disponiveis\n");
    printf("4 - Calcular depreciacao dos equipamentos\n");
    printf("0 - Encerrar programa\n");
    printf("Escolha uma opcao: ");
}


Equipamento* cadastrarEquipamentos(int *quantidade) {
    int n, cat, est;

    do {
        printf("\nInforme a quantidade de equipamentos a cadastrar: ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Erro: A quantidade deve ser maior que zero.\n");
        }
    } while (n <= 0);

    Equipamento *vetor = (Equipamento *) malloc(n * sizeof(Equipamento));
    if (vetor == NULL) {
        printf("Erro critico: Falha na alocacao de memoria!\n");
        exit(1);
    }

    *quantidade = n;

    for (int i = 0; i < n; i++) {
        Equipamento *ptr = (vetor + i);

        printf("\n--- Cadastro do Equipamento %d ---\n", i + 1);

        printf("Codigo: ");
        scanf("%d", &ptr->codigo);

        printf("Nome: ");
        scanf(" %99[^\n]", ptr->nome);

        do {
            printf("Categoria (1 - Computador | 2 - Impressora | 3 - Projetor): ");
            scanf("%d", &cat);
            if (cat < 1 || cat > 3) {
                printf("Opcao invalida! Escolha 1, 2 ou 3.\n");
            }
        } while (cat < 1 || cat > 3);
        ptr->categoria = (Categoria) cat;

      
        switch (ptr->categoria) {
            case COMPUTADOR:
                printf("Quantidade de memoria RAM (GB): ");
                scanf("%d", &ptr->info.ram);
                break;
            case IMPRESSORA:
                printf("Quantidade de paginas impressas: ");
                scanf("%d", &ptr->info.paginas);
                break;
            case PROJETOR:
                printf("Luminosidade (lumens): ");
                scanf("%d", &ptr->info.lumens);
                break;
        }

     
        do {
            printf("Estado (1 - Disponivel | 2 - Em utilizacao): ");
            scanf("%d", &est);
            if (est < 1 || est > 2) {
                printf("Opcao invalida! Escolha 1 ou 2.\n");
            }
        } while (est < 1 || est > 2);
        ptr->estado = (Estado) est;

        printf("Valor de aquisicao (R$): ");
        scanf("%f", &ptr->valor);
    }

    printf("\nCadastro concluido com sucesso!\n");
    return vetor;
}

void listarEquipamentos(const Equipamento *equipamentos, int quantidade) {
    if (equipamentos == NULL || quantidade <= 0) {
        printf("\nNenhum equipamento cadastrado no sistema.\n");
        return;
    }

    printf("\n=== LISTA DE EQUIPAMENTOS CADASTRADOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        const Equipamento *ptr = (equipamentos + i);

        printf("\nCodigo: %d\n", ptr->codigo);
        printf("Nome: %s\n", ptr->nome);

     
        switch (ptr->categoria) {
            case COMPUTADOR:
                printf("Categoria: Computador\n");
                printf("Informacao especifica: %d GB de RAM\n", ptr->info.ram);
                break;
            case IMPRESSORA:
                printf("Categoria: Impressora\n");
                printf("Informacao especifica: %d paginas impressas\n", ptr->info.paginas);
                break;
            case PROJETOR:
                printf("Categoria: Projetor\n");
                printf("Informacao especifica: %d lumens\n", ptr->info.lumens);
                break;
        }

        if (ptr->estado == DISPONIVEL) {
            printf("Estado: Disponivel\n");
        } else {
            printf("Estado: Em utilizacao\n");
        }

        printf("Valor de aquisicao: R$ %.2f\n", ptr->valor);
    }
}


int contarDisponiveis(const Equipamento *equipamentos, int n, int i) {
    // Condição de parada: todos os elementos foram analisados
    if (i == n) {
        return 0;
    }

    if (equipamentos[i].estado == DISPONIVEL) {
        return 1 + contarDisponiveis(equipamentos, n, i + 1);
    } else {
        return contarDisponiveis(equipamentos, n, i + 1);
    }
}


float calcularDepreciacao(float valorAquisicao, int taxaAnual, int tempoAnos) {
    float taxaDecimal = (float) taxaAnual / 100.0f;
    float valorAtual = valorAquisicao * (float) pow(1.0 - taxaDecimal, tempoAnos);
    return valorAtual;
}