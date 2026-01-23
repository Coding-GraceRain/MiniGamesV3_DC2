#pragma once
#include "PlatformData.h"
#include "GoalData.h"

namespace GAME00 {

    struct Course {
        float startX, startY;
        const PlatformData* platforms;
        int platformCount;
        Rect goal;
    };

}
