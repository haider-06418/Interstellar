#include "Unit.hpp"

class Life : public Unit
{
    SDL_Rect src, mover;

public:
    Life(SDL_Renderer *, SDL_Texture *ast);
    void draw(int x);
};
