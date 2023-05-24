#pragma once
#include <iostream>
#include "unit.hpp"
#include <list>
#include "laser.hpp"
using namespace std;

// This class is completely abstract.
class Spaceship : public Unit
{
public:
    SDL_Rect src, mover;
    list<Laser *> lasers;
    int health;
    int velocity;
    Spaceship(SDL_Renderer *rend, SDL_Texture *ast);
    virtual void draw() = 0;
    virtual void decreaseHealth() = 0;
    virtual void increaseHealth() = 0;
    virtual bool checkHealth() = 0;
    virtual void move() = 0;
    virtual void moveRight() = 0;
    virtual void moveLeft() = 0;
    virtual void fire(SDL_Renderer *rend, SDL_Texture *ast) = 0;
};