/**
 * 	@file       main.cpp
 * 	@author     Terry Thibault (tlt@cise.ufl.edu)
 * 	@date       3/22/16
 * 	@version    1.0
 *
 * 	@brief      COP3503 Project, Texas Hold'em
 *
 * 	@section DESCRIPTION
 *
 * 	This project is authored by:
 * 		Diego Amador
 * 		Tim Mai
 * 		Cameron Mockabee
 * 		Alexander Rumak
 * 		Terry Thibault
 * 		Hugh Wu
 *
 */

#include <iostream>
#include "header.h"
#include "Player.cpp"

using namespace std;

// Function declarations
int intro_menu();
void start_game(int num_players);
void end_game();


// MAIN
int main(int argc, char*argv[]){
		
    // The "start game" function calls "intro menu" to find out how many players there are
    intro_menu();
    start_game();
    
}






// Functions
void intro_menu(){
    
    cout << "** Welcome to Poker **" << endl;
    
    cout << "There are 8 players at the table. The game will begin!" << endl;

    cout << "******************************" << endl;
}


void start_game(int num_players){
    //need to create vector of players
    Table * table = new Table;
    table.game();
    
    
    
    /*
     --The table is a vector/arrary of player + computers
     --8(?) total players
     --Each player has an array of 2 card objects
     --Table also has an array of 5 cards (starts with 3, 
       then after each round 1 more is added)
     */
  
    
    
    
}