#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "../interfaces/ViewInterface.h"
#include "../components/Texture.h"
#include "../components/Button.h"
class Nickname : public ViewInterface
{
public:
  Nickname();
  ~Nickname();
  void render(SDL_Renderer *gRenderer);
  void handleEvent(SDL_Event *e);
  void init();

private:
  Texture *title;
  Texture *nickname;
  TTF_Font *gFont;
  std::vector<Button *> buttons;
};