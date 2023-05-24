#include "laser.hpp"

Laser::Laser(SDL_Renderer *rend, SDL_Texture *ast, int x, int y, int choice) : Unit(rend, ast)
{
    // Different laser for enemy and player.
    switch (choice)
    {
    case 1:
        src = {1015, 3010, 115, 1230};
        break;
    case 2:
        src = {1347, 1477, 118, 1101};
        break;
    }
    mover = {x + 33, y - 2, 5, 30};
    // Enemy laser will move down and player laser will move up.
    if (choice == 1)
        velocity = -10;
    else
        velocity = 10;
}

void Laser::draw()
{
    // Drawing and moving laser.
    Unit::draw(src, mover, SDL_FLIP_NONE);
    Laser::move();
}

void Laser::move()
{
    Unit::move(mover, velocity);
}