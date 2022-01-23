#pragma once

#include "MazeGen.hpp"
#include "TileType.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>

class Game
{
	const char *FILE = "level";
	static size_t const MAZE_WIDTH = 53;
	static size_t const MAZE_HEIGHT = 31;
	static int32_t const TILE_SIZE = 24;
	uint32_t SCREEN_WIDTH = MAZE_WIDTH * TILE_SIZE;
	uint32_t SCREEN_HEIGHT = MAZE_HEIGHT * TILE_SIZE;
	static size_t const TILE_COUNT = MAZE_WIDTH * MAZE_HEIGHT;
	// int gameMapTiles[TILE_COUNT] = {};
	std::vector<uint32_t> gameMapTiles = {};
	std::vector<uint32_t> nxtLvlMap = {};
	// std::vector<std::vector<uint32_t>> gameMapTiles = {};




	std::stack<std::vector<uint32_t>> maps; // napravit stack mapa




	MazeGenerator maze;

	bool menu = true;
	bool game = false;
	bool pause = false;
	bool quit = false;

	SDL_Window *window = nullptr;

	SDL_Renderer *renderer = nullptr;

	SDL_Rect gameScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect pauseScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect playerPosition = {0, 0, TILE_SIZE - 8, TILE_SIZE - 8};
	SDL_Rect background_Rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect startBtn_Rect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 30, 100, 50};
	SDL_Rect quitBtn_Rect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 30, 100, 50};

	SDL_Event event;

	SDL_Texture *pauseTex = nullptr;
	SDL_Texture *playerTex = nullptr;
	SDL_Texture *gameMapTex = nullptr;
	SDL_Texture *background = nullptr;
	SDL_Texture *startBtn = nullptr;
	SDL_Texture *quitBtn = nullptr;

	SDL_Color plColor = {255, 255, 255, 255};
	SDL_Color pauseClr = {255, 0, 255, 100};
	SDL_Color wallColor = {75, 75, 75, 255};
	SDL_Color bgColor = {0, 0, 0, 255};

public:
	void prepareForRendering();
	void initialize();
	void shutdown();
	void keyboardInput();
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
