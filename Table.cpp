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
Table::Table(std:vector<Player> players, smallBlindAmount, bigBlindAmount) : players(players) {
	numberOfPlayers = (int)players.size();
	tableDeck = new Deck();
	this.bigBlindAmount = bigBlindAmount;
	this.smallBlindAmount = smallBlindAmount;
}

//Small Blind Amount function; Returns the value of small blind
int Table::smallBlindAmount(){
	return smallBlindAmount;
}

//Increments the Small Blind Amount in Table.cpp
void Table::incrementSmallBlind(int gameSpeed){
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
Table::game(){
	
	//This vector represents the pot; with each location in the pot correponding to the index of the player in the player 
	//vector. This vector will update it's size as computer players are eliminated.
	std::vector<int> pot (numberOfPlayers, 0);

	//Initalizes these indices for a game of poker; Used if player count > 2
	int sBlindInd = 0;
	int bBlindInd = 1;
	int startPlayerInd = 2;//Represents a player to the left of Big Blind
	
	//If the number of players is less than three, the turns vary slightly
	if(numberOfPlayers < 3){
	
	}
	
	///It may be unnecessary to set their bigBlind value and smallBlind values to true; in fact, might remove
	//Initalizes the players with small blind and big blind as 'true'
	players[sBlindInd]->setSmallBlind(true);
	players[bBlindInd]->setBigBlind(true);
	
	//Keeps track of which turn number it is; 1 = cards dealth; 2 = flop; 3 = river 4= last turn
	int turnNumber = 1;
	
	//Keeps track of how many hands have been played; Causes the bigBlind and smallBlind amounts to increment
	int handNumber = 1;
		
	int maximumContribution = 0;

	while (!gameOver()){

		
		//This turn structure does what is required at the start of each match; Such as assigning community cards or
		//forcing big blind small blind payments
		if (turnNumber == 1){
			//Shuffles deck
			tableDeck->shuffleDeck();

			//If turnNumber is a multiple of three, increment the smallBlind
			if(turnNumber % 3 == 0){
				incrementSmallBlind(smallBlindAmount());
			}
			
			int smallBCost = smallBlindAmount();

			//Placeholder functions 'makePayment'; Will replace with player functions that are available soon
			//Calls for big blind and small blind payments
			
			//Increases pot values at the smallBlind bigBlind indices
			pot[sBlindInd] = players[sBlindInd]->call(smallBCost);
			pot[bBlindInd] = players[bBlindInd]->call(smallBCost*2);
			
			//TODO: GUI update here (Iff GUI is implemented)	

			//Passing cards to players
			//Max hand of 2 per player;
			Card playerHands[2];
			
			int topOfDeck = 52;

			//Gives Hands to each player
			for(int i = 0; i != numberOfPlayers; i++){
				playerHands[0] = tableDeck[topOfDeck];		
				playerHands[1] = tableDeck[topOfDeck-numberOfPlayers];	
				topOfDeck--;
				players[i]->giveHand(playerHands);
			}
							
		}
		else if(turnNumber == 2){

		
		}
		else if(turnNumber == 3){
		
		
		}
		else{
			
			//Turn resets to number 1; this means after this turn a new 'hand' will begin
			turnNumber == 1;
			for(int i = 0; i < numberOfPlayers; ++i){	
				
			}
		}
		
		//This runs every 'turn'; Everyone gets a chance to vote, check, etc.

		int lastPin = bBlindInd;  
		int  currPlayer = startPlayerInd
		while(currPlayer != lastPin){
			
			//The player only gets to use his turn if they have more than zero funds, otherwise SKIP
			if(players[currPlayer]->getMoney() != 0){
				int betToBeat = maximumContribution - pot[currPlayer];
				int roundBet = players[currPlayer]->turn(betToBeat);
			
				//If the player contributes more to the pot than required (i.e. a raise), he is now the
				//'last pin', meaning that if everyone checks, or contributes less than needed, then they do 
				//not get to play another bet.
				if(roundBet > betToBeat){
					maximumContribution = pot[currPlayer];
					lastPin = currPlayer;
				}

			}
			int betToBeat = maximumContribution - pot[currPlayer];
			int roundBet = players[currPlayer]->turn(betToBeat);
			
			currPlayer++;
			//If current player index 'outsteps' it's bounds
			if(currPlayer = numberOfPlayers){
				currPlayer = 0;
			}

		//EndWhile, End of current players turn	
		}
	}	
}
