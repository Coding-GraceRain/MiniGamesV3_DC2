#include"../../libOne/inc/graphic.h"
#include "CONTAINER.h"
#include"ANIMS.h"
namespace GAME05 {
    CONTAINER::~CONTAINER() {//ゲーム全体で使用するデータの開放を行う関数
        //１つのアニメーションの開放
        delete Data.treeChara.anim;
        delete Data.bossChara.anim;
        //複数のアニメーションの開放
        //delete Data.suraimu.anims;
        delete Data.playerChara.anims;
        delete Data.suraimuChara.anims;
    }
    void CONTAINER::load() {//ゲーム全体で使用するデータの作成とグラフィックの読み込みを行う関数
        CreateData();
        LoadGraphics();
    }
    void CONTAINER::CreateData() {//ゲーム全体で使用するデータの作成を行う関数
        //背景色
        Data.stage.backColor = COLOR(255, 255, 255, 255);
        Data.stage.gameOverColor = COLOR(255, 255, 255);
        Data.stage.gameClearColor = COLOR(255, 255, 255);
        //ロゴの表示位置
        Data.stage.logoPx = (width - 800) / 2;
        Data.stage.logoPy = 220;
        Data.stage.backToTitleTime = 2; //ゲームクリア後何秒でタイトルへ戻るか

        Data.fade.color = COLOR(60, 60, 60);//フェード色
        Data.fade.speed = 255 * 2;//フェード速度

        //マップ
        Data.map.fileName = "../MAIN/assets/game05/map1.txt";
        Data.map.chipSize = 90;
        Data.map.centerX = width / 2 - Data.map.chipSize / 2;

        //レイヤー
        Data.layer.fileName = "../MAIN/assets/game05/layer1.txt";
        Data.layer.chipSize = 90;
        Data.layer.centerX = width / 2 - Data.layer.chipSize / 2;

        //レイヤー
        Data.layer2.fileName = "../MAIN/assets/game05/layer2.txt";
        Data.layer2.chipSize = 90;
        Data.layer2.centerX = width / 2 - Data.layer2.chipSize / 2;

        //プレイヤー
        Data.playerChara.charaId = MAP::PLAYER_ID;
        Data.playerChara.charaId = LAYER::PLAYER_ID;
        Data.playerChara.hp = 1;
        Data.playerChara.groupId = 0;//味方グループは0
        Data.playerChara.speed = 3.6f * 60;
        Data.playerChara.offsetLeft = 10.0f;
        Data.playerChara.offsetTop = 1.0f;
        Data.playerChara.offsetRight = 40.0f;
        Data.playerChara.offsetBottom = 89.0f;
        Data.player.rightAnimId = 0;//右向き
        Data.player.leftAnimId = 1;//左向き
        Data.player.jumpFlag = 0;
        Data.player.initVecUp = -22.0f;
        Data.player.initVecDown = 3.0f;
        Data.player.gravity = 48;
        Data.player.bulletOffsetX = 20.0f;//銃口位置
        Data.player.bulletCharaId = MAP::PLAYER_BULLET_ID;
        //弾
        Data.playerBulletChara.charaId = MAP::PLAYER_BULLET_ID;
        Data.playerBulletChara.groupId = 0;//味方グループは0 
        Data.playerBulletChara.hp = 1;
        Data.playerBulletChara.speed = 4.7f * 60;
        Data.playerBulletChara.offsetLeft = 20.0f;
        Data.playerBulletChara.offsetTop = 20.0f;
        Data.playerBulletChara.offsetRight = 30.0f;
        Data.playerBulletChara.offsetBottom = 30.0f;

        //スライム
        Data.suraimuChara.charaId = MAP::SURAIMU_ID;
        Data.suraimuChara.groupId = 1;//敵グループは1
        Data.suraimuChara.hp = 4;
        Data.suraimuChara.speed = 1.4f * 90;
        Data.suraimuChara.offsetLeft = 20.0f;
        Data.suraimuChara.offsetTop = 32.0f;
        Data.suraimuChara.offsetRight = 70.0f;
        Data.suraimuChara.offsetBottom = 60.0f;
        Data.suraimu.rightAnimId = 0;
        Data.suraimu.leftAnimId = 1;
        Data.suraimu.damageInterval = 5 * 0.016f;
        Data.suraimu.initVecX = -1;
        Data.suraimu.initVecY = 0;
        Data.suraimu.gravity = 0.8f * 60;
        Data.suraimu.alphaLowVal = 25;

        //木
        Data.treeChara.charaId = MAP::TREE_ID;
        Data.treeChara.hp = 10;
        Data.treeChara.groupId = 1;//敵グループは1
        Data.treeChara.offsetLeft = 10.0f;
        Data.treeChara.offsetTop = 0.0f;
        Data.treeChara.offsetRight = 80.0f;
        Data.treeChara.offsetBottom = 180.0f;
        Data.tree.elapsedTime = 0;
        Data.tree.interval = 0.016f;
        Data.tree.triggerCnt = 60;
        Data.tree.triggerInterval = 255;
        Data.tree.trigger1st = 220;
        Data.tree.trigger2nd = 230;
        Data.tree.trigger3rd = 240;
        Data.tree.trigger4th = 250;
        Data.tree.bulletCharaId = MAP::TREE_BULLET_ID;
        Data.tree.damageTime = 0;
        Data.tree.damageInterval = 5 * 0.016f;
        Data.tree.bulletOffsetX = 30.0f;
        //弾
        Data.treeBulletChara.charaId = MAP::TREE_BULLET_ID;
        Data.treeBulletChara.groupId = 1;//敵グループは1
        Data.treeBulletChara.hp = 1;
        Data.treeBulletChara.speed = 4.7f * 60;
        Data.treeBulletChara.offsetLeft = 20.0f;
        Data.treeBulletChara.offsetTop = 47.0f;
        Data.treeBulletChara.offsetRight = 30.0f;
        Data.treeBulletChara.offsetBottom = 57.0f;

        //ボス
        Data.bossChara.charaId = MAP::BOSS_ID;
        Data.bossChara.hp = 20;
        Data.bossChara.groupId = 1;//敵グループは1
        Data.bossChara.offsetLeft = 40.0f;
        Data.bossChara.offsetTop = 40.0f;
        Data.bossChara.offsetRight = 320.0f;
        Data.bossChara.offsetBottom = 320.0f;
        Data.boss.elapsedTime = 0;
        Data.boss.interval = 0.016f;
        Data.boss.triggerCnt = 60;
        Data.boss.triggerInterval = 311;
        Data.boss.trigger1st = 220;
        Data.boss.trigger2nd = 235;
        Data.boss.trigger3rd = 250;
        Data.boss.trigger4th = 265;
        Data.boss.trigger5nd = 280;
        Data.boss.trigger6rd = 295;
        Data.boss.trigger7th = 310;
        Data.boss.bulletCharaId = MAP::BOSS_BULLET_ID;
        Data.boss.damageTime = 0;
        Data.boss.damageInterval = 5 * 0.016f;
        Data.boss.bulletOffsetX = -135.0f;
        //弾
        Data.bossBulletChara.charaId = MAP::BOSS_BULLET_ID;
        Data.bossBulletChara.groupId = 1;//敵グループは1
        Data.bossBulletChara.hp = 1;
        Data.bossBulletChara.speed = 4.7f * 60;
        Data.bossBulletChara.offsetLeft = 20.0f;
        Data.bossBulletChara.offsetTop = 47.0f;
        Data.bossBulletChara.offsetRight = 30.0f;
        Data.bossBulletChara.offsetBottom = 57.0f;


        Data.charaMng.numPlayers = 1;
        Data.charaMng.numPlayerBullets = 5;
        Data.charaMng.numSuraimus = 10;
        Data.charaMng.numTrees = 5;
        Data.charaMng.numTreeBullets = 50;
        Data.charaMng.numBoss = 1;
        Data.charaMng.numBossBullets = 50;
    }
    void CONTAINER::LoadGraphics() {//ゲーム全体で使用するグラフィックの読み込みを行う関数
        Data.stage.backImg = loadImage("../MAIN/assets/game05/title_wide.png");

        Data.stage.backImg = loadImage("../MAIN/assets/game05/back_wide.png");
        Data.stage.gameClearImg = loadImage("../MAIN/assets/game05/GameClear.png");
        Data.stage.gameOverImg = loadImage("../MAIN/assets/game05/GameOver.png");

        Data.map.blockImg = loadImage("../MAIN/assets/game05/block.png");
        Data.map.block2Img = loadImage("../MAIN/assets/game05/block2.png");
        Data.map.block3Img = loadImage("../MAIN/assets/game05/block3.png");
        Data.map.block4Img = loadImage("../MAIN/assets/game05/block4.png");
        Data.map.block5Img = loadImage("../MAIN/assets/game05/block5.png");
        Data.map.block6Img = loadImage("../MAIN/assets/game05/block6.png");
        Data.map.block7Img = loadImage("../MAIN/assets/game05/block7.png");
        Data.map.block8Img = loadImage("../MAIN/assets/game05/block8.png");
        Data.map.block9Img = loadImage("../MAIN/assets/game05/block9.png");



        Data.layer.blockImg = loadImage("../MAIN/assets/game05/grass.png");
        Data.layer.block2Img = loadImage("../MAIN/assets/game05/grass2.png");
        Data.layer.block3Img = loadImage("../MAIN/assets/game05/grass3.png");
        Data.layer.block4Img = loadImage("../MAIN/assets/game05/grass4.png");
        Data.layer.block5Img = loadImage("../MAIN/assets/game05/grass5.png");
        Data.layer.block6Img = loadImage("../MAIN/assets/game05/grass6.png");

        Data.layer2.blockImg = loadImage("../MAIN/assets/game05/ceiling.png");
        Data.layer2.block2Img = loadImage("../MAIN/assets/game05/ceiling2.png");
        Data.layer2.block3Img = loadImage("../MAIN/assets/game05/ceiling3.png");
        Data.layer2.block4Img = loadImage("../MAIN/assets/game05/ceiling4.png");
        Data.layer2.block5Img = loadImage("../MAIN/assets/game05/ceiling5.png");

        Data.layer2.block6Img = loadImage("../MAIN/assets/game05/ceiling6.png");

        Data.playerBulletChara.img = loadImage("../MAIN/assets/game05/playerBullet.png");

        Data.treeBulletChara.img = loadImage("../MAIN/assets/game05/treeBullet.png");

        Data.bossBulletChara.img = loadImage("../MAIN/assets/game05/bossBullet.png");
        //ANIMS 複数のアニメーションセット
        Data.playerChara.anims = new ANIMS("../MAIN/assets/game05/player");
        Data.playerChara.animData.interval = 0.2f;

        Data.suraimuChara.anims = new ANIMS("../MAIN/assets/game05/suraimu");
        Data.suraimuChara.animData.interval = 0.1f;



        //ANIM １つのアニメーションセット
        Data.treeChara.anim = new ANIM("../MAIN/assets/game05/tree/0");
        Data.treeChara.animData.interval = 0.3f;

        Data.bossChara.anim = new ANIM("../MAIN/assets/game05/boss/0");
        Data.bossChara.animData.interval = 0.3f;
    }
}