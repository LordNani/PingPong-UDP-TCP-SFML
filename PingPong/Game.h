#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Ball.h"
#include <iostream>
#include <chrono>

#ifndef _NOEXCEPT
#define _NOEXCEPT noexcept
#endif

class Game
{
public:
	Game(unsigned width, unsigned height, const unsigned FPS, bool isClient);
	~Game();
	void Run();
private:
	bool ProcessEvents();
	void pause();
	void Update(float deltaTime);
	void Draw();
	int init();
	
private:
	sf::RenderWindow *pWindow = nullptr;  // change to new RenderWindow
	bool isClient;
	unsigned width, height;
	Ball* ball;


};

