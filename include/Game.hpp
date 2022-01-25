#pragma once

#include "MazeGen.hpp"
#include "Music.hpp"
#include "Sound.hpp"
#include "TileType.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <queue>

class Game
{
	const char *FILE = "level";
	static size_t const MAZE_WIDTH = 53;
	static size_t const MAZE_HEIGHT = 31;
	static int32_t const TILE_SIZE = 24;
	int32_t SCREEN_WIDTH = MAZE_WIDTH * TILE_SIZE;
	int32_t SCREEN_HEIGHT = MAZE_HEIGHT * TILE_SIZE;
	static size_t const TILE_COUNT = MAZE_WIDTH * MAZE_HEIGHT;
	// int gameMapTiles[TILE_COUNT] = {};
	std::vector<uint32_t> gameMapTiles = {};
	std::vector<uint32_t> nxtLvlMap = {};
	// std::vector<std::vector<uint32_t>> gameMapTiles = {};

	TTF_Font *gameFont = nullptr;

	Music *MainMusicTrack;
	Sound *SelectSound;
	Sound *StepSound;
	Sound *startSound;
	Sound *finishSound;

	SDL_Surface *fontSurface = nullptr;
	SDL_Surface *gameMapSur = nullptr;
	SDL_Surface *wallTile = nullptr;
	SDL_Surface *exitTile = nullptr;


	// std::queue<std::vector<uint32_t>> maps; // napravit queue mapa

	MazeGenerator maze;

	bool menu = true;
	bool game = false;
	bool pause = false;
	bool quit = false;

	SDL_Window *window = nullptr;

	SDL_Renderer *renderer = nullptr;

	SDL_Texture *pauseTex = nullptr;
	SDL_Texture *menuTex = nullptr;
	SDL_Texture *playerTex = nullptr;
	SDL_Texture *gameMapTex = nullptr;
	SDL_Texture *background = nullptr;
	SDL_Texture *startBtn = nullptr;
	SDL_Texture *resumeBtn = nullptr;
	SDL_Texture *quitBtn = nullptr;
	SDL_Texture *playerN = nullptr;
	SDL_Texture *playerE = nullptr;
	SDL_Texture *playerS = nullptr;
	SDL_Texture *playerW = nullptr;
	SDL_Texture *congrats = nullptr;
	SDL_Texture *Nega = nullptr;

	SDL_Rect gameScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect pauseScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect pauseMenu = {SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 150, 500, 300};
	SDL_Rect playerPosition = {0, 0, TILE_SIZE - 8, TILE_SIZE - 8};
	SDL_Rect background_Rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect rectangle = {0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect newPosition;
	// SDL_Rect startBtn_Rect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 30, 100, 50};
	// SDL_Rect quitBtn_Rect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 30, 100, 50};

	SDL_Rect startBtn_Rect = {SCREEN_WIDTH - 215, SCREEN_HEIGHT / 2 + 100, 150, 50};
	SDL_Rect resumeBtn_Rect = {pauseMenu.x + pauseMenu.w / 2 - 63, pauseMenu.y + pauseMenu.h / 2 - 80, 125, 50};
	SDL_Rect quitBtn_Rect = {SCREEN_WIDTH - 190, SCREEN_HEIGHT / 2 + 175, 100, 50};
	SDL_Rect congrats_Rect = {pauseMenu.x + pauseMenu.w / 2 - 150, pauseMenu.y + 40, 300, 80};
	SDL_Rect Nega_Rect = {35, SCREEN_HEIGHT - 110, 250, 75};

	SDL_Event event;

	SDL_Color plColor = {255, 255, 255, 255};
	SDL_Color pauseClr = {255, 0, 255, 100};
	SDL_Color wallColor = {75, 75, 75, 255};
	SDL_Color bgColor = {25, 0, 25, 0};
	SDL_Color fontColor = {170, 175, 175, 255};

	enum
	{
		NORTH,
		EAST,
		SOUTH,
		WEST
	};
	int32_t playerOrientation = SOUTH;

public:
	void prepareForRendering();
	void initialize();
	void shutdown();
	void playerMovement();
	void createWindow();
	void loadGameMap();
	void printGameMap();
	void setupGameMapSurface();
	SDL_Surface *createGameMapSurface();
	void run();
	uint32_t mapCoordinateToTileId(SDL_Rect position);
	bool isExit(uint32_t tileId);
	void newGame();
};
