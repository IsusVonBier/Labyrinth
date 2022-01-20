#include "Game.hpp"

void fillTexture(SDL_Renderer *renderer, SDL_Texture *texture, int r, int g,
                 int b, int a) {
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderFillRect(renderer, NULL);
}
void prepareForRendering(SDL_Renderer *renderer) {
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 50);
}

void Game::initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL Initialization Error: " << SDL_GetError() << "\n";
    exit(1);
  }
}

void Game::createWindow() {
  this->window =
      SDL_CreateWindow("Labyrinth", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (this->window == NULL) {
    std::cerr << "Window creation Error: " << SDL_GetError() << "\n";
    exit(2);
  }
  this->renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  SDL_RenderClear(renderer);
}

void Game::loadGameMap() {
  std::ifstream gameMapFile(this->FILE);
  if (gameMapFile.is_open()) {

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
        tileColor = SDL_MapRGBA(surface->format, 0, 0, 0,0);
      }
      if (currentTileId == 1) {
        tileColor = SDL_MapRGB(surface->format, 255, 0, 255);
      }
      if (currentTileId == 2) {
        playerPosition.x = column * TILE_SIZE;
        playerPosition.y = row * TILE_SIZE;
        tileColor = SDL_MapRGB(surface->format, 0, 255, 255);
      }
      if (currentTileId == 3) {
        // playerPosition.x = column * TILE_SIZE;
        // playerPosition.y = column * TILE_SIZE;
        tileColor = SDL_MapRGB(surface->format, 255, 0, 0);
      }
      SDL_FillRect(surface, &rectangle, tileColor);
      column++;
    }
    column = 0;
    row++;
  }

  return surface;
}

void Game::run() {

  this->pauseTex =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_SetTextureBlendMode(pauseTex, SDL_BLENDMODE_BLEND);

  this->playerTex =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, TILE_SIZE, TILE_SIZE);

  fillTexture(renderer, playerTex, 255, 255, 255, 255);

  this->gameMapTex =
      SDL_CreateTextureFromSurface(renderer, this->gameMapSurface);

  SDL_FreeSurface(this->gameMapSurface);
  prepareForRendering(renderer);

  while (!quit) {
    if (isExit(mapCoordinateToTileId(playerPosition))) {
      quit = true;
    }
    SDL_RenderCopy(renderer, gameMapTex, NULL, &gameScreen);
    SDL_RenderCopy(renderer, playerTex, NULL, &playerPosition);
    SDL_RenderCopy(renderer, pauseTex, NULL, &pauseScreen);
    SDL_RenderPresent(renderer);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          pause = !pause;
          if (pause)
            fillTexture(renderer, pauseTex, 255, 0, 255, 100);
          else
            fillTexture(renderer, pauseTex, 255, 0, 255, 0);
          prepareForRendering(renderer);
          break;
        default:
          break;
        }
        if (!pause)
          keyboardInput();
      }
    }
  }
}

void Game::shutdown() {
  SDL_DestroyTexture(this->gameMapTex);
  this->gameMapTex = NULL;
  SDL_DestroyTexture(this->playerTex);
  this->playerTex = NULL;
  SDL_DestroyTexture(this->pauseTex);
  this->pauseTex = NULL;
  SDL_DestroyRenderer(this->renderer);
  this->renderer = NULL;
  SDL_DestroyWindow(this->window);
  this->window = NULL;
  SDL_Quit();
}