#pragma once
#ifndef SCORE_H
#define SCORE_H

#include "CardAndDeck.h"
#include "Player.h"
#include <string>
#include <vector>

/**
* 	@file       Score.h
* 	@author(s)  Tim Mai (shiperl@ufl.edu)
* 	@date       4/19/2016
* 	@version    Final
* 	@brief      COP3503 Project, Texas Hold'em
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


/********************************************************************************
* SCORE FILE																	*
* If a vector of players' hands needs to be scored, call playerScorer and pass	*
* the vector of players and the community hand array.				*
*										*
* If a winner needs to be determined (or if there is a tie) among a vector of	*
* players call determineVectorWinner and pass the vector of players (assumed to	*
* be scored already with playerScorer) and the community hand array.		*
*										*
* If an individual player's hand needs to be scored, call score and pass the	*
* player's cards in an array and the community hand array.			*
*																				*
* If the community hand is not complete with five cards, a player's hand can	*
* still be scored using only the available cards. Declare the empty cards in	*
* the community hand as 0s (0 of spades).					*
*										*
********************************************************************************/


/*Default arrays to 0s*/
void defaultArray(Card array[], const int size);



/*Combine the Community Hand and Player's Hand into one array*/
void combiner(Card holder[], const Card handCommunity[], const Card handPlayer[]);


/* Organize card values in a card array from lowest to highest.
** Execute after the community hand and player hand has been combined
*/
void organizeLowToHigh(Card array[]);



/*Organize double values in a double array from lowest to highest*/
void organizeLowToHigh(double array[], int size);



/*Check for multiples*/
void multipleChecker(const Card holder[], Card multiple1[], Card multiple2[], 
	Card multiple3[], int & sizeMultiple1, int & sizeMultiple2, int & sizeMultiple3);



/*Organize the cards into their corresponding suits*/
void suitOrganizer(const Card holder[], Card suit[], int & sizeSuit, char charSuit);



/*Find the intRank and decimal value of a score*/
void determineRankValues(const double rank, int & intRank, int & decimal);



/* Rank the hand of the player once the community and player hand have
** been combined and organized, suits have been organized, and multiples have been found.
** Ranker does the actual scoring/ranking of the hand.
*/
double ranker(const int & sizeSuit, const int & sizeMultiple1, const int & sizeMultiple2,
	const int & sizeMultiple3, const Card suit[], const Card multiple1[],
	const Card multiple2[], const Card multiple3[], const Card holder[]);



/*Score function - calls other functions to score the hand*/
double score(const Card handPlayer[], const Card handCommunity[]);



/* In the event a tie is reached, kicker cards must be used.
** If kicker cards are the same to that of another player, the pot is split.
*/
Card* kicker(const Card handPlayer[], const Card handCommunity[], const int intScore, int decimal);




/*Compare the kickers of two players*/
int compareKickers(const Card kicker1[], const Card kicker2[]);



/*Score a vector of player's hands*/
void playerScorer(std::vector<Player*> players, const Card handCommunity[]);



/*Determine winner (or if there is a tie) between all the players (instead of two - see determineWinner)*/
std::vector<Player*> determineWinnerVector(const std::vector<Player*> players, const Card handCommunity[]);


#endif 
