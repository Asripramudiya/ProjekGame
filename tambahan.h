#ifndef TAMB
#define TAMB

#include "objek.h"

class tamb :public object
{
private:
	double tamb_spd;
	int TambTexIkan;
public:
	tamb(double tx, double ty);
	void draw();
	void updatekoin();
	void update();
	void resetKoin();
	void reset();
	void loadTexture();
	void setTambSpd(double s);
};



#endif