#include "gamepause.hpp"

GamePause::GamePause(SDL_Renderer *rend, SDL_Texture *asst) : Unit(rend, asst)
{
    mover = {0, 0, 600, 750};
    src = {0, 0, 1023, 1920};
}

void GamePause::draw()
{
    Unit::draw(src, mover, SDL_FLIP_NONE);
}