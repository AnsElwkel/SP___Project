#pragma once
#include "Enemies.h"
#include"Game.h"
struct Story
{
	
	Game game;
	enemies FinalBoss;
	character hero;
	GameScenes scene;
	Clock WinClock;
	int WiningNeedTime;
	bool IsWining;
	Font f;
	Text te;
	Vector2f WindowSize;
	RenderWindow* window;
	Story();
	Story(sf::RenderWindow *window);
	int Begin(float DeltaTime, float GameTime, ELARABY::pathFinder& path);
};