#include "board.h"
#include <iostream>
using namespace std;

Board::Board() 
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            grid[r][c] = nullptr;
}

Board::~Board() 
{
    clearBoard();
}

void Board::clearBoard() 
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) 
        {
            delete grid[r][c];
            grid[r][c] = nullptr;
        }
}

Piece* Board::getPiece(int r, int c) const {
    return grid[r][c];
}

void Board::setPiece(int r, int c, Piece* p) {
    grid[r][c] = p;
}

bool Board::isInBounds(int r, int c) const {
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}

void Board::setupBoard() {
    clearBoard();

    grid[0][0] = new Rook(BLACK, 0, 0);
    grid[0][1] = new Knight(BLACK, 0, 1);
    grid[0][2] = new Bishop(BLACK, 0, 2);
    grid[0][3] = new Queen(BLACK, 0, 3);
    grid[0][4] = new King(BLACK, 0, 4);
    grid[0][5] = new Bishop(BLACK, 0, 5);
    grid[0][6] = new Knight(BLACK, 0, 6);
    grid[0][7] = new Rook(BLACK, 0, 7);

    for (int c = 0; c < 8; c++)
        grid[1][c] = new Pawn(BLACK, 1, c);

    for (int c = 0; c < 8; c++)
        grid[6][c] = new Pawn(WHITE, 6, c);

    grid[7][0] = new Rook(WHITE, 7, 0);
    grid[7][1] = new Knight(WHITE, 7, 1);
    grid[7][2] = new Bishop(WHITE, 7, 2);
    grid[7][3] = new Queen(WHITE, 7, 3);
    grid[7][4] = new King(WHITE, 7, 4);
    grid[7][5] = new Bishop(WHITE, 7, 5);
    grid[7][6] = new Knight(WHITE, 7, 6);
    grid[7][7] = new Rook(WHITE, 7, 7);
}

void Board::displayBoard() const {
    cout << "\n    a  b  c  d  e  f  g  h" << endl;
    cout << "  +------------------------+" << endl;
    for (int r = 0; r < 8; r++) {
        cout << (8 - r) << " | ";
        for (int c = 0; c < 8; c++) {
            if (grid[r][c] == nullptr)
                cout << ".  ";
            else
                cout << grid[r][c]->getSymbol() << "  ";
        }
        cout << "| " << (8 - r) << endl;
    }
    cout << "  +------------------------+" << endl;
    cout << "    a  b  c  d  e  f  g  h" << endl;
}

bool Board::movePiece(int fR, int fC, int tR, int tC) {
    if (!isInBounds(fR, fC) || !isInBounds(tR, tC)) return false;

    Piece* p = grid[fR][fC];
    if (p == nullptr) return false;
    if (!p->isValidMove(*this, tR, tC)) return false;

    delete grid[tR][tC];
    grid[tR][tC] = p;
    grid[fR][fC] = nullptr;
    p->setPosition(tR, tC);

    return true;
}

bool Board::isInCheck(Color color) {
    int kingRow = -1, kingCol = -1;

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (grid[r][c] && grid[r][c]->getColor() == color
                && grid[r][c]->getPieceName() == "King") {
                kingRow = r; kingCol = c;
            }

    if (kingRow == -1) return false;

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (grid[r][c] && grid[r][c]->getColor() != color)
                if (grid[r][c]->isValidMove(*this, kingRow, kingCol))
                    return true;

    return false;
}