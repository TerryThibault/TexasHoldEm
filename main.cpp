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
#include "Player.h"
#include "header.h"

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
    while (true){
        ">> ";
        num_players = inputInteger();
        if ((num_players > 7) || (num_players < 1)) {
            std::cout << "Error: please type a valid number between 1 and 8." << std::endl;
        }
		else{
			break;
		}
    } 
    
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
    small_blind = 5;
    
    //game speed
	game_speed = 2;
    
    std::cout << "The game will begin!" << std::endl;
    

    std::cout << "***************************************************************" << std::endl << std::endl;
    
    //table object created and game is run
    Table * table = new Table(players, small_blind, game_speed);
    table->game();
}