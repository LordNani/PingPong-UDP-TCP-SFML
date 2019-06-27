#include "Pad.h"


Pad::Pad(float posX, float posY, int playerID, sf::Texture* texture)
{
	padSpr.setTexture(*texture);
	padSpr.setPosition(posX, posY);
	padSpr.setScale(3.f, 1.f);
	padSpr.setOrigin(sf::Vector2f(padSpr.getGlobalBounds().width / 2, padSpr.getGlobalBounds().height / 2));
}

Pad::~Pad()
{
}

sf::Vector2f Pad::getPosition()
{
	return padSpr.getPosition();
}

void Pad::update(float dt,bool dir) // true - up, false - down
{
	if (dir)
		padSpr.move(0, -moveSpeed * dt);
	else
		padSpr.move(0, moveSpeed * dt);
}

void Pad::draw(sf::RenderWindow& window)
{
	window.draw(padSpr);
}

