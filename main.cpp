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
#include <iostream>
#include "Player.h"
#include "header.h"
#include "Textfill.h"

// Function declarations
void intro_menu();
void end_game();
int inputInteger();

/*************************
 MAIN
 *************************/
int main(int argc, char*argv[]){
	// srand gives a random seed so that shuffle and rand() 
	// gives different values whenever the program is run
	srand(time(NULL));

    // The intro_menu function finds out how many players
	// there are to make the players vector, the small blind 
	// amount, and the game speed for the table
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
	std::string compName;
	std::vector<Player*> players;


	textOpeningMenu();
	std::cout << "NAME IS HARDCODED. CHANGE LATER." << std::endl;
	//std::cout << "What is your name?" << std::endl << ">> ";
    
    //getline(std::cin,name);
    //Human object made and added to players vector.
    Player* human = new Player(500, "HUMAN");
    players.push_back(human);

    // Number players
    std::cout << "How many computer players are there?" << std::endl << ">> ";
    do{
		num_players = inputInteger();
		if (num_players >= 1 && num_players <= 7){
			break;
		}
		else{
			std::cout << "Error, number of computer players must be greater than 0 and less than 8." << std::endl;
		}
	}while (true);
	
    std::cout << "There are " << (num_players + 1) << " total players at the table. " << std::endl;
    
    //Computer names and added to vector
    for (int i = 0; i < num_players; i++) {
			if(i == 0)
			{
				name = "Alex";
			}
			if(i == 1)
			{
				name = "Cameron";
			}
			if(i == 2)
			{
				name = "Terry";
			}
			if(i == 3)
			{
				name = "Hugh";
			}
			if(i == 4)
			{
				name = "Tim";
			}
			if(i == 5)
			{
				name = "Diego";
			}
			if(i == 6)
			{
				name = "Segfault";
			}
		/***********************************************/
        Computer* comp = new Computer(500, name);
        players.push_back(comp);
        //Each Computer player is made and added to the players vector.
    }
    
    //small blind amount
    small_blind = 5;
    
    //game speed
	 game_speed = 2;
    
    std::cout << "\nThe game will begin shortly!\n" << std::endl;
	textloadingGame();
	

    //table object created and game is run
    Table * table = new Table(players, small_blind, game_speed);
    table->game();
}

int inputInteger(){ //Input filtering stuffs
	std::string inputString;
	while (true) {
		getline(std::cin, inputString);
		
		//Checks if integer
		bool validInteger = true;
		for (int i = 0; i != (int)inputString.length(); ++i){
			if (!isdigit(inputString.at(i))){
				validInteger = false;
				break;
			}
		}
		if (validInteger && (int)inputString.size() < 10){ //Is an integer
			int inputInteger = 0;
			for (int j = 0; j != (int)inputString.length(); ++j){
				inputInteger += pow(10,j)*(inputString.at(inputString.length() - 1 - j) - '0'); //Converts input to integer
			}
			
			return inputInteger;
			
		}
		else{ //Not an integer
			std::cout << "Invalid input, not an integer." << std::endl;
		}
	}
		
	return 0;
}
