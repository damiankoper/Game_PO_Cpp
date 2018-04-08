#include "Square.h"
#include "Vector.h"
#include <SDL.h>
#include <iostream>
#include <ctime>
Square::Square() {}

Square::Square(Vector position, Vector speed, int size, int mass, double breakMtp, int accTime)
    : position(position), speed(speed), breakMtp(breakMtp), accTime(accTime), size(size), mass(mass)
{
    velocity = Vector(0, 0);
    jump = false;
    Uint8 colorHexR = (rand() % 200);
    Uint8 colorHexG = (rand() % 200);
    Uint8 colorHexB = (rand() % 200);
    bgColor = {colorHexR, colorHexG, colorHexB};
}

SDL_Rect Square::getRect()
{
    return {position.x, position.y, size, size};
}

void Square::addPosition(double timeStep)
{
    //std::cout << velocity.x << std::endl;
    position += velocity * timeStep;
}

void Square::move()
{
    bool move = false;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_LEFT])
    {
        velocity.x = -speed.x;
        move = true;
    }
    if (keystate[SDL_SCANCODE_RIGHT])
    {
        velocity.x = speed.x;
        move = true;
    }
    if (keystate[SDL_SCANCODE_SPACE] && !jump)
    {
        velocity.y = -speed.y;
        jump = true;
    }
    /* if (keystate[SDL_SCANCODE_UP])
    {
        position.y -= velocityTime.y;
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        position.y += velocityTime.y;
    } */
    if (!move)
    {
        velocity.x *= breakMtp;
    }
}
void Square::processCollision(Vector coll)
{
    position += coll;

    //Corners handling
    if (velocity.y < 0 && coll.y < 0)
        coll.y = 0;
    else if (velocity.y > 0 && coll.y > 0)
        coll.y = 0;
    if (coll.y < 0)
        jump = false;
    velocity.resetNonZero(coll);
}

double Square::getMass()
{
    return mass;
}
Vector &Square::getPosition()
{
    return position;
}
Vector &Square::getVelocity()
{
    return velocity;
}
SDL_Color Square::getColor()
{
    return bgColor;
}
Square::~Square() {}