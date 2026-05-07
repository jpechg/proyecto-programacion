#include "include/glad/glad.h"
#include "reader.h"
#include <SDL2/SDL.h>

#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_SDL_GL3_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_gl3.h"
#include "utilidades.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    /* 1. SDL & OpenGL Setup */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *win = SDL_CreateWindow("Nuklear App", SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 1280, 720, 
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GLContext glContext = SDL_GL_CreateContext(win);    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }
    /* 2. Nuklear SDL/GL3 Setup */
    struct nk_context *ctx = nk_sdl_init(win);

    struct nk_font_atlas *atlas;
    struct nk_font_config config = nk_font_config(0); // Inicializar configuración
    struct nk_font *sans;

    nk_sdl_font_stash_begin(&atlas);

    sans = nk_font_atlas_add_from_file(atlas, "LiberationSans-Regular.ttf", 18, &config); //carga la fuente de texto

    static const nk_rune emojis_rango[] = {0x1f600, 0x1f64f, 0};
    
    config.merge_mode = 1; 
    nk_font_atlas_add_from_file(atlas, "NotoEmoji-Regular.ttf", 18, &config);

    nk_sdl_font_stash_end();

    nk_style_set_font(ctx, &sans->handle);    
    int running = 1;

    struct_estado_app estado = {0};
    estado.datos_actuales = NULL;
    estado.n_datos_actuales = 0;
    estado.mostrar_favoritos = 0;

    unsigned int n_lineas = 0;
    int n_favs = longitud_favoritos();
    actividad *dataptr = read_csv("dataset.csv", &n_lineas);
    actividad *dataptr_favs = leer_favoritos(n_favs);
    printf("%p",dataptr_favs);
    while (running) {
        /* 3. Input Handling */
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) running = 0;
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        if (estado.recargar_f== 1){
            if (dataptr_favs) free(dataptr_favs);
            n_favs = longitud_favoritos();
            dataptr_favs = leer_favoritos(n_favs);
            estado.recargar_f = 0;
        }

        if (estado.mostrar_favoritos == 1) {
            // Recargar favoritos cada vez
            if (dataptr_favs) free(dataptr_favs);
            n_favs = longitud_favoritos();
            if (n_favs > 0) {
                dataptr_favs = leer_favoritos(n_favs);
                if (dataptr_favs){
                    render_app(ctx, dataptr_favs, n_favs, &estado);
                } else {
                    nk_layout_row_dynamic(ctx,30,1);
                    nk_label(ctx,"Error al cargar favoritos", NK_TEXT_CENTERED);
                    if (nk_button_label(ctx,"VOLVER")) {
                        estado.mostrar_favoritos = 0;
                    }
                }
            } else {
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx,"Aun no has guardado favoritos",NK_TEXT_CENTERED);
                if (nk_button_label(ctx,"VOLVER")){
                    estado.mostrar_favoritos = 0;
                }
            }
            if (estado.recargar_f == 1) {
                if (dataptr_favs) free(dataptr_favs);
                n_favs = longitud_favoritos();
                dataptr_favs = leer_favoritos(n_favs);
                estado.recargar_f = 0;
            }
        } else {
            render_app(ctx, dataptr, n_lineas, &estado);
        }
            /* 5. Rendering */
        glViewport(0, 0, 1280, 720);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // This draws the Nuklear command buffer to the screen
        nk_sdl_render(NK_ANTI_ALIASING_ON, 512 * 1024, 128 * 1024);
        
        SDL_GL_SwapWindow(win);
    }

    if (estado.datos_actuales && estado.datos_actuales != dataptr) {
        free(estado.datos_actuales);
    }
    if (dataptr_favs) {
         free(dataptr_favs);
    }
    free(dataptr);
    
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
