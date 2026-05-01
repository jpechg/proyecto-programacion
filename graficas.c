#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CENTROS 200
#define MAX_NOMBRE 100
#define TOP_N 10

typedef struct {
    char nombre[MAX_NOMBRE];
    int ocupacion_total;
} Centro;

// Esta función sirve para ordenar de mayor a menor.
int comparar(const void *a, const void *b) {
    return ((Centro*)b)->ocupacion_total - ((Centro*)a)->ocupacion_total;
}
// Creamos un archivo con todos los centros y sus plazas ocupadas.
void crear_archivo_datos() {
    FILE *f = fopen("datos.txt", "w");
    if (f == NULL) return;

    fprintf(f, "Francisco_Fernandez_Ochoa 0\n");
    fprintf(f, "Francisco_Fernandez_Ochoa 51\n");
    fprintf(f, "Francisco_Fernandez_Ochoa 37\n");
    fprintf(f, "La_Almudena 20\n");
    fprintf(f, "La_Fundi 30\n");
    fprintf(f, "Aluche 40\n");
    fprintf(f, "Felix_Rubio 12\n");
    fprintf(f, "Gallur 5\n");
    fprintf(f, "Gallur 30\n");
    fprintf(f, "Gallur 5\n");
    fprintf(f, "Gallur 0\n");
    fprintf(f, "La_Almudena 6\n");
    fprintf(f, "La_Chopera 5\n");
    fprintf(f, "Marques_de_Samaranch 30\n");
    fprintf(f, "Pradillo 0\n");
    fprintf(f, "Pradillo 22\n");
    fprintf(f, "Pradillo 0\n");
    fprintf(f, "Pradillo 0\n");
    fprintf(f, "Pradillo 0\n");
    fprintf(f, "Pradillo 0\n");
    fprintf(f, "Pradillo 17\n");
    fprintf(f, "Alfredo_Goyeneche 20\n");
    fprintf(f, "Alfredo_Goyeneche 12\n");
    fprintf(f, "Alfredo_Goyeneche 36\n");
    fprintf(f, "Alfredo_Goyeneche 4\n");
    fprintf(f, "Aluche 5\n");
    fprintf(f, "Aluche 4\n");
    fprintf(f, "Antonio_Diaz_Miguel 65\n");
    fprintf(f, "Barajas 0\n");
    fprintf(f, "Blanca_Fernandez_Ochoa 15\n");
    fprintf(f, "Blanca_Fernandez_Ochoa 31\n");
    fprintf(f, "Centro_Integrado_Arganzuela 10\n");
    fprintf(f, "Centro_Integrado_Arganzuela 8\n");
    fprintf(f, "Centro_Integrado_Arganzuela 8\n");
    fprintf(f, "Centro_Integrado_Arganzuela 6\n");
    fprintf(f, "Centro_Integrado_Arganzuela 4\n");
    fprintf(f, "Cerro_Almodovar 25\n");
    fprintf(f, "Cubo_Gym_Chamartin 10\n");
    fprintf(f, "Cubo_Gym_Las_Tablas 3\n");
    fprintf(f, "Cubo_Gym_Madrid_Rio 13\n");
    fprintf(f, "Cubo_Gym_Retiro 16\n");
    fprintf(f, "El_Espinillo 21\n");
    fprintf(f, "El_Espinillo 8\n");
    fprintf(f, "El_Quijote 9\n");
    fprintf(f, "Entrevias 27\n");
    fprintf(f, "Faustina_Valladolid 9\n");
    fprintf(f, "Faustina_Valladolid 23\n");
    fprintf(f, "Faustina_Valladolid 6\n");
    fprintf(f, "Felix_Rubio 1\n");
    fprintf(f, "Felix_Rubio 0\n");
    fprintf(f, "Fernando_Martin 23\n");
    fprintf(f, "Francisco_Fernandez_Ochoa 4\n");
    fprintf(f, "Fuente_del_Berro 0\n");
    fprintf(f, "Gimnasio_Moscardo 10\n");
    fprintf(f, "Gimnasio_Moscardo 20\n");
    fprintf(f, "Gimnasio_Moscardo 14\n");
    fprintf(f, "Gimnasio_Moscardo 0\n");
    fprintf(f, "Hortaleza 9\n");
    fprintf(f, "Hortaleza 2\n");
    fprintf(f, "Hortaleza 5\n");
    fprintf(f, "Hortaleza 28\n");
    fprintf(f, "Hortaleza 4\n");
    fprintf(f, "Jose_Maria_Cagigal 3\n");
    fprintf(f, "Jose_Maria_Cagigal 1\n");
    fprintf(f, "Jose_Maria_Cagigal 22\n");
    fprintf(f, "Jose_Maria_Cagigal 0\n");
    fprintf(f, "Juan_de_Dios_Roman 5\n");
    fprintf(f, "Juan_de_Dios_Roman 12\n");
    fprintf(f, "La_Almudena 14\n");
    fprintf(f, "La_Almudena 0\n");
    fprintf(f, "La_Elipa 24\n");
    fprintf(f, "La_Maso 0\n");
    fprintf(f, "La_Maso 20\n");
    fprintf(f, "La_Maso 7\n");
    fprintf(f, "La_Maso 12\n");
    fprintf(f, "La_Maso 7\n");
    fprintf(f, "Marques_de_Samaranch 18\n");
    fprintf(f, "Marques_de_Samaranch 24\n");
    fprintf(f, "Marques_de_Samaranch 7\n");
    fprintf(f, "Marques_de_Samaranch 5\n");
    fprintf(f, "Orcasitas 20\n");
    fprintf(f, "Orcasitas 3\n");
    fprintf(f, "Orcasur 19\n");
    fprintf(f, "Palomeras 8\n");
    fprintf(f, "Palomeras 9\n");
    fprintf(f, "Palomeras 2\n");
    fprintf(f, "Palomeras 3\n");
    fprintf(f, "Palomeras 30\n");
    fprintf(f, "Palomeras 1\n");
    fprintf(f, "Plata_y_Castanar 14\n");
    fprintf(f, "Plata_y_Castanar 4\n");
    fprintf(f, "Playa_Victoria 6\n");
    fprintf(f, "Playa_Victoria 15\n");
    fprintf(f, "Playa_Victoria 16\n");
    fprintf(f, "Pradillo 38\n");
    fprintf(f, "Pradillo 0\n");
    fprintf(f, "Pueblo_Nuevo 0\n");
    fprintf(f, "Pueblo_Nuevo 0\n");
    fprintf(f, "Raul_Gonzalez 0\n");
    fprintf(f, "San_Blas 12\n");
    fprintf(f, "San_Blas 7\n");
    fprintf(f, "San_Blas 2\n");
    fprintf(f, "San_Blas 0\n");
    fprintf(f, "San_Cristobal 55\n");
    fprintf(f, "Triangulo_de_Oro 9\n");
    fprintf(f, "Triangulo_de_Oro 4\n");
    fprintf(f, "Triangulo_de_Oro 66\n");
    fprintf(f, "Vicente_del_Bosque 20\n");
    fprintf(f, "Wilfred_Agbonavbare 15\n");
    fprintf(f, "Antonio_Diaz_Miguel 9\n");
    fprintf(f, "Antonio_Diaz_Miguel 1\n");
    fprintf(f, "Barajas 8\n");
    fprintf(f, "El_Espinillo 10\n");
    fprintf(f, "Gallur 7\n");
    fprintf(f, "La_Almudena 0\n");
    fprintf(f, "La_Maso 14\n");
    fprintf(f, "Las_Cruces 9\n");
    fprintf(f, "Las_Cruces 72\n");
    fprintf(f, "Francisco_Fernandez_Ochoa 24\n");

    fclose(f);
    printf("Archivo 'datos.txt' creado con exito.\n");
}

int main() {
    // 1. Crear el archivo de origen
    crear_archivo_datos();

    Centro centros[MAX_CENTROS];
    int total_unicos = 0;

    // 2. Abrimos el archivo creado y procesamos todos los datos.
    FILE *archivo = fopen("datos.txt", "r");
    if (!archivo) return 1;

    char nombre_aux[MAX_NOMBRE];
    int ocupacion_aux;

    while (fscanf(archivo, "%s %d", nombre_aux, &ocupacion_aux) == 2) {
        int encontrado = -1;
        for (int i = 0; i < total_unicos; i++) {
            if (strcmp(centros[i].nombre, nombre_aux) == 0) {
                encontrado = i;
                break;
            }
        }
        if (encontrado != -1) {
            centros[encontrado].ocupacion_total += ocupacion_aux;
        } else {
            strcpy(centros[total_unicos].nombre, nombre_aux);
            centros[total_unicos].ocupacion_total = ocupacion_aux;
            total_unicos++;
        }
    }
    fclose(archivo);

    // 3. A continuacion, ordenamos todos los datos.
    qsort(centros, total_unicos, sizeof(Centro), comparar);

    // 4. Esta funcion guarda los 10 centros mas ocupados para Gnuplot
    FILE *f_plot = fopen("ranking.dat", "w");
    int limite = (total_unicos < TOP_N) ? total_unicos : TOP_N;
    for (int i = 0; i < limite; i++) {
        fprintf(f_plot, "\"%s\" %d\n", centros[i].nombre, centros[i].ocupacion_total);
    }
    fclose(f_plot);

    // 5. Una vez tenemos los diez centros con mas plazas ocupadas, esta función crea la grafica con Gnuplot.
    FILE *f_script = fopen("config.gp", "w");
    fprintf(f_script, "set title 'Top 10 Centros con Mayor Ocupacion'\n");
    fprintf(f_script, "set ylabel 'Plazas Ocupadas (Total)'\n");
    fprintf(f_script, "set style fill solid\n");
    fprintf(f_script, "set xtics rotate by -45\n");
    fprintf(f_script, "plot 'ranking.dat' using 2:xtic(1) with boxes title 'Ocupacion'\n");
    fprintf(f_script, "pause -1 'Pulsa Enter para cerrar'\n");
    fclose(f_script);

    // 6. Ejecutamos la grafica.
    printf("Procesamiento finalizado. Mostrando grafica...\n");
    system("gnuplot config.gp");

    return 0;
}