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
#include "Player.h"
#include "Table.cpp"

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
 * enough money, they go all-in.
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
 * they will go all-in. 
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
Card* Player::checkHand() const
{
	return *hand;
}

/*********************************************************
 * @brief Gives the player their hand for the turn
 ********************************************************/
void Player::getHand(Card* givenHand){
	hand = givenHand;
}

/*********************************************************
* @brief Returns the amount of money that the player has
********************************************************/
<<<<<<< HEAD
void Player::setBigBlind(bool isBig) {
	isBigBlind = isBig;
=======
int Player::getMoney(){
	return money;
>>>>>>> cd8e44001e8e1eba59f44a1280e626aa94696c97
}

/*********************************************************
* @brief Set the players hand to NULL; This means the player does not
* have a hand.
********************************************************/
void Player::loseHand(){
	hand = 0;
	return;
}

/*********************************************************
* @brief Returns the player's name
********************************************************/
std::string Player::getName(){
	return name;
}

/*********************************************************
* @brief Sets the players score; Useful for Artifical
* intelligence but also needed to find winners.
********************************************************/
void Player::setScore(int score){
	currentScore = score;
	return;
}

/*********************************************************
* @brief Returns the players score
********************************************************/
double Player::getScore(){
	return currentScore;
}

/*********************************************************
* @brief Returns true if the player has folded
********************************************************/
double Player::hasFolded(){
	return hasFolded;
}
