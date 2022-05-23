#include "tambahan.h"
#include <sl.h>
#include "komponen.h"
#include <cstdlib>

tamb::tamb(double tx, double ty)
{
	posX = tx;
	posY = ty;
};


void tamb::loadTexture()
{
	TambTexIkan = slLoadTexture(TEX_IKAN);
}


void tamb::draw()
{
	slSprite(TambTexIkan, posX, posY, 60, 60);
}

void tamb::updatekoin()
{
	posY += tamb_spd;
	if (posY <= -40)
	{
		resetKoin();
	}
}

void tamb::update()
{
	posY += tamb_spd;
	if (posY <= -40)
	{
		reset();
	}
}

void tamb::setTambSpd(double s)
{
	tamb_spd = s;
}


void tamb::resetKoin()
{
	int arr[] = { 100,132,200,245 };
	int ran = rand() % 4;
	posY = 2000;
	posX = arr[ran];
}

void tamb::reset()
{
	int arr[] = { 100,132,200,245 };
	int ran = rand() % 4;
	posY = 3000;
	posX = arr[ran];
}

