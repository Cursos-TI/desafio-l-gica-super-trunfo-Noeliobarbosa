#include <stdio.h>
#include <string.h>

// Definição da estrutura da carta (reaproveitada do desafio anterior)
typedef struct {
    char estado[3]; // Ex: "SP"
    char codigo_carta[10]; // Ex: "C001"
    char nome_cidade[50];
    int populacao;
    float area; // em km²
    float pib; // em bilhões de R$
    int pontos_turisticos;
    float densidade_populacional; // Calculado
    float pib_per_capita;         // Calculado
} Carta;

// Definições para facilitar a escolha do atributo de comparação
#define POPULACAO 0
#define AREA 1
#define PIB 2
#define DENSIDADE_POPULACIONAL 3
#define PIB_PER_CAPITA 4
#define PONTOS_TURISTICOS 5

// Escolha o atributo para comparação (altere este valor para testar outros atributos)
#define ATRIBUTO_PARA_COMPARAR POPULACAO // Exemplo: POPULACAO, AREA, PIB, DENSIDADE_POPULACIONAL, PIB_PER_CAPITA

// Função para calcular densidade populacional e PIB per capita
void calcularAtributosDerivados(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0; // Evita divisão por zero
    }

    if (carta->populacao > 0) {
        // Multiplica por 1.000.000.000 (1 bilhão) para converter PIB de "bilhões de reais" para "reais" antes de dividir
        carta->pib_per_capita = (carta->pib * 1000000000.0f) / carta->populacao;
    } else {
        carta->pib_per_capita = 0; // Evita divisão por zero
    }
}

// Função para exibir os detalhes de uma carta (útil para debug e visualização)
void exibirCarta(const Carta *carta) {
    printf("  Estado: %s\n", carta->estado);
    printf("  Codigo da Carta: %s\n", carta->codigo_carta);
    printf("  Nome da Cidade: %s\n", carta->nome_cidade);
    printf("  Populacao: %d\n", carta->populacao);
    printf("  Area: %.2f km2\n", carta->area);
    printf("  PIB: %.2f bilhoes R$\n", carta->pib);
    printf("  Pontos Turisticos: %d\n", carta->pontos_turisticos);
    printf("  Densidade Populacional: %.2f hab/km2\n", carta->densidade_populacional);
    printf("  PIB per Capita: %.2f R$\n", carta->pib_per_capita);
}

int main() {
    Carta carta1, carta2;

    // Dados da Carta 1: Berlim
    strcpy(carta1.estado, "A");
    strcpy(carta1.codigo_carta, "A01");
    strcpy(carta1.nome_cidade, "Berlim");
    carta1.populacao = 3664088;
    carta1.area = 891.85f;
    carta1.pib = 1058.345960f; // 1.058.345.960.000 reais = 1058.345960 bilhões de reais
    carta1.pontos_turisticos = 154;

    // Dados da Carta 2: Moscovo
    strcpy(carta2.estado, "B");
    strcpy(carta2.codigo_carta, "B02");
    strcpy(carta2.nome_cidade, "Moscovo");
    carta2.populacao = 11979529;
    carta2.area = 1200.25f;
    carta2.pib = 4061760.60f; // 4.061.760.600.000.000,50 reais = 4061760.60 bilhões de reais (simplificado para float)
    carta2.pontos_turisticos = 182;

    // Calcular Densidade Populacional e PIB per capita para ambas as cartas
    calcularAtributosDerivados(&carta1);
    calcularAtributosDerivados(&carta2);

    printf("--- Dados das Cartas ---\n");
    printf("\nCarta 1:\n");
    exibirCarta(&carta1);
    printf("\nCarta 2:\n");
    exibirCarta(&carta2);
    printf("------------------------\n\n");

    // Comparar um atributo escolhido
    printf("Comparacao de cartas (Atributo: ");

    float valor1, valor2;
    char atributo_nome[50];
    int carta_vencedora = 0; // 0 = empate, 1 = carta1, 2 = carta2

    switch (ATRIBUTO_PARA_COMPARAR) {
        case POPULACAO:
            strcpy(atributo_nome, "Populacao");
            valor1 = (float)carta1.populacao;
            valor2 = (float)carta2.populacao;
            if (valor1 > valor2) {
                carta_vencedora = 1;
            } else if (valor2 > valor1) {
                carta_vencedora = 2;
            }
            break;
        case AREA:
            strcpy(atributo_nome, "Area");
            valor1 = carta1.area;
            valor2 = carta2.area;
            if (valor1 > valor2) {
                carta_vencedora = 1;
            } else if (valor2 > valor1) {
                carta_vencedora = 2;
            }
            break;
        case PIB:
            strcpy(atributo_nome, "PIB");
            valor1 = carta1.pib;
            valor2 = carta2.pib;
            if (valor1 > valor2) {
                carta_vencedora = 1;
            } else if (valor2 > valor1) {
                carta_vencedora = 2;
            }
            break;
        case DENSIDADE_POPULACIONAL:
            strcpy(atributo_nome, "Densidade Populacional");
            valor1 = carta1.densidade_populacional;
            valor2 = carta2.densidade_populacional;
            // Para Densidade Populacional, a carta com MENOR valor vence
            if (valor1 < valor2) {
                carta_vencedora = 1;
            } else if (valor2 < valor1) {
                carta_vencedora = 2;
            }
            break;
        case PIB_PER_CAPITA:
            strcpy(atributo_nome, "PIB per Capita");
            valor1 = carta1.pib_per_capita;
            valor2 = carta2.pib_per_capita;
            if (valor1 > valor2) {
                carta_vencedora = 1;
            } else if (valor2 > valor1) {
                carta_vencedora = 2;
            }
            break;
        case PONTOS_TURISTICOS:
            strcpy(atributo_nome, "Pontos Turisticos");
            valor1 = (float)carta1.pontos_turisticos;
            valor2 = (float)carta2.pontos_turisticos;
            if (valor1 > valor2) {
                carta_vencedora = 1;
            } else if (valor2 > valor1) {
                carta_vencedora = 2;
            }
            break;
        default:
            printf("ATRIBUTO INVALIDO! Verifique a definicao de ATRIBUTO_PARA_COMPARAR.\n");
            return 1; // Sai do programa com erro
    }

    printf("%s):\n", atributo_nome);

    // Exibir o resultado da comparação
    printf("Carta 1 - %s (%s): ", carta1.nome_cidade, carta1.estado);
    // Formatação específica para População e Pontos Turísticos (inteiro)
    if (ATRIBUTO_PARA_COMPARAR == POPULACAO || ATRIBUTO_PARA_COMPARAR == PONTOS_TURISTICOS) {
        printf("%d\n", (int)valor1);
    } else {
        printf("%.2f\n", valor1);
    }

    printf("Carta 2 - %s (%s): ", carta2.nome_cidade, carta2.estado);
    // Formatação específica para População e Pontos Turísticos (inteiro)
    if (ATRIBUTO_PARA_COMPARAR == POPULACAO || ATRIBUTO_PARA_COMPARAR == PONTOS_TURISTICOS) {
        printf("%d\n", (int)valor2);
    } else {
        printf("%.2f\n", valor2);
    }

    printf("Resultado: ");
    if (carta_vencedora == 1) {
        printf("Carta 1 (%s) venceu!\n", carta1.nome_cidade);
    } else if (carta_vencedora == 2) {
        printf("Carta 2 (%s) venceu!\n", carta2.nome_cidade);
    } else {
        printf("Empate!\n");
    }

    return 0;
}