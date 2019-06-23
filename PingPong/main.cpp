#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include"ResourceManager.h"

 sf::RenderWindow window(sf::VideoMode(800, 600), "ping?pong!",
                        sf::Style::Default);
 sf::Sprite testSp;
 sf::Texture tex;
 sf::Color testColor = sf::Color::Green;
 void pause();
 bool paused = false;
 sf::RectangleShape rect;
int main() {
	ResourceManager::getInstance()->addImageFromColor(200, 200, testColor, "2");
	ResourceManager::getInstance()->addTextureFromImage(*ResourceManager::getInstance()->RequestImage("2"),"newText");
	ResourceManager::getInstance()->addImageFromFile("test.jpg", "test");
	ResourceManager::getInstance()->addTextureFromFile("karel1.png", "test");
	rect.setPosition(400, 300);
	rect.setSize(sf::Vector2f(300, 300));
	rect.setTexture(ResourceManager::getInstance()->RequestTexture("test"));
	testSp.setTexture(*ResourceManager::getInstance()->RequestTexture("newText"));
	testSp.setPosition(0, 0);
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
         window.clear(sf::Color::Red);
		 window.draw(rect);
		 window.draw(testSp);
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

