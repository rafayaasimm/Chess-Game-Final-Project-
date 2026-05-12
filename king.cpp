#include "king.h"
#include "board.h"

// Constructor - King object banata hai
// WHITE ho to symbol 'K' aur BLACK ho to symbol 'k' set hota hai
King::King(Color c, int r, int cl) : Piece(c, r, cl, c == WHITE ? 'K' : 'k') {}

// King ka symbol return karta hai
char King::getSymbol() const { return symbol; }

// King ka naam return karta hai
string King::getPieceName() const { return "King"; }

// Check karta hai ke King ka move valid hai ya nahi
bool King::isValidMove(Board& b, int toRow, int toCol) {

    // Kitne squares upar ya neeche ja raha hai
    int rowDiff = abs(toRow - row);

    // Kitne squares left ya right ja raha hai
    int colDiff = abs(toCol - col);

    // King sirf 1 square kisi bhi direction mein ja sakta hai
    // agar 1 se zyada squares ka farq hai to invalid move hai
    if (rowDiff > 1 || colDiff > 1) return false;

    // Same square par nahi ja sakta - koi movement hi nahi hui
    if (rowDiff == 0 && colDiff == 0) return false;

    // Destination square par jo piece hai usse check karo
    Piece* target = b.getPiece(toRow, toCol);

    // Apni hi color ki piece par nahi ja sakta
    if (target != nullptr && target->getColor() == color) return false;

    // Saari conditions pass - valid move hai
    return true;
}