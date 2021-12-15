#include "Unit.hpp"

class GamePause : public Unit
{
    SDL_Rect src, mover;

public:
    GamePause(SDL_Renderer *, SDL_Texture *ast);
    void draw();
};
