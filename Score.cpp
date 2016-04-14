
#include <iostream>
#include <string>


//Copying over the struct

struct Card //These values will only be accessable by the deck, no need to 'hide' them
{
	char suit; // 'd' = diamonds, 'h' = hearts, 'c' = clubs; 's' = spades
	int value; // Allow jack to be 11, Queen 12, King 13, Ace 14 or 1. (Ace should equal 14 for scoring purpose -- Tim)
};


//Organize values in the holder from lowest to highest
void organizeLowToHigh(Card holder[], Card & temp)
{
	//Order values from lowest value to highest

	for (int end = 6; end >= 1; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (holder[i].value > holder[i + 1].value)		//Current value is greater than the next
			{
				temp = holder[i];				//Set current value equal to temp
				holder[i] = holder[i + 1];		//Set current value equal to the next one
				holder[i + 1] = temp;			//Set next value equal to temp 
			}
		}
	}
}



//Check for multiples
void multipleChecker(const Card holder[], Card multiple1[], Card multiple2[], Card multiple3[], int & sizeMultiple1, int & sizeMultiple2, int & sizeMultiple3)
{
	//Multiple checker -- Start from the highest card and go down

	int multipleMarker = 0;	//Keep track of where a multiple ends so that the next multiple array can start from that positions

	//Multiple1
	for (int i = 6, j = 0; i >= 0; i--)
	{
		//If there are already values in the duplicate array
		if (j > 0)
		{
			if (multiple1[j].value == holder[i].value)		//Check to see if the current holder value is the same as the multiple value
			{
				j++;						//Increase counter of how many multiple cards there are in the array (missing one number e.g. if j = 1, there are 2 multiple cards) -- note: could be replaced with sizeMultiple
				multiple1[j] = holder[i];
				sizeMultiple1++;
				multipleMarker = i;
			}
		}

		//If there are no values in the duplicate array
		else if (holder[i].value == holder[i - 1].value)	//The current value equals the value behind it
		{
			multiple1[j] = holder[i];	

			j++;						//Traverse the multiple array
			i--;						//Traverse the holder array (moving down - look for multiples of highest value first)

			multiple1[j] = holder[i];	

			multipleMarker = i;			//Mark the location of where the next multiple array should start (in case there are only two multiples of one card in this array)
			sizeMultiple1 += 2;			//There already are two values in the multiple, so increment the size by two
		}
	}

	if (multiple1[0].value == 0)
	{
		return;			//There are no multiples
	}


	//Multiple2
	//Same comments as the multiple1
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

	if (multiple2[0].value == 0 || sizeMultiple1 + sizeMultiple2 >= 6)
	{
		return;			//There are no more multiples or there are no more possible multiples (because there is one card left - can't be a multiple)
	}

	//Multiple3
	//Same commments as multiple1
	//multipleMarker no longer needs to be incremented because it will not be used after the else statement
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
}



//Organize the cards into their corresponding suits
void suitOrganizer(const Card holder[], Card suit[], int & sizeSuit, char suitChar)
{
	//Find cards of the suit
	for (int i = 0, j = 0; i < 7; i++)
	{
		if (holder[i].suit == suitChar)
		{
			suit[j] = holder[i];
			j++;						//Traverse the suit array
		}

		if (i == 6)	
			sizeSuit = j;				//When the end of the holder array is reached, then set sizeSuit to j
	}

}



//Rank the hand of the player once the community and player hand have been combined and organized, suits have been organized, and multiples have been found
//Does the actual scoring/ranking of the hand
double ranker(const int & sizeSuit, const int & sizeMultiple1, const int & sizeMultiple2, 
	const int & sizeMultiple3, const Card suit[], const Card multiple1[], 
	const Card multiple2[], const Card multiple3[], const Card holder[])
{
	int highCard = 0;		//Keep track of the high card

	//ROYAL FLUSH AND STRAIGHT FLUSH CHECKER
	if (sizeSuit >= 5)
	{
		int run = 0;		//Keep track of how long the run is

		for (int i = sizeSuit; i >= 0; i--)					//Start from top (highest value) and go down
		{
			if (suit[i].value - 1 == suit[i - 1].value)		//If the current card is consecutive (higher in value by 1) with the card behind it
			{
				if (run == 0)								//If the there is no run yet (or the run has restarted
					highCard = suit[i].value;				//Set highest card to the current value (for scoring purposes)

				run++;										//Increase run size
			}

			else 											//A consecutive run was not found - reset the run counter to 0
				run = 0;

			if (run == 4)									//There are five cards found already - check for what the score is
			{

				if (highCard == 14)								//High card is an Ace so its lowest must be a Jack - Royal Flush
					return 10.0;								//Royal Flush - nothing can beat it so the tenths place is zero
				

				else											//Highest card wasn't an ace so the ranking must be a Straight Flush
					return 9 + (double)highCard / 100;	//Return the score -- decimal corresponds to the highest card value in the run

			}
		}

	}

	//FOUR OF A KIND CHECKER
	if (sizeMultiple1 == 4)
	{
		highCard = multiple1[0].value;
		return 8 + (double)highCard / 100;
	}

	else if (sizeMultiple2 == 4)
	{
		highCard = multiple2[0].value;
		return 8 + (double)highCard / 100;
	}

	//No need to check Multiple3 because it should not have four cards 
	//e.g. 2 2 3 3 4 4 4
	//Maximum it should have is only 3 cards


	//FULL HOUSE CHECKER
	//High card will be from the multiple with 3
	//If multiple1 and multiple2 have 3 cards, then the high card will be from multiple1

	if (sizeMultiple1 == 3 && sizeMultiple2 == 2)		
	{
		highCard = multiple1[0].value;
		return 7 + (double)highCard / 100;
	}

	else if (sizeMultiple1 == 3 && sizeMultiple2 == 3)
	{
		highCard = multiple1[0].value;
		return 7 + (double)highCard / 100;
	}

	else if (sizeMultiple1 == 2 && sizeMultiple2 == 3)
	{
		highCard = multiple2[0].value;
		return 7 + (double)highCard / 100;
	}

	else if (sizeMultiple1 == 2 && sizeMultiple3 == 3)	//Doesn't matter if sizeMultiple1 or sizeMultiple2 == 2 - for ranking purposes, only the triple cards matter
	{
		highCard = multiple3[0].value;
		return 7 + (double)highCard / 100;
	}


	//FLUSH CHECKER
	if (sizeSuit >= 5)
	{
		highCard = suit[sizeSuit - 1].value;
		return 6 + (double)highCard / 100;
	}

	//SRAIGHT CHECKER
	int run = 0;

	for (int i = 6; i >= 0; i--)		//Start from top (highest value) and go down
	{
		if (holder[i].value - 1 == holder[i - 1].value)	//If the current card is consecutive (higher in value by 1) with the card behind it
		{
			if (run == 0)								//If the there is no run yet (or the run has restarted)
				highCard = holder[i].value;				//Set highest card to the current value (for scoring purposes)

			run++;										//Increase run size
		}

		else if (holder[i].value == holder[i - 1].value)
		{
			//Do nothing	-- In case a situation such as 7 6 5 5 4 3 2 is encountered
		}

		else 											//A consecutive run was not found - reset the run counter to 0
			run = 0;

		if (run == 4)									//There are five cards found already - check for what the ranking is
			return 5 + (double)highCard / 100;

	}



	//THREE OF A KIND CHECKER
	if (sizeMultiple1 == 3)
	{
		highCard = multiple1[0].value;
		return 4 + (double)highCard / 100;
	}

	else if (sizeMultiple2 == 3)
	{
		highCard = multiple2[0].value;
		return 4 + (double)highCard / 100;
	}
	
	/*Multiple3 does not need to be checked because if it has 3 cards, then there should be a full house already*/


	//TWO PAIR CHECKER
	if (sizeMultiple1 == 2 && sizeMultiple2 == 2)
	{
		highCard = multiple1[0].value;
		return 3 + (double)highCard / 100;
	}

	//It is not necessary to check sizeMultiple3, even if it is occupied, because Multiple1 and Multiple2 have the highest valued cards
	//If there are three cards in Multiple3, then a full house would have already been returned
	//If there are three or four cards in multiple1, then a three of a kind or four of a kind would have already been returned


	//NOTE FOR OTHER STUFF: Check rankings with two pair in the event both players have similar hands
	//Player1 - 5, 6
	//Player2 - 6, 3
	//Community - 6, 7, 7, 2, 9
	//Who wins? Tie?


	//PAIR CHECKER
	if (sizeMultiple1 == 2)
	{
		highCard = multiple1[0].value;
		return 2 + (double)highCard / 100;
	}

	/*It is not necessary to check multiple2 and multiple3 because multiple1 will have the highest valued pair if there is a pair */

	//HIGH CARD CHECKER
	highCard = holder[6].value;	//It's the highest card
	return 1 + (double)highCard / 100;
}



//Score function - calls other functions to score the hand
double score(const Card handPlayer[], const Card handCommunity[])
{
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
	2 - .02
	3 -	.03
	...
	...
	Jack - .11
	Queen - .12
	King - .13
	Ace - .14*/

	/*Exampe: return value 8.13 - Four of a Kind - Four Kings*/





	Card temp;	//Temporarily hold the card


	Card * holder = new Card[7];	//Will combine handCommunity and handPlayer into one array of 7 cards
	Card * spades = new Card[7];	//Contain all the spade cards 
	Card * clubs = new Card[7];		//Contain all the clubs cards
	Card * diamonds = new Card[7];	//Contain all the diamonds cards
	Card * hearts = new Card[7];	//Contain all the hearts cards
	//All above are ordered lowest to highest


	//Keep track of multiples (e.g. check to see if a four of a kind, full house, etc. is possible)
	//It is only possible to have a maximum of 3 multiple sets  (e.g. 2d 2s 3d 3s 4d 4s 5s -- 5s is not a multiple because there is no other 5)
	//Sizes are four because there are only four cards of one value
	//Ordered from highest to lowest

	Card * multiple1 = new Card[4];
	Card * multiple2 = new Card[4];
	Card * multiple3 = new Card[4];

	//Keep track of sizes
	int sizeSpades = 0, sizeClubs = 0, sizeDiamonds = 0, sizeHearts = 0;
	int sizeMultiple1 = 0, sizeMultiple2 = 0, sizeMultiple3 = 0;


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

	//Combining cards of the community and player into holder
	for (int i = 0; i < 7; i++)
	{
		holder[i] = handCommunity[i];	

		if (i == 5)		
			holder[i] = handPlayer[0];

		else if (i == 6)
			holder[i] = handPlayer[1];

	}

	//Organize holder from lowest value to highest
	organizeLowToHigh(holder, temp);


	//Check for multiples of a card value - order the multiples from highest to lowest
	multipleChecker(holder, multiple1, multiple2, multiple3, sizeMultiple1, sizeMultiple2, sizeMultiple3);

	//Organize all of the cards into their respective suits - order from lowest to highest
	suitOrganizer(holder, spades, sizeSpades, 's');
	suitOrganizer(holder, clubs, sizeClubs, 'c');
	suitOrganizer(holder, diamonds, sizeDiamonds, 'd');
	suitOrganizer(holder, hearts, sizeHearts, 'h');

	//Print corresponding values for checking
	/*for (int i = 0; i < 7; i++)
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
	}*/


	double spadesScore = ranker(sizeSpades, sizeMultiple1, sizeMultiple2, sizeMultiple3, spades, multiple1, multiple2, multiple3, holder);
	double clubsScore = ranker(sizeClubs, sizeMultiple1, sizeMultiple2, sizeMultiple3, clubs, multiple1, multiple2, multiple3, holder);
	double diamondsScore = ranker(sizeDiamonds, sizeMultiple1, sizeMultiple2, sizeMultiple3, diamonds, multiple1, multiple2, multiple3, holder);
	double heartsScore = ranker(sizeHearts, sizeMultiple1, sizeMultiple2, sizeMultiple3, hearts, multiple1, multiple2, multiple3, holder);

	

	if (spadesScore > clubsScore && spadesScore > diamondsScore && spadesScore > heartsScore)			//If spadesScore is the highest, return it
		return spadesScore;

	else if (clubsScore > spadesScore && clubsScore > diamondsScore && clubsScore > heartsScore)		//If clubsScore is the highest, return it
		return clubsScore;

	else if (diamondsScore > spadesScore && diamondsScore > clubsScore && diamondsScore > heartsScore)	//If diamondScore is the highest, return it
		return diamondsScore;

	else if (heartsScore > spadesScore && heartsScore > clubsScore && heartsScore > diamondsScore)		//If heartsScore is the highest, return it
		return heartsScore;

	else			//All score are the same - doesn't matter which one to return
		return spadesScore;		


	//NOTE FOR OTHER STUFF: Check rankings with two pair in the event both players have similar hands
	//Player1 - 5, 6
	//Player2 - 6, 3
	//Community - 6, 7, 7, 2, 9
	//Who wins? Tie?

}



int main()
{
	//Creating hypothetical hands

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


	//Score the hand
	double rank = score(handPlayer, handCommunity);

	//Convert the double into an int to find the hand ranking
	int intRank = (int)rank;

	//Hold the double value of rank
	double intermed = rank;

	//Multiply double value by 100 to shift the decimal place by two to the right (get rid of decimal value)
	intermed *= 100;

	//Convert the shifted value to an interger
	int	decimal = int(intermed); 

	//Find the remainder of the shifted value when divided by 100 (essentially finding the value after the decimal point
	decimal = decimal % 100;

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

	delete[] handCommunity;
	delete[] handPlayer;


	int j;
	std::cin >> j;

    return 0;
}

