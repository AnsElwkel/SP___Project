#include "Enemies.h"

//Enemie Set
void enemies::set(int posx = 0, int posy = 0, int heal = 50, string x = "FinalBoss", string y = "Shadow", string z = "Shield", bool ch = 1)
{
	Type = x;
	if (x == "FinalBoss")
	{
		SpriteTexture.loadFromFile("./res/Enemies/FinalBoss/" + y + '/' + z + '/' + x + ".png");
		BossHealthFont.loadFromFile("./res/Fonts/score.otf");
		BossHealthBar.setSize({ (float)heal, 32.f });
		BossHealthBar.setOrigin(BossHealthBar.getLocalBounds().getSize() / 2.f);
		BossHealthBar.setPosition(WindowSize.x / 2, BossHealthBar.getSize().y);
		BossHealthBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
		BossHealthBar.setFillColor(Color::Red);
		BossHealthBarFrame.setSize(BossHealthBar.getSize());
		BossHealthBarFrame.setScale(BossHealthBar.getScale());
		BossHealthBarFrame.setOutlineThickness(5);
		BossHealthBarFrame.setOrigin(BossHealthBar.getOrigin());
		BossHealthBarFrame.setPosition(BossHealthBar.getPosition().x, BossHealthBar.getPosition().y);
		BossHealthBarFrame.setOutlineColor(Color::Blue);
		BossHealthBarFrame.setFillColor(Color::Transparent);
		BossHealthText.setFont(BossHealthFont);
		BossHealthText.setOutlineThickness(5);
		BossHealthText.setFillColor(Color::White);
		HitAnimationHandle = 8;
	}
	else
	{
		SpriteTexture.loadFromFile("./res/Enemies/" + x + ".png");
		HitAnimationHandle = 6;
	}
	sprite.setTexture(SpriteTexture);
	sprite.setTextureRect(IntRect(0, WalkDownIndex, WalkSize.x, WalkSize.y));
	if (ch)sprite.setOrigin(WalkSize / 2.f);
	else sprite.setOrigin(WalkSize.x / 6, 0);
	if (ch)sprite.setScale(1+window->getSize().x/1920, 1+window->getSize().y/1080);
	else sprite.setScale(scale);
	sprite.setPosition(posx, posy);
	IsAlive = true;
	health = heal;
	MaxHealth = heal;
}

void enemies::reset()
{
	health = MaxHealth;
}

enemies::enemies()
{
	find = new ELARABY::pathFinder(5, 5);
}

void enemies::DealDamageTo(int &health)
{
	health -= damage;
}

//Animation
void enemies::move(string x)
{
	if (x == "right")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= NumOfWalkFrames;
			sprite.setTextureRect(IntRect(WalkSize.x * Animationi, WalkRightIndex, WalkSize.x, WalkSize.y));
			sprite.setOrigin(WalkSize / 2.f);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
	else if (x == "down")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= NumOfWalkFrames;
			sprite.setTextureRect(IntRect(WalkSize.x * Animationi, WalkDownIndex, WalkSize.x, WalkSize.y));
			sprite.setOrigin(32, 32);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
	else if (x == "left")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= NumOfWalkFrames;
			sprite.setTextureRect(IntRect(WalkSize.x * Animationi, WalkLeftIndex, WalkSize.x, WalkSize.y));
			sprite.setOrigin(WalkSize / 2.f);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
	else if (x == "up")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= NumOfWalkFrames;
			sprite.setTextureRect(IntRect(WalkSize.x * Animationi, WalkUpIndex, WalkSize.x, WalkSize.y));
			sprite.setOrigin(WalkSize / 2.f);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
}

void enemies::die(string x)
{
	if (x == "defeated")
	{
		if (IsStanding)
		{
			if (DeathTimer < 0)
			{
				Deathi++;
				Deathi %= 4;
				sprite.setTextureRect(IntRect(DieSize.x * Deathi, DieIndex, DieSize.x, DieSize.y));
				sprite.setOrigin(DieSize / 2.f);
				DeathTimer = DeathDelay;
				if (Deathi == 3)
					IsStanding = false;
			}
			else
			{
				DeathTimer -= DeltaTime;
			}
		}
	}
	else if (x == "stand")
	{
		if (!IsStanding)
		{
			if (DeathTimer < 0)
			{
				Deathi--;
				sprite.setTextureRect(IntRect(DieSize.x * Deathi, DieIndex, DieSize.x, DieSize.y));
				sprite.setOrigin(DieSize / 2.f);
				DeathTimer = DeathDelay;
				if (Deathi == 0)
					IsStanding = true, IsAlive = true;
			}
			else
			{
				DeathTimer -= DeltaTime;
			}
		}
	}
	else
	{
		if (DeathTimer < 0)
		{
			Deathi++;
			Deathi %= 6;
			sprite.setTextureRect(IntRect(DieSize.x * Deathi, DieIndex, DieSize.x, DieSize.y));
			sprite.setOrigin(DieSize / 2.f);
			DeathTimer = DeathDelay;
			if (Deathi == 5)
				IsAlive = false;
		}
		else
		{
			DeathTimer -= DeltaTime;
		}
	}
}

void enemies::hit(string x, int& h)
{
	if (x == "up")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(HitSize.x * Hiti, HitUpIndex, HitSize.x, HitSize.y));
			sprite.setOrigin(HitSize / 2.f);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		}
	else if (x == "down")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(HitSize.x * Hiti, HitDownIndex, HitSize.x, HitSize.y));
			sprite.setOrigin(HitSize / 2.f);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		}
	else if (x == "left")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(HitSize.x * Hiti, HitLeftIndex, HitSize.x, HitSize.y));
			sprite.setOrigin(HitSize / 2.f);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
	}
	else if (x == "right")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(HitSize.x * Hiti, HitRightIndex, HitSize.x, HitSize.y));
			sprite.setOrigin(HitSize / 2.f);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		}
}

//Go To some sprite
void enemies::GoTo(Vector2f x, float s)
{
	ChaseDestance = (x - (sprite.getPosition()));
	if (sqrt(ChaseDestance.x * ChaseDestance.x + ChaseDestance.y * ChaseDestance.y) > 3)
	{
		arrive = 0;
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			move("right");
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			move("down");
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			move("left");
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			move("up");
		sprite.move(normalize(ChaseDestance) * s * DeltaTime);
	}
	else
		arrive = 1;
}

void enemies::LookAt(Sprite x)
{
	Vector2f ChaseDestance = VectorDistanceBetween(x, sprite);
	if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
	{
		sprite.setTextureRect(IntRect(0, 64 * 11, 64, 64));
		sprite.setOrigin(32, 32);
	}
	if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
	{
		sprite.setTextureRect(IntRect(0, 64 * 10, 64, 64));
		sprite.setOrigin(32, 32);
	}
	if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
	{
		sprite.setTextureRect(IntRect(0, 64 * 9, 64, 64));
		sprite.setOrigin(32, 32);
	}
	if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
	{
		sprite.setTextureRect(IntRect(0, 64 * 8, 64, 64));
		sprite.setOrigin(32, 32);
	}
}

//Chasing Function
void enemies::ChaceAndHit(character& x, bool ok, ELARABY::pathFinder& path,int i)
{
	ChaseDestance = (x.sprite.getPosition() - (sprite.getPosition()));
	if (sqrt(ChaseDestance.x * ChaseDestance.x + ChaseDestance.y * ChaseDestance.y) > HitDistance)
	{
		if (ok || abs(ChaseDestance.x / 100) > 5 || abs(ChaseDestance.y / 100) >5||(abs(ChaseDestance.x / 100) <= 2 &&abs(ChaseDestance.y / 100) <= 2))
		{
			Hiti = 0;
			if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
				move("right");
			if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
				move("down");
			if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
				move("left");
			if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
				move("up");
			sprite.move(normalize(ChaseDestance) * speed * DeltaTime);
		}
		else
		{
			Vector2f dir =path.Astar(140, 0,0,100, sprite, 100,x.sprite,i);
			if (dir.x==1)
				move("right");
			else if (dir.y==1)
				move("down");
			else if (dir.x==-1)
				move("left");
			else if (dir.y==-1)
				move("up");
			sprite.move(dir.x * 0.5,dir.y*0.5);
		}

	}
	else
	{
		Animationi = 0;
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
		{
			if (HitDirection != "right")
			{
				Hiti = 0;
				HitDirection = "right";
			}
			hit("right", x.health);
		}
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
		{
			if (HitDirection != "down")
			{
				Hiti = 0;
				HitDirection = "down";
			}
			hit("down", x.health);
		}
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
		{
			if (HitDirection != "left")
			{
				Hiti = 0;
				HitDirection = "left";
			}
			hit("left", x.health);
		}
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
		{
			if (HitDirection != "up")
			{
				Hiti = 0;
				HitDirection = "up";
			}
			hit("up", x.health);
		}
	}
}

void enemies::FinalBossDraw(character &x)
{
	if (x.sprite.getPosition().y > sprite.getPosition().y)
		DrawSprite.add(sprite);
	DrawSprite.add(x.sprite);
	if (x.sprite.getPosition().y <= sprite.getPosition().y)
		DrawSprite.add(sprite);
}

void enemies::ShowHealthBar()
{
	BossHealthBar.setSize({ (float)health, BossHealthBar.getSize().y });
	BossHealthBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
	BossHealthText.setString(to_string(health));
	BossHealthText.setScale(BossHealthBar.getScale());
	BossHealthText.setOrigin((BossHealthText.getLocalBounds().width) / 2.f, (BossHealthText.getLocalBounds().height) / 2.f);
	BossHealthText.setPosition(BossHealthBar.getPosition().x + (BossHealthText.getOutlineThickness() - 3.8),
							   BossHealthBar.getPosition().y - BossHealthText.getOutlineThickness() + 
							  (BossHealthText.getOutlineThickness() - (2.2 + BossHealthBar.getScale().x * 2)) * 2);//A very Hard relation done by testing
	window->draw(BossHealthBarFrame);
	window->draw(BossHealthBar);
	window->draw(BossHealthText);
}