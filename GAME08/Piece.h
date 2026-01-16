#pragma once
#include "../../libOne/inc/libOne.h"

namespace GAME08
{
    enum PieceType {
        NONE = 0,
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };

    enum PieceColor {
        WHITE = 0,
        BLACK,
        NONE_COLOR
    };

    class Piece {
    public:
        PieceType type;
        PieceColor color;

        // 空マス用コンストラクタ
        Piece() : type(NONE), color(NONE_COLOR) {}

        // 通常駒用
        Piece(PieceType t, PieceColor c)
            : type(t), color(c) {}

        bool isEmpty() const {
            return type == NONE;
        }

        char getChar() const {
            switch (type) {
            case PAWN:   return 'P';
            case ROOK:   return 'R';
            case KNIGHT: return 'N';
            case BISHOP: return 'B';
            case QUEEN:  return 'Q';
            case KING:   return 'K';
            default:     return ' ';
            }
        }
    };
}
