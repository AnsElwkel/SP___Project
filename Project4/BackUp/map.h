#pragma once
#include "includes.h";
#include"tile.h"
#include"lib.h"
#include"entities.h"
#include"lands.h"
using namespace std;
struct Map
{
	float Gridsizef;
	int count, count1,currentLand=0;
	unsigned gridSize, layer;
	sf::Vector2u maxSize;
	sf::Texture TileSet;
	string loadedTexture, select;
	ELARABY::Vector<lands*>Lands;
	vector<vector<bool>>collision;
	Entity Tree,stone;
	Map();
	Map(float Gridsize, unsigned width, unsigned height);
	~Map();
	void update();
	void saveTofile();
	void LoadFromFile(bool fileName);
	void render(int startX, int width, int startY, int height, sf::RenderTarget* target);
	void render1(sf::Sprite& player, sf::RenderTarget* target, int opened);
};

