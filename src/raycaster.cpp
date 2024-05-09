#include "raycaster.h"

double dirX = -1, dirY = 0;        // initial direction vector
double planeX = 0, planeY = 0.66;  // the 2d raycaster version of camera plane
extern double posX, posY;
extern int worldMap[mapWidth][mapHeight];
extern SDL_Renderer* renderer;
extern Uint32 screenBuffer[SCREEN_HEIGHT][SCREEN_HEIGHT];
extern SDL_Surface* texture[5];

void render() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        raycaster(x);
    }
}

void raycaster(int x) {
    // calculate ray position and direction
    double cameraX =
        2 * x / double(SCREEN_WIDTH) - 1;  // x-coordinate in camera space
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;

    // which box of the map we're in
    int currentCheckerPosX = int(posX);
    int currentCheckerPosY = int(posY);

    // length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    // length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
    double perpWallDistance;  // the distance of the perpendicular wall

    // what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    // calculate step and initial sideDist
    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - currentCheckerPosX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (currentCheckerPosX + 1.0 - posX) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - currentCheckerPosY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (currentCheckerPosY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0;  // was there a wall hit?
    int side;     // was a NS or a EW wall hit?

    // perform DDA (Digital Differential Analyzer)
    while (hit == 0) {
        // jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            currentCheckerPosX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            currentCheckerPosY += stepY;
            side = 1;  // in this case the wall is in the "other" side.. allows
                       // to implement a sort of fake lighting in the scene
        }

        // Check if ray has hit a wall
        if (worldMap[currentCheckerPosX][currentCheckerPosY] > 0) hit = 1;
    }

    // Calculate distance projected on camera direction (Euclidean distance
    // would give fisheye effect!)
    if (side == 0)
        perpWallDistance = (sideDistX - deltaDistX);
    else
        perpWallDistance = (sideDistY - deltaDistY);

    SDL_Color color = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};

    switch (worldMap[currentCheckerPosX][currentCheckerPosY]) {
        case 1:
            color.r = 255;
            break;  // red
        default:
            color.g = 255;
            break;  // green
    }

    if (side) {
        color.r = color.r / 2;
        color.g = color.g / 2;
    }

    int h = SCREEN_HEIGHT;
    // Calculate height of line to draw on screen
    int lineHeight = (int)(h / perpWallDistance);

    // calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + h / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + h / 2;
    if (drawEnd >= h) drawEnd = h - 1;

    if (USE_TEXTURES) {
        int textId = worldMap[currentCheckerPosX][currentCheckerPosY] - 1;

        // calculate value of wallX
        double wallX;  // where exactly the wall was hit
        wallX = (side == 0) ? (posY + perpWallDistance * rayDirY)
                            : (posX + perpWallDistance * rayDirX);

        wallX -= floor((wallX));

        // x coordinate on the texture
        int texX = int(wallX * double(TEX_WIDTH));
        if (side == 0 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * TEX_HEIGHT / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

        // for each pixel in a vertical line
        for (int y = drawStart; y < drawEnd; y++) {
            // Cast the texture coordinate to integer, and mask with (TEX_HEIGHT
            // - 1) in case of overflow
            int texY = (int)texPos & (TEX_HEIGHT - 1);
            texPos += step;

            SDL_LockSurface(texture[textId]);
            // Uint32 tex_pixel_color

            Uint8* pixel = (Uint8*)texture[textId]->pixels +
                           texY * texture[textId]->pitch +
                           texX * texture[textId]->format->BytesPerPixel;
            Uint32 tex_pixel_color = *(Uint32*)pixel;

            SDL_UnlockSurface(texture[textId]);
            SDL_Color color_2;
            SDL_GetRGBA(tex_pixel_color, texture[textId]->format, &(color_2.r),
                        &(color_2.g), &(color_2.b), &(color_2.a));

            if (side == 1) {
                color_2.r = (color_2.r >> 1) & 8355711;
                color_2.b = (color_2.b >> 1) & 8355711;
                color_2.g = (color_2.g >> 1) & 8355711;
            }

            SDL_SetRenderDrawColor(renderer, color_2.r, color_2.g, color_2.b,
                                   color_2.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    } else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}