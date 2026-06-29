#include"../../libOne/inc/framework.h"
#include"../../libOne/inc/graphic.h"
#include"../../libOne/inc/window.h"
#include"../../libOne/inc/input.h"
#include"CONTAINER.h"
#include"TITLE.h"
#include"STAGE.h"
#include"FADE.h"
#include"MAP.h"
#include"LAYER.h"
#include"CHARACTER_MANAGER.h"
#include"GAME.h"
namespace GAME05 {
    GAME_::GAME_() {//コンストラクタ

        Container = new CONTAINER();
        Title = new TITLE(this);
        Stage = new STAGE(this);
        Fade = new FADE(this);
        Map = new MAP(this);
        Layer = new LAYER(this);
        Layer2 = new LAYER2(this);
        CharacterManager = new CHARACTER_MANAGER(this);
    }
    GAME_::~GAME_() {//デストラクタ
        delete CharacterManager;
        delete Map;
        delete Fade;
        delete Stage;
        delete Title;
        delete Container;
        delete Layer;
        delete Layer2;
    }
    void GAME_::run() {//ゲームの実行を行う関数
        hideCursor();

        Container->load();

        Title->create();
        Stage->create();
        Fade->create();
        Map->create();
        Layer->create();
        Layer2->create();
        CharacterManager->create();

        CurScene = Title;
        CurScene->init();
        initDeltaTime();



    }
    void GAME_::setCurScene(SCENE* scene) {//シーンを切り替える関数
        CurScene = scene;
        CurScene->init();
    }
    void GAME_::proc()
    {
        CurScene->proc();
    }
}