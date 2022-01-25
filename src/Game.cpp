#include "Game.hpp"

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
	SDL_SetRenderDrawColor(renderer, 35, 0, 35, 255);
}

void Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL Initialization Error: " << SDL_GetError() << "\n";
		exit(1);
	}
	loadGameMap();

	if (TTF_Init() == -1)
	{
		std::cerr << "Could not initialize SDL2_ttf: " << TTF_GetError() << "\n";
	}
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

	gameFont = TTF_OpenFont("assets/SEGA.ttf", 24);
	fontSurface = TTF_RenderText_Solid(gameFont, "NEGA", {0, 25, 255});
	Nega = SDL_CreateTextureFromSurface(renderer, fontSurface);
	gameFont = TTF_OpenFont("assets/LitterLover2-Bold.ttf", 18);
	fontSurface = TTF_RenderText_Solid(gameFont, "New game", fontColor);
	startBtn = SDL_CreateTextureFromSurface(renderer, fontSurface);
	fontSurface = TTF_RenderText_Solid(gameFont, "Resume", fontColor);
	resumeBtn = SDL_CreateTextureFromSurface(renderer, fontSurface);
	fontSurface = TTF_RenderText_Solid(gameFont, "Quit", fontColor);
	quitBtn = SDL_CreateTextureFromSurface(renderer, fontSurface);
	fontSurface = TTF_RenderText_Solid(gameFont, "Maze complete", {255, 255, 255});
	congrats = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);

	MainMusicTrack = new Music("assets/Kobold - The Cave of the Lost Talisman.mp3");
	MainMusicTrack->PlayMusic(-1);
	MainMusicTrack->SetVolume(40);

	SelectSound = new Sound("assets/select.wav");
	StepSound = new Sound("assets/step.wav");
	StepSound->SetVolume(50);
	finishSound = new Sound("assets/finish.wav");
	startSound = new Sound("assets/start.wav");

	this->background = IMG_LoadTexture(renderer, "assets/background.png");
	this->menuTex = IMG_LoadTexture(renderer, "assets/menu.png");
	this->playerN = IMG_LoadTexture(renderer, "assets/playerN.png");
	this->playerE = IMG_LoadTexture(renderer, "assets/playerE.png");
	this->playerS = IMG_LoadTexture(renderer, "assets/playerS.png");
	this->playerW = IMG_LoadTexture(renderer, "assets/playerW.png");
	// this->startBtn = IMG_LoadTexture(renderer, "assets/startBtn.png");
	// this->quitBtn = IMG_LoadTexture(renderer, "assets/quitBtn.png");
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
	gameMapSur = createGameMapSurface();
	this->gameMapTex = SDL_CreateTextureFromSurface(renderer, gameMapSur);
	SDL_FreeSurface(gameMapSur);
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

	wallTile = IMG_Load("assets/wall.png");
	exitTile = IMG_Load("assets/exit.png");
	uint32_t currentTileId;
	uint32_t tileColor;

	while (row < MAZE_HEIGHT)
	{
		while (column < MAZE_WIDTH)
		{
			rectangle.x = column * TILE_SIZE;
			rectangle.y = row * TILE_SIZE;
			currentTileId = this->gameMapTiles[row * MAZE_WIDTH + column];

			if (currentTileId == 0)
			{
				// SDL_BlitSurface(floor, NULL, surface, &rectangle);
				tileColor = SDL_MapRGB(surface->format, bgColor.r, bgColor.g, bgColor.b);
			}
			if (currentTileId == 1)
			{
				SDL_BlitSurface(wallTile, NULL, surface, &rectangle);
				// tileColor = SDL_MapRGB(surface->format, wallColor.r, wallColor.g, wallColor.b);
			}
			if (currentTileId == 2)
			{
				playerPosition.x = column * TILE_SIZE + 4;
				playerPosition.y = row * TILE_SIZE + 4;
				tileColor = SDL_MapRGB(surface->format, bgColor.r, bgColor.g, bgColor.b);
			}
			if (currentTileId == 3)
			{
				SDL_BlitSurface(exitTile, NULL, surface, &rectangle);
				// tileColor = SDL_MapRGB(surface->format, 255, 0, 255);
			}
			if (/*currentTileId != 0 && */ currentTileId != 1 && currentTileId != 3)
				SDL_FillRect(surface, &rectangle, tileColor);
			column++;
		}
		column = 0;
		row++;
	}
	// SDL_FreeSurface(floor);
	SDL_FreeSurface(exitTile);
	SDL_FreeSurface(wallTile);
	exitTile = nullptr;
	wallTile = nullptr;

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
	bool ngPlayed = false;
	bool rsPlayed = false;
	bool qtPlayed = false;
	bool labyrWon = false;

	while (!quit)
	{
		SDL_GetMouseState(&mouseX, &mouseY);

		if (isExit(mapCoordinateToTileId(playerPosition)) && !labyrWon)
		{
				finishSound->PlaySound();
				labyrWon = true;
		}
		if (game)
		{
			SDL_RenderCopy(renderer, gameMapTex, NULL, &gameScreen);
			switch (playerOrientation)
			{
			case NORTH:
				SDL_RenderCopy(renderer, playerN, NULL, &playerPosition);
				break;
			case EAST:
				SDL_RenderCopy(renderer, playerE, NULL, &playerPosition);
				break;
			case SOUTH:
				SDL_RenderCopy(renderer, playerS, NULL, &playerPosition);
				break;
			case WEST:
				SDL_RenderCopy(renderer, playerW, NULL, &playerPosition);
				break;
			}
		}
		if (menu)
		{
			SDL_RenderCopy(renderer, background, NULL, &background_Rect);
			SDL_RenderCopy(renderer, Nega, NULL, &Nega_Rect);
		}
		if (pause)
		{
			startBtn_Rect = {pauseMenu.x + pauseMenu.w / 2 - 75, pauseMenu.y + pauseMenu.h / 2 - 25, 150, 50};
			quitBtn_Rect = {pauseMenu.x + pauseMenu.w / 2 - 50, pauseMenu.y + pauseMenu.h / 2 + 30, 100, 50};
			SDL_RenderCopy(renderer, pauseTex, NULL, &pauseScreen);
			SDL_RenderCopy(renderer, menuTex, NULL, &pauseMenu);
			SDL_RenderCopy(renderer, resumeBtn, NULL, &resumeBtn_Rect);
		}
		if (labyrWon)
		{
			startBtn_Rect = {pauseMenu.x + pauseMenu.w / 2 - 75, pauseMenu.y + pauseMenu.h / 2 - 10, 150, 50};
			quitBtn_Rect = {pauseMenu.x + pauseMenu.w / 2 - 50, pauseMenu.y + pauseMenu.h / 2 + 35, 100, 50};
			SDL_RenderCopy(renderer, pauseTex, NULL, &pauseScreen);
			SDL_RenderCopy(renderer, menuTex, NULL, &pauseMenu);
			SDL_RenderCopy(renderer, congrats, NULL, &congrats_Rect);
		}
		if (menu || pause || labyrWon)
		{
			SDL_RenderCopy(renderer, startBtn, NULL, &startBtn_Rect);
			SDL_RenderCopy(renderer, quitBtn, NULL, &quitBtn_Rect);
		}
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event))
		{

			if (mouseX >= startBtn_Rect.x && mouseX <= startBtn_Rect.x + startBtn_Rect.w && mouseY >= startBtn_Rect.y && mouseY <= startBtn_Rect.y + startBtn_Rect.h && menu | pause | labyrWon)
			{
				SDL_SetTextureColorMod(startBtn, 0, 255, 255);
				if (!ngPlayed)
				{
					SelectSound->PlaySound();
					ngPlayed = true;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
					{
						if (pause || labyrWon)
							newGame();
						menu = false;
						game = true;
						pause = false;
						labyrWon = false;
						startSound->PlaySound();

				}
			}
			else
			{
				SDL_SetTextureColorMod(startBtn, 250, 250, 250);
				ngPlayed = false;
			}
			if (mouseX >= resumeBtn_Rect.x && mouseX <= resumeBtn_Rect.x + resumeBtn_Rect.w && mouseY >= resumeBtn_Rect.y && mouseY <= resumeBtn_Rect.y + resumeBtn_Rect.h && pause)
			{
				SDL_SetTextureColorMod(resumeBtn, 0, 255, 0);
				if (!rsPlayed)
				{
					SelectSound->PlaySound();
					rsPlayed = true;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						pause = !pause;
					}
				}
			}
			else
			{
				SDL_SetTextureColorMod(resumeBtn, 250, 250, 250);
				rsPlayed = false;
			}
			if (mouseX >= quitBtn_Rect.x && mouseX <= quitBtn_Rect.x + quitBtn_Rect.w && mouseY >= quitBtn_Rect.y && mouseY <= quitBtn_Rect.y + quitBtn_Rect.h && menu | pause | labyrWon)
			{
				SDL_SetTextureColorMod(quitBtn, 250, 0, 0);
				if (!qtPlayed)
				{
					SelectSound->PlaySound();
					qtPlayed = true;
				}

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
				qtPlayed = false;
			}

			if (event.type == SDL_QUIT)
				quit = true;

			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					pause = !pause;
				if (game && !pause)
					playerMovement();
			}

			// switch (event.type)
			// {
			// // case SDL_QUIT:
			// // 	quit = true;
			// // 	break;
			// case SDL_KEYDOWN:
			// 	switch (event.key.keysym.sym)
			// 	{
			// 	case SDLK_ESCAPE:
			// 		pause = !pause;
			// 		if (pause)
			// 		{
			// 			fillTexture(renderer, pauseTex, pauseClr);
			// 			prepareForRendering();
			// 		}
			// 		break;
			// 	default:
			// 		break;
			// 	}
			// 	if (!pause)
			// 		keyboardInput();
			// }
		}
	}
}

void Game::shutdown()
{
	TTF_CloseFont(gameFont);

	SDL_DestroyTexture(this->pauseTex);
	SDL_DestroyTexture(this->menuTex);
	SDL_DestroyTexture(this->gameMapTex);
	SDL_DestroyTexture(this->playerTex);
	SDL_DestroyTexture(this->gameMapTex);
	SDL_DestroyTexture(this->background);
	SDL_DestroyTexture(this->startBtn);
	SDL_DestroyTexture(this->resumeBtn);
	SDL_DestroyTexture(this->quitBtn);
	SDL_DestroyTexture(this->playerN);
	SDL_DestroyTexture(this->playerE);
	SDL_DestroyTexture(this->playerS);
	SDL_DestroyTexture(this->playerW);
	SDL_DestroyTexture(this->congrats);

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	this->pauseTex = nullptr;
	this->menuTex = nullptr;
	this->playerTex = nullptr;
	this->gameMapTex = nullptr;
	this->background = nullptr;
	this->startBtn = nullptr;
	this->resumeBtn = nullptr;
	this->quitBtn = nullptr;
	this->playerN = nullptr;
	this->playerE = nullptr;
	this->playerS = nullptr;
	this->playerW = nullptr;
	this->congrats = nullptr;

	this->renderer = nullptr;
	this->window = nullptr;

	SDL_Quit();
}