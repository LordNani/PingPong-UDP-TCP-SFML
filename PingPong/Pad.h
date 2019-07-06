#pragma once
#include <SFML/Graphics.hpp>
class Pad
{
public:
	Pad(float posX, float posY, int playerID, sf::Texture *texture);
	~Pad();
	sf::Vector2f getPosition();
	void update(float dt, int dir);
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite padSpr;
	float moveSpeed = 300.f;
};

