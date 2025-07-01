#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME06.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
#include <windows.h>

// �}�E�X���N���b�N�����o����֐�
bool isMouseLeftPressed() {
    return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
}

// �}�E�XX���W�擾
int getMouseX() {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(GetForegroundWindow(), &p);
    return p.x;
}

// �}�E�XY���W�擾
int getMouseY() {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(GetForegroundWindow(), &p);
    return p.y;
}

using namespace std::chrono;

namespace GAME06 {

    static int circleX, circleY;
    static int score = 0;
    static const int RADIUS = 50;
    static long long lastUpdateTime = 0;
    // �Q�[���J�n����
    static long long startTime = 0;
    // ��������
    static const int TIME_LIMIT_MS = 60000;

    int GAME::create() {
        srand((unsigned int)time(nullptr));

        // �����ʒu
        circleX = rand() % (1920 - 2 * RADIUS) + RADIUS;
        circleY = rand() % (1080 - 2 * RADIUS) + RADIUS;

        // ���ݎ���
        lastUpdateTime = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()).count();

        // �Q�[���J�n����
        startTime = lastUpdateTime;

        return 0;
    }

    void GAME::destroy() {
        
    }

    void GAME::proc() {
        // �w�i�F
        clear(30, 30, 60); 

        // ���ݎ���
        long long currentTime = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()).count();

        // �o�ߎ���
        long long elapsed = currentTime - startTime;

        // �c�莞��
        int remainingTime = max(0, (TIME_LIMIT_MS - (int)elapsed) / 1000);

        // �X�R�A�\��
        fill(255);
        textSize(32);
        text((std::string("�X�R�A: ") + std::to_string(score)).c_str(), 50, 50);

        // �c�莞�ԕ\��
        text((std::string("�c�莞��: ") + std::to_string(remainingTime) + "�b").c_str(), 50, 90);

        // �������Ԃ𒴂�����I��
        if (elapsed >= TIME_LIMIT_MS) {
            fill(255, 0, 0);
            textSize(60);
            text("TIME UP!", 700, 500);
            return; 
        }

        // 1�b���Ƃɉ~���ړ�
        if (currentTime - lastUpdateTime > 1000) {
            circleX = rand() % (1920 - 2 * RADIUS) + RADIUS;
            circleY = rand() % (1080 - 2 * RADIUS) + RADIUS;
            lastUpdateTime = currentTime;
        }

        // �~
        fill(0, 255, 0);
        circle((float)circleX, (float)circleY, (float)RADIUS);

        // �}�E�X�N���b�N�ŉ~�ɓ���������X�R�A���Z
        if (isMouseLeftPressed()) {
            int mx = getMouseX();
            int my = getMouseY();
            int dx = mx - circleX;
            int dy = my - circleY;
            if (dx * dx + dy * dy <= RADIUS * RADIUS) {
                score++;
                circleX = rand() % (1920 - 2 * RADIUS) + RADIUS;
                circleY = rand() % (1080 - 2 * RADIUS) + RADIUS;
            }
        }
    }
}
