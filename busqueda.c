//esta funcion lo que hace es primero ver que actividades pasan el filtro buscado.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"
void buscar_actividad (actividad *data,unsigned int n_data, const char *busqueda)
{
    int coincidentes[185];
    int coincidencias = 0;

    for (unsigned int i = 0;i<185;i++)
    {
        if (strstr(actividades[i],busqueda) != NULL) //strstr lo que hace es comparar subcadenas, "nado" coincide con "nado_libre"
        {
            coincidentes[coincidencias++] = i; //si por ejemplo el numero 21 coincide lo apuntamos en coincidentes[0] y luego suma 1.
        }
    }
    if (coincidencias == 0)
    {
        printf("no se ha encontrado ninguna coincidencia para '%s'",busqueda);
        return; //como es un void no retorna nada, solo sale de la función
    } else
    {
        printf("Hay %d coincidencia para '%s'",coincidencias, busqueda);
    }
    //Ahora queremos mostrar los resultados
    unsigned int resultados = 0;

    for (unsigned int i = 0;i<n_data;i++)
    {
        for (int j = 0;j<coincidencias;j++)
        {
            if ( data[i].actividad == coincidentes[j])
            {
                printf("centro: %s\n",centro[data[i].centro]);
                printf ("Actividad: %s\n", actividades[data[i].actividad]);
                //alomejor, dependiendo de la interfaz de usuario queremos guardarlos en un struct en vez de printear
            }
        }
    }
    

}