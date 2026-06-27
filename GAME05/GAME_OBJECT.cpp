#include"GAME.h"
#include"GAME05.h"
#include "GAME_OBJECT.h"
namespace GAME05 {
    GAME_OBJECT::GAME_OBJECT(class GAME_* game) {//コンストラクタ
        Game = game;
    }
    GAME_OBJECT::~GAME_OBJECT() {//デストラクタ
        Game = nullptr;
    }
}