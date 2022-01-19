#include <SDL2/SDL.h>
#include <iostream>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Initialization Error: " << SDL_GetError() << "\n";
    return 1;
  }
  SDL_Window *window =
      SDL_CreateWindow("Labyrinth", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (window == NULL) {
    std::cerr << "Window creation Error: " << SDL_GetError() << "\n";
    return 2;
  }

  SDL_Surface *windowSurface = SDL_GetWindowSurface(window);
  // SDL_Surface *surface =
  //     SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

  SDL_FillRect(windowSurface, NULL,
               SDL_MapRGB(windowSurface->format, 255, 0, 255));

  SDL_Rect rectangle1;
  rectangle1.x = SCREEN_WIDTH / 4;
  rectangle1.y = SCREEN_HEIGHT / 4;
  rectangle1.w = SCREEN_WIDTH / 2;
  rectangle1.h = SCREEN_HEIGHT / 2;
  SDL_FillRect(windowSurface, &rectangle1,
               SDL_MapRGB(windowSurface->format, 0, 255, 255));

  SDL_UpdateWindowSurface(window);

  SDL_Delay(5000);

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}