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
 * @brief This function is called by the table. Simply 
 * subtracts from the player cash and tells the table
 * how much to add to the pot. If the player does not have
 * enough money, the program will loop for an amount that 
 * is equal to or less than their funds
 ********************************************************/
int Player::bet(int amount)
{
	if(HasEnoughFunds(amount))
	{
		money -= amount;
		return amount;
	}
	int temp = money;
	money = 0;
	return temp;
}

/*********************************************************
 * @brief This function's input is the largest previous 
 * bet. If the player does not have enough money to call,
 * the player will go all-in. 
 ********************************************************/
int Player::call(int prev_bet)
{
	if(HasEnoughFunds(prev_bet))
	{
		money -= prev_bet;
		return prev_bet;
	}
	int temp = money;
	money = 0;
	return temp;
}
/*********************************************************
 * @brief Returns a pointer to the player's hand.
 ********************************************************/
Card Player::checkHand() const
{
	return *hand;
}

/*********************************************************
 * @brief Gives the player their hand for the turn
 ********************************************************/
void Player::giveHand(Card* givenHand){
	hand = givenHand;
}

/*********************************************************
* @brief Returns the amount of money that the player has
*********************************************************/
int Player::getMoney(){
	return money;
}

/*********************************************************
* @brief Set the players hand to NULL; This means the player does not
* have a hand.
*********************************************************/
void Player::loseHand(){
	hand = 0;
	return;
}

/*********************************************************
* @brief Returns the player's name
*********************************************************/
std::string Player::getName(){
	return name;
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
* @brief Returns true if the player has folded
*********************************************************/
bool Player::playerHasFolded(){
	return hasFolded;
}

/*********************************************************
* @brief Resets player values to their initial states
*********************************************************/
void Player::resetPlayer(){
	hasFolded = false;
	currentScore = 0;
	hand = 0;
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
	//std::cout << "The amount you currently have in the pot is "  << 
	
	//If the current bet is 0, checking is an option. Yes, calling and checking are the same in this situation.
	if(betToMatch == 0)
	{
		std::cout << "1. Check \n2. Raise \n3. Fold\n";
		std::string input; 
		std::cin >> input;
		
		//If they didn't input a valid option, fail.
		if(!(input == "1" || input == "2" || input == "3"))
		{
			std::cout << "Invalid parameter. Please enter a valid option." 
			turn(betToMatch);
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
			
		}
	}
}
