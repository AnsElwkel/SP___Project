#pragma once
#include "includes.h"
#include"global.h"
#include"PressF.h"
struct character
{
	//Stamina Control
	int stamina = 250;//Initial Stamina
	float StaminaConsumtionTime = 0.f, StaminaConsumtionDelay = 0.01f;
	float StaminaRestoreTime = 0.f, StaminaRestoreDelay = 0.1f;

	//Speed Control
	float walk = 150.f;//Initial Speed
	float run = walk + (walk * (60.f / 100));

	//Helth Control
	int health = 1000;//Initial Health
	float HealthRestoreTime = 0.f, HealthRestoreDelay = 0.1f;

	//Hunger Control
	int hunger = 50;
	float HungerConsumeTime = 0.f, HungerConsumeDelay = 5.f;
	float HealthConsumtionTime = 0.f, HealthConsumtionDelay = 0.5f;

	//Hit Control
	int damage = 20, HitDistance = 100;
	float HitSpeed = 0.1f;

	//Dodge Control
	int DodgeStminaConsumtion = 50;
	float DodgeTeleportDis = 100.f * WindowSize.x / 1280.f;

	bool isOpen = 0;
	//Death Control
	float DeathDelay = 0.5f;

	//Hero Scales
	Vector2f scale = { 0.8f + window->getSize().x / 1920.f, 0.8f + window->getSize().y / 1080.f };

	//Sprite Sheet Size
	Vector2f WalkSize = { 64.f, 64.f };
	Vector2f DieSize = { 64.f, 64.f };
	Vector2f HitSize = { 192.f, 192.f };
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
	int maxDamage = damage;
	int score = 0, var /*Dealing Damage Handling Variable*/, MaxStamina = stamina, MaxHealth = health, MaxHunger = hunger;
	bool IsAlive = 0, IsWeapon = 0, IsWalking = 0, IsAttacking = 0, IsStanding = 1,
		arrive = 0, InCave = 1, IsUpdating = 1, control = 1;
	float AnemationTimer = 0, HitTimer = 0, DeathTimer = 0, speed = walk;
	int AnimationI = 0, HitI = 0, DeathI = 0;
	float AnemationDelay = 10.f / speed;

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
	void GoTo(Vector2f Destination, int DestanceToStopBeforeDestenation, int Speed);
	void LookAt(Sprite);
	void chooseHero();
	void ShowHealthBar();
	void ShowStaminaBar();
	void ShowHungerBar();
};