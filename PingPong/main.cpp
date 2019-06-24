#include <SFML\Graphics.h>
#include "Ball.h"
#include"ResourceManager.h"
#define width 1366
#define height 768

 sf::RenderWindow window(sf::VideoMode(width, height), "ping?pong!",
                        sf::Style::Default);
 sf::Sprite testSp;
 sf::Texture tex;
 sf::Color testColor = sf::Color::Green;
 void pause();
 bool paused = false;
 sf::RectangleShape rect;
int main() {
	window.setFramerateLimit(60);
	ResourceManager::getInstance()->addTextureFromFile("ball.png", "ball");
	Ball ball(width / 2, height / 2, true, ResourceManager::getInstance()->RequestTexture("ball"));
   while (window.isOpen()) {
     sf::Event event;
     while (window.pollEvent(event)) {
       switch (event.type) {
       case sf::Event::Closed:
         window.close();
         break;
       case sf::Event::LostFocus:
         pause();
         break;
       }
     }
	 if (ball.getPosition().x < 20 || ball.getPosition().x > width - 20)
		 ball.hit(false);
	 if (ball.getPosition().y < 20 || ball.getPosition().y > height - 20)
		 ball.hit(true);
	 ball.update();
         window.clear(sf::Color::Black);
		 ball.draw(window);
         window.display();

   } 
  return 0;
}

 void pause() {
	while(paused){
		sf::Event event;
		while (window.pollEvent(event)) {
			if(event.type ==  sf::Event::GainedFocus){
				paused = false;
			}
		}
	}
}
