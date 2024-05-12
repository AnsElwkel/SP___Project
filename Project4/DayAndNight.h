#pragma once
#include"Enemies.h"
struct DayAndNight
{
	//Controls
	int darknes = 110;//As the number increase the night darknes increase
	int DNTime = 34; //Control the Day And Night Duration as Seconds
	float SunSetDelay = 0.015f, SunRiseDelay = 0.015f;//The Time SunSet And SunRise Take


	//Constants
	bool Day = 0;
	int DayDate = 0, DarkI = darknes;
	float SunSetTimer = 0.f, SunRiseTimer = 0.f;
	Clock DNclock;
	RectangleShape night;

	void flow();
};