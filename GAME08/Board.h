#pragma once
#include "Piece.h"

namespace GAME08
{
    class Board {
    public:
        // 定数・基本状態
        static const int SIZE = 8;

        Board();

        // メインループ
        void update();
        void draw();

        // 入力・選択
        bool hasSelection() const;
        bool isInsideBoard(int mx, int my, int& bx, int& by);

        // 描画系
        void drawBoard();
        void drawPieces();
        void drawMoveHint();

        // UI系
        void drawUI();
        void drawStatusText();
        void drawCheckKingHighlight();
        void drawPromotionUI();

        // 状態表示用
        bool inCheck;
        bool inCheckmate;
        bool inStalemate;

        // プロモーション状態
        bool promotionPending;
        int promotionX;
        int promotionY;
        PieceColor promotionColor;

    private:

        // 盤面
        Piece squares[SIZE][SIZE];
        PieceColor currentTurn;

        // 選択状態
        int selectedX = -1;
        int selectedY = -1;

        // ヒント管理
        bool moveHint[SIZE][SIZE];        // 通常移動
        bool doubleStepHint[SIZE][SIZE];  // ポーン2歩
        bool specialMoveHint[SIZE][SIZE]; // キャスリング・アンパッサン

        void clearMoveHint();

        void resetSelection();

        // 特殊ルール用状態
        int enPassantX = 0;
        int enPassantY = 0;
        bool enPassantAvailable;

        // 共通ユーティリティ
        bool isInside(int x, int y) const;
        bool isEmpty(int x, int y) const;
        bool isEnemy(int x, int y, PieceColor myColor) const;

        // 共通移動ロジック
        bool canMoveStraight(int sx, int sy, int dx, int dy);
        bool canMoveDiagonal(int sx, int sy, int dx, int dy);

        // ポーン
        void calcPawnMoveHint(int x, int y);
        bool canMovePawn(int sx, int sy, int dx, int dy);
        bool canPawnAttack(int sx, int sy, int tx, int ty);
        bool executeEnPassant(int sx, int sy, int dx, int dy);
        void calcEnPassantHint(int x, int y);

        // ルーク
        void calcRookMoveHint(int x, int y);
        bool canMoveRook(int sx, int sy, int dx, int dy);

        // ビショップ
        void calcBishopMoveHint(int x, int y);
        bool canMoveBishop(int sx, int sy, int dx, int dy);

        // クイーン
        void calcQueenMoveHint(int x, int y);
        bool canMoveQueen(int sx, int sy, int dx, int dy);

        // ナイト
        void calcKnightMoveHint(int x, int y);
        bool canMoveKnight(int sx, int sy, int dx, int dy);

        // キング
        void calcKingMoveHint(int x, int y);
        bool canMoveKing(int sx, int sy, int dx, int dy);

        bool executeCastle(int sx, int sy, int dx, int dy);
        void moveKing(int sx, int sy, int dx, int dy);

        bool canCastleKingSide(PieceColor color);
        bool canCastleQueenSide(PieceColor color);
        bool canCastle(PieceColor color, bool kingSide);
        void calcCastlingHint(int x, int y);

        // 移動・ルール判定
        void movePiece(int sx, int sy, int dx, int dy);

        struct MoveBackup;

        MoveBackup simulateMove(int sx, int sy, int dx, int dy);
        void undoSimulateMove(int sx, int sy, int dx, int dy, const MoveBackup& b);


        // チェック関連
        bool isStalemate(PieceColor color);

        bool canCastleCheckOnly(int sx, int sy, int dx, int dy);

        bool canEnPassantCheckOnly(int sx, int sy, int dx, int dy);

        bool wouldBeInCheckAfterMove(
            int sx, int sy,
            int dx, int dy,
            PieceColor myColor
        );
        bool isKingInCheck(PieceColor kingColor);

        bool canMoveByType(int sx, int sy, int dx, int dy);

        bool hasAnyLegalMove(int sx, int sy);

        bool isCheckmate(PieceColor color);
        
        // プロモーション
        void handlePromotionInput();
    };
}
