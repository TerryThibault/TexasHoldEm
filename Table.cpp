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

	srand(time(NULL));
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
	
	srand((int)time(NULL));
	
	bBlindInd = rand() % (numberOfPlayers - 1);
	
	//DEBUG
	bBlindInd = 0;
	
	//Initalizes these indices for a game of poker; Used if player count > 2
	if(numberOfPlayers < 3){
		sBlindInd = bBlindInd - 1;
		if (sBlindInd == -1){
			sBlindInd = numberOfPlayers - 1;
		}

		buttonInd = bBlindInd;

	}
	else{
		sBlindInd = bBlindInd - 1;
		if(sBlindInd == -1){
			sBlindInd = numberOfPlayers - 1;
		}
		buttonInd = sBlindInd - 1;
		if (buttonInd == -1){
			buttonInd = numberOfPlayers - 1;
		}
	}
	
	numPlayersInPlay = numberOfPlayers;
	
	//If the number of players is less than three, the turns vary slightly
	
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
	for(int i = 0; i != numberOfPlayers; ++i){
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
void Table::newRound(){
	
	//Sets players who lost, to have lost
	for(int i = 0; i != numberOfPlayers; ++i){
		if(players[i]->getMoney() == 0){
			players[i]->playerLost();
			//For networked player; the player would need to be removed here and replaced by a NULL
			numPlayersInPlay--; //Potential error thrower
		}
	}
	
	//Resets players with default values; except for player name and player money
	for(int i = 0; i != numberOfPlayers; ++i){
		players[i]->resetPlayer();
	}
	
	//Sets the new big blind, small blind, and start players
	buttonInd = sBlindInd;
	sBlindInd = bBlindInd;
	bBlindInd++;
	
	//If the index of startPlayers equal the number of players, then the startpin goes to index 0
	if(bBlindInd >= numberOfPlayers - 1){
		bBlindInd = 0;
	}
	//Keep moving big blind index until you find a player
	while(players[bBlindInd]->playerHasLost()){
		bBlindInd++;
		
		//Needed
		if(bBlindInd >= numberOfPlayers - 1){
		bBlindInd = 0;
		}
	}
}

/*********************************************************
 * @brief Scores the hand and distributes the pot to the 
 * respective players
 ********************************************************/
void Table::distributePot(std::vector<Card> communityHand, std::vector<int> pot, int numPlayersFolded){
	
	int * moneyBeforeSplit = new int[numberOfPlayers];
	for(int i = 0; i != numberOfPlayers; ++i){
		moneyBeforeSplit[i] = players[i]->getMoney();
	}
	if(numPlayersFolded == numPlayersInPlay - 1){
		//TODO: GUI plug, everyone but one player folded; find winner:
		for (int i = 0; i != numberOfPlayers; ++i){
			if(!(players[i]->playerHasFolded())){
				//player[i] has won, as he is the only player who has not folded
				
				int winnings = 0;
				
                for(int j = 0; j != numberOfPlayers; ++j){
					
					
					winnings += pot[j];
					//Makes sure that the players own pot is not added to themselves
					
				}
				
				players[i]->addMoney(winnings);
				//No need to look at other players
				
				allfold_win(players[i], winnings);
				
				return; 
			}
		}
	}
	else{
		
		//points to a vector's internal array; cannot change the vectors values due to const.
		//Card const * handCommunity = &communityHand[0];
		Card * handCommunity = new Card[5];
		
		for(int i = 0; i != 5; ++i){
			handCommunity[i] = communityHand[i];
		}
		
		
		//Scores all the players
		playerScorer(players, handCommunity); 
		
		bool potEmptied = false;
		
		//Stores the index values of potential winners
		std::vector<Player*> potentialWinners (players);

		while(!potEmptied){
			
			// int potentWinnersSize = (int)potentialWinners.size();
			// //Removes players who are not potential winners
			// int wIter = 0;
			// while(wIter < potentWinnersSize){
				// if((potentialWinners[wIter]->playerHasFolded()) || (pot[wIter] == 0)){
					// potentialWinners.erase(potentialWinners.begin() + wIter);
					// potentWinnersSize--;
				// }
				// else{
					// wIter++;
				// }
			// }
			
			int wSize = (int)potentialWinners.size();
			int counter = 0;
			do{
				 counter = 0;
				 for(int i = 0; i < wSize; ++i){
					 if(potentialWinners[i]->playerHasFolded() || pot[i] == 0){
						 potentialWinners.erase(potentialWinners.begin() + i);
						 counter++;
						 wSize--;
					 }
				 }
				
			} while(counter > 0);
		
			int smallestPotSize = 0;
			int sPotInd = 0; //Records the index of the smallest pot
			
			for(int i = 0; i != numberOfPlayers; ++i){
				if(!(players[i]->playerHasFolded()) && ((pot[i] < smallestPotSize) || smallestPotSize == 0)){
					smallestPotSize = pot[i];
					sPotInd = i;
				}
			}
			
			if (smallestPotSize != 0){
				
				std::vector<Player*> winners (determineWinnerVector(potentialWinners, handCommunity));
				
				for(int i = 0; i != winners.size(); ++i){
					std::cout << winners[i];
				}
				
				int numberOfWinners = (int)winners.size();
				
				//Split pot
				int potToSplit = 0;
				
				//Finds the amount of money being vyed for
				for(int i = 0; i != numberOfPlayers; ++i){
					if(pot[i] >= smallestPotSize){
						potToSplit += smallestPotSize;
						pot[i] -= smallestPotSize;
					}
					else{
						//Needed for players who have folded; The program does not look for winners out of players who have already folded...
						potToSplit += pot[i];
						pot[i] = 0;
					}
				}
			
				if((numberOfWinners > 1)){
					//Automatically floored, the remaining money goes to the house
					potToSplit = potToSplit/numberOfPlayers; 
					
					for(int i = 0; i != numberOfWinners; ++i){
						winners[i]->addMoney(potToSplit);
					}
				}
				else if ((numberOfWinners == 1)){
					//One person pot
					winners[0]->addMoney(potToSplit);
				}
				else{
					std::cout << "debuggerErrorQQ123" ;
				}
			}
			else{
				potEmptied = true;
			}
			
		}
	}
	
	//TODO: GUI plug
	//Compare everyone's money to their initial money to tell who won what, and how much
	
	split_pot(players, moneyBeforeSplit);
	
	delete moneyBeforeSplit;
	
	return;
}

/*********************************************************
 * @brief The game structure. TODO: describe in detail
 ********************************************************/
void Table::game(){
	
	//This vector represents the pot; with each location in the pot correponding to the index of the player in the player 
	//vector. This vector will update it's size as computer players are eliminated.
	std::vector<int> pot (numberOfPlayers, 0);


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
			if(handNumber % 3 == 0){
				incrementSmallBlind();
			}
			
			int smallBCost = getSmallBlindAmount();

			//Placeholder functions 'makePayment'; Will replace with player functions that are available soon
			//Calls for big blind and small blind payments
			
			//Increases pot values at the smallBlind bigBlind indices
			//TODO: Force Bet
			if(!players[sBlindInd]->playerHasLost()){
				pot[sBlindInd] = players[sBlindInd]->forceBet(smallBCost);
				maximumContribution = pot[sBlindInd];
			}
			
			pot[bBlindInd] = players[bBlindInd]->forceBet(smallBCost*2);
			
			if(pot[bBlindInd] > maximumContribution){
				maximumContribution = pot[bBlindInd];
			}
			
			
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
			

			//Gives Hands to each player
			for(int i = 0; i != numberOfPlayers; i++){
				playerHands[0] = tableDeck->drawCard(topOfDeck);		
				playerHands[1] = tableDeck->drawCard(topOfDeck - numberOfPlayers);	
				topOfDeck--;
				players[i]->giveHand(playerHands);
			}
			topOfDeck = topOfDeck - 2*numberOfPlayers;
			
			delete playerHands;
			
			
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
			
		}
		else if(turnNumber == 3){
			//Round three; another card is added to the communityHand.
			communityHand.push_back(tableDeck->drawCard(topOfDeck));
			topOfDeck--;
			
			//TODO: Show the player the new cards (Might move this into the player object; ASK ME when you see this)
		}
		else{
			//Round four; the final card is added to the communityHand.
			communityHand.push_back(tableDeck->drawCard(topOfDeck));
			
			//TODO: Show the player the new cards (Might move this into the player object; ASK ME when you see this)
		}
		
		//This runs every 'turn'; Everyone gets a chance to vote, check, etc.
		int lastPin = 0;  
		int currPlayer = 0;
		
		//Determines who goes when
		if(turnNumber == 1){
			currPlayer = bBlindInd + 1;
			if (bBlindInd == numberOfPlayers){
				currPlayer = 0;
			}
			lastPin = currPlayer;
		}
		else{
			currPlayer = sBlindInd;
			lastPin = currPlayer;
		}
		
		do{
			//Checks if turns should be allowed; If the number of players folded plus the number of players all ined equals one less than the total number of players, then turns should not run;
			bool allowTurns = !(numPlayersFolded + numPlayersAllIn > numPlayersInPlay - 1);
			
			//The player only gets to use his turn if they have more than zero funds, otherwise SKIP. The player also only gets to use his turn if they have not folded QQPotentialChange
			if(!(players[currPlayer]->getMoney() == 0) && !(players[currPlayer]->playerHasFolded()) && !(players[currPlayer]->playerHasLost()) && !(players[currPlayer]->playerAllIn()) && allowTurns){
				
				int betToBeat = maximumContribution - pot[currPlayer];
				int roundBet = players[currPlayer]->turn(betToBeat, pot[currPlayer], potSize, communityHand);
			
				//If the player contributes more to the pot than required (i.e. a raise), he is now the'last pin', meaning that if everyone checks, or contributes less than needed, then this player does not get to play another bet.
				if(players[currPlayer]->playerAllIn()){
					numPlayersAllIn++;
					
					
					if(roundBet > betToBeat){
						maximumContribution += (roundBet - betToBeat);
						lastPin = currPlayer;
						
					}
					else{
						//Nothing
					}
					//All-in
					//TODO: potential GUI plug; "players[currPlayer] has All Ined!"
					print_allin(players[currPlayer]);
				}
				else if(roundBet > betToBeat){
					//Raise
					maximumContribution += (roundBet - betToBeat);
					lastPin = currPlayer;
                    std::cout << players[currPlayer]->getName() << " has raised to " << maximumContribution << "." << std::endl;
				}
				else if(players[currPlayer]->playerHasFolded()){
					//Player has folded
                    std::cout << players[currPlayer]->getName() << " has folded. Bye!" << std::endl;
					numPlayersFolded++;
				}
				else if(roundBet == betToBeat && betToBeat == 0){
					//Check
					//TODO: GUI CHECK
					std::cout << players[currPlayer]->getName() << " has checked." << std::endl;
				}
				else if(roundBet == betToBeat){
					//Call
					//TODO: GUI CALL
					std::cout << players[currPlayer]->getName() << " has called." << std::endl;
				}
				else {
					//This should never be reached
					std::cout << "Debugger1204124";
				}
				//Changes their pot index
				pot[currPlayer] += roundBet;
				potSize += roundBet;
			}
			
			//Do these things when the player is the last remaining:
			if(numPlayersFolded == numPlayersInPlay - 1){
                                turnNumber = 5; //just go to turn 4
				break; //double check that this breaks out of the while loop
			}
			
			//TODO: GUI; at this point the player at [currPlayer] has increased the pot size; You should update the GUI potsize
						
			currPlayer++;
			
			//If current player index 'outsteps' it's bounds
			if(currPlayer == numberOfPlayers){
				currPlayer = 0;
			}
			
			
		//EndWhile, End of current players turn	
		} while (currPlayer != lastPin);
		
		turnNumber++;
		if(turnNumber == 5){
			//TODO: (GUI) show everyone's cards(??) If everyone is still in game Also need to print the community hand one last time.
			std::cout << "\n";
			print_river(communityHand);
			
			for(int i = 0; i < numberOfPlayers; ++i){
				if(!players[i]->playerHasLost() && !players[i]->playerHasFolded()){
					players[i]->printHand();
				}
			}
			
			//Calculating Scores, and distributing pot:
			//After this method, the pot will be empty.
			//In this function all winners should be named
			distributePot(communityHand, pot, numPlayersFolded);
			//TODO: Will distribute pot here; You can push a GUI update showing everyones money amount here. To get money from a player use player->getMoney(); It returns as an integer.
			
			std::cout << "\n";
			std::cout << "***************** NEW ROUND *********************";
			std::cout << "\n\n";
			
			///END OF HAND MANAGEMENT: determines if the game is to continue or not, and then resets the table for a new hand.
			//Checks if the game is over; Do we have a winner?
			if(gameOver() || players[0]->getMoney() == 0){
				std::cout << "Game over!\n";
				for(int t = 0; t < numberOfPlayers; ++t)
				{
					if(players[t]->getMoney() != 0)
					{
						std::cout << players[t]->getName() << " won! GG NUBS!\n";
					}
				}
				return; //Game ends; while loop is escaped
			}


			//Reset the communityHand vector to be empty
			for(int i = 0; i != 5; ++i){
				communityHand.pop_back();
			}
			
			maximumContribution = 0;
			
			//Reset other stuff
			turnNumber = 1;
			
			topOfDeck = 51;
			
			numPlayersAllIn = 0;
			numPlayersFolded = 0;
			
			potSize = 0;
			
			

			//Resets values stored in TABLE and in the players scores themselves.
			newRound();
			
			//Increments the number of hands played
			handNumber++;

		}
	}
}



    
void Table::print_table(std::vector<Player*> players, int roundNumber, int potsize, std::vector<Card> communityHand){
    //Player Info Table

    int size = players.size();

    //Prints all the players' information
    for (int i = 0; i < size; i++) {
        std::cout << players[i]->getName() << std::endl;
		std::cout << "Money: " << players[i]->getMoney() << std::endl << std::endl;
    }
    
	std::cout << "Pot: ";
	std::cout << potsize << std::endl; //getPot?? nope, potsize is a parameter now
    
    print_river(communityHand);
    
	std::cout << std::endl << "Your cards" << std::endl;
    print_player(players[0]);
}

// MOVED TO PLAYER.CPP 
// UNDER THE TURN FUNCTION
void Table::print_player(Player* player)
{
    //prints the human's cards kind of haphazardly right now
  Card* PlayerHand = players[0]->checkHand(); 
	std::cout << "Your Cards: " << std::endl;
	std::cout << "Suit: " << PlayerHand[0].suit;
	std::cout << "Value: " << PlayerHand[0].value << "\n.";
	std::cout << "Suit: " << PlayerHand[1].suit;
	std::cout << "Value: " << PlayerHand[1].value << "\n.";
}
void Table::print_computer(){
    //prints computer thinking action
	std::cout << "COMPUTER PLAYER" << std::endl << "*******************" << std::endl;
	std::cout << "Thinking . . . " << std::endl;
    
    waiting_is_fun();
    
	std::cout << "Done." << std::endl;

}

                         
void Table::print_river(std::vector<Card> communityHand){
    //prints the community hand depending on the round number
    if ((int)communityHand.size() != 0) {
		std::cout << "The community cards: ";
		for (int i = 0; i < (int)communityHand.size(); ++i) {
			std::cout << communityHand[i].value << communityHand[i].suit << " ";
		}
	}
	std::cout << "\n";
}

                         
void Table::print_allin(Player *player){
	std::cout << player->getName() << " has gone all in!" << std::endl;
}

                         
void Table::allfold_win(Player *player, int amount){
	std::cout << "All other players folded, " << player->getName() << " has won " << amount << "!" << std::endl;
	player = 0;
}

                         
void Table::split_pot(std::vector<Player*> players, int moneyBeforeSplit[]) {
    int money_gained = 0;
    for (int i = 0; i < (int)players.size(); i++){
        money_gained = (players[i]->getMoney() - moneyBeforeSplit[i]);
		if(money_gained > 0){
			std::cout << "Player " << players[i]->getName() << " has gained $" << money_gained << "." << std::endl;
		}
    }
}
                         

void Table::waiting_is_fun() {
    clock_t temp;
    temp = clock () + 3 * CLOCKS_PER_SEC ;
    while (clock() < temp) {}
}				 

