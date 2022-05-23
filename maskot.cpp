#include "maskot.h"
#include "objek.h"
#include "sl.h"
#include "komponen.h"

Maskot::Maskot(double mx, double my)
{
	posX = mx;
	posY = my;
}

void Maskot::loadTexture()
{
	texture = slLoadTexture(TEX_MASKOT);
}

void Maskot::draw()
{
	slSprite(texture, posX, posY, 60, 85);
}

void Maskot::update()
{
	posX += velX;
	if (posX - 23 <= 30 || posX + 20 >= 360)
		velX *= -0.5;
}

void Maskot::control(double cx)
{
	velX += cx;
}