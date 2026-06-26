#include "CONTAINER.h"
namespace GAME03
{
	void CONTAINER::load() {
		setData();
		loadGraphic();
	}
	void CONTAINER::setData() {
		Data.title.backColor = COLOR(0, 0, 64);
		Data.title.textColor = COLOR(0, 255, 0);
		Data.title.textSize = 200;
		Data.title.pos.x = 180;
		Data.title.pos.y = 600;
		strcpy_s(Data.title.str, "STAR ACTION");
		strcpy_s(Data.title.instructions, "SPACEキーで開始");

		Data.stage.respawnPlayerTime = 3;
		Data.stage.nextSceneTime = 3;
		Data.stage.stageNum = 0;
		Data.stage.stage01 = "../main/assets/game03/stage01.txt";
		Data.stage.stage02 = "../main/assets/game03/stage02.txt";
		Data.stage.stage03 = "../main/assets/game03/stage03.txt";
		Data.stage.stage04 = "../main/assets/game03/stage04.txt";
		Data.stage.stage05 = "../main/assets/game03/stage05.txt";
		Data.stage.size = 50;
		Data.stage.tx = 400.0f;
		Data.stage.ty = 400.0f;

		Data.gameClear.textColor = COLOR(255, 255, 0);
		Data.gameClear.textSize = 200;
		Data.gameClear.pos.x = 180;
		Data.gameClear.pos.y = 600;
		strcpy_s(Data.gameClear.str, "GAME CLEAR!");
		strcpy_s(Data.gameClear.instructions, "SPACEキーで戻る");

		Data.fade.color = COLOR(60, 60, 60);
		Data.fade.speed = 255 * 2;

		//Data.map.fileName = "../main/assets/game03/stage03.txt";
		Data.map.chipSize = 100;
		Data.map.mapNumber = 0;
		Data.map.gimmickButton = 0;

		Data.playerChara.charaId = MAP::PLAYER_ID;
		Data.playerChara.hp = 1;
		Data.playerChara.groupId = 0;
		Data.playerChara.speed = 4.8f * 60;
		Data.playerChara.offsetLeft = 10.0f;
		Data.playerChara.offsetTop = 1.0f;
		Data.playerChara.offsetRight = 130.0f;
		Data.playerChara.offsetBottom = 100.0f;
		Data.player.curWx = 0;
		Data.player.gravity = 48;
		Data.player.initVy = -16.0f;
		Data.player.jumpFlag = 0;

		Data.turretChara.charaId = MAP::TURRET_ID;
		Data.turretChara.hp = 2;
		Data.turretChara.groupId = 1;
		Data.turret.elapsedTime = 0;
		Data.turret.interval = 0.016f;
		Data.turret.triggerCnt = 60;
		Data.turret.triggerInterval = 240;
		Data.turret.trigger1st = 55;
		Data.turret.trigger2nd = 110;
		Data.turret.trigger3rd = 165;
		Data.turret.trigger4th = 220;
		Data.turret.bulletCharaId = MAP::TURRET_BULLET_ID;
		Data.turret.bulletOffsetX = 25.0f;
		Data.turret.bulletOffsetY = 70.0f;

		Data.turretBulletChara.charaId = MAP::TURRET_BULLET_ID;
		Data.turretBulletChara.groupId = 1;
		Data.turretBulletChara.hp = 1;
		Data.turretBulletChara.speed = 4.2f * 60;
		Data.turretBulletChara.offsetLeft = 40.0f;
		Data.turretBulletChara.offsetTop = 40.0f;
		Data.turretBulletChara.offsetRight = 40.0f;
		Data.turretBulletChara.offsetBottom = 40.0f;

		Data.buttonChara.charaId = MAP::BUTTON_ID;
		Data.buttonChara.groupId = 0;
		Data.buttonChara.hp = 1;
		Data.buttonChara.offsetLeft = 40.0f;
		Data.buttonChara.offsetTop = 40.0f;
		Data.buttonChara.offsetRight = 80.0f;
		Data.buttonChara.offsetBottom = 40.0f;

		Data.charaMng.numPlayers = 1;
		Data.charaMng.numTurrets = 5;
		Data.charaMng.numTurretBullets = 12;
		Data.charaMng.numButton = 3;
	}
	void CONTAINER::loadGraphic() {
		Data.playerChara.img = loadImage("../main/assets/game03/star.png");
		Data.map.blockImg = loadImage("../main/assets/game03/block.png");
		Data.map.barrierImg = loadImage("../main/assets/game03/barrier.png");
		Data.turretChara.img = loadImage("../main/assets/game03/turret.png");
		Data.turretBulletChara.img = loadImage("../main/assets/game03/bullet.png");
		Data.buttonChara.img = loadImage("../main/assets/game03/button.png");
		Data.buttonChara.gimmickImg = loadImage("../main/assets/game03/push_button.png");
	}
}