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


/*********************************************************
* @brief Returns true if the player has folded
*********************************************************/
bool Player::playerHasFolded() {
	return hasFolded;
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
		std::cout << "1. Check \n2. Raise \n3. Fold\n";
		std::string input; 
		std::cin >> input;
		
		//If they didn't input a valid option, fail.
		if(!(input == "1" || input == "2" || input == "3"))
		{
			std::cout << "Invalid parameter. Please enter a valid option.\n" 
			turn(betToMatch, currentContribution, potSize, communityHand);
		}

		if(input == "1")
		{
			std::cout << "Checked.\n";
			return 0;
		}
		
		if(input == "2")
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
		
		if(input == "3")
		{
			this->hasFolded = true;
			std::cout << "Fold successful.\n";
			return 0;
		}
	}
	
	//Assuming betToMatch > 0. 
	else
	{
		std::cout << "1. Call \n2. Raise \n3. Fold\n;
		std::string input;
		std::cin >> input;

		//Fail for invalid options
		if (!(input == "1" || input == "2" || input == "3"))
		{
			std::cout << "Invalid parameter. Please enter a valid option.\n"
				turn(betToMatch, currentContribution, potSize, communityhand);
		}

		if (input == "1")
		{
			if (this->HasEnoughFunds(betToMatch))
			{
				std::cout << "Called.\n"
				return call(betToMatch);
			}
			std::cout << "Not enough funds to perform that action.\n"
			turn(betToMatch, currentContribution, potSize, communityHand);
		}
		if (input == "2")
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
		if (input == "3")
		{
			this->hasFolded = true;
			std::cout << "Fold successful.\n";
			return 0;
		}
	}
}

Computer::Computer(int money, std::string ) : Player(money, name) {
	// Everytime a new computer player is created, their confidence levels are different
	confidence = rand() % 40 + 1;
}

/*******************************************************
* @brief This function deals with how the computer
* decides their actions.
**********************************************************/
int Computer::turn(int betToMatch, int currentContribution, int potSize, std::vector<Card> communityHand){
	// availableCards is a vector that contains the two cards that were dealt plus the community cards
	std::vector<Card> availableCards; 
	availableCards.push_back(hand[0]);
	availableCards.push_back(hand[1]);
	availableCards.insert(availableCards.end(), communityHand.begin(), communityHand.end());
	
	// When the computer only has their two cards
	if (availableCards.size() = 2) {
		// If the computer gets a pair, then it will greatly increase their confidence
		if (availableCards[0].rank == availableCards[1].rank) {
			confidence += 4 * availableCards[0].rank;
		}
		else {

		}
	}
}

