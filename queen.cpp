#include "queen.h"
#include "board.h"

Queen::Queen(Color c, int r, int cl)
    : Piece(c, r, cl, c == WHITE ? 'Q' : 'q') {}

char Queen::getSymbol() const { return symbol; }
string Queen::getPieceName() const { return "Queen"; }

bool Queen::isValidMove(Board& b, int toRow, int toCol) {
    int rowDiff = abs(toRow - row);
    int colDiff = abs(toCol - col);

    bool straight = (row == toRow || col == toCol);
    bool diagonal = (rowDiff == colDiff && rowDiff != 0);

    if (!straight && !diagonal) return false;

    int rowStep = 0, colStep = 0;
    if (toRow > row) rowStep = 1;
    else if (toRow < row) rowStep = -1;
    if (toCol > col) colStep = 1;
    else if (toCol < col) colStep = -1;

    int r = row + rowStep, c = col + colStep;
    while (r != toRow || c != toCol) {
        if (b.getPiece(r, c) != nullptr) return false;
        r += rowStep; c += colStep;
    }

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color) return false;

    return true;
}