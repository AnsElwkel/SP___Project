#pragma once
#include "includes.h"
#include"lib.h"
#include "tile.h"
#include"entities.h"
#include"MOBS.h"
#include "Enemies.h"
using namespace std;
struct lands
{
	int cost,id,maxEnemy,currentEnemy,currentres,maxres,maxEnemies,currentEnemies=0,maxAnimal,currentAnimal,count=0;
	float gridSize;
	bool isItLoaded=0,night;
	sf::Vector2f maxSize,arr[2];
	bool once = 1;
	RenderTexture* texture = nullptr,*texture2=nullptr;
	string name,type;
	Sprite* monsterSpriteArray = nullptr;
	ELARABY::pathFinder *path;
	vector<pair<int ,int>>empty;
	ELARABY::Vector < ELARABY::Vector < ELARABY::Vector <tile* >> > Land;
	ELARABY::Vector<ELARABY::Vector<bool>>collision;
	vector<MOBS*>cows;
	RectangleShape foodStore, blacksmithStore;
	lands();
	lands(sf::Vector2f maxSize, int cost, int id, int maxRes, int maxAnimal, int MaxObject, int gridSize, std::string filename, bool what);
	void story();
	void pathFinderInitialization();
	void randoming(int x);
	void emptyChecker();
	sf::Sprite* spawning(enemies Monsters[], bool enemiesch[], sf::Sprite);
	void EnemiesRender(enemies Monsters[], bool enemiesch[], RenderTarget* target);
	sf::Sprite* chasing(character& x,ELARABY::pathFinder& path,enemies Monsters[], bool enemiesch[], sf::Sprite);
	void clearEnemies(enemies Monsters[], bool enemiesch[]);
	void rendering(sf::RenderTarget* target, sf::Vector2f playerPosition, sf::RectangleShape& player);
	sf::Vector2f* loading1(string filename);
	void saving(std::string filename);
};

