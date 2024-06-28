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
            {"‚È‚µ","nasi"},
            {"‚Î‚È‚È","banana"},
            {"‚è‚ñ‚²","ringo"},
            {"‚¢‚¿‚²","itigo"},
            {"‚Ô‚Ç‚¤","budou"},
            {"‚«‚¤‚¢","kiui"},
            {"‚´‚­‚ë","zakuro"},
            {"‚·‚¢‚©","suika"},
            {"‚ê‚à‚ñ","remon"},
            {"‚ç‚¢‚¿","raiti"},
            {"‚Ç‚è‚ ‚ñ","dorian"},
            {"‚¨‚ê‚ñ‚¶","orenji"},
            {"‚³‚­‚ç‚ñ‚Ú","sakuranbo"},
            {"‚Ï‚¢‚È‚Á‚Õ‚é","painappuru"},
            
                       
        };

    };
}
