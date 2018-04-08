#include "MapInterface.h"

std::string MapInterface::getName()
{
    return name;
}

void MapInterface::setName(std::string _name)
{
    name = _name;
}

std::vector<SDL_Rect> MapInterface::getGround()
{
    return ground;
}
std::vector<SDL_Rect *> *MapInterface::getPoints()
{
    return &points;
}
SDL_Rect MapInterface::getFinish()
{
    return finish;
}

MapInterface::MapInterface()
{
}

MapInterface::~MapInterface()
{
}