//esta funcion lo que hace es primero ver que actividades pasan el filtro buscado.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"
typedef struct {
    char *filtro_actividad;
    char *filtro_centro;
    int dia_semana;
    int t0;
    int tf;
    int plazas;
} filtro;

unsigned int filtrar(const actividad *data, unsigned int n_data, const filtro *f, actividad *destino, unsigned int max_dest)
{
    for (unsigned int i=0; i<n_data;i++)
    {
        int pasa = 1;
        if (f->filtro_actividad != NULL)
        {
            char *nombre_tabla = actividades[data[i].actividad];
            if (strstr(nombre_tabla,f->filtro_actividad)==NULL)
            {
                pasa = 0;
            }
        }
    }
}