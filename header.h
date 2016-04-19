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
#include <algorithm> //for std::random_shuffle
#include <ctime> //for std::time
#include <cstdlib> //std::rand, std::srand
#include "math.h"
#include "CardAndDeck.h"
#include "Player.h"



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
		int gameSpeed;
		int smallBlindAmount;
		
	public:
        //void print_player();
        //void print_computer(bool ifFold, int betAmount);
        /*print computer would need to take in an action.
         This would be fold, bet, call, check, raise
         */
    
		void game();
		void distributePot(); //Distributes the money in pot to the appropriate players
		bool gameOver(); //Return true if there is only one player with money left
		bool humanPlayersLost(); //Return true if all human players have 0 money
		
		void incrementSmallBlind(); //increments the small blind by some factor known as 'gamespeed'
		int getSmallBlindAmount(); //Returns the small Blind Amount

		void newRound(); //Resets all table values for a new round of Poker
		void distributePot(std::vector<Card> communityHand, int *pot, int numPlayersFolded);
    
        void print_table(std::vector<Player*> players, int roundNumber, int potsize);
        void print_computer();
        void print_river(int roundNumber);
        void print_allin(Player player);
        void allfold_win(Player player);
        void split_pot(players[], moneyBeforeSplit[]);
        void waiting_is_fun();
    
		
		//Table constructor
		Table(std::vector<Player*> players, int smallBlindAmount, int gameSpeed);
		~Table();
};


#endif
