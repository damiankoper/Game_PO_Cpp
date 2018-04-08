#include "Game.h"
#include "../engines/ViewEngine.h"
#include "../engines/PhysicsEngine.h"
#include "../engines/GameInfo.h"
#include "../components/Square.h"
#include "../config.h"
#include <iostream>
void Game::render(SDL_Renderer *gRenderer)
{
    //FPS independent movement calculations
    Uint32 ts = timer->getTicks();
    double timeStep = (ts / 1000.);

    timer->start();

    //Info HUD
    std::string pointsString = std::to_string(GameInfo::getInstance().getPoints()) +
                               "/" + std::to_string(GameInfo::getInstance().getPointsAll());
    time->loadFromRenderedText("Score: " + pointsString, {0, 0, 0}, gFont);
    time->render(20, 20);

    time->loadFromRenderedText("Time: " + GameInfo::getInstance().getTimeString(), {0, 0, 0}, gFont);
    time->render(20, 45);

    //Ground
    SDL_SetRenderDrawColor(ViewEngine::getInstance().getRenderer(), 0, 0, 0, 1);
    std::vector<SDL_Rect> ground = GameInfo::getInstance().getMap()->getGround();
    for (auto &g : ground)
    {
        g.x += offsetX;
        SDL_RenderFillRect(ViewEngine::getInstance().getRenderer(), &g);
    }

    //Points
    SDL_SetRenderDrawColor(ViewEngine::getInstance().getRenderer(), 0, 0xFF, 0xFF, 1);
    std::vector<SDL_Rect *> *points = GameInfo::getInstance().getMap()->getPoints();
    for (auto p : *points)
    {
        SDL_Rect tempRect = *p;
        tempRect.x += offsetX;
        SDL_RenderFillRect(ViewEngine::getInstance().getRenderer(), &tempRect);
    }

    //Finish
    SDL_SetRenderDrawColor(ViewEngine::getInstance().getRenderer(), 255, 0, 0, 1);
    SDL_Rect finish = GameInfo::getInstance().getMap()->getFinish();
    finish.x += offsetX;
    SDL_RenderFillRect(ViewEngine::getInstance().getRenderer(), &finish);

    for (auto &s : squares)
    {
        SDL_SetRenderDrawColor(ViewEngine::getInstance().getRenderer(), s->getColor().r, s->getColor().g, s->getColor().b, 1);
        SDL_Rect squareRect = s->getRect();
        squareRect.x += offsetX;
        SDL_RenderFillRect(ViewEngine::getInstance().getRenderer(), &squareRect);
    }

    //Dont move and do physics if render time is less than 1ms or overlay
    if (ts == 0 || ViewEngine::getInstance().isOverlay())
        return;

    std::cout << ts << std::endl;

    //Camera offset
    calculateOffset();

    //Squares as movable characters
    for (auto &s : squares)
    {
        s->move();
        s->addPosition(timeStep);
    }
    PhysicsEngine::getInstance().handlePhysics(squares,
                                               GameInfo::getInstance().getMap()->getGround(),
                                               GameInfo::getInstance().getMap()->getPoints(),
                                               GameInfo::getInstance().getMap()->getFinish(),
                                               ts);
}

void Game::handleEvent(SDL_Event *e)
{
    switch (e->type)
    {
    case SDL_KEYUP:
        printf("Key release detected\n");
        if (e->key.keysym.sym == SDLK_ESCAPE)
        {
            ViewEngine::getInstance().toggleOverlay();
            if (ViewEngine::getInstance().isOverlay())
                GameInfo::getInstance().getTimer()->pause();
            else
                GameInfo::getInstance().getTimer()->unpause();
        }
        break;
    }
}

void Game::init()
{
    //View config globals
    timer = new Timer();
    offsetX = 50;
    border = 200;
    gFont = TTF_OpenFont(FONT.c_str(), 20);
    GameInfo::getInstance().getMap()->init();

    ViewEngine::getInstance().setOverlay("pause");
    //ViewEngine::getInstance().toggleOverlay();

    GameInfo::getInstance().setStats(GameInfo::getInstance().getMap()->getPoints()->size());

    time = new Texture(ViewEngine::getInstance().getRenderer());
    points = new Texture(ViewEngine::getInstance().getRenderer());

    squares.clear();
    Square *square = new Square(Vector(10, 10), Vector(600, 1000), 50, 4, 0.99, 1);
    squares.push_back(square);
    square = new Square(Vector(80, 80), Vector(500, 1000), 60, 4, 0.9, 1);
    squares.push_back(square);
    square = new Square(Vector(160, 80), Vector(700, 1000), 80, 3, 0.95, 1);
    squares.push_back(square);
}

Square *Game::maxRight()
{
    Square *max = NULL;
    for (auto s : squares)
    {
        if (max == NULL)
            max = s;
        else
        {
            SDL_Rect r = s->getRect();
            SDL_Rect rm = max->getRect();
            if (r.x + r.w > rm.x + rm.w)
            {
                max = s;
            }
        }
    }
    return max;
}
void Game::calculateOffset()
{
    SDL_Rect s = maxRight()->getRect();
    if (s.x + offsetX < border)
        offsetX = -(s.x - border);
    if (s.x + s.w + offsetX > SCREEN_WIDTH - border)
        offsetX = -(s.x + s.w - SCREEN_WIDTH + border);
}
Game::Game()
{
    //init();
    name = "game";
}
Game::~Game()
{
}