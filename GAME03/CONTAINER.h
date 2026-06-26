#pragma once
#include "TITLE.h"
#include "STAGE.h"
#include "FADE.h"
#include "GAME_CLEAR.h"
#include "PLAYER.h"
#include "MAP.h"
#include "TURRETS.h"
#include "CHARACTER_MANAGER.h"
#include "BUTTON.h"
namespace GAME03
{
	class CONTAINER
	{
		struct DATA {
			TITLE::DATA title;
			STAGE::DATA stage;
			GAME_CLEAR::DATA gameClear;
			FADE::DATA fade;
			CHARACTER::DATA playerChara;
			PLAYER::DATA player;
			CHARACTER::DATA turretChara;
			TURRETS::DATA turret;
			CHARACTER::DATA turretBulletChara;
			BUTTON::DATA button;
			CHARACTER::DATA buttonChara;
			MAP::DATA map;
			CHARACTER_MANAGER::DATA charaMng;
		};
		DATA Data;
	public:
		void load();
		void setData();
		void loadGraphic();
		const DATA& data() { return Data; }
	};
}
