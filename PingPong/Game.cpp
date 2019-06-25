#include "Game.h"



Game::Game(unsigned width, unsigned height, const unsigned FPS, bool isClient)
{
	std::cout << "Initialization ran with " << init() << " errors" << std::endl;
	pWindow = new sf::RenderWindow(sf::VideoMode(width, height), "Ping!");
	pWindow->setFramerateLimit(FPS);
	this->isClient = isClient;
	this->width = width;
	this->height = height;
	ball = new Ball(width / 2, height / 2, true, ResourceManager::getInstance()->RequestTexture("ball"));
}


Game::~Game()
{
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
		if (!isRunning) return;
		if (ball->getPosition().x < 10 || ball->getPosition().x > width - 10)
			ball->hit(false);
		if (ball->getPosition().y < 10 || ball->getPosition().y > height - 10)
			ball->hit(true);
		Update(deltaTime);
		Draw();
	}

}

bool Game::ProcessEvents()
{
	sf::Event event;
	while (pWindow->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			pWindow->close();
			return false;
			break;
		case sf::Event::LostFocus:
			pause();
			break;
		}
	}
	return true;
}

void Game::pause() {
	bool paused = true;
	while (paused) {
		sf::Event event;
		while (pWindow->pollEvent(event)) {
			if (event.type == sf::Event::GainedFocus) {
				paused = false;
			}
		}
	}
}

void Game::Update(float deltaTime)
{
	ball->update(deltaTime);
}

void Game::Draw()
{
	pWindow->clear(sf::Color::Black);
	ball->draw(*pWindow);
	pWindow->display();
}

int Game::init()
{
	int initResult = 0;
	if (!ResourceManager::getInstance()->addTextureFromFile("ball.png", "ball"))
		initResult++;

	return initResult;
}

