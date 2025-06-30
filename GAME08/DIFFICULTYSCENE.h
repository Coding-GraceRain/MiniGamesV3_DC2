#pragma once
#include "SCENEBASE.h"
#include "SCENEMANAGER.h"
namespace GAME08 {
	class DIFFICULTYSCENE : public SCENEBASE {
            SCENEMANAGER& mgr;
    public:
        DIFFICULTYSCENE(SCENEMANAGER& manager) : mgr(manager) {}
        void create() override;
        void update() override;
        void destroy() override;
        };
	
}
