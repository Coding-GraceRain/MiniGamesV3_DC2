#include "CourseManager.h"

namespace GAME00 {

    void CourseManager::load(const Course& course, Player& player) {
        platforms.clear();

        for (int i = 0; i < course.platformCount; i++) {
            const auto& d = course.platforms[i];
            platforms.emplace_back(d.x, d.y, d.w, d.h);
        }

        goal = course.goal;
        player.init(course.startX, course.startY);
    }

}
