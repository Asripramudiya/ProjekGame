#include "maskot.h"
#include "batu.h"
#include "komponen.h"
#include "tambahan.h"

#include <sl.h>
#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>

Maskot maskot(200, 100);		
batu vehicle(200, 400, 2);		
batu vehicle2(250, 600, 2.5);		
tamb ikan(100, 2500);	

enum GameStatus :int { Mulai, Main, Pause, GameOver };
GameStatus state = GameStatus::Mulai;

int road;
int font;
int GbIkan;
std::string pemain;

int score = 0;
int count = 0;
int hiscore = 0;
int fuel = 20;

void info();
void key();
bool isCollide(object* e1, object* e2, const double h);

namespace game
{
	void init()
	{
		std::cout << "	*********************************************************\n";
		std::cout << "	**                       EATING CAT	               **\n";
		std::cout << "	*********************************************************\n";


		std::cout << "Nama Pemain: ";
		std::getline(std::cin, pemain);
		if (pemain == "")
			pemain = "Noname";

		slWindow(500, 670, "EatingCat", false);
		slSetBackColor(0, 0.4, 0.2);

		std::cout << "loading ...\n";
		maskot.loadTexture();
		vehicle.loadTexture();
		vehicle2.loadTexture();
		ikan.loadTexture();

		road = slLoadTexture(TEX_BEGE);
		font = slLoadFont(FNT_STYLE);
		slSetFont(font, 20);

		vehicle.setBatuSpd(-3);
		vehicle2.setBatuSpd(-2);
		ikan.setTambSpd(-6);
	}


	void run()
	{
		std::cout << "Mainkan Sekarang\n";
		while (!slShouldClose())
		{

			slSprite(road, SCR_W / 2, SCR_H / 2, SCR_W, SCR_H);

			maskot.draw();
			vehicle.draw();
			vehicle2.draw();
			ikan.draw();

			info();
			key();

			if (state == GameStatus::Main)
			{

				maskot.update();
				vehicle.update();
				vehicle2.update();
				ikan.updatekoin();
				count++;
				if (count == 100)
				{
					score++;
					count = 0;
				}

				if (count == 30)
				{
					fuel--;
				}

				if (isCollide(&maskot, &vehicle, 50.0))
				{
					if (score >= hiscore)
					{
						hiscore = score;
					}
					state = GameStatus::GameOver;
					std::cout << "Game Over!\n";
				}

				if (isCollide(&maskot, &vehicle2, 50.0))
				{
					if (score >= hiscore)
					{
						hiscore = score;
					}
					state = GameStatus::GameOver;
					std::cout << "Game Over!\n";
				}
				if (isCollide(&maskot, &ikan, 40.0))
				{
					fuel += 5;
					ikan.reset();
				}
				if (fuel == 0)
				{
					state = GameStatus::GameOver;
				}

			}

			slRender();
		}

	}

	void end()
	{
		std::cout << "Game Selesai\n";
	}

}
void key()
{
	if (state == GameStatus::Mulai)
	{
		if (slGetKey(SL_KEY_ENTER))
			state = GameStatus::Main;
	}


	else if (state == GameStatus::Main)
	{
		if (slGetKey(SL_KEY_RIGHT))
			maskot.control(0.2);
		if (slGetKey(SL_KEY_LEFT))
			maskot.control(-0.2);
		if (slGetKey('P'))
			state = GameStatus::Pause;
	}

	else if (state == GameStatus::Pause)
	{
		if (slGetKey('R'))
		{
			state = GameStatus::Main;
		}
	}

	else if (state == GameStatus::GameOver)
	{
		if (slGetKey('R'))
		{
			score = 0;
			fuel = 20;
			state = GameStatus::Main;
			vehicle.reset();
			vehicle.setBatuSpd(-1.5);
			vehicle2.reset();
			vehicle2.setBatuSpd(-2);
			ikan.reset();
		}
	}

}

void info()
{
	slSetFontSize(20);
	slSetTextAlign(SL_ALIGN_CENTER);
	slText(SCR_W - 50, SCR_H - 50, pemain.c_str());
	slSetFontSize(18);
	slSetTextAlign(SL_ALIGN_CENTER);
	slText(SCR_W - 50, SCR_H - 210, "skor");
	slText(SCR_W - 50, SCR_H - 230, std::to_string(score).c_str());
	slText(SCR_W - 50, SCR_H - 260, "Energi");
	slText(SCR_W - 50, SCR_H - 290, std::to_string(fuel).c_str());

	if (state == GameStatus::Mulai)
	{
		slSetForeColor(0.0, 0.0, 0.0, 0.7);
		slRectangleFill(SCR_W / 2.0, SCR_H / 2.0, SCR_W, SCR_H);
		slSetFontSize(16);
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slText(SCR_W / 2, 480, "Hindari batu");
		slText(SCR_W / 2 + 35, 350, "Mencari Ikan untuk Menambah Energi");
		slText(SCR_W / 2, 256, "Tekan ENTER untuk Mulai");
	}
	else if (state == GameStatus::GameOver)
	{
		slSetForeColor(0.0, 0.0, 0.0, 0.7);
		slSetFontSize(40);
		slSetTextAlign(SL_ALIGN_CENTER);
		slText(SCR_W / 2.0, SCR_H / 2.0, "Game Over");
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slSetFontSize(16);
		slText(SCR_W / 2.0, SCR_H / 2.0 - 60, "Tekan 'R' untuk Replay");

	}
	else if (state == GameStatus::Pause)
	{
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slSetFontSize(16);
		slSetTextAlign(SL_ALIGN_CENTER);
		slText(SCR_W / 2.0, SCR_H / 2.0, "Tekan R untuk Resume");
	}
	else if (state == GameStatus::Main)
	{
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slSetFontSize(14);
		slSetTextAlign(SL_ALIGN_RIGHT);
		slText(SCR_W - 15, SCR_H - 25, "Tekan P untuk Pause");
	}
}

bool isCollide(object* e1, object* e2, const double h)
{
	return (std::hypot(e1->getX() - e2->getX(), e1->getY() - e2->getY()) <= h);
}