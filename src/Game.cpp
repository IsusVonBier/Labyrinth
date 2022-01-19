#include "Game.hpp"

Game::Game() {
  this->entrancePosition = {0, 0, TILE_SIZE, TILE_SIZE};
  this->exitPosition = {0, 0, TILE_SIZE, TILE_SIZE};
}

void Game::initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    // std::cerr << "SDL Initialization Error: " << SDL_GetError() << "\n";
    std::string error = "SDL Initialization Error: \n";
    error += SDL_GetError();
    const char *err = &error[0];
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", err, NULL);
    exit(1);
  }
}

void Game::createWindow() {
  this->window =
      SDL_CreateWindow("Labyrinth", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (this->window == NULL) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Window creation Error", NULL);
    exit(2);
  }

  this->windowSurface = SDL_GetWindowSurface(this->window);
}

void Game::loadGameMap() {
  std::ifstream gameMapFile(this->FILE);
  if (gameMapFile.is_open()) {
    gameMapFile >> entrancePosition.x >> entrancePosition.y;
    gameMapFile >> exitPosition.x >> exitPosition.y;

    entrancePosition.x *= TILE_SIZE;
    entrancePosition.y *= TILE_SIZE;
    exitPosition.x *= TILE_SIZE;
    exitPosition.y *= TILE_SIZE;

    int tileId, index = 0;
    while (gameMapFile >> tileId) {
      this->gameMapTiles[index++] = tileId;
    }
    gameMapFile.close();
  } else {
    std::cerr << "Error opening file";
  }
}

void Game::printGameMap() {
  std::cout << "Entrance: (" << entrancePosition.x << "," << entrancePosition.y
            << ")\n";
  std::cout << "Exit: (" << exitPosition.x << "," << exitPosition.y << ")\n";

  for (int i = 0; i < 300; i++) {
    if (i != 0 && i % 20 == 0)
      std::cout << "\n";
    std::cout << this->gameMapTiles[i] << " ";
  }
  std::cout << "\n";
}

void Game::setupGameMapSurface() {
  this->gameMapSurface = createGameMapSurface();
  if (gameMapSurface == NULL) {
    std::cerr << "Failed to create game map surface" << SDL_GetError() << "\n";
    exit(3);
  }
}

SDL_Surface *Game::createGameMapSurface() {

  SDL_Surface *surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

  int row = 0;
  int column = 0;

  SDL_Rect rectangle = {0, 0, 32, 32};

  while (row < 15) {
    while (column < 20) {
      rectangle.x = column * 32;
      rectangle.y = row * 32;
      int currentTileId = this->gameMapTiles[row * 20 + column];
      uint32_t tileColor;
      if (currentTileId == 0) {
        tileColor = SDL_MapRGB(surface->format, 0, 0, 0);
      } else if (currentTileId == 1) {
        tileColor = SDL_MapRGB(surface->format, 255, 55, 255);
      }
      SDL_FillRect(surface, &rectangle, tileColor);
      column++;
    }
    column = 0;
    row++;
  }

  return surface;
}

void Game::paintEntrance() {
  uint32_t color = SDL_MapRGB(windowSurface->format, 0, 255, 255);
  SDL_FillRect(windowSurface, &entrancePosition, color);
}

void Game::paintExit() {
  uint32_t color = SDL_MapRGB(windowSurface->format, 255, 0, 0);
  SDL_FillRect(windowSurface, &exitPosition, color);
}

void Game::run() {
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        keyboardInput();
      }
    }
    // SDL_FillRect(windowSurface, NULL,
    //  SDL_MapRGB(windowSurface->format, 0, 0, 0));

    if (SDL_BlitSurface(gameMapSurface, NULL, windowSurface, NULL) != 0) {
      std::cerr << "There was a problem blitting the game map surface onto the "
                   "window surface: "
                << SDL_GetError << "\n";
      exit(4);
    }
    paintEntrance();
    paintExit();

    SDL_FillRect(windowSurface, &playerPosition, playerColor);
    SDL_UpdateWindowSurface(this->window);
  }
}

void Game::shutdown() {
  SDL_FreeSurface(this->gameMapSurface);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}