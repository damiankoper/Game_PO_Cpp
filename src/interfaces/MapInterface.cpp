#include "MapInterface.h"
#include <fstream>
#include <sstream>
#include <string>
std::string MapInterface::getName()
{
    return name;
}

void MapInterface::setName(std::string _name)
{
    name = _name;
}

std::vector<SDL_Rect *> MapInterface::getGround()
{
    return ground;
}
std::vector<SDL_Rect *> *MapInterface::getPoints()
{
    return &points;
}
SDL_Rect *MapInterface::getFinish()
{
    return finish;
}

std::vector<SDL_Rect *> MapInterface::loadRects(std::string what)
{
    std::vector<SDL_Rect *> rects;
    std::ifstream rectsF("assets/maps/" + name + "." + what);
    std::string line;
    while (getline(rectsF, line))
    {
        SDL_Rect *rect = new SDL_Rect;
        std::istringstream ss(line);
        char c1, c2, c3;
        ss >> rect->x >> c1 >>
            rect->y >> c2 >>
            rect->w >> c3 >>
            rect->h;
        rects.push_back(rect);
    }
    rectsF.close();
    return rects;
}

MapInterface::MapInterface()
{
}

MapInterface::~MapInterface()
{
}