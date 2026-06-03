#include "SHOT_POINT.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/mathUtil.h"
namespace GAME02{
	void SHOTPOINT::create() {
		Img = loadImage("../main\\assets\\game02\\onmyoudama.png");
	}
	void SHOTPOINT::init() {
		angleMode(DEGREES);
		Deg = 0;
		Alive = false;
	}
	void SHOTPOINT::setPosition(float x,float y){
		Px = x;
		Py = y;
		Deg += 1;
		Alive = true;
	}
	void SHOTPOINT::draw() {
		if(Alive)
		image(Img, Px, Py,Deg);
	}

}