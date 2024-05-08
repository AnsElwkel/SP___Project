#include "DayAndNight.h"
bool SetOnce = 1;
void DayAndNight::flow()
{
	//Day and Night Apearance
	if ((int)DNclock.getElapsedTime().asSeconds() >= DNTime)
	{
		if (Day)
		{
			if (DarkI < darknes)
			{
				if (SunSetTimer < 0)
				{
					DarkI++;
					SunSetTimer = SunSetDelay;
				}
				else
					SunSetTimer -= DeltaTime;
			}
			else
			{
				Day = !Day;
				DNclock.restart();
			}
		}
		else
		{
			if (DarkI > 0)
			{
				if (SunRiseTimer < 0)
				{
					DarkI--;
					SunRiseTimer = SunRiseDelay;
				}
				else
					SunRiseTimer -= DeltaTime;
			}
			else
			{
				Day = !Day;
				DNclock.restart();
				DayDate++;
				cout << "DayDate: " << DayDate << endl;
			}
		}
	}
	night.setFillColor(Color(0, 0, 0, DarkI));
}