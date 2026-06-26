#pragma once
#include "../../libOne/inc/libOne.h"
class ENEMY {
protected:
	float x, y;
	int anime;
	int animeTimer;
	int* img;
	float w, h;
	int hp;
public:
	virtual ~ENEMY(){}
	virtual void init();
	virtual void update(float speed);
	virtual void draw();


	float getx() const { return x; }
	 float gety() const { return y; }
	 float getw() const { return w; }
	 float geth() const { return h; }
};
class KOUMORI :public ENEMY {
private:
	
public:
	void setImage(int imgKoumori[]) { img=imgKoumori; }
	void init()override;
	void update(float speed)override;
	void draw()override;
	void damage();
	void setx(float kx) { x = kx; }
};
class OBAKE :public ENEMY {
private:

public:
	void setImage(int imgObake[]) { img = imgObake; }
	void init() override;
	void update(float speed)override;
	void draw()override;
	void damage();
	void setx(float ox) { x = ox; }
	
};