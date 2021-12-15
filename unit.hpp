#pragma once
#include <SDL.h>
// This class is inherited by multiple classes.
class Unit
{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;

public:
    Unit(SDL_Renderer *, SDL_Texture *);
    void draw(SDL_Rect srcRect, SDL_Rect moverRect, SDL_RendererFlip flip);
    void move(SDL_Rect &moverRect, int);
};