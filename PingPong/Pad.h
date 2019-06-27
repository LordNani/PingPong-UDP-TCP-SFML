#pragma once
#include <SFML/Graphics.hpp>
class Pad
{
public:
	Pad(float posX, float posY, int playerID, sf::Texture *texture);
	~Pad();
	sf::Vector2f getPosition();
	void update(float dt, bool dir);
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite padSpr;
	float moveSpeed = 150.f;
};

