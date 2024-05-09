#pragma once
#include "includes.h"
#include"global.h"
#include"PressF.h"
struct character
{
	//Stamina Control
	int stamina = 250;//Initial Stamina
	float StaminaConsumtionTime = 0, StaminaConsumtionDelay = 0.01;
	float StaminaRestoreTime = 0, StaminaRestoreDelay = 0.1;

	//Speed Control
	float walk = 150;//Initial Speed
	float run = walk + (walk * (60.0 / 100));

	//Helth Control
	int health = 1000;//Initial Health
	float HealthRestoreTime = 0, HealthRestoreDelay = 0.1;
	//Hunger Control
	int hunger = 500;
	float HungerConsumeTime = 0, HungerConsumeDelay = 5;
	float HealthConsumtionTime = 0, HealthConsumtionDelay = 0.5;

	//Hit Control
	int damage = 20, HitDistance = 100;
	float HitSpeed = 0.1f;

	//Dodge Control
	int DodgeStminaConsumtion = 50;
	float DodgeTeleportDis = 100 * WindowSize.x / 1280;

	bool isOpen = 0;
	//Death Control
	float DeathDelay = 0.5;

	//Hero Scales
	Vector2f scale = { 0.8f+window->getSize().x/1920, 0.8f+window->getSize().y/1080};

	//Sprite Sheet Size
	Vector2f WalkSize = { 64, 64 };
	Vector2f DieSize = { 64, 64 };
	Vector2f HitSize = { 192, 192 };
	int NumOfWalkFrames = 9;
	int NumOfHitFrames = 6;

	// walking to right start frame
	const int WalkRightIndex = 11 * WalkSize.y;
	// walking to left start frame
	const int WalkLeftIndex = 9 * WalkSize.y;
	// walking up start frame
	const int WalkUpIndex = 8 * WalkSize.y;
	// walking down start frame
	const int WalkDownIndex = 10 * WalkSize.y;
	//Dieing index
	const int DieIndex = 20 * WalkSize.y;

	//Hiting Right Start Frame
	int HitRightIndex = 21 * WalkSize.y + 3 * HitSize.y;
	//Hiting Left Start Frame
	int HitLeftIndex = 21 * WalkSize.y + 1 * HitSize.y;
	//Hiting Up Start Frame
	int HitUpIndex = 21 * WalkSize.y + 0 * HitSize.y;
	//Hiting Down Start Frame
	int HitDownIndex = 21 * WalkSize.y + 2 * HitSize.y;


	//Not Controls (Don't touch)
	int score = 0, var /*Dealing Damage Handling Variable*/, MaxStamina = stamina, MaxHealth = health, MaxHunger = hunger;
	bool IsAlive = 0, IsWeapon = 0, IsWalking = 0, IsAttacking = 0, IsStanding = 1, arrive = 0, InCave = 1, IsUpdating = 1;
	float AnemationTimer = 0, HitTimer = 0, DeathTimer = 0, speed = walk;
	int AnimationI = 0, HitI = 0, DeathI = 0;
	float AnemationDelay = 10 / speed;

	string who, weapon = "Saber", shadow = "NoShadow", lastKey, state = "Defeated";
	Vector2f HeroSize = WalkSize;
	Sprite sprite;
	Texture tHero;
	Sound walking;
	SoundBuffer Bwalking;
	RectangleShape HealthBar, HealthBarFrame;
	Font HealthFont;
	Text HealthText;
	RectangleShape StaminaBar, StaminaBarFrame;
	Font StaminaFont;
	Text StaminaText;
	RectangleShape HungerBar, HungerBarFrame;
	Font HungerFont;
	Text HungerText;

	void set(int posx, int posy, bool SetOriginOrNot);
	void reset();
	void HealthBarSet(int NewHeal);
	void StaminaBarSet(int NewStamina);
	void SpeedIncreaseBy(int AddedNumber);
	void walkRight(bool Move);
	void walkLeft(bool Move);
	void walkUp(bool Move);
	void walkDown(bool Move);
	void ChangeWeapon(string weapon);
	void ChangeShadow(string shadow);
	void SkillUpdate(int&, int&, int&, float&, float&);
	void move();
	void dodge();
	void play();
	void play1();
	void die(string);
	void hit();
	void DealDamage(Sprite&, int& heal);
	void GoTo(Vector2f Destination,int DestanceToStopBeforeDestenation, int Speed);
	void LookAt(Sprite);
	void chooseHero();
	void ShowHealthBar();
	void ShowStaminaBar();
	void ShowHungerBar();
};