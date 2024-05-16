#include "GameManager.h"
#include "PressF.h"
Vector2f final;
vector<Wood> collectedWoods;
vector<Stone_collectable> collectedStones;
vector<Iron_collectable>collectedIrons;
bool isitenter = 0;
bool GameManager::colli(RectangleShape& shape, RectangleShape& h,int x,int y)
{
	if (collisionDetector.isColliding(shape, h))
	{
		if (world->Lands[opened]->Land[x][y][1] != nullptr)
		{
			int i = world->Lands[opened]->Land[x][y][1]->type[3] - '0';
			if (i > 3 && i < 7 && Keyboard::isKeyPressed(Keyboard::X))
			{
				world->Lands[opened]->Land[x][y][1]->health--;
				if (world->Lands[opened]->Land[x][y][1]->health <= 0)
				{
					cout << 1 << endl;
					if (i == 4)
					{
						cout << "Tree destroyed, wood dropped!" << endl;
						Wood wood;
						wood.position = world->Lands[opened]->Land[x][y][0]->Tile.getPosition();
						wood.position.y += 50;
						wood.sprite.setPosition(wood.position.x, wood.position.y);
						wood.collected = false;
						wood.sprite.setTexture(woodTexture);
						collectedWoods.push_back(wood);
					}
					else if (i == 5)
					{
						cout << "Stone destroyed!";
						Stone_collectable dropped_stone;
						dropped_stone.position = world->Lands[opened]->Land[x][y][0]->Tile.getPosition();
						dropped_stone.position.y += 30;
						dropped_stone.sprite.setPosition(dropped_stone.position.x, dropped_stone.position.y);
						dropped_stone.collected = false;
						dropped_stone.sprite.setTexture(dropped_stone_texture);
						collectedStones.push_back(dropped_stone);

					}
					else
					{
						cout << "Iron destroyed!\n";
						Iron_collectable dropped_iron;
						dropped_iron.position = world->Lands[opened]->Land[x][y][0]->Tile.getPosition();
						dropped_iron.sprite.setPosition(dropped_iron.position.x, dropped_iron.position.y);
						dropped_iron.collected = false;
						dropped_iron.sprite.setTexture(dropped_iron_texture);
						collectedIrons.push_back(dropped_iron);
					}
					world->Lands[opened]->currentres--;
					world->Lands[opened]->empty.push_back({ x + 1,y + 1 });
					world->Lands[opened]->randoming(opened);
					delete world->Lands[opened]->Land[x][y][1];
					world->Lands[opened]->Land[x][y][1] = nullptr;
					world->Lands[opened]->collision[x + 1][y + 1] = 0;

				}

			}
			else if (i == 7)
			{
				GoToOtherLand(opened + 1);
				return 1;
			}
			else if (world->Lands[opened]->Land[x][y][1]->type=="#G10")
			{
				GoToOtherLand(opened - 1);
				cout << opened << endl;
				return 1;
			}
		}
		shape.setSize({ 0.2 * 64,0.2 * 64 });;
		shape.setPosition(final - Vector2f(0, -0.5 * 64));
		isitenter =	1;
		collisionDetector.setObjectBound(shape, h); collisionDetector.Movement(shape, h); 
	}
	return 0;
}
using namespace sf;
GameManager::GameManager(sf::RenderWindow* windoww, stack<states*>* GameManagerStates) :states(windoww, GameManagerStates)
{
	story = new Story(window);
	world->Lands.push_back(new lands(sf::Vector2f(world->maxSize), 0, 0, 50, 8,2, world->Gridsizef, "land0.txt", 1));
	world->Lands.at(0)->loading1("./Land0.txt");
	world->Lands.at(0)->emptyChecker();
	world->Lands.at(0)->randoming(opened);
	world->Lands[0]->pathFinderInitialization();
	pausinit();
	fonts();
	pre();
	camera.setSize(sf::Vector2f(window->getSize()));
	camera.setCenter(sf::Vector2f(((camera.getSize().x+200) / 2.f), (camera.getSize().y + 200) / 2.f));
	shape.setSize({ 0.2* 64,0.2* 64 });;
	shape.setPosition(800, 400);
	background.setSize(Vector2f(window->getSize()));
	checkCollision.setSize(Vector2f(world->Gridsizef, world->Gridsizef));
	background.setFillColor(sf::Color(0, 0, 255, 120));
}
void GameManager::CheckCollison(int x, int y,RectangleShape &h)
{

	
	if (world->Lands.at(world->currentLand)->collision[x+1][y+1])
	{
		checkCollision.setPosition(x * world->Gridsizef, y * world->Gridsizef);
		if (colli(h, checkCollision, x, y))return;
	}
	if (world->Lands.at(world->currentLand)->collision[x + 1][y + 2])
	{
		checkCollision.setPosition(x * world->Gridsizef, (y+1) * world->Gridsizef);
		if (colli(h, checkCollision, x, y + 1))return;
	}
	if (world->Lands.at(world->currentLand)->collision[x + 2][y + 1])
	{
		checkCollision.setPosition((x+1) * world->Gridsizef, y * world->Gridsizef);
		if (colli(h, checkCollision, x + 1, y))return;
	}
	if (world->Lands.at(world->currentLand)->collision[x + 2][y + 2])
	{
		checkCollision.setPosition((x+1) * world->Gridsizef, (y+1) * world->Gridsizef);
		if (colli(h, checkCollision, x + 1, y + 1))return;

	}
}
void GameManager::buttonUpdate() 
{
	for (auto& i : PauseM->buttons)
	{
		i.second->update(mousePositionWindow);
	}
	if (PauseM->buttons["Save"]->isPressed())
	{
		fstream fout;
		fout.open("saveGame.txt", ios::trunc | ios::in | ios::out);

		fout << story->hero.sprite.getPosition().x << ' ' << story->hero.sprite.getPosition().y << '\n'
			 << story->hero.stamina << ' ' << story->hero.health << ' ' << story->hero.walk << '\n'
			 << story->hero.run << ' ' << story->hero.damage << ' ' << story->hero.score << '\n'
			 << story->hero.hunger;
		

		fout << inventory.currentIron << ' ' << inventory.currentStones << ' ' << inventory.currentWood << '\n';


		for (int i = 0; i < 27; ++i) {
			fout << inv_items[i].weapon_or_mawared_or_nothing << '\n'
				 << inv_items[i].mawared.quantity << ' ' << inv_items[i].mawared.type << '\n'
				 << inv_items[i].weapons.health <<  ' ' << inv_items[i].weapons.type << '\n';
		}

		fout.close();
	}

	if (PauseM->buttons["continue"]->isPressed())
		Pause = false;
	if (PauseM->buttons["Mainmenu"]->isPressed())
	{
		quit = true;
	}
	if (PauseM->buttons["settings"]->isPressed())
	{
		Event ev;
		gameStates->push(new menuSettings(window, gameStates, ev));
	}
	if (PauseM->buttons["daily"]->isPressed())
	{
		gameStates->push(new checkIfDone(window, gameStates));
	}
}
void GameManager::pausinit()
{
	PauseM->List.setSize(sf::Vector2f(window->getSize().x * 0.2, window->getSize().y * 0.45));
	PauseM->List.setPosition(sf::Vector2f(window->getSize().x * 0.4, window->getSize().y * 0.325));
	PauseM->addbutton("Save", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 300 / 1080.0 * window->getSize().y);
	PauseM->addbutton("continue", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 400 / 1080.0 * window->getSize().y);
	PauseM->addbutton("Mainmenu", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 700 / 1080.0 * window->getSize().y);
	PauseM->addbutton("settings", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 600 / 1080.0 * window->getSize().y);
	PauseM->addbutton("daily", 280 * window->getSize().x / 1920, 60 * window->getSize().y / 1080, 820 / 1920.0 * window->getSize().x, 500 / 1080.0 * window->getSize().y);
}
void GameManager::CheckCollison1(int x, int y,int z)
{

	if (world->Lands.at(world->currentLand)->collision[max(min(x + 1,140),0)][max(min(y + 1,100),0)])
	{
		checkCollision.setPosition( max((min(x, 140) - 1),0) * world->Gridsizef, max((min(y + 1, 100) - 1),0) * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}
	if (world->Lands.at(world->currentLand)->collision[max(min(x + 1,140),0)][max(min(y + 2,100),0)])
	{
		checkCollision.setPosition(max(min(x + 1, 140)-1, 0) * world->Gridsizef, max((min(y + 2, 100)-1),0) * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}
	if (world->Lands.at(world->currentLand)->collision[max(min(x + 2,140),0)][max(min(y + 1,100),0)])
	{
		checkCollision.setPosition(max(min(x + 2, 140)-1, 0) * world->Gridsizef, max(min(y+1, 100)-1, 0) * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);

	}
	if (world->Lands.at(world->currentLand)->collision[max(min(x + 2,140),0)][max(min(y + 2,100),0)])
	{
		checkCollision.setPosition(max(min((x + 1),140)-1,0) * world->Gridsizef, max(min(y + 2, 100)-1, 0) * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}

	if (Keyboard::isKeyPressed(Keyboard::X))
	{
		world->Lands.at(world->currentLand)->cows.at(z)->hit(story->hero.sprite, story->hero.HitI);
		if (world->Lands.at(world->currentLand)->cows.at(z)->hp <= 0)
		{
			item_type addedmeat;
			addedmeat.food = rawmeat;
			addedmeat.weapon_or_mawared_or_nothing = 4;
			addedmeat.mawared.quantity = 1;
			addToInventory(addedmeat);
			world->Lands.at(world->currentLand)->cows.at(z)->meatSprite.setPosition(world->Lands.at(world->currentLand)->cows.at(z)->animalSprite.getPosition().x, world->Lands.at(world->currentLand)->cows.at(z)->animalSprite.getPosition().y);
			world->Lands.at(world->currentLand)->cows.erase(world->Lands.at(world->currentLand)->cows.begin() + z);
			world->Lands.at(world->currentLand)->cows.push_back(new MOBS);
			world->Lands.at(world->currentLand)->currentAnimal--;
			world->Lands.at(world->currentLand)->randoming(opened);
			inventory.meat += 1;
		}
	}
	world->Lands.at(world->currentLand)->cows.at(z)->mob(world->Lands.at(world->currentLand)->cows.at(z)->spriteSize);
}
void GameManager::end()
{
}
bool press3 = 0,onc=1;
void GameManager::render(sf::RenderTarget* target)
{
	if (backGroundmanagement==3)
	{
		if (onc)
		{
			story->hero.sprite.setPosition(window->getSize().x / 2, window->getSize().y / 2);
			onc = 0;
		}
		if (Pause)
		{
			target->setView(camera);
			world->render1(story->hero.sprite, target, story->game.enemiesch, opened);
			target->setView(target->getDefaultView());
			PauseM->render(target);
		}
		else
		{
			//cout << inventory.currentWood << endl;

			target->setView(camera);
			world->render1(story->hero.sprite, target, story->game.enemiesch, opened);
			int i = 0;
			for (auto wood : collectedWoods)
			{
				if (!wood.collected)
					target->draw(wood.sprite);
				else
				{
					collectedWoods.erase(collectedWoods.begin() + i);
				}
			}
			i = 0;
			for (auto dstone : collectedStones)
			{
				if (!dstone.collected)
					target->draw(dstone.sprite);
				else
				{
					collectedStones.erase(collectedStones.begin() + i);
				}
			}
			i = 0;
			for (auto& diron : collectedIrons)
			{

				if (!diron.collected)
				{
					diron.sprite.setScale(0.4f, 0.4f);
					target->draw(diron.sprite);
				}
				else
				{
					collectedIrons.erase(collectedIrons.begin() + i);
				}
				i++;
			}
			backGroundmanagement = story->Begin(DeltaTime, GameTime, *world->Lands.at(world->currentLand)->path);
			target->setView(target->getDefaultView());
			target->draw(world->miniMap);
			target->draw(world->mini);
			if (checkDistance(calcDistance(story->hero.sprite, world->Lands[opened]->blacksmithStore), story->hero.sprite, world->Lands[opened]->blacksmithStore))
			{
				if (last == 'f')
				{
					displayWeaponList();
				}
				PressFtoOpenWeapons();
			}
			if (checkDistance(calcDistance(story->hero.sprite, world->Lands[opened]->foodStore), story->hero.sprite, world->Lands[opened]->foodStore))
			{
				if (last == 'f')
				{
					displayFoodList();
				}
				PressFtoOpenfood();
			}
			displayWeaponHeroList();
			if ((Keyboard::isKeyPressed(Keyboard::I)) && !press3)
			{
				story->hero.isOpen ^= 1;
				press3 = 1;
			}
			else if (!(Keyboard::isKeyPressed(Keyboard::I)))
				press3 = 0;
			if (story->hero.isOpen)
			{
				drawInventory();
				last = 'i';
			}
			window->draw(story->game.dn.night);
			story->hero.ShowHealthBar();
			story->hero.ShowStaminaBar();
			story->hero.ShowHungerBar();
		}
	}
	else if (backGroundmanagement == 2)
	{
		target->clear(Color(0, 0, 30, 255));
		backGroundmanagement = story->Begin(DeltaTime, GameTime, *world->Lands.at(world->currentLand)->path);
	}
	else
	{
		backGroundmanagement = story->Begin(DeltaTime, GameTime, *world->Lands.at(world->currentLand)->path);
	}
}
bool once = 1;
void GameManager::update(const float& dt)
{
	if (backGroundmanagement == 3)
	{
		Updatebind(dt);
		if (Pause)
		{
			buttonUpdate();
			UpdateMousePos(&camera);
		}
		else
		{
			//cout << inventory.currentIron << " " << inventory.currentWood << endl;
			collectItems(story->hero.sprite, collectedWoods, collectedStones, collectedIrons);
			cout << 1 / dt << endl;
			for (size_t i = 0; i < world->Lands.at(world->currentLand)->currentAnimal; i++)
			{
				CheckCollison1((int)(world->Lands.at(world->currentLand)->cows.at(i)->animalSprite.getPosition().x / world->Gridsizef), (int)(world->Lands.at(world->currentLand)->cows.at(i)->animalSprite.getPosition().y / world->Gridsizef), i);
				world->Lands.at(world->currentLand)->cows.at(i)->deltaTime = dt;
			}
			Vector2f intial = story->hero.sprite.getPosition();
			story->hero.move();
			story->hero.dodge();
			story->hero.hit();
			//shape.setPosition(final - Vector2f(0, -0.5* 64));
			final = story->hero.sprite.getPosition();
			if (Keyboard::isKeyPressed(Keyboard::X))
			{

				shape.setSize({ 0.6 * 64,0.6 * 64 });
				shape.setPosition(final - Vector2f(0.2 * 64, -0.3 * 64));
			}
			else
			{
				shape.setSize({ 0.2 * 64,0.2 * 64 });
				shape.setPosition(final - Vector2f(0, -0.5 * 64));

			}
			if (click)
			{
				story->hero.hunger = min(5+story->hero.hunger,50);
				click = 0;
			}
			isitenter = 0;
			CheckCollison(shape.getPosition().x / world->Gridsizef, shape.getPosition().y / world->Gridsizef, shape);
			if(!isitenter)
			shape.setPosition(final - Vector2f(0, -0.5 * 64));
			story->hero.sprite.setPosition(shape.getPosition() + Vector2f(0, -0.5 * 64));
			Vector2f pos = story->hero.sprite.getPosition();
			if(pos.x>950 && pos.y<13050)
			camera.move(story->hero.sprite.getPosition().x - intial.x,0);
			if (story->hero.sprite.getPosition().y > 480)
				camera.move(0,story->hero.sprite.getPosition().y - intial.y);
			if (!story->game.dn.Day)
			{
				world->Lands[opened]->night = !story->game.dn.Day;
				world->Lands[opened]->spawning(story->game.Monsters, story->game.enemiesch, story->hero.sprite);
				world->Lands[opened]->path->initial(world->Lands[opened]->chasing(story->hero, *world->Lands[opened]->path, story->game.Monsters, story->game.enemiesch, story->hero.sprite), 2);
			}
			else
			{
				world->Lands[opened]->night = story->game.dn.Day;
				if (story->game.ThereIsMonsters())
				{
					world->Lands[opened]->clearEnemies(story->game.Monsters, story->game.enemiesch);
				}
			}
		}
	}
	else
	{
		story->hero.move();
		story->hero.dodge();
	}
}

void GameManager::Updatebind(const float& dt)
{
	endstate();
}

void GameManager::GoToOtherLand(int x)
{/*
	int w = 10000;
	while (window->isOpen())
	{
		window->draw(background);
		w--;
		if (!w)
			break;
	}*/
	if (story->game.ThereIsMonsters())
	{
		world->Lands[opened]->clearEnemies(story->game.Monsters,story->game.enemiesch);
		world->Lands[opened]->currentEnemies = 0;
	}
	world->Lands[opened]->currentAnimal = 0;
	if (x > opened)
	{
		opened++;
		Vector2f* arr;
		world->currentLand++;

		if (x >= world->Lands.size())
		{
			world->Lands.push_back(new lands(sf::Vector2f(world->maxSize), 0, 0, 50, 8, 2, world->Gridsizef, "land0.txt", 1));
			arr = world->Lands[x]->loading1("./Land" + to_string(x) + ".txt");
			world->Lands.at(x)->emptyChecker();
			world->Lands.at(x)->randoming(opened);
			world->Lands[x]->pathFinderInitialization();
		}
		else
		{
			//world->Lands.at(x)->randoming();
			arr = world->Lands[x]->arr;
			world->Lands.at(x)->randoming(opened);

		}
		world->Lands[x]->once = 1;

		story->hero.sprite.setPosition(window->getSize().x / 2, window->getSize().y / 2);
	}
	else
	{
		opened--;
		world->currentLand--;
		Vector2f* arr = world->Lands[x]->arr;
		world->Lands.at(x)->randoming(opened);
		world->Lands[x]->once = 1;
		story->hero.sprite.setPosition(window->getSize().x / 2, window->getSize().y / 2);
		cout << 1 << endl;
	}
}