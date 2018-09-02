#include <iostream>
#include "Game.h"
#include "Textures.h"

Game::Game(int width, int height)
	:mWindow(sf::VideoMode(width, height), "GameX"), mWindowSize(mWindow.getSize()),
	TIME_PER_FRAME(sf::seconds(1 / 60.f)) {
	if (!mFont.loadFromFile("resources\\fonts\\UbuntuMono-R.ttf")) {
		std::cout << "Failed to load font." << std::endl;
	}
	else {
		mDebugMessage.setString("Debug: ");
		mDebugMessage.setFont(mFont);
		mDebugMessage.setCharacterSize(20);
		mDebugMessage.setPosition(10.f, mWindowSize.y - 30.f);

		mFrameRate.setString("FrameRate: ");
		mFrameRate.setFont(mFont);
		mFrameRate.setCharacterSize(20);
		mFrameRate.setPosition(mWindowSize.x - 200.f, 10.f);

	}

	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Red);

	mTextureHolder.load(Textures::Airplane, "Resources/Textures/Raptor.png");
	mPlane.setTexture(mTextureHolder.get(Textures::Airplane));
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeElapsedSinceLastUpdate;
	while (mWindow.isOpen()) {
		timeElapsedSinceLastUpdate += clock.restart();
		while (timeElapsedSinceLastUpdate > TIME_PER_FRAME) {
			timeElapsedSinceLastUpdate -= TIME_PER_FRAME;
			processEvents();
			update(TIME_PER_FRAME);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mWindow.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			handlePlayerInput(event.key.code, true);
		}
		else if (event.type == sf::Event::KeyReleased) {
			handlePlayerInput(event.key.code, false);
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp) {
		movement.y -= 1.f;
	}
	if (mIsMovingDown) {
		movement.y += 1.f;
	}
	if (mIsMovingLeft) {
		movement.x -= 1.f;
	}
	if (mIsMovingRight) {
		movement.x += 1.f;
	}
	mPlayer.move(movement);
	std::string message = "vector: x:" + std::to_string(movement.x) + " y:" + std::to_string(movement.y);
	d(message);
	mFrameRate.setString("FrameRate: " + std::to_string(1 / deltaTime.asSeconds()) + " fps");
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlane);
	mWindow.draw(mDebugMessage);
	mWindow.draw(mFrameRate);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::Up:
		mIsMovingUp = isPressed;
		break;
	case sf::Keyboard::Down:
		mIsMovingDown = isPressed;
		break;
	case sf::Keyboard::Left:
		mIsMovingLeft = isPressed;
		break;
	case sf::Keyboard::Right:
		mIsMovingRight = isPressed;
		break;

	default:
		break;
	}
}

