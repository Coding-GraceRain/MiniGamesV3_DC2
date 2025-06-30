#pragma once
#include"SCENEBASE.h"
#include"SCENEMANAGER.h"
namespace GAME08 {
	class GAMESCENE :public SCENEBASE{
        SCENEMANAGER& mgr;
        int frame = 0;
        int p1ReactionFrame = -1;
        int p2ReactionFrame = -1;
        int signalFrame = 0;
        bool cutInActive = false;
        int cutInFrame = 0;
        bool cpuTriggered = false;
        int reactionFrame = -1;
        int resultDisplayTimer = 0;
        int foulCount = 0;

        int soraImg = -1;
        int enemyImgs[SCENEMANAGER::HISTORY_SIZE] = {};
        int winnerImg = -1;
        int soraNameImg = -1;
        int enemyNameImgs[SCENEMANAGER::HISTORY_SIZE] = {};

        int exImg = -1;
        int bgImg = -1;

        int cutinImg = -1;
        int enemyCutinImgs[SCENEMANAGER::HISTORY_SIZE] = {};
        float cutinX = 777;
        float enemyCutinX = 1203;
        static const int CUT_IN_DURATION = 60;

        int currentEnemyImg = -1;
        int currentEnemyNameImg = -1;
        int currentEnemyCutinImg = -1;
        bool showEx = false;
        bool redoRound = false;

    public:
        GAMESCENE(SCENEMANAGER& manager) : mgr(manager) {}
        void create() override;
        void update() override;
        void destroy() override;
	};
}

