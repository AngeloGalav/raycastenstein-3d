#include "raycaster.h"

double dirX = -1, dirY = 0; // initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
extern double posX, posY;
extern int worldMap[mapWidth][mapHeight];
extern SDL_Renderer* renderer;

void raycaster(int w) {
    // for every strip
    for (int i = 0; i < w; i++) {
      double cameraX = 2 * i / double(w) - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
    }
}

void render() {
  int w = SCREEN_WIDTH;
  for(int x = 0; x < w; x++)
  {
    //calculate ray position and direction
    double cameraX = 2 * x / double(w) - 1; // x-coordinate in camera space
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;



    //which box of the map we're in
    int mapX = int(posX);
    int mapY = int(posY);

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;


    //calculate step and initial sideDist
    if (rayDirX < 0)
    {
      stepX = -1;
      sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
      stepX = 1;
      sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
      stepY = -1;
      sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
      stepY = 1;
      sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    //perform DDA
    while (hit == 0)
    {
      //jump to next map square, either in x-direction, or in y-direction
      if (sideDistX < sideDistY)
      {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      }
      else
      {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }

      //Check if ray has hit a wall
      if (worldMap[mapX][mapY] > 0) hit = 1;
    }


    //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);

    SDL_Color color = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};

    switch(worldMap[mapX][mapY])
    {
      case 1:  color.r = 255;  break; //red
      default:  color.g = 255;  break; //green
    }

    if (side) {
      color.r = color.r / 2;
      color.g = color.g / 2;
    }
      

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    drawWallLine(perpWallDist, x);
  }

}

void drawWallLine(double distance, int x){
  int h = SCREEN_HEIGHT;
  //Calculate height of line to draw on screen
  int lineHeight = (int)(h / distance);

  //calculate lowest and highest pixel to fill in current stripe
  int drawStart = -lineHeight / 2 + h / 2;
  if(drawStart < 0)drawStart = 0;
  int drawEnd = lineHeight / 2 + h / 2;
  if(drawEnd >= h)drawEnd = h - 1;

  SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
}