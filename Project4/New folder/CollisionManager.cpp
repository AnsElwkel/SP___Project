#include "CollisionManager.h"
bool checkCollision(const sf::Sprite& Animal, const sf::Sprite& box2, const sf::Vector2f& velocity1) {
	sf::FloatRect sweptBox1 = Animal.getGlobalBounds();
	sweptBox1.left += velocity1.x;
	sweptBox1.top += velocity1.y;

	sf::FloatRect sweptBox2 = box2.getGlobalBounds();

	return sweptBox1.intersects(sweptBox2);
}
void collisionManager1::setObjectBound(Sprite& a, Sprite& b) {
	ob1Bounds = a.getGlobalBounds(), ob2Bounds = b.getGlobalBounds();
}
//Testing
void collisionManager1::setObjectBound(RectangleShape& a, RectangleShape& b) {
	ob1Bounds = a.getGlobalBounds(), ob2Bounds = b.getGlobalBounds();
}
//Testing
void collisionManager1::setObjectBound(RectangleShape& a, Sprite& b) {
	ob1Bounds = a.getGlobalBounds(), ob2Bounds = b.getGlobalBounds();
}
void collisionManager1::setObjectBound(Sprite& a, RectangleShape& b) {
	ob1Bounds = a.getGlobalBounds(), ob2Bounds = b.getGlobalBounds();
}


bool collisionManager1::isColliding(Sprite& a, Sprite& b)
{
	setObjectBound(a, b);
	return ob1Bounds.intersects(ob2Bounds);
}
bool collisionManager1::isColliding(RectangleShape& a, RectangleShape& b)
{
	setObjectBound(a, b);
	return ob1Bounds.intersects(ob2Bounds);
}
bool collisionManager1::isColliding(Sprite& a, RectangleShape& b)
{
	setObjectBound(a, b);
	return ob1Bounds.intersects(ob2Bounds);
}

float collisionManager1::calcOverlapX(FloatRect& ob1Bounds, FloatRect& ob2Bounds)
{
	return min(ob1Bounds.left + ob1Bounds.width - ob2Bounds.left, ob2Bounds.left + ob2Bounds.width - ob1Bounds.left);
}

float collisionManager1::calcOverlapY(FloatRect& a, FloatRect& b)
{
	return min(a.top + a.height - b.top, b.top + b.height - a.top);
}

void collisionManager1::Movement(Sprite& a, Sprite& b) {

	Vector2f Dirction;
	float xOverlap = calcOverlapX(ob1Bounds, ob2Bounds);
	float yOverlap = calcOverlapY(ob1Bounds, ob2Bounds);

	if (xOverlap < yOverlap)
		Dirction.x = (ob1Bounds.left < ob2Bounds.left) ? -xOverlap : xOverlap;
	else
		Dirction.y = (ob1Bounds.top < ob2Bounds.top) ? -yOverlap : yOverlap;

	a.move(Dirction);
}

void collisionManager1::Movement(RectangleShape& a, RectangleShape& b) {

	Vector2f Dirction;
	float xOverlap = calcOverlapX(ob1Bounds, ob2Bounds);
	float yOverlap = calcOverlapY(ob1Bounds, ob2Bounds);

	if (xOverlap < yOverlap)
		Dirction.x = (ob1Bounds.left < ob2Bounds.left) ? -xOverlap : xOverlap;
	else
		Dirction.y = (ob1Bounds.top < ob2Bounds.top) ? -yOverlap : yOverlap;

	a.move(Dirction);
}

bool collisionManager1::CollidingWithScreenBounderies(Window& window, RectangleShape& object)
{
	FloatRect objectBounds = object.getGlobalBounds();
	bool isCollidWithLeftBound = (objectBounds.left <= 0);
	bool isCollidWithRightBound = (objectBounds.left + objectBounds.width > window.getSize().x);
	bool isCollidWithTopBound = (objectBounds.top <= 0);
	bool isCollidWithBottomBound = (objectBounds.top + objectBounds.height > window.getSize().y);
	return (isCollidWithLeftBound || isCollidWithRightBound || isCollidWithTopBound || isCollidWithBottomBound);
}
bool collisionManager1::CollidingWithScreenBounderies(Window& window, Sprite& object)
{
	FloatRect objectBounds = object.getGlobalBounds();
	bool isCollidWithLeftBound = (objectBounds.left <= 0);
	bool isCollidWithRightBound = (objectBounds.left + objectBounds.width > window.getSize().x);
	bool isCollidWithTopBound = (objectBounds.top <= 0);
	bool isCollidWithBottomBound = (objectBounds.top + objectBounds.height > window.getSize().y);
	return (isCollidWithLeftBound || isCollidWithRightBound || isCollidWithTopBound || isCollidWithBottomBound);
}





