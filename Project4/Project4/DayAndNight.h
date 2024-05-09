#pragma once
#include"Enemies.h"
struct DayAndNight
{
	//Controls
	int darknes = 110;//As the number increase the night darknes increase
	int DNTime = 15; //Control the Day And Night Duration as Seconds
	float SunSetDelay = 0.015, SunRiseDelay = 0.015;//The Time SunSet And SunRise Take


	//Constants
	bool Day = 0;
	int DayDate = 0, DarkI = darknes;
	float SunSetTimer = 0, SunRiseTimer = 0;
	Clock DNclock;
	RectangleShape night;

	void flow();
};