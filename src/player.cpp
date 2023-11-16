#include "player.h"

Player::Player(){
    player_color = (SDL_Color){.r = 100, .g = 200, .b = 100};
}

void Player::setPlayerImage(int x, int y, int w, int h) {
    player_image = (SDL_Rect){.x = x, .y = y, .w = w, .h = h};
}

// obsolete version for drawing stuff on the screen
void Player::renderPlayer(SDL_Surface* screenSurface) {
    SDL_FillRect(screenSurface, &player_image,
        SDL_MapRGB(screenSurface->format, player_color.r, player_color.g, player_color.b));
}

void Player::move(double x, double y) { }

void Player::renderPlayer(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player_image);
    SDL_RenderPresent(renderer);
}