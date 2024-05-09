#pragma once
#include"includes.h"
struct button
{
	sf::RectangleShape buttons;
	sf::Font font;
	sf::Text text;
	sf::Color hover;
	sf::Color clicked;
	sf::Color none;
	std::string write;
	bool noneb = 0, hoverb = 0, clickedb = 0;
	void Button(sf::Font f , std::string s, sf::Color h,sf::Color c, sf::Color n,int width,int height,int left , int top);
	//void Button(sf::Font f, std::string s, sf::Color h, sf::Color n, int width, int height, int left, int top, sf::Color c);
	void update(sf::Vector2i pos );
	bool isPressed();
	void render(sf::RenderTarget* target);
};

