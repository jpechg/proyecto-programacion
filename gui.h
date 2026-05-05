#include <stdio.h>
#include <string.h>
#include <math.h>
#include "reader.h"

typedef struct {
    actividad *datos_actuales;
    unsigned int n_datos_actuales;
    int mostrar_favoritos;
    
    // Buffers para filtros
    int centro_seleccionado;
    int actividad_seleccionada;

    int mostrar_popup_analisis;
    int tipo_analisis; // 0: frecuencia, 1: popular
    unsigned int frecuencias[N_DIAS]; // Para frecuencia diaria
    int actividad_analizada;
    int centro_analizado;
    int actividad_popular;
} struct_estado_app;

void render_app(struct nk_context *ctx, actividad *dataptr, unsigned int n_lineas, struct_estado_app *estado);
void fill_row_data(char dest[11][512], actividad v);
