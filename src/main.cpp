
// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL2/SDL.h>
#include <stdio.h>
#include "engine.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  SDL_Renderer *renderer;


  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(
			    "raycast-engine",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN
			    );

  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  screenSurface = SDL_GetWindowSurface(window);
  // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  renderer = SDL_CreateRenderer(window, -1, 0);

  // Start(screenSurface, renderer);
  // Update(screenSurface, renderer);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  for (int i = 0; i < SCREEN_WIDTH; ++i)
      SDL_RenderDrawPoint(renderer, i, i);
  SDL_RenderPresent(renderer);

  bool keep_window_open = true;
  while(keep_window_open)
  {
    SDL_Event e;
    while(SDL_PollEvent(&e) > 0)
    {
      switch(e.type)
      {
          case SDL_QUIT:
              keep_window_open = false;
              break;
      }
      SDL_UpdateWindowSurface(window);
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}