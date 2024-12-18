#include "game.h"
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <chrono>
#include <thread>
#include <ctime>
#include <random>

// start_of_game: Just prints the title
void GAME::start_of_game() {
    std::cout << "\t\t\t\t\tBATTLESHIP\n";
}

void GAME::start_of_gamegrid() {
    std::cout << "\n"  << "\n\n";
    std::cout << " ";
    for (int i = 1; i <= 10; i++) {
        if (i < 10) std::cout << "  " << i;
        else std::cout << " " << i;
    }
    std::cout << "\n";
    for (int r = 0; r < 10; r++) {
        char rowLabel = 'A' + r;
        std::cout << rowLabel << " ";
        for (int c = 0; c < 10; c++) {
            std::cout << "[" << '~' << "]";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
// start_of_gamegrid: Initially just shows empty grids


void GAME::set_up_grids(std::string player, std::string computer) {
    playerName = player;
    cpuName = computer;
    initializeGrids();
    
}

void GAME::ship_placement(std::string player, std::string computer) {
    playerName = player;
    cpuName = computer;
    placePlayerShips();
    placeCPUShips();
    playerShipsRemaining = 5;
    cpuShipsRemaining = 5;

    // After placing ships, move into the game loop
    gameLoop();
}

// PLAYagain: ask user if they want to play again
bool GAME::PLAYagain() {
    std::string again;
    bool checkvalid = false;
    do {
        std::cout << "Play Again? Enter: Yes or No: ";
        std::cin >> again;
        std::transform(again.begin(), again.end(), again.begin(),
            [](unsigned char c) { return std::toupper(c); });
        if (again == "YES" || again == "Y" || again == "YE") {
            return true;
        }
        else if ((again == "NO" || again == "N" || again == "O")) {
            return false;
        }
        else {
            std::cout << "Invalid Input." << std::endl;
            checkvalid = true;
        }
    } while (checkvalid);
   
}



void GAME::initializeGrids() {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            playerGrid[r][c] = '~';
            cpuGrid[r][c] = '~';
            playerView[r][c] = '~';
            cpuView[r][c] = '~';    
        }
    }
}

void GAME::printPlayerGrid() {
    std::cout << "\n" << playerName << "'s Ships\n\n";
    std::cout << " ";
    for (int i = 1; i <= 10; i++) {
        if (i < 10) std::cout << "  " << i;
        else std::cout << " " << i;
    }
    std::cout << "\n";
    for (int r = 0; r < 10; r++) {
        char rowLabel = 'A' + r;
        std::cout << rowLabel << " ";
        for (int c = 0; c < 10; c++) {
            std::cout << "[" << playerGrid[r][c] << "]";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void GAME::printPlayerView() {
    std::cout << "\n" << cpuName << "'s Grid (Your Shots)\n\n";
    std::cout << " ";
    for (int i = 1; i <= 10; i++) {
        if (i < 10) std::cout << "  " << i;
        else std::cout << " " << i;
    }
    std::cout << "\n";
    for (int r = 0; r < 10; r++) {
        char rowLabel = 'A' + r;
        std::cout << rowLabel << " ";
        for (int c = 0; c < 10; c++) {
            std::cout << "[" << playerView[r][c] << "]";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void GAME::placePlayerShips() {
    std::cout << "Time to place your ships, " << playerName << "!\n";
    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            std::cout << "Place your " << ships[i].name << " (size " << ships[i].size << ")\n";
            std::cout << "Enter starting coordinate (e.g. A1): ";
            std::string coord;
            std::cin >> coord;
            // Validate coordinate
            if (coord.size() < 2 || coord.size() > 3) {
                std::cout << "Invalid coordinate format.\n";
                continue;
            }
            coord[0] = toupper(coord[0]);
            int row = coord[0] - 'A';
            int col = 0;
            if (coord.size() == 3) {
                if (!isdigit(coord[1]) || !isdigit(coord[2])) {
                    std::cout << "Invalid coordinate.\n";
                    continue;
                }
                col = (coord[1] - '0') * 10 + (coord[2] - '0') - 1;
            }
            else {
                if (!isdigit(coord[1])) {
                    std::cout << "Invalid coordinate.\n";
                    continue;
                }
                col = (coord[1] - '0') - 1;
            }

            if (row < 0 || row > 9 || col < 0 || col > 9) {
                std::cout << "Out of bounds.\n";
                continue;
            }

            std::cout << "Vertical or Horizontal? (V/H): ";
            char vh;
            std::cin >> vh;
            vh = toupper(vh);
            bool vertical;
            if (vh == 'V') vertical = true;
            else if (vh == 'H') vertical = false;
            else {
                std::cout << "Invalid orientation.\n";
                continue;
            }

            if (canPlaceShip(playerGrid, row, col, ships[i].size, vertical)) {
                setShip(playerGrid, row, col, ships[i].size, vertical);
                placed = true;
                printPlayerGrid();
            }
            else {
                std::cout << "Cannot place ship here. Try again.\n";
            }
        }
    }
    std::cout << "All ships placed!\n\n";
}

void GAME::placeCPUShips() {
    // random CPU placement
    std::srand((unsigned)std::time(nullptr));
    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            int row = std::rand() % 10;
            int col = std::rand() % 10;
            bool vertical = (std::rand() % 2 == 0);
            if (canPlaceShip(cpuGrid, row, col, ships[i].size, vertical)) {
                setShip(cpuGrid, row, col, ships[i].size, vertical);
                placed = true;
            }
        }
    }
}

// Check if we can place a ship of given size starting at (r,c) 
// either vertically or horizontally on given grid
bool GAME::canPlaceShip(char grid[10][10], int r, int c, int size, bool vertical) {
    if (vertical) {
        if (r + size > 10) return false;
        for (int i = 0; i < size; i++) {
            if (grid[r + i][c] != '~') return false;
        }
    }
    else {
        if (c + size > 10) return false;
        for (int i = 0; i < size; i++) {
            if (grid[r][c + i] != '~') return false;
        }
    }
    return true;
}

void GAME::setShip(char grid[10][10], int r, int c, int size, bool vertical) {
    for (int i = 0; i < size; i++) {
        if (vertical) {
            grid[r + i][c] = '#';
        }
        else {
            grid[r][c + i] = '#';
        }
    }
}

// Main game loop
void GAME::gameLoop() {
    bool gameOver = false;
    bool playerSurr = false;
    while (!gameOver) {
        // Player's turn
        playerTurn();
        if (allShipsSunk(cpuGrid)) {
            std::cout << "You have destroyed all of " << cpuName << "'s ships! You win!\n";
            wins++;
            gameOver = true;
            break;
        }
        if (!gameOver && !playerSurr) {
            // CPU turn
            cpuTurn();
            if (allShipsSunk(playerGrid)) {
                std::cout << cpuName << " has destroyed all of your ships! You lose!\n";
                losses++;
                gameOver = true;
            }
        }

        if (playerSurr) {
            std::cout << "You surrendered! " << cpuName << " wins!\n";
            losses++;
            gameOver = true;
        }
    }

    std::cout << "Current record: " << wins << " Wins, " << losses << " Losses.\n";
}

bool GAME::allShipsSunk(char grid[10][10]) {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (grid[r][c] == '#') return false;
        }
    }
    return true;
}

void GAME::playerTurn() {
    char choice = ' ';
    bool done = false;
    while (!done) {
        std::cout << playerName << ", it's your turn.\n";
        std::cout << "Options: (F)ire, (V)iew your ships, (S)urrender: ";
        choice = getUserChoice();
        if (choice == 'F') {
            printPlayerView();
            int row, col;
            getFireCoordinates(row, col);
            if (fireAt(playerView, cpuGrid, row, col)) {
                std::cout << "You hit a ship!\n";
            }
            else {
                std::cout << "You missed!\n";
            }
            done = true;
        }
        else if (choice == 'V') {
            printPlayerGrid();
        }
        else if (choice == 'S') {
            // surrender
            // handled by upper logic
            // We'll just end turn and let game loop handle
            playerShipsRemaining = 0;
            // This effectively ends the game in the loop
            done = true;
            // Surrender logic: immediate game end after this turn
            break;
        }
    }
}

void GAME::cpuTurn() {
    std::cout << cpuName << "'s turn...\n";
    // CPU fires randomly at player, but ensure it doesn't hit same spot twice
    int row, col;
    bool valid = false;
    while (!valid) {
        row = std::rand() % 10;
        col = std::rand() % 10;
        if (cpuView[row][col] == '~' || cpuView[row][col] == '#') {
            valid = true;
        }
    }
    if (fireAt(cpuView, playerGrid, row, col)) {
        std::cout << cpuName << " hit your ship at " << (char)('A' + row) << col + 1 << "!\n";
    }
    else {
        std::cout << cpuName << " missed!\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// fireAt: attempts to fire at [row,col] on targetGrid
// view is what the shooter sees; targetGrid is actual ship positions
// Returns true if hit, false if miss
bool GAME::fireAt(char view[10][10], char targetGrid[10][10], int row, int col) {
    if (targetGrid[row][col] == '#') {
        targetGrid[row][col] = 'H';
        view[row][col] = 'H';
        return true;
    }
    else if (targetGrid[row][col] == '~') {
        targetGrid[row][col] = 'M';
        view[row][col] = 'M';
        return false;
    }
    else {
        // If already hit/miss, just return false (should not happen if validated)
        return false;
    }
}

void GAME::getFireCoordinates(int& row, int& col) {
    bool valid = false;
    while (!valid) {
        std::cout << "Enter coordinates to fire at (e.g. A1): ";
        std::string coord;
        std::cin >> coord;
        if (coord.size() < 2 || coord.size() > 3) {
            std::cout << "Invalid coordinate.\n";
            continue;
        }
        coord[0] = toupper(coord[0]);
        row = coord[0] - 'A';
        if (row < 0 || row >= 10) {
            std::cout << "Invalid row.\n";
            continue;
        }
        if (coord.size() == 3) {
            if (!isdigit(coord[1]) || !isdigit(coord[2])) {
                std::cout << "Invalid coordinate.\n";
                continue;
            }
            col = (coord[1] - '0') * 10 + (coord[2] - '0') - 1;
        }
        else {
            if (!isdigit(coord[1])) {
                std::cout << "Invalid coordinate.\n";
                continue;
            }
            col = (coord[1] - '0') - 1;
        }
        if (col < 0 || col >= 10) {
            std::cout << "Invalid column.\n";
            continue;
        }
        // Check if playerView at that location is already H or M
        if (playerView[row][col] == 'H' || playerView[row][col] == 'M') {
            std::cout << "You already fired at this location.\n";
            continue;
        }
        valid = true;
    }
}

char GAME::getUserChoice() {
    char ch;
    std::cin >> ch;
  
    ch = toupper(ch);
    while (ch != 'F' && ch != 'V' && ch != 'S') {
        std::cout << "Invalid choice. Enter F (Fire), V (View), or S (Surrender): ";
        std::cin >> ch;
        ch = toupper(ch);
    }
    return ch;
}

