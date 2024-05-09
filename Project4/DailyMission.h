#pragma once 
#include "includes.h"
#include"states.h"
using namespace std;
using namespace sf;
extern Vector2f resizeAll;
struct checkIfDone:states
{



    int killedMobs = 0, killedMonsters = 0, coin = 0,
        collectedMeat = 0, collectedStone = 0,
        brokenTrees = 0, collectedIron = 0, runDistance = 0;


    bool foundBox = 0, makeMace = 0, makeLongSword = 0, makeSaber = 0, makeWarAxe = 0;
    string gift;
    string mission[91];

    void loadDailyMission(string& lastDay, string gifts[]);

    void saveDailyMission(string& lastDay, string gifts[]);

    void checkMission();
    Vector2f rectSize = { 1200,650 };
    Vector2f rectPosition = { 150,160 };
    Vector2f missionTextPos = { rectPosition.x + 20,rectPosition.y + 30 };
    Vector2f selectorSize = { (rectSize.x - 230) , 67 };
    Vector2f selectorPos = { (rectPosition.x + 80) ,(rectPosition.y) };
    Vector2f checkerPos = { (rectPosition.x + 1100.f), (rectPosition.y) };

    Text missionText;
    Text giftText;
    string currentDayString;
    string lastDayString;//zero indexed

    int current = 0, currentDay = 0, lastDay = 0;
    Sprite checkBox[5];
    Sprite giftSprite;
    Font font;
    RectangleShape done[5];//green Box
    RectangleShape missionBox;
    RectangleShape giftRect;
    int giftt = 0;
    bool forDraw = 0;
    bool once = 1;
    checkIfDone(sf::RenderWindow* windoww, stack<states*>* gameStates);
    void render(sf::RenderTarget* target);
    void update(const float& dt);
    void Updatebind(const float& dt);
    void end();
    void giftBox();
    void selection(Font&);
};


