#pragma once
#include"includes.h"
#include"button.h"
struct PauseMenu
{
	std::map<std::string, button*>buttons;
	sf::RectangleShape Background, List;
	sf::Font font;
	void FontInit();
	void addbutton(std::string s, int width, int height, float left, float top);
	PauseMenu(sf::RenderWindow* window);
	void destroy();
	void render(sf::RenderTarget *target);
	void update();
};

