#pragma once
namespace GAME03 {
    class GAME_OBJECT
    {
    private:
        class GAME* Game = nullptr;
    public:
        GAME_OBJECT(class GAME* game);
        bool flg_clear = false;
        virtual ~GAME_OBJECT();
        class GAME* game() { return Game; }
    };
}
