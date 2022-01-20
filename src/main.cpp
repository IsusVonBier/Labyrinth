#include "Game.hpp"

int main(int argc, char *argv[]) {
  Game game;
  game.initialize();

  game.createWindow();

  game.loadGameMap();
  game.printGameMap();
  game.setupGameMapSurface();
  game.run();

  game.shutdown();

  return 0;
}