#pragma once

#include "FileType.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>

class Game {
  const char *FILE = "level1";
  // uint32_t SCREEN_WIDTH = 640;  // 20 tiles
  // uint32_t SCREEN_HEIGHT = 480; // 15 tiles
  static size_t const MAZE_WIDTH = 41;
  static size_t const MAZE_HEIGHT =31;
  static int32_t const TILE_SIZE = 32;
  uint32_t SCREEN_WIDTH = MAZE_WIDTH*TILE_SIZE; // 50 tiles
  uint32_t SCREEN_HEIGHT = MAZE_HEIGHT*TILE_SIZE; // 25 tiles
  static size_t const TILE_COUNT = MAZE_WIDTH*MAZE_HEIGHT;
  uint32_t playerColor = 0;
  int gameMapTiles[TILE_COUNT] = {};

  bool quit = false;
  bool pause = false;


  SDL_Window *window = nullptr;

  SDL_Surface *gameMapSurface = nullptr;

  SDL_Renderer *renderer = nullptr;

  // SDL_Rect entrancePosition = {0, 0, TILE_SIZE, TILE_SIZE};
  // SDL_Rect exitPosition = {0, 0, TILE_SIZE, TILE_SIZE};
  SDL_Rect gameScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect pauseScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect playerPosition = {0, 0, TILE_SIZE, TILE_SIZE};

  SDL_Event event;

  SDL_Texture *pauseTex = nullptr;
  SDL_Texture *playerTex = nullptr;
  SDL_Texture *gameMapTex = nullptr;

public:
  void initialize();
  void shutdown();
  void keyboardInput();
  void createWindow();
  void loadGameMap();
  void printGameMap();
  void setupGameMapSurface();
  SDL_Surface *createGameMapSurface();
  void run();
  int mapCoordinateToTileId(SDL_Rect position);
  bool isExit(int tileId);
};
