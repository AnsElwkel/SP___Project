#pragma once
#include"includes.h"
#include"states.h"
#include"Map.h"
#include"mainMenu.h"
#include "button.h"
struct application
{
	// variables
	sf::RenderWindow* window;
	sf::Event ev;
	stack<states*>state;
	bool notPressing = true;
	double deltatime;
	bool be = 0;
	sf::Clock dt;
	//methods
	~application();
	void update();
	void render();
	void DeltaUpdate(float dt);
	void EventsUpdate();
	application(sf::RenderWindow* window);
	void statesinitializer();
	bool isRunning();
};

