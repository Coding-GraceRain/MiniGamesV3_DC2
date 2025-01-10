#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME02.h"
namespace GAME02
{
	int GAME::create()
	{
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				square[i][j].w = 100.0f;
				square[i][j].h = 100.0f;
				square[i][j].px = (width / 2 - square[i][j].w * 4) - square[i][j].w / 2 + square[i][j].w * j;
				square[i][j].py = (height / 2 - square[i][j].h * 4) - square[i][j].h / 2 + square[i][j].h * i;
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				frame[i][j].w = 300.0f;
				frame[i][j].h = 300.0f;
				frame[i][j].px = (width / 2 - frame[i][j].w) + frame[i][j].w * j - frame[i][j].w / 2;
				frame[i][j].py = (height / 2 - frame[i][j].h) + frame[i][j].h * i - frame[i][j].h / 2;
			}
		}
		return 0;
	}

	void GAME::destroy()
	{

	}

	void GAME::setnum()
	{

	}

	void GAME::mousecol() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (mouseX > square[i][j].px && mouseX < square[i][j].px + square[i][j].w &&
					mouseY > square[i][j].py && mouseY < square[i][j].py + square[i][j].h) {
					if (isTrigger(MOUSE_LBUTTON)) {
						square[i][j].num++;
						if (square[i][j].num >= 10)square[i][j].num = square[i][j].num % 10 + 1;
					}
				}
			}
		}
	}

	void GAME::draw() {
		strokeWeight(5);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				fill(255);
				rect(square[j][i].px, square[j][i].py, square[j][i].w, square[j][i].h);
				fill(0);
				text((let)+square[j][i].num, square[j][i].px + 38, square[j][i].py + 78);
			}
		}


		strokeWeight(10);
		fill(255, 255, 255, 0);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rect(frame[j][i].px, frame[j][i].py, frame[j][i].w, frame[j][i].h);
			}
		}

	}

	void GAME::title() {
		text("ナンプレ", width / 2 - 100, height / 2 - 100);
		text("SPACEキーで開始", width / 2 - 200, height / 2 + 100);
		if (isTrigger(KEY_SPACE)) {
			State = PLAY;
		}
	}

	void GAME::play() {
		static bool once = true;
		//if (once) { setnum(); once = false; }
		draw();
		mousecol();

		//State = CLEAR;
	}

	void GAME::gameclear() {

	}

	void GAME::proc()
	{
		clear(128, 128, 128);
		textSize(50);
		fill(255, 255, 0);
		textSize(50);
		fill(255);

		if (State == TITLE) { title(); }
		if (State == PLAY) { play(); }
		if (State == CLEAR) { gameclear(); }

		text("ENTERキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}

	}
}
