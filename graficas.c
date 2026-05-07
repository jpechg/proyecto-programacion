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

//funcion para qsort, que compara la ocupacion de 2 actividades
int comparar_actividades(const void *a, const void *b) {
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

    // 1) Inicializamos array de resultados para todas las actividades posibles
    ResultadoActividad resultados[N_ACTS];
    for (int i = 0; i < N_ACTS; i++) {
        resultados[i].nombre_actividad = actividades[i];
        resultados[i].ocupacion_total = 0;
    }

    // 2) Filtramos por el centro elegido y sumamos ocupación por actividad
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

    // 3) Ordenamos para obtener las más ocupadas
    qsort(resultados, N_ACTS, sizeof(ResultadoActividad), comparar_actividades);

    // 4) Escribimos datos para Gnuplot (Top 10)
    FILE *f_plot = fopen("top_actividades.dat", "w");
    if (!f_plot) return;
    for (int i = 0; i < TOP_N_ACT; i++) {
        // Solo escribimos si la ocupación es mayor que cero
        if (resultados[i].ocupacion_total > 0) {
            fprintf(f_plot, "\"%s\" %u\n", resultados[i].nombre_actividad, resultados[i].ocupacion_total);
        }
    }
    fclose(f_plot);

// 5) Script de Gnuplot robusto con persistencia y fuentes grandes
    FILE *f_script = fopen("config_act.gp", "w");
    if (!f_script) return;

    // Definimos el terminal para que la ventana sea grande (1200x800 píxeles)
    // Esto evita que las fuentes grandes amontonen el contenido
    fprintf(f_script, "set terminal qt size 1200,800 font 'Arial,12'\n");

    fprintf(f_script, "set title 'Top 10 Actividades en %s' font 'Arial,18'\n", centro[id_centro]);
    fprintf(f_script, "set ylabel 'Plazas Ocupadas' font 'Arial,14'\n");
    
    // Configuración de etiquetas del eje X con fuente grande y rotación
    fprintf(f_script, "set xtics rotate by -45 font 'Arial,12' offset 0,-1.5\n");
    
    // Aumentamos los márgenes significativamente para que no se corte nada
    fprintf(f_script, "set bmargin 15\n"); 
    fprintf(f_script, "set lmargin 10\n"); 
    
    fprintf(f_script, "set style fill solid 0.8 border -1\n");
    fprintf(f_script, "set boxwidth 0.6\n");
    fprintf(f_script, "plot 'top_actividades.dat' using 2:xtic(1) with boxes notitle\n");
    
    fclose(f_script);

    // USAMOS EL FLAG -persist PARA QUE LA VENTANA NO SE CIERRE
    printf("Generando grafica... Cierra la ventana de Gnuplot para continuar.\n");
    system("gnuplot -persist config_act.gp");
}

int main() {
    unsigned int n_lineas = 0;
    actividad *dataptr = read_csv("dataset.csv", &n_lineas);

    if (dataptr != NULL && n_lineas > 0) {
        // Ejemplo: Top 10 para el centro "Francisco_Fernandez_Ochoa" (ID 0)
        crear_grafica_top_actividades(dataptr, n_lineas, 0);
        free(dataptr);
    } else {
        printf("Error al cargar los datos.\n");
    }

    return 0;
}
