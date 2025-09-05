#include <stdio.h>
#include <stdlib.h>

void intercambiar(int *a, int *b) {
    int temporal;
    temporal = *a;
    *a = *b;
    *b = temporal;
}

int comparar_tuerca_con_tornillo(int tuerca, int tornillo) {
    if (tuerca < tornillo) {
        return -1;
    } else {
        if (tuerca > tornillo) {
            return 1;
        } else {
            return 0;
        }
    }
}

int comparar_tornillo_con_tuerca(int tornillo, int tuerca) {
    if (tornillo < tuerca) {
        return -1;
    } else {
        if (tornillo > tuerca) {
            return 1;
        } else {
            return 0;
        }
    }
}

// Particion de TUERCAS, TORNILLO como pivote
int partir_tuercas(int tuercas[], int bajo, int alto, int tornilloPivote) {
    int i;
    int j;
    int comparacion;
    i = bajo;
    j = bajo;
    while (j < alto) {
        comparacion = comparar_tuerca_con_tornillo(tuercas[j], tornilloPivote);
        if (comparacion < 0) {
            intercambiar(&tuercas[i], &tuercas[j]);
            i = i + 1;
            j = j + 1;
        } else {
            if (comparacion == 0) {
                intercambiar(&tuercas[j], &tuercas[alto]);
            } else {
                j = j + 1;
            }
        }
    }
    intercambiar(&tuercas[i], &tuercas[alto]);
    return i;
}

//Particion de TORNILLOS, TUERCA como pivote
int partir_tornillos(int tornillos[], int bajo, int alto, int tuercaPivote) {
    int i;
    int j;
    int comparacion;
    i = bajo;
    j = bajo;
    while (j < alto) {
        comparacion = comparar_tornillo_con_tuerca(tornillos[j], tuercaPivote);
        if (comparacion < 0) {
            intercambiar(&tornillos[i], &tornillos[j]);
            i = i + 1;
            j = j + 1;
        } else {
            if (comparacion == 0) {
                intercambiar(&tornillos[j], &tornillos[alto]);
            } else {
                j = j + 1;
            }
        }
    }
    intercambiar(&tornillos[i], &tornillos[alto]);
    return i;
}

//QuickSort
void emparejar_recursivo(int tuercas[], int tornillos[], int bajo, int alto) {
    int indicePivoteTuerca;
    int valorTuercaPivote;
    if (bajo >= alto) {
        return;
    }
    indicePivoteTuerca = partir_tuercas(tuercas, bajo, alto, tornillos[alto]);
    valorTuercaPivote = tuercas[indicePivoteTuerca];
    (void)partir_tornillos(tornillos, bajo, alto, valorTuercaPivote);
    emparejar_recursivo(tuercas, tornillos, bajo, indicePivoteTuerca - 1);
    emparejar_recursivo(tuercas, tornillos, indicePivoteTuerca + 1, alto);
}

//Funcion principa
void emparejar_tuercas_y_tornillos(int tuercas[], int tornillos[], int n) {
    if (n <= 1) {
        return;
    } else {
        emparejar_recursivo(tuercas, tornillos, 0, n - 1);
    }
}

/* Imprime un arreglo lineal */
void imprimir_arreglo(const char *etiqueta, int arr[], int n) {
    printf("%s: ", etiqueta);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int m;  // número total de pares provistos en la entrada
    printf("Numero de pares: ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        fprintf(stderr, "Error: m inválido.\n");
        return 1;
    }

    int *tuercas   = (int *)malloc(m * sizeof(int));
    int *tornillos = (int *)malloc(m * sizeof(int));
    if (!tuercas || !tornillos) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        free(tuercas); free(tornillos);
        return 1;
    }

    int n_tuercas = 0, n_tornillos = 0;

    for (int i = 0; i < 2*m; i++) {     // m = #pares -> 2*m = #elementos
        int tipo, valor;
        printf("Ingresa el tipo (0 = Tuerca y 1 = Tornillo) y el valor del elemnto %d: ", i+1);
        if (scanf("%d %d", &tipo, &valor) != 2) {
            fprintf(stderr, "Error: entrada inválida en la línea %d.\n", i + 2);
            free(tuercas); free(tornillos);
            return 1;
        }
        if (tipo == 0) {           // tuerca
            tuercas[n_tuercas++] = valor;
        } else if (tipo == 1) {    // tornillo
            tornillos[n_tornillos++] = valor;
        } else {
            fprintf(stderr, "Error: tipo debe ser 0 (tuerca) o 1 (tornillo).\n");
            free(tuercas); free(tornillos);
            return 1;
        }
    }

    if (n_tuercas != n_tornillos) {
        fprintf(stderr, "Error: cantidad desigual de tuercas (%d) y tornillos (%d).\n",
                n_tuercas, n_tornillos);
        free(tuercas); free(tornillos);
        return 1;
    }

    int n = n_tuercas; // número de parejas

    // Llamada a la función a implementar
    emparejar_tuercas_y_tornillos(tuercas, tornillos, n);

    // Mostrar resultados como dos arreglos lineales
    imprimir_arreglo("Tuercas", tuercas, n);
    imprimir_arreglo("Tornillos", tornillos, n);

    free(tuercas);
    free(tornillos);
    return 0;
}
