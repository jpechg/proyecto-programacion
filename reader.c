#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_INCREMENT 10
char *dia[7] =  {"domingo", "lunes", "martes", "miercoles", "jueves", "viernes", "sabado"}; //el domingo es 0 ya que es el 7o dia

typedef struct {
  int year;
  int mes;
  int dia;
  int dia_semana;
  int t0; //numero de minutos desde las 00:00
  int tf;
  char actividad[128]; //TODO: seria ideal usar un enum, ya que hace un uso mas eficiente de la memoria
  char centro[128];
  int total;
  int ocupado;
  int libre;
  char tipo[128];
} actividad;

actividad *read_csv(char *filename);

actividad *read_csv(char *filename) {
  FILE *csv = fopen(filename, "r");
  actividad *dataptr = malloc(sizeof(actividad)*SIZE_INCREMENT);
  char linea[2048];
  char dia_semana_str[64];
  int h0, hf, m0, mf; //variables locales intermedias para poder leer el archivo
  unsigned int n = 0; //como el tamaño del archivo es de en torno a 5k lineas, nos vale de sobra con un unsigned int (64k)
  unsigned int capacidad = SIZE_INCREMENT;
  
  if (csv == NULL) {
    printf("no se ha podido abrir el archivo");
    free(dataptr);
    return NULL;
  }

  fgets(linea, sizeof(linea), csv); //quitamos la primera linea que no contiene información
  while(fgets(linea, sizeof(linea), csv)) {
    if (n >= capacidad) {
      actividad *tempptr = realloc(dataptr, capacidad*sizeof(actividad));
      capacidad = capacidad * 2; //asi el resizing de memoria se hace en O(log(n)), gastando menos operaciones que una suma O(n)
      if (tempptr == NULL) {
        printf("problema de resizing del buffer");
        free(dataptr);
        return NULL;
      }
    }
    
    sscanf(linea, "%d %d %d %15s %d:%d %d:%d %127s %127s %d %d %d %127s", 
        &dataptr[n].year, 
        &dataptr[n].mes,
        &dataptr[n].dia,
        dia_semana_str,
        &h0, 
        &m0, 
        &hf, 
        &mf, 
        dataptr[n].actividad,
        dataptr[n].centro,
        &dataptr[n].total,
        &dataptr[n].ocupado, 
        &dataptr[n].libre, 
        dataptr[n].tipo);

    dataptr[n].t0 = h0*60 + m0;
    dataptr[n].tf = hf*60 + mf;

    for (int i = 0; i < 7; i++) {
      if(strcmp(dia_semana_str, dia[i]) == 0) {
        dataptr[n].dia_semana = i;
      }
    }

    n++;
    printf("%s", linea);
  }
  fclose(csv);
  return(dataptr);
}

int main(void) {
  read_csv("dataset_muestra.csv");
//  printf("%li", sizeof(actividad));
  return 0;
}
