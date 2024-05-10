#pragma once
#include "CollisionManager.h"
#include "SpriteVector.h"
#include "includes.h"
#ifndef GLOBALS_H 
#define GLOBALS_H 

//Window Control
extern RenderWindow *window;
extern Vector2f WindowSize;

//DeltaTime and GameClock Measure
extern float DeltaTime;
extern int GameTime;

//Press Control
extern float PressTimer, PressDelay;

//Draw Sprite control
extern SpriteVector DrawSprite;

Vector2f normalize(Vector2f vec);
int DistanceBetween(Sprite, Sprite);
Vector2f VectorDistanceBetween(Sprite, Sprite);

#endif