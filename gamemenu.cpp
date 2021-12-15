#include "gamemenu.hpp"


GameMenu::GameMenu(SDL_Renderer *renderer, SDL_Texture *asst, SDL_Texture *gTex) : gRenderer(renderer), assets(asst), gTexture(gTex), background(renderer, gTex, 0)
{
}

void GameMenu::drawObjects()
{
    background.draw(true);
}
