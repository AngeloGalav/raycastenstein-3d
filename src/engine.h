#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include "definitions.h"

void clear(SDL_Renderer * renderer);
void draw(SDL_Renderer * renderer, SDL_Rect * rect);
SDL_Texture* tex_from_image(const char* path, SDL_Renderer* renderer);
void QuitApp(SDL_Window** window, SDL_Renderer** renderer);
double getFrametime(clock_t current_ticks);
void clearColorBuffer();