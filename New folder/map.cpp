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
	stone.CreateEntity("./res/map.png", { 49 * 9+10,68,18,14 });
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
	for (int i = max(startX, 0); i <endX; i++)
	{
		for (int y = max(startY, 0); y < endY; y++)
		{
			if (Lands.at(currentLand)->Land[i][y][0] != nullptr)
			{
				Lands.at(currentLand)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
			}
		}
	}

	for (int i = max(startX, 0); i <endX; i++)
	{
		for (int y = max(startY, 0); y < endY; y++)
		{
			if (Lands.at(currentLand)->Land[i ][y][1] != nullptr)
			{
				if (Lands.at(currentLand)->Land[i][y][1]->type == "#G04")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, Tree.entity, sf::Vector2f(135.0 * Gridsizef / 60.0, 135.0 * Gridsizef / 60.0), i * Gridsizef - 35 * Gridsizef / 60.0, y * Gridsizef - 135.0 * Gridsizef / 60.0 + Gridsizef);

				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G05")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, stone.entity, sf::Vector2f(60.0 * Gridsizef / 60.0, 60 * Gridsizef / 60.0), i * Gridsizef, y * Gridsizef - 60.0 * Gridsizef / 60.0 + Gridsizef);
				}
				else
				{
					Lands.at(currentLand)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);

				}
			}
		}
	}

}
void Map::render1(sf::Sprite &player, sf::RenderTarget* target,int opened)
{
	float endx = min((int)(player.getPosition().x / Gridsizef + 18), (int)maxSize.x), endy = min((int)(player.getPosition().y / Gridsizef + 8), (int)maxSize.y);
	for (int i = max((int)(player.getPosition().x/Gridsizef-15), 0); i < endx; i++)
	{
		for (int y= max((int)(player.getPosition().y / Gridsizef - 10), 0); y < endy; y++)
		{
			if (Lands.at(opened)->Land[i][y][0] != nullptr)
			{
				Lands.at(opened)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
			}
			if (Lands.at(opened)->Land[i][y][1] != nullptr)
			{
				if(Lands.at(opened)->Land[i][y][1]->type == "#G03")
				Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
			}
		}
	}
	for (size_t i = 0; i < Lands.at(opened)->maxAnimal; i++)
	{
		target->draw(Lands.at(opened)->cows.at(i)->animalSprite);
	}
	int id = 0;
	for (int y = max((int)(player.getPosition().y/ Gridsizef - 8), 0); y < endy; y++)
	{
		for (int i = max((int)(player.getPosition().x / Gridsizef - 12), 0); i < endx; i++)
		{
			if (Lands.at(opened)->Land[i][y][1] != nullptr)
			{
				if (Lands.at(opened)->Land[i ][y][1]->type == "#G04")
				{
					Lands.at(opened)->Land[i][y][1]->render(target, Tree.entity, sf::Vector2f(135.0 * Gridsizef / 60.0, 180.0 * Gridsizef / 60.0), i * Gridsizef - 35 * Gridsizef / 60.0, y * Gridsizef - 190.0 * Gridsizef / 60.0 + Gridsizef);
				}
				else if (Lands.at(opened)->Land[i][y][1]->type == "#G05")
				{
					Lands.at(opened)->Land[i][y][1]->render(target, stone.entity, sf::Vector2f(60.0 * Gridsizef / 60.0, 60 * Gridsizef / 60.0), i * Gridsizef, y * Gridsizef - 60.0 * Gridsizef / 60.0 + Gridsizef);
				}
				else if (Lands.at(opened)->Land[i][y][1]->type == "#G07")
				{
					Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);

				}
			}
		}
		if (y == (int)((player.getPosition().y - player.getOrigin().y)/ Gridsizef))
		{
			target->draw(player);
		}
	}

}
