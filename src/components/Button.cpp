#include <SDL.h>
#include "../engines/ViewEngine.h"
#include "Button.h"
#include <iostream>
#include <string>
#include "../config.h"
#include <ctime>

Button::Button(){
  borderX = 10;
  borderY = 0;
  active = false;
}

Button *Button::setPosition(int x, int y)
{
  mPosition.x = x;
  mPosition.y = y;
  return this;
}

Button *Button::setTexture(std::string text, int size, SDL_Color textColor, SDL_Color _bgColor)
{
  TTF_Font *gFont = TTF_OpenFont(FONT.c_str(), size);
  gTexture = new Texture(ViewEngine::getInstance().getRenderer());
  gTexture->loadFromRenderedTextShaded(text.c_str(), textColor, gFont, _bgColor);
  bgColor = _bgColor;
  return this;
}
Button *Button::setBorder(int x, int y)
{
  borderX = x;
  borderY = y;
  return this;
}
Button *Button::handleEvent(SDL_Event *e)
{
  if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
  {
    int x, y;
    SDL_GetMouseState(&x, &y);

    bool inside = true;
    if (x < mPosition.x - borderX)
    {
      inside = false;
    }
    else if (x > mPosition.x + gTexture->getWidth() + borderX)
    {
      inside = false;
    }
    else if (y < mPosition.y - borderY)
    {
      inside = false;
    }
    else if (y > mPosition.y + gTexture->getHeight() + borderY)
    {
      inside = false;
    }
    if (!inside)
    {
      active = false;
    }
    else
    {
      switch (e->type)
      {
      case SDL_MOUSEMOTION:
        break;

      case SDL_MOUSEBUTTONDOWN:
        std::cout << "DOWN" << std::endl;
        active = true;
        break;

      case SDL_MOUSEBUTTONUP:
        std::cout << "UP" << std::endl;
        if (active)
        {
          callback();
        }
        active = false;
        break;
      }
    }
  }
  return this;
}
void Button::render()
{
  SDL_SetRenderDrawColor(ViewEngine::getInstance().getRenderer(),
                         bgColor.r, bgColor.g, bgColor.b, bgColor.a);
  SDL_Rect border = {mPosition.x - borderX, mPosition.y - borderY,
                     gTexture->getWidth() + 2 * borderX, gTexture->getHeight() + 2 * borderY};
  SDL_RenderFillRect(ViewEngine::getInstance().getRenderer(),
                     &border);
  gTexture->render(mPosition.x, mPosition.y);
}
Button *Button::onClick(void (*cb)(void))
{
  callback = cb;
  return this;
}