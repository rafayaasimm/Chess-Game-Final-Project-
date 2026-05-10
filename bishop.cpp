#include "bishop.h"
#include "board.h"

Bishop::Bishop(Color c, int r, int cl)
    : Piece(c, r, cl, c == WHITE ? 'B' : 'b') {}

char Bishop::getSymbol() const { return symbol; }
string Bishop::getPieceName() const { return "Bishop"; }

bool Bishop::isValidMove(Board& b, int toRow, int toCol) 
{
    int rowDiff = abs(toRow - row);
    int colDiff = abs(toCol - col);

    if (rowDiff != colDiff || rowDiff == 0) return false;

    int rowStep = (toRow > row) ? 1 : -1;
    int colStep = (toCol > col) ? 1 : -1;

    int r = row + rowStep, c = col + colStep;
    while (r != toRow || c != toCol) 
    {
        if (b.getPiece(r, c) != nullptr) return false;
        r += rowStep; c += colStep;
    }

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color) return false;

    return true;
}