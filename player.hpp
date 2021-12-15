#include "spaceship.hpp"
#pragma once
using namespace std;
class Player : public Spaceship
{
public:
    Player(SDL_Renderer *rend, SDL_Texture *ast);
    void draw();
    void decreaseHealth();
    void increaseHealth();
    bool checkHealth();
    void fire(SDL_Renderer *rend, SDL_Texture *ast);
    void moveRight();
    void moveLeft();
    void move();
    int life_status();
    ~Player();
};