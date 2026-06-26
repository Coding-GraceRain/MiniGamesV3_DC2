#include "GAME03.h"
#include "TITLE.h"
#include "../../libOne/inc/libOne.h"
#include "CONTAINER.h"
#include "FADE.h"
namespace GAME03
{
    TITLE::TITLE(class GAME* game) :
        SCENE(game) {

    }
    TITLE::~TITLE() {
    }
    void TITLE::init() {
        game()->fade()->inTrigger();
    }
    void TITLE::create() {
        Title = game()->container()->data().title;
    }
    void TITLE::draw() {
        fill(Title.textColor);
        textSize(Title.textSize);
        text(Title.str, Title.pos.x, Title.pos.y);
        textSize(100);
        fill(255);
        text(Title.instructions, Title.pos.x, 700);

        game()->fade()->draw();
    }
    void TITLE::nextScene() {
        if (isTrigger(KEY_SPACE)) {
            game()->fade()->outTrigger();
        }
        if (game()->fade()->outEndFlag()) {
            game()->changeScene(GAME::STAGE_ID);
        }
    }
}