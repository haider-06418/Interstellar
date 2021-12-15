#include "interstellar.hpp"
#include <iostream>

// Intializing game.
Interstellar::Interstellar(SDL_Renderer *renderer, SDL_Texture *asst, SDL_Texture *gTex, SDL_Texture *ex) : gRenderer(renderer), assets(asst), gTexture(gTex), expl(ex), b1(renderer, gTex, 0), b2(renderer, gTex, -750)
{
    score = 0;
    player = new Player(renderer, asst);
}

bool Interstellar::drawObjects()
{
    // Drawing backgrounds
    b1.draw(false);
    b2.draw(false);
    player->draw();
    // Checking collisions
    for (auto *laser : player->lasers) // Each laser of spaceship is checked to see if it has collided with any enemy spaceship.
    {
        for (auto *enemy : enemies)
        {
            bool enemyStatus = Interstellar::checkCollision(laser->mover, enemy->mover);

            if (enemyStatus == true) // If collision has happened we create an explosion and decrease enemy health.
            {
                createExplosion(enemy->mover.x, enemy->mover.y); // Creating an explosion where enemy is located.
                enemy->decreaseHealth();                         // Decreasing enemy health.
                if (enemy->checkHealth() == false)
                {
                    enemies.remove(enemy); // Removing enemy from list.
                    delete enemy;          // Deleting enemy when no longer in use.
                    score += 5;
                }
                player->lasers.remove(laser); // Removing laser from list.
                delete laser;                 // Deleting laser.
            }
        }
        for (auto *asteroid : asteroids) // The same process for collision of laser with asteroids.
        {
            bool asteroidStatus = Interstellar::checkCollision(laser->mover, asteroid->mover);

            if (asteroidStatus == true)
            {
                createExplosion(asteroid->mover.x, asteroid->mover.y);
                player->lasers.remove(laser);
                asteroids.remove(asteroid);
                delete asteroid;
                delete laser;
                score += 5;
            }
        }
    }
    // The rest of the collisions follow the same procedures.
    for (auto *enemy : enemies)
    {
        for (auto *laser : enemy->lasers)
        {
            if (Interstellar::checkCollision(laser->mover, player->mover) == true)
            {
                createExplosion(player->mover.x, player->mover.y);
                laser->src = {0, 0, 0, 0};
                enemy->lasers.remove(laser);
                delete laser;
                player->decreaseHealth();
            }
        }
    }
    for (auto *heart : hearts)
    {
        if (heart->mover.y < 750)
        {
            heart->draw();
            if (Interstellar::checkCollision(player->mover, heart->mover) == true)
            {
                hearts.remove(heart);
                delete heart;
                player->increaseHealth();
            }
        }
        else
        {
            hearts.remove(heart);
            delete heart;
        }
    }
    for (auto *asteroid : asteroids)
    {
        if (asteroid->mover.y < 750)
        {
            asteroid->draw();
            playerStatus = Interstellar::checkCollision(player->mover, asteroid->mover);

            if (playerStatus == true)
            {
                createExplosion(asteroid->mover.x, asteroid->mover.y);
                asteroids.remove(asteroid);
                delete asteroid;
                player->decreaseHealth();
                player->decreaseHealth();
                if (player->checkHealth() == false)
                {
                    createExplosion(player->mover.x, player->mover.y);
                }
            }
        }
        else
        {
            asteroids.remove(asteroid);
            delete asteroid;
        }
    }

    for (auto *enemy : enemies)
    {
        if (enemy->mover.y < 750)
        {
            enemy->draw();
            playerStatus = Interstellar::checkCollision(player->mover, enemy->mover);

            if (playerStatus == true)
            {
                createExplosion(enemy->mover.x, enemy->mover.y);
                enemies.remove(enemy);
                delete enemy;
                player->decreaseHealth();
                player->decreaseHealth();
                player->decreaseHealth();
                if (player->checkHealth() == false)
                {
                    createExplosion(player->mover.x, player->mover.y);
                }
            }
        }
        else
        {
            enemies.remove(enemy);
            delete enemy;
        }
    }
    for (auto *e : explosions) // Drawing and deleting explosions.
    {
        e->draw();
        if (e->animation == 8) // When explosion is complete it is deleted.
        {
            explosions.remove(e);
            delete e;
        }
    }
    if (player->checkHealth() == false) // Checking whether player is alive or not.
    {
        player->mover = {-300, 0, 0, 0};
        if (explosions.size() == 0)
            return true;
    }
    return false;
}

int Interstellar::life_status() // To display health on screen.
{
    return player->health;
}

void Interstellar::createAsteroid(int seconds) // Follows same procedure as enemy creation.
{
    static bool create_five = true;
    static bool create_ten = true;
    if (seconds != 0)
    {
        if (seconds % 2 == 0 && seconds % 3 != 0 && create_five == true)
        {
            create_five = false;
            int ran = rand() % 10 + 1;
            for (int i = 0; i < ran; i++)
            {
                asteroids.push_back(new Asteroid(gRenderer, assets));
            }
        }

        if (seconds % 3 == 0 && seconds % 2 != 0)
        {
            create_five = true;
        }
    }
    for (auto *asteroid : asteroids)
    {
        for (auto *enemy : enemies)
        {
            bool collide = checkCollision(asteroid->mover, enemy->mover);
            if (collide == true)
            {
                enemies.remove(enemy);
                delete enemy;
            }
        }
    }
    for (auto *asteroid1 : asteroids)
    {
        for (auto *asteroid2 : asteroids)
        {
            if (asteroid1 != asteroid2)
            {
                bool collide = checkCollision(asteroid1->mover, asteroid2->mover);

                if (collide == true)
                {
                    asteroids.remove(asteroid2);
                    delete asteroid2;
                }
            }
        }
    }
}

void Interstellar::createEnemy(int seconds)
{
    static bool create_five = true;
    if (seconds != 0)
    { // Creating enemy every 3 seconds.
        if (seconds % 3 == 0 && seconds % 5 != 0 && create_five == true)
        {
            create_five = false;
            int ran = rand() % 10 + 1;
            for (int i = 0; i < ran; i++)
            {
                enemies.push_back(new Enemy(gRenderer, assets));
            }
        }
    }

    if (seconds % 5 == 0 && seconds % 3 != 0)
    {
        create_five = true;
    }
    // Making sure that enemy does not collide with other objects on creation.
    for (auto *enemy : enemies)
    {
        for (auto *asteroid : asteroids)
        {
            bool collide = checkCollision(asteroid->mover, enemy->mover);
            if (collide == true)
            {
                asteroids.remove(asteroid);
                delete asteroid;
            }
        }
    }
    for (auto *enemy1 : enemies)
    {
        for (auto *enemy2 : enemies)
        {
            if (enemy1 != enemy2)
            {
                bool collide = checkCollision(enemy1->mover, enemy2->mover);
                if (collide == true)
                {
                    enemies.remove(enemy2);
                    delete enemy2;
                }
            }
        }
    }
}
void Interstellar::createHearts(int seconds) // Creating heart every 20 seconds.
{
    static bool create_five = true;
    if (seconds != 0)
    {
        if (seconds % 20 == 0 && seconds % 25 != 0 && create_five == true)
        {
            create_five = false;
            hearts.push_back(new Heart(gRenderer, assets));
        }

        if (seconds % 25 == 0 && seconds % 20 != 0)
        {
            create_five = true;
        }
    }
}
void Interstellar::movePlayer(int direction) // Moving player based on direction.
{
    if (direction > 0)
        player->moveRight();
    if (direction < 0)
        player->moveLeft();
}

void Interstellar::fire()
{
    player->fire(gRenderer, assets);
}
void Interstellar::fireEnemy(int seconds) // An enemy spaceship will only fire if player spaceship is in front.
{
    static bool fire = true;

    if (seconds % 1 == 0 && seconds % 2 != 0 && fire == true) // Firing every 1 second.
    {
        fire = false;
        for (auto *enemy : enemies)
        {
            if (player->mover.x >= enemy->mover.x - 25 && player->mover.x <= enemy->mover.x + 100)
                enemy->fire(gRenderer, assets);
        }
    }
    if (seconds % 2 == 0)
    {
        fire = true;
    }
}
void Interstellar::createExplosion(int x, int y)
{
    explosions.push_back(new Explosion(gRenderer, expl, x, y)); // Creating an explosion at x and y coordinates.
}
bool Interstellar::checkCollision(SDL_Rect a, SDL_Rect b) // Takes two mover rectangles as arguments and checks if collision has occured.
{

    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}
void Interstellar::increaseScore(int seconds)
{
    static bool in = true;
    static bool fac = true;
    static int fact = 1;

    if (seconds % 1 == 0 && seconds % 3 != 0 && in == true)
    {
        cout << "Score: " << score << endl;
        score += fact;
        in = false;
    }

    if (seconds % 3 == 0)
        in = true;
}
Interstellar::~Interstellar()
{
    for (auto *asteroid : asteroids)
        delete asteroid;
    asteroids.clear();

    for (auto *enemy : enemies)
        delete enemy;
    enemies.clear();

    for (auto *explosion : explosions)
        delete explosion;
    explosions.clear();

    delete player;
}