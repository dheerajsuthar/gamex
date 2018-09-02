#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
class Game {
public:
	Game(int width = 800, int height = 600);
	void run();
	void d(const std::string& message) {
		mDebugMessage.setString("debug: " + message);
	}
private:
	void processEvents();
	void update(sf::Time);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow mWindow;
	sf::Vector2f mWindowSize;
	sf::CircleShape mPlayer;
	sf::Text mFrameRate;
	sf::Text mDebugMessage;
	sf::Font mFont;
	ResourceHolder<sf::Texture, Textures> mTextureHolder;
	sf::Sprite mPlane;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	const sf::Time TIME_PER_FRAME;
};