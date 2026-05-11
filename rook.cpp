#include "rook.h"
#include "board.h"

Rook::Rook(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'R' : 'r') {}

char Rook::getSymbol() const { return symbol; }
string Rook::getPieceName() const { return "Rook"; }

bool Rook::isValidMove(Board& b, int toRow, int toCol) {
    // Must move in a straight line, and must actually move
    if (row != toRow && col != toCol) return false;
    if (row == toRow && col == toCol) return false;

    int rowStep = 0, colStep = 0;
    if (toRow > row) rowStep = 1;
    else if (toRow < row) rowStep = -1;
    if (toCol > col) colStep = 1;
    else if (toCol < col) colStep = -1;

    // Check every square between source and destination (exclusive)
    int r = row + rowStep, c = col + colStep;
    while (r != toRow || c != toCol) {
        if (b.getPiece(r, c) != nullptr) return false; // path is blocked
        r += rowStep;
        c += colStep;
    }

    // Cannot capture own piece
    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color) return false;
    return true;
}