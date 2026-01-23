#include "CourseManager.h"
#include "Rect.h"

namespace GAME00 {

    void CourseManager::load(const Course& course, Player& player)
    {
        currentCourse = &course;

        platforms.clear();
        for (int i = 0; i < course.platformCount; i++) {
            platforms.push_back({
                course.platforms[i].x,
                course.platforms[i].y,
                course.platforms[i].w,
                course.platforms[i].h
                });
        }

        this->goal = course.goal;

        player.x = course.startX;
        player.y = course.startY;
        player.vx = 0;
        player.vy = 0;
    }

    void CourseManager::reload(Player& player)
    {
        if (!currentCourse) return;
        load(*currentCourse, player);
    }

}
