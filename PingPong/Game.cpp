#include "Game.h"
#define padHeight 150
#define padWidth 40
#define ballSize 20

Game::Game(unsigned width, unsigned height, const unsigned FPS, bool isClient) {
  this->width = width;
  this->height = height;
  pWindow = new sf::RenderWindow(sf::VideoMode(width, height), "Ping!");
  pWindow->setFramerateLimit(FPS);
  this->isClient = isClient;
  std::cout << "Initialization ran with " << initGame() << " errors"
            << std::endl;
}

Game::~Game() {
  delete pWindow;
  pWindow = nullptr;
}

void Game::Run() {

  sf::Clock clock;
  float deltaTime;
  bool isRunning = true;
  while (isRunning) {
    deltaTime = clock.restart().asSeconds();
    isRunning = ProcessEvents();
    if (!isRunning)
      return;
    if (ball->getPosition().x < 0 || ball->getPosition().x > width - ballSize)
      ball->hit(false);
    if (ball->getPosition().y < 0 || ball->getPosition().y > height - ballSize)
      ball->hit(true);
    Update(deltaTime);
    Draw();
  }
}

bool Game::ProcessEvents() {
  sf::Event event;
  while (pWindow->pollEvent(event)) {
    switch (event.type) {
    case sf::Event::Closed:
      pWindow->close();
      return false;
      break;
    }
  }
  return true;
}

void Game::Update(float deltaTime) {
  ball->update(deltaTime);
  pad1->update(deltaTime, 1);
  pad2->update(deltaTime, -1);
}

void Game::Draw() {
  pWindow->clear(sf::Color::Black);
  ball->draw(*pWindow);
  pad1->draw(*pWindow);
  pad2->draw(*pWindow);
  pWindow->display();
}

int Game::initGame() {
  int initResult = 0;
  if (!ResourceManager::getInstance()->addTextureFromFile("ball.png", "ball"))
    initResult++;
  if (!ResourceManager::getInstance()->addTextureFromFile("Pad.png", "pad"))
    initResult++;
  ball = new Ball(width / 2, height / 2, true,
                  ResourceManager::getInstance()->RequestTexture("ball"));
  pad1 = new Pad(0, height / 2 - padHeight / 2, 1,
                 ResourceManager::getInstance()->RequestTexture("pad"));
  pad2 = new Pad(width - padWidth, height / 2 - padHeight / 2, 2,
                 ResourceManager::getInstance()->RequestTexture("pad"));
  return initResult;
}
