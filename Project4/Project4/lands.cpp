#include "lands.h"
lands::lands()
{

}
lands::lands(sf::Vector2f maxSize,int cost, int id, int maxRes, int maxAnimal, int maxEnemies,int gridSize,std::string filename,bool what)
{
	this->cost = cost;
	this->id = id;
	name = filename;
	this->maxSize = maxSize;
	this->gridSize = gridSize;
	this->maxAnimal = maxAnimal;
	currentAnimal = 0;
	night = 0;
	this->maxres = maxRes;
	currentres = 0;
	this->maxEnemies = maxEnemies;
	monsterSpriteArray = new Sprite[maxEnemies];
	if (what)
	{
		Land.resize(maxSize.x);
		for (int x = 0; x < maxSize.x; x++)
		{
			Land[x].resize(maxSize.y);
			for (int y = 0; y < maxSize.y; y++)
			{
				Land[x][y].resize(2);
				Land[x][y][0] = NULL;
				Land[x][y][1] = NULL;
			}
		}
	}
	collision.resize(maxSize.x + 2);
	for (int x = 0; x < maxSize.x + 2; x++)
	{
		collision[x].resize(maxSize.y + 2);
		for (size_t j = 0; j < maxSize.y+2; j++)
		{
			collision[x][j] = 1;
		}
	}
	cows.resize(maxAnimal);
	for (size_t i = 0; i < maxAnimal; i++)
	{
		cows.at(i) = new MOBS;
	}
}
void lands::saving(std::string filename)
{
	fstream file;
	file.open(filename, ios::out);
	if (file.is_open())
	{
		file << maxSize.x << " " << maxSize.y << endl << gridSize << endl << count << endl;
		for (int x = 0; x < maxSize.x; x++)
		{
			for (int y = 0; y < maxSize.y; y++)
			{
				for (int z = 0; z < 2; z++)
				{
					if (Land[x][y][z] != nullptr)
					{
						file << x << " " << y << " " << z << " " << Land[x][y][z]->type << " " << (long long)Land[x][y][z]->Tile.getPosition().x << " "
							<< (long long)Land[x][y][z]->Tile.getPosition().y<<" "<< Land[x][y][z]->what.width<<" " << Land[x][y][z]->what.height<<" "<< Land[x][y][z]->what.left<<" "<< Land[x][y][z]->what.top <<" "<< Land[x][y][z]->whichTexture << endl;
					}
				}
			}
		}
	}
	file.close();
}

void lands::story()
{

}

void lands::pathFinderInitialization()
{
	path = new ELARABY::pathFinder(maxSize.x, maxSize.y);
	for (int x = 0; x < maxSize.x; x++)
	{
		for (int y = 0; y < maxSize.y; y++)
		{
			path->arr[x][y].position=Vector2f(x* 100, y* 100);
			path->arr[x][y].block = collision[x + 1][y + 1];
		}
	}
}


void lands::emptyChecker()
{

	for (size_t i = 0; i < maxSize.x; i++)
	{
		for (int j = 0; j < maxSize.y; j++)
		{
			if (!collision[i][j])
			{
				empty.push_back({i,j});
			}
		}
	}
}
Sprite* lands::spawning(enemies Monsters[],bool enemiesch[], sf::Sprite)
{
	for (int i = 0; i < maxEnemies; i++)
	{
		if (enemiesch[i] == 0)
		{
			int x = rand() % empty.size;
			cout << "Spawn " << i << endl;
			enemiesch[i] = 1;
			if (x)
				Monsters[i].set(empty[x].first*gridSize,empty[x].second*gridSize, 50, "Skelaton", "", "", 1);
			else
				Monsters[i].set(empty[x].first * gridSize, empty[x].second * gridSize, 50, "Zombie", "", "", 1);
			monsterSpriteArray[i] = Monsters[i].sprite;
		}
	}
	return monsterSpriteArray;
}
void lands::EnemiesRender(enemies Monsters[], bool enemiesch[],RenderTarget* target)
{
	
}
sf::Sprite* lands::chasing(character& x, ELARABY::pathFinder& path, enemies Monsters[], bool enemiesch[], sf::Sprite)
{
	for (int i = 0; i < maxEnemies; i++)
	{
		if (enemiesch[i] == 1)
		{
			if (Monsters[i].IsAlive && Monsters[i].health > 0)
			{
				Monsters[i].ChaceAndHit(x, 0, path,i);
				monsterSpriteArray[i] = Monsters[i].sprite;
			}
			else if (Monsters[i].IsAlive)
			{
				Monsters[i].die("");
				monsterSpriteArray[i] = Monsters[i].sprite;
			}
			else if (!Monsters[i].IsAlive)
			{
				x.score++;
				enemiesch[i] = 0;
			}
		}
	}
	return monsterSpriteArray;
}
void lands::clearEnemies(enemies Monsters[], bool enemiesch[])
{
	for (int i = 0; i < maxEnemies; i++)
	{
		if (enemiesch[i] == 1)
		{
			if (Monsters[i].IsAlive)
			{
				Monsters[i].die("");
				monsterSpriteArray[i] = Monsters[i].sprite;
			}
			else
			{
				enemiesch[i] = 0;
			}
		}
	}
}
void lands::randoming()
{

	while (currentAnimal < maxAnimal)
	{
		int x = rand() % empty.size;
		cows.at(currentAnimal)->animalTexture.loadFromFile("./res/cow_walk.png");
		cows.at(currentAnimal)->animalSprite.setTexture(cows.at(currentAnimal)->animalTexture);//cow[0] is a normal cow
		cows.at(currentAnimal)->animalSprite.setPosition(empty[x].first * gridSize, empty[x].second * gridSize);
		currentAnimal++;
	}
	Entity Tree;
	Tree.CreateEntity("./res/map.png", { 49 * 8 + 20,147,70,100 });
	while (currentres < maxres)
	{
		int x = rand() % empty.size;
		Land[empty[x].first - 1][empty[x].second - 1][1] = new tile(empty[x].first - 1, empty[x].second - 1, gridSize, Tree.tex, Tree.tr, "#G04");
		Land[empty[x].first-1][empty[x].second-1][1]->id=currentres;
		currentres++;
		collision[empty[x].first][empty[x].second] = 1;
		empty.erase(empty.begin() + x);
	}
}

void lands::rendering(sf::RenderTarget* target, sf::Vector2f playerPosition, sf::RectangleShape& player)
{
	//sf::Vector2i posi = sf::Vector2i(playerPosition.x / gridSize, playerPosition.y / gridSize);
}

void lands::loading1(string filename)
{
	int i, j, k, left, top, left1, top1, width, height, elem;
	sf::Texture* tex[3] = { new sf::Texture,new sf::Texture,new sf::Texture };
	tex[0]->loadFromFile("./res/map.png");
	tex[1]->loadFromFile("./res/frozenlake.png");
	tex[2]->loadFromFile("./res/dungeonex.png");
	fstream load;
	load.open(filename);
	if (load.is_open())
	{
		load >> maxSize.x >> maxSize.y;
		load >> gridSize;
		load >> count;
		Land.resize(maxSize.x);
		for (int x = 0; x < maxSize.x; x++)
		{
			Land[x].resize(maxSize.y);
			for (int y = 0; y < maxSize.y; y++)
			{
				Land[x][y].resize(2);
				Land[x][y][0] = NULL;
				Land[x][y][1] = NULL;
			}
		}
		collision.resize(maxSize.x + 2);
		for (int x = 0; x < maxSize.x + 2; x++)
		{
			collision[x].resize(maxSize.y + 2);
			for (size_t j = 0; j < maxSize.y + 2; j++)
			{
				collision[x][j] = 1;
			}
		}
		path = new ELARABY::pathFinder(maxSize.x, maxSize.y);
		for (int x = 0; x < count; x++)
		{
			load >> i >> j >> k >> type >> left >> top >> width >> height >> left1 >> top1>>elem;
			Land[i][j][k] = new tile(left, top, gridSize, tex[elem], {left1,top1,width,height}, type);
			Land[i][j][k]->whichTexture = elem;
			if (!k)
			{
				if (type != "#G02")
				{
					collision[i + 1][j + 1] = 0;
				}
			}
			else
			{
				
				if (type != "#G03")
					collision[i + 1][j + 1] = 1;
				else
					collision[i + 1][j + 1] = 0;
			}
		}

	}
	else
		throw("Error!!! Failed to save");
	load.close();
}
