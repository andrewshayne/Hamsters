#pragma once

#include "GameState.h"

#include <memory>
#include <stack>

using namespace std;

//#include "World.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
	const float SCALE;
	const sf::Vector2u RESOLUTION;
	const sf::Time TIME_PER_FRAME;

	sf::RenderWindow window;

	stack<unique_ptr<GameState>> stateStack;

private:
	void processInput();
	void update(sf::Time dt);
	void guiUpdate();
	void render();

	// why was this even here?
	//void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	//void handlePlayerInput(sf::Mouse::Button button, bool isPressed, sf::Vector2i mousePosition);

public:
	Game(void);
	~Game(void);

	void run();
	void pushState(unique_ptr<GameState> state);
	void popState();
	void changeState(unique_ptr<GameState> state);

	sf::Vector2u getResolution();
};

