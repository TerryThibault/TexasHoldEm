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

using namespace std;

// Function declarations
int intro_menu();
void start_game(int num_players);
void end_game();


// MAIN
int main(int argc, char*argv[]){
		
    // The "start game" function calls "intro menu" to find out how many players there are
    start_game(intro_menu());
    
    
    
}






// Functions
int intro_menu(){
    int num_players;
    
    // User inputs number of players
    cout << "** Welcome to Poker **" << endl;
    cout << "How many players are there?" << endl;
    do {
        cout << ">> ";
        cin >> num_players;
        if (!(num_players < 9 & num_players > 0) || !cin) {
            cout << "Your number of players is invalid. Try again!" << endl;
        }
    } while (!(num_players < 9 & num_players > 0));
    
    cout << "There are " << num_players << ". The game will begin!" << endl;
    return num_players;
}


void start_game(int num_players){

    /*
     --The table is a vector/arrary of players + computers
     --8(?) total players
     --Each player has an array of 2 card objects
     --Table also has an array of 5 cards (starts with 3, 
       then after each round 1 more is added)
     */
    
}