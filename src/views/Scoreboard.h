#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "../interfaces/ViewInterface.h"
#include "../components/Texture.h"
#include "../components/Button.h"
class Scoreboard : public ViewInterface
{
public:
  Scoreboard();
  ~Scoreboard();
  void render(SDL_Renderer *gRenderer);
  void handleEvent(SDL_Event *e);
  void init();

private:
  Texture *title;
  std::vector<Texture *> score;
  TTF_Font *gFont;
  std::vector<Button *> buttons;
};