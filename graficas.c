#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "reader.h" 

#define TOP_N 10

// Esta estructura sirve para agrupar los resultados finales.
typedef struct {
    const char *nombre;
    uint32_t ocupacion_total;
} ResultadoCentro;

// Ahora ordenamos de mayor a menor ocupacion.
int comparar_resultados(const void *a, const void *b) {
    ResultadoCentro *resA = (ResultadoCentro *)a;
    ResultadoCentro *resB = (ResultadoCentro *)b;
    return resB->ocupacion_total - resA->ocupacion_total;
}

// Creamos la gráfica usando el dataptr de actividades.
void crear_grafica(actividad *dataptr, unsigned int n_lineas) {
    // 1) Creamos un array para acumular ocupación por cada uno de los 65 centros
    ResultadoCentro resultados[N_CENTROS];
    
    // 2) Inicializamos el array de resultados con los nombres del reader.h
    for (int i = 0; i < N_CENTROS; i++) {
        resultados[i].nombre = centro[i];
        resultados[i].ocupacion_total = 0;
    }

    // 3) Procesamos el dataptr, sumamos la ocupación acumulada por cada centro
    for (unsigned int i = 0; i < n_lineas; i++) {
        uint32_t idx_centro = dataptr[i].centro;
        if (idx_centro < N_CENTROS) {
            resultados[idx_centro].ocupacion_total += dataptr[i].ocupado;
        }
    }

    // 4) Ordenamos los resultados de mayor a menor
    qsort(resultados, N_CENTROS, sizeof(ResultadoCentro), comparar_resultados);

    // 5) Escribimos los datos para Gnuplot (Top 10)
    FILE *f_plot = fopen("ranking.dat", "w");
    if (!f_plot) return;

    for (int i = 0; i < TOP_N; i++) {
        fprintf(f_plot, "\"%s\" %u\n", resultados[i].nombre, resultados[i].ocupacion_total);
    }
    fclose(f_plot);

    // 6) Configuramos la grafica para Gnuplot.
    FILE *f_script = fopen("config.gp", "w");
    if (!f_script) return;

    fprintf(f_script, "set title 'Top 10 Centros con Mayor Ocupacion'\n");
    fprintf(f_script, "set ylabel 'Plazas Ocupadas (Total)'\n");
    fprintf(f_script, "set style fill solid 0.7 border -1\n");
    fprintf(f_script, "set xtics rotate by -45\n");
    fprintf(f_script, "set bmargin 10\n"); // Margen extra para nombres largos
    fprintf(f_script, "plot 'ranking.dat' using 2:xtic(1) with boxes title 'Ocupacion'\n");
    fprintf(f_script, "pause -1 'Pulsa Enter para cerrar'\n");
    fclose(f_script);

    // 7) Ejecutamos Gnuplot.
    printf("Procesando %u registros y generando grafica...\n", n_lineas);
    system("gnuplot config.gp");
}

int main() {
    unsigned int n_lineas = 0;
    
    // dataptr recibirá el malloc que hacemos en read_csv.
    actividad *dataptr = read_csv("datos.csv", &n_lineas);

    if (dataptr != NULL && n_lineas > 0) {
        // Generamos la gráfica usando el puntero a la memoria
        crear_grafica(dataptr, n_lineas);

        // Liberamos la memoria.
        free(dataptr);
    } else {
        printf("Error: No se pudieron cargar datos desde el archivo.\n");
    }

    return 0;
}