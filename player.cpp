#include "player.hpp"
/*The player class has health, velocity and bullets list as attributes.
Whenever user fires a new bullet is added to the list and drawed.
Player has health of 8 and velocity of moving right and left of 15.
 */
Player::Player(SDL_Renderer *rend, SDL_Texture *ast) : Spaceship(rend, ast)
{
    mover = {300 - 32, 675 - 75, 75, 75};
    src = {2013, 2291, 427, 253};
    health = 8;
    velocity = 15;
}

void Player::draw()
{
    Unit::draw(src, mover, SDL_FLIP_NONE);
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

void Player::fire(SDL_Renderer *rend, SDL_Texture *ast)
{
    lasers.push_back(new Laser(rend, ast, mover.x, mover.y, 1)); // Adding laser to list.
}
// Moving player within boundaries.
void Player::moveRight()
{
    if (mover.x + 70 < 600)
    {
        mover.x += velocity;
    }
    else if (mover.x + 70 >= 600)
        mover.x = 600 - 70;
}
void Player::moveLeft()
{
    if (mover.x > 0)
        mover.x -= velocity;
    else if (mover.x <= 0)
        mover.x = 0;
}
void Player::decreaseHealth()
{
    health -= 1;
}
void Player::increaseHealth()
{
    if (health < 8)
        health += 1;
}

// int Player::life_status(){
//     return health;
// }

bool Player::checkHealth() // Checking if player is alive.
{
    if (health <= 0)
    {
        return false;
    }
    return true;
}

void Player::move()
{
}

Player::~Player()
{
    for (auto *laser : lasers)
        delete laser;
    lasers.clear();
}