/**
 * 	@file       Table.cpp
 * 	@author(s)  Alexander Rumak (alexrumak.ufl.edu)
 * 	@date       3/26/16
 * 	@version    1.0
 *
 * 	@brief      COP3503 Project, Texas Hold'em
 *
 * 	@section DESCRIPTION	The Table.cpp file deals with the game logic of Texas Hold'em
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

#include "header.h"

//Constructs A table with all players in it. This works for all human players and ai players
Table::Table(std:vecotr<Person> people) : people(people){
	
}

//Deals with the turn based player system
Table::turn(){
	

}

/*********************************************************
 * @brief Function definitions for the Card and Deck Objects
 * Note: Contents below this message may be moved to their
 * individual CPP files
 ********************************************************/
 
 //Card object constructor
Card::Card(char suit; int value) : suit(suit), value(value){
	
}

//Deck object constructor; Constructs a brand new, unshuffled deck
Deck::Deck (){
	char suit[] = {'d', 'h', 'c' ,'s'}; //Used for initalization of the deck
	int counter = 0;
	
	//initalizes the deck with c_suit and c_val
	for(int c_suit = 0; c_suit != 4; ++c_suit){
		for (int c_val = 2; c_val != 15; ++c_val){
			this->Cards[counter] = new Card(suit[c_suit], c_val);
			counter++;
		}
	}
}
