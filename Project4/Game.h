#pragma once
#include "GameScenes.h"
#include"lib.h"
#include "DayAndNight.h"
struct Game
{
	//Monster Spawn Controls 
	int SpawnDelay = 10; //Delay is random So (Max = SpawnDelay + Min - 1) & (Min = 3)
	int ls = 3; // (Min)
	DayAndNight dn;
	GameScenes blink;
	const int MaxMonsterSpawn = 2;
	enemies Monsters[2];
	bool enemiesch[2]{};
	bool ThereIsMonsters();
	void play(character& hero, ELARABY::pathFinder& path);
	void MonstersKill();
};