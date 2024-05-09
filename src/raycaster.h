#include <SDL2/SDL.h>
#include <cstdlib>
#include "map.h"
#include "definitions.h"
#include "texture.h"

#define USE_TEXTURES 1

void drawWallLine(double distance, int x);
void raycaster(int x);
void render();