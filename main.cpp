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
#include <vector>
#include <string>
#include <iostream>
#include "header.h"
#include "Player.h"

using namespace std;

// Function declarations
void intro_menu();
void end_game();





/*************************
 MAIN
 *************************/
int main(int argc, char*argv[]){
		
    // The "start game" function calls "intro menu" to
    //find out how many players there are to make the
    //players vector, the small blind amount, and the game speed
    //for the table
    
    intro_menu();
    
}






/*************************
 Functions for main
 *************************/
void intro_menu(){
    int num_players;
    int small_blind;
    int game_speed;
    string name;
    std::vector<Player*> players;
    
    
    cout << "***************** Welcome to TexasHoldem! *********************" << endl;
    
    cout << "What is your name?" << endl << ">> ";
    
    cin >> name;
    
    //Human object made and added to players vector.
    Player * human = new Player(500, name);
    players.push_back(human);
    
    //num players
    cout << "How many computer players are there?" << endl;
    do {
        ">> ";
        cin >> num_players;
        if (!cin) {
            cout << "Error: please type a valid number between 1 and 8." << endl;
        }
    } while (!cin);
    
    cout << "There are " << (num_players + 1) << " total players at the table. " << endl;
    
    //Computer names and added to vector
    for (int i = 0; i < num_players; i++) {
        cout << "What is the name of the first computer?" << endl << ">> ";
        cin >> name;
        Player * computer = new Computer(500, name);
        players.push_back(computer);
        //Each Computer player is made and added to the players vector.
    }
    
    //small blind amount
    cout << "What is the amount paid by the small blind?" << endl;
    do {
        ">> $";
        cin >> small_blind;
        if (!cin) {
            cout << "Error: please type a valid amount." << endl;
        }
    } while (!cin);
    
    //game speed
    cout << "What is the game speed (1 = slowest, 5 = fastest)?" << endl;
    do {
        ">> ";
        cin >> game_speed;
        if (!cin) {
            cout << "Error: please type a valid number between 1 and 5." << endl;
    } while (!cin);
    
    cout << "The game will begin!" << endl;
    

    cout << "***************************************************************" << endl << endl;
    
    //table object created and game is run
    Table * table = new Table (players, small_blind, game_speed);
    table.game();
}




