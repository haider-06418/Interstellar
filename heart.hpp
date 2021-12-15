#include "Unit.hpp"
#pragma once
class Heart : public Unit
{
public:
    SDL_Rect src, mover;
    int velocity;

    Heart(SDL_Renderer *rend, SDL_Texture *ast);
    void draw();
    void move();
};