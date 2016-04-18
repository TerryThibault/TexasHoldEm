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
std::vector<int> intro_menu();
void start_game(std::vector<int> prelim_vector);
std::vector<Player*> players(int num_players);
void end_game();





/*************************
 MAIN
 *************************/
int main(int argc, char*argv[]){
		
    // The "start game" function calls "intro menu" to
    //find out how many players there are to make the
    //players vector, the small blind amount, and the game speed
    //for the table
    
    start_game(intro_menu());
    
}






/*************************
 Functions for main
 *************************/
std::vector<int> intro_menu(){
    int num_players;
    int small_blind;
    int game_speed;
    string name;
    std::vector<int> prelim_vector(3);
    //prelim vector holds the preliminary values for the Table
    
    
    cout << "***************** Welcome to TexasHoldem! *********************" << endl;
    
    cout << "What is your name?" << endl << ">> ";
    
    cin >> name;
    
    Player * human = new Player(500, name);
    
    cout << "How many computer players are there?" << endl << ">> ";
    
    cin >> num_players;
    
    cout << "There are " << (num_players + 1) << " players at the table. " << endl;
    
    cout << "What is the amount paid by the small blind?" << endl << ">> $";
    
    cin >> small_blind;
    
    cout << "What is the game speed (1 = slowest, 5 = fastest)?" << endl << ">> ";
    
    cin >> game_speed;
    
    cout << "The game will begin!" << endl;
    

    cout << "***************************************************************" << endl << endl;
    
    prelim_vector[0] = num_players;
    prelim_vector[1] = small_blind;
    prelim_vector[2] = game_speed;
    
    return prelim_vector;
}


void start_game(std::vector<int> prelim_vector){
    //need to create vector of players
    int num_players = prelim_vector[0];
    int small_blind = prelim_vector[1];
    int game_speed = prelim_vector[2];
    
    //Create vector of Player objects (NEEDS TO LOOP)
    //std::vector<Player*> players(num_players);
    
    
    //Create table
    Table * table = new Table (players(num_players), small_blind, game_speed);
    
    //Commence game
    table->game();
    
}


std::vector<Player*> players(int num_players){
    std::vector<Player*> players;
    int money = 500;
    
    for(int i = 0; i < num_players; i++) {
        Player * computer = new Player(500);
        players.push_back(computer);
    }
    
    players.push_back(human);
    
    return players;
}