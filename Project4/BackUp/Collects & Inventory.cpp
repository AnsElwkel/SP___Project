#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include "HBD.h" 
using namespace std;
using namespace sf;


struct Inventory
{
    int currentWood = 0, currentStones = 0, currentIron = 0, meat = 0;
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
    int weapon_or_mawared_or_nothing = -1; // -1 -> not occupied, 1 -> weapon, 2 -> mawared
    weapons_str weapons;
    mawared_str mawared;
};
item_type inv_items[18];


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


const int INVENTORY_SIZE = 18;
bool inventoryOccupied[INVENTORY_SIZE] = {};
Item inventoryItems[INVENTORY_SIZE];
Texture woodTexture, dropped_stone_texture, dropped_iron_texture, treeTexture, stoneTexture, ironTexture, inventoryTexture;
Inventory inventory;

                                    // Function to add an item to the inventory
int addToInventory(item_type item)
{
    for (int i = 0; i < INVENTORY_SIZE; ++i)
    {
        if(inv_items[i].weapon_or_mawared_or_nothing == -1)
        {
            inv_items[i] = item;
            return i; // Return the index where the item was added
        }
    }
    return -1; // Inventory is full
}

                                        // Function to remove an item from the inventory
void removeFromInventory(int index)
{
    item_type null_item;
    if (index >= 0 && index < INVENTORY_SIZE && inventoryOccupied[index])
    {
        inv_items[index] = null_item;
        inventoryOccupied[index] = false;
        // You may want to reset the item at 'index' to a default value
    }
}

                                        // Function to check if an item is in the inventory
bool isInInventory(item_type item)      // if item is in the inventory and not weapon, try to add it 
{
    // If it is a weapon then it can't be added to another weapon, so break and try to add it in another place 
    if (item.weapon_or_mawared_or_nothing == 1)
        return false;
    for (int i = 0; i < INVENTORY_SIZE; ++i)
    {
        if(inv_items[i].mawared.type == item.mawared.type)
        {
            if(inv_items[i].mawared.quantity<16) // if it is not stack (stack is 16 pieces)
                return true;
        }
    }
    return false;
}

bool full()
{
    int count = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++)
        count += (inv_items[i].weapon_or_mawared_or_nothing != -1); // increment the counter if bolck is occupied
    return (count == INVENTORY_SIZE); // if counter == inventory size, so it is all occupied
}


bool isPlayerBesideObject(const Player& player, const Vector2f& objectPos)
{
    return(abs(player.position.x - objectPos.x) < 90 && abs(player.position.y - objectPos.y) < 90);
}


void PlayerMovement(Player& player)
{
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        if (player.inventory.isOpen)
            player.inventory.isOpen = false;
        player.position.x -= player.speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        if (player.inventory.isOpen)
            player.inventory.isOpen = false;
        player.position.x += player.speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        if (player.inventory.isOpen)
            player.inventory.isOpen = false;
        player.position.y -= player.speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        if (player.inventory.isOpen)
            player.inventory.isOpen = false;
        player.position.y += player.speed;
    }
}
/**********************************************************************************************************************************************/

int findAvailableSlot()
{
    for (int i = 0; i < INVENTORY_SIZE; ++i)
    {
        if(inv_items[i].weapon_or_mawared_or_nothing == -1)
            return i;
    }
    return -1;
}

//                                  FUNCTION    TO   UPDATE    HEALTH    FOR     OBJECT     WHEN    HIT
void updateObjectHealth(Player& player, Tree& tree, Stone& stone, Iron &iron, vector<Wood>& collectedWoods, vector<Stone_collectable>& collectedStones, vector<Iron_collectable>&collectedIrons)
{
    if (&tree != nullptr && tree.health > 0 && isPlayerBesideObject(player, tree.sprite.getPosition()))
    {
        tree.health -= 0.1f;
        if (tree.health <= 0)
        {
            cout << "Tree destroyed, wood dropped!" << endl;
            Wood wood;
            wood.position = tree.sprite.getPosition();
            wood.position.y += 50;
            wood.sprite.setPosition(wood.position.x, wood.position.y);
            wood.collected = false;
            wood.sprite.setTexture(woodTexture);
            collectedWoods.push_back(wood);
            tree.health = 0;
            tree.sprite.setPosition(-1000, -1000);
        }
    }
    if(&stone != nullptr && stone.health > 0 && isPlayerBesideObject(player, stone.sprite.getPosition()))
    {
        stone.health -= 0.05f;
        if(stone.health <= 0)
        {
            cout << "Stone destroyed!";
            Stone_collectable dropped_stone;
            dropped_stone.position = stone.sprite.getPosition();
            dropped_stone.position.y += 30;
            dropped_stone.sprite.setPosition(dropped_stone.position.x, dropped_stone.position.y);
            dropped_stone.collected = false;
            dropped_stone.sprite.setTexture(dropped_stone_texture);
            collectedStones.push_back(dropped_stone);
            stone.health = 0;
            stone.sprite.setPosition(-1000, -1000);
        }
    }
    if(&iron != nullptr && iron.health > 0 && isPlayerBesideObject(player, iron.sprite.getPosition()))
    {
        iron.health -= 0.05f;
        if(iron.health <= 0)
        {
            cout << "Iron destroyed!\n";
            Iron_collectable dropped_iron;
            dropped_iron.position = iron.sprite.getPosition();
            //dropped_iron.position.y+
            dropped_iron.sprite.setPosition(dropped_iron.position.x, dropped_iron.position.y);
            dropped_iron.collected = false;
            dropped_iron.sprite.setTexture(dropped_iron_texture);
            collectedIrons.push_back(dropped_iron);
            iron.health = 0;
            iron.sprite.setPosition(-1000, -1000);
        }
    }
}
/********************************************************************************************************************************************/
//                                  FUNCTION    TO   COLLECT    ITEMS    ON     GROUND
void collectItems(Player& player, vector<Wood>& collectedWoods, vector<Stone_collectable>& collectedStones, vector<Iron_collectable>&collectedIrons)
{
    item_type item;
    for (auto& wood : collectedWoods)
    {
        float distanceSquared = (player.position.x - wood.position.x) * (player.position.x - wood.position.x) +
            (player.position.y - wood.position.y) * (player.position.y - wood.position.y);
        if (!wood.collected && distanceSquared <= 500)
        {
            wood.collected = true;
            item.weapon_or_mawared_or_nothing = 2;
            item.mawared.sprite = wood.sprite;
            item.mawared.type = 1;
            item.mawared.quantity= 10;
            if(isInInventory(item)) // If item is already in inventory add to it the quantity collected
            {
                for(int i = 0; i < INVENTORY_SIZE; i++)
                    if(item.mawared.type == inv_items[i].mawared.type)
                        inv_items[i].mawared.quantity += item.mawared.quantity;
            }
            else
                // Add wood to player's inventory if there is space in inventory
                if(!full())
                {
                    addToInventory(item);
                }
            cout << "Wood collected!" << endl;
            /*Sprite woodSprite;
            woodSprite.setTexture(woodTexture);
            woodSprite.setPosition(findAvailableSlot() * 85, 190);*/
            /*inventory.inventorySlots.push_back(woodSprite);*/
        }
    }
    
    for (auto& dstone : collectedStones)
    {
        float distanceSquared = (player.position.x - dstone.position.x) * (player.position.x - dstone.position.x) +
            (player.position.y - dstone.position.y) * (player.position.y - dstone.position.y);
        if(!dstone.collected && distanceSquared <= 500)
        {
            dstone.collected = true;
            item.weapon_or_mawared_or_nothing = 2;
            item.mawared.sprite = dstone.sprite;
            item.mawared.type = 2;
            item.mawared.quantity = 5;
            if (isInInventory(item))
            {
                for (int i = 0; i < INVENTORY_SIZE; i++)
                    if (item.mawared.type == inv_items[i].mawared.type)
                        inv_items[i].mawared.quantity += item.mawared.quantity;
            }
            else
                if(!full())
                    addToInventory(item);
            cout << "Stone collected!" << endl;
            Sprite stoneSprite;
            /*stoneSprite.setTexture(dropped_stone_texture);
            stoneSprite.setPosition(findAvailableSlot() * 80, 185); */
            /*inventory.inventorySlots.push_back(stoneSprite);*/
        }
    }
    for (auto& diron : collectedIrons)
    {
        float distanceSquared = (player.position.x - diron.position.x) * (player.position.x - diron.position.x) +
            (player.position.y - diron.position.y) * (player.position.y - diron.position.y);
        if(!diron.collected && distanceSquared <= 500)
        {
            diron.collected = true;
            item.weapon_or_mawared_or_nothing = 2;
            item.mawared.sprite = diron.sprite;
            item.mawared.type = 3;
            item.mawared.quantity = 5;
            if(isInInventory(item))
            {
                for(int i = 0; i < INVENTORY_SIZE; i++)
                    if(item.mawared.type == inv_items[i].mawared.type)
                        inv_items[i].mawared.quantity += item.mawared.quantity;
            }
            else
                if(!full())
                    addToInventory(item);
            cout << "iron collected!" << endl;
            Sprite ironSprite;
            ironSprite.setTexture(dropped_iron_texture);
            ironSprite.setScale(0.2f, 0.2f);
            ironSprite.setPosition(findAvailableSlot() * 80, 180);
            /*inventory.inventorySlots.push_back(ironSprite);*/
            // Add stone to player's inventory
        }
    }
}
/***********************************************************************************************************************************************/

vector<Wood> collectedWoods;
vector<Stone_collectable> collectedStones;
vector<Iron_collectable>collectedIrons;

    RenderWindow window(VideoMode(1600, 900), "SFML Tree Example");
    Vector2f WindowSize = (Vector2f)window.getSize();
int main()
{
    Player player = { {100, 100}, 5 };
    window.setFramerateLimit(60);

    if(!woodTexture.loadFromFile("wood1.png") ||
        !treeTexture.loadFromFile("trees-green3.png") ||
        !stoneTexture.loadFromFile("stone 2.png") ||
        !ironTexture.loadFromFile("tower 2.png") ||
        !inventoryTexture.loadFromFile("Inventory.jpg") ||
        !dropped_stone_texture.loadFromFile("stone 4.png") ||
        !dropped_iron_texture.loadFromFile("iron1.png") ||
        !inventory.BlocksTexture.loadFromFile("Blocks.jpg"))
    {
        cout << "Failed to load textures!" << endl;
        return 1;
    }
    Tree tree;
    Stone stone;
    Iron iron;
    inventory.inventorySprite.setTexture(inventoryTexture);
    inventory.inventorySprite.setScale(2.f * WindowSize.x / 1920.f, 2.f * WindowSize.y / 900.f);
    inventory.BlocksSprite.setTexture(inventory.BlocksTexture);
    inventory.BlocksSprite.setScale(2.f*WindowSize.x/1920.f, 2.f * WindowSize.x / 1920.f);
    tree.sprite.setOrigin(tree.sprite.getGlobalBounds().width / 2, tree.sprite.getGlobalBounds().height / 2);
    stone.sprite.setOrigin(stone.sprite.getGlobalBounds().width / 2, stone.sprite.getGlobalBounds().height / 2);
    iron.sprite.setOrigin(iron.sprite.getGlobalBounds().width / 2, iron.sprite.getGlobalBounds().height / 2);
    tree.sprite.setTexture(treeTexture);
    tree.sprite.setPosition(400, 300);
    tree.sprite.getPosition();
    stone.sprite.setTexture(stoneTexture);
    stone.sprite.setPosition(100, 190);
    stone.sprite.getPosition();
    iron.sprite.setTexture(ironTexture);
    iron.sprite.setPosition(100, 90);
    iron.sprite.getPosition();
    //stone.collected = false;
    bool playerBesideTree = false, playerBesideStone = false, playerBesideIron = false;
    bool isInventoryOpen = false;
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font file!" << endl;
        return 1;
    }
    float inventoryWidth = 6 * inventory.BlocksSprite.getGlobalBounds().width * 2.f;
    float inventoryHeight = 3 * inventory.BlocksSprite.getGlobalBounds().height * 2.f;
    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::I)
            {
                if (player.inventory.isOpen)
                {
                    player.inventory.isOpen = false;
                }
                else
                {
                    player.inventory.isOpen = true;
                    player.inventory.inventorySprite.setTexture(inventoryTexture);
                }
            }
        }

        playerBesideTree = isPlayerBesideObject(player, tree.sprite.getPosition());
        playerBesideStone = isPlayerBesideObject(player, stone.sprite.getPosition());
        playerBesideIron = isPlayerBesideObject(player, iron.sprite.getPosition());

        PlayerMovement(player);

        updateObjectHealth(player, tree, stone, iron, collectedWoods, collectedStones, collectedIrons);

        window.clear(Color::White);

        window.draw(tree.sprite);
        window.draw(stone.sprite);
        window.draw(iron.sprite);

        for(auto wood : collectedWoods)
        {
            if(!wood.collected)
                window.draw(wood.sprite);
        }
        for(auto dstone : collectedStones)
        {
            if(!dstone.collected)
                window.draw(dstone.sprite);
        }
        for(auto diron : collectedIrons)
        {
            if(!diron.collected)
            {
                diron.sprite.setScale(0.4f, 0.4f);
                window.draw(diron.sprite);
            }
        }
        CircleShape playerShape(20);
        playerShape.setPosition(player.position);
        playerShape.setFillColor(Color::Blue);
        window.draw(playerShape);
        if(player.inventory.isOpen)
        {
            float initial_width = WindowSize.x / 2.f - 3 * inventory.BlocksSprite.getGlobalBounds().width;
            float cur_width = inventory.BlocksSprite.getGlobalBounds().width;
            float intitial_height = WindowSize.y / 2.f - inventory.BlocksSprite.getGlobalBounds().height;
            float cur_height = inventory.BlocksSprite.getGlobalBounds().height;
            inventory.inventorySprite.setOrigin(inventory.inventorySprite.getGlobalBounds().width / 2.f, inventory.inventorySprite.getGlobalBounds().height / 2.f);
            float inv_width = initial_width - inventory.BlocksSprite.getGlobalBounds().width + inventory.inventorySprite.getGlobalBounds().width;
            float inv_height = intitial_height;
            inventory.inventorySprite.setPosition(inv_width, inv_height);
            window.draw(inventory.inventorySprite);
            for (int i = initial_width, idx = 0; i < initial_width + 6 * cur_width; i += cur_width)
            {
                for(int j = intitial_height; j < intitial_height + 3 * cur_height; j += cur_height, idx++)
                {
                    inventory.BlocksSprite.setPosition(i, j);
                    window.draw(inventory.BlocksSprite);

                    if(inv_items[idx].weapon_or_mawared_or_nothing == 1) // if this block contains a weapon
                    {
                        inv_items[idx].weapons.sprite.setOrigin(inv_items[idx].weapons.sprite.getGlobalBounds().width / 2.f, inv_items[idx].weapons.sprite.getGlobalBounds().height / 2.f);
                        inv_items[idx].weapons.sprite.setPosition(i + inventory.BlocksSprite.getGlobalBounds().width / 2.f, j + inventory.BlocksSprite.getGlobalBounds().height / 2.f);
                        window.draw(inv_items[idx].weapons.sprite);
                    }
                    else if(inv_items[idx].weapon_or_mawared_or_nothing == 2) // contains a mawared
                    {
                        inv_items[idx].mawared.sprite.setOrigin(inv_items[idx].mawared.sprite.getGlobalBounds().width / 2.f, inv_items[idx].mawared.sprite.getGlobalBounds().height / 2.f);
                        inv_items[idx].mawared.sprite.setPosition(i + inventory.BlocksSprite.getGlobalBounds().width / 2.f, j + inventory.BlocksSprite.getGlobalBounds().height / 2.f);
                        window.draw(inv_items[idx].mawared.sprite);
                    }
                }
            }
        }
        collectItems(player, collectedWoods, collectedStones, collectedIrons);

        window.display();
    }
}
