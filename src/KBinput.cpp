#include "Game.hpp"

uint32_t Game::mapCoordinateToTileId(SDL_Rect position)
{
	uint32_t tileSize = TILE_SIZE;
	uint32_t tilesAcross = MAZE_WIDTH;
	uint32_t index = position.y / tileSize * tilesAcross + position.x / tileSize;

	return this->gameMapTiles[index];
}

bool isWalkableTile(uint32_t tileId)
{
	if (tileId != WALL)
		return true;
	return false;
}
bool Game::isExit(uint32_t tileId)
{
	if (tileId == EXIT)
		return true;
	return false;
}

void Game::keyboardInput()
{
	SDL_Rect newPosition = playerPosition;
	uint32_t nextTileId;

	switch (event.key.keysym.sym)
	{
	// case SDLK_ESCAPE:
	//   pause = !pause;
	//   break;
	case SDLK_RIGHT:
		if (playerPosition.x + TILE_SIZE < SCREEN_WIDTH)
		{
			newPosition.x += TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
				playerPosition.x += TILE_SIZE;
		}
		break;
	case SDLK_LEFT:
		if (playerPosition.x > 0)
		{
			newPosition.x -= TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
				playerPosition.x -= TILE_SIZE;
		}
		break;
	case SDLK_UP:
		if (playerPosition.y > 0)
		{
			newPosition.y -= TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
				playerPosition.y -= TILE_SIZE;
		}
		break;
	case SDLK_DOWN:
		if (playerPosition.y + TILE_SIZE < SCREEN_HEIGHT)
		{
			newPosition.y += TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
				playerPosition.y += TILE_SIZE;
		}
		break;
	default:
		// std::cerr << event.key.keysym.sym << "\n";
		break;
	}
}