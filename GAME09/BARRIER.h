#pragma once
#include "../../libOne/inc/libOne.h"

class BARRIER {
private:
    float x, y;
    int hp;
    static const int SIZE = 20; // �����ȃu���b�N
public:
    void set(float x, float y) {
        this->x = x;
        this->y = y;
        hp = 2;  // �ϋv�l
    }

    void update() {
        
    }

    void draw() {
        if (hp > 0) {
            if (hp == 3) fill(200, 255, 200);
            else if (hp == 2) fill(150, 255, 150);
            else fill(100, 200, 100);
            rect(x, y, SIZE, SIZE);
        }
    }

    bool isAlive() const {
        return hp > 0;
    }

    bool checkHit(float bx, float by) {
        if (!isAlive()) return false;

        float half = SIZE / 2;
        if (bx >= x - half && bx <= x + half &&
            by >= y - half && by <= y + half) {
            hp--;
            return true;
        }
        return false;
    }
};
