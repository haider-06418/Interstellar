#include "Unit.hpp"

class GameOver : public Unit
{
    SDL_Rect src, mover;

public:
    GameOver(SDL_Renderer *, SDL_Texture *ast);
    void draw();
};
