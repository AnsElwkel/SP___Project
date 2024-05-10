#pragma once
#include "character.h"
#include "lib.h"
struct enemies
{
	//Hit and Damage controls
	int damage = 10, HitDistance = 60;
	float HitSpeed = 0.1;

	//health Control
	int health = 5;

	//Speed Control
	float speed = 150;

	//Death Animation Control
	float DeathDelay = 0.5;

	//Enemies Scales
	Vector2f scale = { 2,2};

	//Sprite Sheet Size
	Vector2f WalkSize = { 64, 64 };
	Vector2f DieSize = { 64, 64 };
	Vector2f HitSize = { 192, 192 };
	int NumOfWalkFrames = 9;
	int NumOfHitFrames = 6;//Defer Between normal monster and boss

	// walking to right start frame
	const int WalkRightIndex = 11 * (int)WalkSize.y;
	// walking to left start frame
	const int WalkLeftIndex = 9 * (int)WalkSize.y;
	// walking up start frame
	const int WalkUpIndex = 8 * (int)WalkSize.y;
	// walking down start frame
	const int WalkDownIndex = 10 * (int)WalkSize.y;
	//Dieing index
	const int DieIndex = 20 * (int)WalkSize.y;

	//Hiting Right Start Frame
	const int HitRightIndex = 21 * (int)WalkSize.y + 3 * (int)HitSize.y;
	//Hiting Left Start Frame
	const int HitLeftIndex = 21 * (int)WalkSize.y + 1 * (int)HitSize.y;
	//Hiting Up Start Frame
	const int HitUpIndex = 21 * (int)WalkSize.y + 0 * (int)HitSize.y;
	//Hiting Down Start Frame
	const int HitDownIndex = 21 * (int)WalkSize.y + 2 * (int)HitSize.y;


	//Not Controls (Don't Touch)
	bool IsAlive = true, IsStanding = true, arrive = 0;
	int MaxHealth = health;
	int Animationi = 0, Hiti = 0, Deathi = 0;
	float AnimationTimer = 0, HitTimer = 0, DeathTimer = 0;
	float AnimationDelay = 10 / speed;
	int HitAnimationHandle = 6;

	string Type, HitDirection;
	RectangleShape BossHealthBar, BossHealthBarFrame;
	Font BossHealthFont;
	Text BossHealthText;
	Vector2f ChaseDestance;
	Sprite sprite;
	Texture SpriteTexture;

	//*********************  AI movement ************************ //
	ELARABY::pathFinder* find=nullptr;

	void set(int posx, int posy, int heal, string type, string shadow, string shield, bool SetOriginOrNot);
	void reset();
	enemies();
	void DealDamageTo(int&);
	void move(string);
	void hit(string, int&);
	void die(string);
	void GoTo(Vector2f Destination, float Speed);
	void LookAt(Sprite);
	/*void ChaceAndHit(character& x, ELARABY::Vector<ELARABY::Vector<bool>>& collision);*/
	void ChaceAndHit(character& x, bool ok, ELARABY::pathFinder& path,int i);
	void FinalBossDraw(character& x);
	//void FinalBossDraw(character);
	void ShowHealthBar();
};