#include "ViewEngine.h"
#include <stdexcept>
#include <iostream>

ViewEngine::ViewEngine()
{
    fullscreen = false;
    quit = false;
    renderOverlay = false;
}
ViewEngine::ViewEngine(const ViewEngine &)
{
}

ViewEngine &ViewEngine::getInstance()
{
    static ViewEngine engine;
    return engine;
}

void ViewEngine::exit()
{
    quit = true;
}
void ViewEngine::toggleOverlay()
{
    renderOverlay = !renderOverlay;
}
bool ViewEngine::isOverlay()
{
    return renderOverlay;
}
void ViewEngine::addView(ViewInterface *i)
{
    interfaces[i->getName()] = i;
}
void ViewEngine::removeView(std::string name)
{
    interfaces.erase(name);
}
void ViewEngine::changeView(std::string name)
{
    interface = interfaces[name];
    interface->init();
}
void ViewEngine::setOverlay(std::string name)
{
    std::cout << name;
    overlay = interfaces[name];
    overlay->init();
}
void ViewEngine::updateView()
{
    interface->init();
}
void ViewEngine::assignRenderer(SDL_Renderer *renderer)
{
    gRenderer = renderer;
}
SDL_Renderer *ViewEngine::getRenderer()
{
    return gRenderer;
}
void ViewEngine::assignWindow(SDL_Window *window)
{
    gWindow = window;
}
SDL_Window *ViewEngine::getWindow()
{
    return gWindow;
}
void ViewEngine::renderView()
{
    if (interface != NULL)
    {
        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render View
        interface->render(gRenderer);

        //Render overlay
        if (renderOverlay)
            overlay->render(gRenderer);

        //Copy to front
        SDL_RenderPresent(gRenderer);
        SDL_Delay(5);
    }
    else
        throw std::runtime_error("Null interface");
}
void ViewEngine::handleEvent(SDL_Event *e)
{
    if (interface != NULL)
    {
        interface->handleEvent(e);
        if (renderOverlay)
            overlay->handleEvent(e);
    }
    else
        throw std::runtime_error("Null interface");
}
void ViewEngine::toggleFullscreen()
{
    Uint32 flags = fullscreen ? 0 : SDL_WINDOW_FULLSCREEN;
    fullscreen = !fullscreen;
    SDL_SetWindowFullscreen(gWindow, flags);
}