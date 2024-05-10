#include "Map.h"

Map::Map()
{

}

Texture *t;
Map::Map(float Gridsize, unsigned width, unsigned height)
{
	Gridsizef = Gridsize;
	maxSize.x = width;
	maxSize.y = height;
	layer = 2;
	t = new Texture;
	count = 0;
	t->loadFromFile("./res/border.png");
	mini.setTexture(*t);
	mini.setScale(2.1, 2.1);
	mini.setPosition(1640, 30);
	miniMap.setPosition(1640, 30);
	miniMap.setRadius(128);
	Tree.CreateEntity("./res/map.png", { 49 * 8 + 20,147,70,100 });
	stone.CreateEntity("./res/ores.png", { 17,0,16,16 });
	blackSmith.CreateEntity("./res/house5.png", { 0,0,320,287 });
	iron.CreateEntity("./res/ores.png", { 36,0,16,16 });
	kitchen.CreateEntity("./res/hou.png", { 0,0,76,90});
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
		file << Lands.size();
	}
	file.close();
	for (size_t i = 0; i < Lands.size(); i++)
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
	/*for (int i = max(startX, 0); i <endX; i++)
	{
		for (int y = max(startY, 0); y < endY; y++)
		{
			if (Lands.at(currentLand)->Land[i][y][0] != nullptr)
			{
				Lands.at(currentLand)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
			}
		}
	}*/
	if (Lands[currentLand]->once)
	{
		Lands[currentLand]->texture->clear();
		for (int i = 0; i < 140; i++)
		{
			for (int y = 0; y < 100; y++)
			{
				if (Lands.at(currentLand)->Land[i][y][0] != nullptr)
				{
					Lands.at(currentLand)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
					Lands[currentLand]->texture->draw(Lands.at(currentLand)->Land[i][y][0]->Tile);
				}
			}
		}
		Lands[currentLand]->texture->display();;
		Lands[currentLand]->once = 0;
	}
	else
	{
		sprite.setTexture(Lands[currentLand]->texture->getTexture());
		sprite.setTextureRect(IntRect(0, 0, 14000, 10000));
		target->draw(sprite);
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
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G06")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, iron.entity, sf::Vector2f(Gridsizef ,  Gridsizef ), i * Gridsizef, y * Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G08")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, kitchen.entity, sf::Vector2f(Gridsizef, 2*Gridsizef), i * Gridsizef, y * Gridsizef-Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G09")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, blackSmith.entity, sf::Vector2f(Gridsizef ,2*Gridsizef), i * Gridsizef, y * Gridsizef-Gridsizef);
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
		endy = min((int)(player.getPosition().y / Gridsizef + 9), (int)maxSize.y);
	if (!max((int)(player.getPosition().x / Gridsizef - 11), 0))
		endx += 11 - player.getPosition().x / Gridsizef;
	if (!max((int)(player.getPosition().y / Gridsizef - 7), 0))
		endy += 7 - player.getPosition().y / Gridsizef;
	if (Lands[opened]->once)
	{
		Lands[opened]->texture->clear();
		Lands[opened]->texture2->clear();
		for (int i = 0; i < 140; i++)
		{
			for (int y = 0; y < 100; y++)
			{
				if (Lands.at(opened)->Land[i][y][0] != nullptr)
				{
					Lands.at(opened)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
					Lands[opened]->texture->draw(Lands.at(opened)->Land[i][y][0]->Tile);
					Lands[opened]->texture2->draw(Lands.at(opened)->Land[i][y][0]->Tile);
				}
				if (Lands.at(opened)->Land[i][y][1] != nullptr)
				{
					if (Lands.at(opened)->Land[i][y][1]->type == "#G03")
					{
						Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
						Lands[opened]->texture->draw(Lands.at(opened)->Land[i][y][1]->Tile);
						Lands[opened]->texture2->draw(Lands.at(opened)->Land[i][y][0]->Tile);

					}
				}
			}
		}
		for (int y =0; y < 100; y++)
		{
			for (int i = 0; i < 140; i++)
			{
				if (Lands.at(opened)->Land[i][y][1] != nullptr)
				{
					if (Lands.at(currentLand)->Land[i][y][1]->type == "#G08")
					{

						Lands.at(currentLand)->Land[i][y][1]->render(target, kitchen.entity, sf::Vector2f(Gridsizef, 2.5 * Gridsizef), i * Gridsizef, y * Gridsizef - 1.5 * Gridsizef);
						kitchen.entity.setSize(sf::Vector2f(Gridsizef, 2.5 * Gridsizef));
						kitchen.entity.setPosition(i * Gridsizef, y * Gridsizef - 1.5 * Gridsizef);
						Lands[currentLand]->texture2->draw(kitchen.entity);
					}
					else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G09")
					{
						Lands.at(currentLand)->Land[i][y][1]->render(target, blackSmith.entity, sf::Vector2f(Gridsizef, 2.5 * Gridsizef), i * Gridsizef, y * Gridsizef - 1.5 * Gridsizef);
						blackSmith.entity.setSize(sf::Vector2f(Gridsizef, 2.5 * Gridsizef));
						blackSmith.entity.setPosition(i * Gridsizef, y * Gridsizef - 1.5 * Gridsizef);
						Lands[currentLand]->texture2->draw(blackSmith.entity);
					}
					else if (Lands.at(opened)->Land[i][y][1]->type == "#G07" || Lands.at(opened)->Land[i][y][1]->type == "#G10")
					{
						Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
						Lands[currentLand]->texture2->draw(Lands.at(opened)->Land[i][y][1]->Tile);
					}

				}
			}
		}

		miniMap.setTexture(&Lands[opened]->texture2->getTexture());
		Lands[opened]->texture->display();
		Lands[opened]->texture2->display();
		Lands[opened]->once = 0;
	}
	else
	{
		sprite.setTexture(Lands[opened]->texture->getTexture());
		sprite.setTextureRect(IntRect(0, 0, 14000, 10000));
		target->draw(sprite);
	}
	for (size_t i = 0; i < Lands.at(opened)->maxAnimal; i++)
	{
		target->draw(Lands.at(opened)->cows.at(i)->animalSprite);
	}
	for (int y = max((int)(player.getPosition().y/ Gridsizef - 7 - (maxSize.y - endx > 7) ? 0 : 7 - maxSize.y - endy), 0); y < endy; y++)
	{
		for (int i = max((int)(player.getPosition().x / Gridsizef - 10-(maxSize.x - endx > 11) ? 0 : 12 - maxSize.x - endx), 0); i < endx; i++)
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
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G06")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, iron.entity, sf::Vector2f(0.75*Gridsizef,0.75*Gridsizef), i * Gridsizef, y * Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G08")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, kitchen.entity, sf::Vector2f(Gridsizef, 2.5 * Gridsizef), i * Gridsizef, y * Gridsizef - 1.5*Gridsizef);
				}
				else if (Lands.at(currentLand)->Land[i][y][1]->type == "#G09")
				{
					Lands.at(currentLand)->Land[i][y][1]->render(target, blackSmith.entity, sf::Vector2f(Gridsizef, 2.5 * Gridsizef), i * Gridsizef, y * Gridsizef - 1.5*Gridsizef);
				}
				else if (Lands.at(opened)->Land[i][y][1]->type == "#G07"|| Lands.at(opened)->Land[i][y][1]->type == "#G10")
				{
					Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
				}
				
			}
		}
		if(Lands[currentLand]->night)
		for (int i = 0; i < Lands[currentLand]->maxEnemies; i++)
		{
			if (enemiesch[i] == 1&& y == (int)((Lands[currentLand]->monsterSpriteArray[i].getPosition().y - Lands[currentLand]->monsterSpriteArray[i].getOrigin().y) / Gridsizef))
			{
				target->draw(Lands[currentLand]->monsterSpriteArray[i]);
			}
		}
		if (y == (int)((player.getPosition().y - player.getOrigin().y)/ Gridsizef))
		{
			target->draw(player);
		}
	}
	miniMap.setTextureRect(IntRect(((int)player.getPosition().x / Gridsizef - 20)* Gridsizef, ((int)player.getPosition().y / Gridsizef - 20)* Gridsizef, 4000, 4000));
}
//Lands[opened]->texture->clear();
//for (int i = max((int)(player.getPosition().x / Gridsizef - 10 - (maxSize.x - endx > 11) ? 0 : 12 - maxSize.x - endx), 0); i < endx; i++)
//{
//	for (int y = max((int)(player.getPosition().y / Gridsizef - 7 - (maxSize.y - endx > 7) ? 0 : 7 - maxSize.y - endy), 0); y < endy; y++)
//	{
//		if (Lands.at(opened)->Land[i][y][0] != nullptr)
//		{
//			Lands.at(opened)->Land[i][y][0]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
//			Lands[opened]->texture->draw(Lands.at(opened)->Land[i][y][0]->Tile);
//		}
//		if (Lands.at(opened)->Land[i][y][1] != nullptr)
//		{
//			if (Lands.at(opened)->Land[i][y][1]->type == "#G03")
//			{
//				Lands.at(opened)->Land[i][y][1]->render1(target, { Gridsizef,Gridsizef }, i * Gridsizef, y * Gridsizef);
//				Lands[opened]->texture->draw(Lands.at(opened)->Land[i][y][1]->Tile);
//			}
//		}
//	}
//}
//Lands[opened]->texture->display();
//Lands[opened]->once = 0;