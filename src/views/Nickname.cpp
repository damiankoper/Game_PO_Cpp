#include "Nickname.h"
#include "../engines/ViewEngine.h"
#include "../engines/GameInfo.h"
#include "../config.h"
#include <iostream>
#include <string>

void Nickname::render(SDL_Renderer *gRenderer)
{
  title->render(20, 20);
  nickname->render((SCREEN_WIDTH - nickname->getWidth()) / 2, (SCREEN_HEIGHT - nickname->getHeight()) / 2);
  for (auto b : buttons)
  {
    b->render();
  }
}

void Nickname::handleEvent(SDL_Event *e)
{
  for (auto b : buttons)
  {
    b->handleEvent(e);
  }
  if (e->type == SDL_KEYDOWN)
  {
    if (e->key.keysym.sym == SDLK_BACKSPACE && GameInfo::getInstance().getPlayer().length() > 0)
    {
      std::string player = GameInfo::getInstance().getPlayer();
      player.pop_back();
      if (player.length() == 0)
        player = " ";
      GameInfo::getInstance().setPlayer(player);
    }
  }
  else if (e->type == SDL_TEXTINPUT)
  {
    std::string player = GameInfo::getInstance().getPlayer();
    if (player.length() == 1 && player[0] == ' ')
      player = "";
    GameInfo::getInstance().setPlayer(player + e->text.text);
  }
  ViewEngine::getInstance().updateView();
}
void Nickname::init()
{
  buttons.clear();
  //View config globals
  gFont = TTF_OpenFont(FONT.c_str(), 80);
  TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);
  SDL_Color color = {0, 0, 0};

  //Buttons
  Button *button = new Button();
  button->setTexture("Main Menu", 40, {255, 255, 255}, {0, 0, 0})
      ->setPosition(30, SCREEN_HEIGHT - 70)
      ->onClick([]() {
        ViewEngine::getInstance().changeView("mainMenu");
      });
  buttons.push_back(button);

  //Labels
  title = new Texture(ViewEngine::getInstance().getRenderer());
  title->loadFromRenderedText("Set Nickname", color, gFont);

  gFont = TTF_OpenFont(FONT.c_str(), 40);
  nickname = new Texture(ViewEngine::getInstance().getRenderer());
  nickname->loadFromRenderedText(GameInfo::getInstance().getPlayer(), color, gFont);
}
Nickname::Nickname()
{
  name = "nickname";
  //init();
}

Nickname::~Nickname()
{
}