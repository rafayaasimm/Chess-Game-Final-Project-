#pragma once
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

// Board class - poora chess board yahan manage hota hai
class Board {
private:
    // 8x8 grid hai jisme saare pieces store hote hain
    // nullptr matlab square empty hai
    Piece* grid[8][8];

public:
    // Constructor - board banata hai aur sab squares empty karta hai
    Board();

    // Destructor - board destroy hone par saare pieces ki memory free karta hai
    ~Board();

    // Kisi bhi square par jo piece hai usse return karta hai
    // agar square empty ho to nullptr return hoga
    Piece* getPiece(int r, int c) const;

    // Kisi square par piece set karta hai
    void setPiece(int r, int c, Piece* p);

    // Check karta hai ke diya gaya row aur column board ke andar hai ya nahi
    bool isInBounds(int r, int c) const;

    // Game shuru hone par saare pieces apni starting position par rakhta hai
    void setupBoard();

    // Console par board display karta hai - testing ke liye use hota tha
    void displayBoard() const;

    // Ek piece ko ek square se doosre square par move karta hai
    // agar move valid na ho to false return karta hai
    bool movePiece(int fR, int fC, int tR, int tC);

    // Check karta hai ke diye gaye color ka king check mein hai ya nahi
    bool isInCheck(Color color);

    // Board ke saare pieces delete karta hai aur grid ko empty karta hai
    void clearBoard();
};