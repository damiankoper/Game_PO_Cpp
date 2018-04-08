#include "MainMenu.h"
#include "../engines/ViewEngine.h"
#include "../engines/GameInfo.h"
#include "../config.h"
#include <iostream>
void MainMenu::render(SDL_Renderer *gRenderer)
{
    title->render(20, 20);
    greetings->render(20, 110);
    for (auto b : buttons)
    {
        b->render();
    }
}

void MainMenu::handleEvent(SDL_Event *e)
{
    for (auto b : buttons)
    {
        b->handleEvent(e);
    }
}

void MainMenu::init()
{

    buttons.clear();
    //////////View config globals
    gFont = TTF_OpenFont(FONT.c_str(), 80);
    TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);
    SDL_Color color = {0, 0, 0};

    //////////Buttons
    //Settings
    Button *button = new Button();
    button->setTexture("Settings", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 140)
        ->onClick([]() {
            ViewEngine::getInstance().changeView("settings");
        });
    buttons.push_back(button);

    //Exit
    button = new Button();
    button->setTexture("Exit", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 70)
        ->onClick([]() {
            ViewEngine::getInstance().exit();
        });
    buttons.push_back(button);
  //Nickname
    button = new Button();
    button->setTexture("Scoreboard", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 210)
        ->onClick([]() {
            ViewEngine::getInstance().changeView("scoreboard");
        });
    buttons.push_back(button);
    //Nickname
    button = new Button();
    button->setTexture("Set nickname", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 280)
        ->onClick([]() {
            ViewEngine::getInstance().changeView("nickname");
        });
    buttons.push_back(button);

    //New Game
    button = new Button();
    button->setTexture("New Game", 40, {255, 255, 255}, {0, 0, 0})
        ->setPosition(30, SCREEN_HEIGHT - 350)
        ->onClick([]() {
            ViewEngine::getInstance().changeView("game");
        });
    buttons.push_back(button);
    //////////Labels
    title = new Texture(ViewEngine::getInstance().getRenderer());
    title->loadFromRenderedText("Main Menu", color, gFont);

    gFont = TTF_OpenFont(FONT.c_str(), 40);
    greetings = new Texture(ViewEngine::getInstance().getRenderer());
    greetings->loadFromRenderedText("Hello " + GameInfo::getInstance().getPlayer(), color, gFont);
}

MainMenu::MainMenu()
{
    name = "mainMenu";
    //init();
}

MainMenu::~MainMenu()
{
}
