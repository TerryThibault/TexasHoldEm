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
	
	std::vector<Card*> communityHand;
	
	int topOfDeck = 51;

	while (true){ //Runs until the game is over

		
		//This turn structure does what is required at the start of each match; Such as assigning community cards or
		//forcing big blind small blind payments
		if (turnNumber == 1){
			//Round one; Cards are distributed and bigBlind and smallBlind are played
			
			//Shuffles deck
			tableDeck->shuffleDeck();

			//If turnNumber is a multiple of three, increment the smallBlind
			if(turnNumber % 3 == 0){
				incrementSmallBlind();
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
			
			int topOfDeck = 51; //52 cards; 51st index

			//Gives Hands to each player
			for(int i = 0; i != numberOfPlayers; i++){
				playerHands[0] = tableDeck[topOfDeck];		
				playerHands[1] = tableDeck[topOfDeck-numberOfPlayers];	
				topOfDeck--;
				players[i]->giveHand(playerHands);
			}
			topOfDeck = topOfDeck - numberOfPlayers;

			turnNumber++;
							
		}
		else if(turnNumber == 2){
			
			//Draws three cards from the deck, places them into the communityHands
			for(int cardsToDraw = 0; cardsToDraw != 3; ++cardsToDraw){
				communityHand.push_back(tableDeck[topOfDeck]);
				topofDeck--;
			}

			turnNumber++;
			
		}
		else if(turnNumber == 3){
			//Round three; another card is added to the communityHand.
			communityHand.push_back(tableDeck[topOfDeck]);
			topOfDeck--;
			turnNumber++;
		}
		else{
			//Round four; the final card is added to the communityHand.
			comunityHand.push_back(tableDeck[topOfDeck]);	
		}
		
		//This runs every 'turn'; Everyone gets a chance to vote, check, etc.

		int lastPin = bBlindInd;  
		int currPlayer = startPlayerInd
		while(currPlayer != lastPin){
			
			//The player only gets to use his turn if they have more than zero funds, otherwise SKIP
			//The player also only gets to use his turn if they have not folded QQPotentialChange
			if((players[currPlayer]->getMoney() != 0) || !(players[currPlayer]->hasFolded)){
				int betToBeat = maximumContribution - pot[currPlayer];
				int roundBet = players[currPlayer]->turn(betToBeat);
			
				//If the player contributes more to the pot than required (i.e. a raise), he is now the
				//'last pin', meaning that if everyone checks, or contributes less than needed, then this 
				//player does not get to play another bet.
				if(roundBet > betToBeat){
					maximumContribution = pot[currPlayer];
					lastPin = currPlayer;
				}
				else if(roundBet == betToBeat){
					//Call
					//TODO: probably do nothing here
				}
				else{
					//All-in
					//TODO: 
				}
				pot[currPlayer] += roundBet;
			}
						
			currPlayer++;
			//If current player index 'outsteps' it's bounds
			if(currPlayer = numberOfPlayers){
				currPlayer = 0;
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
			
			//Increments the hands played
			handNumber++;

			//Sets the new big blind, small blind, and start players
			sBlindInd = bBlindInd;
			bBlindInd = startPlayer;
			startPlayer++;
			//If the index of startPlayers equal the number of players, then the startpin goes to index 0
			if(startPlayer == numberOfPlayers){
				startplayer = 0;
			}
		}
	//EndWhile, End of current players turn	
		
	}	
}
