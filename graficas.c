#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "reader.h" 
#include "graficas.h"

//funcion para qsort, que compara la ocupacion de 2 actividades
static int comparar_actividades(const void *a, const void *b) {
    ResultadoActividad *resA = (ResultadoActividad *)a;
    ResultadoActividad *resB = (ResultadoActividad *)b;
    if (resB->ocupacion_total > resA->ocupacion_total) return 1;
    if (resB->ocupacion_total < resA->ocupacion_total) return -1;
    return 0;
}

void crear_grafica_top_actividades(actividad *dataptr, unsigned int n_lineas, uint32_t id_centro) {
    if (id_centro >= N_CENTROS) {
        printf("ID de centro no válido.\n");
        return;
    }

    //inicializamos array de resultados para todas las actividades posibles
    ResultadoActividad resultados[N_ACTS];
    for (int i = 0; i < N_ACTS; i++) {
        resultados[i].nombre_actividad = actividades[i];
        resultados[i].ocupacion_total = 0;
    }

    //filtramos por el centro elegido y sumamos ocupación por actividad
    int datos_encontrados = 0;
    for (unsigned int i = 0; i < n_lineas; i++) {
        if (dataptr[i].centro == id_centro) {
            uint32_t idx_act = dataptr[i].actividad;
            if (idx_act < N_ACTS) {
                resultados[idx_act].ocupacion_total += dataptr[i].ocupado;
                datos_encontrados = 1;
            }
        }
    }

    if (!datos_encontrados) {
        printf("No hay datos para el centro: %s\n", centro[id_centro]);
        return;
    }

    //ordenamos para obtener las más ocupadas
    qsort(resultados, N_ACTS, sizeof(ResultadoActividad), comparar_actividades);

    //escribimos datos para Gnuplot (Top 10)
    FILE *f_plot = fopen("top_actividades.dat", "w");
    if (!f_plot) return;
    for (int i = 0; i < TOP_N_ACT; i++) {
        // Solo escribimos si la ocupación es mayor que cero
        if (resultados[i].ocupacion_total > 0) {
            fprintf(f_plot, "\"%s\" %u\n", resultados[i].nombre_actividad, resultados[i].ocupacion_total);
        }
    }
    fclose(f_plot);
    //generamos la configuracion que luego correra gnuplot para generar el grafico
    FILE *f_script = fopen("config_act.gp", "w");
    if (!f_script) return;

    //definimos el terminal con 'noenhanced' para evitar problemas con guiones bajos (_)
    fprintf(f_script, "set terminal pngcairo size 1200,800 font 'Verdana,13' noenhanced\n");
    fprintf(f_script, "set output \"grafico.png\"\n");

    fprintf(f_script, "set title 'Top 10 Actividades en %s' font 'Verdana,22' offset 0,1\n", centro[id_centro]);    
    fprintf(f_script, "set ylabel 'Plazas Ocupadas' font 'Verdana,14'\n");

    fprintf(f_script, "set bmargin 15\n");
    fprintf(f_script, "set lmargin 12\n");

    fprintf(f_script, "set xtics rotate by -45 left font 'Verdana,12' offset 0,0\n");

    fprintf(f_script, "set grid y lc rgb '#eeeeee'\n");
    fprintf(f_script, "set style fill solid 0.8 border -1\n");
    fprintf(f_script, "set boxwidth 0.7\n");

    fprintf(f_script, "plot 'top_actividades.dat' using 2:xtic(1) with boxes lc rgb '#7fb3d5' notitle\n");

    fclose(f_script);

    printf("Generando grafica...\n");
    system("gnuplot\\bin\\gnuplot.exe config_act.gp"); //generamos el grafico con la configuracion antes escrita
    system("start grafico.png"); //mostramos el grafico
}
