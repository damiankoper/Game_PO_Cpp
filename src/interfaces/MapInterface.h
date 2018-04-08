#pragma once
#include <SDL.h>
#include <string>
#include <vector>

class MapInterface
{
public:
  virtual void init() = 0;
  std::string getName();
  void setName(std::string name);

  std::vector<SDL_Rect *> loadRects(std::string what);
  std::vector<SDL_Rect *> getGround();
  std::vector<SDL_Rect *> *getPoints();
  SDL_Rect *getFinish();

  MapInterface();
  ~MapInterface();

protected:
  std::string name;
  //Map geometry
  std::vector<SDL_Rect *> ground;
  std::vector<SDL_Rect *> points;
  SDL_Rect *finish;
};