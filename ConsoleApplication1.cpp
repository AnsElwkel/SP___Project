#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include"CollisionManager.h"
#include "PressF.h"
using namespace std;
using namespace sf;
// variables
vector<Wood> collectedWoods;
vector<Stone_collectable> collectedStones;
vector<Iron_collectable>collectedIrons;

int main()
{
	pre();
	float x = 1; 
	Clock clock;
	inventory.currentIron = 1000;
	inventory.currentWood = 1000;
	fonts();
	setCursor();
	float speed = 0;
	Texture mainCharacterTex;
	mainCharacterTex.loadFromFile("./res/Heros/Ramadan/NoShadow/NoWeapon/Ramadan.png");
	Sprite mainCharacter;
	mainCharacter.setTexture(mainCharacterTex);
	mainCharacter.setTextureRect(IntRect(0, 0, 64, 64));
	drawFoodStore({ 500,500 });
	drawWeaponStore({1500,500});
	while (window.isOpen())
	{
		WindowPosition = (Vector2f)window.getPosition();
		dt = clock.restart().asSeconds();
		delay = 0.15f;
		//timer = 0;
		 speed = 1000 / (1.0 / dt);
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed && e.key.code == Keyboard::I)
			{
				if (player.inventory.isOpen)
				{
					player.inventory.isOpen = false;
				}
				else
				{
					player.inventory.isOpen = true;
				}
			}
		}
		if (last == 'f' or last == 'i')
			window.setMouseCursorVisible(true);
		else 
			window.setMouseCursorVisible(false);

		if (checkDistance(calcDistance(mainCharacter,weaponkoisk),mainCharacter,weaponkoisk))
		{
			if (last == 'f')
			{
				displayWeaponList();

			}
			PressFtoOpenWeapons();
		}
		// test
		if (Keyboard::isKeyPressed(Keyboard::X))
		{
			WeaponsBar[0].WeaponHealth --;
		}
		if (checkDistance(calcDistance(mainCharacter,foodkoisk),mainCharacter,foodkoisk))
		{
		if (last == 'f')
		{
			displayFoodList();
		}
		PressFtoOpenfood();
		}
		displayWeaponHeroList();
			PlayerMovement(player);
			mainCharacter.setPosition(player.position);
			window.draw(mainCharacter);
			window.draw(foodkoisk);
			window.draw(weaponkoisk);
			playerBesideTree = isPlayerBesideObject(player, tree.sprite.getPosition());
			playerBesideStone = isPlayerBesideObject(player, stone.sprite.getPosition());
			playerBesideIron = isPlayerBesideObject(player, iron.sprite.getPosition());
			updateObjectHealth(player, tree, stone, iron, collectedWoods, collectedStones, collectedIrons);
			window.draw(tree.sprite);
			window.draw(stone.sprite);
			window.draw(iron.sprite);

			for (auto wood : collectedWoods)
			{
				if (!wood.collected)
					window.draw(wood.sprite);
			}
			for (auto dstone : collectedStones)
			{
				if (!dstone.collected)
					window.draw(dstone.sprite);
			}
			for (auto diron : collectedIrons)
			{
				if (!diron.collected)
				{
					diron.sprite.setScale(0.4f, 0.4f);
					window.draw(diron.sprite);
				}
			}

		   if (player.inventory.isOpen)
			{
				drawInventory();
				last = 'i';
			}

			collectItems(player, collectedWoods, collectedStones, collectedIrons);
			window.display();
			window.clear();
			delay += dt;	
	}
}