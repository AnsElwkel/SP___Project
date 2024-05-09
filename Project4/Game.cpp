#include "Game.h"
#include <time.h>
//void Game::SpawnAndChace(character& x, ELARABY::pathFinder& path)
//{
//}
//void Game::MonstersKill()
//{
//}
bool Game::ThereIsMonsters()
{
	for (int j = 0; j < MaxMonsterSpawn; j++)
	{
		if (enemiesch[j] == 1)
			return 1;
	}
	return 0;
}

bool Fch = 0;
void Game::play(character &hero, ELARABY::pathFinder& path)
{
	//GamePlay
	hero.InCave = 0;
	if (Keyboard::isKeyPressed(Keyboard::P) && Fch == 0)
		Fch = 1;
	if (blink.Blinking && !hero.IsAlive)
	{
		dn.night.setSize(WindowSize * 2.0f);
		dn.DNclock.restart();
		dn.night.setFillColor(Color(0, 0, 0, dn.DarkI));
		window->draw(hero.sprite);
		blink.blink();
		window->draw(dn.night);
	}
	else if (!hero.IsAlive)
	{
		hero.die("stand");
		hero.lastKey = "down";
		//DrawSprite.add(hero.sprite);
		window->draw(dn.night);
	}
	else
	{
		hero.control = 1;
		blink.BlinkReset();
		//If the player Level increase The Upgrade screen will open
		if (hero.IsUpdating)
		{
			hero.SkillUpdate(hero.maxDamage, hero.MaxHealth, hero.MaxStamina, hero.walk, hero.HitSpeed);
			hero.run = hero.walk + (hero.walk * (60.0 / 100));
			hero.StaminaBarSet(hero.MaxStamina);
			hero.HealthBarSet(hero.MaxHealth);
		}
		else
		{
			dn.flow();
			if (dn.DayDate >= 10 || Fch)
			{
				//DrawSprite.add(hero.sprite);
				bool chi = ThereIsMonsters();
				if (!chi)
				{
					//hero.GoTo({ WindowSize.x, WindowSize.y / 2 }, 3, 300);
					hero.arrive = 1;
					if (hero.arrive)
					{
						hero.ChangeWeapon("LongSword");
						hero.HitSpeed = 0.05f;
						hero.damage = 50;
						hero.HealthBarSet(1000);
						hero.health = 1000;
						hero.StaminaBarSet(500);
						hero.hunger = 20;
						hero.HungerConsumeDelay = 20;
						hero.state = "FinalBossFight";
						hero.InCave = 1;
						hero.sprite.setPosition(0, window->getSize().y / 2);
						hero.arrive = 0;
					}
				}
				else
				{
					hero.walking.pause();
				}
				window->draw(dn.night);
			}
			else
			{
				if (!dn.Day)
				{
					//SpawnAndChace(hero, path);
					if (ThereIsMonsters())
					{
						for (int i = 0; i < MaxMonsterSpawn; i++)
						{
							if (enemiesch[i] == 1)
								hero.DealDamage(Monsters[i].sprite, Monsters[i].health);
						}
					}
					else
					{
						//As The Stop hitting Handling is at the (DealDamage()) Function
						if (hero.var == 6 && (hero.weapon == "LongSword" || hero.weapon == "Saber" || hero.weapon == "Waraxe" || hero.weapon == "Mace"))
							hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
						else if (hero.var == 0 && (hero.weapon == "Axe" || hero.weapon == "Pickaxe"))
							hero.var = 6, hero.IsAttacking = 0, hero.IsWalking = 1;
					}
				}
				else
				{
					
					
					//As The Stop hitting Handling is at the (DealDamage()) Function
					if (hero.var == 6 && (hero.weapon == "LongSword" || hero.weapon == "Saber" || hero.weapon == "Waraxe" || hero.weapon == "Mace"))
						hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
					else if (hero.var == 0 && (hero.weapon == "Axe" || hero.weapon == "Pickaxe"))
					hero.var = 6, hero.IsAttacking = 0, hero.IsWalking = 1;
					//path.Enemy.clear();
					//DrawSprite.add(hero.sprite);
				}
				hero.play1();
			}
		}
	}
}
//void Game::SpawnAndChace(character& x, ELARABY::pathFinder& path)
//{
//	Sprite arr[1];
//	srand(time(0));
//	if (GameTime % SpawnDelay == ls)
//	{
//		for (int i = 0; i < MaxMonsterSpawn; i++)
//		{
//			if (enemiesch[i] == 0)
//			{
//				cout << "Spawn " << i << endl;
//				enemiesch[i] = 1;
//				int x = rand() % 2;
//				if (x)
//					Monsters[i].set(rand() % window->getSize().x + 1, rand() % window->getSize().y + 1, 50, "Skelaton", "", "", 1);
//				else
//					Monsters[i].set(rand() % window->getSize().x + 1, rand() % window->getSize().y + 1, 50, "Zombie", "", "", 1);
//				arr[0] = Monsters[i].sprite;
//				cout << arr[0].getPosition().x << endl;
//				path.initial(arr, 1);
//				break;
//
//			}
//		}
//		ls = rand() % SpawnDelay;
//	}
//	for (int i = 0; i < MaxMonsterSpawn; i++)
//	{
//		if (enemiesch[i] == 1)
//		{
//			if (Monsters[i].IsAlive && Monsters[i].health > 0)
//			{
//				Monsters[i].ChaceAndHit(x, 0, path,i);
//
//				DrawSprite.add(Monsters[i].sprite);
//			}
//			else if (Monsters[i].IsAlive)
//			{
//				Monsters[i].die("");
//				DrawSprite.add(Monsters[i].sprite);
//			}
//			else if (!Monsters[i].IsAlive)
//			{
//				cout << "Erase " << i << endl;
//				x.score++;
//				enemiesch[i] = 0;
//			}
//		}
//	}
//	//DrawSprite.add(x.sprite);
//}
void Game::MonstersKill()
{

	for (int i = 0; i < MaxMonsterSpawn; i++)
	{
		if (enemiesch[i] == 1)
		{
			if (Monsters[i].IsAlive)
			{
				Monsters[i].die("");
			//	DrawSprite.add(Monsters[i].sprite);
			}
			else
			{
				cout << "Erase " << i << endl;
				enemiesch[i] = 0;
			}
		}
	}
}