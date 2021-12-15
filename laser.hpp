#include "Unit.hpp"
#pragma once
class Laser : public Unit
{
public:
    SDL_Rect src, mover;
    int velocity;


    Laser(SDL_Renderer *rend, SDL_Texture *ast, int x, int y, int choice);
    void draw();
    void move();
};