#include "Map.h"

Map::Map()
{

}

Map::Map(float Gridsize, unsigned width, unsigned height)
{
	Gridsizef = Gridsize;
	maxSize.x = width;
	maxSize.y = height;
	layer = 2;
	count = 0;
	Tree.CreateEntity("./res/map.png", { 49 * 8 + 20,147,70,100 });
	stone.CreateEntity("./res/ores.png", { 17,0,16,16 });
	blackSmith.CreateEntity("./res/house5.png", { 0,0,320,287 });
	iron.CreateEntity("./res/ores.png", { 36,0,16,16 });
	kitchen.CreateEntity("./res/hou.png", { 0,0,76,90 });
}

Map::~Map()
{

}
void Map::saveTofile()
{
	fstream file;
	file.open("main.txt", ios::out);
	if (file.is_open())
	{
		file << Lands.getSize();
	}
	file.close();
	for (size_t i = 0; i < Lands.getSize(); i++)
	{
		Lands.at(i)->saving("Land" + to_string(i) + ".txt");
	}
}

void Map::LoadFromFile(bool firstTime)
{
	if (!firstTime)
	{
		fstream file;
		file.open("main.txt", ios::in);
		if (file.is_open())
		{
			int x;
			file >> x;
			for (int i = 1; i < x; i++)
			{
				Lands.push_back(new lands);
			}

		}
		Lands.at(currentLand)->loading1("./Land" + to_string(currentLand) + ".txt");
		Lands.at(0)->isItLoaded = 1;
	}

}
void Map::render(int startX, int width, int startY, int height, sf::RenderTarget* target)
{
	int endX = startX + width, endY = startY + height;
	endX = min(max(endX, 0), (int)maxSize.x);
	endY = min(max(endY, 0), (int)maxSize.y);
	for (int i = max(startX, 0); i < endX; i++)
	{
		for (int y = max(startY, 0); y < endY; y++)
		{
			if (Lands.at(currentLand)->Land[i][y][0] != nullptr)
			{
				Lands.at(currentLand)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
			}
		}
	}

	for (int i = max(startX, 0); i < endX; i++)
	{
		for (int y = max(startY, 0); y < endY; y++)
		{
			if (Lands.at(currentLand)->Land[i][y][1] != nullptr)
			{
				if (Lands.at(currentLand)->Land[i][y][1]->type == "#G04")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, Tree.entity, sf::Vector2f(135.0 * Gridsizef / 60.0, 135.0 * Gridsizef / 60.0), i * Gridsizef - 35 * Gridsizef / 60.0, y * Gridsizef - 135.0 * Gridsizef / 60.0 + Gridsizef);

				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G05")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, stone.entity, sf::Vector2f(60.0 * Gridsizef / 60.0, 60 * Gridsizef / 60.0), i * Gridsizef, y * Gridsizef - 60.0 * Gridsizef / 60.0 + Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G06")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, iron.entity, sf::Vector2f(Gridsizef, Gridsizef), i * Gridsizef, y * Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G08")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, kitchen.entity, sf::Vector2f(Gridsizef, 2 * Gridsizef), i * Gridsizef, y * Gridsizef - Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G09")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, blackSmith.entity, sf::Vector2f(Gridsizef, 2 * Gridsizef), i * Gridsizef, y * Gridsizef - Gridsizef);
				}
				else
				{
					Lands.at(currentLand)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);

				}
			}
		}
	}

}
void Map::render1(sf::Sprite& player, sf::RenderTarget* target, bool enemiesch[], int opened)
{
	float endx = min((int)(player.getPosition().x / Gridsizef + 12), (int)maxSize.x),
		endy = min((int)(player.getPosition().y / Gridsizef + 8), (int)maxSize.y);
	if (!max((int)(player.getPosition().x / Gridsizef - 11), 0))
		endx += 11 - player.getPosition().x / Gridsizef;
	if (!max((int)(player.getPosition().y / Gridsizef - 7), 0))
		endy += 7 - player.getPosition().y / Gridsizef;
	for (int i = max((int)(player.getPosition().x / Gridsizef - 10 - (maxSize.x - endx > 11) ? 0 : 12 - maxSize.x - endx), 0); i < endx; i++)
	{
		for (int y = max((int)(player.getPosition().y / Gridsizef - 7 - (maxSize.y - endx > 7) ? 0 : 7 - maxSize.y - endy), 0); y < endy; y++)
		{
			if (Lands.at(opened)->Land[i][y][0] != nullptr)
			{
				Lands.at(opened)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
			}
			if (Lands.at(opened)->Land[i][y][1] != nullptr)
			{
				if (Lands.at(opened)->Land[i][y][1]->type == "#G03")
					Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
			}
		}
	}
	for (size_t i = 0; i < Lands.at(opened)->maxAnimal; i++)
	{
		target->draw(Lands.at(opened)->cows.at(i)->animalSprite);
	}
	for (int y = max((int)(player.getPosition().y / Gridsizef - 7 - (maxSize.y - endx > 7) ? 0 : 7 - maxSize.y - endy), 0); y < endy; y++)
	{
		for (int i = max((int)(player.getPosition().x / Gridsizef - 10 - (maxSize.x - endx > 11) ? 0 : 12 - maxSize.x - endx), 0); i < endx; i++)
		{
			if (Lands.at(opened)->Land[i][y][1] != nullptr)
			{
				if (Lands.at(opened)->Land[i][y][1]->type == "#G04")
				{
					Lands.at(opened)->Land[i][y][1]->render(target, Tree.entity, sf::Vector2f(135.0 * Gridsizef / 60.0, 180.0 * Gridsizef / 60.0), i * Gridsizef - 35 * Gridsizef / 60.0, y * Gridsizef - 190.0 * Gridsizef / 60.0 + Gridsizef);
				}
				else if (Lands.at(opened)->Land[i][y][1]->type == "#G05")
				{
					Lands.at(opened)->Land[i][y][1]->render(target, stone.entity, sf::Vector2f(60.0 * Gridsizef / 60.0, 60 * Gridsizef / 60.0), i * Gridsizef, y * Gridsizef - 60.0 * Gridsizef / 60.0 + Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G06")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, iron.entity, sf::Vector2f(0.75 * Gridsizef, 0.75 * Gridsizef), i * Gridsizef, y * Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G08")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, kitchen.entity, sf::Vector2f(Gridsizef, 2.5 * Gridsizef), i * Gridsizef, y * Gridsizef - 1.5 * Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G09")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, blackSmith.entity, sf::Vector2f(Gridsizef, 2.5 * Gridsizef), i * Gridsizef, y * Gridsizef - 1.5 * Gridsizef);
				}
				else if (Lands.at(opened)->Land[i][y][1]->type == "#G07")
				{
					Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
				}

			}
		}
		if (Lands[currentLand]->night)
			for (int i = 0; i < Lands[currentLand]->maxEnemies; i++)
			{
				if (enemiesch[i] == 1 && y == (int)((Lands[currentLand]->monsterSpriteArray[i].getPosition().y - Lands[currentLand]->monsterSpriteArray[i].getOrigin().y) / Gridsizef))
				{
					target->draw(Lands[currentLand]->monsterSpriteArray[i]);
				}
			}
		if (y == (int)((player.getPosition().y - player.getOrigin().y) / Gridsizef))
		{
			target->draw(player);
		}



	}

}
