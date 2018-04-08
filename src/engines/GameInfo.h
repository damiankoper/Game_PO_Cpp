#pragma once
#include <SDL.h>
#include <string>
#include "../interfaces/MapInterface.h"
#include "../components/Timer.h"

struct statss
{
    int score;
    char name[100];
};

/**
 * Singleton
 */
class GameInfo
{
public:
  std::string getPlayer();
  void setPlayer(std::string name);

  MapInterface* getMap();
  void setMap(MapInterface *_map);

  int getPointsAll();
  int getPoints();
  double getGameTime();
  std::string getTimeString();
  void setPointsAll(int p);
  void addPoint();
  Timer* getTimer();
  void setStats(int _pointsAll);
  std::vector<statss> readSave();
  void writeSave(std::vector<statss> statsss);
  std::vector<statss> getSave();

  void handleFinish();
  static GameInfo &getInstance();

private:
  GameInfo();
  GameInfo(const GameInfo &);
  std::string player;
  std::vector<statss> bestScore;
  int points;
  int pointsAll;
  Timer *gameTimer;

  MapInterface *map;
};