#include "engine.h"

// clears screen
void clear(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// draw a rectangle on the screen (provisional)
void draw(SDL_Renderer * renderer, SDL_Rect * rect) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, rect);
    SDL_RenderPresent(renderer);
}

SDL_Texture* tex_from_image(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("IMAGE PATH NOT VALID");
        return NULL;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

void QuitApp(SDL_Window** window, SDL_Renderer** renderer){
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}