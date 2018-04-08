#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "../interfaces/MapInterface.h"
class Level1 : public MapInterface
{
  public:
    Level1();
    ~Level1();
    void init();

  private:
};