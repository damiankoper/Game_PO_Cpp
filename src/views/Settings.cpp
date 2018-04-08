#include "Settings.h"
#include "../engines/ViewEngine.h"
#include "../config.h"
#include <iostream>
void Settings::render(SDL_Renderer *gRenderer)
{
    title->render(20, 20);
    for (auto b : buttons)
    {
        b->render();
    }
}

void Settings::handleEvent(SDL_Event *e)
{
    for (auto b : buttons)
    {
        b->handleEvent(e);
    }
}

void Settings::init()
{
    buttons.clear();
    //View config globals
    gFont = TTF_OpenFont(FONT.c_str(), 80);
    TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);
    SDL_Color color = {0, 0, 0};

    //Buttons
    Button *button = new Button();
    button->setTexture("Main Menu", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 140)
        ->onClick([]() {
            ViewEngine::getInstance().changeView("mainMenu");
        });
    buttons.push_back(button);

    button = new Button();
    button->setTexture("Fullscreen", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 70)
        ->onClick([]() {
            ViewEngine::getInstance().toggleFullscreen();
        });
    buttons.push_back(button);

    //Labels
    title = new Texture(ViewEngine::getInstance().getRenderer());
    title->loadFromRenderedText("Settings", color, gFont);
}

Settings::Settings()
{
    name = "settings";
    //init();
}
Settings::~Settings()
{
}