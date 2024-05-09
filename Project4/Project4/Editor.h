#pragma once
#include "includes.h"
#include"states.h"
#include"Map.h"
#include"application.h"
#
#include"PauseMenu.h"
struct Editor:states
{
	// making local structs //
	struct textureSelector
	{
		float delta;
		int L=3, T=5;
		bool active,active1,active2,isStillPress;
		pair<const bool, const bool> getActive() const;
		sf::RectangleShape bound,Selector;
		sf::Sprite sprite;
		sf::Vector2i ho;
		sf::Vector2u mousegrid;
		sf::IntRect rect;
		button* hide=new button;
		textureSelector();
		textureSelector(float width, float height, float gridsize, sf::Texture* texture, sf::Font font);
		void render(sf::RenderTarget* target);
		void update(sf::Vector2i* mousepos, sf::IntRect& r, float sizeOfEachOne);
	};

    // *************** detiles and help for map bulider ***************************** //
	struct status
	{
		RectangleShape bound;
		button* Switch = new button;
		map<string, button*>buttons;
		//Text *mouse=new Text;
		//stringstream *s=new stringstream;
		bool active, ispressing, activeAll, AddActive, RemoveActive, ispressing1;
		status();
		status(float x, float y, float width, float height, Color c, int charSize, Font font);
		void render(RenderTarget* target, Vector2i& mousepos, Vector2u& mousePositionGrid, Font font, float Grid,int currentland,int numberOfLands);
		const bool getActive() const;
		void update(Vector2i* mousepos,int &currentLand,int grid,Vector2f,ELARABY::Vector<lands*>&lands);
	};

	// rendering zone and selecting ///
	int width = 10,startX=0,startY=0,elem=0,elem1=0,elem2;
	float delta=0,delta1=0;
	sf::Vector2f startfloat = { 0 ,0};
	string whichOne,o,arr[9] = { "#G01","#G02","#G03","#G04" ,"#G05","#G06","#G07","#G08" ,"#G09" };
	sf::Texture* tex[3] = { new sf::Texture, new sf::Texture, new sf::Texture };
	sf::IntRect TexRect;
	status stat;

	// fonts //
	sf::Font font;
	bool loaded = 0;


	// view and gui//
	sf::View camera;
	tile hoverd;
	sf::RectangleShape selectorRect;


	// lists //
	textureSelector selector;
	Map *tiles=new Map;
	PauseMenu* PauseM = new PauseMenu(window);



	bool activate = 0,activate1;
	sf:: Vector2f i, e;
	int y, y1, l, r;

	// ***********    functions    ************ //
	Editor(sf::RenderWindow *window , stack<states*>*m );
	~Editor();
	void end() ;
	void pausinit();
	bool valid(int x,int y);
	void add(unsigned x, unsigned y, unsigned z,float GridSize,sf::Texture &SelectByS,string ss);
	void UI();
	void remove(unsigned x, unsigned y, unsigned z);
	void UUI();
	void UpdateTile(const float& dt);
	void buttonUpdate();
	void Updatebind(const float& dt) ;
	void FontInit();
	void update(const float &dt);
	void render(sf::RenderTarget* target);
};