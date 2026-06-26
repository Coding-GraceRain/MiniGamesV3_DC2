#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME03.h"
#include "TITLE.h"
#include "STAGE.h"
#include "GAME_CLEAR.h"
#include "CONTAINER.h"
#include "PLAYER.h"
#include "MAP.h"
#include "CHARACTER_MANAGER.h"
namespace GAME03
{
	int GAME::create()
	{
		Container = new CONTAINER();
		
		Scenes[TITLE_ID] = new TITLE(this);
		Scenes[STAGE_ID] = new STAGE(this);
		Scenes[GAME_CLEAR_ID] = new GAME_CLEAR(this);
		CurSceneId = TITLE_ID;

		Fade = new FADE(this);
		Map = new MAP(this);
		CharacterManager = new CHARACTER_MANAGER(this);

		Container->load();
		Scenes[TITLE_ID]->create();
		Scenes[STAGE_ID]->create();
		Scenes[GAME_CLEAR_ID]->create();
		
		Scenes[CurSceneId]->init();
		CharacterManager->create();
		Fade->create();
		Map->create();

		return 0;
	}
	void GAME::destroy()
	{
		delete CharacterManager;
		delete Map;
		delete Fade;
		for (int i = 0; i < NUM_SCENES; i++) {
			delete Scenes[i];
		}
		delete Container;
	}
	void GAME::changeScene(SCENE_ID sceneId) {
		CurSceneId = sceneId;
		Scenes[CurSceneId]->init();
	}
	void GAME::proc()
	{
		clear(0, 0, 64);
		fill(255);


		Scenes[CurSceneId]->proc();

		textSize(50);
		fill(255, 255, 0);
		text("GAME03", 0, 100);
		text("ENTERキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
