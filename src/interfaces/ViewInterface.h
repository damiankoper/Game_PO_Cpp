#pragma once  
#include <SDL.h>
#include <string>

class ViewInterface
{
  public:
    virtual void render(SDL_Renderer *gRenderer) = 0;
    virtual void handleEvent(SDL_Event *e) = 0;
    virtual void init() = 0;
    std::string getName();
    void setName(std::string name);
    ViewInterface();
    ~ViewInterface();

  protected:
    std::string name;

};