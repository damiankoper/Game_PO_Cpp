#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "../interfaces/ViewInterface.h"
#include "../components/Texture.h"
#include "../components/Button.h"
#include "../components/Timer.h"
#include "../components/Square.h"


class Game : public ViewInterface
{
public:
  Game();
  ~Game();
  void render(SDL_Renderer *gRenderer);
  void handleEvent(SDL_Event *e);
  void init();
  Square* maxRight();
  void calculateOffset();


private:
  TTF_Font *gFont;
  TTF_Font *gFontOutline;
  Texture *time;
  Texture *points;
  Timer *timer;
  int offsetX;
  int border;
  std::vector<Square *> squares;
};