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
 * @brief The Table class maintains all the required 
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
}

#endif
