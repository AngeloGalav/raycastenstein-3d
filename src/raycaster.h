#include <SDL2/SDL.h>
#include <cstdlib>
#include <cmath>
#include "map.h"
#include "definitions.h"
#include "texture.h"

#ifndef USE_TEXTURES
#define USE_TEXTURES 1
#endif

void drawWallLine(double distance, int x);
void raycaster(int x);
void render();