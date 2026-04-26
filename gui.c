#include <stdio.h>
#include <string.h>
#include "nuklear.h" 
#include "reader.h"
#include "gui.h"

void render_app(struct nk_context *ctx, actividad *dataptr) {
    if (nk_begin(ctx, "Visor de datos", nk_rect(0, 0, 1200, 500),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_TITLE)) 
    {
        nk_layout_row_dynamic(ctx, 20, 3);
        
        static char search_buffer[256];
        static int search_len;
        nk_edit_string(ctx, NK_EDIT_FIELD, search_buffer, &search_len, 255, nk_filter_default);

        const char *options[] = {"Opción A", "Opción B", "Opción C"};
        static int sel_1 = 0;
        static int sel_2 = 0;

        sel_1 = nk_combo(ctx, actividades, 185, sel_1, 25, nk_vec2(200, 200));
        sel_2 = nk_combo(ctx, options, 3, sel_2, 25, nk_vec2(200, 200));

        nk_layout_row_static(ctx, 30, 100, 10);
        nk_label(ctx, "Year", NK_TEXT_LEFT);
        nk_label(ctx, "M", NK_TEXT_LEFT);
        nk_label(ctx, "D", NK_TEXT_LEFT);
        nk_label(ctx, "Day", NK_TEXT_LEFT);
        nk_label(ctx, "Start", NK_TEXT_LEFT);
        nk_label(ctx, "End", NK_TEXT_LEFT);
        nk_label(ctx, "Type", NK_TEXT_LEFT);
        nk_label(ctx, "Note", NK_TEXT_LEFT);
        nk_label(ctx, "Loc", NK_TEXT_LEFT);
        nk_label(ctx, "ID", NK_TEXT_LEFT);

        nk_layout_row_dynamic(ctx, 9999, 1);
        char row_data[11][512];
        if (nk_group_begin(ctx, "TableRegion", NK_WINDOW_BORDER)) {
            nk_layout_row_static(ctx, 30, 100, 10);

            unsigned int n;
            for (int i = 0; i < 20; i++) {
                fill_row_data(row_data, dataptr[i]);
                for (int j = 0; j < 10; j++) {
                    nk_label(ctx, row_data[j], NK_TEXT_LEFT);
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
