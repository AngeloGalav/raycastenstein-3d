#include "input_handler.h"

extern double posX, posY;  // x and y start position
extern double dirX, dirY;     // initial direction vector
extern double planeX, planeY; // the 2d raycaster version of camera plane
extern float frameTime;
double moveSpeed; // the constant value is in squares/second
double rotSpeed; // the constant value is in radians/second

void inputHandler(SDL_Event event)
{
    moveSpeed = 1; // the constant value is in squares/second
    rotSpeed = 0.2;
    // keyboard API for key pressed
    switch (event.key.keysym.scancode)
    {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
        printf("frametime %f\n", frameTime);

        posX += dirX * moveSpeed;
        posY += dirY * moveSpeed;
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
        posX -= dirX * moveSpeed;
        posY -= dirY * moveSpeed;
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
}
