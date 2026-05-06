#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"

//Vamos a realizar una busqueda por 2 filtros, centro y actividad
actividad *buscar(actividad *dataptr, unsigned int n_lineas, uint32_t centro, uint32_t act,unsigned int *n_result)
{
    actividad *coincidencias;
    unsigned int i=0;
    unsigned int numero_coinc = 0;
    unsigned int contador = 0;
    for (i=0;i<n_lineas;i++)
    {
        if ((dataptr[i].centro == centro) && (dataptr[i].actividad == act))
        {
            contador++;
        }
    }
    coincidencias = malloc(sizeof(actividad) * contador);
    if (coincidencias == NULL) {
        *n_result = 0;
        return NULL;
    }
    contador=0;
    for (i=0;i<n_lineas;i++)
    {
        if ((dataptr[i].centro == centro) && (dataptr[i].actividad == act))
        {
            coincidencias[contador] = dataptr[i];
            contador++;
        }
    }
    *n_result = contador;
    return coincidencias;
}