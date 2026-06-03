#include "haikei.h"
#include "../../libOne/inc/graphic.h"
namespace GAME02 {
	void BACK::create() {
		Img = loadImage("../main\\assets\\game02\\haikei2.png");
		ClearImg = loadImage("../main\\assets\\game02\\sanya.png");
		SecImg = loadImage("../main\\assets\\game02\\blue.png");
		GameOverImg = loadImage("../main\\assets\\game02\\maimero.png");
	}
	void BACK::draw() {
		rectMode(CORNER);
		image(Img, Px, Py);
	}
	void BACK::cleardraw() {
		rectMode(CORNER);
		image(ClearImg, Px, Py);
	}
	void BACK::secdraw() {
		rectMode(CORNER);
		image(SecImg, Px, Py);
	}
	void BACK::gameoverdraw() {
		rectMode(CORNER);
		image(GameOverImg, Px, Py);
	}
}