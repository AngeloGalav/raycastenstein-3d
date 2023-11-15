#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "engine.h"
#include "raycaster.h"
#include <chrono>
#include <iostream>

#define WIDTH 640
#define HEIGHT 480

double posX = 22, posY = 12;  // x and y start position
extern double dirX, dirY;     // initial direction vector
extern double planeX, planeY; // the 2d raycaster version of camera plane

clock_t current_ticks;
double frameTime = 0;
SDL_Renderer *renderer;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow("raycast-engine",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // loads image to our graphics hardware memory.
    SDL_Texture *tex = tex_from_image("../res/simple_square.png", renderer);
    // SDL_RenderCopy(renderer, tex, NULL, &rect);

    // setups texture with the right size
    SDL_Rect rect;
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);

    // adjust height and width of our image box.
    rect.w /= 6;
    rect.h /= 6;

    // sets initial position of object
    rect.x = (WIDTH - rect.w) / 2;
    rect.y = (HEIGHT - rect.h) / 2;

    int close = 0;
    int speed = 30;

    // game loop
    while (!close)
    {
        SDL_Event event;
        current_ticks = clock();

        // speed modifiers
        double moveSpeed = 0.1 * 5.0; // the constant value is in squares/second
        double rotSpeed = 0.1 * 3.0;  // the constant value is in radians/second

        // Events management
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    posX += dirX * moveSpeed;
                    posY += dirY * moveSpeed;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                { // both camera direction and camera plane must be rotated
                    double oldDirX = dirX;
                    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                    break;
                }
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    posX -= dirX * moveSpeed;
                    posY -= dirY * moveSpeed;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                {
                    double oldDirX = dirX;
                    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                    break;
                }
                default:
                    break;
                }
            }
        }

        // clears the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render();
        SDL_RenderPresent(renderer);

        frameTime = getFrametime(current_ticks);
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    QuitApp(&window, &renderer);
    return 0;
}