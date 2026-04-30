#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"
#define SIZE_INCREMENT 10

actividad *read_csv(char *filename, unsigned int *lineas) {
  FILE *csv = fopen(filename, "r");
  actividad *dataptr = malloc(sizeof(actividad)*SIZE_INCREMENT);
  char linea[2048];
  char temp_str[5][128]; //strings que sirven de buffer para leer cada linea
  uint32_t h0, hf, m0, mf; //variables locales intermedias para poder leer el archivo
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
      capacidad = capacidad * 2; //asi el resizing de memoria se hace O(log(n)) veces, gastando menos operaciones que una suma O(n)
      actividad *tempptr = realloc(dataptr, capacidad*sizeof(actividad));
      if (tempptr == NULL) {
        printf("problema de resizing del buffer");
        free(dataptr);
        return NULL;
      }
      dataptr = tempptr;
    }
    
    sscanf(linea, "%u %u %u %15[^ ] %u:%u %u:%u %127[^ ] %127[^ ] %127[^ ] %u %u %u %127s[^\n]", 
        &dataptr[n].year, 
        &dataptr[n].mes,
        &dataptr[n].dia,
        temp_str[0], //dia de la semana
        &h0, //horas de inicio
        &m0, //minutos de inicio
        &hf, 
        &mf, 
        temp_str[1], //actividad
        temp_str[2], //modalidad
        temp_str[3], //centro
        &dataptr[n].total,
        &dataptr[n].ocupado, 
        &dataptr[n].libre,
        temp_str[4] //tipo
        );

    dataptr[n].t0 = h0*60 + m0; //calculamos el tiempo en minutos sumando horas y minutos del dato capturado
    dataptr[n].tf = hf*60 + mf;

    for (int i = 0; i < N_DIAS; i++) {
      if(strcmp(temp_str[0], dia[i]) == 0) {
        dataptr[n].dia_semana = i;
      }
    } for (int i = 0; i < N_CENTROS; i++) {
      if(strcmp(temp_str[3], centro[i]) == 0) {
        dataptr[n].centro = i;
      }
    } for (int i = 0; i < N_MODS; i++) {
      if(strcmp(temp_str[2], modalidad[i]) == 0) {
        dataptr[n].modalidad = i;
      }
    } for (int i = 0; i < N_ACTS; i++) {
      if(strcmp(temp_str[1], actividades[i]) == 0) {
        dataptr[n].actividad = i;
      }
    } for (int i = 0; i < N_TIPOS; i++) {
      if(strcmp(temp_str[4], tipo[i]) == 0) {
        dataptr[n].tipo = i;
      }
    }
    
    n++;
    printf("%s", linea);
  }
  *lineas = n; //devolvemos el numero de lineas que se han escrito (por referencia)

  fclose(csv);
  return(dataptr);
}
