/**
 * 	@file       header.h
 * 	@author(s)  Terry Thibault (tlt@cise.ufl.edu)
 * 		    Alexander Rumak (alexrumak.ufl.edu)
 		    Hugh Wu
 * 	@date       4/11/16
 * 	@version    1.0
 * 	@brief      COP3503 Project, Texas Hold'em
 *
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

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include <time.h>

/*********************************************************
* @brief Default constructor for Player; Will be overridden
* by children classes. Takes in the user's inputted name
* and money 
*********************************************************/
Player::Player(int money, std::string name){
	this->money = money;
	this->name = name;
	currentScore = 0;
	
}

/*********************************************************
* @brief Returns the player's name
*********************************************************/
std::string Player::getName() {
	return name;
}


/*********************************************************
 * @brief This function checks if the player has enough 
 * funds to make a bet. 
 ********************************************************/
bool Player::HasEnoughFunds(int bet)
{
	if (money < bet) return false;
	return true;
}

/*********************************************************
 * @brief This function will add money to the player money
 * in the event that they win a hand.
 ********************************************************/
void Player::addMoney(int amount) 
{
	money += amount;
}

/*********************************************************
* @brief Returns the amount of money that the player has
*********************************************************/
int Player::getMoney() {
	return money;
}


/*********************************************************
 * @brief This function is called by the table. Simply 
 * subtracts from the player cash and tells the table
 * how much to add to the pot. If the player does not have
 * enough money, the program will loop for an amount that 
 * is equal to or less than their funds
 ********************************************************/
int Player::raise(int amount, int prev_bet)
{
	money -= (amount + prev_bet);
	return (amount + prev_bet);
	
}

/*********************************************************
 * @brief This function's input is the largest previous 
 * bet. If the player does not have enough money to call,
 * the player will go all-in.
 ********************************************************/
int Player::call(int prev_bet)
{
	money -= prev_bet
	return prev_bet;
}

int Player::allIn() {
	int allMyMoney = money;
	money = 0;
	playerAllIn = true;

	return allMyMoney;
}

/*********************************************************
* @brief Returns true if the player has folded
*********************************************************/
bool Player::playerHasFolded() {
	return hasFolded;
}

/*********************************************************
* @brief Returns true if the player has fall-in'd
*********************************************************/
bool Player::playerAllIn() {
	return hasAllIn;
}

/*********************************************************
 * @brief Returns a pointer to the player's hand.
 ********************************************************/
Card* Player::checkHand() const
{
	return hand;
}

/*********************************************************
 * @brief Gives the player their hand for the turn
 ********************************************************/
void Player::giveHand(Card* givenHand){
	hand = givenHand;
}


/*********************************************************
* @brief Set the players hand to NULL; This means the player does not
* have a hand.
*********************************************************/
void Player::loseHand(){
	hand = NULL;
	return;
}

/*********************************************************
* @brief Sets the players score; Useful for Artifical
* intelligence but also needed to find winners.
*********************************************************/
void Player::setScore(double score){
	currentScore = score;
	return;
}

/*********************************************************
* @brief Returns the players score
*********************************************************/
double Player::getScore(){
	return currentScore;
}



/*********************************************************
* @brief Resets player values to their initial states
*********************************************************/
void Player::resetPlayer(){
	hasFolded = false;
	currentScore = 0;
	hand = NULL;
}

/*********************************************************
 * @brief Turn is the main mechanism by which the game is 
 * able to tell what the user's action is. 
 ********************************************************/
int Player::turn(int betToMatch, int currentContribution, int potSize, std::vector<Card> communityHand)
{
	//Give a list of possibile options
	std::cout << "The current bet is: " << betToMatch << ".\n";
	std::cout << "Your money: " << this->getMoney() << ".\n";
	std::cout << "The amount you currently have in the pot is " << currentContribution << ".\n";
	std::cout << "The pot has " << potSize << " dollars in it.\n";
	
	
	//If the current bet is 0, checking is an option. Yes, calling and checking are the same in this situation.
	if(betToMatch == 0)
	{
		std::cout << "1. Check \n2. Raise \n3. All-In \n4. Fold \n";
		std::string input; 
		std::cin >> input;
		
		//If they didn't input a valid option, fail.
		if(!(input == "1" || input == "2" || input == "3" || input == "4"))
		{
			std::cout << "Invalid parameter. Please enter a valid option.\n" 
			turn(betToMatch, currentContribution, potSize, communityHand);
		}

		if(input == "1")
		{
			std::cout << "Checked.\n";
			return 0;
		}
		
		else if(input == "2")
		{
			std::cout << "Raise amount: ";
			std::cin >> input;
			//Check to ensure it's really a number -- not done yet
			if(this->HasEnoughFunds(input + betToMatch))
			{
				std::cout << "Raised.\n";
				return raise(input, betToMatch);
			}
			std::cout << "You don't have enough money to do that. \n"
			turn(betToMatch, currentContribution, potSize, communityHand);
		}

		else if(input == "3")
		{
			std::cout << "GOING ALL IN BOSS.\n";
			return allIn();
		}
		
		else // input has to be 4
		{
			this->hasFolded = true;
			std::cout << "Fold successful.\n";
			return 0;
		}
	}
	
	//Assuming betToMatch > 0. 

	else
	{
		std::cout << "1. Call \n2. Raise \n3. All-In\n 4. Fold \n";
		std::string input;
		std::cin >> input;

		//Fail for invalid options
		if (!(input == "1" || input == "2" || input == "3" || input == "4"))
		{
			std::cout << "Invalid parameter. Please enter a valid option.\n"
			turn(betToMatch, currentContribution, potSize, communityhand);
		}

		else if (input == "1")
		{
			if (this->HasEnoughFunds(betToMatch))
			{
				std::cout << "Called.\n"
				return call(betToMatch);
			}
			std::cout << "Not enough funds to perform that action.\n"
			turn(betToMatch, currentContribution, potSize, communityHand);
		}

		else if (input == "2")
		{
			std::cout << "Raise amount: ";
			std::cin >> input;
			//Check to ensure it's really a number -- not done yet
			if (this->HasEnoughFunds(input + betToMatch))
			{
				std::cout << "Raised.\n";
				return raise(input, betToMatch);
			}
			std::cout << "You don't have enough money to do that. \n";
			turn(betToMatch, currentContribution, potSize, communityHand);
		}

		else if (input == "3")
		{
			std::cout << "GOING ALL IN BOSS.\n";
			return allIn();
		}

		else if (input == "4")
		{
			this->hasFolded = true;
			std::cout << "Fold successful.\n";
			return 0;
		}
	}
}


/*********************************************************
* @brief The computer inheirits everything from the 
* player class but its methods are overridden so it does
* not take user input
**********************************************************/
Computer::Computer(int money, std::string ) : Player(money, name) {
	// Everytime a new computer player is created, their confidence levels are different
	// rand() % x + y gives a random integer from [y, y + x)
	confidence = rand() % 21 + 20;
}

/*******************************************************
* @brief This function deals with how the computer
* decides their actions.
**********************************************************/
int Computer::turn(int betToMatch, int currentContribution, int potSize, std::vector<Card> communityHand){
	//Seeding the random number generator
	srand(time(NULL));

	// When the computer only has their two cards (the first turn)
	if (communityHand.size() == 0) {
		// If the computer gets a pair, then it will greatly increase their confidence
		if (hand[0].value == hand[1].value) {
			confidence += (rand() % 11 + 10) + (1.5 * hand[0].value);
		}
		// Otherwise if they get a high card (Jack or Higher), they get a smaller boost in confidence
		else if (hand[0].value > 10 || hand[1].value > 10){
			confidence += (rand() % 11 + 5) + hand[0].value + hand[1].value;
		}
		// Otherwise if they have matching suits, smaller boost in confidence
		else if (hand[0].suit == hand[1].suit) {
			confidence += (rand() % 6 + 5) + hand[0].value + hand[1].value;
		}
		// Otherwise their hand is pretty bad and should probably fold
		else {
			confidence += (rand() % 5 + 1) + hand[0].value + hand[1].value;
		}
	}

	else {
		// Do stuff based off the hand plus community cards

		// During the flop..
		if(communityHand.size() == 3)
		{
			for(int i = 0; i < 3; ++i)
			{
				// If the computer has a pair, copy the confidence function from before
				if(communityHand[i].value == hand[0].value || communityHand[i].value == hand[1].value)
				{
					confidence += (rand() % 11 + 10) + (1.5 * hand[0].value);
				}
				// If they have matching suits, copy from before
				else if(communityHand[i].suit == hand[0].suit || communityHand[i].suit == hand[1].suit)
				{
					confidence += (rand() % 6 + 5) + hand[0].value + hand[1].value;
				}
				// If they don't have matching suits and they don't haave a pair (or higher) 
				// then they only have a high card. 
				else
				{	// These values aren't necessarily representative of their highest cards.
					// We can justify this by saying it "adds to the randomness."
					confidence += (rand() % 11 + 5) + hand[0].value + hand[1].value 
				}
			}
		}
	}
	return takeAction(confidence, betToMatch);
}

int Computer::takeAction(int confidence, int betToMatch) {
	if (confidence >= 90) {
		return allIn();
	}
	else if (confidence >= 50) {
		if (confidence >= 75) {
			int amountToRaise = money - betToMatch;

		}
	}
}
