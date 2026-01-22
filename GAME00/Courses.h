#pragma once
#include "PlatformData.h"
#include "GoalData.h"

namespace GAME00 {

    struct Course {
        float startX, startY;
        PlatformData* platforms;
        int platformCount;
        GoalData goal;
    };

}
