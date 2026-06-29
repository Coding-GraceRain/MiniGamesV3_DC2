#include"../../libOne/inc/graphic.h"
#include"../../libOne/inc/window.h"
#include"GAME.h"
#include"CONTAINER.h"
#include "FADE.h"
namespace GAME05 {
    void FADE::create() {//フェードの初期設定を行う関数
        Fade = game()->container()->data().fade;
    }
    void FADE::inTrigger() {//フェードインのトリガーを引く関数
        if (State == STATE::OUT_END) {
            State = STATE::IN_TRIGGER;
        }
    }
    void FADE::outTrigger() {//フェードアウトのトリガーを引く関数
        if (State == STATE::IN_END) {
            State = STATE::OUT_TRIGGER;
        }
    }
    void FADE::draw() {//フェードの描画を行う関数
        if (State == STATE::IN_END ||
            State == STATE::OUT_END) {
            return;
        }
        rectMode(CORNER);
        colorMode(RGB, 255);
        switch (State) {
        case STATE::IN_TRIGGER:
            Fade.color.a = 255;
            fill(Fade.color);
            rect(0, 0, width, height);
            State = STATE::IN_NOW;
            break;
        case STATE::IN_NOW:
            fill(Fade.color);
            rect(0, 0, width, height);
            Fade.color.a += -Fade.speed * delta;
            if (Fade.color.a < 0.0) {
                Fade.color.a = 0.0f;
                State = STATE::IN_END;
            }
            break;
        case STATE::OUT_TRIGGER:
            Fade.color.a = 0.0f;
            State = STATE::OUT_NOW;
            break;
        case STATE::OUT_NOW:
            fill(Fade.color);
            rect(0, 0, width, height);
            Fade.color.a += Fade.speed * delta;
            if (Fade.color.a >= 255.0f) {
                Fade.color.a = 255.0f;
                State = STATE::OUT_END;
            }
            break;
        }
    }
    int FADE::inEndFlag() {//フェードインが終了したかどうかを返す関数
        return (State == STATE::IN_END);
    }
    int FADE::outEndFlag() {//フェードアウトが終了したかどうかを返す関数
        return (State == STATE::OUT_END);
    }
    void FADE::setColor(const COLOR& color) {
        Fade.color = color;
    }
    void FADE::setSpeed(float speed) {
        Fade.speed = speed;
    }
}