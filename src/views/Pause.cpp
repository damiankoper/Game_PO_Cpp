#include "Pause.h"
#include "../engines/ViewEngine.h"
#include "../engines/GameInfo.h"
#include "../config.h"
#include <iostream>
void Pause::render(SDL_Renderer *gRenderer)
{
    SDL_SetRenderDrawBlendMode(ViewEngine::getInstance().getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ViewEngine::getInstance().getRenderer(), 255, 255, 255, 128);
    SDL_RenderFillRect(ViewEngine::getInstance().getRenderer(), &bgRect);
    SDL_SetRenderDrawBlendMode(ViewEngine::getInstance().getRenderer(), SDL_BLENDMODE_NONE);
    title->render(20, 20);
    for (auto b : buttons)
    {
        b->render();
    }
}

void Pause::handleEvent(SDL_Event *e)
{
    for (auto b : buttons)
    {
        b->handleEvent(e);
    }
}

void Pause::init()
{
    buttons.clear();
    //View config globals
    gFont = TTF_OpenFont(FONT.c_str(), 80);
    TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);
    SDL_Color color = {0, 0, 0};

    //Buttons
    Button *button = new Button();
    button->setTexture("Resume", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 140)
        ->onClick([]() {
            ViewEngine::getInstance().toggleOverlay();
            GameInfo::getInstance().getTimer()->unpause();
        });
    buttons.push_back(button);

    button = new Button();
    button->setTexture("Main menu", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 70)
        ->onClick([]() {
            ViewEngine::getInstance().changeView("mainMenu");
            ViewEngine::getInstance().toggleOverlay();
        });
    buttons.push_back(button);

    //Labels
    title = new Texture(ViewEngine::getInstance().getRenderer());
    title->loadFromRenderedText("Pause", color, gFont);
    //BG
    bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

Pause::Pause()
{
    name = "pause";
    //init();
}
Pause::~Pause()
{
}