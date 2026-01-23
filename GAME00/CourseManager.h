#pragma once
#include <vector>
#include "Platform.h"
#include "CourseData.h"
#include "PlatformData.h"
#include "Player.h"
#include "Rect.h"

namespace GAME00 {

    class CourseManager {
    public:
        std::vector<Platform> platforms;
        Rect goal;

        void load(const Course& course, Player& player);
        void reload(Player& player);

    private:
        const Course* currentCourse = nullptr;
    };

}
