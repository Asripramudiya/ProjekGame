#ifndef MASKOT
#define MASKOT

#include "objek.h"

class Maskot : public object
{
private:
	int texture;
public:
	Maskot(double mx, double my);
	void draw();
	void update();
	void control(double cx);
	void loadTexture();
};
#endif