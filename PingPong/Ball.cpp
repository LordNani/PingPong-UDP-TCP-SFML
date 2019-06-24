#include "Ball.h"



Ball::Ball(unsigned startX,unsigned startY,bool isFlyingRight,sf::Texture* texture)
{
	exists = true;
	if(isFlyingRight)
		this->velocity.x = defaultVelocity;
	else
		this->velocity.x = -defaultVelocity;
	this->velocity.y = defaultVelocity;
	this->position.x = startX;
	this->position.y = startY;
	this->ballSp.setPosition(startX, startY);
	this->ballSp.setOrigin(20, 20);
	this->ballSp.setTexture(*texture);
}


Ball::~Ball()
{
	exists = false;
}


void Ball::draw(sf::RenderWindow& target) {
	target.draw(ballSp);
}


void Ball::update() {
	ballSp.move(velocity);
	position = ballSp.getPosition();
}

void Ball::hit(bool horizontal) {

	if (horizontal)
		velocity.y = -velocity.y;
	else
		velocity.x = -velocity.x;
}

sf::Vector2f Ball::getPosition() {
	return position;
}