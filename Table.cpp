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
 * 		Cameron Mockabee-TEST
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

Table::Table(std:vector<Player> players,int smallBlindAmount, int gameSpeed) : players(players) {
	numberOfPlayers = (int)players.size();
	tableDeck = new Deck();
	this.smallBlindAmount = smallBlindAmount;
	this.gameSpeed = gameSpeed;
}

//Small Blind Amount function; Returns the value of small blind
int Table::smallBlindAmount(){
	return smallBlindAmount;
}

//Increments the Small Blind Amount in Table.cpp
void Table::incrementSmallBlind(){
	smallBlindAmount += gameSpeed;
}

bool Table::gameOver(){
	//This counter counts how many players have no money
	int haveMoneyCount = 0;
	for(int i = 0; i < numberOfPlayers; ++i){
		if(players[i]->getMoney() > 0){
			haveMoneyCount++;
		}
	}
	
	//More than one player has money; Game is not over;
	if(haveMoneyCount >= 2){
		return false;
	}

	//Game is over
	return true;

}

//Deals with the turn based player system
Table::turn(){

	//Keeps track of the indices of big blind and small blind
	int smallBlindIndex = 0;
	int bigBlindIndex = 1;
	
	//Initalizes the players with small blind and big blind as 'true'
	players[smallBlindIndex]->setSmallBlind(true);
	players[smallBlindIndex + 1]->setBigBlind(true);
	
	//Keeps track of which turn number it is; 1 = cards dealth; 2 = flop; 3 = river 4= last turn
	int turnNumber = 1;

	//Keeps track of small blind payment amount'
	int smallBlindPayment = 5;
	
	while (!gameOver()){


		//This turn structure does what is required at the start of each match; Such as assigning community cards or
		//forcing big blind small blind payments
		if (turnNumber == 1){
			//Shuffles deck
			tableDeck->shuffleDeck();

			//Placeholder functions 'makePayment'; Will replace with player functions that are available soon
			//Calls for big blind and small blind payments
			players[smallBlindIndex]->makePayment(smallBlindPayment);
			players[bigBlindIndex]->makePayment(smallBlindPayment*2);

		
		}
		else if(turnNumber == 2){

		
		}
		else if(turnNumber == 3){
		
		

	}

		if(turnNumber == 4){
			//Calculating Scores, and distributing pot:
			
			
			
			
			
			//Checks if the game is over; Do we have a winner?
			if(gameOver() || humanPlayersLost()){
				break; //Game ends; while loop is escaped
			}


			//Reset the communityHand vector to be empty
			for(int cardsRemaining = 5; cardsRemaining != 0; --i){
				communityHand.pop_back();
			}
			
			//Reset the pot contribution
			for(int i = 0; i != numberOfPlayers; ++i){
				pot[i] = 0;
			}
			maximumContribution = 0;
			
			//Reset other stuff
			turnNumber = 1;
			
			topOfDeck = 51;

			//Resets values stored in TABLE and in the players scores themselves.
			resetTable();

		}
		else{

			
			//Turn resets to number 1 
			turnNumber == 1;
			for(int i = 0; i < numberOfPlayers; ++i){	
				
			}
		}
		

	}	


		
		
		
	}

}
