#include "Game.hpp"

uint32_t Game::mapCoordinateToTileId(SDL_Rect position)
{
	uint32_t index = position.y / TILE_SIZE * MAZE_WIDTH + position.x / TILE_SIZE;

	return this->gameMapTiles[index];
}

bool isWalkableTile(uint32_t tileId)
{
	return tileId != WALL;
}
bool Game::isExit(uint32_t tileId)
{
	return tileId == EXIT;
}

void Game::playerMovement()
{
	newPosition = playerPosition;
	uint32_t nextTileId;

	// switch (event.key.keysym.sym)
	// {
	// case SDLK_ESCAPE:
	//   pause = !pause;
	//   break;
	// case SDLK_RIGHT:
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		playerOrientation = EAST;

		if (playerPosition.x + TILE_SIZE < SCREEN_WIDTH)
		{
			newPosition.x += TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
			{
				playerPosition.x += TILE_SIZE;
				StepSound->PlaySound();
			}
		}
	}
	// break;
	// case SDLK_LEFT:
	else if (event.key.keysym.sym == SDLK_LEFT)
	{
		playerOrientation = WEST;
		if (playerPosition.x > 0)
		{
			newPosition.x -= TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
			{
				playerPosition.x -= TILE_SIZE;
				StepSound->PlaySound();
			}
		}
	}
	// break;
	// case SDLK_UP:
	else if (event.key.keysym.sym == SDLK_UP)
	{
		playerOrientation = NORTH;
		if (playerPosition.y > 0)
		{
			newPosition.y -= TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
			{

				playerPosition.y -= TILE_SIZE;
				StepSound->PlaySound();
			}
		}
	}
	// break;
	// case SDLK_DOWN:
	else if (event.key.keysym.sym == SDLK_DOWN)
	{
		playerOrientation = SOUTH;
		if (playerPosition.y + TILE_SIZE < SCREEN_HEIGHT)
		{
			newPosition.y += TILE_SIZE;
			nextTileId = mapCoordinateToTileId(newPosition);
			if (isWalkableTile(nextTileId))
			{
				playerPosition.y += TILE_SIZE;
				StepSound->PlaySound();
			}
		}
	}
	// break;
	// default:
	// std::cerr << event.key.keysym.sym << "\n";
	// break;
	// }
}