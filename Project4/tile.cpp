#include "tile.h"

tile::tile(float x, float y, float sizef, sf::Texture *tex,sf::IntRect Rect,std::string s)
{
	what = Rect;
	this->tex = tex;
	Tile.setTexture(this->tex);
	Tile.setTextureRect(Rect);
	Tile.setSize(sf::Vector2f(sizef, sizef));
	Tile.setPosition(sizef*x, sizef*y);
	type = s;
}
tile::tile()
{
}
void tile::render(sf::RenderTarget* target,sf::RectangleShape Tile,sf::Vector2f sizef, int x, int y)
{
	//if (once1)
	{
		Tile.setSize(sizef);
		Tile.setPosition(x, y);
		//once1 = 0;
	}
	target->draw(Tile);
}
void tile::render1(sf::RenderTarget* target, sf::Vector2f sizef, int x, int y)
{
	//if (once)
	{
		Tile.setSize(sizef);
		Tile.setPosition(x, y);
		//once = 0;
	}
	target->draw(Tile);
}
