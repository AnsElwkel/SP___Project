#include "application.h"
void application::update()
{ 
	EventsUpdate();
	if (!state.empty())
	{
		state.top()->update(deltatime);
		if ((state.top()->getQuit()&&notPressing))
		{
			notPressing = false;
			state.top()->end();
			delete state.top();
			state.pop();
		}
		else if (!state.top()->getQuit() && !notPressing)
		{
			notPressing = true;
		}
	}
	else
	{
		window->close();
	}
	
}

void application::render()
{
	window->clear();
	if (!state.empty())
		state.top()->render(window);
	window->display();
}

void application::DeltaUpdate(float dt)
{
	deltatime = dt;
	////cout << 1.0/deltatime << endl;
}

void application::statesinitializer()
{
	state.push(new mainMenu(window, &state,ev));
}

void application::EventsUpdate()
{
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
	}
}

application::application(sf::RenderWindow *window)
{ 
	this->window = window;
	statesinitializer();
}

application::~application()
{
	delete window;
	while (!state.empty())
	{
		delete state.top();
		state.pop();
	} 
}

bool application::isRunning()
{
	return window->isOpen();
}

