#include <stdio.h>
#include <stdlib.h>
#include "equipamentos.h"

int main(void) {
    Equipamento *equipamentos = NULL;
    int quantidade = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (equipamentos != NULL) {
                    printf("\nOs equipamentos ja foram cadastrados nesta execucao.\n");
                } else {
                    equipamentos = cadastrarEquipamentos(&quantidade);
                }
                break;

            case 2:
                listarEquipamentos(equipamentos, quantidade);
                break;

            case 3:
                if (equipamentos == NULL || quantidade <= 0) {
                    printf("\nNenhum equipamento cadastrado para realizar a contagem.\n");
                } else {
                    int disponiveis = contarDisponiveis(equipamentos, quantidade, 0);

                    float percentual = ((float) disponiveis / (float) quantidade) * 100.0f;

                    printf("\n=== DISPONIBILIDADE DE EQUIPAMENTOS ===\n");
                    printf("Quantidade de equipamentos disponiveis: %d\n", disponiveis);
                    printf("Percentual de equipamentos disponiveis: %.2f%%\n", percentual);
                }
                break;

            case 4:
                if (equipamentos == NULL || quantidade <= 0) {
                    printf("\nNenhum equipamento cadastrado para calcular depreciacao.\n");
                } else {
                    int taxa, tempo;
                    printf("\nInforme a taxa anual de depreciacao (%%): ");
                    scanf("%d", &taxa);
                    printf("Informe o tempo de uso (anos): ");
                    scanf("%d", &tempo);

                    printf("\n=== DEPRECIACAO DOS EQUIPAMENTOS ===\n");
                    for (int i = 0; i < quantidade; i++) {
                        float valorDepreciado = calcularDepreciacao(
                            equipamentos[i].valor,
                            taxa,
                            tempo
                        );
                        printf("Equipamento: %s | Valor Original: R$ %.2f | Valor Depreciado: R$ %.2f\n",
                               equipamentos[i].nome,
                               equipamentos[i].valor,
                               valorDepreciado);
                    }
                }
                break;

            case 0:

                if (equipamentos != NULL) {
                    free(equipamentos);
                    equipamentos = NULL;
                }
                printf("\nMemoria liberada com sucesso. Programa encerrado!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
