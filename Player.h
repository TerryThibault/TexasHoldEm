/**
* 	@file       Player.h
* 	@author(s)  Alexander Rumak (alexrumak.ufl.edu)
* 				Hugh Wu (wuhugh@ufl.edu)
		

* 	@date       4/15/16
* 	@version    1.0
* 	@brief      COP3503 Project, Texas Hold'em
*
*
* 	@section DESCRIPTION
*	This file contains the fields and methods associated with the Player class
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

#ifndef PLAYER_H
#define PLAYER_H

#include "CardAndDeck.h"
#include <string>
#include <vector>

class Player
{
private:
	std::string name; // The player's name they enter
	Card* hand;	// The player's two cards
	int money;	// How much money the player has
	bool hasFolded;	// If the player has folded, then they cannot take any actions for the rest of a round
	bool hasAllIn; // If the player has all-in'd, then their money should be zero and they cannot make any more bets
	double currentScore; //What's the players score based off of the community pot and his hand

public:
	Player(int money, std::string name); // Constructor for the player
	~Player(); // Deconstructor for the player
	std::string getName(); //Returns the players name
	bool HasEnoughFunds(int bet); // Checks to see if the player has enough funds to match the pervious bet
	void addMoney(int amount); // If the player wins a hand, they get money added to their funds
	int getMoney(); //Accessor method that finds the amount of money that the player has
	int raise(int amount, int prev_bet); // This is the equivalent of raising the bet
	int call(int prev_bet); // This option allows the player to match the current bet amount
	int allIn(); // This takes all the player's money and adds it to the pot
	bool playerHasFolded(); //Returns true if the player has folded;
	bool playerAllIn(); //Returns whether the player has all-ined
	int forceBet(int blindCost);

	// Turn returns an int equal to the amount the player is adding to the pot.
	// For human players, this presents them with a menu and they can choose their action
	int turn(int betToMatch, int currentContribution, int potSize, std::vector<Card> communityHand)); 

	// Hand functions
	Card*checkHand() const; //Checks what hand the player has
	void giveHand(Card* givenHand); //Gives the player their hand
	void loseHand(); //sets hand to 'null'

	//Score operations
	void setScore(double score);
	double getScore();
	
	void resetPlayer(); //Resets the player for a new hand


// TODO: Create functions for the computer
class Computer : public Player {
	private:
		int confidence; // How likely the computer will continue to bet with their hand

	public:
		Computer(int money, std::string name);
		int turn(int betToMatch, int currentContribution, int potSize, std::vector<Card> communityHand);
		int takeAction(int confidence, int betToMatch)
};

#endif
