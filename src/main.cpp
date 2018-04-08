#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "config.h"
#include "engines/ViewEngine.h"
#include "engines/GameInfo.h"
#include "views/MainMenu.h"
#include "views/Settings.h"
#include "views/Nickname.h"
#include "views/Pause.h"
#include "views/Game.h"
#include "views/Scoreboard.h"
#include "maps/Level1.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

ViewInterface *mainMenu;
ViewInterface *settings;
ViewInterface *nickname;
ViewInterface *scoreboard;
ViewInterface *game;
ViewInterface *pause;
MapInterface *level1;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;

void init()
{
	try
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		gWindow = SDL_CreateWindow("3 AS 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		int imgFlags = IMG_INIT_PNG;
		IMG_Init(imgFlags);
		TTF_Init();

		ViewEngine::getInstance().assignRenderer(gRenderer);
		ViewEngine::getInstance().assignWindow(gWindow);
	}
	catch (int i)
	{
		throw i;
	}
}
void loadInterfaces()
{
	level1 = new Level1();
	GameInfo::getInstance().setMap(level1);

	mainMenu = new MainMenu();
	settings = new Settings();
	nickname = new Nickname();
	scoreboard = new Scoreboard();
	game = new Game();
	pause = new Pause();
	ViewEngine::getInstance().addView(mainMenu);
	ViewEngine::getInstance().addView(settings);
	ViewEngine::getInstance().addView(nickname);
	ViewEngine::getInstance().addView(pause);
	ViewEngine::getInstance().addView(game);
	ViewEngine::getInstance().addView(scoreboard);
}

void loadMedia()
{
}

int main(int, char **)
{
	srand(time(NULL));
	init();
	loadInterfaces();
	loadMedia();
	ViewEngine::getInstance().changeView("game");
	SDL_Event e;
	while (!ViewEngine::getInstance().quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				ViewEngine::getInstance().exit();
			}
			else
			{
				ViewEngine::getInstance().handleEvent(&e);
			}
		}
		try
		{
			ViewEngine::getInstance().renderView();
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}