#include "PressF.h"
#include"global.h"
#include"tile.h"
int INVENTORY_SIZE = 18;
bool inventoryOccupied[18];
Item inventoryItems[18];
Texture woodTexture, dropped_stone_texture, dropped_iron_texture, treeTexture, stoneTexture, ironTexture, inventoryTexture;
Inventory inventory;
Tree tree;
Stone stone;
Iron iron;
item_type inv_items[27];
Player player = { {100, 100}, 5 };
bool playerBesideTree = false, playerBesideStone = false, playerBesideIron = false;
bool isInventoryOpen = false;
float inventoryWidth = 6 * inventory.BlocksSprite.getGlobalBounds().width * 2.f;
float inventoryHeight = 3 * inventory.BlocksSprite.getGlobalBounds().height * 2.f;
void pre()
{
    inventory.BlocksTexture.loadFromFile("./res/weapons/list - Copy.png");
    inventory.BlocksSprite.setTexture(inventory.BlocksTexture);
    //inventory.inventoryTexture.loadFromFile("./res/weapons/inventory.");
    inventory.inventorySprite.setTexture(inventoryTexture);
    inventory.inventorySprite.setScale(2.f * WindowSize.x / 1920.f, 2.f * WindowSize.y / 1080.f);
    window->draw(inventory.inventorySprite);
    inventory.BlocksSprite.setScale(2.f * WindowSize.x / 1920.f, 2.f * WindowSize.x / 1920.f);
    treeTexture.loadFromFile("./res/used res/trees-green3.png");
    stoneTexture.loadFromFile("./used res/stone 2.png");
    ironTexture.loadFromFile("./used res/tower 2.png");
    tree.sprite.setOrigin(tree.sprite.getGlobalBounds().width / 2, tree.sprite.getGlobalBounds().height / 2);
    stone.sprite.setOrigin(stone.sprite.getGlobalBounds().width / 2, stone.sprite.getGlobalBounds().height / 2);
    iron.sprite.setOrigin(iron.sprite.getGlobalBounds().width / 2, iron.sprite.getGlobalBounds().height / 2);
    tree.sprite.setTexture(treeTexture);
    tree.sprite.setPosition(400, 800);
    tree.sprite.getPosition();
    tex.loadFromFile("./res/food/rawmeat.png");
    rawmeat.setTexture(tex);
    stone.sprite.setTexture(stoneTexture);
    stone.sprite.setPosition(100, 190);
    stone.sprite.getPosition();
    iron.sprite.setTexture(ironTexture);
    iron.sprite.setPosition(100, 90);
    iron.sprite.getPosition();
    woodTexture.loadFromFile("./res/res/used res/wood1.png");
    dropped_stone_texture.loadFromFile("./res/res/used res/stone 4.png");
    dropped_iron_texture.loadFromFile("./res/Iron.png");
    //stone.collected = false;

}

// Function to add an item to the inventory
int addToInventory(item_type item)
{
    for (int i = 0; i < INVENTORY_SIZE; ++i)
    {
        if (inv_items[i].weapon_or_mawared_or_nothing == -1)
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
    inv_items[index] = null_item;
    // You may want to reset the item at 'index' to a default value

}
// the magic function from number one HHHHHHHHhhhhhhhhhhhh 
void drawInventory()
{
    Texture invt;
    invt.loadFromFile("./res/inv.png");
    Sprite inv;
    inv.setTexture(invt);
    inventory.BlocksSprite.setScale(2 * WindowSize.x / 1920.f, 2 * WindowSize.x / 1920.f);

    float initial_width = WindowSize.x / 2.f - 4.f * inventory.BlocksSprite.getGlobalBounds().width;
    float cur_width = inventory.BlocksSprite.getGlobalBounds().width;
    float intitial_height = WindowSize.y / 2.f - inventory.BlocksSprite.getGlobalBounds().height;
    float cur_height = inventory.BlocksSprite.getGlobalBounds().height;
    inv.setPosition(initial_width - 5.f, intitial_height - 0.5 * cur_height - 10);

    window->draw(inv);
    RectangleShape eat, drop;
    Text eatf, dropf, counter;
    counter.setFont(pressfont);
    eatf.setFont(pressfont);
    dropf.setFont(pressfont);
    eatf.setCharacterSize(12.f * WindowSize.x / 1920.f);
    dropf.setCharacterSize(12.f * WindowSize.x / 1920.f);
    counter.setCharacterSize(20.f * WindowSize.x / 1920.f);
    counter.setFillColor(Color::Black);
    counter.setOrigin(counter.getGlobalBounds().width / 2.f, counter.getGlobalBounds().height / 2.f);
    for (int i = initial_width, idx = 0; i < initial_width + 8 * cur_width; i += cur_width)
    {
        for (int j = intitial_height; j < intitial_height + 3 * cur_height; j += cur_height, idx++)
        {
            inventory.BlocksSprite.setPosition(i, j);
            window->draw(inventory.BlocksSprite);
            if (inv_items[idx].mawared.quantity > 0)
            {
                counter.setString(to_string(inv_items[idx].mawared.quantity));
                counter.setPosition(i + inventory.BlocksSprite.getGlobalBounds().width - counter.getGlobalBounds().width - 10, j + inventory.BlocksSprite.getGlobalBounds().height - counter.getGlobalBounds().height - 15);
            }
            if (inv_items[idx].weapon_or_mawared_or_nothing == 1) // if this block contains a weapon
            {
                inv_items[idx].weapons.sprite.setPosition(i + inventory.BlocksSprite.getGlobalBounds().width / 2.f, j + inventory.BlocksSprite.getGlobalBounds().height / 2.f);
                window->draw(inv_items[idx].weapons.sprite);
                HealthBarSet(inv_items[idx].weapons.health, { (float)i,(float)j });
                if (inventory.BlocksSprite.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
                {
                    drop.setSize({ inventory.BlocksSprite.getGlobalBounds().width, 15 * WindowSize.x / 1920.f });
                    drop.setPosition(i, j + inventory.BlocksSprite.getGlobalBounds().height - drop.getGlobalBounds().height);
                    drop.setFillColor(Color::Red);
                    dropf.setString("drop");
                    dropf.setPosition(drop.getPosition().x + drop.getGlobalBounds().width / 4.f, drop.getPosition().y);
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        removeFromInventory(idx);
                    }
                }

            }
            else if (inv_items[idx].weapon_or_mawared_or_nothing == 2) // contains a mawared
            {
                if (inv_items[idx].mawared.type == 3)
                {
                    inv_items[idx].mawared.sprite.setPosition(i, j);

                }
                else
                {
                    inv_items[idx].mawared.sprite.setOrigin(inv_items[idx].mawared.sprite.getGlobalBounds().width / 2.f, inv_items[idx].mawared.sprite.getGlobalBounds().height / 2.f);
                    inv_items[idx].mawared.sprite.setPosition(i + inventory.BlocksSprite.getGlobalBounds().width / 2.f, j + inventory.BlocksSprite.getGlobalBounds().height / 2.f);
                    inv_items[idx].mawared.sprite.setScale(0.8f, 0.8f);
                }
                window->draw(inv_items[idx].mawared.sprite);
                if (inventory.BlocksSprite.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
                {
                    drop.setSize({ inventory.BlocksSprite.getGlobalBounds().width, 15 * WindowSize.x / 1920.f });
                    drop.setPosition(i, j + inventory.BlocksSprite.getGlobalBounds().height - drop.getGlobalBounds().height);
                    drop.setFillColor(Color::Red);
                    dropf.setString("drop");
                    dropf.setPosition(drop.getPosition().x + drop.getGlobalBounds().width / 4.f, drop.getPosition().y);
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        removeFromInventory(idx);
                    }
                }

            }
            else if (inv_items[idx].weapon_or_mawared_or_nothing == 3) // if this block contains a roasted food
            {
                inv_items[idx].food.setPosition(i + inventory.BlocksSprite.getGlobalBounds().width / 2.f, j + inventory.BlocksSprite.getGlobalBounds().height / 2.f);
                window->draw(inv_items[idx].food);
                if (inventory.BlocksSprite.getGlobalBounds().contains((Vector2f)Mouse::getPosition(*window)))
                {
                    eat.setSize({ inventory.BlocksSprite.getGlobalBounds().width / 2.f, 15 * WindowSize.x / 1920.f });
                    eat.setPosition(i, j + inventory.BlocksSprite.getGlobalBounds().height - eat.getGlobalBounds().height);
                    eat.setFillColor(Color::Green);
                    eatf.setString("eat");
                    eatf.setPosition(eat.getPosition());
                   
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        removeFromInventory(idx);
                        click = 1;
                    }
                }
            }
            else if (inv_items[idx].weapon_or_mawared_or_nothing == 4) // if this block contains a roasted food
            {
                inv_items[idx].food.setPosition(i + inventory.BlocksSprite.getGlobalBounds().width / 2.f, j + inventory.BlocksSprite.getGlobalBounds().height / 2.f);
                window->draw(inv_items[idx].food);
             

            }



            window->draw(eat);
            window->draw(drop);
            window->draw(eatf);
            window->draw(dropf);
            window->draw(counter);

        }
    }
}
bool isInInventory(item_type item)      // if item is in the inventory and not weapon, try to add it 
{
    // If it is a weapon then it can't be added to another weapon, so break and try to add it in another place 
    if (item.weapon_or_mawared_or_nothing == 1)
        return false;
    for (int i = 0; i < INVENTORY_SIZE; ++i)
    {
        if (inv_items[i].mawared.type == item.mawared.type)
        {
            if (inv_items[i].mawared.quantity <= 16) // if it is not stack (stack is 16 pieces)
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
}
/**********************************************************************************************************************************************/

int findAvailableSlot()
{
    for (int i = 0; i < INVENTORY_SIZE; ++i)
    {
        if (inv_items[i].weapon_or_mawared_or_nothing == -1)
            return i;
    }
    return -1;
}

//                                  FUNCTION    TO   UPDATE    HEALTH    FOR     OBJECT     WHEN    HIT
void updateObjectHealth(Player& player, Tree& tree, Stone& stone, Iron& iron, vector<Wood>& collectedWoods, vector<Stone_collectable>& collectedStones, vector<Iron_collectable>& collectedIrons)
{
    if (&tree != nullptr && tree.health > 0 && isPlayerBesideObject(player, tree.sprite.getPosition()))
    {
        tree.health -= 0.1f;
        if (tree.health <= 0)
        {
            //cout << "Tree destroyed, wood dropped!" << endl;

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
    if (&stone != nullptr && stone.health > 0 && isPlayerBesideObject(player, stone.sprite.getPosition()))
    {
        stone.health -= 0.05f;
        if (stone.health <= 0)
        {
            //cout << "Stone destroyed!";
            Stone_collectable dropped_stone;
            dropped_stone.position = stone.sprite.getPosition();
            dropped_stone.position.y += 30;
            dropped_stone.sprite.setPosition(dropped_stone.position.x, dropped_stone.position.y);
            dropped_stone.collected = false;
            dropped_stone.sprite.setTexture(dropped_stone_texture);
            collectedStones.push_back(dropped_stone);
            stone.health = 0;

        }
    }
    if (&iron != nullptr && iron.health > 0 && isPlayerBesideObject(player, iron.sprite.getPosition()))
    {
        iron.health -= 0.05f;
        if (iron.health <= 0)
        {
            //cout << "Iron destroyed!\n";
            Iron_collectable dropped_iron;
            // dropped_iron.position = iron.sprite.getPosition();
             //dropped_iron.position.y+
           //  dropped_iron.sprite.setPosition(dropped_iron.position.x, dropped_iron.position.y);
            dropped_iron.collected = false;
            dropped_iron.sprite.setTexture(dropped_iron_texture);
            collectedIrons.push_back(dropped_iron);
            iron.health = 0;
            // iron.sprite.setPosition(-1000, -1000);
        }
    }
}
/********************************************************************************************************************************************/
//                                  FUNCTION    TO   COLLECT    ITEMS    ON     GROUND
void collectItems(Sprite& player, vector<Wood>& collectedWoods, vector<Stone_collectable>& collectedStones, vector<Iron_collectable>& collectedIrons)
{
    item_type item;
    for (auto& wood : collectedWoods)
    {
        float distanceSquared = (player.getPosition().x - wood.position.x) * (player.getPosition().x - wood.position.x) +
            (player.getPosition().y - wood.position.y) * (player.getPosition().y - wood.position.y);
        if (!wood.collected && distanceSquared <= 500)
        {
            wood.collected = true;
            item.weapon_or_mawared_or_nothing = 2;
            item.mawared.sprite = wood.sprite;

            item.mawared.type = 1;
            item.mawared.quantity = 8;
            inventory.currentWood += item.mawared.quantity;
            if (isInInventory(item)) // If item is already in inventory add to it the quantity collected
            {
                for (int i = 0; i < INVENTORY_SIZE; i++)
                    if (item.mawared.type == inv_items[i].mawared.type)
                        inv_items[i].mawared.quantity += item.mawared.quantity;
            }
            else
                // Add wood to player's inventory if there is space in inventory
                if (!full())
                {
                    addToInventory(item);
                }
            //cout << "Wood collected!" << endl;

        }
    }

    for (auto& dstone : collectedStones)
    {
        float distanceSquared = (player.getPosition().x - dstone.position.x) * (player.getPosition().x - dstone.position.x) +
            (player.getPosition().y - dstone.position.y) * (player.getPosition().y - dstone.position.y);
        if (!dstone.collected && distanceSquared <= 500)
        {
            dstone.collected = true;
            item.weapon_or_mawared_or_nothing = 2;
            item.mawared.sprite = dstone.sprite;
            item.mawared.type = 2;
            item.mawared.quantity = 2;
            inventory.currentStones += item.mawared.quantity;

            if (isInInventory(item))
            {
                for (int i = 0; i < INVENTORY_SIZE; i++)
                    if (item.mawared.type == inv_items[i].mawared.type)
                        inv_items[i].mawared.quantity += item.mawared.quantity;
            }
            else
                if (!full())
                    addToInventory(item);
            //cout << "Stone collected!" << endl;
            Sprite stoneSprite;
        }
    }
    for (auto& diron : collectedIrons)
    {
        float distanceSquared = (player.getPosition().x - diron.position.x) * (player.getPosition().x - diron.position.x) +
            (player.getPosition().y - diron.position.y) * (player.getPosition().y - diron.position.y);
        if (!diron.collected && distanceSquared <= 500)
        {
            diron.collected = true;
            item.weapon_or_mawared_or_nothing = 2;
            item.mawared.sprite = diron.sprite;
            item.mawared.type = 3;
            item.mawared.quantity = 4;
            inventory.currentIron += item.mawared.quantity;

            if (isInInventory(item))
            {
                for (int i = 0; i < INVENTORY_SIZE; i++)
                    if (item.mawared.type == inv_items[i].mawared.type)
                        inv_items[i].mawared.quantity += item.mawared.quantity;
            }
            else
                if (!full())
                    addToInventory(item);
            //cout << "iron collected!" << endl;
            Sprite ironSprite;
            ironSprite.setTexture(dropped_iron_texture);
            ironSprite.setScale(0.2f, 0.2f);
            // ironSprite.setPosition(findAvailableSlot() * 80, 180);
        }
    }
}
