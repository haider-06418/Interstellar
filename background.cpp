#include "background.hpp"
#include <iostream>
using namespace std;

Background::Background(SDL_Renderer *rend, SDL_Texture *gTex, int yy) : Unit(rend, gTex), y(yy)
{
    mover = {0, y, 600, 750};
    src = {0, 0, 1023, 1920};
}

void Background::draw(bool menu)
{
    if (menu == false)
        Background::move();
    Unit::draw(src, mover, SDL_FLIP_NONE);
}

void Background::move()
{
    // Two backgrounds will move downwards continously and will be placed at top of screen when their y coordinate reaches 750.
    mover.y += 3;
    if (mover.y == 750)
        mover.y = -750;
}