#include "Game.hpp"
// #include <SDL2/SDL.h>
// #include <fstream>
// #include <iostream>
// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define TILE_SIZE 32
// #define FILE "level1"

// enum TileType {
//   Floor, // 0
//   Wall,  // 1
// };

// SDL_Surface *createGameMapSurface(int *tiles) {
//   SDL_Surface *surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

//   int row = 0;
//   int column = 0;

//   SDL_Rect rectangle = {0, 0, 32, 32};

//   while (row < 15) {
//     while (column < 20) {
//       rectangle.x = column * 32;
//       rectangle.y = row * 32;
//       int currentTileId = tiles[row * 20 + column];
//       uint32_t tileColor;
//       if (currentTileId == 0) {
//         tileColor = SDL_MapRGB(surface->format, 0, 0, 0);
//       } else if (currentTileId == 1) {
//         tileColor = SDL_MapRGB(surface->format, 255, 55, 255);
//       }
//       SDL_FillRect(surface, &rectangle, tileColor);
//       column++;
//     }
//     column = 0;
//     row++;
//   }

//   return surface;
// }

// void printGameMap(int *tiles, SDL_Rect &entrancePosition,
//                   SDL_Rect &exitPosition) {
//   std::cout << "Entrance: (" << entrancePosition.x << "," <<
//   entrancePosition.y
//             << ")\n";
//   std::cout << "Exit: (" << exitPosition.x << "," << exitPosition.y << ")\n";

//   for (int i = 0; i < 300; i++) {
//     if (i != 0 && i % 20 == 0)
//       std::cout << "\n";
//     std::cout << tiles[i] << " ";
//   }
//   std::cout << "\n";
// }

// void loadGameMap(int *tiles, SDL_Rect &entrancePosition,
//                  SDL_Rect &exitPosition) {
//   std::ifstream gameMapFile(FILE);
//   if (gameMapFile.is_open()) {
//     gameMapFile >> entrancePosition.x >> entrancePosition.y;
//     gameMapFile >> exitPosition.x >> exitPosition.y;

//     entrancePosition.x *= TILE_SIZE;
//     entrancePosition.y *= TILE_SIZE;
//     exitPosition.x *= TILE_SIZE;
//     exitPosition.y *= TILE_SIZE;

//     int tileId;
//     int index = 0;
//     while (gameMapFile >> tileId) {
//       tiles[index++] = tileId;
//     }
//     gameMapFile.close();
//   } else {
//     std::cerr << "Error opening file";
//   }
// }

// int mapCoordinateToTileId(SDL_Rect position, int *tiles) {
//   int tileSize = 32;
//   int tilesAcross = 20;
//   int index = position.y / tileSize * tilesAcross + position.x / tileSize;

//   return tiles[index];
// }

// bool isWalkableTile(int tileId) {
//   if (tileId == Floor)
//     return true;
//   return false;
// }

// void handlePlayerInput(SDL_Event event, SDL_Rect &playerPosition,
//                        int *gameMapTiles, bool &quit) {
//   SDL_Rect newPosition = playerPosition;
//   int nextTileId;

//   switch (event.key.keysym.sym) {
//   case SDLK_ESCAPE:
//     quit = true;
//     break;
//   case SDLK_RIGHT:
//     if (playerPosition.x + 32 < SCREEN_WIDTH) {
//       newPosition.x += 32;
//       nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
//       if (isWalkableTile(nextTileId))
//         playerPosition.x += 32;
//     }
//     break;
//   case SDLK_LEFT:
//     if (playerPosition.x > 0) {
//       newPosition.x -= 32;
//       nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
//       if (isWalkableTile(nextTileId))
//         playerPosition.x -= 32;
//     }
//     break;
//   case SDLK_UP:
//     if (playerPosition.y > 0) {
//       newPosition.y -= 32;
//       nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
//       if (isWalkableTile(nextTileId))
//         playerPosition.y -= 32;
//     }
//     break;
//   case SDLK_DOWN:
//     if (playerPosition.y + 32 < SCREEN_HEIGHT) {
//       newPosition.y += 32;
//       nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
//       if (isWalkableTile(nextTileId))
//         playerPosition.y += 32;
//     }
//     break;
//   default:
//     // std::cerr << event.key.keysym.sym << "\n";
//     break;
//   }
// }

// void paintEntrance(SDL_Surface *surface, SDL_Rect entrancePosition) {
//   uint32_t color = SDL_MapRGB(surface->format, 0, 255, 255);
//   SDL_FillRect(surface, &entrancePosition, color);
// }

// void paintExit(SDL_Surface *surface, SDL_Rect exitPosition) {
//   uint32_t color = SDL_MapRGB(surface->format, 255, 0, 0);
//   SDL_FillRect(surface, &exitPosition, color);
// }

int main(int argc, char *argv[]) {
  Game game;
  game.initialize();
  // if (SDL_Init(SDL_INIT_VIDEO) < 0) {
  //   std::cerr << "SDL Initialization Error: " << SDL_GetError() << "\n";
  //   return 1;
  // }

  game.createWindow();
  // SDL_Window *window =
  //     SDL_CreateWindow("Labyrinth", SDL_WINDOWPOS_CENTERED,
  //                      SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
  //                      0);
  // if (window == NULL) {
  //   std::cerr << "Window creation Error: " << SDL_GetError() << "\n";
  //   return 2;
  // }

  // SDL_Surface *windowSurface = SDL_GetWindowSurface(game.getWindow());

  game.loadGameMap();
  game.printGameMap();
  game.setupGameMapSurface();
  game.setPlayer();
  game.run();

  // SDL_Surface *gameMapSurface = createGameMapSurface(gameMapTiles);
  // if (gameMapSurface == NULL) {
  //   std::cerr << "Failed to create game map surface" << SDL_GetError() <<
  //   "\n"; return 3;
  // }

  // SDL_Event event;
  // SDL_Rect playerPosition = {entrancePosition.x, entrancePosition.y, 32, 32};
  // uint32_t playerColor = SDL_MapRGB(windowSurface->format, 128, 128, 128);

  // bool quit = false;

  // SDL_Delay(5000);
  // while (!quit) {
  //   while (SDL_PollEvent(&event)) {
  //     switch (event.type) {
  //     case SDL_QUIT:
  //       quit = true;
  //       break;
  //     case SDL_KEYDOWN:
  //       handlePlayerInput(event, playerPosition, gameMapTiles, quit);
  //     }
  //   }
  //   // SDL_FillRect(windowSurface, NULL,
  //   //  SDL_MapRGB(windowSurface->format, 0, 0, 0));

  //   if (SDL_BlitSurface(gameMapSurface, NULL, windowSurface, NULL) != 0) {
  //     std::cerr << "There was a problem blitting the game map surface onto
  //     the "
  //                  "window surface: "
  //               << SDL_GetError << "\n";
  //     return 4;
  //   }
  //   game.paintEntrance();
  //   game.paintExit();

  //   SDL_FillRect(windowSurface, &playerPosition, playerColor);
  //   SDL_UpdateWindowSurface(game.getWindow());
  // }

  game.shutdown();
  // SDL_Quit();

  return 0;
}