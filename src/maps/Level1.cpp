#include "Level1.h"
#include "../config.h"

void Level1::init()
{
  //Double loading prevention
  ground.clear();
  points.clear();

  SDL_Rect rect = {0, SCREEN_HEIGHT - 100, 10000, 100};
  ground.push_back(rect);
  rect = {0, SCREEN_HEIGHT - 500, 100, 500};
  ground.push_back(rect);
  rect = {500, SCREEN_HEIGHT - 200, 100, 100};
  ground.push_back(rect);

  SDL_Rect *rect_p = new SDL_Rect({300, SCREEN_HEIGHT - 150, 20, 20});
  points.push_back(rect_p);

  finish = {600, SCREEN_HEIGHT - 200, 80, 80};
}
Level1::Level1()
{
  name = "level1";
  //init();
}

Level1::~Level1()
{
}