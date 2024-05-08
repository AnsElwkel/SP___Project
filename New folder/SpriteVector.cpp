#include "SpriteVector.h"
using namespace sf;
void SpriteVector::add(Sprite x)
{
	if (VecSize < memory)
	{
		pvec[VecSize] = x;
		VecSize++;
	}
	else
	{
		Sprite* temp = new Sprite[memory];
		for (int i = 0; i < VecSize; i++)
			temp[i] = pvec[i];
		VecSize++;
		delete[]pvec;
		pvec = NULL;
		memory *= 2;
		pvec = new Sprite[memory];
		for (int i = 0; i < VecSize - 1; i++)
			pvec[i] = temp[i];
		delete[]temp;
		temp = NULL;
		pvec[VecSize - 1] = x;
	}
}

void SpriteVector::remove(int idx)
{
	if (idx < VecSize && idx >= 0)
	{
		Sprite* temp = new Sprite[VecSize];
		for (int i = 0, j = 0; i < VecSize; i++, j++)
		{
			if (j == idx)
			{
				i--;
			}
			else
			{
				temp[i] = pvec[j];
			}
		}
		VecSize--;
		for (int i = 0; i < VecSize; i++)
			pvec[i] = temp[i];
		delete[]temp;
		temp = NULL;
	}
}

void SpriteVector::clear()
{
	VecSize = 0;
	delete[]pvec;
	pvec = NULL;
	pvec = new Sprite[memory];
}

bool SpriteVector::empty()
{
	if (VecSize == 0)
		return 1;
	return 0;
}

int SpriteVector::size()
{
	return VecSize;
}