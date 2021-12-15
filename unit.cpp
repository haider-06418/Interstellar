#include "unit.hpp"

Unit::Unit(SDL_Renderer *rend, SDL_Texture *ast) : gRenderer(rend), assets(ast) {}

void Unit::draw(SDL_Rect srcRect, SDL_Rect moverRect, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(gRenderer, assets, &srcRect, &moverRect, NULL, NULL, flip); // Drawing based on assets, mover rectangle and source rectangle.
}

void Unit::move(SDL_Rect &moverRect, int velocity)
{
    moverRect.y += velocity;
}