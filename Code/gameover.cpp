#include "gameover.hpp"
#include <iostream>
using namespace std;
GameOver::GameOver(SDL_Renderer *rend, SDL_Texture *asst) : Unit(rend, asst)
{
    src = {1, 1, 1340, 700};
    mover = {150, 250, 300, 300};
}

void GameOver::draw()
{
    Unit::draw(src, mover, SDL_FLIP_NONE);
}