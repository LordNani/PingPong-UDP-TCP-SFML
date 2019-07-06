#include "Pad.h"


Pad::Pad(float posX, float posY, int playerID, sf::Texture* texture)
{
	padSpr.setTexture(*texture);
	padSpr.setPosition(posX, posY);
	padSpr.setScale(0.8f, 0.75f);
}

Pad::~Pad()
{
}

sf::Vector2f Pad::getPosition()
{
	return padSpr.getPosition();
}

void Pad::update(float dt,int dir) //-1 - stop, 0 - down, 1 - up
{
	if (dir == 1)
		padSpr.move(0, -moveSpeed * dt);
	else if (dir == 0)
		padSpr.move(0, moveSpeed * dt);
}

void Pad::draw(sf::RenderWindow& window)
{
	window.draw(padSpr);
}

