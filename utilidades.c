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
    //valor es el indice del struct a guardar
    int i = 0;
    FILE *pf;
    pf = fopen("Favoritos.txt","a");
    if (pf == NULL)
    {
        printf("Ha habido un error al leer Favoritos.txt\n");
        return -1;
    }
    uint32_t *campos = (uint32_t*)&dataptr[valor];
    for (i=0;i<13;i++) //13 son el numero de datos que queremos copiar en el favoritos
    {
        fprintf(pf,"%u,",campos[i]);
    }
    fprintf(pf,"\n");
    fclose(pf);
    return 1;
}
int longitud_favoritos()
{
  char linea[2048];
  unsigned int i = 0;
  FILE *pf;
  pf = fopen("Favoritos.txt","r");
  if (pf == NULL)
    {
        printf("Ha habido un error al leer Favoritos.txt\n");
        return -1;
    }
  while (fgets(linea,sizeof(linea),pf))
  {
    i++;
  }
  fclose(pf);
  return i;
}
actividad *leer_favoritos()
{
  actividad *aux;
  FILE *pf;
  int n_favoritos = longitud_favoritos();
  pf = fopen("Favoritos.txt","r");
    if (pf == NULL)
    {
        printf("Ha habido un error al leer Favoritos.txt\n");
        return NULL;
    }
  unsigned int i=0;
  aux = malloc(sizeof(actividad) * n_favoritos);
  if (aux == NULL)
  {
    printf ("MEMORIA NO DISPONIBLE\n");
    exit(-1);
  }
  while (i<n_favoritos && fscanf(pf,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,\n",
        &aux[i].year,
        &aux[i].mes,
        &aux[i].dia,
        &aux[i].dia_semana,
        &aux[i].t0,
        &aux[i].tf,
        &aux[i].actividad,
        &aux[i].modalidad,
        &aux[i].centro,
        &aux[i].total,
        &aux[i].ocupado,
        &aux[i].libre,
        &aux[i].tipo) == 13)
    {
      i++;
}
fclose(pf); 
return aux;
}
//Esta funcion hace lo mismo que la anterior pero ahora lo que hace es eliminar una actividad de favoritos.
int eliminar_favoritos(actividad act_a_elim)
{
    char linea[2048];
    unsigned int lineas = 0;
    unsigned int i = 0;
    unsigned int contador = longitud_favoritos();
    actividad aux;
    int j =0;
    FILE *pf;
    FILE *pf_aux;
    int coincidencia = 0;
    pf = fopen("Favoritos.txt","r");
    if (pf == NULL)
    {
        printf("Ha habido un error al leer Favoritos.txt\n");
        return -1;
    }
    pf_aux = fopen("Favoritos_aux.txt","w");
    if (pf_aux == NULL)
    {
        printf("Ha habido un error al leer Favoritos_aux.txt\n");
        return -1;
    }
    while (fscanf(pf,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,\n",
        &aux.year,
        &aux.mes,
        &aux.dia,
        &aux.dia_semana,
        &aux.t0,
        &aux.tf,
        &aux.actividad,
        &aux.modalidad,
        &aux.centro,
        &aux.total,
        &aux.ocupado,
        &aux.libre,
        &aux.tipo) == 13)
    {
      uint32_t *campos = (uint32_t*)&aux;
      uint32_t *campos2 = (uint32_t*)&act_a_elim;
      for(i=0;i<13;i++)
      {
        if (campos[i]==campos2[i])
        {

        }
      }
      //if (aux.actividad != act_a_elim)
      {
        uint32_t *campos = (uint32_t*)&aux;
        for (i=0;i<13;i++)
        {
          fprintf(pf_aux,"%u,",campos[i]);
        }
        fprintf(pf_aux,"\n");
      }
        //else if (aux.actividad == valor)
      {
        coincidencia = 1;
      }
    }
    rewind(pf_aux);
    while (fgets(linea,sizeof(linea),pf_aux))
    {
      lineas++;
    }
    if (lineas == (contador - 1))
    {
      remove("Favoritos.txt");
      rename("Favoritos_aux.txt","Favoritos.txt");
    } else if ((lineas==contador)&& (coincidencia == 0))
    {
      remove("Favoritos.txt");
      rename("Favoritos_aux.txt","Favoritos.txt");
    } else
    {
      printf("HA HABIDO UN ERROR\n");
    }
    fclose(pf);
    fclose(pf_aux);
    if (coincidencia == 1)
    {
      printf("Se ha eliminado con exito\n");
      return 1;
    } else
    {
      printf("NO ESTA EN FAVORITOS o ha habido un error\n");
      return -1;
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
