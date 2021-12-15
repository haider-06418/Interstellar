#include <SDL.h>
#include "Background.hpp"
#include <Windows.h>
#include <iostream>
using namespace std;
class GameMenu
{
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    SDL_Texture *gTexture;

    Background background;

public:
    GameMenu(SDL_Renderer *, SDL_Texture *, SDL_Texture *);
    void drawObjects();
};