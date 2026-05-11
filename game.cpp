#include "game.h"


Player::Player(string n, Color c): name(n), color(c) {}
 
string Player::getName()  const
 {
     return name;
     }
Color  Player::getColor() const 
{
     return color; 
    }
 


//  GAME Implementations

void Game::switchTurn()
{
    currentTurn = 1 - currentTurn;
}
 
bool Game::parseInput(string in, int& r, int& c) {
    if (in.length() != 2) 
    {
        return false;
    }
    c = in[0] - 'a';        
    r = 8 - (in[1] - '0'); 
    return (r >= 0 && r < 8 && c >= 0 && c < 8);
}
 
Game::Game(string p1Name, string p2Name): players{{p1Name, WHITE}, {p2Name, BLACK}}, currentTurn(0)
{
    board.setupBoard();
}

bool Game::isCheckmate(Color color)
 {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) 
    {
            Piece* p = board.getPiece(r, c);
            if (p == nullptr || p->getColor() != color) 
            {
                continue;
            }
            for (int tr = 0; tr < 8; tr++)
                for (int tc = 0; tc < 8; tc++)
                    if (p->isValidMove(board, tr, tc))     
                    {
                        return false;  
                    }
        }
    return true;
}
 
void Game::start()
{
    board.displayBoard();
    while (true) 
    {
        Player& current = players[currentTurn];
        cout << "\n" << current.getName()
             << " (" << (current.getColor() == WHITE ? "WHITE" : "BLACK")
             << ") -- Enter move (e.g. e2 e4): ";
        string from, to;
        cin >> from >> to;
        int fR, fC, tR, tC;
        if (!parseInput(from, fR, fC) || !parseInput(to, tR, tC))
         {
            cout << "Invalid input format. Use letter+number like e2." << endl;
            continue;
        }
        Piece* p = board.getPiece(fR, fC);
        if (p == nullptr) 
        {
            cout << "No piece at " << from << "." << endl;
            continue;
        }
        if (p->getColor() != current.getColor()) 
        {
            cout << "That is not your piece!" << endl;
            continue;
        }
        if (!board.movePiece(fR, fC, tR, tC))
       { 
            cout << "Invalid move. Try again." << endl;
            continue;
        }
 
        board.displayBoard();
        Color opponent = (current.getColor() == WHITE) ? BLACK : WHITE;
        if (board.isInCheck(opponent))
         {
            if (isCheckmate(opponent))
             {
                cout << "\nCHECKMATE! " << current.getName() << " WINS!" << endl;
                break;
            }
            cout << "CHECK!" << endl;
        }
        switchTurn();
    }
}    
