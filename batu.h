#ifndef BATU
#define BATU
#include "objek.h"

class batu :public object
{
private:
	int texture;
	double batu_spd;
public:
	batu(double bx, double by, double vx);
	void draw();
	void update();
	void reset();
	void loadTexture()override;
	void setBatuSpd(double s);
};
#endif