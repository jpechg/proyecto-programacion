#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "reader.h"


//Esta funcion compara dos actividades por ocupacion, la usamos dentro de qsort para ordenar de mayor ocupado a menor ocupado.
static int comparar_por_ocupacion(const void *a_void, const void *b_void)
{
    const actividad *a = (const actividad *)a_void;
    const actividad *b = (const actividad *)b_void;

    if (a->ocupado > b->ocupado) {
        return -1; // a va antes que b
    }

    if (a->ocupado < b->ocupado) {
        return 1; // b va antes que a
    }

    return 0; // son iguales
}

actividad *ordenar_actividades_centro_por_ocupacion(actividad *dataptr,unsigned int n_lineas,uint32_t centro_elegido,unsigned int *n_resultado)
{
    actividad *aux;
    unsigned int contador = 0;
    unsigned int j = 0;

    if (dataptr == NULL || n_resultado == NULL) {
        printf("Error: puntero NULL\n");
        return NULL;
    }

    // Primero contamos cuantas actividades pertenecen a ese centro
    for (unsigned int i = 0; i < n_lineas; i++) {
        if (dataptr[i].centro == centro_elegido) {
            contador++;
        }
    }

    // Guardamos el numero de actividades encontradas
    *n_resultado = contador;

    // Si no hay actividades de ese centro, devolvemos NULL
    if (contador == 0) {
        printf("No se han encontrado actividades para ese centro\n");
        return NULL;
    }

    // Reservamos memoria solo para las actividades de ese centro
    aux = malloc(sizeof(actividad) * contador);

    if (aux == NULL) {
        printf("MEMORIA NO DISPONIBLE\n");
        return NULL;
    }

    // Copiamos en aux solamente las actividades del centro elegido
    for (unsigned int i = 0; i < n_lineas; i++) {
        if (dataptr[i].centro == centro_elegido) {
            aux[j] = dataptr[i];
            j++;
        }
    }

    // Ordenamos el vector aux por ocupacion
    qsort(aux, contador, sizeof(actividad), comparar_por_ocupacion);

    // Devolvemos el array ordenado
    return aux;
}