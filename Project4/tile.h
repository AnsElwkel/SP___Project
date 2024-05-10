#pragma once
#include "includes.h"
struct tile
{
	sf::RectangleShape Tile;
	std::string  type;
//	bool once = 1,once1=1;
	int health = 0;
	sf::IntRect what, TILE, tr = { 49 * 8 + 20,147,70,100 };
	sf::Texture* tex = nullptr;
	int id=0,whichTexture=-0;
	tile(float x, float y, float sizef, sf::Texture* tex, sf::IntRect Rect, std::string s);
	tile();
	void render(sf::RenderTarget* target, sf::RectangleShape Tile, sf::Vector2f sizef, int x, int y);
	void render1(sf::RenderTarget* target, sf::Vector2f sizef, int x, int y);

};