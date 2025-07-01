#pragma once
#include"SCENEBASE.h"
#include"SCENEMANAGER.h"
namespace GAME08 {
	class TITLESCENE:public SCENEBASE
	{
		SCENEMANAGER& mgr;
		int bgImg = -1;
		int select = 0;
		int difficultySelect = 0;
		bool selectingDifficulty = false;
		bool assetsLoaded = false;
	public:
		TITLESCENE(SCENEMANAGER& manager) : mgr(manager) {}
		void create() override;
		void update() override;
		void destroy() override;
	};
}
