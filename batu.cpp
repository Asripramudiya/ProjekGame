#include "objek.h"
#include "batu.h"
#include "komponen.h"
#include <sl.h>
#include <cstdlib>


batu::batu(double bx, double by, double vx)
{
	posX = bx;
	posY = by;
	velX = vx;
}

void batu::loadTexture()
{
	texture = slLoadTexture(TEX_BATU);
}

void batu::draw()
{
	slSprite(texture, posX, posY, 50, 30);
}

void batu::update()
{
	posY += batu_spd;
	if (posY <= -40)
	{
		reset();
		batu_spd -= 0.2;
	}
}

void batu::reset()
{
	int arr[] = { 66,132,200,266 };
	int random;
	random = rand() % 4;
	posY = 700;
	posX = arr[random];
}

void batu::setBatuSpd(double s)
{
	batu_spd = s;
}