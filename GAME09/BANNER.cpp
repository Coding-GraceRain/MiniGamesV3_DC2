#include "BANNER.h"
#include "GAME09.h"
#include "CONTAINER.h"
//#include "RHYTHM_GAME_CONTROLLER.h"
#include "CHARTMANAGER.h"
#include "../../libOne/inc/window.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/mathUtil.h"
#include "textFunc.h"

namespace GAME09 {
	BANNER::BANNER(GAME* game) :
		GAME_OBJECT(game) {
	}

	BANNER::~BANNER() {

	}

	void BANNER::create() {
		Banner = game()->container()->data().banner;
		CurNum = 0;
		BackGroundImageNum = CurNum;
		AnimeNum = CurNum;
	}

	void BANNER::init() {
		PlayDemoMusic = true;
		AnimeFlag = false;
	}

	void BANNER::update() {
		if (AnimeFlag) {
			float ratio = AnimeTime / Banner.moveAnimeTime;
			AnimeNum = CurNum + MoveNum * ratio;
			AnimeTime += delta;
			if (AnimeTime > Banner.moveAnimeTime) {
				CurNum = (CurNum + MoveNum + game()->songs().size()) % (int)game()->songs().size();
				if (isPress(KEY_DOWN)) {
					AnimeTime -= Banner.moveAnimeTime;
					MoveNum = 1;
				}
				else if (isPress(KEY_UP)) {
					AnimeTime -= Banner.moveAnimeTime;
					MoveNum = -1;
				}
				else {
					AnimeFlag = false;
					PlayDemoMusic = true;
					AnimeNum = (float)CurNum;
					BackGroundImageNum = CurNum;
				}
			}
		}
		else {
			if (PlayDemoMusic) {
				game()->soundMNG()->playMusic(game()->songs()[CurNum].musicIdx);
				PlayDemoMusic = false;
			}
			if (isPress(KEY_DOWN)) {
				AnimeFlag = true;
				AnimeTime = 0;
				MoveNum = 1;
			}
			else if (isPress(KEY_UP)) {
				AnimeFlag = true;
				AnimeTime = 0;
				MoveNum = -1;
			}
		}
	}

	void BANNER::draw() {
		rectMode(CENTER);
		//image(Banner.backImg, Banner.centerPos.x, Banner.centerPos.y, 0, Banner.imgSize);
		const int drawBannerNum = 9;
		const int startBannerIdx = (int)Round(AnimeNum) - (drawBannerNum / 2);
		for (int i = 0; i < drawBannerNum; i++) {
			float dist = startBannerIdx + i - AnimeNum;
			int bannerNum = (startBannerIdx + i) % (int)game()->songs().size();
			if (bannerNum < 0) bannerNum += (int)game()->songs().size();

			VECTOR2 pos = Banner.centerPos;
			if (dist < 0) {
				pos.x -= Banner.nextPosOfst.x * dist;
				pos.y += Banner.nextPosOfst.y * dist;
			}
			else {
				pos += Banner.nextPosOfst * dist;
			}
			//game()->songs()[bannerNum]
			game()->songTitle()->draw(game()->songs()[bannerNum], pos, 1);
		}
	}

}