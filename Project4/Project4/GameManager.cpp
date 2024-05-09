#include "GameManager.h"
#define colli(shape,h) if (collisionDetector.isColliding(shape,h)){collisionDetector.setObjectBound(shape, h);collisionDetector.Movement(shape, h); }
using namespace sf;
GameManager::GameManager(sf::RenderWindow* windoww, stack<states*>* GameManagerStates) :states(windoww, GameManagerStates)
{
	story = new Story(window);
	world->Lands.push_back(new lands(sf::Vector2f(world->maxSize), 0, 0, 50, 10,5, world->Gridsizef, "land0.txt", 1));
	world->Lands.at(0)->loading1("./Land0.txt");
	world->Lands.at(0)->emptyChecker();
	world->Lands.at(0)->randoming();
	world->Lands[0]->pathFinderInitialization();
	camera.setSize(sf::Vector2f(window->getSize()));
	camera.setCenter(sf::Vector2f(camera.getSize() / 2.f));
	shape.setSize({ 0.2* 64,0.2* 64 });;
	shape.setPosition(800, 400);
	background.setSize(Vector2f(window->getSize()));
	checkCollision.setSize(Vector2f(world->Gridsizef, world->Gridsizef));
	background.setFillColor(sf::Color(0, 0, 255, 120));
	//world->Lands.at(world->currentLand)->cows.at(0)->animalTexture.loadFromFile("./res/cow_walk.png");
	//world->Lands.at(world->currentLand)->cows.at(0)->animalSprite.setTexture(world->Lands.at(world->currentLand)->cows.at(0)->animalTexture);//cow[0] is a normal cow
	//world->Lands.at(world->currentLand)->cows.at(0)->animalSprite.setPosition(400, 400);
}
void GameManager::CheckCollison(int x, int y,RectangleShape &h)
{

	if (world->Lands.at(world->currentLand)->collision[x + 1][y + 1])
	{
		checkCollision.setPosition(x * world->Gridsizef, y * world->Gridsizef);
		colli(h, checkCollision)
	}
	if (world->Lands.at(world->currentLand)->collision[x + 1][y + 2])
	{
		checkCollision.setPosition(x * world->Gridsizef, (y+1) * world->Gridsizef);
		colli(h, checkCollision)
	}
	if (world->Lands.at(world->currentLand)->collision[x + 2][y + 1])
	{
		checkCollision.setPosition((x+1) * world->Gridsizef, y * world->Gridsizef);
		colli(h, checkCollision)
	}
	if (world->Lands.at(world->currentLand)->collision[x + 2][y + 2])
	{
		checkCollision.setPosition((x+1) * world->Gridsizef, (y+1) * world->Gridsizef);
		colli(h,checkCollision)
	}
	if (world->Lands.at(world->currentLand)->collision[x][y + 1])
	{
		checkCollision.setPosition((x - 1) * world->Gridsizef, (y) * world->Gridsizef);
		colli(h, checkCollision)
	}
	if (world->Lands.at(world->currentLand)->collision[x][y + 2])
	{
		checkCollision.setPosition((x - 1) * world->Gridsizef, (y + 1) * world->Gridsizef); 
		colli(h, checkCollision)
	}
}
void GameManager::CheckCollison1(int x, int y,int z)
{

	if (world->Lands.at(world->currentLand)->collision[x + 1][y + 1])
	{
		checkCollision.setPosition(x * world->Gridsizef, y * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}
	if (world->Lands.at(world->currentLand)->collision[x + 1][y + 2])
	{
		checkCollision.setPosition(x * world->Gridsizef, (y + 1) * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}
	if (world->Lands.at(world->currentLand)->collision[x + 2][y + 1])
	{
		checkCollision.setPosition((x + 1) * world->Gridsizef, y * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);

	}
	if (world->Lands.at(world->currentLand)->collision[x + 2][y + 2])
	{
		checkCollision.setPosition((x + 1) * world->Gridsizef, (y + 1) * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}
	if (world->Lands.at(world->currentLand)->collision[x][y + 1])
	{
		checkCollision.setPosition((x - 1) * world->Gridsizef, (y)*world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}
	if (world->Lands.at(world->currentLand)->collision[x][y + 2])
	{
		checkCollision.setPosition((x - 1) * world->Gridsizef, (y + 1) * world->Gridsizef);
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(checkCollision);
	}
	if (Keyboard::isKeyPressed(Keyboard::X))
	{
		world->Lands.at(world->currentLand)->cows.at(z)->randomlyMove(shape);
	}
	world->Lands.at(world->currentLand)->cows.at(z)->mob(world->Lands.at(world->currentLand)->cows.at(z)->spriteSize);
}
void GameManager::end()
{
}

void GameManager::render(sf::RenderTarget* target)
{
	if (backGroundmanagement==3)
	{
		target->setView(camera);
		world->render1(story->hero.sprite,target,story->game.enemiesch, opened);
		backGroundmanagement = story->Begin(DeltaTime, GameTime,*world->Lands.at(world->currentLand)->path);
		//target->draw(shape);
		story->hero.hit();
		//world->Lands[opened]->spawning(story->game.Monsters, story->game.enemiesch, story->hero.sprite);
		target->setView(target->getDefaultView());
		window->draw(story->game.dn.night);
		story->hero.ShowHealthBar();
		story->hero.ShowStaminaBar();
		story->hero.ShowHungerBar();
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

void GameManager::update(const float& dt)
{
	if (backGroundmanagement == 3)
	{
		Updatebind(dt);
		UpdateMousePos(&camera);
		cout << 1 / dt << endl;
		for (size_t i = 0; i < world->Lands.at(world->currentLand)->maxAnimal; i++)
		{
			CheckCollison1((int)(world->Lands.at(world->currentLand)->cows.at(i)->animalSprite.getPosition().x / world->Gridsizef), (int)(world->Lands.at(world->currentLand)->cows.at(i)->animalSprite.getPosition().y / world->Gridsizef), i);
		}
		Vector2f intial = story->hero.sprite.getPosition();
		story->hero.move();
		story->hero.dodge();
		Vector2f final = story->hero.sprite.getPosition();
		shape.setPosition(final- Vector2f(0, -0.7 * 64));
		CheckCollison(shape.getPosition().x / world->Gridsizef, shape.getPosition().y / world->Gridsizef, shape);
		story->hero.sprite.setPosition(shape.getPosition()+ Vector2f(0, -0.7 * 64));
		camera.move(story->hero.sprite.getPosition() - intial);
		if (!story->game.dn.Day)
		{
			world->Lands[opened]->night = !story->game.dn.Day;
			world->Lands[opened]->spawning(story->game.Monsters, story->game.enemiesch, story->hero.sprite);
			world->Lands[opened]->path->initial(world->Lands[opened]->chasing(story->hero, *world->Lands[opened]->path, story->game.Monsters, story->game.enemiesch, story->hero.sprite), 5);
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

