#include "Game.hpp"
#define RED 255, 0, 0

void fillTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Color color)
{
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, NULL);
}
void Game::prepareForRendering()
{
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Game::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL Initialization Error: " << SDL_GetError() << "\n";
		exit(1);
	}
	loadGameMap();
}

void Game::createWindow()
{
	this->window = SDL_CreateWindow("Labyrinth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (this->window == NULL)
	{
		std::cerr << "Window creation Error: " << SDL_GetError() << "\n";
		exit(2);
	}
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	prepareForRendering();
	SDL_RenderClear(renderer);

	int flags = IMG_INIT_PNG;
	int initStatus = IMG_Init(flags);
	if ((initStatus & flags) != flags)
	{
		std::cerr << "SDL2_Image Error: " << SDL_GetError() << "\n";
		exit(7);
	};

	this->background = IMG_LoadTexture(renderer, "assets/background.png");
	this->startBtn = IMG_LoadTexture(renderer, "assets/startBtn.png");
	this->quitBtn = IMG_LoadTexture(renderer, "assets/quitBtn.png");
}

void Game::loadGameMap()
{
	maze.createMaze();
	this->nxtLvlMap = maze.getArray();
	// std::ifstream gameMapFile(this->FILE);
	// if (gameMapFile.is_open())
	// {

	// 	int tileId, index = 0;
	// 	while (gameMapFile >> tileId)
	// 	{
	// 		this->gameMapTiles[index++] = tileId;
	// 	}
	// 	gameMapFile.close();
	// }
	// else
	// {
	// 	std::cerr << "Error opening file";
	// }
}

void Game::newGame()
{
	this->gameMapTiles = this->nxtLvlMap;
	this->gameMapTex = SDL_CreateTextureFromSurface(renderer, createGameMapSurface());
	prepareForRendering();
	loadGameMap();
}

void Game::printGameMap()
{
	for (uint32_t i = 0; i < TILE_COUNT; i++)
	{
		if (i != 0 && i % MAZE_WIDTH == 0)
			std::cout << "\n";
		std::cout << this->gameMapTiles[i] << " ";
	}
	std::cout << "\n";
}

SDL_Surface *Game::createGameMapSurface()
{

	SDL_Surface *surface =
		SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

	int row = 0;
	int column = 0;

	SDL_Rect rectangle = {0, 0, TILE_SIZE, TILE_SIZE};

	while (row < MAZE_HEIGHT)
	{
		while (column < MAZE_WIDTH)
		{
			rectangle.x = column * TILE_SIZE;
			rectangle.y = row * TILE_SIZE;
			uint32_t currentTileId = this->gameMapTiles[row * MAZE_WIDTH + column];
			uint32_t tileColor;
			if (currentTileId == 0)
			{
				tileColor =
					SDL_MapRGB(surface->format, bgColor.r, bgColor.g, bgColor.b);
			}
			if (currentTileId == 1)
			{
				tileColor =
					SDL_MapRGB(surface->format, wallColor.r, wallColor.g, wallColor.b);
			}
			if (currentTileId == 2)
			{
				playerPosition.x = column * TILE_SIZE + 4;
				playerPosition.y = row * TILE_SIZE + 4;
				tileColor = SDL_MapRGB(surface->format, 0, 255, 255);
			}
			if (currentTileId == 3)
			{
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

void Game::run()
{

	int32_t mouseX = 0;
	int32_t mouseY = 0;

	this->pauseTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetTextureBlendMode(pauseTex, SDL_BLENDMODE_BLEND);
	fillTexture(renderer, pauseTex, pauseClr);
	this->playerTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TILE_SIZE, TILE_SIZE);
	fillTexture(renderer, playerTex, plColor);
	prepareForRendering();

	while (!quit)
	{
		SDL_GetMouseState(&mouseX, &mouseY);

		if (isExit(mapCoordinateToTileId(playerPosition)))
		{
			pause = true;
		}
		if (game)
		{
			SDL_RenderCopy(renderer, gameMapTex, NULL, &gameScreen);
			SDL_RenderCopy(renderer, playerTex, NULL, &playerPosition);
		}
		if (!game)
		{
			SDL_RenderCopy(renderer, background, NULL, &background_Rect);
			SDL_RenderCopy(renderer, startBtn, NULL, &startBtn_Rect);
			SDL_RenderCopy(renderer, quitBtn, NULL, &quitBtn_Rect);
		}
		if (pause)
		{
			SDL_RenderCopy(renderer, pauseTex, NULL, &pauseScreen);
			SDL_RenderCopy(renderer, startBtn, NULL, &startBtn_Rect);
			SDL_RenderCopy(renderer, quitBtn, NULL, &quitBtn_Rect);
		}
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event))
		{

			if (mouseX >= startBtn_Rect.x && mouseX <= startBtn_Rect.x + startBtn_Rect.w && mouseY >= startBtn_Rect.y && mouseY <= startBtn_Rect.y + startBtn_Rect.h)
			{
				SDL_SetTextureColorMod(startBtn, 0, 255, 255);
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						newGame();
						game = true;
						pause = false;
					}
				}
			}
			else
			{
				SDL_SetTextureColorMod(startBtn, 250, 250, 250);
			}
			if (mouseX >= quitBtn_Rect.x && mouseX <= quitBtn_Rect.x + quitBtn_Rect.w && mouseY >= quitBtn_Rect.y && mouseY <= quitBtn_Rect.y + quitBtn_Rect.h)
			{
				SDL_SetTextureColorMod(quitBtn, 250, 0, 0);

				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						quit = true;
					}
				}
			}
			else
			{
				SDL_SetTextureColorMod(quitBtn, 250, 250, 250);
			}

			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					pause = !pause;
					if (pause)
					{
						fillTexture(renderer, pauseTex, pauseClr);
						prepareForRendering();
					}
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

void Game::shutdown()
{
	SDL_DestroyTexture(this->pauseTex);
	this->gameMapTex = nullptr;
	SDL_DestroyTexture(this->playerTex);
	this->gameMapTex = nullptr;
	SDL_DestroyTexture(this->gameMapTex);
	this->playerTex = nullptr;
	SDL_DestroyTexture(this->background);
	this->pauseTex = nullptr;
	SDL_DestroyTexture(this->startBtn);
	this->pauseTex = nullptr;
	SDL_DestroyTexture(this->quitBtn);
	this->pauseTex = nullptr;

	SDL_DestroyRenderer(this->renderer);
	this->renderer = nullptr;
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
	SDL_Quit();
}