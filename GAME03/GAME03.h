#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME03
{
    class GAME :
        public GAME_BASE
    {
    private:
        class CONTAINER* Container = nullptr;
    public:
        class CONTAINER* container() { return Container; }

    public:
        enum SCENE_ID {
            TITLE_ID,
            STAGE_ID,
            GAME_CLEAR_ID,
            NUM_SCENES
        };
    private:
        class SCENE* Scenes[NUM_SCENES];
        SCENE_ID CurSceneId;
        class FADE* Fade = nullptr;
    public:
        void changeScene(SCENE_ID sceneId);
        class FADE* fade() { return Fade; }
    private:
        class MAP* Map = nullptr;
        class CHARACTER_MANAGER* CharacterManager = nullptr;
    public:
        class MAP* map() { return Map; }
        class CHARACTER_MANAGER* characterManager() { return CharacterManager; }
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        void init();
        int create();
        void proc();
        void destroy();
    };
}
