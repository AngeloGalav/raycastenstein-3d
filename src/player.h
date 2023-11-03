#include "structs.h"
#include <SDL2/SDL.h>

class Player {
    Player();
    vec3 position;
    SDL_Rect player_image;
    SDL_Color player_color;
    void setPlayerImage(int x, int y, int w, int h);
    void renderPlayer(SDL_Surface* screenSurface);
};
