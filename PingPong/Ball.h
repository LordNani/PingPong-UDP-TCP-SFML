#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
public:
	Ball(unsigned startX, unsigned startY, bool isFlyingRight, sf::Texture* texture);
	~Ball();
	void draw(sf::RenderWindow& target);
	void update();
	void hit(bool horizontal);
	sf::Vector2f getPosition();
private: 
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Sprite ballSp;
	const float speedIncrement = 0.2f;
	const float defaultVelocity = 4.f;
	bool exists;
};

