#include"MOBS.h"
void MOBS::randomlyMove(RectangleShape object)
{
	int select = 0, tar = 0;
	int size = 4;
	if (collision.isColliding(animalSprite, object))
	{
		RectangleShape shape(sf::Vector2f(animalSprite.getGlobalBounds().width, (animalSprite.getGlobalBounds().height)));
		shape.setPosition(animalSprite.getGlobalBounds().left, animalSprite.getGlobalBounds().top);
		collision.setObjectBound(shape, object);
		collision.Movement(shape, object);
		animalSprite.setPosition(shape.getPosition());
		if (object.getPosition().x > animalSprite.getPosition().x)//animal is left
		{
			tar = 1;
		}
		else if (object.getPosition().x < animalSprite.getPosition().x)//animal is right
		{
			tar = 2;
		}
		else if (object.getPosition().y > animalSprite.getPosition().y) //animal is up
		{
			tar = 3;
		}
		else if (object.getPosition().y < animalSprite.getPosition().y)//animal is down
		{
			tar = 4;
		}
		select = rand() % 4 + 1;
		while (select == tar)
			select = rand() % 4 + 1;
		if (Keyboard::isKeyPressed(Keyboard::X))
		{
			hp -= 25;
		}
	}
	if (select == 1)
		animalVelocity = { normalVelocity * deltaTime ,0 };//move right

	else if (select == 2)
		animalVelocity = { -normalVelocity * deltaTime ,0 };//move left

	else if (select == 3)
		animalVelocity = { 0, normalVelocity * deltaTime };//move down

	else if (select == 4)
		animalVelocity = { 0,-normalVelocity * deltaTime };//move up
	animalSprite.move(animalVelocity);
}

void MOBS::Animation(float& rate, Vector2i&size)
{
	if (timer < 0) 
	{
		animationCounterAnimal++;
		animationCounterAnimal %= 4;
		animalSprite.setTextureRect(IntRect(animationCounterAnimal * (size.x / 4), int(size.y * rate), size.x / 4, size.y / 4));
		timer = animalDelay;
	}
	else 
	{
		timer -= deltaTime;
	}
}
void MOBS::mob(Vector2i&size) 
{
	srand(unsigned int(time(nullptr)));
	if (once)
	{
		animalSprite.setScale(scale);
		animalSprite.setTextureRect(IntRect((size.x / 4), int(size.y * 0.75), size.x / 4, size.y / 4));
		//animalSprite.setPosition(Vector2f(450, 490)); //--->REMOVE;
		int select = 0;
		select = (rand() % 4) + 1;

		if (select == 1)
			animalVelocity = { -normalVelocity * deltaTime ,0 };//move left

		else if (select == 2)
			animalVelocity = { normalVelocity * deltaTime ,0 };//move Right

		else if (select == 3)
			animalVelocity = { 0, -normalVelocity * deltaTime };//move up

		else if (select == 4)
			animalVelocity = { 0,normalVelocity * deltaTime };//move down

		once = 0;
	}

	//move right
	if (animalVelocity.x > 0) {
		float ratio = 0.75f;
		Animation(ratio, size);
	}
	//move up
	else  if (animalVelocity.y < 0) {
		float ratio = 0.f;
		Animation(ratio, size);
	}
	//move left
	else  if (animalVelocity.x < 0) {
		float ratio = 0.25f;
		Animation(ratio, size);
	}
	//move down
	else if (animalVelocity.y > 0) {
		float ratio = 0.5f;
		Animation(ratio, size);
		
	}

	animalSprite.move(animalVelocity);


}
void MOBS::playSound(Sprite& mainChar) {
	//distance between mainCharacter and animal
	int distance = (int)sqrt(pow((mainChar.getPosition().x - animalSprite.getPosition().x), 2) + pow((mainChar.getPosition().y - animalSprite.getPosition().y), 2));
	if (distance <= 950 && soundTimer >= 9)//every 16 sec sound will be played if distance lessthan or equal 950px
	{
		animalSound.play();

		soundClock.restart();

	}

}

void MOBS::hit(Sprite& mainChar, int& animationCounterHit) {

	int distance = (int)sqrt(pow((mainChar.getPosition().x - animalSprite.getPosition().x), 2) + pow((mainChar.getPosition().y - animalSprite.getPosition().y), 2));
	if (distance <= 150 && Keyboard::isKeyPressed(Keyboard::X)) {
		
		if (animationCounterHit == 3)
		{
			animalVelocity *= 2.F;
			hp -= swordCode;
			isHit = 1;
		}
		hitSound.play();
	}
	else if (distance == 400 && isHit == 1)//When will i reset velocity edit condition
	{
		animalVelocity *= 0.5F;
		isHit = 0;
	}
	if (hp <= 0)
	{
		meatSprite.setPosition(animalSprite.getPosition().x, animalSprite.getPosition().y);
		animalSprite.setScale(0, 0);
		killedMobs++;
	}
}
