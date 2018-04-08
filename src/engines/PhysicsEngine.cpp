#include "PhysicsEngine.h"
#include "../components/Square.h"
#include "../components/Vector.h"
#include "../engines/GameInfo.h"
#include "../engines/ViewEngine.h"
#include <SDL.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

PhysicsEngine::PhysicsEngine()
{
    gravityForce = Vector(0, 1);
}
PhysicsEngine::PhysicsEngine(const PhysicsEngine &)
{
}

PhysicsEngine &PhysicsEngine::getInstance()
{
    static PhysicsEngine engine;
    return engine;
}
void PhysicsEngine::handlePhysics(std::vector<Square *> squares,
                                  std::vector<SDL_Rect> collisionObjects,
                                  std::vector<SDL_Rect *> *pointsObjects,
                                  SDL_Rect finish,
                                  double timeStep)
{
    for (Square *s : squares)
    {
        //gravity

        s->getVelocity() += gravityForce * s->getMass() * timeStep;

        //collisions
        SDL_Rect r = s->getRect();
        Vector coll = Vector(0, 0);
        for (Square *sc : squares)
        {
            if (s == sc)
                continue;
            SDL_Rect rc = sc->getRect();
            coll += collision(&r, &rc);
        }
        s->processCollision(coll);
        coll = Vector(0, 0);
        r = s->getRect();
        for (SDL_Rect c : collisionObjects)
        {
            coll += collision(&r, &c);
        }
        s->processCollision(coll);
        //points
        for (size_t i = 0; i < pointsObjects->size(); i++)
        {
            if (collision(&r, pointsObjects->at(i)) != 0)
            {
                GameInfo::getInstance().addPoint();
                pointsObjects->erase(pointsObjects->begin() + i);
            }
        }
        if (collision(&r, &finish) != 0)
        {
            GameInfo::getInstance().handleFinish();
        }
    }
}
Vector PhysicsEngine::collision(SDL_Rect *A, SDL_Rect *B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A->x;
    rightA = A->x + A->w;
    topA = A->y;
    bottomA = A->y + A->h;

    leftB = B->x;
    rightB = B->x + B->w;
    topB = B->y;
    bottomB = B->y + B->h;

    if (bottomA <= topB)
    {
        return Vector(0, 0);
    }

    if (topA >= bottomB)
    {
        return Vector(0, 0);
    }

    if (rightA <= leftB)
    {
        return Vector(0, 0);
    }

    if (leftA >= rightB)
    {
        return Vector(0, 0);
    }

    std::vector<Vector> overlap;
    overlap.push_back(Vector(0, topB - bottomA));
    overlap.push_back(Vector(0, bottomB - topA));
    overlap.push_back(Vector(leftB - rightA, 0));
    overlap.push_back(Vector(rightB - leftA, 0));
    return *std::min_element(overlap.begin(), overlap.end());
}
