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
	
	//initalizes the deck with c_suit and c_val
	for(int c_suit = 0; c_suit != 4; ++c_suit){
		for (int c_val = 2; c_val != 15; ++c_val){
			this->Cards.push_back(new Card(suit[c_suit], c_val));
			numberOfCards++;
		}
	}
}

Deck::~Deck(){
	while(numberOfCards > 0){
		Card* toDelete = Cards.back();
		Cards.pop_back();
		numberOfCards--;
		delete toDelete;
	}
}

Deck::Shuffle () {
void Deck::Shuffle () {
	std::vector<Card*> temporaryDeck;
	while (numberOfCards > 0){
		//Generate random number number here
		int random = 0; //To replace with random number from 0 to numberOfCards - 1;
		temporaryDeck.push_back(drawCard(random));
	}
        
	Cards = temporaryDeck;
	return;
}

Card* Deck::drawCard(){
	Card* drawnCard = Cards.back(); //Sets drawnCard equal to the card at the top of the deck
	numberOfCards--; //Lowers deck size by 1
	Cards.pop_back(); //Removes last card
	return drawnCard;
}

Card* Deck::drawCard(int random){
	Card* drawnCard = Cards[random]; //Sets drawnCard equal to the card at the index
	numberOfCards--; //Lowers deck size by 1
	Cards.erase(random); //Removes the card at the given index
	return drawnCard;
}

/*********************************************************
 * @brief Definitions of game logic structures; The main method will take the Table object and use it for all game logic
 ********************************************************/

//Constructs A table with all players in it. This works for all human players and ai players
Table::Table(std:vector<Player> players) : players(players){
	numberOfPlayers = (int)players.size();
}

//Deals with the turn based player system
Table::turn(){
	players[0]->setSmallBlind(true);
	players[1]->setBigBlind(true);
	while (!gameOver()){
		int turnNumber = 1;
		if (turnNumber == 1){
			tableDeck = new Deck();
			tableDeck->shuffleDeck();
			Card
			
		}
		else if(turnNumber == 2){

		}
		else if(turnNumber == 3){

		}
		else{
			
			//Turn resets to number 1 
			turnNumber == 1;
			delete tableDeck;
		}
		
		for (int playerNumber = 0; playerNumber != numberOfPlayers; ++i){
			players[i]->turn();
			//Run turns
		}
	}
}