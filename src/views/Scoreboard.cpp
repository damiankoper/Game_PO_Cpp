#include "Scoreboard.h"
#include "../engines/ViewEngine.h"
#include "../engines/GameInfo.h"
#include "../config.h"
#include <iostream>
#include <string>

void Scoreboard::render(SDL_Renderer *gRenderer)
{
  title->render(20, 20);
  for (auto b : buttons)
  {
    b->render();
  }
  for (int i = 0;i<score.size();i++){
    score[i]->render(60,140+i*60);
  }
}

void Scoreboard::handleEvent(SDL_Event *e)
{
  for (auto b : buttons)
  {
    b->handleEvent(e);
  }
}
void Scoreboard::init()
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
  title->loadFromRenderedText("Scoreboard", color, gFont);
  gFont = TTF_OpenFont(FONT.c_str(), 40);
  std::vector<statss> s = GameInfo::getInstance().readSave();
  score.clear();
  for (int i = 0; i < s.size(); i++)
  {
    Texture *temp = new Texture(ViewEngine::getInstance().getRenderer());
    temp->loadFromRenderedText(std::to_string(i+1) + ". " + s[i].name + " - " + std::to_string(s[i].score), color, gFont);
    score.push_back(temp);
  }
}
Scoreboard::Scoreboard()
{
  name = "scoreboard";
  //init();
}

Scoreboard::~Scoreboard()
{
}