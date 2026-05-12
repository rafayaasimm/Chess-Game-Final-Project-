#include "knight.h"
#include "board.h"

// Constructor - Knight object banata hai
// WHITE ho to symbol 'N' aur BLACK ho to symbol 'n' set hota hai
// N isliye use karte hain kyunke K already King ke liye hai
Knight::Knight(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'N' : 'n') {}

// Knight ka symbol return karta hai
char Knight::getSymbol() const { return symbol; }

// Knight ka naam return karta hai
string Knight::getPieceName() const { return "Knight"; }

// Check karta hai ke Knight ka move valid hai ya nahi
bool Knight::isValidMove(Board& b, int toRow, int toCol) {

    // Kitne squares upar ya neeche ja raha hai
    int rowDiff = abs(toRow - row);

    // Kitne squares left ya right ja raha hai
    int colDiff = abs(toCol - col);

    // Knight sirf L shape mein move karta hai
    // ya to 2 rows aur 1 column - ya 1 row aur 2 columns
    // Knight akela aisa piece hai jo doosre pieces ke upar se jump kar sakta hai
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
        return false;

    // Destination square par jo piece hai usse check karo
    Piece* target = b.getPiece(toRow, toCol);

    // Apni hi color ki piece par nahi ja sakta
    if (target != nullptr && target->getColor() == color) return false;

    // Saari conditions pass - valid move hai
    return true;
}