#include <stdio.h>
#include <stdlib.h>

/*
  Ejercicio: Completar la implementación del algoritmo QuickSort.

  Recordatorio:
    - QuickSort es un algoritmo de ordenamiento basado en "divide y conquista".
    - Se elige un pivote y se reordenan los elementos de modo que:
         * a la izquierda del pivote: menores o iguales,
         * a la derecha del pivote: mayores.
    - Luego se aplica recursivamente en las dos mitades.
*/

/* Función para intercambiar dos elementos */
void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
  Función de partición:
    - Debe elegir un pivote (por ejemplo, el último elemento).
    - Reordenar el arreglo colocando menores a la izquierda y mayores a la derecha.
    - Retornar el índice final del pivote.
*/
int particion(int arr[], int bajo, int alto)
{
    int pivote = arr[alto];
    int i = bajo - 1; // Placeholder, reemplazar por el índice real del pivote

    for (int j = bajo; j < alto; j++) {
        if (arr[j] <= pivote) {
            i++;
            intercambiar(&arr[i], &arr[j]);
        }
    }
    intercambiar(&arr[i + 1], &arr[alto]);
    return i + 1;
}

/*
  Función QuickSort:
    - Caso base: si bajo >= alto, terminar.
    - Paso recursivo: llamar a particion, y aplicar QuickSort en las dos mitades.
*/
void quicksort(int arr[], int bajo, int alto) {
    if(bajo < alto){
        int p = particion(arr, bajo, alto);
        quicksort(arr,bajo, p-1);
        quicksort(arr, p+1,alto);
    }
}

/* Función auxiliar para imprimir un arreglo */
void imprimir_arreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int n;
    printf("Ingrese el número de elementos: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        return 1;
    }

    printf("Ingrese los %d elementos:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Arreglo original:\n");
    imprimir_arreglo(arr, n);

    quicksort(arr, 0, n - 1);  // Llamada al algoritmo

    printf("Arreglo ordenado:\n");
    imprimir_arreglo(arr, n);

    free(arr);
    return 0;
}
