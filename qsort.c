#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar uma palestra no auditório
typedef struct {
    char nome[30];
    int inicio;
    int fim;
} Palestra;

int compararPalestras(const void *a, const void *b) {
    Palestra *p1 = (Palestra *)a;
    Palestra *p2 = (Palestra *)b;
    
    if (p1->fim != p2->fim) {
        return p1->fim - p2->fim; 
    }
    return p1->inicio - p2->inicio;
}

void gerenciarAuditorio(Palestra arr[], int n) {
    printf("==================================================\n");
    printf("     GESTAO DE AGENDA DO AUDITORIO (GULOSO)       \n");
    printf("==================================================\n\n");

    // Passo 1: Ordenar as palestras pelo horário de término — O(N log N)
    qsort(arr, n, sizeof(Palestra), compararPalestras);

    printf("Pedidos organizados por horario de termino:\n");

    for (int i = 0; i < n; i++) {
        printf("  - %s: [%02d:00 as %02d:00]\n", arr[i].nome, arr[i].inicio, arr[i].fim);
    }
    printf("\n--- Passo a Passo da Aprovacao ---\n");

    // Passo 2: A primeira palestra ordenada é sempre aprovada
    int ultimaSelecionada = 0;
    int totalAprovadas = 1;
    printf("[APROVADA]  %s (%02d:00 - %02d:00) -> Primeira a liberar o auditorio.\n", 
           arr[0].nome, arr[0].inicio, arr[0].fim);

    // Passo 3: Percorrer as demais palestras — O(N)
    for (int j = 1; j < n; j++) {
        // Se o horário de início da palestra atual for >= ao término da última aceita
        if (arr[j].inicio >= arr[ultimaSelecionada].fim) {
            printf("[APROVADA]  %s (%02d:00 - %02d:00) -> Comeca apos o fim de %s (%02d:00).\n", 
                   arr[j].nome, arr[j].inicio, arr[j].fim, 
                   arr[ultimaSelecionada].nome, arr[ultimaSelecionada].fim);
            ultimaSelecionada = j;
            totalAprovadas++;
        } else {
            printf("[REJEITADA] %s (%02d:00 - %02d:00) -> Conflita com %s (ocupa ate %02d:00).\n", 
                   arr[j].nome, arr[j].inicio, arr[j].fim, 
                   arr[ultimaSelecionada].nome, arr[ultimaSelecionada].fim);
        }
    }

    printf("\nTotal maximo de eventos realizados no auditorio: %d\n\n", totalAprovadas);
}

int main() {
    // Lista de palestras enviadas para o exemplo do auditório
    Palestra pedidos[] = {
        {"Palestra A (RH)", 9, 12},
        {"Palestra B (Vendas)", 10, 11},
        {"Palestra C (IA)", 11, 13},     // Ajustado para 11:30 -> 12:30/13:00 (usando inteiros para facilitar)
        {"Palestra D (Ciberseguranca)", 12, 14},
        {"Palestra E (Projetos)", 14, 15}
    };
    int n = sizeof(pedidos) / sizeof(pedidos[0]);

    gerenciarAuditorio(pedidos, n);

    return 0;
}
