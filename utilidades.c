#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "reader.h"

int actividad_ocupada(actividad *dataptr, unsigned int i) {
    if (dataptr[i].libre == 0) {
        return 1;
    }
    return 0;
}

int add_favoritos(actividad *dataptr,uint32_t valor,unsigned int n_datos)
{
    unsigned int i = 0;
    FILE *pf;
    pf = fopen("Favoritos.txt","w");
    if (pf == NULL)
    {
        printf("Ha habido un error");
        return 0;
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
int main ()
{
    int n = 0;
    actividad *dataptr = read_csv("dataset.csv",&n);
    add_favoritos (dataptr,5,n);
    return 0;
    
}