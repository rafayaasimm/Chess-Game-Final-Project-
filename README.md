# ♟ Chess Game in C++
### Object Oriented Programming — Semester Project
**National University of Computer & Emerging Sciences, Faisalabad-Chiniot Campus**

---

## Project Description

This is a fully functional two-player Chess Game built in C++ using Object Oriented Programming principles. The game features a graphical interface built with the SFML library where two players take turns clicking pieces on a visual chess board.

Every chess piece is its own class inheriting from a common base class, demonstrating inheritance and polymorphism. The board is managed by a dedicated Board class showing composition. All piece movement rules are correctly implemented including check, checkmate, stalemate detection, and pawn promotion.

---

## Features

- Full chess board with all 6 piece types — King, Queen, Rook, Bishop, Knight, Pawn
- Click to select a piece — green dots show all legal moves
- Green ring on enemy pieces that can be captured
- Prevents moves that leave your own king in check
- Check detection with red border warning
- Checkmate and stalemate detection with end screen
- Pawn promotion popup — choose Queen, Rook, Bishop, or Knight
- Player names displayed in bottom bar with turn indicator
- Exception handling throughout — missing files or bad input will not crash the game

---

## OOP Concepts Used

| Concept | Where Used |
|---|---|
| Encapsulation | Private data members in all classes, accessed through getters |
| Inheritance | Pawn, Rook, Knight, Bishop, Queen, King all inherit from Piece |
| Polymorphism | isValidMove() is virtual — each piece implements its own movement |
| Composition | Board contains Piece* grid[8][8], Game contains Board and Player |
| Abstraction | Piece is abstract — cannot be instantiated directly |

---

## Project Structure

```
chess_game_rrf/
├── piece.h          ← Abstract base class for all pieces
├── pawn.h/cpp       ← Pawn movement logic
├── rook.h/cpp       ← Rook movement logic
├── knight.h/cpp     ← Knight movement logic
├── bishop.h/cpp     ← Bishop movement logic
├── queen.h/cpp      ← Queen movement logic
├── king.h/cpp       ← King movement logic
├── board.h/cpp      ← 8x8 grid, move execution, check detection
├── game.h/cpp       ← Game loop, turn management, checkmate logic
├── gui.h/cpp        ← SFML window, rendering, mouse click handling
├── main.cpp         ← Entry point
└── pieces/          ← PNG images for all 12 chess pieces
```

---

## Requirements

- Windows OS
- Visual Studio 2019 or 2022
- SFML 2.6 — download from https://www.sfml-dev.org/download.php

---

## SFML Setup (do this once)

1. Download **SFML 2.6** for Visual C++ 64-bit from sfml-dev.org
2. Extract to `C:\SFML`
3. In Visual Studio right click project → **Properties**
4. **C/C++ → General → Additional Include Directories** → add `C:\SFML\include`
5. **Linker → General → Additional Library Directories** → add `C:\SFML\lib`
6. **Linker → Input → Additional Dependencies** → add:
```
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib
```
7. Copy these DLL files from `C:\SFML\bin` to your `x64\Debug\` folder:
```
sfml-graphics-d-2.dll
sfml-window-d-2.dll
sfml-system-d-2.dll
```

---

## How to Run

1. Clone the repository:
```bash
git clone https://github.com/rafayaasimm/Chess-Game-Final-Project-.git
```
2. Open `chess_game_rrf.sln` in Visual Studio
3. Complete SFML setup above
4. Copy the `pieces` folder to your `x64\Debug\` folder
5. Press **F5** to build and run
6. Enter both player names in the console
7. The chess board window will open — click to play

---

## How to Play

| Action | How |
|---|---|
| Select a piece | Left click on it |
| See legal moves | Green dots appear automatically |
| Move a piece | Click the destination square |
| Deselect | Click the same piece again |
| Promote a pawn | Click the piece you want in the popup |

---

## Group Members

| Name | Roll Number |
|---|---|
| Abdul Rafay | 25F-0073 |
| Rameen Ajmal | 25F-0036 |
| Faryal Fatime | 25F-0022 |

---

## GitHub Repository

https://github.com/rafayaasimm/Chess-Game-Final-Project-
