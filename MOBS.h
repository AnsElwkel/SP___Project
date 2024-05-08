#ifndef MOBS_H_
#define MOBS_H_
#pragma once
#include"CollisionManager.h"
#include"includes.h"
using namespace sf;
using namespace std;


struct MOBS
{
	collisionManager1 collision;

	int swordCode = 10;
	float deltaTime = 1 / 60.f;
	float timer = 0;

	int normalVelocity = 30;
	int killedMobs = 0;
	Texture animalTexture;
	Texture meatTexure;
	
	Sprite animalSprite;
	Sprite meatSprite;

	SoundBuffer animalBuffer;
	SoundBuffer hitBuffer;
	Sound animalSound;
	Sound hitSound;
	Vector2i spriteSize = { 512,512 };
	Vector2i spriteChickenSize = { 128,128 };
	Vector2f animalVelocity = { 0,0 };
	Vector2f scale { 1.4,1.4 };
	
	int animationCounterAnimal = 0;//a for animal
	int hp = 120;

	float animalDelay = 0.06f;
	float heroDelay = 0.06f;
	float soundTimer = 0;
	
	Clock soundClock;

	bool isHit=0;
	bool once=1;

	
	
	void randomlyMove(RectangleShape object);
	void Animation(float&, Vector2i&);
	void hit(Sprite&, int&);
	void mob(Vector2i&);
	void playSound(Sprite& );



};//use a vector here


#endif
