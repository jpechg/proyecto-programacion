#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "reader.h" 

#define TOP_N_ACT 10

typedef struct {
    const char *nombre_actividad;
    uint32_t ocupacion_total;
} ResultadoActividad;

void crear_grafica_top_actividades(actividad *dataptr, unsigned int n_lineas, uint32_t id_centro);
