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
    int modo_analisis; // 0: Frecuencia, 1: Popular, 2: Gráfica

    int mostrar_popup_analisis;
    char titulo_popup[256];
    char contenido_popup[2048];
} struct_estado_app;

void render_app(struct nk_context *ctx, actividad *dataptr, unsigned int n_lineas, struct_estado_app *estado);
void fill_row_data(char dest[11][512], actividad v);
