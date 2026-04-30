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
    
    // Load Fonts (Important for rendering text)
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    // nk_font_atlas_add_default(atlas); // Use default or load .ttf here
    nk_sdl_font_stash_end();

    int running = 1;
    unsigned int n_lineas = 0;
    actividad *dataptr = read_csv("dataset.csv", &n_lineas);
    while (running) {
        /* 3. Input Handling */
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) running = 0;
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        /* 4. UI Logic (Your Code) */
        render_app(ctx, dataptr);

        /* 5. Rendering */
        glViewport(0, 0, 1280, 720);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // This draws the Nuklear command buffer to the screen
        nk_sdl_render(NK_ANTI_ALIASING_ON, 512 * 1024, 128 * 1024);
        
        SDL_GL_SwapWindow(win);
    }

    /* 6. Cleanup */
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
