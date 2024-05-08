#pragma once
#include "includes.h"
using namespace std;
struct states
{
	sf::RenderWindow* window;
	vector<sf::Texture>texture;
	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Vector2u mousePositionGrid;
	stack<states*>*gameStates;
	bool quit,Exit,Pause,ispressed;
	states(sf::RenderWindow *windoww,stack<states*>*gameStates);
	~states();
	void pause();
	bool close();
	const bool getQuit()const;
	virtual void  UpdateMousePos(sf::View *view=NULL);
	virtual void endstate();
	virtual void end() = 0;
	virtual void Updatebind(const float &dt)=0;
	virtual void update(const float &dt)=0;
	virtual void render(sf::RenderTarget *target= nullptr)=0;
};
