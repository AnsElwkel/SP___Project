#pragma once
#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include"states.h".
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
//#include "CollisionManager.h"
using namespace std;
using namespace sf;

//Button Structure -> Called in below Structs
struct Buttons {
    Font* font;
    Text* text;
    RectangleShape* rect;
    Color* idle;
    Color* touch;
    Color* press;
    bool isIdle;
    bool isTouch;
    bool isPress;
    int size;

    void setButtonDetails(int x, int y, int xT, int yT, int width, int height, string text, Color idle, Color touch, Color press, RenderTarget* window);
    Buttons();
    ~Buttons();
};

//List Structure -> Called in below Structs
struct list1 {
    void setListDetails(float width, float height, float x, float y, float xT, float yT, int sizeChar, string str[], Color idle, Color press, RenderTarget* window);
    void whenPress(RenderTarget* window, Event& ev, Vector2f mousePos);

    void render(RenderTarget* window);

    string  getText();

    list1(int size);
    ~list1();

    bool isOpen;
    RectangleShape* elements;
    Text* text;
private:
    string* str;
    Font* font;
    float* width;
    float* height;
    float* x;
    float* y;
    int* size;
    Color* idle;
    Color* press;
    bool isIdle;
    bool isTouch;
    bool isPress;
};

//Resolution Structure
struct Resolution {
    list1* List;
    list1* List1;
    void setResolutionDetails(RenderTarget* window);
    Resolution(int);
    ~Resolution();

private:
    string* resolutionList;
    string* name ;
};

//FPS Structure
struct fps {
    list1* List;
    list1* List1;
    void setFPSDetails(RenderTarget* window);
    fps(int);
    ~fps();

private:
    string* FPSList;
    string* name;
};

//SFX Structure
struct SFX {
    list1* List;
    list1* List1;
    void setSFXDetails(RenderTarget*);
    SFX();
    ~SFX();
private:
    string* name;
    string* sfxOptions;
};

//vSync Structure
struct vSync {
    list1* List;
    list1* List1;
    void setVSyncDetails(RenderTarget* window);

    vSync();
    ~vSync();

private:
    string* name;
    string* vSyncOptions;
};

//Save Structure
struct Save {
    Buttons* button;
    void setSaveDetails(RenderTarget*);
    void whenPress(RenderTarget* window, Vector2f& mousePos, string textRes,
        string textFps, string textSFX, string textVSync);
    void render(RenderTarget* window);
    Save();
    ~Save();
    bool apply;
private:
    string* name;
};

//Active all  above structures
struct menuSettings:states
{
    Resolution* RESOLUTION_SETTINGS;
    fps* FPS_SETTINGS;
    SFX* SFX_SETTINGS;
    vSync* VERTICAL_SYNC_SETTINGS;
    Save* SAVE_SETTINGS;
    RectangleShape* BACK_GROUND; //Gray Rectangle

    Event event;
    void setResolution_Settings(RenderTarget*);
    void setFPS_Settings(RenderTarget*);
    void setSFX_Settings(RenderTarget*);
    void setVSync_Settings(RenderTarget*);
    void setSave_Settings(RenderTarget*);
    menuSettings(sf::RenderWindow* windoww, stack<states*>* gameStates,Event &ev);
    void end();
    void render(sf::RenderTarget* target);
    void update(const float& dt);
    void Updatebind(const float& dt);
    void applySettings(RenderTarget* window, Vector2f& mousePos , bool& apply);
    
    void renderBackGround(RenderTarget* window);
    ~menuSettings();
};

#endif
