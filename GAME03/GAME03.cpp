#define NOMINMAX
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME03.h"
#include <algorithm>
#include <random>
#include <queue>
#include <cstdio> 


namespace GAME03 {

    GAME::GAME(MAIN* main) : GAME_BASE(main) {}

    int GAME::create() {
        selectedDifficulty = 0;
        numBlocks = 0;
        gameClear = false;
        State = TITLE;
        playInitFlg = false;
        return 0;
    }

    void GAME::resetVisited() {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                visited[x][y] = false;
    }

    void GAME::loadPredefinedMap(int difficulty, int index) {

        static const char* easyMaps[5] = {
            "P.......................#................#............................#.............................",
            "P....#...............................................#................#.............................",
            "P...............................................#..................................#.......#........",
            "P.............##..........#.........................................................................",
            "P#..............................#...........................#......................................."
        };

        static const char* normalMaps[5] = {
            "P...........#.....#.........#.............................#..................#......................",
            "P...#...........................#........#......#......................................#............",
            "P...#.....#...............................#.#...................................................#...",
            "P....................#.............#...#.#.......................#..................................",
            "P....................#................................#.#.........#...............#................."
        };

        static const char* hardMaps[5] = {
            "P......#.....#........#....................#...................#............#................#......",
            "P.............#.............##................#...#....................................#..#.........",
            "P.........#.........##.....#.........................................#...##.........................",
            "P....................#.#.............##....................#..........................#.......#.....",
            "P.................#...........#...#..................#.........#..................#..........#......",

        };
        px = 0;
        py = 0;
        const char* mapStr = nullptr;
        if (difficulty == 0) mapStr = easyMaps[index];
        else if (difficulty == 1) mapStr = normalMaps[index];
        else if (difficulty == 2) mapStr = hardMaps[index];

        if (!mapStr) return;

        int idx = 0;
        int blockCount = 0;
        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE; ++x) {
                char c = mapStr[idx++];
                if (c == 'S') { px = x; py = y; board[x][y] = EMPTY; }
                else if (c == '.') board[x][y] = EMPTY;
                else if (c == '#') { board[x][y] = BLOCK; blockCount++; }
            }
        }

        resetVisited();
        visited[px][py] = true;
        visitCount = 1;
        totalEmpty = SIZE * SIZE - blockCount;
        playInitFlg = true;
        path = { {px, py} };
    }

    void GAME::generateMap() {
        loadPredefinedMap(selectedDifficulty, selectedMapIndex);
    }



    void GAME::handleInput() {
        static bool prevA = false, prevD = false, prevW = false, prevS = false, prevZ = false;

        bool a = inValue(KEY_A), d = inValue(KEY_D),
            w = inValue(KEY_W), s = inValue(KEY_S),
            z = inValue(KEY_R);

        if (a && !prevA && px > 0 && board[px - 1][py] != BLOCK && !visited[px - 1][py]) {
            moveHistory.push_back(std::make_pair(px, py));
            px--;
        }
        else if (d && !prevD && px < SIZE - 1 && board[px + 1][py] != BLOCK && !visited[px + 1][py]) {
            moveHistory.push_back(std::make_pair(px, py));
            px++;
        }
        else if (w && !prevW && py > 0 && board[px][py - 1] != BLOCK && !visited[px][py - 1]) {
            moveHistory.push_back(std::make_pair(px, py));
            py--;
        }
        else if (s && !prevS && py < SIZE - 1 && board[px][py + 1] != BLOCK && !visited[px][py + 1]) {
            moveHistory.push_back(std::make_pair(px, py));
            py++;
        }
        else if (z && !prevZ && !moveHistory.empty()) {
            std::pair<int, int> prev = moveHistory.back(); moveHistory.pop_back();
            visited[px][py] = false;
            px = prev.first;
            py = prev.second;
            visitCount--;
        }
    

        prevA = a; prevD = d; prevW = w; prevS = s; prevZ = z;

        if (!visited[px][py]) {
            visited[px][py] = true;
            visitCount++;
        }

        if (visitCount >= totalEmpty) {
            gameClear = true;
            State = CLEAR;
        }
    }
    void GAME::drawBoard() {
        clear(0, 0, 0);

        const int cellSize = 40;
        const int margin = 4;
        const int boardSize = SIZE * cellSize;


        const int offsetX = (1920 - boardSize) / 2;
        const int offsetY = (1080 - boardSize) / 2 - 50;

        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE; ++x) {
                int cx = x * cellSize + offsetX;
                int cy = y * cellSize + offsetY;

                bool onHighlight = false;
                for (const auto& p : highlightPath) {
                    if (p.first == x && p.second == y) {
                        onHighlight = true;
                        break;
                    }
                }

                if (onHighlight) fill(0, 0, 255);
                else if (board[x][y] == BLOCK) fill(100, 100, 100);
                else if (visited[x][y]) fill(0, 200, 0);
                else fill(255, 255, 255);

                rect(cx, cy, cellSize - margin, cellSize - margin);

                if (x == px && y == py) {
                    fill(255, 0, 0);
                    circle(cx + (cellSize - margin) / 2, cy + (cellSize - margin) / 2, 10);
                }
            }
        }

        
        const int textY = offsetY + boardSize + 30;
        fill(255, 255, 255);
        textSize(24);
        text("移動: A/D/W/S", offsetX, textY);
        text("Z: リスタート R: 1マス戻る  B: タイトルへ ", offsetX, textY + 30);


        char buf[64];
        sprintf_s(buf, "訪問マス: %d / %d", visitCount, totalEmpty);
        fill(200, 200, 0);
        textSize(24);
        text(buf, offsetX, textY + 70);
    }
    void GAME::restartPlay() {
        if (path.empty()) return; 
        px = path.front().first;
        py = path.front().second;
        resetVisited();
        visited[px][py] = true;
        visitCount = 1;
        gameClear = false;
    }

    void GAME::drawCenteredText(const char* str, int centerX, int y, int size) {
        textSize(size);
        int width = strlen(str) * 10;
        text(str, centerX - width / 2, y);
    }

    void GAME::proc() {
 

        bool currentEnter = inValue(KEY_ENTER);

        switch (State) {
        case TITLE: {
            clear(0, 0, 0);
            textSize(32);
            drawCenteredText("迷路ゲーム", 960, 100);
            textSize(24);
            drawCenteredText("難易度とマップ番号を選んでください", 960, 180);

            const char* diff[] = { "簡単", "普通", "難しい" };

            static int keyWait = 0;
            if (keyWait > 0) keyWait--;

            if (keyWait == 0) {
                if (inValue(KEY_UP)) {
                    selectedDifficulty = (selectedDifficulty + 2) % 3;
                    keyWait = 10;
                }
                if (inValue(KEY_DOWN)) {
                    selectedDifficulty = (selectedDifficulty + 1) % 3;
                    keyWait = 10;
                }
                if (inValue(KEY_LEFT)) {
                    selectedMapIndex = (selectedMapIndex + 4) % 5;
                    keyWait = 10;
                }
                if (inValue(KEY_RIGHT)) {
                    selectedMapIndex = (selectedMapIndex + 1) % 5;
                    keyWait = 10;
                }
            }

            // 難易度表示
            for (int i = 0; i < 3; ++i) {
                fill(i == selectedDifficulty ? 255 : 200, 255, 0);
                drawCenteredText(i == selectedDifficulty ? ("> " + std::string(diff[i])).c_str() : diff[i], 960, 240 + i * 40);
            }

            // マップ番号表示
            char mapLabel[32];
            sprintf_s(mapLabel, "マップ番号: %d", selectedMapIndex);
            drawCenteredText(mapLabel, 960, 400);

            drawCenteredText("↑↓ : 難易度選択   ←→ : マップ選択   Enter : 決定", 960, 460, 20);

            if (currentEnter && !prevEnterKey) {
                if (selectedDifficulty == 0) numBlocks = 3;
                else if (selectedDifficulty == 1) numBlocks = 5;
                else numBlocks = 7;

                State = PLAY;
                playInitFlg = false;
            }
            break;
        }


        case PLAY: {
            clear(0, 0, 0);
            if (!playInitFlg) generateMap();
            drawBoard();
            handleInput();
            if (inValue(KEY_Z)) restartPlay();
            if (inValue(KEY_B)) {
                State = TITLE;
                playInitFlg = false;
            }
            break;
        }
        case CLEAR: {
            clear(0, 0, 0);
            fill(255, 255, 0);
            drawCenteredText("CLEAR!", 960, 300, 32);

            fill(200, 200, 200);
            drawCenteredText("Rキーでタイトルへ", 960, 360, 20);

            if (inValue(KEY_R)) State = TITLE;
            break;
        }

        }

        prevEnterKey = currentEnter;
    }
    
    void GAME::destroy() {}

} // namespace GAME03
