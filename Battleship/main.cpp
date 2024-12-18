/* 
Brooks D Cowell
Computer Science Fall 2024
Due: December 17 2024
Lab 7, Battleship
Battleship game
*/

#include "Players.h"
#include "game.h"
#include <iostream>
#include <string>
#include <array>
#include <ctime>
#include <cstdlib>

int main() {
    GAME game_frame; //Class: GAME ; Object game_frame
    PLAYERS player;  //Class: PLAYERS ; Object player
    bool play_again; //Declaring do_while loop control variable

    do {
        game_frame.start_of_game(); //"BATTLESHIP"
        std::string livePlayer = player.player_name(); //Defining name of player
        game_frame.start_of_gamegrid(); //Showing a single grid
        std::string cpu_player = player.cpu_name();    //Random Computer name
       
        game_frame.set_up_grids(livePlayer, cpu_player); //Setting grids
       
        game_frame.ship_placement(livePlayer, cpu_player);

        play_again = game_frame.PLAYagain();
    } while (play_again);

    return 0;
}


