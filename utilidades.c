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

