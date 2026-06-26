#include"../../libOne/inc/window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include "TREE.h"
namespace GAME05 {
    void TREE::create() {
        Chara = game()->container()->data().treeChara;
        Tree = game()->container()->data().tree;
    }
    void TREE::appear(float wx, float wy, float vx, float vy) {
        Chara.hp = game()->container()->data().treeChara.hp;
        Chara.wx = wx;
        Chara.wy = wy;
        Tree.triggerCnt = game()->container()->data().tree.triggerCnt;
    }
    void TREE::update() {
        //木弾発射----------------------------------------------------------------
        Tree.elapsedTime += delta;//経過時間を加算
        if (Tree.elapsedTime >= Tree.interval) {
            Tree.elapsedTime -= Tree.interval;
            ++Tree.triggerCnt %= Tree.triggerInterval;
            if (Tree.triggerCnt == Tree.trigger1st ||
                Tree.triggerCnt == Tree.trigger2nd ||
                Tree.triggerCnt == Tree.trigger3rd ||
                Tree.triggerCnt == Tree.trigger4th) {
                game()->characterManager()->appear(Tree.bulletCharaId,
                    Chara.wx - Tree.bulletOffsetX, Chara.wy+29, -1, 0);
            }
        }
        //マップ------------------------------------------------------------------------
        // ウィンドウの外に出た
        if (Chara.wx < game()->map()->wDispLeft()) {
            Chara.hp = 0;
        }
       
    }
    void TREE::damage() {
        if (Chara.hp > 0) {
            Tree.damageTime = Tree.damageInterval;
            Chara.hp--;
            if (Chara.hp == 0) {
                game()->characterManager()->appear(Tree.explosionCharaId,
                    Chara.wx, Chara.wy);
            }
        }
    }
}