#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include "game.h"
using namespace std;

// GUI class - SFML use karke chess board screen par dikhata hai
class GUI {
private:
    // SFML window jisme game render hoti hai
    sf::RenderWindow window;

    // Font jo player names aur messages dikhane ke liye use hoti hai
    sf::Font font;

    // Board ka reference - GUI yahan se pieces ki information leta hai
    Board& board;

    // Har square ka size pixels mein - 80x80 pixels per square
    static const int TILE = 80;

    // 12 pieces ki textures - images memory mein store hoti hain
    sf::Texture textures[12];

    // 12 pieces ke sprites - texture se image screen par draw karta hai
    sf::Sprite sprites[12];

    // Har index par konsa piece symbol hai yeh store karta hai
    // jaise 'K','Q','R','B','N','P','k','q','r','b','n','p'
    char symMap[12];

    // Light square ka color - cream/beige rang
    sf::Color lightSq = sf::Color(240, 217, 181);

    // Dark square ka color - brown rang
    sf::Color darkSq = sf::Color(181, 136, 99);

    // Selected piece ke square ka color - dark green
    sf::Color hlGreen = sf::Color(20, 85, 30, 180);

    // Abhi konsa square select hua hai uska row aur column
    // -1 matlab kuch select nahi
    int selRow = -1, selCol = -1;

    // True matlab koi piece select ho chuki hai
    bool pieceSelected = false;

    // Abhi kiski baari hai - WHITE ya BLACK
    Color currentTurn = WHITE;

    // 8x8 array - true matlab us square par ja sakte hain
    // yeh green dots dikhane ke liye use hota hai
    bool legalMoves[8][8];

    // True matlab pawn last row par pahuncha hai aur promotion choose karni hai
    bool promoWaiting = false;

    // Woh square jahan promotion honi hai
    int promoRow = -1, promoCol = -1;

    // Promote hone wale pawn ka color
    Color promoColor = WHITE;

    // Dono players ke naam - bottom bar mein dikhte hain
    string player1Name;
    string player2Name;

    // Saari 12 piece images load karta hai
    void loadSprites();

    // Symbol se us piece ka index dhundta hai symMap mein
    int getIndex(char sym);

    // 64 squares draw karta hai aur bottom info bar bhi
    void drawBoard();

    // Selected piece par green highlight aur legal moves par dots draw karta hai
    void drawHighlightsAndDots();

    // Saari pieces apni position par draw karta hai
    void drawPieces();

    // Promotion popup dikhata hai jab pawn last row par pahunche
    void drawPromotionPanel();

    // Diye gaye square se piece ke saare valid moves calculate karta hai
    void computeLegalMoves(int row, int col);

    // legalMoves array ko saaf karta hai - sab false kar deta hai
    void clearLegalMoves();

    // Mouse click handle karta hai - piece select ya move karna
    void handleClick(int mx, int my, Game& game);

    // Promotion popup par click handle karta hai
    void handlePromoClick(int mx, int my);

    // Har move ke baad check karta hai checkmate ya stalemate hua ya nahi
    void checkEndConditions(Color opponent, Game& game, string moverName);

    // Game khatam hone par bada message screen par dikhata hai
    void drawEndScreen(string line1, string line2, sf::Color col);

public:
    // Constructor - board reference aur dono players ke naam leta hai
    GUI(Board& b, string p1, string p2);

    // Main game loop - events handle karta hai aur har frame board draw karta hai
    void run(Game& game);
};