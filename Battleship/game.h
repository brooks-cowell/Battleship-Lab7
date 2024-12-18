#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

class GAME {
public:
    void start_of_game();
    void start_of_gamegrid();
    void set_up_grids(std::string num1, std::string num2);
    void ship_placement(std::string player, std::string computer);
    bool PLAYagain();

private:
    // Grids: [row][col]
    // playerGrid: player's ships
    // cpuGrid: computer's ships
    // playerView: what player sees of CPU's grid (~ and hits/misses)
    // cpuView: what CPU sees of player's grid (~ and hits/misses)
    char playerGrid[10][10];
    char cpuGrid[10][10];
    char playerView[10][10]; // CPU grid from player's perspective
    char cpuView[10][10];    // Player grid from CPU's perspective

    // Ship sizes
    const int CARRIER_SIZE = 5;
    const int BATTLESHIP_SIZE = 4;
    const int CRUISER_SIZE = 3;
    const int SUBMARINE_SIZE = 3;
    const int DESTROYER_SIZE = 2;

    // Ships arrays
    // We'll always place one of each for both player and CPU
    struct Ship {
        std::string name;
        int size;
    } 
    ships[5] = {
        {"Carrier", CARRIER_SIZE},
        {"Battleship", BATTLESHIP_SIZE},
        {"Cruiser", CRUISER_SIZE},
        {"Submarine", SUBMARINE_SIZE},
        {"Destroyer", DESTROYER_SIZE}
    };

    int playerShipsRemaining;
    int cpuShipsRemaining;

    int wins = 0;
    int losses = 0;

    std::string playerName;
    std::string cpuName;

    // Private helper methods
    void initializeGrids();
   
    void printPlayerGrid();
    void printPlayerView();
    void placePlayerShips();
    void placeCPUShips();
    
    bool canPlaceShip(char grid[10][10], int r, int c, int size, bool vertical);
    void setShip(char grid[10][10], int r, int c, int size, bool vertical);

    void playerTurn();
    void cpuTurn();
    bool fireAt(char view[10][10], char targetGrid[10][10], int row, int col);
    bool allShipsSunk(char grid[10][10]);
    void gameLoop();

    // Input helpers
    void getFireCoordinates(int& row, int& col);
    char getUserChoice();
};

#endif //GAME_H

