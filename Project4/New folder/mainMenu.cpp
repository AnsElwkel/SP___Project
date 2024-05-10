#include "mainMenu.h"
int u = 1;
mainMenu::mainMenu(sf::RenderWindow* windoww,stack<states*>*m) : states(windoww,m)
{
	Background.setSize(sf::Vector2f(windoww->getSize().x, windoww->getSize().y));
	Background.setTexture(&texBackgnd);
	FontInit();
	buttoninit();
}
mainMenu::~mainMenu()
{
}
void mainMenu::buttoninit()
{
	buttons["Game"] = new button;
	buttons["Game"]->Button(font, "MARIO", sf::Color(0, 0, 255, 120), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 280, 60, 200, 400);
	buttons["editor"] = new button;
	buttons["editor"]->Button(font, "Editor", sf::Color(0, 0, 255, 120), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 280, 60, 200, 600);
	buttons["exit"] = new button;
	buttons["exit"]->Button(font, "Exit", sf::Color(0, 0, 255, 120), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 280, 60, 200, 700);
}
void mainMenu::buttonRender(sf::RenderTarget *target) 
{
	for(auto &i:buttons)
	{
		i.second->render(target);
	}
}
void mainMenu::buttonUpdate()
{
	for (auto& i : buttons)
	{
		i.second->update((Vector2i)mousePositionView);
	}
	if (buttons["exit"]->isPressed())
	{
		quit = true;
	}
	if (buttons["Game"]->isPressed())
	{
		gameStates->push(new GameManager(window, gameStates));
	}
	if (buttons["editor"]->isPressed())
	{
		gameStates->push(new Editor(window, gameStates));
	}
}
void mainMenu::FontInit()
{
	if (!font.loadFromFile("./res/Vogue.ttf")) 
	{
		throw("error!!! can't load font\n");
	}
}

void mainMenu::end()
{
	cout << "mainmenu State Has Closed" << endl;
}

void mainMenu::Updatebind(const float& dt)
{
	endstate();
}

void mainMenu::update(const float& dt)
{
	//ImGui::SFML::Update(*window, this->dt.restart());
	Updatebind(dt);
	UpdateMousePos();
	buttonUpdate();
}

void mainMenu::render(sf::RenderTarget* target)
{
	target->draw(Background);
	buttonRender(target);
}