int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida.\n");
        return 1;
    }

    Atividade *arr = malloc(n * sizeof(Atividade));

    if (arr == NULL && n > 0) {
        printf("Erro de memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%4s %d %d", arr[i].id, &arr[i].inicio, &arr[i].fim) != 3) {
            printf("Erro ao ler a atividade %d.\n", i + 1);
            free(arr);
            return 1;
        }
    }

    selecionar(arr, n);
    free(arr);
    return 0;
}
