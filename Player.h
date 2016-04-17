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

#include <string>

class Player
{
private:
	Card *hand;	// The player's two cards
	int money;	// How much money the player has
	bool hasFolded;	// If the player has folded, then they cannot take any actions for the rest of a round
	std::string name;
	double currentScore; //What's the players score based off of the community pot and his hand

public:
	bool HasEnoughFunds(int bet); // Checks to see if the player has enough funds to match the pervious bet
	void addMoney(int amount); // If the player wins a hand
	int bet(int amount);
	int call(int prev_bet);
	bool check(); // Returns false if check option is not available
	
	int turn(int betToMatch); //Turn needs to return an integer amount that is equal to or greater than the 'betToMatch'
	//unless the player cannot afford to, then the player will be going 'all in';
	
	int getMoney(); //Accessor method that finds the amount of money that the player has

	Card *checkHand() const; //Checks what hand the player has
	void getHand(Card* givenHand); //Gives the player their hand 
	void loseHand(); //sets hand to 'null'

	//Score operations
	void setScore(double score);
	double getScore();
	
	std::string getName(); //Returns the players name
	
	bool playerHasFolded(); //Returns true if the player has folded;
};

// TODO: Create functions for the computer
Class Computer : public Player {

};

#endif
