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
#include "CardAndDeck.h"
#include "Player.h"
#include "math.h"
#include "Score.h"



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
		int numberOfPlayers; //This is that number of players that can be at the table, not the amount of players remaining at the the table
		int gameSpeed;
		int smallBlindAmount;
		
		int sBlindInd;
		int bBlindInd;
		int buttonInd;
		
		int numPlayersInPlay;
		
	public:
       
        //void print_computer(bool ifFold, int betAmount);
        /*print computer would need to take in an action.
         This would be fold, bet, call, check, raise
         */
    
		void game();
		bool gameOver(); //Return true if there is only one player with money left
		
		void incrementSmallBlind(); //increments the small blind by some factor known as 'gamespeed'
		int getSmallBlindAmount(); //Returns the small Blind Amount

		void newRound(); //Resets all table values for a new round of Poker
		void distributePot(std::vector<Card> communityHand, std::vector<int> pot, int numPlayersFolded); //potential errorQQ42
    
        void print_table(std::vector<Player*> players, int roundNumber, int potsize, std::vector<Card> communityHand);
        void print_computer();
        void print_river(int roundNumber, std::vector<Card> communityHand);
		
		void print_player(Player* player);
        void print_allin(Player * player);
        void allfold_win(Player * player);
        void split_pot(std::vector<Player*> players, int moneyBeforeSplit[]);
        void waiting_is_fun();
    
		
		//Table constructor
		Table(std::vector<Player*> players, int smallBlindAmount, int gameSpeed);
		~Table();
};


#endif
