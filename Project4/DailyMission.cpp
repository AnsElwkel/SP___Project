//Day 1 kill 3 MOBS
//* **
//1
//Day 2 Collect 3 stone blocks from the forest.
//###
//1
//Day 3  break 5 trees
//$$$$$
//0
//Day 4  run 1000 meter
//R1000
//1
//Day 5  Collect 3 iron blocks from the forest.
//% %%
//1
//Day 6  kill 3 monsters
//&& &
//1
//Day 7  make a long sword
//ML
//0
//Day 8  gather 4 meat
//++++
//0
//Day 9  find the hidden box
//HB
//0
//Day 10 make a mace
//MM
//1
//Day 11 Collect 3 stone blocks from the forest.
//###
//1
//Day 12 make a waraxe
//MW
//0
//Day 13 kill 3 MOBS
//* **
//0
//Day 14 Collect 3 iron blocks from the forest.
//% %%
//1
//Day 15 break 5 trees
//$$$$$
//0
//Day 16 make a saber
//MS
//0
//Day 17 run 1000 meter
//R1000
//1
//Day 18 kill 3 monsters
//&& &
//0
//Day 19 make a long sword
//ML
//1
//Day 20 gather 4 meat
//++++
//0
//Day 21 find the hidden box
//HB
//1
//Day 22 make a mace
//MM
//1
//Day 23 Collect 3 iron blocks from the forest.
//% %%
//1
//Day 24 kill 3 MOBS
//* **
//0
//Day 25 make a waraxe
//MW
//1
//Day 26 Collect 3 stone blocks from the forest.
//###
//1
//Day 27 make a mace
//MM
//0
//Day 28 gather 4 meat
//++++
//0
//Day 29 run 1000 meter
//R1000
//0
//Day 30 make a saber
//MS
//1






#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include<stack>
#include "button.h"
#include"Settings.h"
#include "DailyMission.h"
#include "PauseMenu.h"
#include "mainMenu.h"

Color A = sf::Color(203, 255, 255, 0);
Color B = sf::Color(196, 138, 100, 0);
Color C = sf::Color(165, 180, 125, 0);
Vector2f resizeAll = { 1.f,1.f };
float resizeText = min(resizeAll.x, resizeAll.y);


time_t now = time(0);
tm ltm;
int cur[5];
Vector2f windowDefaultSize = { 1920,1080 };
Clock coinTimer;
bool doneToday;
float coinFlat = 0;
int p = 0;





Vector2f multiply(Vector2f& vec1, Vector2f& vec2, int i = -1) {
    Vector2f vec3 = Vector2f(vec1.x * vec2.x, (vec1.y * vec2.y + (80 * (i + 1))));//for selectors to make spaces
    return vec3;

}
void checkIfDone::loadDailyMission(string& lastDay, string gifts[]) {
    ifstream inputFile("daily_mission.txt");
    if (inputFile.is_open()) {
        getline(inputFile, lastDay);
        for (int i = 1; i < 91; i++)
        {

            getline(inputFile, gifts[i]);
        }
        inputFile.close();
    }
}
void checkIfDone::saveDailyMission(string& lastDay, string gifts[]) {
    ofstream outputFile("daily_mission.txt");
    if (outputFile.is_open()) {
        outputFile << lastDay << endl;
        for (int i = 1; i < 91; i++)
        {
            outputFile << gifts[i] << endl;

        }


        outputFile.close();
    }
}
void checkIfDone::checkMission()//check the mission of today
{

    current = 3 * currentDay;
    loadDailyMission(lastDayString, mission);
    localtime_s(&ltm, &now);
    currentDay = ltm.tm_mday;

    if (mission[current - 1] == "***" && mission[current - 1].size() <= killedMobs && once)//kill 3 MOBS
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "MM" && makeMace && once)//make a mace
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "++++" && mission[current - 1].size() <= collectedMeat && once)//gather 4 meat
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "ML" && makeLongSword && once)//make a long sword
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "MS" && makeSaber && once)//make a saber
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "MW" && makeWarAxe && once)//make awaraxe
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "###" && mission[current - 1].size() <= collectedStone && once)//Collect 3 stone blocks from the forest
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "$$$$$" && mission[current - 1].size() <= brokenTrees && once)//break 5 trees
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "%%%" && mission[current - 1].size() <= collectedIron && once)//Collect 3 iron blocks from the forest.
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "R1000" && runDistance >= 10000 && once)// run 1000 meter
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "HB" && foundBox && once)//find the hidden box
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;
    }
    else if (mission[current - 1] == "&&&" && mission[current - 1].size() <= killedMonsters && once)//kill 3 monsters
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
        once = 0;

    }
    else if (Keyboard::isKeyPressed(Keyboard::L))
    {
        mission[current] = "1";
        forDraw = 1;
        coinTimer.restart();
    }



    if (mission[current] == "1" && coinFlat <= 2 && p < 450)
    {
        giftt = rand() % 3001 + 2000;
        p++;

        if (p == 450)
        {
            coin += giftt;

        }
    }
}
void checkIfDone::selection() {


    current = currentDay * 3;
    currentDayString = to_string(currentDay);
    lastDay = stoi(lastDayString);

    missionBox.setSize(multiply(rectSize, resizeAll));
    missionBox.setPosition(multiply(rectPosition, resizeAll));
    missionBox.setFillColor(Color(128, 128, 128, 120));//grey


    missionText.setFont(font);
    missionText.setCharacterSize(resizeText * 30.f);
    missionText.setFillColor(Color::Black);
    missionText.setPosition(multiply(missionTextPos, resizeAll));

    if (currentDay == 1)
    {
        cur[0] = 79;
        cur[1] = 82;
        cur[2] = 85;
        cur[3] = 88;
        cur[4] = 1;

    }
    else if (currentDay == 2)
    {
        cur[0] = 82;
        cur[1] = 85;
        cur[2] = 88;
        cur[3] = 1;
        cur[4] = 4;
    }
    else if (currentDay == 3)
    {
        cur[0] = 85;
        cur[1] = 88;
        cur[2] = 1;
        cur[3] = 4;
        cur[4] = 7;
    }
    else if (currentDay == 4)
    {
        cur[0] = 88;
        cur[1] = 1;
        cur[2] = 4;
        cur[3] = 7;
        cur[4] = 10;
    }

    else
    {

        cur[0] = current - 14;
        cur[1] = current - 11;
        cur[2] = current - 8;
        cur[3] = current - 5;
        cur[4] = current - 2;

    }
    missionText.setString("Daily Mission Is: "
        "\n\n\t\t\t" + mission[cur[0]] + ""
        "\n\n\t\t\t" + mission[cur[1]] + ""
        "\n\n\t\t\t" + mission[cur[2]] + ""
        "\n\n\t\t\t" + mission[cur[3]] + ""
        "\n\n\t\t\t" + mission[cur[4]] + ""
    );
    missionText.setStyle(Text::Bold);




    for (int i = 0; i < 5; i++)
    {

        if (mission[cur[i] + 2] == "1") {
            done[i].setSize(multiply(selectorSize, resizeAll));
            done[i].setPosition(multiply(selectorPos, resizeAll, i));
            checkBox[i].setPosition(multiply(checkerPos, resizeAll, i));
            done[i].setFillColor(Color(145, 230, 80, 160));//green
            checkBox[i].setTextureRect(IntRect(0, 0, 70, 80));

        }
        else if (mission[cur[i] + 2] == "0") {
            done[i].setSize(multiply(selectorSize, resizeAll));
            done[i].setPosition(multiply(selectorPos, resizeAll, i));
            checkBox[i].setPosition(multiply(checkerPos, resizeAll, i));
            done[i].setFillColor(Color(255, 50, 80, 160));
            checkBox[i].setTextureRect(IntRect(70, 0, 70, 80));
        }

    }
    done[4].setOutlineColor(Color::Black);
    done[4].setOutlineThickness(3.5);



    saveDailyMission(currentDayString, mission);
}

checkIfDone::checkIfDone(sf::RenderWindow* windoww, stack<states*>* gameStates) :states(windoww, gameStates)
{

    checkbox.loadFromFile("./res/gifts/check.png");

    for (size_t i = 0; i < 5; i++)
        checkBox[i].setTexture(checkbox);
    Gift.loadFromFile("./res/gifts/coins.png");
    giftSprite.setTexture(Gift);
    font.loadFromFile("./res/Fonts/minecraft_font.ttf");
    bGround.loadFromFile("./res/siltara4.jpg");
    backGround.setTexture(bGround);
    coinTex.loadFromFile("./res/gifts/coinn.png");
    coinSprit.setTexture(coinTex);
    coinNum.setString("" + to_string(coin) + " \ncoins ");
    coinNum.setCharacterSize(60 * resizeText);
    coinNum.setFillColor(Color(249, 188, 0));
    coinNum.setFont(font);

    coinNum.setPosition(200, 35);
    coinSprit.setPosition(100, 35);
}

void checkIfDone::render(RenderTarget* window) {
    window->draw(backGround);
    window->draw(coinSprit);
    window->draw(coinNum);
    for (int i = 0; i < 5; i++)
    {
        window->draw(checkBox[i]);
        window->draw(done[i]);
    }
    window->draw(missionBox);
    window->draw(missionText);
    if (forDraw && coinFlat <= 10)
    {
        window->draw(giftSprite);
        window->draw(giftText);
        coinFlat = coinTimer.getElapsedTime().asSeconds();
    }
}
void checkIfDone::update(const float& dt)
{
    Updatebind(dt);
    UpdateMousePos();
    checkMission();
    selection();
    giftBox();
}
void checkIfDone::Updatebind(const float& dt)
{
    endstate();
}
void checkIfDone::end()
{
    cout << "daily has closed" << endl;
}
void checkIfDone::giftBox() {

    giftText.setPosition(650 * resizeAll.x, 600 * resizeAll.y);
    giftText.setString("You got  " + to_string(giftt) + "  Coins ");
    giftText.setFont(font);
    giftText.setCharacterSize(50 * resizeAll.x);
    giftText.setFillColor(Color::Black);
}

