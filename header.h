/**
 * 	@file       header.h
 * 	@author(s)  Terry Thibault (tlt@cise.ufl.edu)
 * 				Alexander Rumak (alexrumak.ufl.edu)
 * 	@date       3/26/16
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

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include "math.h"
#include "Player.cpp"
#include "Score.cpp"
#include "Table.cpp"


/*********************************************************
 * @brief The Table object maintains all the required 
 * information that is public domain (That can be accessed
 * by everyone playing). The Table class also maintains
 * the deck of cards.
 ********************************************************/

class Table
{
	private:
		Deck* tableDeck; //Thinking about it; not sure if this 'data' field is necessary;
		std::vector<Player*> players; //A vector Player Objects; For input logic
		int numberOfPlayers;
		int bigBlindAmount = 10;
		int smallBlindAmount = 5;
	public:
		void turn();
		void createNewPot(); // Creates a new pot to deal with extraneous conditions
		void addMoney(int amount); // Adds bet amount to pot
		///void drawCard(); // Draws card from the Deck object
		void resetDeck(); // Declares a new Deck object
		void distributePot(); //Distributes the money in pot to the appropriate 	players
		bool gameOver();
		Table();
		~Table();
};

/*********************************************************
 * @brief The Deck object manages the cards in a deck.
 ********************************************************/

class Deck
{
	private:
		std::vector<Card*> Cards;
		int numberOfCards = 52;
		// Note: the syntax for assigning elements of the vector is the
		// same as assigning elements to an array. 	Deck[0] = etc..

	public:
		void shuffleDeck();
		Deck(); //Constructor
		~Deck(); //Deconstructor
		bool hasCards(); //Determines whether the deck is empty or not
		Card* drawCard();
		
};

/*********************************************************
 * @brief The Card object manages the values of the cards.
 ********************************************************/

struct Card //These values will only be accessable by the deck, no need to 'hide' them
{
	char suit; // 'd' = diamonds, 'h' = hearts, 'c' = clubs; 's' = spades
	int value; // Allow jack to be 11, Queen 12, King 13, Ace 14 or 1.
		
	Card(char suit; int value);
};
#endif
