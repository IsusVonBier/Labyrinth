#include "Game.hpp"

int Game::mapCoordinateToTileId(SDL_Rect position) {
  int tileSize = 32;
  int tilesAcross = 20;
  int index = position.y / tileSize * tilesAcross + position.x / tileSize;

  return this->gameMapTiles[index];
}

bool isWalkableTile(int tileId) {
  if (tileId != Wall)
    return true;
  return false;
}
bool Game::isExit(int tileId) {
  if (tileId == Exit)
    return true;
  return false;
}

void Game::keyboardInput() {
  SDL_Rect newPosition = playerPosition;
  int nextTileId;

  switch (event.key.keysym.sym) {
  // case SDLK_ESCAPE:
  //   pause = !pause;
  //   break;
  case SDLK_RIGHT:
    if (playerPosition.x + 32 < SCREEN_WIDTH) {
      newPosition.x += 32;
      nextTileId = mapCoordinateToTileId(newPosition);
      if (isWalkableTile(nextTileId))
        playerPosition.x += 32;
    }
    break;
  case SDLK_LEFT:
    if (playerPosition.x > 0) {
      newPosition.x -= 32;
      nextTileId = mapCoordinateToTileId(newPosition);
      if (isWalkableTile(nextTileId))
        playerPosition.x -= 32;
    }
    break;
  case SDLK_UP:
    if (playerPosition.y > 0) {
      newPosition.y -= 32;
      nextTileId = mapCoordinateToTileId(newPosition);
      if (isWalkableTile(nextTileId))
        playerPosition.y -= 32;
    }
    break;
  case SDLK_DOWN:
    if (playerPosition.y + 32 < SCREEN_HEIGHT) {
      newPosition.y += 32;
      nextTileId = mapCoordinateToTileId(newPosition);
      if (isWalkableTile(nextTileId))
        playerPosition.y += 32;
    }
    break;
  default:
    // std::cerr << event.key.keysym.sym << "\n";
    break;
  }
}