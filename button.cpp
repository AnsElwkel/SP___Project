#include "button.h"
void button::Button(sf::Font f, std::string s,sf::Color h, sf::Color c, sf::Color n, int width, int height, int left, int top)
{
	buttons.setSize(sf::Vector2f(width, height));
	buttons.setPosition(left, top);
	hover = h;
	none = n;
	clicked = c;
	font = f;
	text.setFont(font);
	text.setString(s);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(35);
	text.setPosition(buttons.getPosition().x+ (((float)width - (text.getGlobalBounds().width)) / 2.0), (buttons.getPosition().y + (((float)height - (text.getGlobalBounds().height)) / 2.0)-5));
}
void button::update(sf::Vector2i pos)
{

	if (buttons.getGlobalBounds().contains(sf::Vector2f(pos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			clickedb = 1;
			noneb = 0;
			hoverb = 0;
		}
		else
		{
			clickedb = 0;
			noneb = 0;
			hoverb = 1;
		}
		
	}
	else
	{
		clickedb = 0;
		noneb = 1;
		hoverb = 0;
	}
	if (clickedb == 1)
		buttons.setFillColor(clicked);
	else if (hoverb == 1)
		buttons.setFillColor(hover);
	else
		buttons.setFillColor(none);
}
bool button::isPressed()
{
	if (clickedb)
		return true;
	//return false;
}
void button::render(sf::RenderTarget* target)
{
	target->draw(buttons);
	target->draw(text);
}
