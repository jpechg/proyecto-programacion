#include "reader.h"

//estado de actividades
int actividad_ocupada(actividad *dataptr, unsigned int i);

//analisis y filtrado
actividad *actividades_llenas(actividad *dataptr, unsigned int n_lineas, unsigned int *n_resultado);
actividad *ordenar_por_ocupacion(actividad *dataptr, unsigned int n_lineas, uint32_t centro, unsigned int *n_resultado);
void frecuencia_diaria_actividad(actividad *dataptr, unsigned int n_lineas, uint32_t actividad_id, unsigned int resultado[31]);
int actividad_popular(actividad *dataptr, unsigned int lineas, uint32_t c);

//gestion de favoritos (persistencia)
int add_favoritos(actividad *dataptr, uint32_t valor, unsigned int n_datos);
int longitud_favoritos();
actividad *leer_favoritos(int n_favoritos);
int eliminar_favoritos(actividad act_a_elim);
