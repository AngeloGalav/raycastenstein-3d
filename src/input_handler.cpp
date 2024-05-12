#include "input_handler.h"
#include <cstdio>

extern double posX, posY;  // x and y start position
extern double dirX, dirY;     // initial direction vector
extern double planeX, planeY; // the 2d raycaster version of camera plane
extern float frameTime;
extern int worldMap[mapWidth][mapHeight];
double moveSpeed; // the constant value is in squares/second
double rotSpeed; // the constant value is in radians/second

void inputHandler(SDL_Event event)
{

    double transX = 0, transY = 0;

    moveSpeed = 1; // the constant value is in squares/second
    rotSpeed = 0.2;
    // keyboard API for key pressed
    switch (event.key.keysym.scancode)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        transX = dirX * moveSpeed;
        transY = dirY * moveSpeed;
        break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
    { // both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        break;
    }
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
        transX = -(dirX * moveSpeed);
        transY = -(dirY * moveSpeed);
        break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
    {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        break;
    }
    default:
        break;
    }

    if (transX != 0 || transY != 0) {
        double _posX = posX + transX;
        double _posY = posY + transY;

        // applies transformation only if in map bounds
        if (worldMap[(int)floor(_posX)][(int)floor(_posY)] == 0) {
            posX = _posX;
            posY = _posY;
        }
    }


}
