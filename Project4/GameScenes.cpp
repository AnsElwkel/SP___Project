#include "GameScenes.h"
using namespace sf;

Text t[31];
string s[31];
int i[31];//Typing index

Font f;
bool tch = 1;
GameScenes::GameScenes()
{
}
void GameScenes::DisplayText(Text& t, string& s, int& idx, enemies& e, character& h, string talker)
{
	bool tech = 0;
	Text te, te2;
	te.setFont(f);
	te.setString("Press Enter To Continue");
	Vector2f teSize = te.getGlobalBounds().getSize();
	te.setScale(scale * ((float)4 / 5));
	te.setOrigin(teSize.x / 2, teSize.y / 2);
	te.setPosition(WindowSize.x / 2, window->getSize().y - te.getCharacterSize());
	te.setFillColor(Color::White);
	te2.setFont(f);
	te2.setString("Hold RightShift To Speed Up");
	Vector2f teSize2 = te2.getGlobalBounds().getSize();
	te2.setScale(scale * ((float)4 / 5));
	te2.setOrigin(teSize2.x / 2, teSize2.y / 2);
	te2.setPosition(WindowSize.x / 2, window->getSize().y - te2.getCharacterSize());
	te2.setFillColor(Color::White);

	if (Keyboard::isKeyPressed(Keyboard::RShift))
		TextDelay = 0.0005, ComaDelay = 0.0005, SlowTextDelay = 0.0005;
	else
	{
		if (TextDelay != InitSlowTextDelay)
			TextDelay = InitTextDelay;
		ComaDelay = InitComaDelay, SlowTextDelay = InitSlowTextDelay;
	}

	if (TextTimer < 0)
	{
		if (tch)
		{
			if (typech == 0)
				typech = 1, typing.play();
			t.setString(t.getString() + s[idx]);
			if (t.findCharacterPos(idx).x > WindowSize.x * 9 / 10.f && s[idx] == ' ' /*&& s[idx - 2] != ' '*/)
				t.setString(t.getString() + '\n');
		}
		if (idx + 2 < s.size() && s[idx + 1] == '/' && s[idx + 2] == '/')
		{
			tch = 0;
			typech = 0;
			typing.stop();
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				tch = 1;
				tech = 0;
				t.setString("");
				idx += 3;
			}
			else
			{
				window->draw(t);
				tech = 1;
				window->draw(te);
			}
		}
		else if (s[idx] == ',')
			TextTimer = ComaDelay, idx++, typech = 0, typing.stop();
		else if (idx + 1 < s.size() && s[idx + 1] != ' ')
			TextTimer = TextDelay, idx++;
		else
			idx++;
	}
	else
	{
		TextTimer -= DeltaTime;
	}
	if (talker == "no")
	{
		window->draw(t);
		if (!tech)
			window->draw(te2);
	}
	else
	{
		window->draw(h.sprite);
		window->draw(e.sprite);
		if (talker == "hero")
			window->draw(HeroTalk.sprite);
		else
			window->draw(FinalBossTalk.sprite);
		window->draw(t);
		if (!tech)
			window->draw(te2);
	}
}

string si;
Text ti;
void GameScenes::InstructionsSceneSet()
{
	ti.setFont(f);
	ti.setString("");
	ti.setFillColor(Color::White);
	ti.setScale(scale);
	ti.setPosition(50, 300);
	si = "Use Arrows To Move\n\nPress X To Attack\n\nPress C To Dodge Attacks\n\nHold Left Shift To Run//";
}

int ii = 0;
RectangleShape screen;
void GameScenes::InstructionsScene(enemies& e, character& h)
{
	screen.setSize({ (float)window->getSize().x, (float)window->getSize().y });
	screen.setFillColor(Color::Black);
	if (ii < si.size())
	{
		DisplayText(ti, si, ii, e, h, "no");
	}
	else if (ii == si.size())
	{
		ii++;
		window->draw(h.sprite);
		window->draw(e.sprite);
		window->draw(HeroTalk.sprite);
		window->draw(screen);
		window->draw(ti);
	}
	else
	{
		ii++;
		InstructionsSceneCh = 0;
	}
}

void GameScenes::Scene0Set()
{
	f.loadFromFile("./res/Fonts/minecraft_font.ttf");
	Btyping.loadFromFile("./res/Sounds/typing.mp3");
	typing.setBuffer(Btyping);
	s[0] = "It all starts when i was traveling with the only person i know and trust in the whole world, everyone we meet ";
	s[0] += "thinks we are brothers, however, we are not, but he was like a brother to me//";
	s[0] += "We were discovering the surroundings of our village until we fell in a monsters trap, i ran away whith all my strength,";
	s[0] += " I thought my friend will catch up with me, i waited far away, but he did not make it//";
	s[0] += "I lost my best friend back then, So I decided to take revenge at any cost and kill all these creepy monsters and relieve people from their evil//";
	t[0].setFont(f);
	t[0].setString("");
	t[0].setFillColor(Color::White);
	t[0].setScale(scale);
	t[0].setPosition(32, window->getSize().y / 2 - 64);
}

void GameScenes::scene0(enemies& e, character& h)
{
	if (i[0] < s[0].size())
	{
		DisplayText(t[0], s[0], i[0], e, h, "no");
	}
	else if (i[0] == s[0].size())
	{
		i[0]++;
		window->draw(h.sprite);
		window->draw(e.sprite);
		window->draw(HeroTalk.sprite);
		window->draw(screen);
		window->draw(t[0]);
	}
	else
	{
		i[0]++;
		scene0ch = 0;
	}
}

void GameScenes::Scene1Set(enemies& e, character& h)
{
	FinalBossTalk.scale = { WindowSize.x / 320, WindowSize.y / 180 };
	FinalBossTalk.set(0, WindowSize.y - FinalBossTalk.WalkSize.y * FinalBossTalk.scale.y, 0, "FinalBoss", "NoShadow", "NoShield", 0);
	HeroTalk.who = h.who;
	HeroTalk.scale = { WindowSize.x / 320, WindowSize.y / 180 };
	HeroTalk.set(0, WindowSize.y - HeroTalk.WalkSize.y * HeroTalk.scale.y, 0);
	for (int i = 1; i < 31; i++)
	{
		t[i].setFont(f);
		t[i].setString("");
		t[i].setFillColor(Color::White);
		t[i].setScale(scale);
		t[i].setPosition(HeroTalk.WalkSize.x * HeroTalk.scale.x / 1.5, window->getSize().y - HeroTalk.WalkSize.y * HeroTalk.scale.y / 1.5);
	}
	e.sprite.setOrigin(e.WalkSize / 2.f);
	e.sprite.setPosition(window->getSize().x * 3 / 4, window->getSize().y / 2);
	e.sprite.setTextureRect(IntRect(0, e.WalkLeftIndex, e.WalkSize.x, e.WalkSize.y));
	h.sprite.setOrigin(h.WalkSize / 2.f);
	h.sprite.setPosition((float)window->getSize().x / 4, (float)window->getSize().y / 2);
	h.sprite.setTextureRect(IntRect(0, h.WalkRightIndex, h.WalkSize.x, h.WalkSize.y));
	s[1] = "Ah, He is so strong//";
}

int che = 1, ieye = 255;
float EyeTimer = 0, EyeDelay = 0.009;
bool BlinkCheck = true;
RectangleShape eye;
void GameScenes::blink()
{
	eye.setSize({ (float)window->getSize().x, (float)window->getSize().y });
	eye.setFillColor(Color(0, 0, 0, ieye));
	if (ieye >= 0 && BlinkCheck)
	{
		if (EyeTimer < 0)
		{
			EyeTimer = EyeDelay;
			ieye--;
			if (ieye == 110 && che == 1)
				BlinkCheck = false, che++;
			else if (ieye == 0 && che == 2)
				Blinking = false;
		}
		else
		{
			EyeTimer -= DeltaTime;
		}
	}
	else if (!BlinkCheck)
	{
		if (EyeTimer < 0)
		{
			EyeTimer = EyeDelay;
			ieye++;
			if (ieye == 255)
				BlinkCheck = true, EyeDelay = 0.002;
		}
		else
		{
			EyeTimer -= DeltaTime;
		}
	}
	window->draw(eye);
}

void GameScenes::BlinkReset()
{
	che = 1;
	ieye = 255;
	EyeDelay = 0.009;
	Blinking = 1;
}

void GameScenes::scene1(enemies& e, character& h)
{
	if (Blinking)
	{
		window->draw(h.sprite);
		window->draw(e.sprite);
		blink();
	}
	else if (i[1] < s[1].size())
	{
		DisplayText(t[1], s[1], i[1], e, h, "hero");
	}
	else
	{

		i[1]++;
		BlinkReset();
		scene1ch = 0;
	}
}

void GameScenes::Scene2Set()
{
	s[2] = "Do you think you can Defeat me, hhh, You are a useles pathetic weak hero who does not even deserve to be killed by my blade//";
	s[3] = "Egh, i will take revenge on my friend and defeat you at any cost//";
	s[4] = "HHHH, your friend is still alive, but you will never see him again//";
	s[5] = "What do you mean?!";
	s[6] = "HaHaHaHa, FareWell, Hero!//";
}

int inap = 0;
float NapTimer = 0, NapDelay = 0.015;
RectangleShape nap;
void GameScenes::scene2(enemies& e, character& h)
{
	nap.setSize({ (float)window->getSize().x, (float)window->getSize().y });
	nap.setFillColor(Color(0, 0, 0, inap));
	HeroTalk.sprite.setTextureRect(IntRect(HeroTalk.DieSize.x * 3, HeroTalk.DieIndex, HeroTalk.DieSize.x, HeroTalk.DieSize.y));
	if (i[2] < s[2].size())
	{
		DisplayText(t[2], s[2], i[2], e, h, "FinalBoss");
	}
	else if (i[3] < s[3].size())
	{
		DisplayText(t[3], s[3], i[3], e, h, "hero");
	}
	else if (i[4] < s[4].size())
	{
		DisplayText(t[4], s[4], i[4], e, h, "FinalBoss");
	}
	else if (i[5] < s[5].size())
	{
		TextDelay = SlowTextDelay;
		DisplayText(t[5], s[5], i[5], e, h, "hero");
	}
	else if (h.IsAlive)
	{
		TextDelay = InitTextDelay;
		typing.stop();
		typech = 0;
		h.die("");
		HeroTalk.sprite.setTextureRect(h.sprite.getTextureRect());
		e.FinalBossDraw(h);
		window->draw(HeroTalk.sprite);
		window->draw(t[5]);
	}
	else if (!h.IsAlive)
	{
		if (inap < 255)
		{
			HeroTalk.sprite.setTextureRect(h.sprite.getTextureRect());
			if (NapTimer < 0)
			{
				NapTimer = NapDelay;
				inap++;
			}
			else
			{
				NapTimer -= DeltaTime;
			}
			e.FinalBossDraw(h);
			window->draw(HeroTalk.sprite);
			window->draw(t[5]);
			window->draw(nap);
		}
		else if (i[6] < s[6].size())
		{
			window->draw(nap);
			DisplayText(t[6], s[6], i[6], e, h, "no");
			t[6].setOrigin(t[6].getLocalBounds().getSize() / 2.f);
			t[6].setPosition(WindowSize / 2.f);
		}
		else
		{
			i[6]++;
			HeroTalk.sprite.setTextureRect(IntRect(0, HeroTalk.WalkDownIndex, HeroTalk.WalkSize.x, HeroTalk.WalkSize.y));
			scene2ch = 0;
		}
	}
}

void GameScenes::Scene3Set()
{
	s[7] = "hmm, So you survived my small monsters, hero//";
	s[8] = "I defeated them all, and now it is your turn, i will defeat you and get my friend back//";
	s[9] = "hahaha, come to your death you fool//";
}

void GameScenes::scene3(enemies& e, character& h)
{
	if (!h.arrive)
	{
		h.GoTo({ ((float)window->getSize().x / 4), ((float)window->getSize().y / 2) }, 3, 200);
		window->draw(h.sprite);
		window->draw(e.sprite);
	}
	else if (i[7] < s[7].size())
	{
		e.sprite.setTextureRect(IntRect(0, e.WalkLeftIndex, e.WalkSize.x, e.WalkSize.y));
		h.sprite.setTextureRect(IntRect(0, h.WalkRightIndex, h.WalkSize.x, h.WalkSize.y));
		DisplayText(t[7], s[7], i[7], e, h, "FinalBoss");
	}
	else if (i[8] < s[8].size())
	{
		i[7]++;
		DisplayText(t[8], s[8], i[8], e, h, "hero");
	}
	else if (i[9] < s[9].size())
	{
		i[8]++;
		DisplayText(t[9], s[9], i[9], e, h, "FinalBoss");
	}
	else
	{
		i[9]++;
		scene3ch = 0;
		h.arrive = 0;
	}
}

void GameScenes::Scene4Set()
{
	s[10] = "Okay Okay, you are strong, you win, i will take you to your friend//";
	s[11] = "hh, you better do//";
}

void GameScenes::scene4(enemies& e, character& h)
{
	FinalBossTalk.sprite.setTextureRect(IntRect(FinalBossTalk.DieSize.x * 3, FinalBossTalk.DieIndex, FinalBossTalk.DieSize.x, FinalBossTalk.DieSize.y));
	if (i[10] < s[10].size())
	{
		DisplayText(t[10], s[10], i[10], e, h, "FinalBoss");
	}
	else if (i[11] < s[11].size())
	{
		i[10]++;
		DisplayText(t[11], s[11], i[11], e, h, "hero");
	}
	else
	{
		i[11]++;
		FinalBossTalk.sprite.setTextureRect(IntRect(0, FinalBossTalk.WalkDownIndex, FinalBossTalk.WalkSize.x, FinalBossTalk.WalkSize.y));
		scene4ch = false;
	}
}

Sprite FakeBrother;
Texture t1FakeBrother, t2FakeBrother;
void GameScenes::Scene5Set()
{
	t1FakeBrother.loadFromFile("./res/enemies/FakeBrother/NoShadow/CoverWeapon/FakeBrother.png");
	t2FakeBrother.loadFromFile("./res/enemies/FakeBrother/NoShadow/NoCoverWeapon/FakeBrother.png");
	FakeBrother.setTexture(t1FakeBrother);
	FakeBrother.setScale(WindowSize.x / 853.33f, WindowSize.y / 480.f);
	FakeBrother.setOrigin(32, 32);
	FakeBrother.setTextureRect(IntRect(0, 64 * 8, 64, 64));
	FakeBrother.setPosition(WindowSize.x / 2, WindowSize.y / 2 + 50);
	s[12] = "Siltara, Brother, Are you okay?//";
	s[30] = "A Zombie??!!//";
	s[13] = "Where is My friend you freaking pumpkin head??//";
	s[14] = "hhhhhhhhhh, hahahaha, aah hero, my friend, my best friend, What you were looking for was always infront of you//";
	s[15] = "Siltara???????!//";
	s[16] = "Yes friend, it is me//";
	s[17] = "but, how?, why??//";
	s[18] = "Why?!, Are you asking me Why??!, dont you know what you have done to me, dont you know what happened after you ";
	s[18] += "ran away that day and left me behind//";
	s[19] = "you left me to my death and ran away from some weak monsters, we could have killed them and survived that ";
	s[19] += "sitiuation together, but because of your cowrdness I am who i am today//";
	s[20] = "Sorry Siltara, but my fear defeated me, i didnt realize what was happening until I was far away from you, forgive me//";
	s[21] = "A useless pathetic excuse just like you, No forgiveness today brother, my only cure is to step on your dead body//";
	s[22] = "Sorry siltara, But i wont let you kill me today//";
	s[23] = "hhhhhh, we will see, my old friend//";
}

bool chw = 0, chh = 1, ttch = 1, IsFBalive = 1, ach = 1, bch = 1, cch = 1;
float AnemationTimer = 0, AnemationDelay = 0.03;
float HitTimer = 0, HitSpeed = 0.045;
float DeathTimer = 0, DeathDelay = 0.7;
int heroi1 = 6, heroi2 = 0, FBi = 0, Deathi = 0;
void GameScenes::scene5(enemies& e, character& h)
{
	if (!e.IsStanding)
	{
		e.die("stand");
		e.FinalBossDraw(h);
	}
	else if (!e.arrive && ach)
	{
		e.GoTo({ WindowSize.x / 2, WindowSize.y }, 300);
		e.FinalBossDraw(h);
	}
	else if (!h.arrive && !chw)
	{
		e.sprite.setPosition(WindowSize.x / 2 + 100, 100);
		ach = 0;
		e.arrive = 0;
		e.sprite.setTextureRect(IntRect(0, e.WalkDownIndex, e.WalkSize.x, e.WalkSize.y));
		h.GoTo({ WindowSize.x / 2, WindowSize.y }, 3, 300);
		window->draw(h.sprite);
	}
	else if (i[12] < s[12].size())
	{
		if (h.weapon != "LongSword")
			h.ChangeWeapon("LongSword");
		h.sprite.setPosition(WindowSize.x / 2, 64);
		h.sprite.setTextureRect(IntRect(0, h.WalkDownIndex, h.WalkSize.x, h.WalkSize.y));
		window->draw(FakeBrother);
		DisplayText(t[12], s[12], i[12], e, h, "hero");
		h.arrive = 0;
		chw = 1;
	}
	else if (!h.arrive && bch)
	{
		h.GoTo({ WindowSize.x / 2, WindowSize.y / 2 }, 3, 300);
		window->draw(FakeBrother);
		window->draw(h.sprite);
		window->draw(e.sprite);
	}
	else if (heroi2 < 5 || chh)
	{
		bch = 0;
		h.arrive = 0;
		if (heroi1 > 0 && chh)
		{
			if (ttch)
				FakeBrother.setTexture(t2FakeBrother), ttch = 0;
			if (AnemationTimer < 0 && heroi1 > 0)
			{

				heroi1--;
				h.sprite.setTextureRect(IntRect(heroi1 * h.WalkSize.x, h.WalkDownIndex, h.WalkSize.x, h.WalkSize.y));
				h.sprite.setOrigin(h.WalkSize / 2.f);
				AnemationTimer = AnemationDelay;
			}
			else
			{
				AnemationTimer -= DeltaTime;
			}
			h.sprite.move(0, -110 * DeltaTime);
		}
		else
			chh = 0;
		if (HitTimer < 0 && FBi < 5)
		{
			FBi++;
			FBi %= 6;
			FakeBrother.setTextureRect(IntRect(64 * FBi, 64 * 12, 64, 64));
			HitTimer = HitSpeed;
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		if (i[30] < s[30].size())
			DisplayText(t[30], s[30], i[30], e, h, "hero");
		else if (!chh && FBi == 5)
		{
			FakeBrother.setTextureRect(IntRect(0, 64 * 8, 64, 64));
			HitSpeed = 0.2;
			if (HitTimer < 0 && heroi1 != 6)
			{
				heroi1++;
				heroi1 %= 6;
				h.sprite.setTextureRect(IntRect(heroi1 * h.HitSize.x, h.HitDownIndex, h.HitSize.x, h.HitSize.y));
				h.sprite.setOrigin(h.HitSize / 2.f);
				HitTimer = HitSpeed;
				if (heroi1 == 5)
					heroi1++;
			}
			else {
				HitTimer -= DeltaTime;
			}
			if (HitTimer < 0 && heroi1 == 6)
			{
				heroi2++;
				heroi2 %= 6;
				h.sprite.setTextureRect(IntRect(heroi2 * h.HitSize.x, 39 * 64, h.HitSize.x, h.HitSize.y));
				h.sprite.setOrigin(h.HitSize / 2.f);
				HitTimer = HitSpeed;
			}
			else {
				HitTimer -= DeltaTime;
			}
		}
		window->draw(FakeBrother);
		window->draw(h.sprite);
		window->draw(e.sprite);
	}
	else if (IsFBalive)
	{
		h.sprite.setTextureRect(IntRect(0, h.WalkDownIndex, h.WalkSize.x, h.WalkSize.y));
		h.sprite.setOrigin(h.WalkSize / 2.f);
		if (DeathTimer < 0)
		{
			Deathi++;
			Deathi %= 6;
			FakeBrother.setTextureRect(IntRect(64 * Deathi, 64 * 20, 64, 64));
			FakeBrother.setOrigin(32, 32);
			DeathTimer = DeathDelay;
			if (Deathi == 5)
				IsFBalive = 0;
		}
		else
		{
			DeathTimer -= DeltaTime;
		}
		window->draw(FakeBrother);
		window->draw(h.sprite);
		window->draw(e.sprite);
	}
	else if (i[13] < s[13].size())
	{
		h.sprite.setTextureRect(IntRect(0, h.WalkUpIndex, h.WalkSize.x, h.WalkSize.y));
		i[12]++;
		DisplayText(t[13], s[13], i[13], e, h, "hero");
	}
	else if (i[14] < s[14].size())
	{
		i[13]++;
		DisplayText(t[14], s[14], i[14], e, h, "FinalBoss");
	}
	else if (!e.arrive)
	{
		e.GoTo({ WindowSize.x / 2, 0 }, 300);
		e.FinalBossDraw(h);
	}
	else if (!h.arrive && cch)
	{
		h.GoTo({ WindowSize.x / 2, 0 }, 3, 300);
		window->draw(h.sprite);
	}
	else if (h.arrive && cch)
	{
		e.set(WindowSize.x / 2, 100, 1000, "FinalBoss", "NoShadow", "Shield", 1);
		h.sprite.setPosition(WindowSize.x / 2, WindowSize.y);
		e.sprite.setTextureRect(IntRect(0, h.WalkUpIndex, h.WalkSize.x, h.WalkSize.y));
		FinalBossTalk.sprite.setTexture(e.SpriteTexture);
		FinalBossTalk.sprite.setTextureRect(IntRect(0, FinalBossTalk.WalkDownIndex, FinalBossTalk.WalkSize.x, FinalBossTalk.WalkSize.y));
		cch = 0;
		h.arrive = 0;
	}
	else if (!h.arrive)
	{
		h.GoTo({ WindowSize.x / 2, WindowSize.y / 2 + 100 }, 3, 300);
		e.FinalBossDraw(h);
	}
	else if (i[15] < s[15].size())
	{
		e.sprite.setTextureRect(IntRect(0, e.WalkDownIndex, 64, 64));
		DisplayText(t[15], s[15], i[15], e, h, "hero");
	}
	else if (i[16] < s[16].size())
	{
		i[15]++;
		DisplayText(t[16], s[16], i[16], e, h, "FinalBoss");
	}
	else if (i[17] < s[17].size())
	{
		i[16]++;
		DisplayText(t[17], s[17], i[17], e, h, "hero");
	}
	else if (i[18] < s[18].size())
	{
		i[17]++;
		DisplayText(t[18], s[18], i[18], e, h, "FinalBoss");
	}
	else if (i[19] < s[19].size())
	{
		i[18]++;
		DisplayText(t[19], s[19], i[19], e, h, "FnalBoss");
	}
	else if (i[20] < s[20].size())
	{
		i[19]++;
		DisplayText(t[20], s[20], i[20], e, h, "hero");
	}
	else if (i[21] < s[21].size())
	{
		i[20]++;
		DisplayText(t[21], s[21], i[21], e, h, "FinalBoss");
	}
	else if (i[22] < s[22].size())
	{
		i[21]++;
		DisplayText(t[22], s[22], i[22], e, h, "hero");
	}
	else if (i[23] < s[23].size())
	{
		i[22]++;
		DisplayText(t[23], s[23], i[23], e, h, "FinalBoss");
	}
	else
		scene5ch = 0;
}

void GameScenes::Scene6Set(character h)
{
	s[24] = "Why do you keep avoiding my attacks and run away without killing me, dont tell me you are afraid of killing a human//";
	s[25] = "Siltara, I cant kill my best friend becuse of some stupid act he did as a reaction on my betrayal, ";
	s[25] += "it was my fault Siltara, and you have all the right to be mad, but forgive me please, i know you still have kindness inside//";
	s[26] = "But i threw you to the monsters and tried to kill you many times, I cant stop now after all what i have done//";
	s[27] = "No Siltara, you can, you tried to kill me but i am stell alive, and that all what mater, We can always ";
	s[27] += "regret our mistakes and correct them";
	s[28] = "Come here Siltara, I know its been tough while you were alone all this years//";
	s[29] = h.who + "..........//";
	t[29].setString("Siltara: ");
	t[28].setPosition(32, WindowSize.y / 2 - t[28].getCharacterSize() / 2);
}

int iCS = 0;
float CSTimer = 0, CSDelay = 0.015;
RectangleShape CS;
void GameScenes::scene6(enemies& e, character& h)
{
	if (i[24] < s[24].size())
	{
		e.LookAt(h.sprite);
		i[23]++;
		DisplayText(t[24], s[24], i[24], e, h, "FinalBoss");
	}
	else if (i[25] < s[25].size())
	{
		h.LookAt(e.sprite);
		i[24]++;
		DisplayText(t[25], s[25], i[25], e, h, "hero");
	}
	else if (i[26] < s[26].size())
	{
		if (!h.arrive)
			h.GoTo(e.sprite.getPosition(), 30 * e.scale.x, 100);
		e.die("defeated");
		FinalBossTalk.sprite.setTextureRect(e.sprite.getTextureRect());
		i[25]++;
		DisplayText(t[26], s[26], i[26], e, h, "FinalBoss");
	}
	else if (i[27] < s[27].size())
	{
		if (!h.arrive)
			h.GoTo(e.sprite.getPosition(), 70 * e.scale.x, 100);
		i[26]++;
		DisplayText(t[27], s[27], i[27], e, h, "hero");
	}
	else if (iCS < 255)
	{
		typing.stop();
		typech = 0;
		CS.setSize({ (float)window->getSize().x, (float)window->getSize().y });
		CS.setFillColor(Color(0, 0, 0, iCS));
		if (CSTimer < 0)
		{
			iCS++;
			CSTimer = CSDelay;
		}
		else
		{
			CSTimer -= DeltaTime;
		}
		e.FinalBossDraw(h);
		window->draw(HeroTalk.sprite);
		window->draw(t[27]);
		window->draw(CS);
	}
	else if (i[28] < s[28].size())
	{
		i[27]++;
		DisplayText(t[28], s[28], i[28], e, h, "no");
	}
	else if (i[29] < s[29].size())
	{
		i[28]++;
		DisplayText(t[29], s[29], i[29], e, h, "no");
		t[29].setOrigin(t[29].getLocalBounds().getSize() / 2.f);
		t[29].setPosition(WindowSize / 2.f);
	}
	else
	{
		scene6ch = 0;
		i[29]++;
	}
}

Text tte;
string sse;
void GameScenes::EndSceneSet()
{
	tte.setFont(f);
	tte.setString("");
	tte.setFillColor(Color::White);
	tte.setScale(scale);
	tte.setPosition(64, 128);
	sse = "Creators:\n\nYusuf Mahmud\n\nHossam El3araby\n\nMohamed Ramadan\n\nHossam ElNemr The Animal\n\nAnas Elwkel\n\nAhmed Labib\n\nMohamed Zanaty//";
}

int iie = 0;
void GameScenes::EndScene(enemies &e, character &h)
{
	if (iie < sse.size())
	{
		DisplayText(tte, sse, iie, e, h, "no");
	}
	else
	{
		iie++;
		EndSceneCh = 0;
	}
}

void GameScenes::GameScenesSet(enemies& e, character& h)
{
	Scene0Set();
	InstructionsSceneSet();
	Scene1Set(e, h);
	Scene2Set();
	Scene3Set();
	Scene4Set();
	Scene5Set();
	Scene6Set(h);
	EndSceneSet();
}