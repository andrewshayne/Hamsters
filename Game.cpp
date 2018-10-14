#include "Game.h"

#include "MenuState.h"
#include "PauseState.h"
#include "PlayState.h"

#include <iostream>

// be sure to #include <Windows.h> .. at least temporarily
    

using namespace std;

Game::Game() : SCALE(1.f), TIME_PER_FRAME(sf::seconds(1.f/60.f)), RESOLUTION({(unsigned)(1600.f * SCALE), (unsigned)(900.f * SCALE)}), window(sf::VideoMode(RESOLUTION.x, RESOLUTION.y), "Hamster Game", sf::Style::Close)
{
	unique_ptr<MenuState> menuState(new MenuState(*this, this->window));
	pushState(move(menuState));

	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	//window.setFramerateLimit(60);
	window.setView(window.getDefaultView());
}


Game::~Game(void)
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//GAME LOOP
	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    while (window.isOpen())
    {
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while(timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processInput();
			update(TIME_PER_FRAME);
		}
		render();
    }
	ImGui::SFML::Shutdown();
}

void Game::pushState(unique_ptr<GameState> state)
{
	stateStack.push(move(state));
}

void Game::popState()
{
	stateStack.pop();
}

void Game::changeState(unique_ptr<GameState> state)
{
	popState();
	pushState(move(state));
}

void Game::processInput()
{
	sf::Event event;
	while(window.pollEvent(event)) //necessary for window to process internal events, even if unused by me
	{
		ImGui::SFML::ProcessEvent(event);

		//Real-time input, put a function here later
		switch(event.type)
		{
		case sf::Event::KeyPressed:
			stateStack.top()->handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			stateStack.top()->handlePlayerInput(event.key.code, false);
			break;
		//case sf::Event::MouseMoved:
		//	stateStack.top()->handlePlayerInput();
		//	break;
		case sf::Event::MouseButtonPressed:
			stateStack.top()->handlePlayerInput(event.mouseButton.button, true, sf::Mouse::getPosition(window));
			break;
		case sf::Event::MouseButtonReleased:
			stateStack.top()->handlePlayerInput(event.mouseButton.button, false, sf::Mouse::getPosition(window));
			break;
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{
				printf("scroll delta: ");
				std::cout << event.mouseWheelScroll.delta << std::endl;
				stateStack.top()->handlePlayerInputScroll(event.mouseWheelScroll.delta, sf::Mouse::getPosition()); //get raw Desktop mouse position
			}
			break;

			//close window
		case sf::Event::Closed:
			window.close();
			break;
		}
	}

	//player.handleRealtimeInput(commands);
	//yeah right^
}

void Game::update(sf::Time dt)
{
	stateStack.top()->update(dt, sf::Mouse::getPosition(window));
}

void Game::render()
{
	//window.setView(window.getDefaultView());
	stateStack.top()->draw();
	window.display();
}

sf::Vector2u Game::getResolution()
{
	return window.getSize();
}