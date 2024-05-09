#include "PauseMenu.h"
PauseMenu::PauseMenu(sf::RenderWindow* window)
{
	Background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	Background.setFillColor(sf::Color(0, 0, 0, 80));
	List.setSize(sf::Vector2f(window->getSize().x * 0.2, window->getSize().y * 0.4));
	List.setFillColor(sf::Color(100, 100, 100, 120));
	List.setPosition(window->getSize().x * 0.4, window->getSize().y * 0.3);
	FontInit();
}
void PauseMenu::FontInit()
{
	if (!font.loadFromFile("./res/Vogue.ttf")) {
		throw("error!!! can't load font\n");
	}
}

void PauseMenu::addbutton(std::string s,int width,int height,float left,float top)
{
	buttons[s] = new button;
	buttons[s]->Button(font, s, sf::Color(0, 0, 255, 120), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), width, height, left, top);
}
void PauseMenu::destroy()
{
	delete& Background;
	delete &List;
	for (auto& i : buttons)
	{
		delete &i;
	}
}
void PauseMenu::render(sf::RenderTarget* target)
{
	target->draw(Background);
	target->draw(List);
	for (auto& i : buttons)
	{
		i.second->render(target);
	}
}
void PauseMenu::update()
{

}
