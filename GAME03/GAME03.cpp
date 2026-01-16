#define NOMINMAX
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME03.h"
#include <algorithm>
#include <random>
#include <queue>
#include <cstdio> 
#include "MiniTemplate.h"
namespace GAME03 {
    GAME::GAME(MAIN* main) : GAME_BASE(main) {
        miniTemplates = g_miniTemplates;
    }

    //

    int GAME::create() {
        selectedDifficulty = 0;
        numBlocks = 0;
        gameClear = false;
        State = TITLE;
        playInitFlg = false;
        return 0;
    }
    MiniTemplate GAME::pickStartTemplate()
    {
        while (true)
        {
            MiniTemplate base =
                g_miniTemplates[rand() % g_miniTemplates.size()];

            auto variants = generateVariants(base);

            for (auto& t : variants)
            {
                // 左上マスが道 ＋ 右に出口がある
                if (t.cell[0][0] == 0 && canExitRight(t))
                    return t;
            }
        }
    }


    int GAME::countEmptyCells() const
    {
        int count = 0;
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                if (board[y][x] == EMPTY)
                    count++;
            }
        }
        return count;
    }
    int GAME::getTargetBlockCount() const
    {
        switch (selectedDifficulty) {
        case EASY:   return 5;
        case NORMAL: return 7;
        case HARD:   return 9;
        }
        return 5;
    }
    void GAME::clearMap()
    {
        for (int y = 0; y < 9; ++y)
            for (int x = 0; x < 9; ++x)
                board[y][x] = EMPTY;
    }
    void GAME::resetVisited()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                visited[y][x] = false;
            }
        }
    }
    void GAME::adjustBlockCount()
    {
        int target = 0;

        if (selectedDifficulty == EASY)   target = 5;
        if (selectedDifficulty == NORMAL) target = 7;
        if (selectedDifficulty == HARD)   target = 9;

        std::vector<std::pair<int, int>> emptyCells;
        std::vector<std::pair<int, int>> blockCells;

        for (int y = 0; y < 9; ++y) {
            for (int x = 0; x < 9; ++x) {
                if (board[y][x] == EMPTY)
                    emptyCells.push_back({ x, y });
                else if (board[y][x] == BLOCK)
                    blockCells.push_back({ x, y });
            }
        }

        std::mt19937 rng{ std::random_device{}() };

        // ===== ブロックが多すぎる場合 → 減らす =====
        while ((int)blockCells.size() > target) {
            std::uniform_int_distribution<int> dist(0, blockCells.size() - 1);
            int idx = dist(rng);
            auto p = blockCells[idx];

            board[p.second][p.first] = EMPTY;
            blockCells.erase(blockCells.begin() + idx);
            emptyCells.push_back(p);
        }

        // ===== ブロックが少なすぎる場合 → 増やす =====
        while ((int)blockCells.size() < target && !emptyCells.empty()) {
            std::uniform_int_distribution<int> dist(0, emptyCells.size() - 1);
            int idx = dist(rng);
            auto p = emptyCells[idx];

            board[p.second][p.first] = BLOCK;
            emptyCells.erase(emptyCells.begin() + idx);
            blockCells.push_back(p);
        }
    }
    int countDegree(const MiniTemplate& t, int x, int y)
    {
        int d = 0;
        const int dx[4] = { 1, -1, 0, 0 };
        const int dy[4] = { 0, 0, 1, -1 };

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
            if (t.cell[ny][nx] == 0) d++;
        }
        return d;
    }
    void buildCanStartGoal(MiniTemplate& t, int sx, int sy)
    {
        // 初期化
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                t.canStart[y][x] = t.canGoal[y][x] = false;

        // 通路の端点（次数1）を探す
        std::vector<std::pair<int, int>> endpoints;

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (t.cell[y][x] != 0) continue;
                if (countDegree(t, x, y) == 1)
                    endpoints.push_back({ x, y });
            }
        }

        // 正しい一筆書きテンプレでなければ無効
        if (endpoints.size() != 2) return;

        auto e1 = endpoints[0];
        auto e2 = endpoints[1];

        // スタートと一致する方を canStart に
        if (e1.first == sx && e1.second == sy) {
            t.canStart[sy][sx] = true;
            t.canGoal[e2.second][e2.first] = true;
        }
        else if (e2.first == sx && e2.second == sy) {
            t.canStart[sy][sx] = true;
            t.canGoal[e1.second][e1.first] = true;
        }
    }
    void buildCanStartGoalFromPath(MiniTemplate& t)
    {
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                t.canStart[y][x] = t.canGoal[y][x] = false;

        auto s = t.mainPath.front();
        auto g = t.mainPath.back();

        t.canStart[s.second][s.first] = true;
        t.canGoal[g.second][g.first] = true;
    }

    void buildArrowFromPath(MiniTemplate& t)
    {
        // 矢印初期化
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                t.arrow[y][x] = NONE;
            }
        }

        for (size_t i = 0; i + 1 < t.mainPath.size(); i++)
        {
            std::pair<int, int> p1 = t.mainPath[i];
            std::pair<int, int> p2 = t.mainPath[i + 1];

            int x1 = p1.first;
            int y1 = p1.second;
            int x2 = p2.first;
            int y2 = p2.second;

            if (x2 == x1 + 1)      t.arrow[y1][x1] = RIGHT;
            else if (x2 == x1 - 1) t.arrow[y1][x1] = LEFT;
            else if (y2 == y1 + 1) t.arrow[y1][x1] = DOWN;
            else if (y2 == y1 - 1) t.arrow[y1][x1] = UP;
        }
    }
    void GAME::drawMiniTemplateDebug(const MiniTemplate& t, int ox, int oy)
    {
        const int cell = 40;
        const int margin = 4;

        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                int cx = ox + x * cell;
                int cy = oy + y * cell;

                // マスの色
                if (t.cell[y][x] == 1)
                    fill(80, 80, 80);          // 壁
                else
                    fill(230, 230, 230);       // 道

                rect(cx, cy, cell - margin, cell - margin);

                // スタート候補
                if (t.canStart[y][x])
                {
                    fill(0, 200, 255);
                    circle(cx + 18, cy + 18, 6);
                }

                // ゴール候補
                if (t.canGoal[y][x])
                {
                    fill(255, 200, 0);
                    circle(cx + 30, cy + 30, 6);
                }

                // 矢印（mainPath）
                if (t.arrow[y][x] != NONE)
                {
                    fill(0, 0, 0);
                    const char* s = "";
                    if (t.arrow[y][x] == RIGHT) s = "→";
                    else if (t.arrow[y][x] == LEFT) s = "←";
                    else if (t.arrow[y][x] == UP) s = "↑";
                    else if (t.arrow[y][x] == DOWN) s = "↓";

                    textSize(18);
                    text(s, cx + 10, cy + 22);
                }
            }
        }
    }

    void GAME::generateMap()
    {
        srand((unsigned)time(nullptr));

        clearMap();

        // =========================

        MiniTemplate placed[9];

        DIR dirs[8] = {
            RIGHT, RIGHT,
            DOWN,
            LEFT, LEFT,
            DOWN,
            RIGHT, RIGHT
        };

        // 左上スタート
        placed[0] = pickStartTemplate();


        buildCanStartGoal(placed[0], 0, 0);
        for (int i = 1; i < 9; i++)
        {
            DIR d = dirs[i - 1];
            std::vector<MiniTemplate> candidates;

            for (auto& base : g_miniTemplates)
            {
                auto variants = generateVariants(base);

                for (auto& t : variants)
                {
                    if (canConnect(placed[i - 1], t, d))
                        candidates.push_back(t);
                }
            }

            // 接続不能 → 最初からやり直し
            if (candidates.empty()) {
                i = 0;
                placed[0] = pickStartTemplate();
                continue;
            }

            placed[i] = candidates[rand() % candidates.size()];
            if (i == 8)
            {
                std::vector<MiniTemplate> finalCandidates;
                for (auto& t : candidates)
                {
                    if (canExitDown(t))   // ← ゴール出口保証
                        finalCandidates.push_back(t);
                }

                if (finalCandidates.empty()) {
                    i = 0;
                    placed[0] = pickStartTemplate();
                    continue;
                }

                placed[i] = finalCandidates[rand() % finalCandidates.size()];
            }
            else
            {
                placed[i] = candidates[rand() % candidates.size()];
            }
        }

        for (int i = 0; i < 9; i++)
        {
            int baseX = (i % 3) * 3;
            int baseY = (i / 3) * 3;

            MiniTemplate& t = placed[i];

            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    board[baseY + y][baseX + x] =
                        (t.cell[y][x] == 0) ? EMPTY : BLOCK;
                }
            }
        }

        adjustBlockCount();

        resetVisited();
        totalEmpty = countEmptyCells();
        visitCount = 1;

        playerX = 0;
        playerY = 0;
        visited[0][0] = true;

        playInitFlg = true;
    }

    bool GAME::canConnect(
        const MiniTemplate& A,
        const MiniTemplate& B,
        DIR dir)
    {
        if (dir == RIGHT) {
            for (int y = 0; y < 3; y++) {
                if (A.canGoal[y][2] && B.canStart[y][0])
                    return true;
            }
        }

        if (dir == LEFT) {
            for (int y = 0; y < 3; y++) {
                if (A.canGoal[y][0] && B.canStart[y][2])
                    return true;
            }
        }

        if (dir == DOWN) {
            for (int x = 0; x < 3; x++) {
                if (A.canGoal[2][x] && B.canStart[0][x])
                    return true;
            }
        }

        if (dir == UP) {
            for (int x = 0; x < 3; x++) {
                if (A.canGoal[0][x] && B.canStart[2][x])
                    return true;
            }
        }

        return false;
    }

    bool GAME::canExitRight(const MiniTemplate& t)
    {
        for (int y = 0; y < 3; ++y)
            if (t.cell[y][2] == 0)
                return true;
        return false;
    }

    bool GAME::canExitLeft(const MiniTemplate& t)
    {
        for (int y = 0; y < 3; ++y)
            if (t.cell[y][0] == 0)
                return true;
        return false;
    }

    bool GAME::canExitUp(const MiniTemplate& t)
    {
        for (int x = 0; x < 3; ++x)
            if (t.cell[0][x] == 0)
                return true;
        return false;
    }

    bool GAME::canExitDown(const MiniTemplate& t)
    {
        for (int x = 0; x < 3; ++x)
            if (t.cell[2][x] == 0)
                return true;
        return false;
    }
    bool GAME::dfsPath(int x, int y, int target)
    {
        if ((int)correctPath.size() == target)
            return true;

        used[x][y] = true;

        std::vector<int> dir = { 0,1,2,3 };
        std::shuffle(dir.begin(), dir.end(),
            std::mt19937{ std::random_device{}() });

        for (int d : dir) {
            int nx = x, ny = y;
            if (d == 0) nx++;
            if (d == 1) nx--;
            if (d == 2) ny++;
            if (d == 3) ny--;

            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE) continue;
            if (used[nx][ny]) continue;

            correctPath.push_back({ nx, ny });
            if (dfsPath(nx, ny, target))
                return true;
            correctPath.pop_back();
        }

        // ★ ここが超重要 ★
        used[x][y] = false;
        return false;
    }

    void GAME::buildArrowPath()
    {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                arrow[x][y] = NONE;

        // 正解ルート分だけ矢印を作る
        for (int i = 0; i + 1 < clearRouteLength; ++i) {

            int x1 = path[i].first;
            int y1 = path[i].second;
            int x2 = path[i + 1].first;
            int y2 = path[i + 1].second;

            // BLOCK マスには矢印を置かない
            if (board[x1][y1] == BLOCK) continue;
            if (board[x2][y2] == BLOCK) continue;

            if (x2 == x1 + 1)      arrow[x1][y1] == RIGHT;
            else if (x2 == x1 - 1) arrow[x1][y1] == LEFT;
            else if (y2 == y1 + 1) arrow[x1][y1] == DOWN;
            else if (y2 == y1 - 1) arrow[x1][y1] == UP;
        }
    }
    void GAME::handleInput() {
        static bool prevA = false, prevD = false, prevW = false, prevS = false, prevZ = false;

        bool a = inValue(KEY_A), d = inValue(KEY_D),
            w = inValue(KEY_W), s = inValue(KEY_S),
            r = inValue(KEY_R);

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
        else if (r && !prevZ && moveHistory.size() > 0) {
            auto prev = moveHistory.back();
            moveHistory.pop_back();
            visited[px][py] = false;
            px = prev.first;
            py = prev.second;
            visitCount--;
        }


        prevA = a; prevD = d; prevW = w; prevS = s; prevZ = r;

        if (!visited[px][py]) {
            visited[px][py] = true;
            visitCount++;
        }

        if (visitCount >= totalEmpty) {
            gameClear = true;
            State = CLEAR;
        }
        if (isTrigger(KEY_V)) {
            showRoute = !showRoute;
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

                // --- マスの色 ---
                if (board[x][y] == BLOCK) fill(100, 100, 100);
                else if (visited[x][y])  fill(0, 200, 0);
                else                     fill(255, 255, 255);

                rect(cx, cy, cellSize - margin, cellSize - margin);



                // --- ルート矢印 ---
                if (showRoute && arrow[x][y] != NONE && board[x][y] == EMPTY) {
                    fill(0, 0, 0);
                    const char* s = "";
                    if (arrow[x][y] == RIGHT) s = "→";
                    else if (arrow[x][y] == LEFT) s = "←";
                    else if (arrow[x][y] == UP) s = "↑";
                    else if (arrow[x][y] == DOWN) s = "↓";

                    textSize(20);
                    text(s, cx + 10, cy + 25);
                }

                // --- プレイヤー ---
                if (x == px && y == py) {
                    fill(255, 0, 0);
                    circle(cx + (cellSize - margin) / 2,
                        cy + (cellSize - margin) / 2, 10);
                }
            }
        }

        // --- UI ---
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

        // ===== デバッグ表示 =====
        if (!g_miniTemplates.empty())
        {
            drawMiniTemplateDebug(g_miniTemplates[0], 50, 50);
        }
        // ===== mainPath デバッグ表示 =====
        MiniTemplate t = g_miniTemplates[0];

        // 仮 mainPath
        t.mainPath = {
            {0,0},{1,0},{2,0},
            {2,1},{1,1},{0,1},
            {0,2},{1,2},{2,2}
        };

        buildArrowFromPath(t);
        drawMiniTemplateDebug(t, 50, 50);


    }
    void GAME::restartPlay() {
        // スタート位置に戻す
        px = 0;
        py = 0;

        // 訪問情報リセット
        resetVisited();
        visited[px][py] = true;

        // ★重要：移動履歴を完全に破棄

        visitCount = 1;
        gameClear = false;
        showClearRoute = false;
        moveHistory.clear();

    }
    void GAME::createFullSnakePath()
    {
        path.clear();

        for (int y = 0; y < SIZE; ++y) {
            if (y % 2 == 0) {
                for (int x = 0; x < SIZE; ++x)
                    path.push_back({ x, y });
            }
            else {
                for (int x = SIZE - 1; x >= 0; --x)
                    path.push_back({ x, y });
            }
        }
    }
    void GAME::buildArrowFromPath(MiniTemplate& t)
    {
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                t.arrow[y][x] = NONE;

        for (size_t i = 0; i + 1 < t.mainPath.size(); i++)
        {
            int x1 = t.mainPath[i].first;
            int y1 = t.mainPath[i].second;
            int x2 = t.mainPath[i + 1].first;
            int y2 = t.mainPath[i + 1].second;

            if (x2 == x1 + 1) t.arrow[y1][x1] = RIGHT;
            else if (x2 == x1 - 1) t.arrow[y1][x1] = LEFT;
            else if (y2 == y1 + 1) t.arrow[y1][x1] = DOWN;
            else if (y2 == y1 - 1) t.arrow[y1][x1] = UP;
        }
    }

    void GAME::drawCenteredText(const char* str, int centerX, int y, int size) {
        textSize(size);
        int width = strlen(str) * 10;
        text(str, centerX - width / 2, y);
    }

    void GAME::proc() {


        bool currentEnter = inValue(KEY_SPACE);

        switch (State) {
        case TITLE: {
            clear(0, 0, 0);
            textSize(32);
            drawCenteredText("迷路ゲーム", 960, 100);
            textSize(24);
            drawCenteredText("難易度とマップ番号を選んでください", 960, 180);

            text("ENTERキーでメニューに戻る", 0, 1080);
            if (isTrigger(KEY_ENTER)) {
                main()->backToMenu();
            }
            const char* diff[] = { "簡単　", "普通　", "難しい" };

            static int keyWait = 0;
            if (keyWait > 0) keyWait--;
            if (keyWait == 0) {
                if (isTrigger(KEY_UP)) {
                    selectedDifficulty = (selectedDifficulty + 2) % 3;
                    keyWait = 10;
                }
                if (isTrigger(KEY_DOWN)) {
                    selectedDifficulty = (selectedDifficulty + 1) % 3;
                    keyWait = 10;
                }
            }
            for (int i = 0; i < 3; ++i) {
                if (i == selectedDifficulty) fill(255, 255, 0);
                else                         fill(200, 200, 200);

                drawCenteredText(diff[i], 960, 240 + i * 40);
            }

            // 選択矢印
            fill(255, 255, 255);
            textSize(24);
            text(">", 960 - 120, 240 + selectedDifficulty * 40);





            drawCenteredText("↑↓ : マップ選択   SPACE : 決定", 960, 460, 20);

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

            if (!playInitFlg) {
                generateMap();

                // ===== 状態初期化 =====
                resetVisited();
                visitCount = 0;
                gameClear = false;

                // プレイヤー初期位置
                py = 0;
                px = 0;


                // スタートマスを訪問済みにする
                visited[playerY][playerX] = true;
                visitCount = 1;
                moveHistory.clear(); // ★必須
                moveHistory.push_back({ 0,0 });
                playInitFlg = true;
            }

            drawBoard();
            handleInput();

            if (isTrigger(KEY_Z)) {
                restartPlay();
            }

            if (isTrigger(KEY_B)) {
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

            if (isTrigger(KEY_R)) {
                State = TITLE;

                // ===== 次回プレイ用に初期化フラグを戻す =====
                playInitFlg = false;
            }
            break;
        }
        }

        prevEnterKey = currentEnter;
    }

    void GAME::destroy() {}

} // namespace GAME03