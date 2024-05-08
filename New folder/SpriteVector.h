#include "includes.h"
using namespace sf;
struct SpriteVector
{
	int VecSize = 0;
	int memory = 64;//initial memory Size
	Sprite* pvec = new Sprite[memory];
	void add(Sprite);
	void remove(int);
	void clear();
	bool empty();
	int size();
};