#include "board.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor - board banata hai aur saare squares empty karta hai
Board::Board()
{
    // Shuru mein grid ki har cell nullptr set karo - koi piece nahi
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            grid[r][c] = nullptr;
}

// Destructor - board destroy hone par saari pieces ki memory free karta hai
Board::~Board()
{
    clearBoard();
}

// Saare pieces delete karta hai aur grid ko dobara empty karta hai
void Board::clearBoard()
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
        {
            // Piece ki memory free karo
            delete grid[r][c];
            // Square ko nullptr set karo taake dangling pointer na rahe
            grid[r][c] = nullptr;
        }
}

// Diye gaye square par jo piece hai usse return karta hai
// agar square empty ho to nullptr return hoga
Piece* Board::getPiece(int r, int c) const {
    try {
        // Check karo ke position board ke andar hai
        if (!isInBounds(r, c))
            throw out_of_range("getPiece: position board se bahar hai! row="
                + to_string(r) + " col=" + to_string(c));

        return grid[r][c];
    }
    catch (const out_of_range& e) {
        // Invalid position - error print karo aur nullptr return karo
        cout << "Board access error: " << e.what() << "\n";
        return nullptr;
    }
}

// Diye gaye square par piece set karta hai
void Board::setPiece(int r, int c, Piece* p) {
    try {
        // Check karo ke position board ke andar hai
        if (!isInBounds(r, c))
            throw out_of_range("setPiece: position board se bahar hai! row="
                + to_string(r) + " col=" + to_string(c));

        grid[r][c] = p;
    }
    catch (const out_of_range& e) {
        // Invalid position - error print karo piece set nahi hogi
        cout << "Board set error: " << e.what() << "\n";
    }
}

// Check karta hai ke diya gaya row aur column board ke andar hai ya nahi
bool Board::isInBounds(int r, int c) const {
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}

// Game shuru hone par saare pieces apni starting position par rakhta hai
void Board::setupBoard() {
    try {
        // Pehle board saaf karo agar pehle se kuch tha
        clearBoard();

        // BLACK pieces row 0 par - upar wali row
        grid[0][0] = new Rook(BLACK, 0, 0);
        grid[0][1] = new Knight(BLACK, 0, 1);
        grid[0][2] = new Bishop(BLACK, 0, 2);
        grid[0][3] = new Queen(BLACK, 0, 3);
        grid[0][4] = new King(BLACK, 0, 4);
        grid[0][5] = new Bishop(BLACK, 0, 5);
        grid[0][6] = new Knight(BLACK, 0, 6);
        grid[0][7] = new Rook(BLACK, 0, 7);

        // BLACK pawns row 1 par
        for (int c = 0; c < 8; c++)
            grid[1][c] = new Pawn(BLACK, 1, c);

        // WHITE pawns row 6 par
        for (int c = 0; c < 8; c++)
            grid[6][c] = new Pawn(WHITE, 6, c);

        // WHITE pieces row 7 par - neeche wali row
        grid[7][0] = new Rook(WHITE, 7, 0);
        grid[7][1] = new Knight(WHITE, 7, 1);
        grid[7][2] = new Bishop(WHITE, 7, 2);
        grid[7][3] = new Queen(WHITE, 7, 3);
        grid[7][4] = new King(WHITE, 7, 4);
        grid[7][5] = new Bishop(WHITE, 7, 5);
        grid[7][6] = new Knight(WHITE, 7, 6);
        grid[7][7] = new Rook(WHITE, 7, 7);
    }
    catch (const bad_alloc& e) {
        // Memory alloc fail ho gayi - board setup nahi ho saka
        cout << "Board setup mein memory error: " << e.what() << "\n";
        cout << "Game band ho rahi hai.\n";
        clearBoard();
        throw; // Upar tak error pohnchao taake game band ho sake
    }
    catch (...) {
        // Koi aur masla aaya - board saaf karo
        cout << "Board setup mein unknown error!\n";
        clearBoard();
        throw;
    }
}

// Console par board print karta hai - testing ke liye use hota tha
void Board::displayBoard() const {
    try {
        cout << "\n    a  b  c  d  e  f  g  h" << endl;
        cout << "  ---------------------------" << endl;
        for (int r = 0; r < 8; r++) {
            cout << (8 - r) << " | ";
            for (int c = 0; c < 8; c++) {
                // Agar square empty hai to dot print karo
                if (grid[r][c] == nullptr)
                    cout << ".  ";
                // Warna piece ka symbol print karo
                else
                    cout << grid[r][c]->getSymbol() << "  ";
            }
            cout << "| " << (8 - r) << endl;
        }
        cout << "  ---------------------------" << endl;
        cout << "    a  b  c  d  e  f  g  h" << endl;
    }
    catch (...) {
        // Display mein masla - game chalti rahegi
        cout << "Board display mein error aaya.\n";
    }
}

// Piece ko ek square se doosre par move karta hai
// agar move valid na ho to false return karta hai
bool Board::movePiece(int fR, int fC, int tR, int tC) {
    try {
        // Check karo ke dono squares board ke andar hain
        if (!isInBounds(fR, fC) || !isInBounds(tR, tC))
            throw out_of_range("movePiece: position board se bahar hai!");

        // Source square par piece lao
        Piece* p = grid[fR][fC];

        // Agar source square empty hai to move nahi ho sakta
        if (p == nullptr) return false;

        // Piece ki apni movement rules se check karo move valid hai ya nahi
        if (!p->isValidMove(*this, tR, tC)) return false;

        // Destination par jo piece hai usse save karo - undo ke liye
        Piece* captured = grid[tR][tC];

        // Temporarily move karo - test karne ke liye ke king check mein to nahi aaya
        grid[tR][tC] = p;
        grid[fR][fC] = nullptr;
        p->setPosition(tR, tC);

        // Agar apna king check mein aa gaya to move wapas undo karo
        if (isInCheck(p->getColor())) {
            p->setPosition(fR, fC);
            grid[fR][fC] = p;
            grid[tR][tC] = captured;
            return false;
        }

        // Move valid hai - captured piece ki memory free karo
        delete captured;

        // Agar piece pawn tha to uska hasMoved true karo
        // taake agle baar 2 square wala option band ho jaye
        Pawn* pawn = dynamic_cast<Pawn*>(p);
        if (pawn != nullptr) pawn->setMoved();

        return true;
    }
    catch (const out_of_range& e) {
        // Invalid position - move reject karo
        cout << "Move error: " << e.what() << "\n";
        return false;
    }
    catch (...) {
        // Koi aur masla - safely false return karo
        cout << "movePiece mein unknown error!\n";
        return false;
    }
}

// Check karta hai ke diye gaye color ka king check mein hai ya nahi
bool Board::isInCheck(Color color) {
    try {
        int kingRow = -1, kingCol = -1;

        // Pehle apna king dhundo board par
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                if (grid[r][c] && grid[r][c]->getColor() == color
                    && grid[r][c]->getPieceName() == "King") {
                    kingRow = r; kingCol = c;
                }

        // Agar king nahi mila to check nahi hai
        if (kingRow == -1) return false;

        // Ab saare enemy pieces check karo ke koi king par attack kar sakta hai ya nahi
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                if (grid[r][c] && grid[r][c]->getColor() != color)
                    if (grid[r][c]->isValidMove(*this, kingRow, kingCol))
                        return true; // Koi enemy piece king ko attack kar sakta hai - check hai

        // Koi bhi enemy piece king ko attack nahi kar sakta - check nahi hai
        return false;
    }
    catch (...) {
        // Check calculation mein masla - safe side par false return karo
        cout << "isInCheck mein error aaya.\n";
        return false;
    }
}