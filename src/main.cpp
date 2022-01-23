#include "Game.hpp"

int main(int argc, char *argv[]) {
  Game game;
  game.initialize();

  game.createWindow();

  game.newGame();
//   game.printGameMap();
  game.run();

  game.shutdown();

  return 0;
}