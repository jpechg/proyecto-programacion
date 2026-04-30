#include <stdio.h>
#include <string.h>
#include "nuklear.h" 
#include "reader.h"
#include "gui.h"

void render_app(struct nk_context *ctx, actividad *dataptr) {
    if (nk_begin(ctx, "Visor de Actividades Deportivas", nk_rect(10, 10, 1200, 700),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_TITLE)) 
    {
        //Seccion de arriba (selectores para buscar)
        nk_layout_row_dynamic(ctx, 35, 4);
        //static ya que la funcion se llamara cada vez que se renderice, no queremos reinicializar la variable siempre
        static char buffer_busqueda[256];
        static int len_busqueda;
        nk_edit_string(ctx, NK_EDIT_FIELD, buffer_busqueda, &len_busqueda, 255, nk_filter_default);
        const char *options[] = {"Frecuencia Diaria", "Más Popular", "Evolución Gráfica"};
        int seleccion_1 = 0;
        int seleccion_modo = 0;
        seleccion_1 = nk_combo(ctx, actividades, 185, seleccion_1, 25, nk_vec2(200, 200));
        seleccion_modo = nk_combo(ctx, options, 3, seleccion_modo, 25, nk_vec2(200, 200));

        if (nk_button_label(ctx, "Ejecutar Análisis")) {
            //TODO: hacer el analisis de los datos mediante las funciones de busqueda
        }

        //Botones para las acciones
        nk_layout_row_dynamic(ctx, 30, 3);
        if (nk_button_label(ctx, "Ver Favoritos ⭐")) {
            //rellenar con los indices de ver_favoritos

        }
        if (nk_button_label(ctx, "Centros 100% Ocupación")) {
            //rellenar con la funcion de utilidades.c
        }
        if (nk_button_label(ctx, "Ordenar por Ocupación")) {
            //hacer un qsort con la ocupacion, y si eso filtrar por centro
        }

        nk_layout_row_template_begin(ctx, 30);
        nk_layout_row_template_push_static(ctx, 50);  // año
        nk_layout_row_template_push_static(ctx, 30);  // mes
        nk_layout_row_template_push_static(ctx, 30);  // dia
        nk_layout_row_template_push_static(ctx, 80);  // dia de la semana
        nk_layout_row_template_push_static(ctx, 60);  // hora inicio
        nk_layout_row_template_push_variable(ctx, 120); // nombre de actividad (longitud dinamica)
        nk_layout_row_template_push_variable(ctx, 100); // modalidad
        nk_layout_row_template_push_variable(ctx, 150); //centro
        nk_layout_row_template_push_static(ctx, 60);  // ocupacion total
        nk_layout_row_template_push_static(ctx, 60);  // ocupacion libre
        nk_layout_row_template_push_static(ctx, 60);  // ocupacion ocupada
        nk_layout_row_template_push_static(ctx, 80);  // favoritos
        nk_layout_row_template_end(ctx);

        nk_label(ctx, "Año", NK_TEXT_LEFT);
        nk_label(ctx, "M", NK_TEXT_LEFT);
        nk_label(ctx, "D", NK_TEXT_LEFT);
        nk_label(ctx, "Dia", NK_TEXT_LEFT);
        nk_label(ctx, "Inicio", NK_TEXT_LEFT);
        nk_label(ctx, "Actividad", NK_TEXT_LEFT);
        nk_label(ctx, "Modalidad", NK_TEXT_LEFT);
        nk_label(ctx, "Centro", NK_TEXT_LEFT);
        nk_label(ctx, "total", NK_TEXT_LEFT);
        nk_label(ctx, "libre", NK_TEXT_LEFT);
        nk_label(ctx, "ocupado", NK_TEXT_LEFT);
        nk_label(ctx, "Fav", NK_TEXT_LEFT);

        // --- TABLE CONTENT ---
        nk_layout_row_dynamic(ctx, 500, 1);
        if (nk_group_begin(ctx, "TableRegion", NK_WINDOW_BORDER)) {
            char row_data[11][512];
            
            for (int i = 0; i < 20; i++) {
                fill_row_data(row_data, dataptr[i]);
                
                // Replicate the template for the rows
                nk_layout_row_template_begin(ctx, 30);
                nk_layout_row_template_push_static(ctx, 50);
                nk_layout_row_template_push_static(ctx, 30);
                nk_layout_row_template_push_static(ctx, 30);
                nk_layout_row_template_push_static(ctx, 80);
                nk_layout_row_template_push_static(ctx, 60);
                nk_layout_row_template_push_variable(ctx, 120);
                nk_layout_row_template_push_variable(ctx, 100);
                nk_layout_row_template_push_variable(ctx, 150);
                nk_layout_row_template_push_static(ctx, 60);
                nk_layout_row_template_push_static(ctx, 60);
                nk_layout_row_template_push_static(ctx, 60);
                nk_layout_row_template_push_static(ctx, 80);
                nk_layout_row_template_end(ctx);

                for (int j = 0; j < 11; j++) {
                    nk_label(ctx, row_data[j], NK_TEXT_LEFT);
                }
                
                if (nk_button_label(ctx, "⭐")) {
                    //llamar a la funcion de guardar favoritos
                }
            }
            nk_group_end(ctx);
        }
    }
    nk_end(ctx);
}

void fill_row_data(char dest[11][512], actividad v) {
    sprintf(dest[0], "%d", v.year);
    sprintf(dest[1], "%d", v.mes);
    sprintf(dest[2], "%d", v.dia);
    strcpy(dest[3], dia[v.dia_semana]);
    sprintf(dest[4], "%02d:%02d", v.t0 / 60, v.t0 % 60);
    strcpy(dest[5], actividades[v.actividad]);
    strcpy(dest[6], actividades[v.modalidad]);
    strcpy(dest[7], actividades[v.centro]);
    sprintf(dest[8], "%d", v.total);
    sprintf(dest[9], "%d", v.ocupado);
    sprintf(dest[10], "%d", v.libre);
}
