#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	Game game(1366, 768, 60, true);
	game.Run();
  return 0;
}
