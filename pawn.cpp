#include "pawn.h"
#include "board.h"

// Pawn created WHITE ho to P aur BLACK ho to p
Pawn::Pawn(Color c, int r, int cl): Piece(c, r, cl, c == WHITE ? 'P' : 'p') {
    hasMoved = false; // abhi nahi chala
}

// Pawn ka symbol return 
char Pawn::getSymbol() const {
    return symbol;
}

// Pawn ka name return 
string Pawn::getPieceName() const {
    return "Pawn";
}

// check move valid hai
bool Pawn::isValidMove(Board& b, int toRow, int toCol) {

    // WHITE upar jata hai isliye -1
    // BLACK neeche jata hai isliye +1
    int direction = (color == WHITE) ? -1 : 1;

    // kitni rows aur colums move hua
    int rowDiff = toRow - row;
    int colDiff = toCol - col;

    // sirf ek step aage chal sakta hai
    if (colDiff == 0 && rowDiff == direction) {
        return true;
    }

    // wrong move
    return false;
}