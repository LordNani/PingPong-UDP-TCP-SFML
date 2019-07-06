#pragma once
#include "Ball.h"
#include "Pad.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#ifndef _NOEXCEPT
#define _NOEXCEPT noexcept
#endif

class Game {
public:
  Game(unsigned width, unsigned height, const unsigned FPS, bool isClient);
  ~Game();
  void Run();

private:
  bool ProcessEvents();
  void Update(float deltaTime);
  void Draw();
  int initGame();

private:
  sf::RenderWindow *pWindow = nullptr; // change to new RenderWindow
  bool isClient;
  unsigned width, height;
  Ball *ball;
  Pad *pad1;
  Pad *pad2;
};
