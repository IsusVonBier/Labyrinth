#pragma once

#include "FileType.hpp"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>

class Game {
  uint32_t SCREEN_WIDTH = 640;  // 20 tiles
  uint32_t SCREEN_HEIGHT = 480; // 15 tiles
  int32_t TILE_SIZE = 32;
  const char *FILE = "level1";
  SDL_Window *window = nullptr;
  SDL_Surface *windowSurface = nullptr;
  int gameMapTiles[300] = {};
  SDL_Rect entrancePosition = {0, 0, 0, 0};
  SDL_Rect exitPosition = {0, 0, 0, 0};
  SDL_Surface *gameMapSurface = nullptr;
  SDL_Event event;
  SDL_Rect playerPosition = {0, 0, 0, 0};
  uint32_t playerColor = 0;
  bool quit = false;

public:
  Game();
  void initialize();
  void shutdown();
  void keyboardInput();
  void createWindow();
  SDL_Window *&getWindow() { return this->window; }
  void loadGameMap();
  void printGameMap();
  void setupGameMapSurface();
  SDL_Surface *createGameMapSurface();
  void paintEntrance();
  void paintExit();
  void run();
  void setPlayer() {
    playerPosition = {entrancePosition.x, entrancePosition.y, 32, 32};
    playerColor = SDL_MapRGB(windowSurface->format, 128, 128, 128);
  }
};
