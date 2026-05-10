#pragma once
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

class Board {
private:
    Piece* grid[8][8];

public:
    Board();
    ~Board();

    Piece* getPiece(int r, int c) const;
    void setPiece(int r, int c, Piece* p);
    bool isInBounds(int r, int c) const;
    void setupBoard();
    void displayBoard() const;
    bool movePiece(int fR, int fC, int tR, int tC);
    bool isInCheck(Color color);
    void clearBoard();
};