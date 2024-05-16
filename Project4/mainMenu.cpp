#include "mainMenu.h"
int u = 1;
mainMenu::mainMenu(sf::RenderWindow* windoww,stack<states*>*m,Event &ev) : states(windoww,m)
{
	Background.setSize(sf::Vector2f(windoww->getSize().x, windoww->getSize().y));
	texBackgnd.loadFromFile("./res/siltara4.jpg");
	Background.setTexture(&texBackgnd);
	FontInit();
	buttoninit();
	this->ev = ev;
}
mainMenu::~mainMenu()
{
}
void mainMenu::buttoninit()
{
	buttons["New Game"] = new button;
	buttons["New Game"]->Button(font, "New Game", sf::Color(0, 0, 0, 255), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 360, 60, window->getSize().x / 2 - 180 * window->getSize().x / 1920, 300);
	buttons["Load Game"] = new button;
	buttons["Load Game"]->Button(font, "Load Game", sf::Color(0, 0, 0, 255), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 360, 60, window->getSize().x/2-180*window->getSize().x/1920, 400);
	buttons["settings"] = new button;
	buttons["settings"]->Button(font, "Settings", sf::Color(0, 0, 0, 255), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 360, 60, window->getSize().x / 2 - 180 * window->getSize().x / 1920, 500);
	buttons["editor"] = new button;
	buttons["editor"]->Button(font, "MAP", sf::Color(0, 0, 0, 255), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 360, 60, window->getSize().x / 2 - 180 * window->getSize().x / 1920, 600);
	buttons["exit"] = new button;
	buttons["exit"]->Button(font, "Exit", sf::Color(0, 0, 0, 255), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 0, 80), 360, 60, window->getSize().x / 2 - 180 * window->getSize().x / 1920, 700);
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
	if (buttons["Load Game"]->isPressed())
	{
		//Load from files
		
		fstream fin;
		float x, y;
		fin.open("saveGame.txt", ios::trunc | ios::in | ios::out);
		//Hero
		fin >> x >> y;

		//Include GameManager
		
		/*fin	>> story->hero.stamina >> story->hero.health >> story->hero.walk ;
		fin >> story->hero.run >> story->hero.damage >> story->hero.score;
		fin >> story->hero.hunger;*/
		
		//Resources
		fin >> inventory.currentIron >> inventory.currentStones >> inventory.currentWood;

	
		for (int i = 0; i < 27; ++i) {
			fin >> inv_items[i].weapon_or_mawared_or_nothing;
			fin >> inv_items[i].mawared.quantity >> inv_items[i].mawared.type;
			fin >> inv_items[i].weapons.health >> inv_items[i].weapons.type;
		}

		fin.close();
		story->hero.sprite.setPosition({ x, y });

		gameStates->push(new GameManager(window, gameStates));
	}
	if (buttons["New Game"]->isPressed())
	{
		gameStates->push(new GameManager(window, gameStates));
	}
	if (buttons["editor"]->isPressed())
	{
		gameStates->push(new Editor(window, gameStates));
	}
	if (buttons["settings"]->isPressed())
	{
		gameStates->push(new menuSettings(window,gameStates,ev));
	}
}
void mainMenu::FontInit()
{
	if (!font.loadFromFile("./minecraft_font.ttf")) 
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