#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nuklear.h" 
#include "reader.h"
#include "utilidades.h"
#include "gui.h"
#include "ordenar.h"
#include "busqueda.h"

// Funcion para renderizar el popup de analisis
static void render_popup_analisis(struct nk_context *ctx, struct_estado_app *estado) {
    if (estado->mostrar_popup_analisis) {
        struct nk_rect popup_bounds = nk_rect(250, 150, 500, 450);
        
        if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Análisis de Datos", 
                          NK_WINDOW_BORDER|NK_WINDOW_TITLE|NK_WINDOW_CLOSABLE,
                          popup_bounds)) 
        {
            if (estado->tipo_analisis == 0) { // Frecuencia Diaria
                nk_layout_row_dynamic(ctx, 25, 1);
                char titulo[128];
                snprintf(titulo, sizeof(titulo), "Actividad: %s", 
                        actividades[estado->actividad_analizada]);
                nk_label(ctx, titulo, NK_TEXT_CENTERED);
                
                // Tabla con encabezados
                nk_layout_row_dynamic(ctx, 25, 3);
                nk_label(ctx, "Día", NK_TEXT_CENTERED);
                nk_label(ctx, "Ocurrencias", NK_TEXT_CENTERED);
                nk_label(ctx, "Porcentaje", NK_TEXT_CENTERED);
                
                // Calcular total
                unsigned int total = 0;
                for (int i = 0; i < 31; i++) {
                    total += estado->frecuencias[i];
                }
                
                // Contenido scrollable
                nk_layout_row_dynamic(ctx, 300, 1);
                if (nk_group_begin(ctx, "FreqTable", NK_WINDOW_BORDER)) {
                    char buffer[64];
                    
                    for (int i = 0; i < 31; i++) {
                        if (estado->frecuencias[i] > 0) {
                            nk_layout_row_dynamic(ctx, 25, 3);
                            
                            // Día
                            snprintf(buffer, sizeof(buffer), "%d", i + 1);
                            nk_label(ctx, buffer, NK_TEXT_CENTERED);
                            
                            // Ocurrencias
                            snprintf(buffer, sizeof(buffer), "%u", estado->frecuencias[i]);
                            nk_label(ctx, buffer, NK_TEXT_CENTERED);
                            
                            // Porcentaje
                            float porcentaje = (estado->frecuencias[i] * 100.0f) / total;
                            snprintf(buffer, sizeof(buffer), "%.1f%%", porcentaje);
                            nk_label(ctx, buffer, NK_TEXT_CENTERED);
                        }
                    }
                    
                    nk_group_end(ctx);
                }
                
                // Total al final
                nk_layout_row_dynamic(ctx, 25, 1);
                char total_str[64];
                snprintf(total_str, sizeof(total_str), "Total: %u ocurrencias", total);
                nk_label(ctx, total_str, NK_TEXT_CENTERED);
                
            } else if (estado->tipo_analisis == 1) { // Más Popular
                nk_layout_row_dynamic(ctx, 25, 1);
                char titulo[128];
                snprintf(titulo, sizeof(titulo), "Centro: %s", 
                        centro[estado->centro_analizado]);
                nk_label(ctx, titulo, NK_TEXT_CENTERED);
                
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "", NK_TEXT_LEFT); // Espaciador
                
                nk_layout_row_dynamic(ctx, 25, 1);
                nk_label(ctx, "Actividad más popular:", NK_TEXT_LEFT);
                
                nk_layout_row_dynamic(ctx, 30, 1);
                if (estado->actividad_popular >= 0) {
                    char act_nombre[256];
                    snprintf(act_nombre, sizeof(act_nombre), "→ %s", 
                            actividades[estado->actividad_popular]);
                    nk_label(ctx, act_nombre, NK_TEXT_LEFT);
                } else {
                    nk_label(ctx, "No se encontraron datos", NK_TEXT_LEFT);
                }
            }
            
            // Botón cerrar
            nk_layout_row_dynamic(ctx, 30, 1);
            if (nk_button_label(ctx, "Cerrar")) {
                estado->mostrar_popup_analisis = 0;
                nk_popup_close(ctx);
            }
            
            nk_popup_end(ctx);
        } else {
            estado->mostrar_popup_analisis = 0;
        }
    }
}


void render_app(struct nk_context *ctx, actividad *dataptr, unsigned int n_lineas, struct_estado_app *estado) {
    if (nk_begin(ctx, "Visor de Actividades Deportivas", nk_rect(10, 10, 1200, 700),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_TITLE)) 
    {
        //Seccion de arriba (selectores para buscar)
        nk_layout_row_dynamic(ctx, 35, 4);

        //static ya que la funcion se llamara cada vez que se renderice, no queremos reinicializar la variable siempre
        static int centro_combo = 0;
        static int actividad_combo = 0;
        static int modo_combo = 0;

        const char *options[] = {"Frecuencia Diaria", "Más Popular", "Evolución Gráfica"};
        int seleccion_1 = 0;
        int seleccion_modo = 0;
        centro_combo = nk_combo(ctx, centro, N_CENTROS, centro_combo, 25, nk_vec2(200, 200));
        actividad_combo = nk_combo(ctx, actividades, N_ACTS, actividad_combo, 25, nk_vec2(200, 200));
        modo_combo = nk_combo(ctx, options, 3, modo_combo, 25, nk_vec2(200, 200));

        if (nk_button_label(ctx,"Ejecutar búsqueda"))
        {
            if (estado->datos_actuales != dataptr && estado->datos_actuales != NULL){
                free(estado->datos_actuales);
            }

            unsigned int resultados_busqueda = 0;
            actividad *Filtradas = buscar(dataptr,n_lineas,centro_combo,actividad_combo, &resultados_busqueda);

            if (Filtradas && resultados_busqueda > 0){
                estado -> datos_actuales = Filtradas;
                estado -> n_datos_actuales = resultados_busqueda;
                estado -> mostrar_favoritos = 0;
            } else {
                estado->datos_actuales = NULL;
                estado ->n_datos_actuales = 0;
            }
        }
        if (estado->datos_actuales != NULL && estado->datos_actuales != dataptr) {
            nk_layout_row_dynamic(ctx, 30, 1);

            if (nk_button_label(ctx, "VOLVER")) {
                free(estado->datos_actuales);
                estado->datos_actuales = NULL; 
                estado->n_datos_actuales = 0;
            }
    }
        
        if (nk_button_label(ctx, "Ejecutar Análisis")) {
            if (modo_combo == 0) { // Frecuencia Diaria
                frecuencia_diaria_actividad(dataptr, n_lineas, actividad_combo, 
                                           estado->frecuencias);
                estado->tipo_analisis = 0;
                estado->actividad_analizada = actividad_combo;
                estado->mostrar_popup_analisis = 1;
 
            } else if (modo_combo == 1) { // Más Popular
                estado->actividad_popular = actividad_popular(dataptr, n_lineas, centro_combo);
                estado->tipo_analisis = 1;
                estado->centro_analizado = centro_combo;
                estado->mostrar_popup_analisis = 1;
            }
        }

        //botones para las acciones
        nk_layout_row_dynamic(ctx, 30, 3);
        if (nk_button_label(ctx, "Ver Favoritos ⭐")) {
                    estado->mostrar_favoritos = 1;
        }
        if (estado->mostrar_favoritos == 1) {
            if (nk_button_label(ctx,"VOLVER")){
                estado->mostrar_favoritos = 0;
            }
        }
        if (nk_button_label(ctx, "Centros 100% Ocupación")) {
            unsigned int n_result = 0;
            actividad *llenos = centros_llenos(dataptr, n_lineas, &n_result);
            
            if (llenos && n_result > 0) {
                //liberar datos actuales si existen y no son los originales
                if (estado->datos_actuales != dataptr && estado->datos_actuales != NULL) {
                    free(estado->datos_actuales);
                }
                estado->datos_actuales = llenos;
                estado->n_datos_actuales = n_result;
                estado->mostrar_favoritos = 0;
                
                printf("Encontrados %u centros con 100%% ocupación\n", n_result);
            }
        }
        if (nk_button_label(ctx, "Ordenar por Ocupación")) {
            unsigned int n_result = 0;
    
            // Usar el centro seleccionado del combo
            actividad *ordenados = ordenar_actividades_centro_por_ocupacion(
                dataptr, 
                n_lineas, 
                centro_combo,  // Usar el centro seleccionado en el combo
                &n_result
            );
    
            if (ordenados && n_result > 0) {
                // Liberar datos anteriores si existen
                if (estado->datos_actuales != dataptr && estado->datos_actuales != NULL) {
                    free(estado->datos_actuales);
                }
        
                estado->datos_actuales = ordenados;
                estado->n_datos_actuales = n_result;
                estado->mostrar_favoritos = 0;
        
                printf("Ordenadas %u actividades del centro %s por ocupación\n", 
                       n_result, centro[centro_combo]);
            } else {
                printf("No se encontraron actividades para el centro seleccionado\n");
            }
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

            actividad *datos_mostrar = estado -> datos_actuales ? estado -> datos_actuales : dataptr;
            unsigned int n_mostrar = estado -> datos_actuales ? estado -> n_datos_actuales : n_lineas;
            
            for (unsigned int i = 0; i < n_mostrar; i++) {
                fill_row_data(row_data, datos_mostrar[i]);
                
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
                
                if (estado -> mostrar_favoritos == 0) {
                    if (nk_button_label(ctx, "F")) {
                        add_favoritos(dataptr, i, n_lineas);
                        estado->recargar_f=1;
                    }
                }
                else if (estado -> mostrar_favoritos == 1) {
                    if (nk_button_label(ctx, "NF")) {
                    if (eliminar_favoritos(datos_mostrar[i])==1)
                    estado->recargar_f = 1;
                    }
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
    strcpy(dest[6], modalidad[v.modalidad]);
    strcpy(dest[7], centro[v.centro]);
    sprintf(dest[8], "%d", v.total);
    sprintf(dest[9], "%d", v.ocupado);
    sprintf(dest[10], "%d", v.libre);
}
