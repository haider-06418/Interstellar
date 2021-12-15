#include "life.hpp"
#include <iostream>
#include "interstellar.hpp"
using namespace std;
Life::Life(SDL_Renderer *rend, SDL_Texture *asst) : Unit(rend, asst)
{
    mover = {50, 700, 250, 10};
}

void Life::draw(int x)
{
    // Source rectangle will change based on current player health.
    switch (x)
    {
    case 0:
        src = {1, 631, 1050, 40};
        break;
    case 1:
        src = {1, 581, 1050, 40};
        break;
    case 2:
        src = {1, 531, 1050, 40};
        break;
    case 3:
        src = {1, 441, 1050, 40};
        break;
    case 4:
        src = {1, 341, 1050, 40};
        break;
    case 5:
        src = {1, 291, 1050, 40};
        break;
    case 6:
        src = {1, 191, 1050, 40};
        break;
    case 7:
        src = {1, 101, 1050, 40};
        break;
    case 8:
        src = {1, 1, 1050, 40};

        break;
    }
    Unit::draw(src, mover, SDL_FLIP_NONE);
}