#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"
//Esta funcion se encarga de comprobar si la actividad esta completa o no. Devuelve un verdadero o un falso.
int actividad_ocupada(actividad *dataptr, unsigned int i) {
    if (dataptr[i].libre == 0) {
        return 1;
    }
    return 0;
}
//Esta funcion nos permite agregar a nuestros favoritos alguna actividad que nos guste para no tener que andala buscando siempre.
int add_favoritos(actividad *dataptr,uint32_t valor,unsigned int n_datos)
{
    int i = 0;
    FILE *pf;
    pf = fopen("Favoritos.txt","a");
    if (pf == NULL)
    {
        printf("Ha habido un error");
        return -1;
    }
    uint32_t *campos = (uint32_t*)&dataptr[valor];
    for (i=0;i<9;i++) //9 son el numero de datos que queremos copiar en el favoritos
    {
        fprintf(pf,"%u,",campos[i]);
    }
    fprintf(pf,"\n");
    fclose(pf);
    return 1;
}
//Esta funcion hace lo mismo que la anterior pero ahora lo que hace es eliminar una actividad de favoritos.
int eliminar_favoritos(actividad *dataptr, unsigned int n_datos,uint32_t valor)
{
    char linea[2048];
    unsigned int i = 0;
    int j =0;
    FILE *pf;
    pf = fopen ("Favoritos.txt","w");
    if (pf == NULL)
    {
        printf("Ha habido un error");
        return -1;
    }
    while (fgets(linea,sizeof(linea),pf) != NULL)
    {
        if 
    }
    
    

}
//Esta funcion actividad comprueba cual es la actividad mas popular en cada centro.
int actividad_popular(actividad *dataptr, unsigned int lineas, uint32_t c) {
  unsigned int contador[N_ACTS] = {0};
  int popular = -1;
  unsigned int max = 0;

  for (unsigned int i = 0; i < lineas; i++) {
    if (dataptr[i].centro == c) {
      contador[dataptr[i].actividad] += dataptr[i].ocupado;
    }
  }

  for (int i = 0; i < N_ACTS; i++) {
    if (contador[i] > max) {
      max = contador[i];
      popular = i;
    }
  }

  return popular;
}