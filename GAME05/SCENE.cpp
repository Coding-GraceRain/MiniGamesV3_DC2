#include"GAME.h"
#include "SCENE.h"
namespace GAME05 {
    void SCENE::create() {}//シーンの初期設定を行う関数
    void SCENE::init() {}//シーンの初期化を行う関数
    void SCENE::proc() {// シーンの処理を行う関数
        update();
        draw();
        nextScene();
    }
    void SCENE::update() {}//シーンの更新を行う関数
    void SCENE::draw() {}//シーンの描画を行う関数
    void SCENE::nextScene() {}//次のシーンに切り替える関数
}