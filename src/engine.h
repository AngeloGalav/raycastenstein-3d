#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void clear(SDL_Renderer * renderer);
void draw(SDL_Renderer * renderer, SDL_Rect * rect);
SDL_Texture* tex_from_image(const char* path, SDL_Renderer* renderer);
void QuitApp(SDL_Window** window, SDL_Renderer** renderer);