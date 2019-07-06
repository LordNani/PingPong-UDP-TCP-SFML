#include "Ball.h"



Ball::Ball(unsigned startX,unsigned startY,bool isFlyingRight,sf::Texture* texture)
{
	exists = true;
	if(isFlyingRight)
		this->velocity.x = defaultVelocity;
	else
		this->velocity.x = -defaultVelocity;
	this->velocity.y = defaultVelocity;
	this->ballSpr.setPosition(startX, startY);
	this->ballSpr.setTexture(*texture);
	this->ballSpr.setScale(0.5f,0.5f);
}


Ball::~Ball()
{
	exists = false;
}


void Ball::draw(sf::RenderWindow& target) {
	target.draw(ballSpr);
}


void Ball::update(float dt) {
	ballSpr.move(velocity*dt);
}

void Ball::hit(bool horizontal) {
	if (velocity.x > 0.f)
		velocity.x += speedIncrement;
	else 
		velocity.x -= speedIncrement;
	if (velocity.y > 0.f)
		velocity.y += speedIncrement;
	else 
		velocity.y -= speedIncrement;
	if (horizontal)
		velocity.y = -velocity.y;
	else
		velocity.x = -velocity.x;
}

sf::Vector2f Ball::getPosition() {
	return ballSpr.getPosition();
}