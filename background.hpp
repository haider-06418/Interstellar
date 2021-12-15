#include "Unit.hpp"
#include <SDL.h>
#pragma once
class Background : public Unit
{
    SDL_Rect src, mover;
    int velocity;
    int x, y;
    int flip;

public:
    Background(SDL_Renderer *, SDL_Texture *ast, int);
    void draw(bool menu);
    void move();
};