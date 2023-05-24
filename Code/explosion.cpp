#include "explosion.hpp"
#include <iostream>
using namespace std;
Explosion::Explosion(SDL_Renderer *rend, SDL_Texture *ast, int x, int y) : Unit(rend, ast)
{

    mover = {x, y, 75, 75};
    src = {0, 0};
    animate = true;
    animation = 1;
}

Explosion::draw()
{
    if (animate == true)
    {
        switch (animation) // Animating bullet from assets file.
        {
        case 1:
            src = {20, 43, 92, 95};
            break;
        case 2:
            src = {170, 22, 133, 141};
            break;
        case 3:
            src = {320, 11, 162, 165};
            break;
        case 4:
            src = {487, 11, 162, 165};
            break;
        case 5:
            src = {662, 11, 154, 165};
            break;
        case 6:
            src = {828, 11, 154, 165};
            break;
        case 7:
            src = {991, 11, 158, 165};
            animate = false;
            break;
        }
        Unit::draw(src, mover, SDL_FLIP_NONE);
        animation += 1;
    }
}