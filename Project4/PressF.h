
#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include"global.h"
#ifndef PressF_H_
#define PressF_H_
using namespace std;
using namespace sf;
extern int WeaponType;
extern int WeaponID;
extern int TARGETDISTANCE;
extern Font pressfont;
extern Text press;
extern char last;
extern float dt;

extern float delay;
extern float timer;
extern int currentIron;
extern int currentWood;
extern int currentMeat;
extern int currentLamb;
extern int currentChicken;
extern Texture foodStoreTex;
extern Sprite foodkoisk;
extern Texture weaponStoreTex;
extern Sprite weaponkoisk;
extern Texture cursorText;
extern Cursor cursor;
extern Vector2f WindowSize;
extern Vector2f WindowPosition;
extern RectangleShape WeaponHealthBar, WeaponHealthBarFrame;

/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

struct Inventory
{
    int currentWood = 100, currentStones = 0, currentIron = 100, meat = 100,lamb = 0,chicken = 0;
    bool isOpen;
    Texture inventoryTexture;
    Sprite inventorySprite;
    Texture BlocksTexture;
    Sprite BlocksSprite;
};
// longSowrd -> 1, Axe -> 2 , Saber -> 3, pickAxe -> 4
// 1st material = 5 ............. 6th material = 10
struct mawared_str
{
    int type;
    int quantity;
    Sprite sprite;
};
struct weapons_str
{
    int type;
    int health = 100;
    Sprite sprite;
};
struct item_type
{
    int weapon_or_mawared_or_nothing = -1; // -1 -> not occupied, 1 -> weapon, 2 -> mawared, 3 -> roasted food
    weapons_str weapons;
    mawared_str mawared;
    Sprite food;

};
extern item_type inv_items[27];
struct Player
{
    Vector2f position;
    float speed;
    Inventory inventory;
};
struct Tree
{

    Sprite sprite;
    int health = 50;
};

struct Stone
{
    Sprite sprite;
    int health = 75;
};

struct Iron
{
    Sprite sprite;
    int health = 100;
};

struct Iron_collectable
{
    Sprite sprite;
    Vector2f position;
    bool collected;
};

struct Stone_collectable
{
    Sprite sprite;
    Vector2f position;
    bool collected;
};

struct Wood
{
    Sprite sprite;
    Vector2f position;
    bool collected;
};

struct Item
{
    string name;
    int quantity;
    int health;
    Vector2f position;
    Sprite sprite;
};

extern bool playerBesideTree, playerBesideStone, playerBesideIron;
extern bool isInventoryOpen;
extern float inventoryWidth;
extern float inventoryHeight;
extern Tree tree;
extern Stone stone;
extern Iron iron;
extern int INVENTORY_SIZE;
extern bool inventoryOccupied[18];
extern Item inventoryItems[18];
extern Texture woodTexture, dropped_stone_texture, dropped_iron_texture, treeTexture, stoneTexture, ironTexture, inventoryTexture;
extern Inventory inventory;
extern Player player;
int addToInventory(item_type item);
// Function to remove an item from the inventory
void removeFromInventory(int index);
void drawInventory();
// Function to check if an item is in the inventory
bool isInInventory(item_type item);     // if item is in the inventory and not weapon, try to add it 
bool full();
bool isPlayerBesideObject(const Player& player, const Vector2f& objectPos);
void PlayerMovement(Player& player);
/**********************************************************************************************************************************************/
int findAvailableSlot();
//                                  FUNCTION    TO   UPDATE    HEALTH    FOR     OBJECT     WHEN    HIT
void updateObjectHealth(Player& player, Tree& tree, Stone& stone, Iron& iron, vector<Wood>& collectedWoods, vector<Stone_collectable>& collectedStones, vector<Iron_collectable>& collectedIrons);
/********************************************************************************************************************************************/
//                                  FUNCTION    TO   COLLECT    ITEMS    ON     GROUND
void collectItems(Sprite& player, vector<Wood>& collectedWoods, vector<Stone_collectable>& collectedStones, vector<Iron_collectable>& collectedIrons);
//********************************************************************************************
extern struct foodDetails
{
	int meatWood = 3, lambWood = 2,chickenWood = 1;
	
	
};
extern struct foodStore
{
	Texture meatText, lambText, chickenText,FoodListText,LockTex;
	Sprite Meat, Lamb, Chicken,FoodList,Lock;
	Text foodName, fooddt;
	foodDetails FoodDetails;
};

extern foodStore food;
extern struct weaponsDetails
{
	int longSowrdIron = 6, maceIron = 3, saberIron = 2;
	int longSowrdWood = 3, warAxeWood = 3, saberWood = 1, maceWood = 2;
	int longSowrdHealth = 100, warAxeHealth = 100, saberHealth = 100, maceHealth = 100;
};
extern struct weaponStore
{
	Texture LongSowrdTex, WarAxeTex, MaceTex, SaberTex,weaponListTex,LockTex;
	Sprite LongSowrd,WarAxe,Mace,Saber,weaponList,Lock;
	Text weaponName, weapondt;
	weaponsDetails WeaponsDetails;
};
extern struct blocks
{
	Texture LongSowrdTexB, WarAxeTexB, MaceTexB, SaberTexB;
	Sprite LongSowrdB, WarAxeB, MaceB, SaberB;
	Texture meatTextB, lambTextB, chickenTextB;
	Sprite MeatB, LambB, ChickenB;
	Texture WeaponBarText;
	Sprite WeaponBarB;

};
extern struct myWeapons
{
	// 1 -> longsword , 2 -> Axe, 3 -> Saber , 4 -> Pickaxe
	int Weapontype, WeaponID, WeaponHealth = 100;
};
extern myWeapons WeaponsBar[4];
extern blocks Blocks;
extern weaponStore weapons;
extern Texture currentWeaponText[4];
extern Sprite currentWeapon[4];
 bool checkDistance(float currentDistance, Sprite mainCharcter, RectangleShape store);
float calcDistance(Sprite mainCharcter, RectangleShape store);
void PressFtoOpenWeapons();
void PressFtoOpenfood();
void displayFoodList();
void  displayWeaponList();
void fonts();
void drawFoodStore(Vector2f pos);
void drawWeaponStore(Vector2f pos);
void  displayWeaponHeroList();
void setCursor();
void setblocks(Texture& blockText, Sprite& blocks);
void HealthBarSet(float x,Vector2f pos);
void pre();
#endif