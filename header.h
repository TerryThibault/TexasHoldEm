/**
 * 	@file       main.cpp
 * 	@author     Terry Thibault (tlt@cise.ufl.edu)
 * 	@date       3/26/16
 * 	@version    1.0
 *
 * 	@brief      COP3503 Project, Texas Hold'em
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

/*********************************************************
 * @brief The Table object maintains all the required 
 * information that is public domain (That can be accessed
 * by everyone playing). The Table class also maintains
 * the deck of cards.
 *
 ********************************************************/

class Table
{
	private:
		Deck Deck;
		int[] pot;	
		std::string[] people;
	
	public:
		createNewPot(); // Creates a new pot to deal with extraneous conditions
		addMoney(int amount); // Adds bet amount to pot
		drawCard(); // Draws card from the Deck object
		resetDeck(); // Declares a new Deck object
		distributePot(); //Distributes the money in pot to the appropriate players	
};

/*********************************************************
 * @brief The Deck object manages the cards in a deck.
 *
 ********************************************************/

class Deck
		std::vector<Card> Deck(52);
		// Note: the syntax for assigning elements of the vector is the
		// same as assigning elements to an array. 	Deck[0] = etc..

	public:
		shuffleDeck();
		createDeck();
};

/*********************************************************
 * @brief The Card object manages the values of the cards.
 *
 ********************************************************/

	private:
class Card
{
	private:
		char suit;
		int value; // Allow jack to be 11, Queen 12, King 13, Ace 14 or 1.	
};
#endif
