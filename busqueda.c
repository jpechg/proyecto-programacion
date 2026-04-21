//esta funcion lo que hace es buscar por un filtro(mes,año,actividad...) máximo de dos condiciones.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"
int *buscar_actividad (actividad *data,unsigned int n_data,int *coincidentes,int indice, uint32_t valor)
{
    int *indices_coincidentes = malloc(sizeof(int)*n_data);
    if (indices_coincidentes == NULL) {
        printf("Ha habido un error");
        return NULL;
    }
    int coincidencias = 0;
    for (int i=0;i<n_data; i++)
    {
        uint32_t *campos = (uint32_t*)&data[i]; //esto esta trasformando el struct en un vector
        //el struct solo contiene enteros, asi que se puede tratar de esta forma
        if (campos[indice] == valor)
        {
            indices_coincidentes[coincidencias] = i;
            coincidencias++;
        }
    }
    *coincidentes = coincidencias;
    return indices_coincidentes;
}
int filtrado_doble(actividad *data,int *indices_entrada, int n_entrada,int campo,uint32_t valor, int *indices_salida)
{
    int n_final = 0;
    for (int i =0;i<n_entrada;i++)
    {
        uint32_t *campos = (uint32_t*)&data[indices_entrada[i]];
        if (campos[campo] == valor)
        {
            indices_salida[n_final] = indices_entrada[i];
            n_final++;
        }
    }
    return n_final;
}


