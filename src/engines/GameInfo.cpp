#include "GameInfo.h"
#include "../engines/ViewEngine.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <algorithm>
#include "../components/Timer.h"

GameInfo::GameInfo()
{
    player = "Stranger";
    gameTimer = new Timer();
}
GameInfo::GameInfo(const GameInfo &)
{
}
GameInfo &GameInfo::getInstance()
{
    static GameInfo engine;
    return engine;
}
std::string GameInfo::getPlayer()
{
    return player;
}
void GameInfo::setPlayer(std::string name)
{
    player = name;
}

MapInterface *GameInfo::getMap()
{
    return map;
}

void GameInfo::setMap(MapInterface *_map)
{
    map = _map;
}

int GameInfo::getPointsAll()
{
    return pointsAll;
}
int GameInfo::getPoints()
{
    return points;
}
void GameInfo::setPointsAll(int p)
{
    pointsAll = p;
}
void GameInfo::addPoint()
{
    points++;
}
void GameInfo::setStats(int _pointsAll)
{
    gameTimer->start();
    pointsAll = _pointsAll;
    points = 0;
}
double GameInfo::getGameTime()
{
    return gameTimer->getTicks() / 1000.;
}
std::string GameInfo::getTimeString()
{
    Uint32 t = gameTimer->getTicks();
    int ms = t % 1000;
    int s = (t / 1000) % 60;
    int m = (t / 60000) % 3600;
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << m << ':' << std::setw(2) << std::setfill('0') << s << '.' << ms;
    return ss.str();
}
Timer *GameInfo::getTimer()
{
    return gameTimer;
}

std::vector<statss> GameInfo::readSave()
{
    std::vector<statss> v;
    std::ifstream input("save.XD", std::ios::binary);
    if (input.good())
    {
        statss s;
        input.read((char *)&s, sizeof(statss));
        while (input.gcount() > 0)
        {
            v.push_back(s);
            std::cout << s.score << std::endl;
            input.read((char *)&s, sizeof(statss));
        }
    }
    input.close();
    bestScore = v;
    return v;
}
void GameInfo::writeSave(std::vector<statss> statsss)
{
    std::ofstream input("save.XD", std::ios::binary | std::ios::trunc);
    if (input.good())
    {
        for (auto s : statsss)
        {
            input.write((char *)&s, sizeof(statss));
        }
    }
    input.close();
}
void GameInfo::handleFinish()
{
    readSave();
    statss s;
    strcpy(s.name, player.c_str());
    s.score = (points * 1000+1000) / getGameTime();
    bestScore.push_back(s);
    sort(bestScore.begin(), bestScore.end(), [](const statss s1, const statss s2) {
        return s1.score > s2.score;
    });
    if (bestScore.size() > 5)
        bestScore.erase(bestScore.begin() + 5, bestScore.end());
    writeSave(bestScore);
    ViewEngine::getInstance().changeView("scoreboard");
}

std::vector<statss> GameInfo::getSave(){
    return bestScore;
}