#pragma once
#include "SCENEBASE.h"
#include "SCENEMANAGER.h"
namespace GAME08 {
	class RESULTSCENE : public SCENEBASE
	{
		SCENEMANAGER& mgr;
		int bgImg = -1;
		bool assetsLoaded = false;

	public:
		RESULTSCENE(SCENEMANAGER& manager) : mgr(manager) {}
		void create() override;
		void update() override;
		void destroy() override;
	};
}

