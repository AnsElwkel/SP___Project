#include"map.h"
#include "CollisionManager.h"
#include"states.h"
#include"Story.h"
#include "MOBS.h"
struct GameManager :states
{
	int opened=0,backGroundmanagement=0;
	sf::View camera;
	GameManager(sf::RenderWindow* windoww, stack<states*>* gameStates);
	collisionManager1 collisionDetector;
	Story* story = nullptr;
	RectangleShape arr[10];
	Map* world = new Map(100, 100, 100);
	sf::RectangleShape shape,background,checkCollision;
	Sprite check;
	void end();
	void render(sf::RenderTarget* target);
	void update(const float& dt);
	void Updatebind(const float& dt);
	void CheckCollison(int x, int y, RectangleShape& h);
	void CheckCollison1(int x, int y,int z);
};