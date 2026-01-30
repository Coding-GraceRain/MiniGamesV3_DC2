#include "../../libOne/inc/libOne.h"
#include "Board.h"

namespace GAME08
{     
    static const float CELL = 100.0f;
    static const float BOARD_X = 200.0f;
    static const float BOARD_Y = 100.0f;

    struct Board::MoveBackup {
        Piece from;
        Piece to;

        // 特殊手用
        bool hadExtra = false;
        int ex = -1;
        int ey = -1;
        Piece extra;
    };
    
    Board::Board()
        : currentTurn(WHITE),
        selectedX(-1),
        selectedY(-1),
        enPassantX(0),
        enPassantY(0),
        enPassantAvailable(false),
        inCheck(false),
        inCheckmate(false),
        inStalemate(false),
        promotionPending(false),
        promotionColor(WHITE),
        promotionX(0),
        promotionY(0)
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                squares[y][x] = Piece();
                moveHint[y][x] = false;
                doubleStepHint[y][x] = false;
                specialMoveHint[y][x] = false;
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

    // メインループ
    void Board::update()
    {
        if (inCheckmate)return;

        if (promotionPending) {
            handlePromotionInput();
            return;
        }

        bool leftClick = isTrigger(MOUSE_LBUTTON);
        bool rightClick = isTrigger(MOUSE_RBUTTON);

        if (!leftClick && !rightClick) return;

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

            clearMoveHint();

            //特殊ヒント
            if (rightClick) {
                if (clicked.type == KING) {
                    calcCastlingHint(bx, by);
                }
                else if (clicked.type == PAWN) {
                    calcEnPassantHint(bx, by);
                }
                return;
            }

            //通常ヒント
            switch (clicked.type) {
            case PAWN:   calcPawnMoveHint(bx, by); break;
            case ROOK:   calcRookMoveHint(bx, by); break;
            case BISHOP: calcBishopMoveHint(bx, by); break;
            case QUEEN:  calcQueenMoveHint(bx, by); break;
            case KNIGHT: calcKnightMoveHint(bx, by); break;
            case KING:   calcKingMoveHint(bx, by); break;
            }

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

            //右クリックのヒント表示
            if (hasSelection() && rightClick) {
                clearMoveHint();

                Piece& p = squares[selectedY][selectedX];

                if (p.type == KING) {
                    calcCastlingHint(selectedX, selectedY);
                }
                else if (p.type == PAWN) {
                    calcEnPassantHint(selectedX, selectedY);
                }
                return;
            }

            switch (clicked.type) {
            case PAWN:   calcPawnMoveHint(bx, by); break;
            case ROOK:   calcRookMoveHint(bx, by); break;
            case BISHOP: calcBishopMoveHint(bx, by); break;
            case QUEEN:  calcQueenMoveHint(bx, by); break;
            case KNIGHT: calcKnightMoveHint(bx, by); break;
            case KING:   calcKingMoveHint(bx, by); break;
            }

            return;
        }

        //特殊手の移動
        if (!rightClick && hasSelection() && specialMoveHint[by][bx]) 
        {
            int sx = selectedX;
            int sy = selectedY;
            Piece& p = squares[sy][sx];
            bool moved = false;

            if (p.type == KING) {
                moved = executeCastle(sx, sy, bx, by);
            }
            else if (p.type == PAWN) {
                moved = executeEnPassant(sx, sy, bx, by);
            }

            if (moved) {
                resetSelection();
                currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;

                inCheck = isKingInCheck(currentTurn);
                inCheckmate = isCheckmate(currentTurn);
            }
            return; 
        }

        //通常手の移動
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
            //王手が解消されるか確認
            if (wouldBeInCheckAfterMove(sx, sy, bx, by, currentTurn)) {
                return; //王手が続く手はNG
            }
            if (selected.type == KING) {
                moveKing(sx, sy, bx, by);
            }
            else {
                movePiece(sx, sy, bx, by);
                // プロモーション判定
                if (squares[by][bx].type == PAWN) {
                    if ((squares[by][bx].color == WHITE && by == 0) ||
                        (squares[by][bx].color == BLACK && by == 7))
                    {
                        promotionPending = true;
                        promotionX = bx;
                        promotionY = by;
                        promotionColor = squares[by][bx].color;
                        return; // ターンを進めない
                    }
                }
                squares[by][bx].hasMoved = true;
            }

            resetSelection();
            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;

            // 状態更新
            inCheck = isKingInCheck(currentTurn);
            inCheckmate = isCheckmate(currentTurn);
            inStalemate = isStalemate(currentTurn);
        }

    }
    void Board::draw()
    {
        drawBoard();

        drawMoveHint();

        drawPieces();

        drawUI();

        if (promotionPending) {
            drawPromotionUI();
        }
    }

    // 描画系
    void Board::drawBoard()
    {
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
                    BOARD_X + x * CELL,
                    BOARD_Y + y * CELL,
                    CELL,
                    CELL
                );
            }
        }
    }
    void Board::drawMoveHint()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                if (moveHint[y][x]) {
                    fill(0, 255, 0, 80); // 通常移動：緑
                }

                else if (doubleStepHint[y][x]) {
                    fill(0, 150, 255, 100); // 初回2マス：青
                }

                else if (specialMoveHint[y][x]) {
                    fill(255, 0, 255, 120); // 紫
                }

                else {
                    noFill();
                    continue;
                }

                rect(
                    BOARD_X + x * CELL,
                    BOARD_Y + y * CELL,
                    CELL,
                    CELL
                );
            }
        }
    }
    void Board::drawPieces()
    {
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

                char str[2] = { c, '\0' };

                text(
                    str,
                    BOARD_X + x * CELL + CELL * 0.35f,
                    BOARD_Y + y * CELL + CELL * 0.65f
                );
            }
        }       
    }

    // UI系
    void Board::drawUI() 
    {
        drawStatusText();
        drawCheckKingHighlight();
    }
    void Board::drawStatusText()
    {
        float x = 30.0f;
        float y = 40.0f;

        // 手番表示
        fill(255);
        textSize(28);

        if (currentTurn == WHITE) {
            text("Turn : WHITE", x, y);
        }
        else {
            text("Turn : BLACK", x, y);
        }

        y += 40;

        // チェック表示
        if (inCheck) {
            fill(255, 0, 0);   
            textSize(32);
            text("CHECK!", x, y);
            y += 45;
        }

        // チェックメイト表示
        if (inCheckmate) {
            fill(255, 215, 0);
            textSize(36);
            text("CHECKMATE!", x, y);
        }

        // ステイルメイト表示
        if (inStalemate) {
            fill(180, 180, 255);
            textSize(32);
            text("STALEMATE", x, y);
        }
    }
    void Board::drawCheckKingHighlight()
    {
        // 王手じゃなければ何もしない
        if (!inCheck) return;

        PieceColor kingColor = currentTurn;

        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                Piece& p = squares[y][x];
                if (p.type == KING && p.color == kingColor) {

                    float px = BOARD_X + x * CELL;
                    float py = BOARD_Y + y * CELL;

                    noFill();
                    stroke(255, 0, 0);
                    strokeWeight(4);
                    rect(px, py, CELL, CELL);
                    strokeWeight(1);
                    noStroke();

                    return;
                }
            }
        }
    }
    void Board::drawPromotionUI()
    {
        float x = 1050.0f;
        float y = 200.0f;

        fill(50);
        rect(x - 20, y - 40, 220, 260);

        fill(255);
        textSize(32);
        text("Promotion", x, y - 10);

        const char* labels[4] = { "Q", "R", "B", "N" };

        for (int i = 0; i < 4; i++) {
            text(
                labels[i],
                x,
                y + 50 + i * 45
            );
        }
    }

    // 入力・選択
    bool Board::hasSelection() const {
        return selectedX != -1 && selectedY != -1;
    }
    bool Board::isInsideBoard(int mx, int my, int& bx, int& by)
    {
        if (mx < BOARD_X || my < BOARD_Y) return false;
        if (mx >= BOARD_X + CELL * SIZE) return false;
        if (my >= BOARD_Y + CELL * SIZE) return false;

        bx = (int)((mx - BOARD_X) / CELL);
        by = (int)((my - BOARD_Y) / CELL);

        return true;
    }
    void Board::clearMoveHint()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                moveHint[y][x] = false;
                doubleStepHint[y][x] = false;
                specialMoveHint[y][x] = false;
            }
        }
    }
    void Board::resetSelection()
    {
        clearMoveHint();
        selectedX = selectedY = -1;
    }

    // 共通ユーティリティ
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

    // 共通移動ロジック
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

    // ポーン
    void Board::calcPawnMoveHint(int x, int y)
    {
        Piece& p = squares[y][x];
        if (p.type != PAWN) return;

        int dir = (p.color == WHITE) ? -1 : 1;
        int ny = y + dir;

        // 1マス前進
        if (isInside(x, ny) && isEmpty(x, ny)) {
            if (!wouldBeInCheckAfterMove(x, y, x, ny, p.color)) {
                moveHint[ny][x] = true;
            }

            // 初期位置なら2マス前進
            int startRow = (p.color == WHITE) ? 6 : 1;
            int ny2 = y + dir * 2;

            if (y == startRow && isInside(x, ny2) && isEmpty(x, ny2)) {
                if (!wouldBeInCheckAfterMove(x, y, x, ny2, p.color)) {
                    doubleStepHint[ny2][x] = true;
                }
            }
        }

        // 斜め攻撃
        for (int dx = -1; dx <= 1; dx += 2) {
            int nx = x + dx;
            if (isInside(nx, ny) && isEnemy(nx, ny, p.color)) {
                if (!wouldBeInCheckAfterMove(x, y, nx, ny, p.color)) {
                    moveHint[ny][nx] = true;
                }
            }
        }
    }
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
    bool Board::canPawnAttack(int sx, int sy, int tx, int ty)
    {
        Piece& pawn = squares[sy][sx];
        if (pawn.type != PAWN) return false;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        return (ty == sy + dir) &&
            (tx == sx - 1 || tx == sx + 1);
    }
    bool Board::executeEnPassant(int sx, int sy, int dx, int dy)
    {
        if (!enPassantAvailable) return false;

        Piece& pawn = squares[sy][sx];
        if (pawn.type != PAWN) return false;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        // 移動先チェック
        if (dx != enPassantX || dy != sy + dir)
            return false;

        // 取られるポーン確認
        Piece& target = squares[sy][dx];
        if (target.type != PAWN || target.color == pawn.color)
            return false;

        // 実行
        squares[sy][dx] = Piece();   // 敵ポーン除去
        movePiece(sx, sy, dx, dy);

        enPassantAvailable = false;
        return true;
    }
    void Board::calcEnPassantHint(int x, int y)
    {
        if (!enPassantAvailable) return;

        Piece& pawn = squares[y][x];
        if (pawn.type != PAWN) return;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        // ★ ここが修正点
        if (abs(enPassantX - x) == 1 && enPassantY == y + dir) {
            specialMoveHint[y + dir][enPassantX] = true;
        }
    }

    // ルーク
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
                    if (!wouldBeInCheckAfterMove(x, y, cx, cy, p.color)) {
                        moveHint[cy][cx] = true;
                    }
                }
                else {
                    if (isEnemy(cx, cy, p.color)) {
                        if (!wouldBeInCheckAfterMove(x, y, cx, cy, p.color)) {
                            moveHint[cy][cx] = true;
                        }
                    }
                    break; // ★ ここ超重要
                }

                cx += dx;
                cy += dy;
            }
        }
    }
    bool Board::canMoveRook(int sx, int sy, int dx, int dy)
    {
        Piece& r = squares[sy][sx];
        if (r.type != ROOK) return false;

        return canMoveStraight(sx, sy, dx, dy);
    }

    // ビショップ
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
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, p.color)) {
                        moveHint[ny][nx] = true;
                    }
                }
                // 敵 → 取れるが、そこで終了
                else if (isEnemy(nx, ny, p.color)) {
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, p.color)) {
                        moveHint[ny][nx] = true;
                    }
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
    bool Board::canMoveBishop(int sx, int sy, int dx, int dy)
    {
        Piece& b = squares[sy][sx];
        if (b.type != BISHOP) return false;

        return canMoveDiagonal(sx, sy, dx, dy);
    }

    // クイーン 
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
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                        moveHint[ny][nx] = true;
                    }
                }
                else {
                    if (isEnemy(nx, ny, myColor)) {
                        if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                            moveHint[ny][nx] = true;
                        }
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
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                        moveHint[ny][nx] = true;
                    }
                }
                else {
                    if (isEnemy(nx, ny, myColor)) {
                        if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                            moveHint[ny][nx] = true;
                        }
                    }
                    break;
                }
                nx += d[0];
                ny += d[1];
            }
        }
    }
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

    // ナイト 
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
                if (!wouldBeInCheckAfterMove(x, y, nx, ny, n.color)) {
                    moveHint[ny][nx] = true;
                }
            }
        }
    }
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

    // キング 
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
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, k.color)) {
                        moveHint[ny][nx] = true;
                    }
                }
            }
        }
    }
    bool Board::canMoveKing(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        Piece& k = squares[sy][sx];
        if (k.type != KING) return false;

        int dxAbs = abs(dx - sx);
        int dyAbs = abs(dy - sy);

        if (dxAbs <= 1 && dyAbs <= 1) {
            if (isEmpty(dx, dy) || isEnemy(dx, dy, k.color)) {
                if (!wouldBeInCheckAfterMove(sx, sy, dx, dy, k.color))
                    return true;
            }
        }

        return false;
    }
 
    bool Board::executeCastle(int sx, int sy, int dx, int dy)
    {
        Piece& k = squares[sy][sx];
        if (k.type != KING) return false;

        if (abs(dx - sx) != 2 || dy != sy) return false;

        bool kingSide = (dx > sx);

        if (!canCastle(k.color, kingSide)) return false;

        moveKing(sx, sy, dx, dy);
        return true;
    }
    void Board::moveKing(int sx, int sy, int dx, int dy) {
        bool isCastling = (abs(dx - sx) == 2);

        if (isCastling) {
            int step = (dx > sx) ? 1 : -1;
            int rookFromX = (step == 1) ? 7 : 0;
            int rookToX = sx + step;

            // ルーク移動
            squares[sy][rookToX] = squares[sy][rookFromX];
            squares[sy][rookToX].hasMoved = true;
            squares[sy][rookFromX] = Piece();
        }

        // キング移動
        squares[dy][dx] = squares[sy][sx];
        squares[dy][dx].hasMoved = true;
        squares[sy][sx] = Piece();
    }

    bool Board::canCastleKingSide(PieceColor color)
    {
        int row = (color == WHITE) ? 7 : 0;

        //キング確認
        if (squares[row][4].type != KING ||
            squares[row][4].hasMoved)
            return false;

        // ルーク確認
        if (squares[row][7].type != ROOK ||
            squares[row][7].color != color ||
            squares[row][7].hasMoved)
            return false;

        // 間が空いているか
        if (!isEmpty(5, row) || !isEmpty(6, row)) return false;

        // 通過マスが安全か
        if (wouldBeInCheckAfterMove(4, row, 5, row, color)) return false;
        if (wouldBeInCheckAfterMove(4, row, 6, row, color)) return false;

        return true;
    }
    bool Board::canCastleQueenSide(PieceColor color)
    {
        int row = (color == WHITE) ? 7 : 0;

        // クイーン側ルークがいるか
        if (squares[row][0].type != ROOK ||
            squares[row][0].color != color ||
            squares[row][0].hasMoved)
            return false;

        // キング側も確認
        if (squares[row][4].type != KING ||
            squares[row][4].hasMoved)
            return false;

        // 間のマスが空か（b,c,d）
        if (!isEmpty(1, row) || !isEmpty(2, row) || !isEmpty(3, row))
            return false;

        // キングが通過・到達するマスが安全か
        // e → d
        if (wouldBeInCheckAfterMove(4, row, 3, row, color))
            return false;

        // e → c
        if (wouldBeInCheckAfterMove(4, row, 2, row, color))
            return false;

        return true;

    }
    bool Board::canCastle(PieceColor color, bool kingSide)
    {
        // 共通：今チェックされていたら不可
        if (isKingInCheck(color))
            return false;

        if (kingSide)
            return canCastleKingSide(color);
        else
            return canCastleQueenSide(color);
    }
    void Board::calcCastlingHint(int x, int y)
    {
        Piece& king = squares[y][x];
        if (king.type != KING) return;

        // すでにチェック中なら不可
        if (isKingInCheck(king.color)) return;

        int row = (king.color == WHITE) ? 7 : 0;

        // キング側
        if (canCastleKingSide(king.color)) {
            specialMoveHint[row][6] = true;
        }

        // クイーン側
        if (canCastleQueenSide(king.color)) {
            specialMoveHint[row][2] = true;
        }
    }

    // 実移動
    void Board::movePiece(int sx, int sy, int dx, int dy)
    {
        Piece& p = squares[sy][sx];

        // デフォルトでアンパッサン無効
        enPassantAvailable = false;

        // ポーンの2マス前進を検知
        if (p.type == PAWN && abs(dy - sy) == 2) {
            enPassantAvailable = true;
            enPassantX = dx;
            enPassantY = (sy + dy) / 2; // 通過マス
        }

        squares[dy][dx] = p;
        squares[dy][dx].hasMoved = true;
        squares[sy][sx] = Piece();
    }
    bool Board::canMoveByType(int sx, int sy, int dx, int dy)
    {
        Piece& p = squares[sy][sx];

        switch (p.type) {
        case PAWN:   return canMovePawn(sx, sy, dx, dy);
        case ROOK:   return canMoveRook(sx, sy, dx, dy);
        case BISHOP: return canMoveBishop(sx, sy, dx, dy);
        case QUEEN:  return canMoveQueen(sx, sy, dx, dy);
        case KNIGHT: return canMoveKnight(sx, sy, dx, dy);
        case KING:   return canMoveKing(sx, sy, dx, dy);
        default:     return false;
        }
    }

    // 仮想移動
    Board::MoveBackup Board::simulateMove(int sx, int sy, int dx, int dy)
    {
        MoveBackup b;

        b.from = squares[sy][sx];
        b.to = squares[dy][dx];

        Piece& p = squares[sy][sx];

        // ---- アンパッサン ----
        int dir = (p.color == WHITE) ? -1 : 1;

        if (p.type == PAWN &&
            enPassantAvailable &&
            dx == enPassantX &&
            dy == sy + dir)
        {
            int capY = sy;
            b.hadExtra = true;
            b.ex = dx;
            b.ey = capY;
            b.extra = squares[capY][dx];

            squares[capY][dx] = Piece();
        }

        // ---- 本体移動 ----
        squares[dy][dx] = p;
        squares[sy][sx] = Piece();

        return b;
    }
    void Board::undoSimulateMove(
        int sx, int sy,
        int dx, int dy,
        const MoveBackup& b
    ) {
        squares[sy][sx] = b.from;
        squares[dy][dx] = b.to;

        if (b.hadExtra) {
            squares[b.ey][b.ex] = b.extra;
        }
    }

    // チェック関連
    bool Board::isStalemate(PieceColor color)
    {
        // チェックされていたらステイルメイトではない
        if (isKingInCheck(color)) return false;

        // 自分の駒すべてを調べる
        for (int sy = 0; sy < SIZE; sy++) {
            for (int sx = 0; sx < SIZE; sx++) {

                Piece& p = squares[sy][sx];
                if (p.isEmpty() || p.color != color) continue;

                // 1つでも合法手があれば継続
                if (hasAnyLegalMove(sx, sy)) {
                    return false;
                }
            }
        }

        // チェックされてない & 合法手ゼロ
        return true;
    }
    bool Board::canCastleCheckOnly(int sx, int sy, int dx, int dy)
    {
        Piece& k = squares[sy][sx];
        if (k.type != KING) return false;

        // キングの2マス移動か？
        if (abs(dx - sx) != 2 || dy != sy) return false;

        bool kingSide = (dx > sx);

        // ルール上キャスリング可能か
        if (!canCastle(k.color, kingSide)) return false;

        // 仮想的に動かして王手にならないか
        if (wouldBeInCheckAfterMove(sx, sy, dx, dy, k.color))
            return false;

        return true;
    }
    bool Board::canEnPassantCheckOnly(int sx, int sy, int dx, int dy)
    {
        if (!enPassantAvailable) return false;

        Piece& p = squares[sy][sx];
        if (p.type != PAWN) return false;

        int dir = (p.color == WHITE) ? -1 : 1;

        // アンパッサンの移動先か？
        if (dx != enPassantX || dy != sy + dir)
            return false;

        // 仮想的に動かして王手にならないか
        if (wouldBeInCheckAfterMove(sx, sy, dx, dy, p.color))
            return false;

        return true;
    }
    bool Board::wouldBeInCheckAfterMove(
        int sx, int sy,
        int dx, int dy,
        PieceColor color
    ) {
        MoveBackup backup = simulateMove(sx, sy, dx, dy);

        bool inCheck = isKingInCheck(color);

        undoSimulateMove(sx, sy, dx, dy, backup);

        return inCheck;
    }
    bool Board::isKingInCheck(PieceColor kingColor)
    {
        int kingX = -1;
        int kingY = -1;

        //キングの位置を探す
        bool found = false;
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                Piece& p = squares[y][x];
                if (p.type == KING && p.color == kingColor) {
                    kingX = x;
                    kingY = y;
                    found = true;
                    break;
                }
            }
            if (found)break;
        }

        if (kingX == -1) return false;

        //敵の駒がキングを取れるか？
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                Piece& enemy = squares[y][x];

                if (enemy.isEmpty()) continue;
                if (enemy.color == kingColor) continue;

                bool canAttack = false;

                switch (enemy.type) {
                case PAWN:
                    canAttack = canPawnAttack(x, y, kingX, kingY);
                    break;
                case ROOK:
                    canAttack = canMoveRook(x, y, kingX, kingY);
                    break;
                case BISHOP:
                    canAttack = canMoveBishop(x, y, kingX, kingY);
                    break;
                case QUEEN:
                    canAttack = canMoveQueen(x, y, kingX, kingY);
                    break;
                case KNIGHT:
                    canAttack = canMoveKnight(x, y, kingX, kingY);
                    break;
                case KING:
                    canAttack = abs(x - kingX) <= 1 && abs(y - kingY) <= 1;
                    break;
                }

                if (canAttack) {
                    return true; // チェック！
                }
            }
        }

        return false;
    }
    
    // 勝敗判定
    bool Board::hasAnyLegalMove(int sx, int sy)
    {
        Piece& p = squares[sy][sx];

        for (int dy = 0; dy < SIZE; dy++) {
            for (int dx = 0; dx < SIZE; dx++) {

                // 通常手
                if (canMoveByType(sx, sy, dx, dy) &&
                    !wouldBeInCheckAfterMove(sx, sy, dx, dy, p.color))
                {
                    return true;
                }

                // キャスリング
                if (p.type == KING &&
                    canCastleCheckOnly(sx, sy, dx, dy))
                {
                    return true;
                }

                // アンパッサン
                if (p.type == PAWN &&
                    canEnPassantCheckOnly(sx, sy, dx, dy))
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool Board::isCheckmate(PieceColor color)
    {
        //チェックかどうか
        if (!isKingInCheck(color)) return false;

        //いずれかの駒に合法手があるか
        for (int sy = 0; sy < SIZE; sy++) {
            for (int sx = 0; sx < SIZE; sx++) {

                Piece& p = squares[sy][sx];
                if (p.isEmpty() || p.color != color) continue;

                //その駒の合法手を1つでも試す
                if (hasAnyLegalMove(sx, sy)) {
                    return false; //合法手あり → メイトじゃない
                }
            }
        }

        //チェックメイト
        return true;
    }

    // プロモーション 
    void Board::handlePromotionInput()
    {
        if (!isTrigger(MOUSE_LBUTTON)) return;

        int mx = (int)mouseX;
        int my = (int)mouseY;

        // UI配置（drawPromotionUIと一致させる）
        float x = 1050.0f;
        float y = 200.0f;

        // 各選択肢の当たり判定
        for (int i = 0; i < 4; i++) {

            float tx = x;
            float ty = y + 50 + i * 45;

            // 簡易当たり判定（文字周辺）
            if (mx >= tx - 20 && mx <= tx + 40 &&
                my >= ty - 35 && my <= ty + 5)
            {
                PieceType newType;

                switch (i) {
                case 0: newType = QUEEN;  break;
                case 1: newType = ROOK;   break;
                case 2: newType = BISHOP; break;
                case 3: newType = KNIGHT; break;
                }

                // 駒を昇格
                squares[promotionY][promotionX] =
                    Piece(newType, promotionColor);

                squares[promotionY][promotionX].hasMoved = true;

                resetSelection();

                // 状態解除
                promotionPending = false;

                // ターン交代
                currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;

                // 状態更新
                inCheck = isKingInCheck(currentTurn);
                inCheckmate = isCheckmate(currentTurn);
                inStalemate = isStalemate(currentTurn);

                return;
            }
        }
    }

}