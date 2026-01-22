#pragma once
#include <vector>
#include "CourseData.h"
#include "Platform.h"
#include "Player.h"

namespace GAME00 {

    class CourseManager {
    public:
        std::vector<Platform> platforms;
        GoalData goal;

        void load(const Course& course, Player& player);
    };

}
