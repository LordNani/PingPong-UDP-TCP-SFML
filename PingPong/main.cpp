#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	Game game(1366, 768, 30, true);
	game.Run();
  return 0;
}
