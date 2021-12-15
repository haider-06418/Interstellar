#include "Unit.hpp"
class Asteroid : public Unit
{
public:
    SDL_Rect src, mover;
    int velocity;

    Asteroid(SDL_Renderer *rend, SDL_Texture *ast);
    void draw();
    void move();
};