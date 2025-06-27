#pragma once
namespace GAME05 {

    class GAME_STRUCT {
    public:
        const enum game {
            MAEGAKI,TITLE, SELECT, PLAY, OVER, CLEAR
        };
        int game_state = 0;
        bool title = 0;
        bool select = 0;
        bool play = 0;
        bool play_start = 0;
        bool music_onoff = 0;
    public:
        void Music_Change();
        //void ScreenTransition();
    };
}
