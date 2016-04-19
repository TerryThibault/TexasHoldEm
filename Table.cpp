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
#include <iostream>

/*********************************************************
 * @CardClassBriefing Function definitions for the Card and Deck Objects
 * Note: Contents below this message may be moved to their
 * individual CPP files
 ********************************************************/

 /*********************************************************
 * @brief Empty constructor for the Card Object. This is
 * needed for array declarations.
 ********************************************************/
 Card::Card(){
	suit = 's';
	value = 0;
}
 
/*********************************************************
 * @brief Constructor for the Card object
 ********************************************************/
Card::Card(char suit, int value) : suit(suit), value(value){

}

/*********************************************************
 * @brief The deck object consists of a vector of card
 * objects that are created and stored in the vector. This
 * constructor defines the cards based on a character that
 * represents suit, 'd': diamonds, 'h': hearts, 'c': clubs
 * , and 's': spades. The numbers range from 2-14; 11 being
 * Jack, 12 being Queen, 13 being King, and 14 being Ace.
 ********************************************************/
//Deck object constructor; Constructs a brand new, unshuffled deck
Deck::Deck (){
	
	numberOfCards = 0;
		
	char suit[] = {'d', 'h', 'c' ,'s'}; //Used for initalization of the deck
	
	//initalizes the deck with c_suit and c_val
	for(int c_suit = 0; c_suit != 4; ++c_suit){
		for (int c_val = 2; c_val != 15; ++c_val){
			Card cardToPush(suit[c_suit], c_val);
			this->cards.push_back(cardToPush);
			numberOfCards++;
		}
	}
}

/*********************************************************
 * @brief This destroys the deck.
 ********************************************************/
Deck::~Deck(){
	
	/*
	while(numberOfCards > 0){
		Card* toDelete = cards.back();
		cards.pop_back();
		numberOfCards--;
		delete toDelete;
	}
	*/ //Cards are no longer pointers, so this is no longer necessary.
}

/*********************************************************
 * @brief shuffles the deck using the vector shuffle from
 * the <algorithm> library. 
 ********************************************************/
void Deck::shuffleDeck() {

	//Generate random number number here
	std::random_shuffle(cards.begin(), cards.end());
	return;
	
}

/*
Card* Deck::drawCard(){
	Card* drawnCard = cards.back(); //Sets drawnCard equal to the card at the top of the deck
	numberOfCards--; //Lowers deck size by 1
	return drawnCard;
)*/

/*********************************************************
 * @brief Returns a card at the given index
 ********************************************************/
Card Deck::drawCard(int cardInd){
	return cards[cardInd];	
}

/*
Card* Deck::drawCard(int random){
	Card* drawnCard = Cards[random]; //Sets drawnCard equal to the card at the index
	numberOfCards--; //Lowers deck size by 1
	Cards.erase(random); //Removes the card at the given index
	return drawnCard;
}*/

/*********************************************************
 * @TableClassBrief Definitions of game logic structures; The main method will take the Table object and use it for all game logic
 ********************************************************/

 
 /*********************************************************
 * @brief Constructor for Table; is passed in a vector of
 * pointers to players. This works for both human players and
 * computer players
 ********************************************************/
Table::Table(std::vector<Player*> players, int smallBlindAmount, int gameSpeed) {
	this->players = players;
	numberOfPlayers = (int)players.size();
	tableDeck = new Deck();
	this->smallBlindAmount = smallBlindAmount;
	this->gameSpeed = gameSpeed;
}

 /*********************************************************
 * @brief Small Blind Amount function; Returns the value of small blind
 ********************************************************/
int Table::getSmallBlindAmount(){
	return smallBlindAmount;
}

 /*********************************************************
 * @brief Increments the Small Blind Amount in Table.cpp
 * The amount it is incremented by is based off of the difficulty
 * of the game, which determines the gameSpeed incrementor.
 ********************************************************/
void Table::incrementSmallBlind(){
	smallBlindAmount *= gameSpeed;
}

/*********************************************************
 * @brief Returns true when the game is deemed to be over;
 * the game is deemed to be over when there is only one player
 * with money remaining, the human player has no money, or
 * the human player has quit
 ********************************************************/
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

/*********************************************************
 * @brief Resets the Table values so that a new round can be played
 ********************************************************/
void newRound(){
	for(int i = 0; i != numberOfPlayers; ++i){
		players[i]->resetPlayer();
	}
	
}

/*********************************************************
 * @brief Scores the hand and distributes the pot to the 
 * respective players
 ********************************************************/
void Table::distributePot(std::vector<Card> communityHand, int *pot, int numPlayersFolded){
	
	int * moneyBefore = new int[numberOfPlayers];
	
	for(int i = 0; i != numberOfPlayers; ++i){
		moneyBefore[i] = players[i]->getMoney();
	}
	
	if(numPlayersFolded == numberOfPlayers - 1){
		//TODO: GUI plug, everyone but one player folded; find winner:
		for (int i = 0; i != numberOfPlayers; ++i){
			if(!(players[i]->playerHasFolded())){
				//player[i] has won, as he is the only player who has not folded
                allfold_win(players[i]); //Might need to dereference the player at i, since this passed a pointer to the player
				
                for(int j = 0; j != numberOfPlayers; j++){
					
					//Makes sure that the players own pot is not added to themselves
					if(i != j){
						pot[i] += pot[j];
						pot[j] = 0;
					}
				}
				//No need to look at other players
				break;
			}
		}
	}
	else{
		
		//points to a vector's internal array; cannot change the vectors values due to const.
		Card const * handCommunity = &communityHand[0];
		
		playerScorer(players, handCommunity); 
		
		bool potEmptied = false;
		
		while(!potEmptied){
			
			std::vector<Player*> potentialWinners;
			
			int smallestPotSize = 0;
			int sPotInd = 0; //Records the index of the smallest pot
			bool foundBound = false;
			
			for(int i = 0; i != numberOfPlayers; ++i){
				if(!(players[i]->playerHasFolded()) && ((pot[i] < smallestPotSize) || smallestPotSize == 0)){
					smallestPotSize = pot[i];
					sPotInd == i;
				}
			}
			
			if (smallestPotSize != 0){
				
			}
			else{
				potEmptied = true;
			}
			
		}
	}
}

/*********************************************************
 * @brief The game structure. TODO: describe in detail
 ********************************************************/
void Table::game(){
	
	//This vector represents the pot; with each location in the pot correponding to the index of the player in the player 
	//vector. This vector will update it's size as computer players are eliminated.
	std::vector<int> pot (numberOfPlayers, 0);

	//Initalizes these indices for a game of poker; Used if player count > 2
	int sBlindInd = 0;
	int bBlindInd = 1;
	int startPlayer = 2;//Represents a player to the left of Big Blind
	
	//If the number of players is less than three, the turns vary slightly
	if(numberOfPlayers < 3){
	
	}
	
	

	//Keeps track of which turn number it is; 1 = cards dealth; 2 = flop; 3 = add a card 4= add a card,last turn
	int turnNumber = 1;
	
	//Keeps track of how many hands have been played; Causes the bigBlind and smallBlind amounts to increment
	int handNumber = 1;
		
	//Records the maximum individual player contribution for a turn	
	int maximumContribution = 0;
	
	//Records the communityHand for a current turn
	std::vector<Card> communityHand;
	
	//Records the current top of the deck for card drawing
	int topOfDeck = 51;
	
	//Records the total amount of money played in one turn; i.e. the pot size
	int potSize = 0;
	
	//Records number of players who have folded for a turn
	int numPlayersFolded = 0;
	
	//Records number of players who have all ined for a turn
	int numPlayersAllIn = 0;

	while (true){ //Runs until the game is over

		
		//This turn structure does what is required at the start of each match; Such as assigning community cards or
		//forcing big blind small blind payments
		if (turnNumber == 1){
			//Round one; Cards are distributed and bigBlind and smallBlind are played
			
			//TODO: tell everyone who big blind and small blind are; Who the start player is(???)
			
			//Shuffles deck
			tableDeck->shuffleDeck();

			//If turnNumber is a multiple of three, increment the smallBlind
			if(turnNumber % 3 == 0){
				incrementSmallBlind();
			}
			
			int smallBCost = getSmallBlindAmount();

			//Placeholder functions 'makePayment'; Will replace with player functions that are available soon
			//Calls for big blind and small blind payments
			
			//Increases pot values at the smallBlind bigBlind indices
			pot[sBlindInd] = players[sBlindInd]->call(smallBCost);
			pot[bBlindInd] = players[bBlindInd]->call(smallBCost*2);
			
			//Updates potsize
			potSize += pot[sBlindInd];
			potSize += pot[bBlindInd];
						
			//TODO: GUI update here (Iff GUI is implemented)
            /*
             
             print_table(players, human, turnNumber);
             
             */

			//Passing cards to players
			//Max hand of 2 per player;
			Card* playerHands = new Card[2]; 
			
			int topOfDeck = 51; //52 cards; 51st index

			//Gives Hands to each player
			for(int i = 0; i != numberOfPlayers; i++){
				playerHands[0] = tableDeck->drawCard(topOfDeck);		
				playerHands[1] = tableDeck->drawCard(topOfDeck - numberOfPlayers);	
				topOfDeck--;
				players[i]->giveHand(playerHands);
			}
			topOfDeck = topOfDeck - numberOfPlayers;
			
			delete playerHands;
			
			turnNumber++;
							
		}
		else if(turnNumber == 2){
			
			//Draws three cards from the deck, places them into the communityHands
			
			//if I wanted to pay HOMAGE to poker i'd burn a few cards first
			for(int cardsToDraw = 0; cardsToDraw != 3; ++cardsToDraw){
				communityHand.push_back(tableDeck->drawCard(topOfDeck));
				topOfDeck--;
			}
			
			//TODO: Show the player the new cards (Might move this into the player object; ASK ME when you see this)
            //print_river(turnNumber);

			turnNumber++;
			
		}
		else if(turnNumber == 3){
			//Round three; another card is added to the communityHand.
			communityHand.push_back(tableDeck->drawCard(topOfDeck));
			topOfDeck--;
			turnNumber++;
			
			//TODO: Show the player the new cards (Might move this into the player object; ASK ME when you see this)
		}
		else{
			//Round four; the final card is added to the communityHand.
			communityHand.push_back(tableDeck->drawCard(topOfDeck));
			
			//TODO: Show the player the new cards (Might move this into the player object; ASK ME when you see this)
		}
		
		//This runs every 'turn'; Everyone gets a chance to vote, check, etc.

		int lastPin = bBlindInd;  
		int currPlayer = startPlayer;
		while(currPlayer != lastPin){
			
			//Checks if turns should be allowed; If the number of players folded plus the number of players all ined equals one less than the total number of players, then turns should not run;
			bool allowTurns = !(numPlayersFolded + numPlayersAllIn == numberOfPlayers - 1);
			
			//The player only gets to use his turn if they have more than zero funds, otherwise SKIP. The player also only gets to use his turn if they have not folded QQPotentialChange
			if((players[currPlayer]->getMoney() != 0) || !(players[currPlayer]->playerHasFolded()) || allowTurns){
				
				int betToBeat = maximumContribution - pot[currPlayer];
				int roundBet = players[currPlayer]->turn(betToBeat, pot[currPlayer], potSize, communityHand);
			
				//If the player contributes more to the pot than required (i.e. a raise), he is now the'last pin', meaning that if everyone checks, or contributes less than needed, then this player does not get to play another bet.
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
					//TODO: potential GUI plug; "players[currPlayer] has All Ined!"
                    
					numPlayersAllIn++;
				}
				pot[currPlayer] += roundBet;
				potSize += roundBet;
			}
			
			if(players[currPlayer]->playerHasFolded){
				numPlayersFolded++;
			}
			
			//Do these things when the player is the last remaining:
			if(numPlayersFolded == numberOfPlayers - 1){
				turnNumber == 4; //just go to turn 4
				break; //double check that this breaks out of the while loop
			}
			
			//TODO: GUI; at this point the player at [currPlayer] has increased the pot size; You should update the GUI potsize
						
			currPlayer++;
			//If current player index 'outsteps' it's bounds
			if(currPlayer == numberOfPlayers){
				currPlayer = 0;
			}
			
			
		//EndWhile, End of current players turn	
		}	
		if(turnNumber == 4){
			//TODO: (GUI) show everyone's cards(??) If everyone is still in game
			
			
			//Calculating Scores, and distributing pot:
			//After this method, the pot will be empty.
			//In this function all winners should be named
			void distributePot(std::vector<Card> communityHand, int *pot, numPlayersFolded);
			
			//TODO: Will distribute pot here; You can push a GUI update showing everyones money amount here. To get money from a player use player->getMoney(); It returns as an integer.
			
			///END OF HAND MANAGEMENT: determines if the game is to continue or not, and then resets the table for a new hand.
			
			//Checks if the game is over; Do we have a winner?
			if(gameOver() || humanPlayersLost()){
				break; //Game ends; while loop is escaped
			}


			//Reset the communityHand vector to be empty
			for(int cardsRemaining = 5; cardsRemaining != 0; --cardsRemaining){
				communityHand.pop_back();
			}
			
			maximumContribution = 0;
			
			//Reset other stuff
			turnNumber = 1;
			
			topOfDeck = 51;
			
			numPlayersAllIn = 0;
			numPlayersFolded = 0;

			//Resets values stored in TABLE and in the players scores themselves.
			newRound();
			
			//Increments the number of hands played
			handNumber++;

			//Sets the new big blind, small blind, and start players
			sBlindInd = bBlindInd;
			bBlindInd = startPlayer;
			startPlayer++;
			//If the index of startPlayers equal the number of players, then the startpin goes to index 0
			if(startPlayer == numberOfPlayers){
				startPlayer = 0;
			}
		}
	}
}



    
void Table::print_table(std::vector<Computer> computers, Player human, int roundNumber){
    //Player Info Table
    
    cout << "Player 1" << endl;
    cout << human.getMoney << endl;

    //Prints all the computers' information
    for (int i = 0; i < computers.size(); i++) {
        cout << computers[i].getName() << endl;
        cout << "Money: " << computers[i].getMoney() << endl << endl;
    }
    
    cout << "Pot: ";
    cout << table->pot << endl; //getPot??
    
    print_river(roundNumber);
    
    cout << endl << "Cards" << endl;
    print_player(human);
}

    
void Table::print_player(Player human){
    cout << "Your Cards: " << endl;
    cout << "|[" << /*SUIT 1*/ << "][" << /*NUMBER 1*/ << "]|" << endl;
    cout << "|[" << /*SUIT 2*/ << "][" << /*NUMBER 2*/ << "]|" << endl;
}

void Table::print_computer(){
    cout << "COMPUTER PLAYER" << endl << "*******************" << endl;
    cout << "Thinking . . . " << endl;
    cout << "Done." << endl;
}

void Table::print_river(int roundNumber){
    switch (roundNumber) {
        case 4:
            cout << communityHand[4] << endl;
            
        case 3:
            cout << communityHand[3] << endl;
            
        case 2:
            cout << communityHand[2] << endl;
            cout << communityHand[1] << endl;
            cout << communityHand[0] << endl;
            break;
            
        case 1:
            break;
            
        default:
            cout << "An error has occured." << endl;
    }
}

void Table::print_allin(Player player){
    cout << player.getName << " has gone all in!" << endl;
}

void Table::allfold_win(Player player){
    cout << "All other players folded, " << player.getName << " has won!" << endl;
}
