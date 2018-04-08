#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "../interfaces/MapInterface.h"
class Level : public MapInterface
{
  public:
    Level(std::string name);
    ~Level();
    void init();

  private:
};