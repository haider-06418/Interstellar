#include "game.hpp"
#include <vector>

bool Game::init()
{
    // Initialization flag
    bool success = true;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow("Interstellar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) // Initializing images.
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) // Initializing sound.
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool Game::loadMedia()
{
    // Loading success flag
    bool success = true;
    // Loading images and sounds.
    // Images will be sent to Unit class draw function.
    assets = loadTexture("assets.png");
    gTexture = loadTexture("bg.png");
    explosions = loadTexture("explosions.png");
    over = loadTexture("gameover.png");
    life = loadTexture("life.png");
    pause = loadTexture("gamepause.png");
    menu = loadTexture("menu.png");

    if (assets == NULL || gTexture == NULL)
    {
        printf("Unable to run due to error: %s\n", SDL_GetError());
        success = false;
    }
    bgMusic = Mix_LoadMUS("music.wav");

    if (bgMusic == NULL)
    {
        printf("Unable to load music: %s \n", Mix_GetError());
        success = false;
    }
    return success;
}

void Game::close()
{
    // Free loaded images
    SDL_DestroyTexture(assets);
    assets = NULL;
    SDL_DestroyTexture(gTexture);

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    Mix_FreeMusic(bgMusic);
    bgMusic = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *Game::loadTexture(std::string path)
{
    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void Game::run()
{
    bool quit = false;
    SDL_Event e;
    Interstellar *interstellar;
    GameMenu gamemenu(gRenderer, assets, menu);
    GameOver go(gRenderer, over);
    Life lf(gRenderer, life);
    GamePause gp(gRenderer, pause);
    // int lf_st;
    bool gamerun = false;
    bool gamepause = false;
    bool playerstatus = true;
    time_t start = time(0); // Time since start of the game.

    while (!quit)
    {
        // Handle events on queue

        while (SDL_PollEvent(&e) != 0)
        {

            // User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true; // Quiting game.
            }

            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN && gamerun == false && gamepause == false) // Starting game.
            {
                interstellar = new Interstellar(gRenderer, assets, gTexture, explosions); // Creating a new game.
                gamerun = true;                                                           // Setting game run to true.
                playerstatus = true;                                                      // Setting playerstatus to true.
            }
            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_RETURN && gamerun == true && gamepause == true && playerstatus == true) // Pausing game.
            {
                gamepause = false;
            }
            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE && gamepause == true) // Quiting game.
            {
                gamerun = false;
                gamepause = false;
                delete interstellar; // Deleting current game.
            }
            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE && gamepause == false && gamerun == true)
            {
                gamepause = true;
            }
            if (gamerun == true && gamepause == false) // Events when game is running.
            {

                if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
                {
                    interstellar->fire();
                }
                // Moving player.
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    interstellar->movePlayer(1);
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    interstellar->movePlayer(-1);
                }
                // if (e.type == SDL_MOUSEBUTTONDOWN)
                // {
                //     int xMouse, yMouse;
                //     SDL_GetMouseState(&xMouse, &yMouse);
                //     // interstellar->createExplosions(xMouse, yMouse);
                // }
            }
            if (Mix_PlayingMusic() == 0)
            {
                // Play the music
                Mix_PlayMusic(bgMusic, 2);
            }
        }
        SDL_RenderClear(gRenderer); // removes everything from renderer

        if (gamepause == true && playerstatus == true)
        {
            gp.draw(); // Showing pause screen.
            SDL_RenderPresent(gRenderer);
        }
        if (gamerun == true && gamepause == false)
        { // Calling game functions to create objects on screen.
            double seconds_since_start = difftime(time(0), start);
            // Creating objects.
            interstellar->createAsteroid(seconds_since_start);
            interstellar->createEnemy(seconds_since_start);
            interstellar->createHearts(seconds_since_start);
            interstellar->fireEnemy(seconds_since_start);
            interstellar->increaseScore(seconds_since_start);
            gamepause = interstellar->drawObjects();
            int LF = interstellar->life_status(); // Current health of player.
            lf.draw(LF);

            if (gamepause == true)
            {
                playerstatus = false;
                go.draw(); // When player dies.
            }
            SDL_RenderPresent(gRenderer);
        }
        else if (gamerun == false)
        {
            gamemenu.drawObjects(); // displays the updated renderer
            SDL_RenderPresent(gRenderer);
        }
        // displays the updated renderer
        SDL_Delay(30); // causes sdl engine to delay for specified miliseconds
    }
}
