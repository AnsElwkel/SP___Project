#pragma once
#include"includes.h"
#include"Editor.h"
#include"Story.h"
#include"character.h"
#include"Game.h"
#include"Enemies.h"
#include"Settings.h"
#include"GameManager.h"
#include"states.h"
#include "button.h"
struct mainMenu : states
{
	sf::RectangleShape Background;
	sf::Font font;
	sf::Texture texBackgnd;
	map<string, button*>buttons;
	Event ev;
	mainMenu(sf::RenderWindow* windoww, stack<states*>*m,Event &ev);
	~mainMenu();
	sf::Clock dt;
	void buttoninit();
	void buttonRender(sf::RenderTarget* target);
	void buttonUpdate();
	void FontInit();
	void end();
	void Updatebind(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

