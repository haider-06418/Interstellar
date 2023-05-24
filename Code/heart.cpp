#include "heart.hpp"

Heart::Heart(SDL_Renderer *rend, SDL_Texture *ast) : Unit(rend, ast)
{
    src = {5382, 4906, 526, 453};
    int x, y;
    x = rand() % 450 + 50;
    y = rand() % 500 + 50;

    y = -1 * y;
    mover = {x, y, 25, 25};
    velocity = 5;
}

void Heart::draw()
{
    Unit::draw(src, mover, SDL_FLIP_NONE);
    Heart::move();
}

void Heart::move()
{
    Unit::move(mover, velocity);
}