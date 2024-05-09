#include "texture.h"

SDL_Surface* texture[5];

void initTexture() {
    texture[0] = IMG_Load("textures/purplestone.png");
    texture[1] = IMG_Load("textures/bluestone.png");
    texture[2] = IMG_Load("textures/greystone.png");
    texture[3] = IMG_Load("textures/redbrick.png");
    texture[4] = IMG_Load("textures/mossy.png");
}