#pragma once
#include <vector>
#include "../MAIN/GAME_BASE.h"

namespace GAME03 {

    class GAME : public GAME_BASE {
    public:
        GAME(class MAIN* main);

        int  create()  override;
        void proc()    override;
        void destroy() override;

    private:
        enum STATE { TITLE, PLAY, CLEAR };

        static const int SIZE = 10;
        static const int EMPTY = 0;
        static const int BLOCK = 2;

        STATE State = TITLE;
        bool  playInitFlg = false;
        bool  prevEnterKey = false;

        int selectedDifficulty = 0;      // 難易度（0:簡単, 1:普通, 2:難しい）
        int selectedMapIndex = 0;        // マップ番号（0～4）
        int numBlocks = 0;               // ブロック数（参考用）
        int titleBgm = -1;
        int playBgm = -1;
        int clearBgm = -1;
        int  board[SIZE][SIZE];          // マップデータ
        bool visited[SIZE][SIZE];        // 訪問フラグ
        int  px = 0, py = 0;             // プレイヤー位置

        int  visitCount = 0;             // 訪問済みマス数
        int  totalEmpty = SIZE * SIZE;   // 通れるマス数
        bool gameClear = false;


        std::vector<std::pair<int, int>> path;           // スネーク状の初期経路
        std::vector<std::pair<int, int>> moveHistory;    // 移動履歴（Zキー用）
        std::vector<std::pair<int, int>> shortestPath;   // 最短経路（未使用）
        std::vector<std::pair<int, int>> highlightPath;  // 経路ハイライト表示用

        // 各処理関数
        void resetVisited();
        void generateMap();                              // マップ生成（固定マップに切替）
        void drawBoard();                                // マップ描画
        void handleInput();                              // 入力処理
        void restartPlay();                              // リスタート

        void loadPredefinedMap(int difficulty, int index);  // 固定マップを読み込む
        void drawCenteredText(const char* str, int centerX, int y, int size = 24); // 中央描画補助
    };

} // namespace GAME03
