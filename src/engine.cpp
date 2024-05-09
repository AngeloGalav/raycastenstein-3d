#include "engine.h"

// screen color buffer
Uint32 screenBuffer[SCREEN_HEIGHT][SCREEN_HEIGHT];

// clears screen
void clear(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// draw a rectangle on the screen (provisional)
void draw(SDL_Renderer *renderer, SDL_Rect *rect)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, rect);
    SDL_RenderPresent(renderer);
}

void blitDraw(SDL_Surface* src, SDL_Surface* dst) {
    SDL_Rect window_dim;
    window_dim.w = SCREEN_WIDTH;
    window_dim.h = SCREEN_HEIGHT;
    SDL_BlitSurface(src, &window_dim, dst, &window_dim);
}

SDL_Texture *tex_from_image(const char *path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(path);
    if (!surface)
    {
        printf("IMAGE PATH NOT VALID");
        return NULL;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

void QuitApp(SDL_Window **window, SDL_Renderer **renderer)
{
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}

double getFrametime(clock_t current_ticks)
{
    clock_t delta_ticks = clock() - current_ticks; // the time, in ms, that took to render the scene
    return delta_ticks / 10000.0f;
}

void clearColorBuffer()
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
        for (int x = 0; x < SCREEN_WIDTH; x++)
            screenBuffer[y][x] = 0;
}