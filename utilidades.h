#include "reader.h"

int actividad_ocupada(actividad *dataptr, unsigned int i);
int add_favoritos(actividad *dataptr,uint32_t valor,unsigned int n_datos);
int longitud_favoritos();
int leer_favoritos(int n_favoritos);
int eliminar_favoritos(uint32_t valor);
int actividad_popular(actividad *dataptr, unsigned int lineas, uint32_t c);
