#include"../../libOne/inc/graphic.h"
#include"../../libOne/inc/window.h"
#include<filesystem>
#include"ANIM.h"
namespace GAME05 {
    ANIM::ANIM() {}//引数なしのコンストラクタは、load関数で画像を読み込む場合に使用する。
    ANIM::ANIM(const char* pathName) {//引数ありのコンストラクタは、引数で指定したパスから画像を読み込む場合に使用する。
        load(pathName);
    }
    ANIM::~ANIM() {//アニメーションで使用している画像を開放する。
        delete[] Imgs;
    }
    void ANIM::load(const char* path) {//指定したパスから画像を読み込む。ファイル名は連番でなくてもよい。
        namespace fs = std::filesystem;//std::filesystemからfsに名前変更
        NumImgs = 0;
        for (const auto& e : fs::directory_iterator(path)) {//アニメーション数を数える
            NumImgs++;
        }
        Imgs = new int[NumImgs];//ANIM配列を作る
        int i = 0;
        for (const auto& e : fs::directory_iterator(path)) {//各ファイルを読み込む
            Imgs[i] = loadImage(e.path().string().c_str());
            i++;
        }
    }
    void ANIM::divideRow(int imgIdx, int row, int cols, int w, int h) {//指定した画像を、横にcols個、縦に1個の合計cols個の画像に分割する。rowは0から始まる。
        NumImgs = cols;
        Imgs = new int[NumImgs];
        for (int i = 0; i < NumImgs; i++) {
            Imgs[i] = cutImage(imgIdx, w * i, row * h, w, h);
        }
    }
    void ANIM::divide(const char* fileName, int cols, int rows, int w, int h) {//指定したファイルから画像を分割する。
        NumImgs = cols * rows;
        Imgs = new int[NumImgs];
        int img = loadImage(fileName);
        divideImage(img, cols, rows, w, h, Imgs);
    }
    void ANIM::draw(ANIM_DATA* ad, float px, float py, float angle, float scale) {//アニメーションを描画する。adはアニメーションの状態を表す構造体へのポインタ。px, pyは描画位置、angleは回転角度、scaleは拡大率。
        if (LoopFlag) {
            ad->elapsedTime += delta;//経過時間を足す
            if (ad->elapsedTime >= ad->interval) {//一定時間経ったら
                ad->elapsedTime -= ad->interval;
                ++(ad->imgIdx); //次の画像に切り替える
                if (ad->imgIdx >= NumImgs) {//最後までいったら
                    ad->imgIdx = 0;
                }
            }
            image(Imgs[ad->imgIdx], px, py, angle, scale);
        }
        else {
            if (ad->imgIdx >= NumImgs) {
                return;
            }
            ad->elapsedTime += delta;
            if (ad->elapsedTime >= ad->interval) {
                ad->elapsedTime -= ad->interval;
                ++(ad->imgIdx);
            }
            if (ad->imgIdx < NumImgs) {
                image(Imgs[ad->imgIdx], px, py, angle, scale);
            }
        }
    }
}