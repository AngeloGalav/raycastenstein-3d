#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "engine.h"

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      printf("error initializing SDL: %s\n", SDL_GetError());
  }

  SDL_Window* window = SDL_CreateWindow("raycast-engine",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WIDTH, HEIGHT, 0);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // loads image to our graphics hardware memory.
  SDL_Texture* tex = tex_from_image("../res/simple_square.png", renderer);
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

  // controls animation loop
  int close = 0;
  int speed = 300;

  // animation loop
  while (!close) {
      SDL_Event event;

      // Events management
      while (SDL_PollEvent(&event)) {
          switch (event.type) {

          case SDL_QUIT:
              // handling of close button
              close = 1;
              break;

          case SDL_KEYDOWN:
              // keyboard API for key pressed
              switch (event.key.keysym.scancode) {
              case SDL_SCANCODE_W:
              case SDL_SCANCODE_UP:
                  rect.y -= speed / 30;
                  break;
              case SDL_SCANCODE_A:
              case SDL_SCANCODE_LEFT:
                  rect.x -= speed / 30;
                  break;
              case SDL_SCANCODE_S:
              case SDL_SCANCODE_DOWN:
                  rect.y += speed / 30;
                  break;
              case SDL_SCANCODE_D:
              case SDL_SCANCODE_RIGHT:
                  rect.x += speed / 30;
                  break;
              default:
                  break;
              }
          }
      }

    // right boundary
    if (rect.x + rect.w > WIDTH)
        rect.x = WIDTH - rect.w;

    // left boundary
    if (rect.x < 0)
        rect.x = 0;

    // bottom boundary
    if (rect.y + rect.h > HEIGHT)
        rect.y = HEIGHT - rect.h;

    // upper boundary
    if (rect.y < 0)
        rect.y = 0;

    // clears the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    // triggers the double buffers
    // for multiple rendering (updates backbuffer)
    SDL_RenderPresent(renderer);
    // calculates to 60 fps
    SDL_Delay(1000 / 60);
  }

  QuitApp(&window, &renderer);
  return 0;
}