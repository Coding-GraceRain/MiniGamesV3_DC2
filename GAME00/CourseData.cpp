#include "CourseData.h"

namespace GAME00 {

    static PlatformData COURSE_1_PLATFORMS[] = {
        {300, 800, 3000, 30},
        {800, 550, 300, 30},
        {200, 400, 250, 30},
        {1200, 350, 40, 300}
    };

    Course COURSE_1 = {
        640, 500,
        COURSE_1_PLATFORMS,
        4,
        {1800, 300, 50, 50}
    };

    static PlatformData COURSE_2_PLATFORMS[] = {
        {100, 700, 300, 30},
        {500, 600, 400, 30},
        {950, 450, 200, 30}
    };

    Course COURSE_2 = {
        150, 650,
        COURSE_2_PLATFORMS,
        3,
        {1100, 400, 50, 50}
    };

    static PlatformData COURSE_3_PLATFORMS[] = {
        {200, 700, 200, 30},
        {500, 550, 200, 30},
        {800, 400, 300, 30}
    };

    Course COURSE_3 = {
        220, 650,
        COURSE_3_PLATFORMS,
        3,
        {1050, 350, 50, 50}
    };

}
