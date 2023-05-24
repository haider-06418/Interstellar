#include "asteroid.hpp"
#include <iostream>
using namespace std;
Asteroid::Asteroid(SDL_Renderer *rend, SDL_Texture *ast) : Unit(rend, ast)
{

    int ran = rand() % 4 + 1;
    switch (ran)
    {
    case 1:
        src = {4384, 131, 589, 633};
        break;
    case 2:
        src = {116, 1962, 741, 1007};
        break;
    case 3:
        src = {4295, 1572, 607, 644};
        break;
    case 4:
        src = {5834, 3236, 813, 637};
        break;
    }

    int x, y;
    x = rand() % 450 + 50;
    y = rand() % 700 + 50;

    y = -1 * y;
    mover = {x, y, 75, 75};
    velocity = 5;
}

void Asteroid::draw()
{
    Unit::draw(src, mover, SDL_FLIP_VERTICAL);
    Asteroid::move();
}

void Asteroid::move()
{
    mover.y += velocity;
};