#pragma once
#include "Piece.h"

namespace GAME08
{
    class Board {
    public:
        //盤面とターン管理
        static const int SIZE = 8;
        Piece squares[SIZE][SIZE];
        PieceColor currentTurn;

        //選択状態
        int selectedX;
        int selectedY;
        bool hasSelection() const;


        Board();

        void update();

        //描画系
        void draw();
        void drawBoard();
        void drawMoveHint();
        void drawPieces();

        //マウスからマス変換
        bool isInsideBoard(int mx, int my, int& bx, int& by);

        bool isInside(int x, int y)const;
        bool isEmpty(int x, int y) const;
        bool isEnemy(int x, int y, PieceColor myColor) const;

        //移動ヒント用配列
        bool moveHint[Board::SIZE][Board::SIZE];
        bool doubleStepHint[Board::SIZE][Board::SIZE];
        void clearMoveHint();

        //斜め移動用のロジック
        bool canMoveDiagonal(int sx, int sy, int dx, int dy);

        //直線移動用のロジック
        bool canMoveStraight(int sx, int sy, int dx, int dy);

        //ポーン専用のロジック
        void calcPawnMoveHint(int x, int y);
        bool canMovePawn(int sx, int sy, int dx, int dy);

        //ルーク専用のロジック
        void calcRookMoveHint(int x, int y);
        bool canMoveRook(int sx, int sy, int dx, int dy);

        //ビショップ専用のロジック
        void calcBishopMoveHint(int x, int y);
        bool canMoveBishop(int sx, int sy, int dx, int dy);

        //クイーン専用のロジック
        void calcQueenMoveHint(int x, int y);
        bool canMoveQueen(int sx, int sy, int dx, int dy);

        //ナイト専用のロジック
        void calcKnightMoveHint(int x, int y);
        bool canMoveKnight(int sx, int sy, int dx, int dy);

        //キング専用のロジック
        void calcKingMoveHint(int x, int y);
        bool canMoveKing(int sx, int sy, int dx, int dy);


        void movePiece(int sx, int sy, int dx, int dy);
    };
}