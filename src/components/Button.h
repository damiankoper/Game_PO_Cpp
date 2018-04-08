#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "../components/Texture.h"

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class Button
{
public:
  Button();
  Button *setPosition(int x, int y);
  Button *handleEvent(SDL_Event *e);
  void render();
  Button *setTexture(std::string text, int size, SDL_Color, SDL_Color _bgColor);
  Button *onClick(void (*cb)(void));
  Button *setBorder(int x, int y);

private:
  SDL_Point mPosition;
  Texture *gTexture;

  int borderX;
  int borderY;

  SDL_Color bgColor;

  bool active;

  void (*callback)(void); //click callback function
};