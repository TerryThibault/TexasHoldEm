/**
 * 	@file       header.h
 * 	@author(s)  Alexander Rumak (alexrumak.ufl.edu)		
 * 	@date       4/17/2016
 * 	@version    1.0
 * 	@brief      COP3503 Project, Texas Hold'em
 *
 *
 * 	@section This file defines the card and deck objects, which are needed in the
 *	player.h file and the header.h file
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
 
 
#ifndef CARDANDDECK_H
#define CARDANDDECK_H
#include <vector>
 
/*********************************************************
 * @brief The Card object manages the values of the cards.
 ********************************************************/

struct Card //These values will only be accessable by the deck, no need to 'hide' them
{
	char suit; // 'd' = diamonds, 'h' = hearts, 'c' = clubs; 's' = spades
	int value; // Allow jack to be 11, Queen 12, King 13, Ace 14 or 1.
		
	Card();
	Card(char suit, int value);
};



/*********************************************************
 * @brief The Deck object manages the cards in a deck.
 ********************************************************/

class Deck
{
	private:
		std::vector<Card> cards;
		int numberOfCards;
		// Note: the syntax for assigning elements of the vector is the
		// same as assigning elements to an array. 	Deck[0] = etc..

	public:
		void shuffleDeck();
		Deck(); //Constructor
		~Deck(); //Deconstructor
		bool hasCards(); //Determines whether the deck is empty or not
		Card drawCard(int cardInd);
		
};

#endif
