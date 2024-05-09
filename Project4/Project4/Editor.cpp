#include "Editor.h"
bool isCatch;
Editor::Editor(sf::RenderWindow* window, stack<states*>* m):states(window,m)
{
	tiles = new Map(50,200, 120);
	tiles->Lands.push_back(new lands(sf::Vector2f(tiles->maxSize), 0, 0, 40, 5, 45, tiles->Gridsizef, "land0.txt", 1));
	FontInit();
	pausinit();
	stat = status(100, 65, 100, 65, Color(80, 90, 100, 100), 30, font);
	tex[0]->loadFromFile("./res/map.png");
	tex[1]->loadFromFile("./res/m.png");
	tex[2]->loadFromFile("./res/dungeonex.png");
	UI();
	camera.setSize(sf::Vector2f(window->getSize()));
	camera.setCenter(sf::Vector2f(camera.getSize() / 2.f));
}

Editor::~Editor()
{
	for (auto& i : PauseM->buttons)
	{
		delete& i;
	}
	delete tiles;
	delete& selector;
}

void Editor::end()
{
	cout << "editor has closed\n";
}

void Editor::pausinit()
{
	PauseM->List.setSize(sf::Vector2f(window->getSize().x * 0.2, window->getSize().y * 0.45));
	PauseM->List.setPosition(sf::Vector2f(window->getSize().x * 0.4, window->getSize().y * 0.325));
	PauseM->addbutton("continue", 280*window->getSize().x/1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 400 / 1080.0 * window->getSize().y);
	PauseM->addbutton("Mainmenu", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 700 / 1080.0 * window->getSize().y);
	PauseM->addbutton("load", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 600 / 1080.0 * window->getSize().y);
	PauseM->addbutton("Save", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 500 / 1080.0 * window->getSize().y);
}

void Editor::UI()
{
	selectorRect.setSize(sf::Vector2f(tiles->Gridsizef,tiles->Gridsizef));
	selectorRect.setFillColor(sf::Color::Transparent);
	selectorRect.setOutlineColor(sf::Color::Red);
	selectorRect.setOutlineThickness(1);
	selector = textureSelector(500, 500,tiles->Gridsizef, tex[elem1], font);
	TexRect = sf::IntRect(-1, 0,33, 33);
	isCatch = 0;
}
bool Editor::valid(int x, int y)
{
	if (x < tiles->maxSize.x and x >= 0 and y < tiles->maxSize.y and y >= 0)
	{
		return true;
	}
	return false;
}
void Editor::add(unsigned x, unsigned y, unsigned z, float GridSize, sf::Texture& SelectByS, string type)
{
	if (tiles->Lands.at(tiles->currentLand)->Land[x][y][z] == nullptr)
	{
		tiles->Lands.at(tiles->currentLand)->Land[x ][y][z] = new tile(x * GridSize, y * GridSize, GridSize, &SelectByS, TexRect, type);
		tiles->Lands.at(tiles->currentLand)->count++;
		tiles->Lands.at(tiles->currentLand)->Land[x][y][z]->whichTexture = elem1;

	}
	else if (tiles->Lands.at(tiles->currentLand)->Land[x ][y][z + 1] == nullptr)
	{
		tiles->Lands.at(tiles->currentLand)->Land[x ][y][z + 1] = new tile(x * GridSize, y * GridSize, GridSize, &SelectByS, TexRect, type);
		tiles->Lands.at(tiles->currentLand)->count++;
		tiles->Lands.at(tiles->currentLand)->Land[x ][y][z+1]->whichTexture = elem1;

	}
}

void Editor::remove(unsigned x, unsigned y, unsigned z)
{
	if (tiles->Lands.at(tiles->currentLand)->Land[x ][y][z + 1] != nullptr)
	{
		tiles->Lands.at(tiles->currentLand)->count--;
		tiles->Lands.at(tiles->currentLand)->Land[x ][y][z + 1] = nullptr;
	}
	else if (tiles->Lands.at(tiles->currentLand)->Land[x ][y][z] != nullptr)
	{
		tiles->Lands.at(tiles->currentLand)->Land[x ][y][z] = nullptr;
		tiles->Lands.at(tiles->currentLand)->count--;

	}
}

void Editor::UUI()
{
	selectorRect.setPosition(mousePositionGrid.x*tiles->Gridsizef,mousePositionGrid.y*tiles->Gridsizef);
	cout << arr[elem] << "\n";
}
void Editor::buttonUpdate(){
	for (auto& i : PauseM->buttons)
	{
		i.second->update(mousePositionWindow);
	}
	if (PauseM->buttons["continue"]->isPressed())
		Pause = false;
	if (PauseM->buttons["Mainmenu"]->isPressed())
	{
		quit = true;
	}
	if (PauseM->buttons["Save"]->isPressed())
	{
		tiles->saveTofile();
	}
	if (PauseM->buttons["load"]->isPressed())
	{
		tiles->LoadFromFile(loaded);
		loaded = 1;
	}
}
void Editor::UpdateTile(const float& dt)
{
	delta += dt;

	if (Keyboard::isKeyPressed(Keyboard::RControl) &&Mouse::isButtonPressed(Mouse::Left))
	{
		if ((i.x - e.x) != 0 || (i.y - e.y) != 0)
		{
			activate = 1;
		}
		y = min(i.y, e.y);
		y1 = max(i.y, e.y);
		l = min(i.x, e.x);
		r = max(i.x, e.x);
		e = Vector2f(mousePositionGrid);
	}
	else if (Keyboard::isKeyPressed(Keyboard::RShift) && Mouse::isButtonPressed(Mouse::Left))
	{
		if ((i.x - e.x) != 0 || (i.y - e.y) != 0)
		{
			activate1 = 1;
		}
		y = min(i.y, e.y);
		y1 = max(i.y, e.y);
		l = min(i.x, e.x);
		r = max(i.x, e.x);
		e = Vector2f(mousePositionGrid);
	}
	else 
	{
		i= Vector2f(mousePositionGrid);
		if (activate)
		{
			for (int j = y; j <= y1; j++)
			{
				for (int i = l; i <= r; i++)
				{
					if (valid(i, j))
					{
						add(i, j, 0, tiles->Gridsizef, *tex[elem1], arr[elem]);
					}
				}
			}
			activate = 0;
		}
		else if (activate1)
		{

			for (int j = y; j <= y1; j++)
			{
				for (int i = l; i <= r; i++)
				{

					if (valid(i, j))
					{
						remove(i, j, 0);
					}
				}
			}
			activate1 = 0;
		}
		else if (valid(mousePositionGrid.x, mousePositionGrid.y))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && delta >= 0.12f && !selector.getActive().first && !selector.getActive().second && isCatch)
			{
				add(mousePositionGrid.x, mousePositionGrid.y, 0, tiles->Gridsizef, *tex[elem1], arr[elem]);
				delta = 0;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && delta >= 0.32)
			{
				remove(mousePositionGrid.x, mousePositionGrid.y, 0);
				delta = 0;
			}
			else if (TexRect.left != -1)
				hoverd = tile(mousePositionGrid.x * tiles->Gridsizef, mousePositionGrid.y * tiles->Gridsizef, tiles->Gridsizef, tex[elem1], TexRect, "ss");
		}
	}
	
}

void Editor::Updatebind(const float& dt)
{
	endstate();
}

void Editor::FontInit()
{
	if (!font.loadFromFile("./res/Vogue.ttf"))
	{
		throw("error!!! can't load font\n");
	}
}
void Editor::update(const float& dt)
{
	//cout << arr[elem] << endl;
	Updatebind(dt);
	UpdateMousePos(&camera);
	selector.hide->update(mousePositionWindow);
	mousePositionGrid = sf::Vector2u(static_cast<unsigned>(mousePositionView.x) / tiles->Gridsizef, static_cast<unsigned>(mousePositionView.y) / tiles->Gridsizef);
	if (Pause)
	{
		buttonUpdate();
	}
	else
	{
	
		stat.update(&mousePositionWindow,tiles->currentLand,tiles->Gridsizef,(Vector2f)tiles->maxSize,tiles->Lands);
		selector.update(&mousePositionWindow, TexRect, 50);
		if (!selector.getActive().first && !selector.getActive().second)
			UpdateTile(dt), selectorRect.setSize(sf::Vector2f(tiles->Gridsizef, tiles->Gridsizef)), UUI();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		camera.move(-5, 0);
		startfloat.x -= 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		camera.move(5, 0);
		startfloat.x += 5;
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		startfloat.y -= 5;
		camera.move(0, -5);
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		startfloat.y += 5;
		camera.move(0, 5);
	}
	if (Keyboard::isKeyPressed(Keyboard::RControl) && Keyboard::isKeyPressed(Keyboard::C))
	{
		tiles->Gridsizef += 0.2;
	}
	if (Keyboard::isKeyPressed(Keyboard::RControl) && Keyboard::isKeyPressed(Keyboard::B))
	{
		tiles->Gridsizef -= 0.2;
	}
	delta1 += dt;
	if (Keyboard::isKeyPressed(Keyboard::RControl) && Keyboard::isKeyPressed(Keyboard::Up)&&delta1>0.4)
	{
		elem = min(elem + 1, 8);
		delta1 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::RControl) && Keyboard::isKeyPressed(Keyboard::Down)&&delta1>0.4)
	{
		elem = max(elem - 1, 0);
		delta1 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::RControl) && Keyboard::isKeyPressed(Keyboard::Right) && delta1 > 0.4)
	{
		elem1 = min(elem1 + 1, 2);
		selector.sprite.setTexture(*tex[elem1]);
		if (elem1 == 1)
		{
			selector.Selector.setSize(Vector2f(32 * selector.sprite.getScale().x, 32));
			selector.L = 0;
			selector.T=0;

		}
		else if (!elem1)
		{
			selector.Selector.setSize(Vector2f(49 * selector.sprite.getScale().x, 49));
			selector.L = 3;
			selector.T = 5;
		}
		else
		{
			selector.Selector.setSize(Vector2f(32 * selector.sprite.getScale().x, 32));

		}

		delta1 = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::RControl) && Keyboard::isKeyPressed(Keyboard::Left) && delta1 > 0.4)
	{
		elem1 = max(elem1 - 1, 0);
		selector.sprite.setTexture(*tex[elem1]);
		if (elem1 == 1)
		{
			selector.Selector.setSize(Vector2f(32 * selector.sprite.getScale().x, 32));
			selector.L = 0;
			selector.T = 0;

		}
		else if (!elem1)
		{
			selector.Selector.setSize(Vector2f(49 * selector.sprite.getScale().x, 49));
			selector.L = 3;
			selector.T = 5;
		}
		else
		{
			selector.Selector.setSize(Vector2f(28 * selector.sprite.getScale().x, 28));

		}

		delta1 = 0;
	}
}

void Editor::render(sf::RenderTarget* target)
{
	target->setView(camera);
	startX = startfloat.x/tiles->Gridsizef;
	Vector2i h = (Vector2i)mousePositionView;
	startY = startfloat.y/tiles->Gridsizef;
	tiles->render(startX,(int)(window->getSize().x/tiles->Gridsizef)+5, startY, (int)(window->getSize().y / tiles->Gridsizef)+5, target);
	target->setView(target->getDefaultView());
	if (Pause)
	{
		PauseM->render(target);
	}
	else
	{

		selector.render(target);
		stat.render(target, h, mousePositionGrid, font, tiles->Gridsizef,tiles->currentLand,tiles->Lands.size);
		if (!selector.getActive().first && !selector.getActive().second&&!stat.getActive())
		{
			target->setView(camera);
			target->draw(selectorRect);
			if (isCatch)hoverd.render1(target, { tiles->Gridsizef, tiles->Gridsizef }, mousePositionGrid.x* tiles->Gridsizef, mousePositionGrid.y* tiles->Gridsizef);
			target->setView(target->getDefaultView());
		}
	}
}
Editor::textureSelector::textureSelector()
{

}

Editor::textureSelector::textureSelector(float width, float height, float gridsize, sf::Texture* texture, sf::Font font)
{
	int W = 80, H = 60, L = 2, T = 2;
	hide->Button(font,"TS", sf::Color(0, 0, 255, 180),sf::Color(0, 0, 255, 150), sf::Color(80,90,100,400),W,H,L,T);
	hide->text.setCharacterSize(30);
	hide->text.setPosition(hide->buttons.getPosition().x + (((float)W - (hide->text.getGlobalBounds().width)) / 2.0), (hide->buttons.getPosition().y + (((float)H - (hide->text.getGlobalBounds().height)) / 2.0) - 5));
	bound.setSize(sf::Vector2f(width, height));
	bound.setPosition(L+W,T+10);
	bound.setFillColor(sf::Color(20, 20, 20, 120));
	bound.setOutlineColor(sf::Color::White);
	bound.setOutlineThickness(1.3f);
	sprite.setTexture(*texture);
	sprite.setPosition(bound.getPosition());
	sprite.setScale(0.5, 1);
	Selector.setSize(sf::Vector2f(49*sprite.getScale().x, 49));
	Selector.setPosition(L,T);
	Selector.setFillColor(sf::Color::Transparent);
	Selector.setOutlineColor(sf::Color::Red);
	Selector.setOutlineThickness(1);
	active = 0,active1=0,active2=0;
}

pair<const bool,const bool> Editor::textureSelector::getActive() const
{
	return { active2&active,active1 };
}

void Editor::textureSelector::render(sf::RenderTarget* target)
{
	if (active2)
	{
		target->draw(bound);
		target->draw(sprite);
		if (active)
		{
			target->draw(Selector);
		}
	}
	hide->render(target);
}

void Editor::textureSelector::update(sf::Vector2i* mousepos, sf::IntRect& r, float sizeOfEachOne)
{

	if (bound.getGlobalBounds().contains(static_cast<sf::Vector2f>(*mousepos)))
	{
		active = true;
	}
	else
		active = false;
	if (hide->hoverb || hide->clickedb)
	{
		active1 = 1;
	}
	else
		active1 = 0;
	if (hide->clickedb && !isStillPress)
	{
		active2 ^= 1;
		delta = 0;
		isStillPress = 1;
	}
	if (!hide->clickedb)
		isStillPress = 0;
	if (active && active2)
	{
		mousegrid.x = (-(int)bound.getPosition().x + mousepos->x) / (unsigned)(Selector.getSize().x);
		mousegrid.y = (-(int)bound.getPosition().y + mousepos->y) / (unsigned)Selector.getSize().y;
		Selector.setPosition(bound.getPosition().x + (mousegrid.x * (unsigned)(Selector.getSize().x))+L, bound.getPosition().y + (mousegrid.y * Selector.getSize().y)+T);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isCatch = 1;
			r.left = mousegrid.x * Selector.getSize().x / sprite.getScale().x +T, r.top = mousegrid.y * Selector.getSize().y+T, r.width = Selector.getSize().x/sprite.getScale().x - L, r.height = Selector.getSize().y - L;
		}
	}
}

Editor::status::status()
{

}
Editor::status::status(float x, float y, float width, float height, Color c, int charSize, Font font)
{
	bound.setSize(Vector2f(width*2, 5.5 * height));
	bound.setPosition(x, y);
	bound.setFillColor(c);
	Switch->Button(font, "status", Color(194, 194, 194, 120), Color(194, 194, 194, 120), Color(80, 90, 100, 100), width, height, 100, 0);
	Switch->text.setCharacterSize(charSize);
	Switch->text.setPosition(Switch->buttons.getPosition().x + (((float)width - (Switch->text.getGlobalBounds().width)) / 2.0),
		(Switch->buttons.getPosition().y + (((float)height - (Switch->text.getGlobalBounds().height)) / 2.0) - 5));
	buttons["GoToNext"] = new button;
	buttons["GoToNext"]->Button(font, "Next", Color(194, 194, 194, 120), Color(194, 194, 194, 120), Color(80, 90, 100, 100), 2*width, height, 100, 3.5 * height);
	buttons["GoToPrevious"] = new button;
	buttons["GoToPrevious"]->Button(font, "Previous", Color(194, 194, 194, 120), Color(194, 194, 194, 120), Color(80, 90, 100, 100), 2*width, height, 100, 4.5 * height);
	buttons["New"] = new button;
	buttons["New"]->Button(font, "New", Color(194, 194, 194, 120), Color(194, 194, 194, 120), Color(80, 90, 100, 100), 2*width, height, 100, 5.5 * height);
	active = 0;
	AddActive = 0;
	RemoveActive = 0;
	ispressing = 0;
	ispressing1 = 0;
}
const bool Editor::status::getActive() const
{
	return activeAll;
}
void Editor::status::render(RenderTarget* target, Vector2i& mousepos, Vector2u& mousePositionGrid, Font font, float Grid,int currentLand,int numberOfLands)
{
	Switch->render(target);
	if (active)
	{
		Text mouse;
		mouse.setPosition(100, 65);
		mouse.setFont(font);
		mouse.setFillColor(Color::White);
		mouse.setLineSpacing(2);
		mouse.setCharacterSize(20);
		stringstream s;
		s << "X : " << mousepos.x << "    " << "Y: " << mousepos.y << endl << "GridX: " << mousePositionGrid.x << "   " << "GridY: " << mousePositionGrid.y << endl << "Grid Tile Size : " << Grid<< endl << "Current Land : " << currentLand << endl << "Number of Lands : " << numberOfLands;
		mouse.setString(s.str());
		target->draw(bound);
		target->draw(mouse);
	for (auto& i : buttons)
		i.second->render(target);
	}
}

void Editor::status::update(Vector2i* mousepos, int& currentLand,int grid,Vector2f maxsize, ELARABY::Vector<lands*>& Lands)
{
	Switch->update(*mousepos);
	if (Switch->isPressed() && !ispressing)
	{
		active ^= 1;
		ispressing = 1;
	}
	if (!Switch->isPressed())
		ispressing = 0;
	if (Switch->hoverb || Switch->isPressed())
		activeAll = 1;
	else if (active && bound.getGlobalBounds().contains(Vector2f(*mousepos)))
		activeAll = 1;
	else
		activeAll = 0;
	if (active)
	{
		for (auto& i : buttons)
		{
			i.second->update(*mousepos);
		}
		if (buttons["GoToNext"]->isPressed() && !ispressing1)
		{
			if (currentLand < Lands.getSize() - 1)
			{
				currentLand++;
				if (!Lands.at(currentLand)->isItLoaded)
				{
					Lands.at(currentLand)->loading1("./Land" + to_string(currentLand) + ".txt");
				}
			}
			ispressing1 = 1;
		}
		else if (buttons["GoToPrevious"]->isPressed() && !ispressing1)
		{
			ispressing1 = 1;
			if(currentLand>0)
			currentLand--;
		}
		else if (buttons["New"]->isPressed() && !ispressing1)
		{
			ispressing1 = 1;
			Lands.push_back(new lands(maxsize, 0, 0, 40, 5, 45, grid, "land0.txt", 1));
			Lands.at(Lands.size - 1)->isItLoaded = 1;
		}
		else if (!buttons["GoToNext"]->isPressed()&&!buttons["GoToPrevious"]->isPressed()&&!buttons["New"]->isPressed())
			ispressing1 = 0;
	
	}

}