#include"map.h"
#include "CollisionManager.h"
#include"states.h"
#include"Story.h"
#include "MOBS.h"
#include"PauseMenu.h"
#include"Settings.h"
#include"DailyMission.h"
struct GameManager :states
{
	int opened=0,backGroundmanagement=0;
	sf::View camera;
	void colli(RectangleShape& shape, RectangleShape& h, int x, int y);
	collisionManager1 collisionDetector;
	Story* story = nullptr;
	RectangleShape arr[10];
	Map* world = new Map(100, 140, 100);
	sf::RectangleShape shape,background,checkCollision;
	PauseMenu* PauseM=new PauseMenu(window);
	Sprite check;
	GameManager(sf::RenderWindow* windoww, stack<states*>* gameStates);
	void end();
	void render(sf::RenderTarget* target);
	void buttonUpdate();
	void pausinit();
	void update(const float& dt);
	void Updatebind(const float& dt);
	void CheckCollison(int x, int y, RectangleShape& h);
	void CheckCollison1(int x, int y,int z);
};