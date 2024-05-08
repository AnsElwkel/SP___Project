#include"includes.h"
#include"application.h"
#include <time.h>
#include"Global.h"
SpriteVector DrawSprite;

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Siltara", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar|sf::Style::Fullscreen); 
Vector2f WindowSize = { (float)window->getSize().x, (float)window->getSize().y };

//Control DeltaTime
float DeltaTime = 0;
Clock DTclock;

//Count the game time begin from it's run
int GameTime = 0;
Clock GameClock;

//Press Control
float PressTimer = 0, PressDelay = 0.19;


//Normalize to auto move
Vector2f normalize(Vector2f vec)
{
	float mag = sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (mag != 0)
	{
		vec.x /= mag;
		vec.y /= mag;
	}
	return vec;
}

//Get the distance between two Sprites
int DistanceBetween(Sprite x, Sprite y)
{
	Vector2f Destance;
	Destance = (x.getPosition() - (y.getPosition()));
	return sqrt(Destance.x * Destance.x + Destance.y * Destance.y);
}
Vector2f VectorDistanceBetween(Sprite x, Sprite y)
{
	return (x.getPosition() - (y.getPosition()));
}

using namespace std;
int main()
{

	
	//window->setFramerateLimit(100);
	setCursor();
	application Application(window);
	srand(time(NULL));
	sf::Clock dt;
	while (Application.isRunning())
	{	
		window->setMouseCursorVisible(1);
		DeltaTime = dt.restart().asSeconds();
		GameTime = GameClock.getElapsedTime().asSeconds();
		Application.DeltaUpdate(DeltaTime);
		Application.update();
		Application.render();
	}
}