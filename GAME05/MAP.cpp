#include"../../libOne/inc/window.h"
#include"../../libOne/inc/graphic.h"
#include"GAME.h"
#include"GAME05.h"
#include"CONTAINER.h"
#include "MAP.h"
#include"CHARACTER_MANAGER.h"
namespace GAME05 {
    MAP::MAP(class GAME_* game) :
        GAME_OBJECT(game) {}//コンストラクタ
    MAP::~MAP() {//デストラクタ
        if (Map.data) { delete[] Map.data; Map.data = 0; }
    }
    void MAP::create() {//マップデータの読み込み
        Map = game()->container()->data().map;
    }
    void MAP::init() {//マップの初期設定を行う関数
        //ファイルを開く
        FILE* fp;
        fopen_s(&fp, Map.fileName, "rb");
        WARNING(fp == 0, "マップデータを読み込めません", Map.fileName);
        //ファイルサイズ取得
        fseek(fp, 0, SEEK_END);
        int fileSize = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        //リトライ時、Dataは0でないので開放。
        if (Map.data) { delete[] Map.data; Map.data = 0; }
        //サイズ分のdata配列を用意する
        Map.data = new char[fileSize];
        //データを読み込む
        fread(Map.data, sizeof(char), fileSize, fp);
        fclose(fp);
        //行数、列数を数える（最後の行も必ず改行して終わっていることが条件）
        Map.rows = 0;//行数
        Map.cols = 0;//改行２文字分を含んだ列数になる
        int cnt = 0;
        for (int i = 0; i < fileSize; i++) {
            cnt++;
            //行の最後の文字
            if (Map.data[i] == '\n') {
                if (Map.rows == 0) {
                    //最初の行の列数
                    Map.cols = cnt;
                }
                else if (Map.cols != cnt) {
                    //行ごとの列数が違ったらエラー
                    WARNING(1, "列数が不揃い", "");
                }
                //行を数えてカウンタをリセット
                Map.rows++;
                cnt = 0;
            }
        }
        if (fileSize % Map.cols != 0) {
            WARNING(1, "最後の行を改行していない", "");
        }
        Map.dispCols = (int)width / Map.chipSize + 2;//表示すべき列数
        Map.worldWidth = (float)Map.chipSize * (Map.cols - 2);//ワールドの横幅
        Map.endWorldX = Map.worldWidth - width;//表示できる最後の座標
        Map.wx = 0.0f;//現在表示しているワールド座標
    }
    void MAP::update() {//マップの更新を行う関数
        //プレイヤーが画面の中央を超えた分だけスクロール
        Map.wx += game()->characterManager()->player()->overCenterVx();
        if (Map.wx > Map.endWorldX) {
            Map.wx = Map.endWorldX;
        }
    }
    void MAP::draw() {//マップの描画を行う関数
        int startCol = (int)Map.wx / Map.chipSize;//表示開始列
        int endCol = startCol + Map.dispCols;//表示終了列
        for (int c = startCol; c < endCol; c++) {
            float wx = (float)Map.chipSize * c;
            for (int r = 0; r < Map.rows; r++) {
                float wy = (float)Map.chipSize * r;
                char charaId = Map.data[r * Map.cols + c];
                if (charaId >= '0' && charaId <= '9') {
                    float px = wx - Map.wx;
                    float py = wy - Map.wy;
                    if (charaId == '1')image(Map.blockImg, px, py);
                    else if (charaId == '2')image(Map.block2Img, px, py);
                    else if (charaId == '3')image(Map.block3Img, px, py);
                    else if (charaId == '4')image(Map.block4Img, px, py);
                    else if (charaId == '5')image(Map.block5Img, px, py);
                    else if (charaId == '6')image(Map.block6Img, px, py);
                    else if (charaId == '7')image(Map.block7Img, px, py);
                    else if (charaId == '8')image(Map.block8Img, px, py);
                    else if (charaId == '9')image(Map.block9Img, px, py);

                }
                else if (charaId >= 'a' && charaId <= 'z') {
                    game()->characterManager()->appear(charaId, wx, wy);
                    Map.data[r * Map.cols + c] = '.';
                }
            }
        }
    }
    //マップチップとキャラの当たり判定用関数群---------------------------------------------------
    //　指定されたワールド座標( wx wy )が、マップチップの中にはいっているかチェックする
    bool MAP::collisionCheck(float wx, float wy) {//この関数は下の当たり判定関数群から呼び出して使う関数
        //ワールド座標からマップDataの列colと行rowを求める
        int col = (int)wx / Map.chipSize;
        int row = (int)wy / Map.chipSize;
        //Dataの範囲外は判定できないので除外
        if ((col < 0) || (col >= Map.cols) || (row < 0) || (row >= Map.rows)) {
            return false;
        }
        //次の記述で座標がマップチップの中に入っているか判定できる
        if (Map.data[col + row * Map.cols] == '1') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '2') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '3') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '4') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '5') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '6') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '7') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '8') {
            return true;
        }
        if (Map.data[col + row * Map.cols] == '9') {
            return true;
        }
        return false;
    }
    //　マップチップとキャラの左辺が重なっているか
    bool MAP::collisionCharaLeft(float wx, float wy) {//マップチップとキャラの左辺が重なっているかチェックする
        bool leftTop = collisionCheck(wx, wy);
        bool leftBottom = collisionCheck(wx, wy + Map.chipSize - 1);
        return leftTop || leftBottom;
    }
    //　マップチップとキャラの右辺が重なっているか
    bool MAP::collisionCharaRight(float wx, float wy) {//マップチップとキャラの右辺が重なっているかチェックする
        bool rightTop = collisionCheck(wx + Map.chipSize - 1, wy);
        bool rightBottom = collisionCheck(wx + Map.chipSize - 1, wy + Map.chipSize - 1);
        return rightTop || rightBottom;
    }
    //　マップチップとキャラの上辺が重なっているか
    bool MAP::collisionCharaTop(float wx, float wy) {//マップチップとキャラの上辺が重なっているかチェックする
        bool topLeft = collisionCheck(wx, wy);
        bool topRight = collisionCheck(wx + Map.chipSize - 1, wy);
        return topLeft || topRight;
    }
    //　マップチップとキャラの下辺が重なっている、または、接しているか。ここだけ他と違う！
    bool MAP::collisionCharaBottom(float wx, float wy) {//マップチップとキャラの下辺が重なっている、または、接しているかチェックする
        // wy + Map.chipSizeをCheck関数に渡すことにより
        // キャラがマップチップと接しているかチェックできる。
        bool bottomLeft = collisionCheck(wx, wy + Map.chipSize);
        bool bottomRight = collisionCheck(wx + Map.chipSize - 1, wy + Map.chipSize);
        return bottomLeft || bottomRight;
    }
    //　マップチップと弾の当たり判定に使用
    bool MAP::collisionCharaRect(float wLeft, float wTop, float wRight, float wBottom) {//マップチップと弾の当たり判定に使用する関数
        bool rightTop = collisionCheck(wRight, wTop);
        bool rightBottom = collisionCheck(wRight, wBottom);
        bool leftTop = collisionCheck(wLeft, wTop);
        bool leftBottom = collisionCheck(wLeft, wBottom);
        return rightTop || rightBottom || leftTop || leftBottom;
    }
    //ウィンドウからのはみだし判定用---------------------------------------------------------
    float MAP::wDispLeft() {//表示領域の左端を取得
        return Map.wx - Map.chipSize;
    }
    float MAP::wDispRight() {//表示領域の右端を取得
        return Map.wx + width;
    }
}

