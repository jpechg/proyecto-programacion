int *ordenarActividadesDeCentro(actividad *dataPtr, unsigned int numLineas,uint32_t centroBuscado,int *numEncontradas)
{
    int i, j;
    int contador = 0;
    int *posiciones;
    int aux;

    /*
        Primero contamos cuántas filas pertenecen al centro buscado.

        Ejemplo:
        si centroBuscado es La_Almudena,
        contamos cuántas líneas del fichero tienen ese centro.
    */
    for (i = 0; i < numLineas; i++) {

        if (dataPtr[i].centro == centroBuscado) {
            contador++;
        }
    }

    /*
        Si no encontramos ninguna actividad de ese centro,
        devolvemos NULL.
    */
    if (contador == 0) {
        *numEncontradas = 0;
        return NULL;
    }

    /*
        Reservamos memoria solo para las posiciones
        de las actividades de ese centro.
    */
    posiciones = malloc(sizeof(int) * contador);

    if (posiciones == NULL) {
        printf("Error al reservar memoria\n");
        *numEncontradas = 0;
        return NULL;
    }

    /*
        Ahora guardamos las posiciones de dataPtr
        que pertenecen al centro buscado.
    */
    contador = 0;

    for (i = 0; i < numLineas; i++) {

        if (dataPtr[i].centro == centroBuscado) {

            posiciones[contador] = i;
            contador++;
        }
    }

    /*
        Ahora ordenamos esas posiciones alfabéticamente
        según el nombre de la actividad.
    */
    for (i = 0; i < contador - 1; i++) {

        for (j = i + 1; j < contador; j++) {

            /*
                posiciones[i] es una posición dentro de dataPtr.

                dataPtr[posiciones[i]].actividad es el número de la actividad.

                actividades[dataPtr[posiciones[i]].actividad] es el nombre real.
            */

            if (strcmp(actividades[dataPtr[posiciones[i]].actividad],
                       actividades[dataPtr[posiciones[j]].actividad]) > 0) {

                aux = posiciones[i];
                posiciones[i] = posiciones[j];
                posiciones[j] = aux;
            }
        }
    }

    /*
        Guardamos cuántas actividades hemos encontrado
        para que el main pueda recorrer el vector.
    */
    *numEncontradas = contador;

    /*
        Devolvemos las posiciones ordenadas.
    */
    return posiciones;
}