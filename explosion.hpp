#pragma once
#include "Unit.hpp"

class Explosion : public Unit
{
public:
    SDL_Rect src, mover;
    int animation;
    bool animate;

    Explosion(SDL_Renderer *rend, SDL_Texture *ast, int x, int y);
    draw();
};