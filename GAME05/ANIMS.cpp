#include"../../libOne/inc/window.h"
#include"../../libOne/inc/graphic.h"
#include<filesystem>
#include "ANIMS.h"
namespace GAME05 {
    ANIMS::ANIMS() {}//空のコンストラクタ
    ANIMS::ANIMS(const char* path) {//ディレクトリからアニメーションを読み込むコンストラクタ
        load(path);
    }
    ANIMS::ANIMS(const char* fileName, int cols, int rows, int w, int h) {//スプライトシートからアニメーションを読み込むコンストラクタ
        load(fileName, cols, rows, w, h);
    }
    ANIMS::~ANIMS() {//開放
        for (int i = 0; i < NumAnims; i++) {
            delete Anims[i];
        }
        delete[] Anims;
    }
    void ANIMS::load(const char* path) {//ディレクトリからアニメーションを読み込む関数
        namespace fs = std::filesystem;//std::filesystemからfsに名前変更
        NumAnims = 0;
        for (const auto& e : fs::directory_iterator(path)) {//アニメーション数を数える
            NumAnims++;
        }
        Anims = new ANIM * [NumAnims];//ANIM配列を作る
        int i = 0;
        for (const auto& e : fs::directory_iterator(path)) {//各ファイルを読み込む
            Anims[i] = new ANIM(e.path().string().c_str());
            i++;
        }
    }
    void ANIMS::load(const char* fileName, int cols, int rows, int w, int h) {//スプライトシート(コマ送りをまとめたファイル)からアニメーションを読み込む関数
        NumAnims = rows;
        int img = loadImage(fileName);//画像のファイルを読み込む
        Anims = new ANIM * [NumAnims];//ANIMを作る
        //rowごとにアニメーションを作る
        for (int i = 0; i < NumAnims; i++) {//各行ごとに分割
            Anims[i] = new ANIM;
            Anims[i]->divideRow(img, i, cols, w, h);
        }
    }
    //getter
    ANIM* ANIMS::anim(int animIdx) {//animIdx番目のANIMを返す関数
        if (animIdx >= NumAnims) {//範囲外なら
            return Anims[NumAnims - 1];//最後のアニメーションを返す
        }
        return Anims[animIdx];
    }
}