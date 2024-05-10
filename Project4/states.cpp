#include "states.h"
states::states(sf::RenderWindow *window,stack<states*>*gameStates)
{
	this->window = window;
	quit = false;
	this->gameStates = gameStates;
	Exit = false;
	ispressed = false;
	Pause = 0;
}

states::~states()
{
}

void states::pause()
{
	Pause ^=true;
}

bool states::close()
{
	return Exit;
}

const bool states::getQuit() const
{
	return quit;
}

void states::UpdateMousePos(sf::View *view)
{
	mousePositionScreen = sf::Mouse::getPosition();
	mousePositionWindow= sf::Mouse::getPosition(*window);
	if (view)
		window->setView(*view);
	mousePositionView =window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	window->setView(window->getDefaultView());
}
void states::endstate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete))
	{
		quit = true;
	}
	else
		quit = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && !ispressed)
	{
		pause();
		ispressed = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		ispressed = false;

}

