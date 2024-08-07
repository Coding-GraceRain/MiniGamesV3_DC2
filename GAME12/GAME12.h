#pragma once
#include "../MAIN/GAME_BASE.h"
#include<time.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<chrono>
#include<thread>
#include<random>
#include"../../libOne/inc/input.h"
#define Qnumber 14

namespace GAME12
{
    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
    private:
        enum STATE { TITLE, INIT, WAIT, PLAY, OVER ,END };
        STATE State = TITLE;
        void title();
        void init();
        void wait();
        void play();
        void over();
        void ending();
        void count();
        void gmain();
        void dec(int num, int wnum);
        void draw(int snum);
        INPUT_CODE gettriggerkeycode();

        int miss, num, wnum, flag, fflag, gend, lend;
        INPUT_CODE ch[Qnumber][100];
        size_t sum;
        size_t str;
        float curtime;
       

        const char* ward[Qnumber][2] = {
            {"なし","nasi"},
            {"ばなな","banana"},
            {"りんご","ringo"},
            {"いちご","itigo"},
            {"ぶどう","budou"},
            {"きうい","kiui"},
            {"ざくろ","zakuro"},
            {"すいか","suika"},
            {"れもん","remon"},
            {"らいち","raiti"},
            {"どりあん","dorian"},
            {"おれんじ","orenji"},
            {"さくらんぼ","sakuranbo"},
            {"ぱいなっぷる","painappuru"},
            
                       
        };

    };
}
