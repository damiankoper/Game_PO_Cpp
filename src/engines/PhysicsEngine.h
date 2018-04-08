#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "../components/Square.h"
#include "../components/Vector.h"

/**
 * Singleton
 */
class PhysicsEngine
{
public:
  static PhysicsEngine &getInstance();
  void handlePhysics(std::vector<Square *> squares,
                     std::vector<SDL_Rect *> collisionObjects,
                     std::vector<SDL_Rect *> *pointsObjects,
                     SDL_Rect *finish,
                     double timeStep);

private:
  PhysicsEngine();
  PhysicsEngine(const PhysicsEngine &);
  Vector collision(SDL_Rect *A, SDL_Rect *B);
  Vector gravityForce;
};