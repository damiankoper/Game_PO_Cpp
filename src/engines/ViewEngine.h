#pragma once
#include <SDL.h>
#include "../interfaces/ViewInterface.h"
#include <string>
#include <map>

/**
 * Singleton
 */
class ViewEngine
{
public:
  bool quit;
  void exit();
  void addView(ViewInterface *i);
  void removeView(std::string name);
  void changeView(std::string name);
  void updateView();
  void assignRenderer(SDL_Renderer *renderer);
  void assignWindow(SDL_Window *window);
  SDL_Renderer *getRenderer();
  SDL_Window *getWindow();
  void toggleFullscreen();
  void toggleOverlay();
  void setOverlay(std::string name);
  bool isOverlay();
  void renderView();
  void handleEvent(SDL_Event *e);

  static ViewEngine &getInstance();

private:
  ViewEngine();
  ViewEngine(const ViewEngine &);
  std::map<std::string, ViewInterface *> interfaces;
  ViewInterface *interface = NULL;
  ViewInterface *overlay = NULL;
  bool renderOverlay;
  SDL_Renderer *gRenderer;
  SDL_Window *gWindow;
  bool fullscreen;
};