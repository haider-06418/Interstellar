#include "enemy.hpp"
#include <iostream>
using namespace std;
Enemy::Enemy(SDL_Renderer *rend, SDL_Texture *ast) : Spaceship(rend, ast)
{
    int ran = rand() % 5 + 1;

    // Picking a random enemy from assets.
    switch (ran)
    {
    case 1:
        src = {2005, 3851, 443, 205};
        break;
    case 2:
        src = {2013, 3490, 427, 194};
        break;
    case 3:
        src = {2013, 2291, 427, 253};
        break;
    case 4:
        src = {2005, 4572, 443, 394};
        break;
    case 5:
        src = {2005, 5139, 443, 382};
        break;
    }
    // Placing at random x and y coordinates above the screen.
    int x, y;
    x = rand() % 450 + 50;
    y = rand() % 800 + 50;
    y = -1 * y;
    mover = {x, y, 75, 75};
    velocity = 5;
    health = 3;
}

void Enemy::draw()
{
    Unit::draw(src, mover, SDL_FLIP_VERTICAL);
    Enemy::move();
    for (auto *laser : lasers)
    {
        laser->draw();
        if (laser->mover.y < 0)
        {
            lasers.remove(laser);
            delete laser;
        }
    }
}

void Enemy::move()
{
    Unit::move(mover, velocity);
}
void Enemy::fire(SDL_Renderer *rend, SDL_Texture *ast)
{
    if (mover.y >= 0)
        lasers.push_back(new Laser(rend, ast, mover.x, mover.y + 40, 2));
}
void Enemy::decreaseHealth()
{
    health -= 1;
}
void Enemy::increaseHealth()
{
    health += 1;
}
bool Enemy::checkHealth()
{
    if (health == 0)
    {
        return false;
    }
    return true;
}

void Enemy::moveLeft() {}
void Enemy::moveRight() {}

Enemy::~Enemy()
{
    for (auto *laser : lasers)
        delete laser;
    lasers.clear();
}
