#include "spaceship.hpp"
class Enemy : public Spaceship
{
public:
    Enemy(SDL_Renderer *rend, SDL_Texture *ast);
    void draw();
    void decreaseHealth();
    void increaseHealth();
    bool checkHealth();
    void moveRight();
    void moveLeft();
    void move();
    void fire(SDL_Renderer *rend, SDL_Texture *ast);
    ~Enemy();
};