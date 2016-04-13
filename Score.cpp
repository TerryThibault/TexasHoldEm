
#include <iostream>
#include <string>
#include <vector>




//The next segments that are commented out have been copy pastad from other files

/*class Table
{
private:
	Deck Deck;
	int pot; //Maybe a 2d Array; With strings? Maybe a Pot object and then a 1D Array	
	std::vector<Person> people; //A vector Person Objects; For input logic

public:
	void turn();
	void createNewPot(); // Creates a new pot to deal with extraneous conditions
	void addMoney(int amount); // Adds bet amount to pot
	void drawCard(); // Draws card from the Deck object
	void resetDeck(); // Declares a new Deck object
	void distributePot(); //Distributes the money in pot to the appropriate players	
};

/*********************************************************
* @brief The Deck object manages the cards in a deck.
********************************************************/

/*class Deck
{
private:
	std::vector<Card> Cards(52);
	// Note: the syntax for assigning elements of the vector is the
	// same as assigning elements to an array. 	Deck[0] = etc..

public:
	void shuffleDeck();
	Deck(); //Constructor
	~Deck(); //Deconstructor

};*/

/*********************************************************
* @brief The Card object manages the values of the cards.
********************************************************/

struct Card //These values will only be accessable by the deck, no need to 'hide' them
{
	char suit; // 'd' = diamonds, 'h' = hearts, 'c' = clubs; 's' = spades
	int value; // Allow jack to be 11, Queen 12, King 13, Ace 14 or 1. (Ace should equal 14 for scoring purpose -- Tim)
};

/*class Person
{
private:
	Card[] hand;
	int money;
	bool bigBlind;
	bool smallBlind;
	bool canCheck;
	bool myTurn;
	std::string name;

public:
	bool HasEnoughFunds(int bet); // Checks to see if the player has enough funds to match the pervious bet
	bool addMoney(int amount); // If the player wins a hand
	int bet(int amount);
	void call();
	bool check(); // Returns false if check option is not available
	int raise(int amount);
	void passBlind(); // Pass Big Blind to the next player
	void endTurn();
	void turn();
};*/


//Work in progress organizer
void organizeLowToHigh(Card * holder[], Card & temp)
{
	//Order values from lowest value to highest
	for (int end = 6; end >= 1; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (holder[i]->value > holder[i + 1]->value)
			{
				temp = *holder[i];
				holder[i] = holder[i + 1];
				holder[i + 1] = &temp;
			}
		}
	}
}

double score(Card handPlayer[], Card handCommunity[])
{
	//Work in progress scorer - might change to return a double
	/*Double will return a decimal - the number before the decimal (is there a formal term?) represents the ranking of the hand (Royal Flush, Four of a Kind, etc.
	The values after the decimal will represent the highest card of one's hand (in case there are two similar hands, different high card)*/

	/*Return Values*/
	/*Before Decimal Point*/
	/*Royal Flush - 10
	Straight Flush - 9
	....
	....
	High Card - 1*/


	/*After Decimal Point*/
	/*Corresponding value of the card
	Jack - 11
	Queen - 12
	King - 13
	Ace - 14*/


	Card temp;	//Temporarily hold the card
	Card * holder = new Card[7];	//Will combine handCommunity and handPlayer into one array of 7 cards
	Card * spades = new Card[7];	//Contain all the spade cards 
	Card * clubs = new Card[7];		//Contain all the clubs cards
	Card * diamonds = new Card[7];	//Contain all the diamonds cards
	Card * hearts = new Card[7];	//Contain all the hearts cards


	//Keep track of multiples (e.g. check to see if a four of a kind, full house, etc. is possible)
	//It is only possible to have a maximum of 3 multiple sets  (e.g. 2d 2s 3d 3s 4d 4s 5s -- 5s is not a multiple because there is no other 5)
	//Sizes are four because there are only four cards of one value

	Card * multiple1 = new Card[4];
	Card * multiple2 = new Card[4];
	Card * multiple3 = new Card[4];

	//Keep track of sizes
	int sizeSpades = 0, sizeClubs = 0, sizeDiamonds = 0, sizeHearts = 0;
	int sizeMultiple1 = 0, sizeMultiple2 = 0, sizeMultiple3 = 0;


	//Experimenting with vectors

	/*std::vector<Card> spades1;
	std::vector<Card> clubs1;
	std::vector<Card> diamonds1;
	std::vector<Card> hearts1;*/


	//Defaulting all created array values to 0s
	for (int i = 0; i < 7; i++)
	{
		holder[i].value = 0;
		holder[i].suit = 's';

		spades[i].value = 0;
		spades[i].suit = 's';

		clubs[i].value = 0;
		clubs[i].suit = 's';

		diamonds[i].value = 0;
		diamonds[i].suit = 's';

		hearts[i].value = 0;
		hearts[i].suit = 's';
	}

	for (int i = 0; i < 4; i++)
	{
		multiple1[i].value = 0;
		multiple1[i].suit = 's';

		multiple2[i].value = 0;
		multiple2[i].suit = 's';

		multiple3[i].value = 0;
		multiple3[i].suit = 's';
	}

	//Transferring and combining cards of the community and player
	for (int i = 0; i < 7; i++)
	{
		holder[i] = handCommunity[i];	

		if (i == 5)		
			holder[i] = handPlayer[0];

		else if (i == 6)
			holder[i] = handPlayer[1];

	}


	//Order values from lowest value to highest
	for (int end = 6; end >= 1; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (holder[i].value > holder[i + 1].value)
			{
				temp = holder[i];
				holder[i] = holder[i + 1];
				holder[i + 1] = temp;
			}
		}
	}


	int multipleMarker = 0;	//Keep track of where a multiple ends


	//Multiple checker -- Start from the highest card and go down
	//Multiple1
	for (int i = 6, j = 0; i >= 0; i--)
	{
		//If there is already values in the duplicate array
		if (j > 0)
		{
			if (multiple1[j].value == holder[i].value)
			{
				j++;						//Increase counter of how many multiple cards there are in the array (missing one number e.g. if j = 1, there are 2 multiple cards) -- note: could be replaced with sizeMultiple
				multiple1[j] = holder[i];
				sizeMultiple1++;
				multipleMarker = i;
			}
		}

		//If there are no values in the duplicate array
		else if (holder[i].value == holder[i - 1].value)
		{
			multiple1[j] = holder[i];
			j++;						//Traverse the array
			i--;
			multiple1[j] = holder[i];

			multipleMarker = i;			//Mark the location of where the next multiple array should start (in case there are only two multiples of one card in this array)
			sizeMultiple1 += 2;
		}
	}

	if (multiple1[0].value == 0)
	{
		//There are no multiples
	}


	//Multiple2
	else
	{
		for (int i = multipleMarker - 1, j = 0; i >= 0; i--)
		{
			if (j > 0)
			{
				if (multiple2[0].value == holder[i].value)
				{
					j++;
					multiple2[j] = holder[i];
					sizeMultiple2++;
					multipleMarker = i;
				}
			}

			else if (holder[i].value == holder[i - 1].value)
			{
				multiple2[j] = holder[i];
				i--;
				j++;
				multiple2[j] = holder[i];

				multipleMarker = i;
				sizeMultiple2 += 2;
			}
		}
	}

	if (multiple2[0].value == 0)
	{
		//There are no more multiples
	}

	if (sizeMultiple1 + sizeMultiple2 >= 6)
	{
		//There have been two sets of multiples found but there are no more possible multiples
	}

	//Multiple3
	else
	{
		{
			for (int i = multipleMarker - 1, j = 0; i >= 0; i--)
			{
				if (j > 0)
				{
					if (multiple3[j].value == holder[i].value)
					{
						j++;
						multiple3[j] = holder[i];
						sizeMultiple3++;
					}
				}

				else if (holder[i].value == holder[i - 1].value)
				{
					multiple3[j] = holder[i];
					i--;
					j++;
					multiple3[j] = holder[i];
					sizeMultiple3 += 2;
				}


			}
		}
	}




	//Multiple Checker -- OLD -- Went through the array starting from lowest value to highest -- seemed illogical
	/*for (int i = 0, j = 0; i < 7; i++)
	{
		//If there is already values in the duplicate array
		if (j > 0)
		{
			if (multiple1[j].value == holder[i].value)
			{
				j++;						//Increase counter of how many multiple cards there are in the array (missing one number e.g. if j = 1, there are 2 multiple cards) -- note: could be replaced with sizeMultiple
				multiple1[j] = holder[i];
				sizeMultiple1++;
				multipleMarker = i;
			}
		}

		//If there are no values in the duplicate array
		else if (holder[i].value == holder[i + 1].value)
		{
			multiple1[j] = holder[i];		
			j++;						//Traverse the array
			i++;
			multiple1[j] = holder[i];

			multipleMarker = i;			//Mark the location of where the next multiple array should start (in case there are only two multiples of one card in this array)
			sizeMultiple1 += 2;
		}
	}

	if (multiple1[0].value == 0)
	{
		//There are no multiples
	}


	//Multiple2
	else
	{
		for (int i = multipleMarker + 1, j = 0; i < 7; i++)
		{
			if (j > 0)
			{
				if (multiple2[0].value == holder[i].value)
				{
					j++;
					multiple2[j] = holder[i];
					sizeMultiple2++;
					multipleMarker = i;
				}
			}

			else if (holder[i].value == holder[i + 1].value)
			{
				multiple2[j] = holder[i];
				i++;
				j++;
				multiple2[j] = holder[i];
				multipleMarker = i;
				sizeMultiple2 += 2;
			}
		}
	}

	if (multiple2[0].value == 0)
	{
		//There are no more multiples
	}

	if (sizeMultiple1 + sizeMultiple2 >= 6)
	{
		//There have been two sets of multiples found but there are no more possible multiples
	}

	//Multiple3
	else
	{
		{
			for (int i = multipleMarker + 1, j = 0; i < 7; i++)
			{
				if (j > 0)
				{
					if (multiple3[j].value == holder[i].value)
					{
						j++;
						multiple3[j] = holder[i];
						sizeMultiple3++;
					}
				}

				else if (holder[i].value == holder[i + 1].value)
				{
					multiple3[j] = holder[i];
					i++;
					j++;
					multiple3[j] = holder[i];
					sizeMultiple3 += 2;
				}


			}
		}
	}*/

	//Find cards that are spades
	for (int i = 0, j = 0; i < 7; i++)
	{
		if (holder[i].suit == 's')
		{
			spades[j] = holder[i];
			j++;
		}

		if (i == 6)
			sizeSpades = j;
	}

	//Find cards that are clubs
	for (int i = 0, j = 0; i < 7; i++)
	{
		if (holder[i].suit == 'c')
		{
			clubs[j] = holder[i];
			j++;
		}

		if (i == 6)
			sizeClubs = j;
	}

	//Find cards that are diamonds
	for (int i = 0, j = 0; i < 7; i++)
	{
		if (holder[i].suit == 'd')
		{
			diamonds[j] = holder[i];
			j++;
		}

		if (i == 6)
			sizeDiamonds = j;
	}

	//Find cards that are hearts
	for (int i = 0, j = 0; i < 7; i++)
	{
		if (holder[i].suit == 'h')
		{
			hearts[j] = holder[i];
			j++;
		}

		if (i == 6)
			sizeHearts = j;
	}


	std::cout << std::endl;

	//Print corresponding values for checking
	for (int i = 0; i < 7; i++)
	{
		std::cout << "Card " << i + 1 << " is: " << holder[i].value << holder[i].suit << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < sizeSpades; i++)
	{
		std::cout << "Spade " << i + 1 << " is: " << spades[i].value << spades[i].suit << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < sizeClubs; i++)
	{
		std::cout << "Club " << i + 1 << " is: " << clubs[i].value << clubs[i].suit << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < sizeDiamonds; i++)
	{
		std::cout << "Diamonds " << i + 1 << " is: " << diamonds[i].value << diamonds[i].suit << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < sizeHearts; i++)
	{
		std::cout << "Heart " << i + 1 << " is: " << hearts[i].value << hearts[i].suit << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < sizeMultiple1; i++)
	{
		std::cout << "Multiple1 " << i + 1 << " is: " << multiple1[i].value << multiple1[i].suit << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < sizeMultiple2; i++)
	{
		std::cout << "Multiple2 " << i + 1 << " is: " << multiple2[i].value << multiple2[i].suit << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < sizeMultiple3; i++)
	{
		std::cout << "Multiple3 " << i + 1 << " is: " << multiple3[i].value << multiple3[i].suit << std::endl;
	}


	
	
	//If all suit sizes are less than 5, no flushes are possible


	//Card * run = new Card[7];

	int highCard = 0;		//Keep track of the high card

	//2 3 4 5 6 7 8

	//ROYAL FLUSH AND STRAIGHT FLUSH CHECKER
	if (sizeSpades >= 5)
	{
		int run = 0;		//Keep track of how long the run is

		for (int i = sizeSpades /*6*/; i >= 0; i--)		//Start from top (highest value) and go down
		{
			if (spades[i].value - 1 == spades[i-1].value)	//If the current card is consecutive (higher in value by 1) with the card behind it
			{
				if (run == 0)								//If the there is no run yet (or the run has restarted)
				{
					highCard = spades[i].value;				//Set highest card to the current value (for scoring purposes)
				}

				run++;										//Increase run size
			}

			else 											//A consecutive run was not found - reset the run counter to 0
				run = 0;

			if (run == 4)									//There are five cards found already - check for what the ranking is
			{

				if (highCard == 14)								//High card is an Ace so its lowest must be a Jack - Royal Flush
				{
					std::cout << "Royal Flush" << std::endl;
					return 10;								//Royal Flush - nothing can beat it so there is no decimal
				}

				else											//Highest card wasn't an ace so the ranking must be a Straight Flush
				{
					std::cout << "Straight Flush - High Card: " << highCard << std::endl;

					return 9 + (double)highCard / 100;	//Return the score -- decimal corresponds to the highest card value in the run

				}

				break;
			}
		}

	}
	
	//FOUR OF A KIND CHECKER
	if (sizeMultiple1 == 4)
	{
		highCard = multiple1[0].value;
		std::cout << "Four of a Kind: Four cards of " << highCard << std::endl;
		return 8 + (double)highCard / 100;
	}
	
	//FULL HOUSE CHECKER
	//Multiple 3 does not need to be checked because if there is a full house, it should already exists between Multiple 1 and Multiple 2
	//Do I even need Multiple 3?
	//Yes I do.

	if (sizeMultiple1 == 3 && sizeMultiple2 == 2) 
	{
		highCard = multiple1[0].value;
		std::cout << "Full House: " << highCard << " full of " << multiple2[0].value << "." << std::endl;
		return 7 + (double)highCard / 100;
	}

	else if (sizeMultiple1 == 3 && sizeMultiple2 == 3)
	{
		highCard = multiple1[0].value;
		std::cout << "Full House: " << highCard << " full of " << multiple2[0].value << "." << std::endl;
		return 7 + (double)highCard / 100;
	}

	else if (sizeMultiple1 == 2 && sizeMultiple2 == 3)
	{
		highCard = multiple2[0].value;
		std::cout << "Full House: " << highCard << " full of " << multiple1[0].value << "." << std::endl;
		return 7  + (double)highCard / 100;
	}

	else if (sizeMultiple1 == 2 && sizeMultiple3 == 3)	//Doesn't matter if sizeMultiple1 or sizeMultiple2 == 2 - for ranking purposes, only the triple cards matter
	{
		highCard = multiple3[0].value;
		std::cout << "Full House: " << highCard << " full of " << multiple1[0].value << "." << std::endl;
		return 7 + (double)highCard / 100;
	}




	//Mark - Did not test anything below yet
	//Already checked - I should check again later for correctness


	//FLUSH CHECKER

	if (sizeSpades >= 5)
	{
		highCard = spades[sizeSpades-1].value;
		std::cout << "Flush: High card " << highCard << std::endl;
		return 6 + (double)highCard / 100;
	}

	//SRAIGHT CHECKER
	int run = 0;

	for (int i = 6; i >= 0; i--)		//Start from top (highest value) and go down
	{
		if (holder[i].value - 1 == holder[i - 1].value)	//If the current card is consecutive (higher in value by 1) with the card behind it
		{
			if (run == 0)								//If the there is no run yet (or the run has restarted)
			{
				highCard = holder[i].value;				//Set highest card to the current value (for scoring purposes)
			}

			run++;										//Increase run size
		}

		else if (holder[i].value == holder[i - 1].value)
		{
			//Do nothing	-- In case a situation such as 7 6 5 5 4 3 2 is encountered
		}

		else 											//A consecutive run was not found - reset the run counter to 0
			run = 0;

		if (run == 4)									//There are five cards found already - check for what the ranking is
		{

			std::cout << "Straight - High Card: " << highCard << std::endl;
			return 5 + (double)highCard / 100;
			break;
		}

	}



	//THREE OF A KIND CHECKER
	if (sizeMultiple1 == 3)
	{
		highCard = multiple1[0].value;
		std::cout << "Triple " << highCard << std::endl;
		return 4 + (double)highCard / 100;
	}

	else if (sizeMultiple2 == 3)
	{
		highCard = multiple2[0].value;
		std::cout << "Triple " << highCard << std::endl;
		return 4 + (double)highCard / 100;
	}

	/*else if (sizeMultiple3 == 3)				//Use Multiple3 in case of the scenario: 10 10 9 9 8 8 8 -- FULL HOUSE though - go back to FULL HOUSE CHECKER TO RECODE
	{
		highCard = multiple3[0].value;
		std::cout << "Triple " << highCard << std::endl;
		//return 4 + (double)highCard / 100;
	}*/

	//TWO PAIR CHECKER
	if (sizeMultiple1 == 2 && sizeMultiple2 == 2)
	{
		highCard = multiple1[0].value;
		std::cout << "Two Pair: High Card " << highCard << std::endl;
		return 3 + (double)highCard / 100;
	}
	//Don't need to check sizeMultiple3, even if it is occupied, because Multiple1 and Multiple2 have the highest valued cards
	//If there are three cards in Multiple3, then a full house would have already been returned


	//NOTE FOR OTHER STUFF: Check rankings with two pair in the event both players have similar hands
	//Player1 - 5, 6
	//Player2 - 6, 3
	//Community - 6, 7, 7, 2, 9
	//Who wins? Tie?


	//PAIR CHECKER
	if (sizeMultiple1 == 2)
	{
		highCard = multiple1[0].value;
		std::cout << "Pair of " << highCard << std::endl;
		return 2 + (double)highCard / 100;
	}

	//HIGH CARD CHECKER
	highCard = holder[6].value;	//It's the highest card
	std::cout << "High Card: " << highCard << std::endl;
	return 1 + (double)highCard / 100;


	//NOTE: Some functions may be unnecessary, but it is currently in the works
	//Also looking to change some parts into methods to simplify

}

int main()
{
	Card * handCommunity = new Card[5];
	Card * handPlayer = new Card[2];

	handPlayer[0].value = 7;
	handPlayer[0].suit = 's';

	handPlayer[1].value = 6;
	handPlayer[1].suit = 'd';

	handCommunity[0].value = 5;
	handCommunity[0].suit = 's';

	handCommunity[1].value = 5;
	handCommunity[1].suit = 's';

	handCommunity[2].value = 4;
	handCommunity[2].suit = 's';

	handCommunity[3].value = 3;
	handCommunity[3].suit = 'c';

	handCommunity[4].value = 2;
	handCommunity[4].suit = 'd';

	/*std::cout << "Before Sorting: " << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << "Card " << i+1 << " is: " << handCommunity[i].value << handCommunity[i].suit << std::endl;
	}*/

	double rank = score(handPlayer, handCommunity);


	int intRank = (int)rank;

	double intermed = rank;
	intermed *= 100;

	int decimal = 0;
	decimal = int(intermed);
	decimal &= 100;

	//Above is overly complex in many lines
	//For some reason Windows believes that 507 % = 96 above
	//??????????????????????????
	//Need to recode to display correctly
	//Do I need to work on displaying the code? Maybe this is just for my own looking

	switch (intRank)
	{
	case 10:
		std::cout << "Royal Flush." << std::endl;
		break;

	case 9:
		std::cout << "Straight Flush. High Card: ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 8:
		std::cout << "Four of a Kind. Four ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 7:
		std::cout << "Full House. High Card: ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 6:
		std::cout << "Flush. High Card: ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 5:
		std::cout << "Straight. High Card: ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 4:
		std::cout << "Three of a Kind. Three ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 3:
		std::cout << "Two Pair. High Card: ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 2:
		std::cout << "One Pair. Pair of ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	case 1:
		std::cout << "No Pair. High Card: ";
		switch (decimal)
		{
		case 14:
			std::cout << "Ace \n";
			break;

		case 13:
			std::cout << "King \n";
			break;

		case 12:
			std::cout << "Queen \n";
			break;

		case 11:
			std::cout << "Jack \n";
			break;

		default:
			std::cout << decimal << std::endl;
			break;
		}
		break;

	}
	int k;		//Random int - no purpose except to check for a crash

	delete[] handCommunity;
	delete[] handPlayer;


	int j;
	std::cin >> j;

    return 0;
}

