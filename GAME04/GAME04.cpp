#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <math.h>
#include "GAME04.h"
#include <sstream> 
#include <cstdlib>  
#include <ctime>    
namespace GAME04
{
    float scrollX = 0;

    int GAME::create()
    {
        player = new PLAYER();

        enemies.clear();
        enemies.push_back(new ENEMY(800));
        enemies.push_back(new ENEMY(1200));
        enemies.push_back(new ENEMY(1600));

        return 0;
    }

    void GAME::destroy()
    {
        delete player;
        player = nullptr;

        for (auto e : enemies) delete e;
        enemies.clear();
    }

    void GAME::move()
    {
        player->move();
        for (auto e : enemies) e->move();
    }
    void GAME::draw() {

    }

    void GAME::proc()
    {
        move();

        clear(255, 255, 255);
        fill(0);
        rect(-fmod(scrollX, 800), 830, 800, 250);
        rect(800 - fmod(scrollX, 800), 830, 800, 250);

        player->draw();
        for (auto e : enemies) e->draw();
    }
}