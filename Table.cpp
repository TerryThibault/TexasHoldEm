#include "TexasHoldem.h"

//Constructs A table with all players in it. This works for all human players and ai players
Table::Table(Person[] people) : people(people){
	
}

Table::turn(){
	
	
	
}

Card::Card(char suit; int value) : suit(suit), value(value){
	
}

Deck::Deck (){
	char suit[] = {'d', 'h', 'c' ,'s'}; //Used for initalization of the deck
	int counter = 0;
	
	//initalizes the deck with c_suit and c_val
	for(int c_suit = 0; c_suit != 4; ++c_suit){
		for (int c_val = 2; c_val != 15; ++c_val){
			this->Cards[counter] = new Card(suit[c_suit], c_val);
			counter++;
		}
	}
}
