/**
 * 	@file       main.cpp
 * 	@author     Terry Thibault (tlt@cise.ufl.edu)
 * 	@date       3/22/16
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

#include <iostream>
//#include "header.h"
using namespace std;

void intro_menu();
void start_game();
void end_game();


int main(int argc, char*argv[]){
		
    //FIRST INTRODUCTORY MENU
    intro_menu();
    start_game();
    
    
    
}





void intro_menu(){
    int num_players;
    
    // User inputs number of players
    cout << "** Welcome to Poker **" << endl;
    cout << "How many players are there?" << endl;
    do {
        cout << ">> ";
        cin >> num_players;
        if (!(num_players < 9 & num_players > 0) || !cin) {
            cout << "Your number of players is invalid. Try again!" << endl;
        }
    } while (!(num_players < 9 & num_players > 0));
    
    cout << "There are " << num_players << ". The game will begin!" << endl;
    
}


void start_game(){
    cout << num_players;
    
    
}