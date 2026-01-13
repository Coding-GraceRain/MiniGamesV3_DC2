#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <math.h>
#include "GAME04.h"
#include <sstream> 
#include <cstdlib>  
#include <ctime>   
#include <cmath>
namespace GAME04
{
    float scrollX = 0;

    float distance(float x1, float y1, float x2, float y2)
    {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return sqrtf(dx * dx + dy * dy);
    }
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

        for (auto e : enemies)
        {
            if (!e->active) continue;

            float d = distance(
                player->wx, player->wy,
                e->wx, e->wy
            );

            if (d < player->pr + e->pr)
            {
                float playerFootY = player->wy + player->pr;
                float enemyHeadY = e->wy - e->pr;

                // 踏みつけ
                if (player->vy > 0 && playerFootY < enemyHeadY + 10)
                {
                    e->active = false;
                    player->vy = -15;
                }
                else
                {
                    // 横 or 下からヒット

                    // 押し戻し（貫通防止）
                    if (player->wx < e->wx)
                        player->wx = e->wx - (player->pr + e->pr);
                    else
                        player->wx = e->wx + (player->pr + e->pr);

                    // ★ノックバック発生
                    player->vx = (player->wx < e->wx) ? -10 : 10;
                    player->vy = -8;
                    player->knockTimer = 15;

                    player->hp--;
                }

            }
        }
    }

    void GAME::draw() {
        player->draw();
        for (auto e : enemies) e->draw();
    }

    void GAME::proc()
    {
        move();

        clear(255, 255, 255);
        fill(0);
        rect(-fmod(scrollX, 800), 830, 800, 250);
        rect(800 - fmod(scrollX, 800), 830, 800, 250);

        draw();
        //drawNumber(10, 10, player->hp);
    }
}