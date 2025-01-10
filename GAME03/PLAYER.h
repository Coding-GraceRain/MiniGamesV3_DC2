#pragma once
#include"CHARACTER.h"
namespace GAME03 {
    class PLAYER :public CHARACTER {
    public:
        struct DATA {
            int rightAnimId = 0;
            int leftAnimId = 1;
            float curWx = 0;
            float initVecUp = 0;
            float initVecDown = 0;
            float gravity = 0;
            time_t s_time = 0, time = 0,
                   n_time = 0, stp_time = 0,
                   cnt_time = 0;
        };
    private:
        DATA Player;
        DATA Stage;
        enum class STATE { STRUGGLING, SURVIVED, DIED };
        STATE State = STATE::STRUGGLING;
        FILE* fp{};
    public:
        PLAYER(class GAME* game) :CHARACTER(game) {}
        void create();
        void appear(float wx, float wy, float vx, float vy);
        void update();
    private:
        void Move();
        void CollisionWithMap();
        void CheckState();
    public:
        bool died();
        bool survived() const;
        float overCenterVx();
        float overCenterVy();
        int DeterPlayer = 0;
        int op_option = false;
    };
}

