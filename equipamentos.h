#ifndef EQUIPAMENTOS_H
#define EQUIPAMENTOS_H

#define TAM_NOME 100

typedef enum {
    COMPUTADOR = 1,
    IMPRESSORA = 2,
    PROJETOR = 3
} Categoria;

typedef enum {
    DISPONIVEL = 1,
    EM_UTILIZACAO = 2
} Estado;

typedef union {
    int ram;      // Computador: quantidade de memória RAM (GB)
    int paginas;  // Impressora: quantidade de páginas impressas
    int lumens;   // Projetor: luminosidade (lúmens)
} Informacao;


typedef struct {
    int codigo;
    char nome[TAM_NOME];
    Categoria categoria;
    Estado estado;
    Informacao info;
    float valor;
} Equipamento;


void exibirMenu(void);
Equipamento* cadastrarEquipamentos(int *quantidade);
void listarEquipamentos(const Equipamento *equipamentos, int quantidade);
int contarDisponiveis(const Equipamento *equipamentos, int n, int i);
float calcularDepreciacao(float valorAquisicao, int taxaAnual, int tempoAnos);

#endif