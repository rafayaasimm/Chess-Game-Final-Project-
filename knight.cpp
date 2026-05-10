#include "Knight.h"
#include "Board.h"

// Knight banana - WHITE ho to N aur BLACK ho to n
Knight::Knight(Color c, int r, int cl): Piece(c, r, cl, c == WHITE ? 'N' : 'n') {
}

// Knight ka symbol return karna
char Knight::getSymbol() const {
    return symbol;
}

// Knight ka name return karna
string Knight::getPieceName() const {
    return "Knight";
}

// check valid move
bool Knight::isValidMove(Board& b, int toRow, int toCol) {

    // rows moved up
    int rowDiff = abs(toRow - row);

    // colums moves left or right
    int colDiff = abs(toCol - col);

    // L shape means 2 steps in one direction and 1 in other
    if ((rowDiff == 2 && colDiff == 1) ||(rowDiff == 1 && colDiff == 2)) {
        return true; // sahi L shape hai
    }

    // L shape nahi bana galat move
    return false;
}