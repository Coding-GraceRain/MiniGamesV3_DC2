#include "GAME03.h"
#include "STAGE.h"
#include "../../libOne/inc/libOne.h"
#include "PLAYER.h"
#include "MAP.h"
#include "CHARACTER_MANAGER.h"
#include "CONTAINER.h"
namespace GAME03
{
    STAGE::STAGE(class GAME* game) :
        SCENE(game) {

    }
    STAGE::~STAGE() {
    }
    void STAGE::create() {
        Stage = game()->container()->data().stage;
    }
    void STAGE::init() {
        Stage.stageNum = game()->container()->data().stage.stage01;
        StageNum = STAGE_NUMBER::STAGE01;
        Stage.respawnPlayerTime = game()->container()->data().stage.respawnPlayerTime;
        Stage.nextSceneTime = game()->container()->data().stage.nextSceneTime;
        Stage.size = game()->container()->data().stage.size;
        game()->map()->init(Stage.stageNum);
        game()->characterManager()->init();
        game()->fade()->inTrigger();
    }
    void STAGE::update() {
        game()->characterManager()->update();
    }
    void STAGE::respawn() {
        Stage.respawnPlayerTime = game()->container()->data().stage.respawnPlayerTime;
        game()->map()->init(Stage.stageNum);
        game()->characterManager()->init();
    }
    void STAGE::tutorial() {
        switch (StageNum) {
        case STAGE_NUMBER::STAGE01:
            fill(255);
            textSize(Stage.size);
            text("A or Dキーで左右移動", Stage.tx, Stage.ty);
            break;
        case STAGE_NUMBER::STAGE02:
            fill(255);
            textSize(Stage.size);
            text("敵の弾に当たるとGAME OVER", Stage.tx, Stage.ty);
            break;
        case STAGE_NUMBER::STAGE03:
            fill(255);
            textSize(Stage.size);
            text("Wキーでジャンプ", Stage.tx, Stage.ty);
            break;
        case STAGE_NUMBER::STAGE04:
            fill(255);
            textSize(Stage.size);
            text("ボタンを踏むとバリアが消える", Stage.tx, Stage.ty);
            break;
        }
    }
    void STAGE::draw() {
        clear(0, 0, 64);
        tutorial();
        game()->map()->draw();
        game()->characterManager()->draw();
        if (game()->characterManager()->player()->died()) {
            Logo();
        }
        else if (game()->characterManager()->player()->survived()) {
            nextStage();
        }
        game()->fade()->draw();
    }
    void STAGE::Logo() {
        float size;
        size = 100;
        textSize(size);
        if (game()->characterManager()->player()->died()) {
            fill(255, 0, 0);
            text("YOU DIED", (width - size * 7) / 2 + 2, height / 2);
            Stage.respawnPlayerTime -= delta;
        }
        if (game()->characterManager()->player()->survived()) {
            fill(255, 255, 0);
            text("ALL CLEAR", (width - size * 7) / 2 + 2, height / 2);
            Stage.nextSceneTime -= delta;
        }
    }
    void STAGE::nextStage() {
        switch (StageNum) {
        case STAGE_NUMBER::STAGE01:
            StageNum = STAGE_NUMBER::STAGE02;
            Stage.stageNum = Stage.stage02;
            respawn();
            break;
        case STAGE_NUMBER::STAGE02:
            StageNum = STAGE_NUMBER::STAGE03;
            Stage.stageNum = Stage.stage03;
            respawn();
            break;
        case STAGE_NUMBER::STAGE03:
            StageNum = STAGE_NUMBER::STAGE04;
            Stage.stageNum = Stage.stage04;
            respawn();
            break;
        case STAGE_NUMBER::STAGE04:
            StageNum = STAGE_NUMBER::STAGE05;
            Stage.stageNum = Stage.stage05;
            respawn();
            break;
        case STAGE_NUMBER::STAGE05:
            Logo();
            break;
        }
    }
    void STAGE::nextScene() {
        if (Stage.respawnPlayerTime <= 0) {
            respawn();
        }
        if (Stage.nextSceneTime <= 0) {
            game()->fade()->outTrigger();
        }
        if (game()->fade()->outEndFlag()) {
            game()->changeScene(GAME::GAME_CLEAR_ID);
        }
    }
}