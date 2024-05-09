#include "Story.h"
using namespace sf;
Story::Story()
{
}
int Story::Begin(float DeltaTime, float GameTime, ELARABY::pathFinder& path)
{
	srand(time(0));//Randoms the (rand()) Function

	//Hide the mouse cursor //Disabled
	window->setMouseCursorVisible(1);


	if (hero.InCave && hero.shadow == "Shadow")
		hero.ChangeShadow("NoShadow");

	//Starting The Game
	if (scene.InstructionsSceneCh)
	{
		hero.control = 0;
		scene.InstructionsScene(FinalBoss, hero);
	}
	else if (scene.scene0ch)
	{
		hero.control = 0;
		scene.scene0(FinalBoss, hero);
	}
	else if (scene.scene1ch)
	{
		hero.control = 0;
		scene.scene1(FinalBoss, hero);
		hero.health = 40;
	}
	else if (hero.health > 15 && scene.scene2ch)
	{
		hero.control = 1;
		if (!hero.IsWeapon)
		{
			hero.ChangeWeapon("Saber");
		}
		hero.play();
		hero.DealDamage(FinalBoss.sprite, FinalBoss.health);
		FinalBoss.ChaceAndHit(hero, 1, path, 0);
		window->draw(FinalBoss.sprite);
		window->draw(hero.sprite);
		FinalBoss.ShowHealthBar();
	}
	else if (scene.scene2ch)
	{
		hero.control = 0;
		FinalBoss.LookAt(hero.sprite);
		if (hero.health <= 0)
			hero.health = 2;
		hero.die("defeated");
		if (hero.IsStanding)
		{
			FinalBoss.FinalBossDraw(hero);
			hero.ShowHealthBar();
			hero.ShowStaminaBar();
			hero.ShowHungerBar();
			FinalBoss.ShowHealthBar();
		}
		else
			scene.scene2(FinalBoss, hero);
	}
	else if (hero.state == "Defeated")
	{
		hero.control = 0;
		hero.HealthBarSet(500);
		hero.health = hero.MaxHealth;
		hero.stamina = hero.MaxStamina;
		FinalBoss.health = FinalBoss.MaxHealth;
		hero.state = "BeingStronger";
		hero.ChangeWeapon("Pickaxe");
		hero.sprite.setPosition(window->getSize().x / 2, window->getSize().y / 2);
		scene.Blinking = 1;
	}
	else if (hero.state == "BeingStronger")
	{
		game.play(hero, path);
	}
	else if (hero.state == "FinalBossFight")
	{
		if (scene.scene3ch)
		{
			hero.control = 0;
			FinalBoss.sprite.setOrigin(FinalBoss.WalkSize / 2.f);
			FinalBoss.sprite.setPosition(WindowSize.x * 3 / 4, WindowSize.y / 2);
			FinalBoss.sprite.setTextureRect(IntRect(0, FinalBoss.WalkLeftIndex, FinalBoss.WalkSize.x, FinalBoss.WalkSize.y));
			scene.scene3(FinalBoss, hero);
		}
		else if (FinalBoss.health > 15 && scene.scene4ch)
		{
			hero.control = 1;
			if (hero.health > 0)
			{
				hero.play();
				hero.DealDamage(FinalBoss.sprite, FinalBoss.health);
				FinalBoss.ChaceAndHit(hero, 1, path, 0);
				window->draw(FinalBoss.sprite);
				window->draw(hero.sprite);
				FinalBoss.ShowHealthBar();
			}
			else
			{
				hero.die("");
				hero.state = "BeingStronger";
			}
		}
		else if (scene.scene4ch)
		{
			hero.control = 0;
			if (FinalBoss.health <= 0)
				FinalBoss.health = 2;
			FinalBoss.ShowHealthBar();
			if (FinalBoss.IsStanding)
			{
				FinalBoss.die("defeated");
				FinalBoss.FinalBossDraw(hero);
			}
			else
				scene.scene4(FinalBoss, hero);
		}
		else if (scene.scene5ch)
		{
			hero.control = 0;
			scene.scene5(FinalBoss, hero);
		}
		else if (!IsWining || (int)WinClock.getElapsedTime().asSeconds() < WiningNeedTime)
		{
			hero.control = 1;
			if (hero.health > 0)
			{
				if (FinalBoss.health > 2)
				{
					hero.play();
					hero.DealDamage(FinalBoss.sprite, FinalBoss.health);
					FinalBoss.ChaceAndHit(hero, 1, path, 0);
					window->draw(FinalBoss.sprite);
					window->draw(hero.sprite);
					FinalBoss.ShowHealthBar();
				}
				else if (FinalBoss.health < 1)
					FinalBoss.health = 2;
				else
				{
					if (!IsWining)
						WinClock.restart(), IsWining = 1;
					hero.play();
					//As The Stop hitting Handling is at the (DealDamage()) Function
					if (hero.var == 6)
						hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
					window->draw(te);
					FinalBoss.ChaceAndHit(hero, 1, path, 0);
					window->draw(FinalBoss.sprite);
					window->draw(hero.sprite);
					FinalBoss.ShowHealthBar();
				}
			}
			else
			{
				hero.die("");
				hero.state = "BeingStronger";
				hero.reset();
				FinalBoss.reset();
			}
		}
		else if (scene.scene6ch)
		{
			hero.control = 0;
			hero.walking.pause();
			scene.scene6(FinalBoss, hero);
		}
	}
	////Temp, Control Back Ground Color
	if (hero.InCave)
		return 1;
	else if (hero.IsUpdating)
		return 2;
	else
		return 3;
}
Story::Story(sf::RenderWindow* window)
{
	//Initializing FinalBoss
	FinalBoss.set(500, 400, 100, "FinalBoss", "NoShadow", "NoShield", 1);
	FinalBoss.HitDistance = 100;
	FinalBoss.HitSpeed = 0.07;// As the number decrease the hit speed increase
	FinalBoss.damage = 10;

	//Initializing Hero
	hero.chooseHero();
	hero.set(0, 0, 1);

	//Set Game Scenes
	scene.GameScenesSet(FinalBoss, hero);


	//Count the need time to avoid the FinalBoss and win
	WiningNeedTime = 10; //Time That The Player need to survive while avoiding Siltara's attacks to win
	IsWining = 0;

	//Last Scene instructions
	f.loadFromFile("./res/Fonts/minecraft_font.ttf");
	te.setFont(f);
	te.setString("I Cant kill My best Friend");
	te.setFillColor(Color::White);
	te.setOrigin(te.getLocalBounds().getSize() / 2.f);
	te.setPosition(WindowSize.x / 2, window->getSize().y - te.getCharacterSize() * 5);
	te.setScale(WindowSize.x / 1600, WindowSize.y / 900);
	this->window = window;
	WindowSize = (Vector2f)window->getSize();
}
