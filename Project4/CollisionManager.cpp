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



//Collision Manager 2
void collisionManager2::setNextBound(FloatRect& ob1Bounds, Vector2f& Velocity)
{
	nextStep = ob1Bounds;
	nextStep.left += Velocity.x;
	nextStep.top += Velocity.y;
}

/*
	This Function is handling Collision by another approach 
Parameters -> 1- walls (or anything that have colliding with object
			  2- movementSpeed of object (To handle movement when colliding)
			  3- objects to check that every object(like as cheep or enemy and so on...)
				 has been colliding with walls (or anything in map)
*/
void collisionManager2::applyCollision(vector<Sprite>& walls, Vector2f& Velocity, vector<Sprite>& objects)
{
	for (auto& object : objects) {
		for (auto& wall : walls) {
			setObjectBound(object, wall);
			setNextBound(ob1Bounds, Velocity);
			if (ob2Bounds.intersects(nextStep)) {
				//Handle Left Collision
				if (leftCollision()) {
					Velocity.x = 0;
					object.setPosition(ob2Bounds.left + ob2Bounds.width, object.getPosition().y);
				}
				//Handle Right Collision
				else if (rightCollision()) {
					Velocity.x = 0;
					object.setPosition(ob2Bounds.left - ob1Bounds.width, object.getPosition().y);
				}

				//Handle Top Collision
				if (topCollision()) {
					Velocity.y = 0;
					object.setPosition(object.getPosition().x, ob2Bounds.top + ob2Bounds.height);
				}
				//Handle Bottom Collision
				else if (bottomCollision()) {
					Velocity.y = 0;
					object.setPosition(object.getPosition().x, ob2Bounds.top - ob1Bounds.height);
				}
			}
		}
	}
}

//Testing 
void collisionManager2::applyCollision(vector<RectangleShape>& walls, Vector2f& Velocity, RectangleShape& object)
{
	for (auto& wall : walls) {
		setObjectBound(object, wall);
		setNextBound(ob1Bounds, Velocity);
		if (ob2Bounds.intersects(nextStep)) {
			//Handle Left Collision
			if (leftCollision()) {
				Velocity.x = 0;
				object.setPosition(ob2Bounds.left + ob2Bounds.width, object.getPosition().y);
			}
			//Handle Right Collision
			else if (rightCollision()) {
				Velocity.x = 0;
				object.setPosition(ob2Bounds.left - ob1Bounds.width, object.getPosition().y);
			}

			//Handle Top Collision
			if (topCollision()) {
				Velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top + ob2Bounds.height);
			}
			//Handle Bottom Collision
			else if (bottomCollision()) {
				Velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top - ob1Bounds.height);
			}

		}
	}
}

//Testing 
void collisionManager2::applyCollision(Sprite  wall, Vector2f& Velocity, Sprite& object) {
	srand(time(nullptr));
	int tar = 0, select = -1;
	//for (int i = 0; i < 4; i++) {
	setObjectBound(object, wall);
	setNextBound(ob1Bounds, Velocity);
	if (ob2Bounds.intersects(nextStep)) {
		//Handle Left Collision
		if (leftCollision()) {
			object.setPosition(ob2Bounds.left + ob2Bounds.width, ob1Bounds.top);
			tar = 1;
		}
		//Handle Right Collision
		else if (rightCollision()) {
			object.setPosition(ob2Bounds.left - ob1Bounds.width, ob1Bounds.top);
			tar = 2;
		}

		//Handle Top Collision
		if (topCollision()) {
			object.setPosition(ob1Bounds.left, ob2Bounds.top + ob2Bounds.height);
			tar = 3;

		}
		//Handle Bottom Collision
		else if (bottomCollision()) {
			object.setPosition(ob1Bounds.left, ob2Bounds.top - ob1Bounds.height);
			tar = 4;

		}
		select = rand() % 4 + 1;
		while (select == tar)
			select = rand() % 4 + 1; // 2 3 4

		if (tar == 1 || tar == 2) {
			if (select == 1) {
				Velocity.x *= -1;
			}
			else if (select == 2) {
				Velocity.x *= -1;
			}
			else if (select == 3) {
				Velocity.y = Velocity.x;
				Velocity.x = 0;
			}
			else if (select == 4) {
				Velocity.y = Velocity.x;
				Velocity.x = 0;
			}
		}
		else if (tar == 3 || tar == 4) {
			if (select == 1) {
				Velocity.x = Velocity.y;
				Velocity.y = 0;
			}
			else if (select == 2) {
				Velocity.x = Velocity.y;
				Velocity.y = 0;
			}
			else if (select == 3) {
				Velocity.y *= -1;
			}
			else if (select == 4) {
				Velocity.y *= -1;
			}

		}
	}

}

//Check the collision from Left side
bool collisionManager2::leftCollision()
{
	return (ob1Bounds.left > ob2Bounds.left
		&& ob1Bounds.left + ob1Bounds.width > ob2Bounds.left + ob2Bounds.width
		&& ob1Bounds.top < ob2Bounds.top + ob2Bounds.height
		&& ob2Bounds.top < ob1Bounds.top + ob1Bounds.height);
}

//Check the collision from Right side
bool collisionManager2::rightCollision()
{
	return (ob1Bounds.left < ob2Bounds.left
		&& ob1Bounds.left + ob1Bounds.width < ob2Bounds.left + ob2Bounds.width
		&& ob1Bounds.top < ob2Bounds.top + ob2Bounds.height
		&& ob2Bounds.top < ob1Bounds.top + ob1Bounds.height);
}

//Check the collision from Top 
bool collisionManager2::topCollision()
{
	return (ob1Bounds.top > ob2Bounds.top
		&& ob1Bounds.top + ob1Bounds.height > ob2Bounds.top + ob2Bounds.height
		&& ob1Bounds.left < ob2Bounds.left + ob2Bounds.width
		&& ob2Bounds.left < ob1Bounds.left + ob1Bounds.width);
}

//Check the collision from Bottom 
bool collisionManager2::bottomCollision()
{
	return (ob1Bounds.top < ob2Bounds.top
		&& ob1Bounds.top + ob1Bounds.height < ob2Bounds.top + ob2Bounds.height
		&& ob1Bounds.left < ob2Bounds.left + ob2Bounds.width
		&& ob2Bounds.left < ob1Bounds.left + ob1Bounds.width);
}

void collisionManager2::applyCollisionWithAnimals(Sprite& object, Vector2f& velocity, Sprite wall[], float& dt, bool& isRandom)
{
	int size = 4;
	srand(time(nullptr));

	int select = 0;
	for (int i = 0; i < size; i++) {
		setObjectBound(object, wall[i]);
		setNextBound(ob1Bounds, velocity);
		if (ob2Bounds.intersects(nextStep)) {

			select = (rand() % 4) + 1;

			//Handle Left Collision  select!=1
			if (leftCollision()) {
				object.setPosition(ob2Bounds.left + ob2Bounds.width, object.getPosition().y);
				velocity.x = 0;
				if (!isRandom) {
					while (select == 1)
						select = (rand() % 4) + 1;
				}
			}

			//Handle Right Collision select!=2
			else if (rightCollision()) {
				velocity.x = 0;
				object.setPosition(ob2Bounds.left - ob1Bounds.width, object.getPosition().y);
				if (!isRandom) {
					while (select == 2)
						select = (rand() % 4) + 1;
				}
			}

			//Handle Top Collision select!=3
			else if (topCollision()) {
				velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top + ob1Bounds.height);
				if (!isRandom) {
					while (select == 3)
						select = (rand() % 4) + 1;
				}
			}

			//Handle Bottom Collision select !=4
			else if (bottomCollision()) {
				velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top - ob1Bounds.height);
				if (!isRandom) {
					while (select == 4)
						select = (rand() % 4) + 1;
				}

			}

			if (select == 1)
				velocity = { -15 * dt ,0 };//move left

			else if (select == 2)
				velocity = { 15 * dt ,0 };//move Right

			else if (select == 3)
				velocity = { 0, -15 * dt };//move up

			else if (select == 4)
				velocity = { 0,15 * dt };//move down
		}
	}
}

//overloading for mobs to be eating
void collisionManager2::applyCollisionWithAnimals(Sprite& mainChar, Vector2f& Velocity, Sprite& object, int& Hp, float& SwordCode, float& dt)
{
	srand(time(nullptr));
	int select = 0;
	setObjectBound(object, mainChar);
	setNextBound(ob1Bounds, Velocity);
	if (ob2Bounds.intersects(nextStep)) {


		//Handle Left Collision  select!=1
		if (leftCollision()) {
			Velocity.x = 0;
			object.setPosition(ob2Bounds.left + ob2Bounds.width + 3, object.getPosition().y);
			select = (rand() % 4) + 1;
			while (select == 1)
				select = (rand() % 4) + 1;
		}


		//Handle Right Collision select!=2
		else if (rightCollision()) {
			Velocity.x = 0;
			object.setPosition(ob2Bounds.left - ob1Bounds.width - 3, object.getPosition().y);
			select = (rand() % 4) + 1;
			while (select == 2)
				select = (rand() % 4) + 2;

		}


		//Handle Top Collision select!=3
		if (topCollision()) {
			Velocity.y = 0;
			object.setPosition(object.getPosition().x, object.getPosition().y);
			select = (rand() % 4) + 1;
			while (select == 2)
				select = (rand() % 4) + 1;


		}


		//Handle Bottom Collision select !=4
		else if (bottomCollision()) {
			Velocity.y = 0;
			object.setPosition(object.getPosition().x, object.getPosition().y);
			select = (rand() % 4) + 1;
			while (select == 4)
				select = (rand() % 4) + 1;
		}

		if (select == 1)
			Velocity.x = -((rand() % 30) + 40) * dt;//move left
		else if (select == 2)
			Velocity.x = ((rand() % 30) + 40) * dt;//move Right
		else if (select == 3)
			Velocity.y = -((rand() % 30) + 40) * dt;//move up
		else if (select == 4)
			Velocity.y = ((rand() % 30) + 40) * dt;//move down


	}
}
