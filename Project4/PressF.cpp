#include "PressF.h"
// Variables
float dt=1/200.0;
int WeaponID = 0;
int WeaponType = 0;
int TARGETDISTANCE = 40000;
Font pressfont;
Text press, weaponName, weapondt, foodName, fooddt;
char last;
blocks Blocks;
foodDetails FoodDetails;
foodStore food;
weaponsDetails WeaponsDetails;
weaponStore weapons;
Vector2f WindowPosition = (Vector2f)window->getPosition();
float delay = 0.15f;
float timer = 0;
int currentIron = 0;
int currentWood = 0;
int currentMeat = 0;
int currentLamb = 0;
int currentChicken = 0;
const int WEAPONSNUMBER = 4;
myWeapons WeaponsBar[WEAPONSNUMBER];
Texture currentWeaponText[WEAPONSNUMBER];
Sprite currentWeapon[WEAPONSNUMBER];
Texture foodStoreTex;
Sprite foodkoisk;
Texture weaponStoreTex;
Sprite weaponkoisk;
Texture cursorText;
Cursor cursor;
RectangleShape WeaponHealthBar, WeaponHealthBarFrame;
///////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
bool checkDistance(float currentDistance, Sprite mainCharcter, Sprite store);
float calcDistance(Sprite mainCharcter, Sprite store);
void PressFtoOpenWeapons();
void displayFoodList();
void setblocks(Texture& blockText, Sprite& blocks,Vector2f pos);
// end
float calcDistance(Sprite mainCharcter, RectangleShape store)
{
	// distance^2 = (x1-x2)^2+(y1-y2)^2
	return pow(mainCharcter.getPosition().x - store.getPosition().x, 2) + pow(mainCharcter.getPosition().y - store.getPosition().y, 2);
}
bool checkDistance(float currentDistance, Sprite mainCharcter, RectangleShape store)
{
	currentDistance = calcDistance(mainCharcter,store);
	if (currentDistance <= TARGETDISTANCE)
		return true;
	else return false;
}
void PressFtoOpenWeapons()
{
	//each block is 72*72
	// fonts
	press.setString("Press F to open");
	weapons.weaponName.setOrigin(weapons.weaponName.getLocalBounds().width / 2.0, weapons.weaponName.getLocalBounds().height / 2.0);
	weapons.weaponName.setPosition(WindowSize.x/2.0, WindowSize.x / 1920.f * 100);
	weapons.weapondt.setCharacterSize(24*WindowSize.x/1920.f);
	weapons.weapondt.setPosition(0, 200* WindowSize.x / 1920.f);
	// end fonts
	if (last != 'f')
	{
		window->draw(press);
	}
	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		last = 'f';
		// add sound here
	}
	// lock
	if (last == 'f')
	{
		if (weapons.WeaponsDetails.longSowrdIron > inventory.currentIron or weapons.WeaponsDetails.longSowrdWood > inventory.currentWood)
		{
			weapons.Lock.setPosition(Blocks.LongSowrdB.getPosition());
			window->draw(weapons.Lock);
		}
		if (weapons.WeaponsDetails.warAxeWood > inventory.currentWood)
		{
			weapons.Lock.setPosition(Blocks.WarAxeB.getPosition());
			window->draw(weapons.Lock);
		}
		if (weapons.WeaponsDetails.saberIron > inventory.currentIron or weapons.WeaponsDetails.saberWood > inventory.currentWood)
		{
			weapons.Lock.setPosition(Blocks.SaberB.getPosition());
			window->draw(weapons.Lock);
		}
		if (weapons.WeaponsDetails.maceIron > inventory.currentIron or weapons.WeaponsDetails.maceWood > inventory.currentWood)
		{
			weapons.Lock.setPosition(Blocks.MaceB.getPosition());
			window->draw(weapons.Lock);
		}
	}
	if (last == 'f' and Blocks.LongSowrdB.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y))
	{
		weapons.weaponName.setString("Long Sword");
		weapons.weapondt.setString("Iron x" + to_string(weapons.WeaponsDetails.longSowrdIron)+"\n" + "wood x" + to_string(weapons.WeaponsDetails.longSowrdWood)+"\n"+"health: "+ to_string(weapons.WeaponsDetails.longSowrdHealth));
		window->draw(weapons.weapondt);
		window->draw(weapons.weaponName);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (timer < 0)
			{
				if (weapons.WeaponsDetails.longSowrdIron <= inventory.currentIron and weapons.WeaponsDetails.longSowrdWood <= inventory.currentWood)
				{
					inventory.currentIron -= weapons.WeaponsDetails.longSowrdIron;
					inventory.currentWood -= weapons.WeaponsDetails.longSowrdWood;
					for (int i = 0; i < INVENTORY_SIZE; i++)
						if (1 == inv_items[i].mawared.type)
						{
							inv_items[i].mawared.quantity -= weapons.WeaponsDetails.longSowrdWood;
							if (inv_items[i].mawared.quantity == 0)
							{
								removeFromInventory(i);
							}
						}
					for (int i = 0; i < INVENTORY_SIZE; i++)
						if (3 == inv_items[i].mawared.type)
						{
							inv_items[i].mawared.quantity -= weapons.WeaponsDetails.longSowrdIron;
							if (inv_items[i].mawared.quantity == 0)
							{
								removeFromInventory(i);
							}
						}
					inventory.currentWood -= weapons.WeaponsDetails.longSowrdWood;
					inventory.currentIron -= weapons.WeaponsDetails.longSowrdIron;
					item_type longSowrd = { 1,{1,100,weapons.LongSowrd}};
					addToInventory(longSowrd);

				}
					timer = delay;
			//cout << currentIron << '\n';
			}
			else
				timer -= dt;
		
		}
	}
	else if (last == 'f' and Blocks.WarAxeB.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
	{
		weapons.weaponName.setString("War Axe");
		weapons.weapondt.setString("wood x" + to_string(weapons.WeaponsDetails.warAxeWood) + "\n" + "health: " + to_string(weapons.WeaponsDetails.warAxeHealth));
		window->draw(weapons.weapondt);
		window->draw(weapons.weaponName);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (timer < 0)
			{
				if(weapons.WeaponsDetails.warAxeWood <= inventory.currentWood)
				{
					for (int i = 0; i < INVENTORY_SIZE; i++)
						if (1 == inv_items[i].mawared.type)
						{
							inv_items[i].mawared.quantity -= weapons.WeaponsDetails.warAxeWood;
							if (inv_items[i].mawared.quantity == 0)
							{
								removeFromInventory(i);
							}
						}
					inventory.currentWood -= weapons.WeaponsDetails.warAxeWood;
					item_type waraxe = { 1,{2,100,weapons.WarAxe} };
					addToInventory(waraxe);
				}
				timer = delay;
				cout << currentIron << '\n';
			}
			else
				timer -= dt;

		}
	}
	else if (last == 'f' and Blocks.SaberB.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
	{
		weapons.weaponName.setString("Saber");
		weapons.weapondt.setString("Iron x" + to_string(weapons.WeaponsDetails.saberIron) + "\n" + "wood x" + to_string(weapons.WeaponsDetails.saberWood) + "\n" + "health: " + to_string(weapons.WeaponsDetails.saberHealth));
		window->draw(weapons.weapondt);
		window->draw(weapons.weaponName);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (timer < 0)
			{
				if (weapons.WeaponsDetails.saberIron <= inventory.currentIron and weapons.WeaponsDetails.saberWood <= inventory.currentWood)
				{
					inventory.currentIron -= weapons.WeaponsDetails.saberIron;
					inventory.currentWood -= weapons.WeaponsDetails.saberWood;
					for (int i = 0; i < INVENTORY_SIZE; i++)
						if (1 == inv_items[i].mawared.type)
						{
							inv_items[i].mawared.quantity -= weapons.WeaponsDetails.saberWood;
							if (inv_items[i].mawared.quantity == 0)
							{
								removeFromInventory(i);
							}
						}
					for (int i = 0; i < INVENTORY_SIZE; i++)
						if (3 == inv_items[i].mawared.type)
						{
							inv_items[i].mawared.quantity -= weapons.WeaponsDetails.saberIron;
							if (inv_items[i].mawared.quantity == 0)
							{
								removeFromInventory(i);
							}
						}
					inventory.currentWood -= weapons.WeaponsDetails.saberWood;
					inventory.currentIron -= weapons.WeaponsDetails.saberIron;
					item_type saber = { 1,{3,100,weapons.Saber} };
					addToInventory(saber);
				}
					timer = delay;
				cout << currentIron << '\n';
			}
			else
				timer -= dt;

		}
	}
	else if (last == 'f' and Blocks.MaceB.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
	{
		weapons.weaponName.setString("Mace");
		weapons.weapondt.setString("Iron x" + to_string(weapons.WeaponsDetails.maceIron) + "\n" + "wood x" + to_string(weapons.WeaponsDetails.maceWood) + "\n" + "health: " + to_string(weapons.WeaponsDetails.maceHealth));
		window->draw(weapons.weapondt);
		window->draw(weapons.weaponName);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (timer < 0)
			{
				if (weapons.WeaponsDetails.maceIron <= inventory.currentIron and weapons.WeaponsDetails.maceWood <= inventory.currentWood)
				{
					inventory.currentIron -= weapons.WeaponsDetails.maceIron;
					inventory.currentWood -= weapons.WeaponsDetails.maceWood;
					for (int i = 0; i < INVENTORY_SIZE; i++)
						if (1 == inv_items[i].mawared.type)
						{
							inv_items[i].mawared.quantity -= weapons.WeaponsDetails.maceWood;
							if (inv_items[i].mawared.quantity == 0)
							{
								removeFromInventory(i);
							}
						}
					for (int i = 0; i < INVENTORY_SIZE; i++)
						if (3 == inv_items[i].mawared.type)
						{
							inv_items[i].mawared.quantity -= weapons.WeaponsDetails.maceIron;
							if (inv_items[i].mawared.quantity == 0)
							{
								removeFromInventory(i);
							}
						}
					inventory.currentWood -= weapons.WeaponsDetails.maceWood;
					inventory.currentIron -= weapons.WeaponsDetails.maceIron;
					item_type mace = { 1,{4,100,weapons.Mace} };
					addToInventory(mace);
				}
					timer = delay;
			}
			else
				timer -= dt;

		}
	}
}
void PressFtoOpenfood()
{
	//each block is 72*72
	// fonts
	food.foodName.setOrigin(food.foodName.getLocalBounds().width / 2.0, food.foodName.getLocalBounds().height / 2.0);
	food.foodName.setPosition(WindowSize.x / 2.0, 100 * WindowSize.x / 1920.f);
	food.fooddt.setPosition(0, 200 * WindowSize.x / 1920.f);
	food.fooddt.setCharacterSize(24 * WindowSize.x / 1920.f);
	// end fonts
	press.setString("Press F to open");

	if (last != 'f')
		window->draw(press);
	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		last = 'f';
		// add sound here
	}
	// lock
	if (last == 'f')
	{
		if (food.FoodDetails.meatWood > inventory.currentWood or inventory.meat == 0)
		{
			food.Lock.setPosition(Blocks.MeatB.getPosition());
			window->draw(food.Lock);
		}
		if (food.FoodDetails.lambWood > inventory.currentWood or inventory.lamb == 0)
		{
			food.Lock.setPosition(Blocks.LambB.getPosition());
			window->draw(food.Lock);
		}
		if (food.FoodDetails.chickenWood > inventory.currentWood or inventory.chicken == 0)
		{
			food.Lock.setPosition(Blocks.ChickenB.getPosition());
			window->draw(food.Lock);
		}
	}
	if (last == 'f' and Blocks.MeatB.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
	{
		food.foodName.setString("Meat");
		food.fooddt.setString("Meat x1\nwood x" + to_string(food.FoodDetails.meatWood));
		window->draw(food.fooddt);
		window->draw(food.foodName);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (timer < 0)
			{
				if (food.FoodDetails.meatWood <= inventory.currentWood and inventory.meat >= 0)
				{
					inventory.meat--;
					inventory.currentWood -= food.FoodDetails.meatWood;
					item_type Meat;
					Meat.weapon_or_mawared_or_nothing = 3;
					Meat.food = food.Meat;
					addToInventory(Meat);
				}
				timer = delay;
				cout << currentMeat << '\n';
			}
			else
				timer -= dt;

		}
	}
	else if (last == 'f' and Blocks.LambB.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
	{
		food.foodName.setString("Lamb");
		food.fooddt.setString("Lamb x1\nwood x" + to_string(food.FoodDetails.lambWood));
		window->draw(food.fooddt);
		window->draw(food.foodName);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (timer < 0)
			{
				if (food.FoodDetails.lambWood <= inventory.currentWood and inventory.lamb >= 0)
				{
					inventory.lamb--;
					inventory.currentWood -= food.FoodDetails.lambWood;
					item_type Lamb;
					Lamb.weapon_or_mawared_or_nothing = 3;
					Lamb.food = food.Lamb;
					addToInventory(Lamb);
				}
				timer = delay;
				cout << currentLamb << '\n';
			}
			else
				timer -= dt;

		}
	}
	else if (last == 'f' and Blocks.ChickenB.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
	{
		food.foodName.setString("Chicken");
		food.fooddt.setString("Chicken x1\nwood x" + to_string(food.FoodDetails.chickenWood));
		window->draw(food.fooddt);
		window->draw(food.foodName);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (timer < 0)
			{
				if (food.FoodDetails.chickenWood <= inventory.currentWood and inventory.chicken >= 0)
				{
					inventory.chicken--;
					inventory.currentWood -= food.FoodDetails.chickenWood;
					item_type chicken;
					chicken.weapon_or_mawared_or_nothing = 3;
					chicken.food = food.Chicken;
					addToInventory(chicken);

				}
				timer = delay;
				cout << currentChicken << '\n';
			}
			else
				timer -= dt;

		}
	}
	
}
void setblocks(Texture& blockText, Sprite& blocks,Vector2f pos)
{
	blockText.loadFromFile("./res./weapons/list - Copy.jpg");
	blocks.setTexture(blockText);
	blocks.setPosition(pos);
	blocks.setScale(2.f * WindowSize.x / 1920.f, 2.f * WindowSize.x / 1920.f);
	window->draw(blocks);
}
void  displayWeaponList()
{
	// weapon list
	setblocks(Blocks.LongSowrdTexB, Blocks.LongSowrdB, { WindowSize.x / 2.f - 2 * Blocks.LongSowrdB.getGlobalBounds().width, 0 * WindowSize.x / 1920.f });
	setblocks(Blocks.WarAxeTexB, Blocks.WarAxeB, { WindowSize.x / 2.f - Blocks.WarAxeB.getGlobalBounds().width, 0 * WindowSize.x / 1920.f });
	setblocks(Blocks.MaceTexB, Blocks.SaberB, { WindowSize.x / 2.f, 0 * WindowSize.x / 1920.f });
	setblocks(Blocks.SaberTexB, Blocks.MaceB, { WindowSize.x / 2.f + Blocks.SaberB.getGlobalBounds().width, 0 * WindowSize.x / 1920.f });

	// long sword
	weapons.LongSowrdTex.loadFromFile("./res/weapons/long_sword.png");
	weapons.LongSowrd.setTexture(weapons.LongSowrdTex);
	weapons.LongSowrd.setOrigin(weapons.LongSowrd.getLocalBounds().width / 2.0, weapons.LongSowrd.getLocalBounds().height / 2.0);
	weapons.LongSowrd.setPosition(Blocks.LongSowrdB.getPosition().x + Blocks.LongSowrdB.getGlobalBounds().width / 2.f, Blocks.LongSowrdB.getPosition().y + Blocks.LongSowrdB.getGlobalBounds().height / 2.f);
	weapons.LongSowrd.setScale(0.8f * (WindowSize.x / 1920.f), 0.8f * (WindowSize.y / 1080.f));
	window->draw(weapons.LongSowrd);
	// war axe
	weapons.WarAxeTex.loadFromFile("./res/weapons/waraxe.png");
	weapons.WarAxe.setTexture(weapons.WarAxeTex);
	weapons.WarAxe.setOrigin(weapons.WarAxe.getLocalBounds().width / 2.0, weapons.WarAxe.getLocalBounds().height / 2.0);
	weapons.WarAxe.setPosition(Blocks.WarAxeB.getPosition().x + Blocks.WarAxeB.getGlobalBounds().width / 2.f, Blocks.WarAxeB.getPosition().y + Blocks.WarAxeB.getGlobalBounds().height / 2.f);
	weapons.WarAxe.setScale(0.8f * (WindowSize.x / 1920.f), 0.8f * (WindowSize.y / 1080.f));
	window->draw(weapons.WarAxe);
	// saber
	weapons.SaberTex.loadFromFile("./res/weapons/saber.png");
	weapons.Saber.setTexture(weapons.SaberTex);
	weapons.Saber.setOrigin(weapons.WarAxe.getLocalBounds().width / 2.0, weapons.WarAxe.getLocalBounds().height / 2.0);
	weapons.Saber.setPosition(Blocks.SaberB.getPosition().x + Blocks.SaberB.getGlobalBounds().width / 2.f, Blocks.SaberB.getPosition().y + Blocks.SaberB.getGlobalBounds().height / 2.f);
	weapons.Saber.setScale(0.7f * (WindowSize.x / 1920.f), 0.7f * (WindowSize.y / 1080.f));
	window->draw(weapons.Saber);
	// Mace
	weapons.MaceTex.loadFromFile("./res/weapons/mace.png");
	weapons.Mace.setTexture(weapons.MaceTex);
	weapons.Mace.setOrigin(weapons.WarAxe.getLocalBounds().width / 2.0, weapons.WarAxe.getLocalBounds().height / 2.0);
	weapons.Mace.setPosition(Blocks.MaceB.getPosition().x + Blocks.MaceB.getGlobalBounds().width / 2.f, Blocks.MaceB.getPosition().y + Blocks.MaceB.getGlobalBounds().height / 2.f);
	weapons.Mace.setScale(0.8f * (WindowSize.x / 1920.f), 0.8f * (WindowSize.y / 1080.f));
	window->draw(weapons.Mace);
	// lock
	weapons.LockTex.loadFromFile("./res/weapons/lock.png");
	weapons.Lock.setTexture(weapons.LockTex);
	weapons.Lock.setScale(0.35f * (WindowSize.x / 1920.f), 0.35f * (WindowSize.y / 1080.f));
}
void displayFoodList()
{
	// food list
	setblocks(Blocks.meatTextB, Blocks.MeatB, { WindowSize.x / 2.f - 1.5f * Blocks.MeatB.getGlobalBounds().width, 0 * WindowSize.x / 1920.f });
	setblocks(Blocks.lambTextB, Blocks.LambB, { WindowSize.x / 2.f - 0.5f * Blocks.LambB.getGlobalBounds().width, 0 * WindowSize.x / 1920.f });
	setblocks(Blocks.chickenTextB, Blocks.ChickenB, { WindowSize.x / 2.f + 0.5f * Blocks.ChickenB.getGlobalBounds().width, 0 * WindowSize.x / 1920.f });
	// meat
	food.meatText.loadFromFile("./res/food/meat.png");
	food.Meat.setTexture(food.meatText);
	food.Meat.setOrigin(food.Meat.getLocalBounds().width / 2.0, food.Meat.getLocalBounds().height / 2.0);
	food.Meat.setPosition(Blocks.MeatB.getPosition().x + Blocks.MeatB.getGlobalBounds().width / 2.f, Blocks.MeatB.getPosition().y + Blocks.MeatB.getGlobalBounds().height / 2.f);
	food.Meat.setScale(0.7f * WindowSize.x / 1920.f, 0.7f * WindowSize.x / 1920.f);
	window->draw(food.Meat);
	// lamb
	food.lambText.loadFromFile("./res/food/lamb.png");
	food.Lamb.setTexture(food.lambText);
	food.Lamb.setOrigin(food.Lamb.getLocalBounds().width / 2.0, food.Lamb.getLocalBounds().height / 2.0);
	food.Lamb.setPosition(Blocks.LambB.getPosition().x + Blocks.LambB.getGlobalBounds().width / 2.f, Blocks.LambB.getPosition().y + Blocks.LambB.getGlobalBounds().height / 2.f);
	food.Lamb.setScale(0.85f * WindowSize.x / 1920.f, 0.85f * WindowSize.x / 1920.f);
	window->draw(food.Lamb);
	// chicken
	food.chickenText.loadFromFile("./res/food/chicken.png");
	food.Chicken.setTexture(food.chickenText);
	food.Chicken.setOrigin(food.Chicken.getLocalBounds().width / 2.0, food.Chicken.getLocalBounds().height / 2.0);
	food.Chicken.setPosition(Blocks.ChickenB.getPosition().x + Blocks.ChickenB.getGlobalBounds().width / 2.f, Blocks.ChickenB.getPosition().y + Blocks.ChickenB.getGlobalBounds().height / 2.f);
	food.Chicken.setScale(0.75f * WindowSize.x / 1920.f, 0.75f * WindowSize.x / 1920.f);
	window->draw(food.Chicken);
	// lock
	food.LockTex.loadFromFile("./res/weapons/lock.png");
	food.Lock.setTexture(food.LockTex);
	food.Lock.setScale(0.35f * (WindowSize.x / 1920.f), 0.35f * (WindowSize.y / 1080.f));
}
void fonts()
{
	pressfont.loadFromFile("./res/Fonts/Press F.otf");
	press.setFont(pressfont);
	weapons.weaponName.setFont(pressfont);
	weapons.weapondt.setFont(pressfont);
	food.foodName.setFont(pressfont);
	food.fooddt.setFont(pressfont);
	press.setCharacterSize(WindowSize.x/1920.f*48);
	
}
void drawFoodStore(Vector2f pos)
{
	foodStoreTex.loadFromFile("./res/food/foodStore.png");
	foodkoisk.setTexture(foodStoreTex);
	foodkoisk.setPosition(pos);
	foodkoisk.setOrigin(foodkoisk.getGlobalBounds().width/2.0, foodkoisk.getGlobalBounds().height / 2.0);
	foodkoisk.setScale(0.2f*WindowSize.x/1920.f, 0.2f* WindowSize.x / 1920.f);
}
void drawWeaponStore(Vector2f pos)
{
	weaponStoreTex.loadFromFile("./res/weapons/weaponStore.png");
	weaponkoisk.setTexture(weaponStoreTex);
	weaponkoisk.setPosition(pos);
	weaponkoisk.setOrigin(weaponkoisk.getGlobalBounds().width / 2.0, weaponkoisk.getGlobalBounds().height / 2.0);
	weaponkoisk.setScale(0.3f*WindowSize.x/1920.f, 0.3f*WindowSize.x / 1920.f);
}
void  displayWeaponHeroList()
{
	
		
	for (int i = 0; i < WEAPONSNUMBER; i++)
	{
		setblocks(Blocks.WeaponBarText, Blocks.WeaponBarB, { WindowSize.x / 2.f-2*Blocks.WeaponBarB.getGlobalBounds().width+i* Blocks.WeaponBarB.getGlobalBounds().width,WindowSize.y- Blocks.WeaponBarB.getGlobalBounds().height});
	}
	for (int i = 0; i < WEAPONSNUMBER; i++)
	{
		if (WeaponsBar[i].WeaponHealth <= 0)
		{
			WeaponsBar[i].Weapontype = 0;
			WeaponsBar[i].WeaponHealth = 100;
		}
	}
	for (int idx = 0; idx < INVENTORY_SIZE; idx++)
	{
		if (inv_items[idx].weapon_or_mawared_or_nothing == 1) // if this block contains a weapon
		{
			if (inv_items[idx].weapons.type == 1)
			{
				if (WeaponsBar[0].Weapontype == 0)
				{
					WeaponsBar[0].Weapontype = 1;
					removeFromInventory(idx);
				}
			}
			else if (inv_items[idx].weapons.type == 2)
			{
				if (WeaponsBar[1].Weapontype == 0)
				{
					WeaponsBar[1].Weapontype = 2;
					removeFromInventory(idx);
				}
			}
			else if (inv_items[idx].weapons.type == 3)
			{
				if (WeaponsBar[2].Weapontype == 0)
				{
					WeaponsBar[2].Weapontype = 3;
					removeFromInventory(idx);
				}
			}
			else if (inv_items[idx].weapons.type == 4)
			{
				if (WeaponsBar[3].Weapontype == 0)
				{
					WeaponsBar[3].Weapontype = 4;
					removeFromInventory(idx);
				}
			}
		}
	}
	for (int i = 0; i < WEAPONSNUMBER; i++)
	{

		if (WeaponsBar[i].Weapontype == 0)
			continue;
		if (WeaponsBar[i].Weapontype == 1)
		{
			currentWeaponText[i].loadFromFile("./res/weapons/long_sword.png");
		}
		else if(WeaponsBar[i].Weapontype == 2)
		{
			currentWeaponText[i].loadFromFile("./res/weapons/waraxe.png");
		}
		else if (WeaponsBar[i].Weapontype == 3)
		{
			currentWeaponText[i].loadFromFile("./res/weapons/saber.png");
		}
		else if (WeaponsBar[i].Weapontype == 4)
		{
			currentWeaponText[i].loadFromFile("./res/weapons/mace.png");
		}
			currentWeapon[i].setTexture(currentWeaponText[i]);
			currentWeapon[i].setOrigin(currentWeapon[i].getLocalBounds().width / 2.0, currentWeapon[i].getLocalBounds().height / 2.0);
			currentWeapon[i].setPosition(WindowSize.x / 2.f - 2 * Blocks.WeaponBarB.getGlobalBounds().width + i * Blocks.WeaponBarB.getGlobalBounds().width + Blocks.WeaponBarB.getGlobalBounds().width / 2.f, WindowSize.y - Blocks.WeaponBarB.getGlobalBounds().height + Blocks.WeaponBarB.getGlobalBounds().height / 2.f);
			currentWeapon[i].setScale(0.8f * (WindowSize.x / 1920.f), 0.8f * (WindowSize.y / 1080.f));
			window->draw(currentWeapon[i]);
			HealthBarSet(WeaponsBar[i].WeaponHealth, {WindowSize.x / 2.f - 2 * Blocks.WeaponBarB.getGlobalBounds().width + i * Blocks.WeaponBarB.getGlobalBounds().width,WindowSize.y - Blocks.WeaponBarB.getGlobalBounds().height});
	}

}
void HealthBarSet(float x,Vector2f pos)
{
	float BlockSize = 72*WindowSize.x/1920.f;
	WeaponHealthBar.setSize({ BlockSize*x/100.f, 5.f*WindowSize.x/1600.f});
	WeaponHealthBar.setOrigin(0, WeaponHealthBar.getLocalBounds().getSize().y);
	WeaponHealthBar.setPosition(pos.x, pos.y+ BlockSize);
	WeaponHealthBar.setFillColor(Color::Green);
	WeaponHealthBarFrame.setSize({ Blocks.LongSowrdB.getGlobalBounds().width, 5.f * WindowSize.x / 1600.f });
	WeaponHealthBarFrame.setScale(WeaponHealthBar.getScale());
	WeaponHealthBarFrame.setOutlineThickness(1.4f);
	WeaponHealthBarFrame.setOrigin(WeaponHealthBar.getOrigin());
	WeaponHealthBarFrame.setPosition(WeaponHealthBar.getPosition());
	WeaponHealthBarFrame.setOutlineColor(Color::Blue);
	WeaponHealthBarFrame.setFillColor(Color::Transparent);
	window->draw(WeaponHealthBar);
	window->draw(WeaponHealthBarFrame);
	
}
void setCursor()
{
	cursorText.loadFromFile("./res/weapons/cursor.png");
	cursor.loadFromPixels(cursorText.copyToImage().getPixelsPtr(), cursorText.getSize(), { 0,0 });
	window->setMouseCursor(cursor);
}