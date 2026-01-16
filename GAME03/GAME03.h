#pragma once
#include <vector>
#include "../MAIN/GAME_BASE.h"
#include "MiniTemplate.h"

namespace GAME03 {

    class GAME : public GAME_BASE {
    public:
        GAME(class MAIN* main);

        int  create()  override;
        void proc()    override;
        void destroy() override;
        int playerX, playerY;
        enum DIFFICULTY { EASY, NORMAL, HARD };
    private:
        MiniTemplate pickStartTemplate();
        static const int SIZE = 9;
        static const int EMPTY = 0;
        static const int BLOCK = 2;

        bool canConnect(const MiniTemplate& A,
            const MiniTemplate& B,
            DIR dir);

        void buildEntryExit(MiniTemplate& t);
        DIR arrow[SIZE][SIZE];


        bool showRoute = false;
        bool canExitRight(const MiniTemplate& t);
        bool canExitLeft(const MiniTemplate& t);
        bool canExitUp(const MiniTemplate& t);
        bool canExitDown(const MiniTemplate& t);

        std::vector<MiniTemplate> miniTemplates;
        void init(DIFFICULTY diff);
        void drawMiniTemplateDebug(const MiniTemplate& t, int ox, int oy);


        void buildArrowFromPath(MiniTemplate& t);


        enum STATE { TITLE, PLAY, CLEAR };

        STATE State = TITLE;
        bool  playInitFlg = false;
        bool  prevEnterKey = false;
        bool showClearRoute = false;

        int clearRouteLength;
        int getTargetBlockCount() const;
        void clearMap();
        void adjustBlockCount();
        int countEmptyCells() const;

        int selectedDifficulty;
        int numBlocks = 0;
        int titleBgm = -1;
        int playBgm = -1;
        int clearBgm = -1;
        int  board[SIZE][SIZE];
        bool visited[SIZE][SIZE];
        int  px = 0, py = 0;

        int  visitCount = 0;
        int  totalEmpty = SIZE * SIZE;
        bool gameClear = false;

        std::vector<std::pair<int, int>> correctPath;
        bool used[SIZE][SIZE];

        // 正解ルート用矢印生成
        bool dfsPath(int x, int y, int target);
        void buildArrowFromCorrectPath();
        std::vector<std::pair<int, int>> path;
        std::vector<std::pair<int, int>> moveHistory;
        std::vector<std::pair<int, int>> shortestPath;
        std::vector<std::pair<int, int>> highlightPath;


        void aaaa();
        // 各処理関数
        void resetVisited();
        void generateMap();
        void drawBoard();
        void handleInput();
        void restartPlay();
        void buildArrowPath();

        void createFullSnakePath();
        void createSolvableMap(int difficulty);
        void loadPredefinedMap(int difficulty, int index);
        void drawCenteredText(const char* str, int centerX, int y, int size = 24);
    };

} // namespace GAME03

