#include <stdio.h>
#include <string.h>
#include <math.h>
#include "reader.h"

/* Define Nuklear implementation constants in one C file */

void render_app(struct nk_context *ctx, actividad *dataptr, unsigned int n_lineas);
void fill_row_data(char dest[11][512], actividad v);
