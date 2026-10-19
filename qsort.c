    #include <stdio.h>
    #include <stdlib.h>

    typedef struct {
        char id[5];
        int inicio;
        int fim;
    } Atividade;

    //recebe dois ponteiros genericos
    int comparar(const void *a, const void *b) {
        const Atividade *x = (const Atividade *)a;
        const Atividade *y = (const Atividade *)b;

        if (x->fim != y->fim)
            return (x->fim < y->fim) ? -1 : 1;
        if (x->inicio != y->inicio)
            return (x->inicio < y->inicio) ? -1 : 1;
        return 0;
        
    }

    void selecionar(Atividade arr[], int n) {
        printf("==================================================\n");
        printf("EXECUTANDO: Algoritmo Guloso de Selecao de Atividades\n");
        printf("==================================================\n");

        if (n <= 0) {
            printf("Nenhuma atividade para selecionar.\n");
            printf("Total de atividades selecionadas: 0\n");
            return;
        }

        qsort(arr, n, sizeof(Atividade), comparar);
        printf("Atividades apos ordenacao por termino:\n");

        for (int i = 0; i < n; i++) {
            printf(" %s: [%d, %d)\n", arr[i].id, arr[i].inicio, arr[i].fim);
        }

        //pois o primeiro ordenado é o primeiro a ser selecionado
        int ultimaSelecionada = 0;
        int totalSelecionadas = 1;
        printf("\nResultado da selecao:\n");
        printf(" %s: [%d, %d) - Selecionada\n", arr[ultimaSelecionada].id, arr[ultimaSelecionada].inicio, 
            arr[ultimaSelecionada].fim);

        for (int j = 1; j < n; j++) {
            if (arr[j].inicio >= arr[ultimaSelecionada].fim) {
                ultimaSelecionada = j;
                totalSelecionadas++;
                printf(" %s: [%d, %d) - Selecionada\n",
                    arr[j].id, arr[j].inicio, arr[j].fim);
            } else {
                printf(" %s: [%d, %d) - Ignorada\n",
                    arr[j].id, arr[j].inicio, arr[j].fim);
            }
        }
        
        printf("\nTotal de atividades selecionadas: %d\n", totalSelecionadas);
    }


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
