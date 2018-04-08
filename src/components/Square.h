#pragma once
#include <SDL.h>
#include "Vector.h"

class Square
{
public:
  Square();
  Square(Vector position, Vector speed, int size, int mass, double breakMtp, int accTime);
  SDL_Rect getRect();
  void move();
  void addPosition(double timeStep);
  double getMass();
  Vector &getPosition();
  Vector &getVelocity();
  SDL_Color getColor();
  void processCollision(Vector coll);
  ~Square();

private:
  Vector velocity;
  Vector position;
  int size;
  double mass;
  Vector speed;
  double breakMtp;
  int accTime;
  bool jump;
  SDL_Color bgColor;
};