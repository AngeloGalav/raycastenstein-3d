#include "structs.h"
#include <SDL2/SDL.h>

class Player {
public:
    Player();
    vec3 position;
    SDL_Rect player_image;
    SDL_Color player_color;
    void setPlayerImage(int x, int y, int w, int h);
    void renderPlayer(SDL_Surface* screenSurface);
    void renderPlayer(SDL_Renderer * renderer);
    void move();
};
