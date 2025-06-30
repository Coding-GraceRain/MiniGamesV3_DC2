#include "SCENEMANAGER.h"
#include "TITLESCENE.h"
#include "DIFFICULTYSCENE.h"
#include "GAMESCENE.h"
#include "RESULTSCENE.h"
namespace GAME08 {
    void SCENEMANAGER::change(SCENEID id) {
        if (current) {
            current->destroy();
            delete current;
            current = nullptr;
        }

        switch (id) {
        case TITLE:
            current = new TITLESCENE(*this);
            break;
        case DIFFICULTY:
            current = new DIFFICULTYSCENE(*this);
            break;
        case GAME:
            current = new GAMESCENE(*this);
            break;
        case RESULT:
            current = new RESULTSCENE(*this);
            break;
        }

        if (current) {
            current->create();
        }
    }

    void SCENEMANAGER::update() {
        if (current) {
            current->update();
        }
    }

    void SCENEMANAGER::shutdown() {
        if (current) {
            current->destroy();
            delete current;
            current = nullptr;
        }
        winCount = 0;
        winner = 0;
        currentRound = 0;
        for (int& w : winHistory) w = 0;
    }

}
