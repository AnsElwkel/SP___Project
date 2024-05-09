#pragma once
#include "GameScenes.h"
#include"lib.h"
#include "DayAndNight.h"
struct Game
{
	//Monster Spawn Controls 
	int SpawnDelay = 10; //Delay is random So (Max = SpawnDelay + Min - 1) & (Min = 3)
	int ls = 3; // (Min)
	const int MaxMonsterSpawn = 1;
	bool enemiesch[5] = {};
	enemies Monsters[5] = {};
	DayAndNight dn;
	GameScenes blink;
	void SpawnAndChace(character& x, ELARABY::pathFinder& path);
	void MonstersKill();
	bool ThereIsMonsters();
	void play(character&, ELARABY::pathFinder &path);
};