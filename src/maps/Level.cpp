#include "Level.h"
#include "../config.h"
#include <string>

void Level::init()
{
  //Double loading prevention
  ground.clear();
  points.clear();

  //Ground
  ground = loadRects("ground");

  //Points
  points = loadRects("points");

  //Finish
  finish = loadRects("finish")[0];
}
Level::Level(std::string name)
{
  setName(name);
  //init();
}

Level::~Level()
{
}