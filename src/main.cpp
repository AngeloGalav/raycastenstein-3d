#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <chrono>
#include <iostream>
#include "map.h"
#include "engine.h"
#include "raycaster.h"
#include "input_handler.h"
#include "definitions.h"

double posX = 22, posY = 12;  // x and y start position
extern double dirX, dirY;     // initial direction vector
extern double planeX, planeY; // the 2d raycaster version of camera plane

clock_t current_ticks;
double frameTime = 0;
SDL_Renderer *renderer;
SDL_Rect background = {.x = 0, .y = SCREEN_HEIGHT/2, .w = SCREEN_WIDTH, .h = SCREEN_HEIGHT};

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    //disable vsync for research purposes
    SDL_GL_SetSwapInterval(0);

    SDL_Window *window = SDL_CreateWindow("raycast-engine",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // loads image to our graphics hardware memory.
    // SDL_Texture *tex = tex_from_image("res/simple_square.png", renderer);
    // SDL_RenderCopy(renderer, tex, NULL, &rect);
    // SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);

    int program_closed = 0;
    int speed = 30;

    // game loop
    while (!program_closed)
    {
        SDL_Event event;
        current_ticks = clock();

        // Events management
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                // handling of close button
                program_closed = 1;
                break;

            case SDL_KEYDOWN:
                inputHandler(event);
                break;
            }
        }

        // clears the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // renders background
        SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
        SDL_RenderDrawRect(renderer, &background);
        SDL_RenderFillRect(renderer, &background);
        render();
        renderMapOnScreen(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / 60);
        frameTime = getFrametime(current_ticks);
    }

    QuitApp(&window, &renderer);
    return 0;
}