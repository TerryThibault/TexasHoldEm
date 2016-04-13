
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

void score(Card handPlayer[], Card handCommunity[])
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

	//Multiple1
	for (int i = 0, j = 0; i < 7; i++)
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
				if (multiple2[j].value == holder[i].value)
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
				multiple3[j] = holder[i];
				multipleMarker = i;
				sizeMultiple2 += 2;
			}
		}
	}

	if (multiple2[0].value == 0)
	{
		//There are no more multiples
	}

	if (multipleMarker >= 6)
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
	}

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


	
	
	//If all sizes are less than 5, no flushes are possible



	//NOTE: Some functions may be unnecessary, but it is currently in the works
	//Also looking to change some parts into methods to simplify


}

int main()
{
	/*Card * player = new Card[2];
	player[0].suit = 'c';
	player[0].value = 12;*/
	Card * handCommunity = new Card[5];
	Card * handPlayer = new Card[2];

	handPlayer[0].value = 8;
	handPlayer[0].suit = 'd';

	handPlayer[1].value = 14;
	handPlayer[1].suit = 's';

	handCommunity[0].value = 12;
	handCommunity[0].suit = 'c';

	handCommunity[1].value = 5;
	handCommunity[1].suit = 'd';

	handCommunity[2].value = 7;
	handCommunity[2].suit = 'h';

	handCommunity[3].value = 5;
	handCommunity[3].suit = 's';

	handCommunity[4].value = 13;
	handCommunity[4].suit = 'd';

	std::cout << "Before Sorting: " << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << "Card " << i+1 << " is: " << handCommunity[i].value << handCommunity[i].suit << std::endl;
	}

	score(handPlayer, handCommunity);
	
	int k;		//Random int - no purpose except to check for a crash

	delete[] handCommunity;
	delete[] handPlayer;

	/*NOTE: For some reason, the program crashes around here sometimes. Sometimes it doesn't.*/



	int j;
	std::cin >> j;

    return 0;
}

