#include "haikei.h"
#include "../../libOne/inc/graphic.h"
#include <ctime>
namespace GAME02 {
	void BACK::create() {
		Img = loadImage("../main\\assets\\game02\\haikei2.png");
		ClearImg = loadImage("../main\\assets\\game02\\sanya.png");
		SecImg = loadImage("../main\\assets\\game02\\black.jpg");
		GameOverImg[0] = loadImage("../main\\assets\\game02\\neko1.jpg");
		GameOverImg[1] = loadImage("../main\\assets\\game02\\neko2.jpg");
		GameOverImg[2] = loadImage("../main\\assets\\game02\\neko3.jpg");
		GameOverImg[3] = loadImage("../main\\assets\\game02\\neko4.jpg");
		GameOverImg[4] = loadImage("../main\\assets\\game02\\neko5.jpg");
		TitleImg = loadImage("../main\\assets\\game02\\Title.png");
	}
	void BACK::draw() {
		rectMode(CORNER);
		image(Img, Px, Py);
	}
	void BACK::titledraw() {
		rectMode(CORNER);
		image(TitleImg, Px, Py);
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
		if (Take == 0) {
			srand((unsigned)time(NULL));
			i = rand() % 5;
			Take = 1;
		}
			image(GameOverImg[i], Px, Py);
	}
}