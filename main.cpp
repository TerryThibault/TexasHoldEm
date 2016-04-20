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


//apparently this isn't allowed
//using namespace std;

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
    return 0;
}






/*************************
 Functions for main
 *************************/
void intro_menu(){
    int num_players;
    int small_blind;
    int game_speed;
    std::string name;
    std::vector<Player*> players;
    
    
    std::cout << "***************** Welcome to TexasHoldem! *********************" << std::endl;
    
    std::cout << "What is your name?" << std::endl << ">> ";
    
    std::cin >> name;
    
    //Human object made and added to players vector.
    Player * human = new Player(500, name);
    players.push_back(human);
    
    //num players
    std::cout << "How many computer players are there?" << std::endl;
    do {
        ">> ";
        std::cin >> num_players;
        if ((!std::cin) || (num_players > 8) || (num_players < 1)) {
            std::cout << "Error: please type a valid number between 1 and 8." << std::endl;
        }
    } while (!std::cin);
    
    std::cout << "There are " << (num_players + 1) << " total players at the table. " << std::endl;
    
    //Computer names and added to vector
    for (int i = 0; i < num_players; i++) {
        std::cout << "What is the name of the computer " << i << "?" << std::endl << ">> ";
        std::cin >> name;
        Player * computer = new Computer(500, name);
        players.push_back(computer);
        //Each Computer player is made and added to the players vector.
    }
    
    //small blind amount
    std::cout << "What is the amount paid by the small blind?" << std::endl;
    do {
        ">> $";
        std::cin >> small_blind;
        if (!std::cin) {
            std::cout << "Error: please type a valid amount." << std::endl;
        }
    } while (!std::cin);
    
    //game speed
    std::cout << "What is the game speed (1 = slowest, 5 = fastest)?" << std::endl;
    do {
        ">> ";
        std::cin >> game_speed;
        if ((!std::cin) || (game_speed < 1) || (game_speed > 5)) {
            std::cout << "Error: please type a valid number between 1 and 5." << std::endl;
        }
    } while (!std::cin);
    
    std::cout << "The game will begin!" << std::endl;
    

    std::cout << "***************************************************************" << std::endl << std::endl;
    
    //table object created and game is run
    Table * table = new Table (players, small_blind, game_speed);
    table->game();
}