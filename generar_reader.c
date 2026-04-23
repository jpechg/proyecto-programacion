#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 500
#define MAX_STR_LEN 256

// Función auxiliar para añadir strings únicos a un array (para generar los enums/arrays)
int add_unique(char items[][MAX_STR_LEN], int *count, char *new_item) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(items[i], new_item) == 0) return i;
    }
    if (*count < MAX_ITEMS) {
        strcpy(items[*count], new_item);
        (*count)++;
        return *count - 1;
    }
    return -1;
}

int main() {
    FILE *csv = fopen("dataset.csv", "r");
    if (!csv) {
        perror("Error al abrir dataset.csv");
        return 1;
    }

    char line[2048];
    char d_sem[MAX_STR_LEN], centro[MAX_STR_LEN], mod[MAX_STR_LEN], act[MAX_STR_LEN], tipo[MAX_STR_LEN];
    
    // Arrays para recolectar valores únicos
    char lista_dias[7][MAX_STR_LEN]; int n_dias = 0;
    char lista_centros[MAX_ITEMS][MAX_STR_LEN]; int n_centros = 0;
    char lista_mods[MAX_ITEMS][MAX_STR_LEN]; int n_mods = 0;
    char lista_acts[MAX_ITEMS][MAX_STR_LEN]; int n_acts = 0;
    char lista_tipos[MAX_ITEMS][MAX_STR_LEN]; int n_tipos = 0;

    // Saltar cabecera
    fgets(line, sizeof(line), csv);

    // Variables temporales para sscanf
    unsigned int y, m, d, h0, mi0, hf, mif, tot, ocu, lib;

    while (fgets(line, sizeof(line), csv)) {
        int res = sscanf(line, "%u %u %u %s %u:%u %u:%u %s %s %s %u %u %u %s", 
               &y, &m, &d, d_sem, &h0, &mi0, &hf, &mif, act, mod, centro, &tot, &ocu, &lib, tipo);
        
        if (res >= 15) {
            add_unique(lista_dias, &n_dias, d_sem);
            add_unique(lista_centros, &n_centros, centro);
            add_unique(lista_mods, &n_mods, mod);
            add_unique(lista_acts, &n_acts, act);
            add_unique(lista_tipos, &n_tipos, tipo);
        }
    }
    fclose(csv);

    //creamos y empezamos a escribir el archivo
    FILE *h = fopen("reader.h", "w");
    fprintf(h, "#ifndef READER_H\n#define READER_H\n\n");
    fprintf(h, "#include <stdint.h>\n\n");

    // Escribir los arrays de strings
    auto void print_array(FILE* f, char* name, char items[][MAX_STR_LEN], int count) {
        fprintf(f, "char *%s[%d] = {", name, count);
        for (int i = 0; i < count; i++) {
            fprintf(f, "\"%s\"%s", items[i], (i == count - 1) ? "" : ", ");
        }
        fprintf(f, "};\n");
    }

    fprintf(h, "char *dia[%d] = {", n_dias);
    for(int i=0; i<n_dias; i++) fprintf(h, "\"%s\"%s", lista_dias[i], i==n_dias-1?"":", ");
    fprintf(h, "};\n");

    fprintf(h, "char *centro[%d] = {", n_centros);
    for(int i=0; i<n_centros; i++) fprintf(h, "\"%s\"%s", lista_centros[i], i==n_centros-1?"":", ");
    fprintf(h, "};\n");

    fprintf(h, "char *modalidad[%d] = {", n_mods);
    for(int i=0; i<n_mods; i++) fprintf(h, "\"%s\"%s", lista_mods[i], i==n_mods-1?"":", ");
    fprintf(h, "};\n");

    fprintf(h, "char *actividades[%d] = {", n_acts);
    for(int i=0; i<n_acts; i++) fprintf(h, "\"%s\"%s", lista_acts[i], i==n_acts-1?"":", ");
    fprintf(h, "};\n");

    fprintf(h, "char *tipo[%d] = {", n_tipos);
    for(int i=0; i<n_tipos; i++) fprintf(h, "\"%s\"%s", lista_tipos[i], i==n_tipos-1?"":", ");
    fprintf(h, "};\n\n");

    // Definición de la estructura
    fprintf(h, "typedef struct {\n");
    fprintf(h, "  uint32_t year, mes, dia, dia_semana; //fechas\n");
    fprintf(h, "  uint32_t t0, tf //tiempo en minutos totales desde las 00:00;\n");
    fprintf(h, "  uint32_t actividad, modalidad, centro; //indices sobre los arrays de cada elemento\n");
    fprintf(h, "  uint32_t total, ocupado, libre, tipo; //contadores\n");
    fprintf(h, "} actividad;\n\n");

    fprintf(h, "actividad *read_csv(char *filename, unsigned int *lineas);\n\n");
    fprintf(h, "#endif\n");
    
    fclose(h);
    printf("reader.h generado exitosamente con %d actividades y %d centros.\n", n_acts, n_centros);

    return 0;
}
