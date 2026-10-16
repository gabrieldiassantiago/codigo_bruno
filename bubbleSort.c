#include <stdio.h>

typedef struct {
    char nome[30];
    int inicio;
    int fim;
} Palestra;

// Passo 1: ordenar por horario de termino (bubble sort)
void ordenarPorFim(Palestra arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j].fim > arr[j + 1].fim) {
                Palestra temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void gerenciarAuditorio(Palestra arr[], int n) {
    if (n == 0) {
        printf("Nenhuma palestra.\n");
        return;
    }

    ordenarPorFim(arr, n);

    printf("Ordenadas por termino:\n");
    for (int i = 0; i < n; i++) {
        printf("  - %s: [%02d:00 as %02d:00]\n", arr[i].nome, arr[i].inicio, arr[i].fim);
    }
    printf("\n");

    // Passo 2: a primeira sempre e aprovada
    int ultima = 0;
    int total = 1;
    printf("[APROVADA]  %s\n", arr[0].nome);

    // Passo 3: percorrer as demais
    for (int j = 1; j < n; j++) {
        if (arr[j].inicio >= arr[ultima].fim) {
            printf("[APROVADA]  %s\n", arr[j].nome);
            ultima = j;
            total++;
        } else {
            printf("[REJEITADA] %s (conflita com %s)\n", arr[j].nome, arr[ultima].nome);
        }
    }

    printf("\nTotal: %d\n", total);
}

int main() {
    Palestra pedidos[] = {
        {"Palestra A", 9, 12},
        {"Palestra B", 10, 11},
        {"Palestra C", 11, 13},
        {"Palestra D", 12, 14},
        {"Palestra E", 14, 15}
    };
    int n = sizeof(pedidos) / sizeof(pedidos[0]);

    gerenciarAuditorio(pedidos, n);
    return 0;
}
