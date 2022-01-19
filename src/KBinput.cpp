#include "Game.hpp"

int mapCoordinateToTileId(SDL_Rect position, int *tiles) {
  int tileSize = 32;
  int tilesAcross = 20;
  int index = position.y / tileSize * tilesAcross + position.x / tileSize;

  return tiles[index];
}

bool isWalkableTile(int tileId) {
  if (tileId == Floor)
    return true;
  return false;
}

void Game::keyboardInput() {
  SDL_Rect newPosition = playerPosition;
  int nextTileId;

  switch (event.key.keysym.sym) {
  case SDLK_ESCAPE:
    quit = true;
    break;
  case SDLK_RIGHT:
    if (playerPosition.x + 32 < SCREEN_WIDTH) {
      newPosition.x += 32;
      nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
      if (isWalkableTile(nextTileId))
        playerPosition.x += 32;
    }
    break;
  case SDLK_LEFT:
    if (playerPosition.x > 0) {
      newPosition.x -= 32;
      nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
      if (isWalkableTile(nextTileId))
        playerPosition.x -= 32;
    }
    break;
  case SDLK_UP:
    if (playerPosition.y > 0) {
      newPosition.y -= 32;
      nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
      if (isWalkableTile(nextTileId))
        playerPosition.y -= 32;
    }
    break;
  case SDLK_DOWN:
    if (playerPosition.y + 32 < SCREEN_HEIGHT) {
      newPosition.y += 32;
      nextTileId = mapCoordinateToTileId(newPosition, gameMapTiles);
      if (isWalkableTile(nextTileId))
        playerPosition.y += 32;
    }
    break;
  default:
    // std::cerr << event.key.keysym.sym << "\n";
    break;
  }
}