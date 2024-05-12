#include "Settings.h"
void list1::setListDetails(float width, float height, float x, float y, float xT, float yT, int sizeChar,
	string str[], Color idle, Color press,
	RenderTarget* window)
{
	*this->width = width;
	*this->height = height;
	*this->x = x;
	*this->y = y;
	*this->idle = idle;
	*this->press = press;
	this->isOpen = 0;

	this->elements->setPosition(x, y);
	this->elements->setSize(Vector2f(width, height));
	this->elements->setFillColor(idle);

	this->font->loadFromFile("minecraft_font.ttf");
	for (short i = 0; i < *this->size; ++i)
		this->str[i] = str[i];

	this->text[0].setPosition(xT, yT);

	for (short i = 0; i < *this->size; ++i) {
		this->text[i].setFont(*font);
		this->text[i].setString(this->str[i]);
		this->text[i].setCharacterSize(sizeChar * window->getSize().x / 1920);
		if (i)
			this->text[i].setPosition(10000, 10000);
	}
}

//This function call in Event loop**
float deltaTime = 0;
void list1::whenPress(RenderTarget* window, Event& ev, Vector2f mousePos)
{
	//Now Rectangle`s Color is idle
	isIdle = 1;
	isTouch = 0;
	isPress = 0;
	deltaTime += 1 / 200.0;
	if (this->elements->getGlobalBounds().contains(mousePos))
	{
		//Now Rectangle`s outline thickness is appear
		isIdle = 0;
		isTouch = 1;
		isPress = 0;


		if (Mouse::isButtonPressed(Mouse::Left) && deltaTime > 1)
		{
			isIdle = 0;
			isTouch = 0;
			isPress = 1;
			deltaTime = 0;
			string Tmp = text[0].getString();
			for (int i = 0; i < *this->size - 1; ++i)
			{
				text[i].setString(text[i + 1].getString());
			}
			text[(*this->size) - 1].setString(Tmp);

		}
		//apply changes
	}
	if (this->isIdle) {
		this->elements->setFillColor(*idle);
		this->elements->setOutlineColor(*idle);
	}
	else if (this->isTouch) {
		this->elements->setOutlineThickness(5.f * window->getSize().x / 1920);
		this->elements->setOutlineColor(Color::Black);
	}
	else if (this->isPress) {
		this->elements->setOutlineColor(*press);
		this->elements->setFillColor(*press);
	}
}

void list1::render(RenderTarget* window) {
	window->draw(*this->elements);
	window->draw(this->text[0]);
}

string list1::getText()
{
	return this->text[0].getString();
}

//Initialize Atrributes
list1::list1(int size)
	: elements(new RectangleShape), str(new string[size]),
	x(new float(0)), y(new float(0)),
	font(new Font()), text(new Text[size]),
	width(new float(0)), height(new float(0)),
	isOpen(new bool(false)), isIdle(0), isTouch(0),
	isPress(0),
	size(new int(size)),
	idle(new Color(Color::White)), press(new Color(Color::White)) {}
//Delete Dynamic Atrributes
list1::~list1()
{
	delete elements;
	delete[] str;
	delete[] text;
	delete width;
	delete height;
	delete size;
	delete x;
	delete y;
	delete font;
	delete idle;
	delete press;
}



//Button Struct **this struct only used in Save struct
void Buttons::setButtonDetails(int x, int y, int xT, int yT,
	/*same logic of list*/	       int width, int height, string text,
	Color idle, Color touch, Color press,
	RenderTarget* window)
{
	this->rect->setPosition(x, y);
	this->rect->setSize(Vector2f(width, height));

	this->font->loadFromFile("minecraft_font.ttf");
	this->text->setFont(*this->font);
	this->text->setString(text);
	this->text->setFillColor(Color::White);
	this->text->setCharacterSize(70 * window->getSize().x / 1920);
	this->text->setPosition(xT, yT);

	*this->idle = idle;
	*this->touch = touch;
	*this->press = press;

	this->isIdle = false;
	this->isTouch = false;
	this->isPress = false;

	this->rect->setFillColor(*this->idle);
}

//Initialize Atrributes
Buttons::Buttons()

	: rect(new RectangleShape()), font(new Font()),
	idle(new Color()), touch(new Color()), text(new Text()),
	press(new Color()), isIdle(0),
	isTouch(0), isPress(0), size(0) {	}

//Delete Dynamic Atrributes
Buttons::~Buttons()
{
	delete font;
	delete text;
	delete rect;
	delete idle;
	delete touch;
	delete press;
}



//Resolution Struct
void Resolution::setResolutionDetails(RenderTarget* window)
{
	//Set Options
	this->name[0] = "Resolution";
	this->resolutionList[0] = "1920 x 1080";
	this->resolutionList[1] = "1600 x 900";
	this->resolutionList[2] = "1280 x 720";

	//Get Details of FPS from file
	fstream fin;
	string currentRes;
	fin.open("settings/window.ini", ios::in | ios::out);
	string ignore;
	getline(fin, ignore);
	getline(fin, currentRes);
	fin.close();

	//Handle first last saved option in file to appear on screen
	int idx = 0;
	currentRes.insert(currentRes.begin() + 5, 'x');
	currentRes.insert(currentRes.begin() + 6, ' ');
	for (int i = 0; i < 3; ++i) {
		if (currentRes == resolutionList[i]) {
			idx = i;
			break;
		}
	}
	string tmp = resolutionList[0];
	resolutionList[0] = currentRes;
	resolutionList[idx] = tmp;

	//Set Details of right rectangle <1920 x 1080> or <1600 x 900> or <1280 , 720>
	this->List->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,
		window->getSize().x / 3.2, window->getSize().x / 6.7,
		window->getSize().x / 3.1, window->getSize().x / 6.3, 45,
		this->resolutionList,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);

	//Set Details of left rectangle <Resolution>
	this->List1->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,
		window->getSize().x / 18.f, window->getSize().x / 6.7,
		window->getSize().x / 17.7, window->getSize().x / 6.3,
		55, this->name,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);
}

//Initialize Atrributes
Resolution::Resolution(int size)
	: resolutionList(new string[size]), name(new string[1]),
	List(new list1(size)), List1(new list1(1)) {	}

//Delete Dynamic Atrributes
Resolution::~Resolution()
{
	delete[] resolutionList;
	delete[] name;
	delete List;
	delete List1;
}



//FPS Struct
void fps::setFPSDetails(RenderTarget* window)
{
	//Set Options
	this->name[0] = "FPS";
	this->FPSList[0] = "60";
	this->FPSList[1] = "30";
	this->FPSList[2] = "40";
	this->FPSList[3] = "90";
	this->FPSList[4] = "120";
	this->FPSList[5] = "240";

	//Get Details of FPS from file
	fstream fin;
	string currentFPS;
	fin.open("settings/window.ini", ios::in | ios::out);
	string ignore;
	getline(fin, ignore);
	getline(fin, ignore);
	fin >> currentFPS;
	fin.close();

	//Handle first last saved option in file to appear on screen
	int idx{};
	for (int i = 0; i < 6; ++i) {
		if (currentFPS == FPSList[i]) {
			idx = i;
			break;
		}
	}
	string tmp = FPSList[0];
	FPSList[0] = currentFPS;
	FPSList[idx] = tmp;

	//Set Details of right rectangle <30> or <60> and so on..
	this->List->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,
		window->getSize().x / 3.2, window->getSize().y / 2.7,
		window->getSize().x / 2.65, window->getSize().y / 2.6,
		60, this->FPSList,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);

	//Set Details of left rectangle <FPS>
	this->List1->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,
		window->getSize().x / 18.f, window->getSize().y / 2.7,
		window->getSize().x / 9.f, window->getSize().y / 2.6, 70,
		this->name,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);
}

//Initialize Atrributes
fps::fps(int size) : List(new list1(size)), List1(new list1(1)),
FPSList(new string[size]), name(new string[size]) {}

//Delete Dynamic Atrributes
fps::~fps() {
	delete List;
	delete List1;
	delete[] name;
	delete[] FPSList;
}



//SFX Struct
void SFX::setSFXDetails(RenderTarget* window)
{
	//Set Options
	this->name[0] = "SFX Sound";
	this->sfxOptions[0] = "on";
	this->sfxOptions[1] = "off";

	//Set Details of right rectangle <on> or <off>
	this->List->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,
		window->getSize().x / 3.2, window->getSize().y / 2.1,
		window->getSize().x / 2.65, window->getSize().y / 2.05, 65,
		this->sfxOptions,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);


	//Set Details of left rectangle <SFX Sound>
	this->List1->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,
		window->getSize().x / 18, window->getSize().y / 2.1,
		window->getSize().x / 17.3, window->getSize().y / 2.05, 55,
		this->name,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);
}

//Initialize Atrributes
SFX::SFX()
	:
	List(new list1(2)), List1(new list1(1)),
	name(new string[1]), sfxOptions(new string[2]) {}

//Delete Dynamic Atrributes
SFX::~SFX()
{
	delete[] this->sfxOptions;
	delete[] this->name;
	delete this->List;
	delete this->List1;
}



//vSync Struct
void vSync::setVSyncDetails(RenderTarget* window)
{
	//Set Options
	this->name[0] = "vSync";
	this->vSyncOptions[0] = "on";
	this->vSyncOptions[1] = "off";

	//Set Details of right rectangle <on> or <off>
	this->List->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,//Size
		window->getSize().x / 3.2, window->getSize().y / 1.72,//Position Icon
		window->getSize().x / 2.65, window->getSize().y / 1.7,//Position Text ( in icon)
		65, this->vSyncOptions,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);

	//Set Details of left rectangle <vSync>
	this->List1->setListDetails(window->getSize().x / 5.4, window->getSize().y / 10.6,//Size
		window->getSize().x / 18.f, window->getSize().y / 1.72f, //Position Icon
		window->getSize().x / 12.f, window->getSize().y / 1.72f, //Position Text ( in icon)
		70, this->name,
		Color(145, 230, 80, 100),
		Color(255, 50, 80, 85), window);

}

//Initialize Atrributes
vSync::vSync() : List(new list1(2)), List1(new list1(1)),
name(new string[1]), vSyncOptions(new string[2]) {}

//Delete Dynamic Atrributes
vSync::~vSync() {
	delete List;
	delete List1;
	delete[] name;
	delete[] vSyncOptions;
}



//Save Struct
void Save::setSaveDetails(RenderTarget* window)
{
	this->button->setButtonDetails(window->getSize().x / 1.3, window->getSize().y / 1.2f,  //Position Icon
		window->getSize().x / 1.23, window->getSize().y / 1.17f,//Position Text
		window->getSize().x / 5.4, window->getSize().y / 10.6,  //Size
		"Save",
		Color(145, 230, 80, 100),
		Color(150, 150, 150, 200),
		Color(255, 50, 80, 85), window);
}

void Save::whenPress(RenderTarget* window, Vector2f& mousePos,
	string textRes, string textFps, string textSFX, string textVSync)
{
	this->button->isIdle = 1;
	this->button->isTouch = 0;
	this->button->isPress = 0;

	if (this->button->rect->getGlobalBounds().contains(mousePos)) {
		this->button->isIdle = 0;
		this->button->isTouch = 1;
		this->button->isPress = 0;

		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->button->isIdle = 0;
			this->button->isTouch = 0;
			this->button->isPress = 1;
		}
	}

	if (this->button->isIdle) {
		this->button->rect->setFillColor(*this->button->idle);
		this->button->rect->setOutlineThickness(0);

	}
	else if (this->button->isTouch) {
		this->button->rect->setOutlineThickness(5.f * window->getSize().x / 1920);
		this->button->rect->setOutlineColor(Color::Black);

	}
	else if (this->button->isPress) {
		this->button->rect->setFillColor(*this->button->press);
		this->button->rect->setOutlineThickness(0);
		this->apply = true;


		//Save Changes
		fstream fout;
		fout.open("settings/window.ini", ios::trunc | ios::out | ios::in);
		string titleGame = "Siltara";
		string width = textRes.substr(0, (textRes.find(' ')));
		string height = textRes.substr(1 + (textRes.rfind(' ')), textRes.size() - 1);
		fout << titleGame << endl;
		fout << width << ' ' << height << endl;
		fout << textFps << endl;
		fout << (textSFX == "on" ? 1 : 0) << endl;
		fout << (textVSync == "on" ? 1 : 0) << endl;
		fout.close();

	}
}

void Save::render(RenderTarget* window)
{
	window->draw(*this->button->rect);
	window->draw(*this->button->text);
}

//Initialize Variables
Save::Save() : name(new string[1]), button(new Buttons()), apply(0) {}

//Delete Dynamic Atrributes
Save::~Save() {
	delete button;
	delete[] name;
}



//MenuSttings Struct contain all settings details
void menuSettings::setResolution_Settings(RenderTarget* window)
{
	this->RESOLUTION_SETTINGS->setResolutionDetails(window);
}

void menuSettings::setFPS_Settings(RenderTarget* window)
{
	this->FPS_SETTINGS->setFPSDetails(window);
}

void menuSettings::setSFX_Settings(RenderTarget* window)
{
	this->SFX_SETTINGS->setSFXDetails(window);
}

void menuSettings::setVSync_Settings(RenderTarget* window)
{
	this->VERTICAL_SYNC_SETTINGS->setVSyncDetails(window);
}

void menuSettings::setSave_Settings(RenderTarget* window)
{
	this->SAVE_SETTINGS->setSaveDetails(window);
}

void menuSettings::end()
{
	cout << "settings has closed\n";
}

void menuSettings::render(RenderTarget* window)
{
	renderBackGround(window);
	RESOLUTION_SETTINGS->List->render(window);
	RESOLUTION_SETTINGS->List1->render(window);
	FPS_SETTINGS->List->render(window);
	FPS_SETTINGS->List1->render(window);
	SFX_SETTINGS->List1->render(window);
	SFX_SETTINGS->List->render(window);
	VERTICAL_SYNC_SETTINGS->List1->render(window);
	VERTICAL_SYNC_SETTINGS->List->render(window);
	SAVE_SETTINGS->render(window);
}

void menuSettings::update(const float& dt)
{
	UpdateMousePos();
	Updatebind(dt);
	Vector2f mousePos = Vector2f(mousePositionWindow);
	SAVE_SETTINGS->whenPress(window, mousePos,
		RESOLUTION_SETTINGS->List->getText(),
		FPS_SETTINGS->List->getText(),
		SFX_SETTINGS->List1->getText(),
		VERTICAL_SYNC_SETTINGS->List1->getText());
	applySettings(window, mousePos, SAVE_SETTINGS->apply);
	//while (window->pollEvent(event))
	{
		SFX_SETTINGS->List->whenPress(window, event, mousePos);
		VERTICAL_SYNC_SETTINGS->List->whenPress(window, event, mousePos);
		RESOLUTION_SETTINGS->List->whenPress(window, event, mousePos);
		FPS_SETTINGS->List->whenPress(window, event, mousePos);
	}
}

void menuSettings::Updatebind(const float& dt)
{
	endstate();
}

//apply settings
void menuSettings::applySettings(RenderTarget* target, Vector2f& mousePos, bool& apply)
{
	if (once) {
		tground.loadFromFile("./res/siltara4.jpg");
		bGround.setTexture(tground);

		once = 0;
	}

	if (apply) {

		VideoMode bounds;
		int fps;
		bool SFX, vSync;
		string titleGame;

		//Read details from file
		fstream fin;
		fin.open("settings/window.ini");
		getline(fin, titleGame);			//To Skip the first line in file
		fin >> bounds.width >> bounds.height;
		fin >> fps;
		fin >> SFX;
		fin >> vSync;


		//apply settings
		double scale = (double)bounds.width / (double)window->getSize().x; //Handle Scale

		//Handle Resolution Details after changes
		this->RESOLUTION_SETTINGS->List->elements->setPosition(
			RESOLUTION_SETTINGS->List->elements->getPosition().x * scale,
			RESOLUTION_SETTINGS->List->elements->getPosition().y * scale
		);
		this->RESOLUTION_SETTINGS->List1->elements->setPosition(
			RESOLUTION_SETTINGS->List1->elements->getPosition().x * scale,
			RESOLUTION_SETTINGS->List1->elements->getPosition().y * scale
		);

		this->RESOLUTION_SETTINGS->List->text->setPosition(
			RESOLUTION_SETTINGS->List->text->getPosition().x * scale,
			RESOLUTION_SETTINGS->List->text->getPosition().y * scale
		);
		this->RESOLUTION_SETTINGS->List1->text->setPosition(
			RESOLUTION_SETTINGS->List1->text->getPosition().x * scale,
			RESOLUTION_SETTINGS->List1->text->getPosition().y * scale
		);
		this->RESOLUTION_SETTINGS->List->elements->setSize(Vector2f(
			RESOLUTION_SETTINGS->List->elements->getSize().x * scale,
			RESOLUTION_SETTINGS->List->elements->getSize().y * scale)
		);
		this->RESOLUTION_SETTINGS->List1->elements->setSize(Vector2f(
			RESOLUTION_SETTINGS->List1->elements->getSize().x * scale,
			RESOLUTION_SETTINGS->List1->elements->getSize().y * scale)
		);

		this->RESOLUTION_SETTINGS->List->text->setCharacterSize(
			RESOLUTION_SETTINGS->List->text->getCharacterSize() * scale
		);
		this->RESOLUTION_SETTINGS->List1->text->setCharacterSize(
			RESOLUTION_SETTINGS->List1->text->getCharacterSize() * scale
		);


		//Handle FPS Details after changes
		this->FPS_SETTINGS->List->elements->setPosition(
			FPS_SETTINGS->List->elements->getPosition().x * scale,
			FPS_SETTINGS->List->elements->getPosition().y * scale
		);
		this->FPS_SETTINGS->List1->elements->setPosition(
			FPS_SETTINGS->List1->elements->getPosition().x * scale,
			FPS_SETTINGS->List1->elements->getPosition().y * scale
		);

		this->FPS_SETTINGS->List->text->setPosition(
			FPS_SETTINGS->List->text->getPosition().x * scale,
			FPS_SETTINGS->List->text->getPosition().y * scale
		);
		this->FPS_SETTINGS->List1->text->setPosition(
			FPS_SETTINGS->List1->text->getPosition().x * scale,
			FPS_SETTINGS->List1->text->getPosition().y * scale
		);
		this->FPS_SETTINGS->List->elements->setSize(Vector2f(
			FPS_SETTINGS->List->elements->getSize().x * scale,
			FPS_SETTINGS->List->elements->getSize().y * scale)
		);
		this->FPS_SETTINGS->List1->elements->setSize(Vector2f(
			FPS_SETTINGS->List1->elements->getSize().x * scale,
			FPS_SETTINGS->List1->elements->getSize().y * scale)
		);

		this->FPS_SETTINGS->List->text->setCharacterSize(
			FPS_SETTINGS->List->text->getCharacterSize() * scale
		);
		this->FPS_SETTINGS->List1->text->setCharacterSize(
			FPS_SETTINGS->List1->text->getCharacterSize() * scale
		);



		//Handle vSync Details after changes
		this->VERTICAL_SYNC_SETTINGS->List->elements->setPosition(
			VERTICAL_SYNC_SETTINGS->List->elements->getPosition().x * scale,
			VERTICAL_SYNC_SETTINGS->List->elements->getPosition().y * scale
		);
		this->VERTICAL_SYNC_SETTINGS->List1->elements->setPosition(
			VERTICAL_SYNC_SETTINGS->List1->elements->getPosition().x * scale,
			VERTICAL_SYNC_SETTINGS->List1->elements->getPosition().y * scale
		);

		this->VERTICAL_SYNC_SETTINGS->List->text->setPosition(
			VERTICAL_SYNC_SETTINGS->List->text->getPosition().x * scale,
			VERTICAL_SYNC_SETTINGS->List->text->getPosition().y * scale
		);
		this->VERTICAL_SYNC_SETTINGS->List1->text->setPosition(
			VERTICAL_SYNC_SETTINGS->List1->text->getPosition().x * scale,
			VERTICAL_SYNC_SETTINGS->List1->text->getPosition().y * scale
		);

		this->VERTICAL_SYNC_SETTINGS->List->elements->setSize(Vector2f(
			VERTICAL_SYNC_SETTINGS->List->elements->getSize().x * scale,
			VERTICAL_SYNC_SETTINGS->List->elements->getSize().y * scale)
		);
		this->VERTICAL_SYNC_SETTINGS->List1->elements->setSize(Vector2f(
			VERTICAL_SYNC_SETTINGS->List1->elements->getSize().x * scale,
			VERTICAL_SYNC_SETTINGS->List1->elements->getSize().y * scale)
		);

		this->VERTICAL_SYNC_SETTINGS->List->text->setCharacterSize(
			VERTICAL_SYNC_SETTINGS->List->text->getCharacterSize() * scale
		);
		this->VERTICAL_SYNC_SETTINGS->List1->text->setCharacterSize(
			VERTICAL_SYNC_SETTINGS->List1->text->getCharacterSize() * scale
		);


		//Handle SFX Details after changes
		this->SFX_SETTINGS->List->elements->setPosition(
			SFX_SETTINGS->List->elements->getPosition().x * scale,
			SFX_SETTINGS->List->elements->getPosition().y * scale
		);
		this->SFX_SETTINGS->List1->elements->setPosition(
			SFX_SETTINGS->List1->elements->getPosition().x * scale,
			SFX_SETTINGS->List1->elements->getPosition().y * scale
		);

		this->SFX_SETTINGS->List->text->setPosition(
			SFX_SETTINGS->List->text->getPosition().x * scale,
			SFX_SETTINGS->List->text->getPosition().y * scale
		);
		this->SFX_SETTINGS->List1->text->setPosition(
			SFX_SETTINGS->List1->text->getPosition().x * scale,
			SFX_SETTINGS->List1->text->getPosition().y * scale
		);
		this->SFX_SETTINGS->List->elements->setSize(Vector2f(
			SFX_SETTINGS->List->elements->getSize().x * scale,
			SFX_SETTINGS->List->elements->getSize().y * scale)
		);
		this->SFX_SETTINGS->List1->elements->setSize(Vector2f(
			SFX_SETTINGS->List1->elements->getSize().x * scale,
			SFX_SETTINGS->List1->elements->getSize().y * scale)
		);

		this->SFX_SETTINGS->List->text->setCharacterSize(
			SFX_SETTINGS->List->text->getCharacterSize() * scale
		);
		this->SFX_SETTINGS->List1->text->setCharacterSize(
			SFX_SETTINGS->List1->text->getCharacterSize() * scale
		);

		//Resize Save Details 
		this->SAVE_SETTINGS->button->rect->setPosition(
			SAVE_SETTINGS->button->rect->getPosition().x * scale,
			SAVE_SETTINGS->button->rect->getPosition().y * scale
		);
		this->SAVE_SETTINGS->button->text->setPosition(
			SAVE_SETTINGS->button->text->getPosition().x * scale,
			SAVE_SETTINGS->button->text->getPosition().y * scale
		);
		this->SAVE_SETTINGS->button->rect->setSize(Vector2f(
			SAVE_SETTINGS->button->rect->getSize().x * scale,
			SAVE_SETTINGS->button->rect->getSize().y * scale)
		);
		this->SAVE_SETTINGS->button->text->setCharacterSize(
			SAVE_SETTINGS->button->text->getCharacterSize() * scale
		);

		this->BACK_GROUND->setPosition(BACK_GROUND->getPosition().x * scale, BACK_GROUND->getPosition().y * scale);
		this->BACK_GROUND->setSize(Vector2f(BACK_GROUND->getSize().x * scale, BACK_GROUND->getSize().y * scale));
		window->create(bounds, titleGame, Style::Titlebar | Style::Close | Style::Fullscreen);

		window->setFramerateLimit(fps);
		if (SFX)
		{
			//SFX is open
		}
		else {
			//SFX is close
		}
		window->setVerticalSyncEnabled(vSync);

		apply = 0;
	}
}

//Gray Rectangle
void menuSettings::renderBackGround(RenderTarget* window)
{
	window->draw(this->bGround);
	window->draw(*this->BACK_GROUND);
}

menuSettings::menuSettings(sf::RenderWindow* window, std::stack<states*>* m, Event& ev) :states(window, m), RESOLUTION_SETTINGS(new Resolution(3)), FPS_SETTINGS(new fps(6)),
SFX_SETTINGS(new SFX()), VERTICAL_SYNC_SETTINGS(new vSync()),
SAVE_SETTINGS(new Save()), BACK_GROUND(new RectangleShape())
{
	setResolution_Settings(window);
	setFPS_Settings(window);
	setSFX_Settings(window);
	setVSync_Settings(window);
	setSave_Settings(window);
	BACK_GROUND->setPosition(window->getSize().x / 30.f, window->getSize().y / 4.5);
	BACK_GROUND->setFillColor(Color(128, 128, 128, 100));
	BACK_GROUND->setSize(Vector2f(window->getSize().x / 2, window->getSize().y / 2)); //900 490
	event = ev;
}

//Initialize Atrributes
//Delete Dynamic Atrributes
menuSettings::~menuSettings()
{
	delete RESOLUTION_SETTINGS;
	delete FPS_SETTINGS;
	delete SFX_SETTINGS;
	delete VERTICAL_SYNC_SETTINGS;
	delete SAVE_SETTINGS;
	delete BACK_GROUND;
}
