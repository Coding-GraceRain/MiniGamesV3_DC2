#include "../../libOne/inc/libOne.h"
#include "Board.h"

namespace GAME08
{
    Board::Board()
        : currentTurn(WHITE),
        selectedX(-1),
        selectedY(-1)
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                squares[y][x] = Piece();
            }
        }

        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                moveHint[y][x] = false;
                doubleStepHint[y][x] = false;
            }
        }

        // ポーン配置
        for (int x = 0; x < SIZE; x++) {
            squares[1][x] = Piece(PAWN, BLACK);
            squares[6][x] = Piece(PAWN, WHITE);
        }

        // ルーク
        squares[0][0] = squares[0][7] = Piece(ROOK, BLACK);
        squares[7][0] = squares[7][7] = Piece(ROOK, WHITE);

        // ナイト
        squares[0][1] = squares[0][6] = Piece(KNIGHT, BLACK);
        squares[7][1] = squares[7][6] = Piece(KNIGHT, WHITE);

        // ビショップ
        squares[0][2] = squares[0][5] = Piece(BISHOP, BLACK);
        squares[7][2] = squares[7][5] = Piece(BISHOP, WHITE);

        // クイーン
        squares[0][3] = Piece(QUEEN, BLACK);
        squares[7][3] = Piece(QUEEN, WHITE);

        // キング
        squares[0][4] = Piece(KING, BLACK);
        squares[7][4] = Piece(KING, WHITE);
    }

    void Board::draw()
    {
        drawBoard();

        drawMoveHint();

        drawPieces();
    }

    //マスの描画
    void Board::drawBoard()
    {
        const float cell = 100.0f;
        const float offsetX = 200.0f;
        const float offsetY = 100.0f;

        textSize(40);

        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                // 通常マス
                if ((x + y) % 2 == 0) fill(200);
                else fill(100);

                // 選択中マス
                if (x == selectedX && y == selectedY) {
                    fill(255, 200, 0);
                }

                rect(
                    offsetX + x * cell,
                    offsetY + y * cell,
                    cell,
                    cell
                );
            }
        }
    }

    //ヒントの描画
    void Board::drawMoveHint()
    {
        const float cell = 100.0f;
        const float offsetX = 200.0f;
        const float offsetY = 100.0f;

        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                if (moveHint[y][x]) {
                    fill(0, 255, 0, 80); // 通常移動：緑
                }

                else if (doubleStepHint[y][x]) {
                    fill(0, 150, 255, 100); // 初回2マス：青
                }

                else {
                    continue;
                }

                rect(
                    offsetX + x * cell,
                    offsetY + y * cell,
                    cell,
                    cell
                );
            }
        }
    }

    //駒の描画
    void Board::drawPieces()
    {
        const float cell = 100.0f;
        const float offsetX = 200.0f;
        const float offsetY = 100.0f;

        textSize(48);

        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                const Piece& p = squares[y][x];

                // 空マスは描画しない
                if (p.isEmpty()) continue;

                // 色設定
                if (p.color == WHITE) {
                    fill(255);        // 白駒
                }
                else if (p.color == BLACK) {
                    fill(0);          // 黒駒
                }
                else {
                    continue;         // 念のため
                }

                // 駒文字
                char c = p.getChar();

                // ★ libOne では char* が必要
                char str[2] = { c, '\0' };

                text(
                    str,
                    offsetX + x * cell + cell * 0.35f,
                    offsetY + y * cell + cell * 0.65f
                );
            }
        }

    }

    bool Board::isInsideBoard(int mx, int my, int& bx, int& by)
    {
        const int cell = 100;
        const int offsetX = 200;
        const int offsetY = 100;

        if (mx < offsetX || my < offsetY) return false;
        if (mx >= offsetX + cell * SIZE) return false;
        if (my >= offsetY + cell * SIZE) return false;

        bx = (mx - offsetX) / cell;
        by = (my - offsetY) / cell;

        return true;
    }

    //色々更新！
    void Board::update()
    {
        if (!isTrigger(MOUSE_LBUTTON)) return;

        int mx = (int)mouseX;
        int my = (int)mouseY;

        int bx, by;
        if (!isInsideBoard(mx, my, bx, by)) return;

        Piece& clicked = squares[by][bx];

        // まだ何も選択していない場合
        if (selectedX == -1 && selectedY == -1) {

            // 空マスは不可
            if (clicked.isEmpty()) return;

            // 自分の駒のみ選択可能
            if (clicked.color != currentTurn) return;

            // 選択
            selectedX = bx;
            selectedY = by;

            switch (clicked.type) {
            case PAWN:   calcPawnMoveHint(bx, by); break;
            case ROOK:   calcRookMoveHint(bx, by); break;
            case BISHOP: calcBishopMoveHint(bx, by); break;
            case QUEEN:  calcQueenMoveHint(bx, by); break;
            case KNIGHT: calcKnightMoveHint(bx, by); break;
            case KING:   calcKingMoveHint(bx, by); break;
            }

            /*if (clicked.type == PAWN) {
                calcPawnMoveHint(bx, by);
            }
            else if (clicked.type == ROOK) {
                calcRookMoveHint(bx, by);
            }
            else if (clicked.type == BISHOP) {
                calcBishopMoveHint(bx, by);
            }
            else if (clicked.type == QUEEN) {
                calcQueenMoveHint(bx, by);
            }
            else if (clicked.type == KNIGHT) {
                calcKnightMoveHint(bx, by);
            }
            else if (clicked.type == KING) {
                calcKingMoveHint(bx, by);
            }*/


            return;
        }

        // すでに駒を選択している場合
        int sx = selectedX;
        int sy = selectedY;

        if (sx < 0 || sx >= SIZE || sy < 0 || sy >= SIZE) {
            return;
        }

        Piece& selected = squares[sy][sx];

        // 同じ色の駒をクリック → 選び直し
        if (!clicked.isEmpty() && clicked.color == currentTurn) {

            selectedX = bx;
            selectedY = by;

            clearMoveHint();

            switch (clicked.type) {
            case PAWN:   calcPawnMoveHint(bx, by); break;
            case ROOK:   calcRookMoveHint(bx, by); break;
            case BISHOP: calcBishopMoveHint(bx, by); break;
            case QUEEN:  calcQueenMoveHint(bx, by); break;
            case KNIGHT: calcKnightMoveHint(bx, by); break;
            case KING:   calcKingMoveHint(bx, by); break;
            }

            /*if (clicked.type == PAWN) {
                calcPawnMoveHint(bx, by);
            }
            else if (clicked.type == ROOK) {
                calcRookMoveHint(bx, by);
            }
            else if (clicked.type == BISHOP) {
                calcBishopMoveHint(bx, by);
            }
            else if (clicked.type == QUEEN) {
                calcQueenMoveHint(bx, by);
            }
            else if (clicked.type == KNIGHT) {
                calcKnightMoveHint(bx, by);
            }
            else if (clicked.type == KING) {
                calcKingMoveHint(bx, by);
            }*/

            
            return;
        }

        //駒の移動
        bool moved = false;

        switch (selected.type) {
        case PAWN:   moved = canMovePawn(sx, sy, bx, by); break;
        case ROOK:   moved = canMoveRook(sx, sy, bx, by); break;
        case BISHOP: moved = canMoveBishop(sx, sy, bx, by); break;
        case QUEEN:  moved = canMoveQueen(sx, sy, bx, by); break;
        case KNIGHT: moved = canMoveKnight(sx, sy, bx, by); break;
        case KING:   moved = canMoveKing(sx, sy, bx, by); break;
        }

        if (moved) {
            movePiece(sx, sy, bx, by);
            clearMoveHint();
            selectedX = selectedY = -1;
            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
        }

        /*// ポーンの移動
        if (selected.type == PAWN &&
            canMovePawn(sx, sy, bx, by)) {

            movePiece(sx, sy, bx, by);

            clearMoveHint();

            // 選択解除
            selectedX = -1;
            selectedY = -1;

            // 手番交代
            currentTurn =
                (currentTurn == WHITE) ? BLACK : WHITE;
        }

        //ルークの移動
        if (selected.type == ROOK &&
            canMoveRook(sx, sy, bx, by)) {

            movePiece(sx, sy, bx, by);

            clearMoveHint();

            selectedX = -1;
            selectedY = -1;

            currentTurn =
                (currentTurn == WHITE) ? BLACK : WHITE;
        }

        // ビショップの移動
        if (selected.type == BISHOP &&
            canMoveBishop(sx, sy, bx, by)) {

            movePiece(sx, sy, bx, by);

            clearMoveHint(); 

            selectedX = -1;
            selectedY = -1;

            currentTurn =
                (currentTurn == WHITE) ? BLACK : WHITE;
        }

        //クイーンの移動
        if (selected.type == QUEEN &&
            canMoveQueen(sx, sy, bx, by)) {

            movePiece(sx, sy, bx, by);

            clearMoveHint();

            selectedX = -1;
            selectedY = -1;

            currentTurn = 
                (currentTurn == WHITE) ? BLACK : WHITE;
        }

        //ナイトの移動
        if (selected.type == KNIGHT &&
            canMoveKnight(sx, sy, bx, by)) {

            movePiece(sx, sy, bx, by);
            clearMoveHint();

            selectedX = -1;
            selectedY = -1;

            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
        }

        //キングの移動
        if (selected.type == KING &&
            canMoveKing(sx, sy, bx, by)) {

            movePiece(sx, sy, bx, by);
            clearMoveHint();

            selectedX = -1;
            selectedY = -1;

            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
        }*/


    }

    bool Board::isInside(int x, int y) const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    bool Board::isEmpty(int x, int y) const {
        return isInside(x, y) && squares[y][x].isEmpty();
    }

    bool Board::isEnemy(int x, int y, PieceColor myColor) const {
        return isInside(x, y)
            && !squares[y][x].isEmpty()
            && squares[y][x].color != myColor;
    }

    bool Board::hasSelection() const {
        return selectedX != -1 && selectedY != -1;
    }

    //ヒントのクリア
    void Board::clearMoveHint()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                moveHint[y][x] = false;
                doubleStepHint[y][x] = false;
            }
        }
    }

    //ポーンのヒント計算
    void Board::calcPawnMoveHint(int x, int y)
    {
        Piece& p = squares[y][x];
        if (p.type != PAWN) return;

        int dir = (p.color == WHITE) ? -1 : 1;
        int ny = y + dir;

        // 1マス前進
        if (isInside(x, ny) && isEmpty(x, ny)) {
            moveHint[ny][x] = true;

            // 初期位置なら2マス前進
            int startRow = (p.color == WHITE) ? 6 : 1;
            int ny2 = y + dir * 2;

            if (y == startRow && isInside(x, ny2) && isEmpty(x, ny2)) {
                doubleStepHint[ny2][x] = true;
            }
        }

        // 斜め攻撃
        for (int dx = -1; dx <= 1; dx += 2) {
            int nx = x + dx;
            if (isInside(nx, ny) && isEnemy(nx, ny, p.color)) {
                moveHint[ny][nx] = true;
            }
        }
    }

    //ルークのヒント計算
    void Board::calcRookMoveHint(int x, int y)
    {
        Piece& p = squares[y][x];
        if (p.type != ROOK) return;

        // 4方向：右・左・下・上
        const int dirs[4][2] = {
            { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
        };

        for (int d = 0; d < 4; d++) {
            int dx = dirs[d][0];
            int dy = dirs[d][1];

            int cx = x + dx;
            int cy = y + dy;

            while (isInside(cx, cy)) {

                if (isEmpty(cx, cy)) {
                    moveHint[cy][cx] = true;
                }
                else {
                    if (isEnemy(cx, cy, p.color)) {
                        moveHint[cy][cx] = true;
                    }
                    break; // ★ ここ超重要
                }

                cx += dx;
                cy += dy;
            }
        }
    }

    //ビショップのヒント計算
    void Board::calcBishopMoveHint(int x, int y)
    {
        Piece& p = squares[y][x];
        if (p.type != BISHOP) return;

        // 4方向の斜め
        const int dx[4] = { -1,  1, -1,  1 };
        const int dy[4] = { -1, -1,  1,  1 };

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            while (isInside(nx, ny)) {

                // 空マス → 移動可
                if (isEmpty(nx, ny)) {
                    moveHint[ny][nx] = true;
                }
                // 敵 → 取れるが、そこで終了
                else if (isEnemy(nx, ny, p.color)) {
                    moveHint[ny][nx] = true;
                    break;
                }
                // 味方 → そこで終了
                else {
                    break;
                }

                nx += dx[dir];
                ny += dy[dir];
            }
        }
    }

    //クイーンのヒント計算
    void Board::calcQueenMoveHint(int x, int y)
    {
        Piece& q = squares[y][x];
        if (q.type != QUEEN) return;

        PieceColor myColor = q.color;

        // =========================
        // ルーク方向（縦横）
        // =========================
        const int rookDir[4][2] = {
            { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
        };

        for (auto& d : rookDir) {
            int nx = x + d[0];
            int ny = y + d[1];

            while (isInside(nx, ny)) {
                if (isEmpty(nx, ny)) {
                    moveHint[ny][nx] = true;
                }
                else {
                    if (isEnemy(nx, ny, myColor)) {
                        moveHint[ny][nx] = true;
                    }
                    break;
                }
                nx += d[0];
                ny += d[1];
            }
        }

        // =========================
        // ビショップ方向（斜め）
        // =========================
        const int bishopDir[4][2] = {
            { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
        };

        for (auto& d : bishopDir) {
            int nx = x + d[0];
            int ny = y + d[1];

            while (isInside(nx, ny)) {
                if (isEmpty(nx, ny)) {
                    moveHint[ny][nx] = true;
                }
                else {
                    if (isEnemy(nx, ny, myColor)) {
                        moveHint[ny][nx] = true;
                    }
                    break;
                }
                nx += d[0];
                ny += d[1];
            }
        }
    }

    //ナイトのヒント計算
    void Board::calcKnightMoveHint(int x, int y)
    {
        Piece& n = squares[y][x];
        if (n.type != KNIGHT) return;

        const int dx[8] = { 1,  2,  2,  1, -1, -2, -2, -1 };
        const int dy[8] = { -2, -1,  1,  2,  2,  1, -1, -2 };

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (!isInside(nx, ny)) continue;

            // 空 or 敵ならOK
            if (isEmpty(nx, ny) || isEnemy(nx, ny, n.color)) {
                moveHint[ny][nx] = true;
            }
        }
    }

    //キングのヒント計算
    void Board::calcKingMoveHint(int x, int y)
    {
        Piece& k = squares[y][x];
        if (k.type != KING) return;

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {

                if (dx == 0 && dy == 0) continue;

                int nx = x + dx;
                int ny = y + dy;

                if (!isInside(nx, ny)) continue;

                if (isEmpty(nx, ny) || isEnemy(nx, ny, k.color)) {
                    moveHint[ny][nx] = true;
                }
            }
        }
    }



    //移動
    //斜め移動
    bool Board::canMoveDiagonal(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        int dxDir = dx - sx;
        int dyDir = dy - sy;

        if (abs(dxDir) != abs(dyDir)) return false;

        int stepX = (dxDir > 0) ? 1 : -1;
        int stepY = (dyDir > 0) ? 1 : -1;

        int x = sx + stepX;
        int y = sy + stepY;

        while (x != dx) {
            if (!isEmpty(x, y)) return false;
            x += stepX;
            y += stepY;
        }

        // 行き先が味方ならNG
        if (!isEmpty(dx, dy) &&
            squares[dy][dx].color == squares[sy][sx].color)
            return false;

        return true;
    }

    //直線移動
    bool Board::canMoveStraight(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        // 縦でも横でもない
        if (sx != dx && sy != dy) return false;

        int stepX = (dx > sx) ? 1 : (dx < sx ? -1 : 0);
        int stepY = (dy > sy) ? 1 : (dy < sy ? -1 : 0);

        int cx = sx + stepX;
        int cy = sy + stepY;

        while (cx != dx || cy != dy) {
            if (!isEmpty(cx, cy)) return false;
            cx += stepX;
            cy += stepY;
        }

        // 行き先が味方ならNG
        if (!isEmpty(dx, dy) &&
            squares[dy][dx].color == squares[sy][sx].color) {
            return false;
        }

        return true;
    }


    //ポーンの移動判定
    bool Board::canMovePawn(int sx, int sy, int dx, int dy)
    {
        // 範囲外は即NG
        if (!isInside(dx, dy)) return false;

        Piece& pawn = squares[sy][sx];
        if (pawn.type != PAWN) return false;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        // === 前に1マス ===
        if (dx == sx && dy == sy + dir) {
            if (isEmpty(dx, dy)) {
                return true;
            }
        }

        // === 初期位置から2マス ===
        int startRow = (pawn.color == WHITE) ? 6 : 1;
        if (sy == startRow && dx == sx && dy == sy + dir * 2) {
            if (isEmpty(sx, sy + dir) && isEmpty(dx, dy)) {
                return true;
            }
        }

        // === 斜め取り ===
        if (dy == sy + dir && (dx == sx - 1 || dx == sx + 1)) {
            if (isEnemy(dx, dy, pawn.color)) {
                return true;
            }
        }

        return false;
    }

    //ルークの移動判定
    bool Board::canMoveRook(int sx, int sy, int dx, int dy)
    {
        Piece& r = squares[sy][sx];
        if (r.type != ROOK) return false;

        return canMoveStraight(sx, sy, dx, dy);
    }

    //ビショップの移動判定
    bool Board::canMoveBishop(int sx, int sy, int dx, int dy)
    {
        Piece& b = squares[sy][sx];
        if (b.type != BISHOP) return false;

        return canMoveDiagonal(sx, sy, dx, dy);
    }

    //クイーンの移動判定
    bool Board::canMoveQueen(int sx, int sy, int dx, int dy)
    {
        Piece& q = squares[sy][sx];
        if (q.type != QUEEN) return false;

        // 縦横 or 斜め
        if (sx == dx || sy == dy) {
            return canMoveStraight(sx, sy, dx, dy);
        }
        else {
            return canMoveDiagonal(sx, sy, dx, dy);
        }
    }

    //ナイトの移動判定
    bool Board::canMoveKnight(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        Piece& n = squares[sy][sx];
        if (n.type != KNIGHT) return false;

        int dxAbs = abs(dx - sx);
        int dyAbs = abs(dy - sy);

        // L字判定
        if (!((dxAbs == 1 && dyAbs == 2) ||
            (dxAbs == 2 && dyAbs == 1))) {
            return false;
        }

        // 行き先が味方ならNG
        if (!isEmpty(dx, dy) && squares[dy][dx].color == n.color) {
            return false;
        }

        return true;
    }

    //キングの移動判定
    bool Board::canMoveKing(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        Piece& k = squares[sy][sx];
        if (k.type != KING) return false;

        int dxAbs = abs(dx - sx);
        int dyAbs = abs(dy - sy);

        // 1マス移動のみ
        if (dxAbs > 1 || dyAbs > 1) return false;

        // 味方の駒ならNG
        if (!isEmpty(dx, dy) && squares[dy][dx].color == k.color) {
            return false;
        }

        return true;
    }



    //駒の移動
    void Board::movePiece(int sx, int sy, int dx, int dy)
    {
        squares[dy][dx] = squares[sy][sx];
        squares[sy][sx] = Piece(); // 空マス
    }
}