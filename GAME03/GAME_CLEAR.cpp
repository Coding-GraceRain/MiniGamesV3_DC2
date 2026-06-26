#include "../../libOne/inc/libOne.h"
#include "GAME_CLEAR.h"
#include "FADE.h"
#include "CONTAINER.h"
#include "GAME03.h"
namespace GAME03
{
    GAME_CLEAR::GAME_CLEAR(class GAME* game) :
        SCENE(game) {

    }
    GAME_CLEAR::~GAME_CLEAR() {
    }
    void GAME_CLEAR::init() {
        game()->fade()->inTrigger();
    }
    void GAME_CLEAR::create() {
        GameClear = game()->container()->data().gameClear;
    }
    void GAME_CLEAR::draw() {
        clear();
        fill(GameClear.textColor);
        textSize(GameClear.textSize);
        text(GameClear.str, GameClear.pos.x, GameClear.pos.y);
        textSize(100);
        fill(255);
        text(GameClear.instructions, GameClear.pos.x, 700);
        game()->fade()->draw();
    }
    void GAME_CLEAR::nextScene() {
        if (isTrigger(KEY_SPACE)) {
            game()->fade()->outTrigger();
        }
        if (game()->fade()->outEndFlag()) {
            game()->changeScene(GAME::TITLE_ID);
        }
    }
}