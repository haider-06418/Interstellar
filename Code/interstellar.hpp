#include <SDL.h>
#include "player.hpp"
#include "asteroid.hpp"
#include "Background.hpp"
#include "enemy.hpp"
#include "spaceship.hpp"
#include "explosion.hpp"
#include "heart.hpp"
#include <Windows.h>
#include <list>

using namespace std;
class Interstellar
{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    SDL_Texture *gTexture;
    SDL_Texture *expl;
    bool playerStatus;
    int score;
    // Each class is inheriting unit class which draws the object to canvas.
    list<Asteroid *> asteroids;

    list<Explosion *> explosions;
    list<Heart *> hearts;

    // Spaceship class is completely abstract.
    list<Spaceship *> enemies;
    Spaceship *player;
    // Background surfaces are moving regulary.
    Background b1, b2;

public:
    Interstellar(SDL_Renderer *, SDL_Texture *, SDL_Texture *, SDL_Texture *);
    void createAsteroid(int);
    void createEnemy(int);
    bool drawObjects();
    void fire();
    void movePlayer(int);
    void createExplosion(int, int);
    void createHearts(int);
    void fireEnemy(int);
    bool checkCollision(SDL_Rect, SDL_Rect);
    void displayScore();
    void increaseScore(int);
    int life_status();

    ~Interstellar();
};