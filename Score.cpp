#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>


struct Card //These values will only be accessable by the deck, no need to 'hide' them
{
	char suit; // 'd' = diamonds, 'h' = hearts, 'c' = clubs; 's' = spades
	int value; // Allow jack to be 11, Queen 12, King 13, Ace 14 or 1. (Ace should equal 14 for scoring purpose -- Tim)
};


//Copy pasta-d from player
class Player
{
private:
	Card *hand;	// The player's two cards
	int money;	// How much money the player has
	bool fold;	// If the player has folded, then they cannot take any actions for the rest of a round
	std::string name;
	double currentScore; //What's the players score based off of the community pot and his hand

public:
	bool HasEnoughFunds(int bet); // Checks to see if the player has enough funds to match the pervious bet
	void addMoney(int amount); // If the player wins a hand
	int bet(int amount);
	int call(int prev_bet);
	bool check(); // Returns false if check option is not available

	int turn(int betToMatch); //Turn needs to return an integer amount that is equal to or greater than the 'betToMatch'
							  //unless the player cannot afford to, then the player will be going 'all in';

	int getMoney(); //Accessor method that finds the amount of money that the player has

	Card *checkHand() const; //Checks what hand the player has
	void getHand(Card* givenHand); //Gives the player their hand 
	void loseHand(); //sets hand to 'null'

					 //Score operations
	void setScore(double score);
	double getScore();

	std::string getName(); //Returns the players name

	bool playerHasFolded(); //Returns true if the player has folded;
};



/*Default arrays to 0s*/
void defaultArray(Card array[], const int size)
{
	/* Size will vary depending on if the array will be a community hand, 
	** player hand, combined community and player hand, or kicker cards
	*/

	for (int i = 0; i < size; i++)
	{
		array[i].value = 0;
		array[i].suit = 's';
	}
}



/*Combine the Community Hand and Player's Hand into one array*/
void combiner(Card holder[], const Card handCommunity[], const Card handPlayer[])
{
	/* Combining cards of the community and player into holder.
	** Last two cards will equal the players hand, but it doesn't  
	** necssarily matter which position they are in since the array 
	** will be reorganized from lowest value to highest value afterwards in the score method.
	*/

	for (int i = 0; i < 7; i++)
	{
		holder[i] = handCommunity[i];

		if (i == 5)
			holder[i] = handPlayer[0];

		else if (i == 6)
			holder[i] = handPlayer[1];

	}
}



/*Organize card values in a card array from lowest to highest -- execute after the community hand and player hand has been combined*/
void organizeLowToHigh(Card array[])
{
	//Create temporary card to hold a value
	Card temp;


	//Array size will be 7, therefore end will equal 7-1=6
	for (int end = 6; end >= 1; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (array[i].value > array[i + 1].value)		//Current value is greater than the next
			{
				temp = array[i];				//Set current value equal to temp
				array[i] = array[i + 1];		//Set current value equal to the next one
				array[i + 1] = temp;			//Set next value equal to temp 
			}
		}
	}
}



/*Organize double values in a double array from lowest to highest*/
void organizeLowToHigh(double array[], int size)
{
	//Create temporary variable to hold a value
	double temp;

	//Order values from lowest value to highest

	for (int end = size-1; end >= 1; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (array[i] > array[i + 1])		//Current value is greater than the next
			{
				temp = array[i];				//Set current value equal to temp
				array[i] = array[i + 1];		//Set current value equal to the next one
				array[i + 1] = temp;			//Set next value equal to temp 
			}
		}
	}
}


/*Organize hand scores from lowest to highest*/
void organizeLowToHigh(Player array[], int size)
{
	//Create temporary variable to hold a player
	Player temp;

	//Order values from lowest value to highest

	for (int end = size-1; end >= 1; end--)
	{
		for (int i = 0; i < end; i++)
		{
			if (array[i].getScore() > array[i + 1].getScore())		//Current value is greater than the next
			{
				temp = array[i];									//Set current value equal to temp
				array[i] = array[i + 1];							//Set current value equal to the next one
				array[i + 1] = temp;								//Set next value equal to temp 
			}
		}
	}
}



/*Check for multiples*/
void multipleChecker(const Card holder[], Card multiple1[], Card multiple2[], Card multiple3[], int & sizeMultiple1, int & sizeMultiple2, int & sizeMultiple3)
{
	/* Multiple checker -- Start from the highest card and go down
	** 
	** e.g. 5 5 5 4 4 4 3
	** Multiple1[] = 5 5 5
	** Multiple2[] = 4 4 4
	**
	**
	** e.g. 5 5 4 4 3 3 2
	** Multiple1[] = 5 5
	** Multiple2[] = 4 4
	** Multiple3[] = 3 3
	**
	** 
	** e.g. 10 9 8 7 6 5 4
	** No multiples - there are only singles 
	*/


	//Keep track of where a multiple ends so that the next multiple array can start from that positions
	int multipleMarker = 0;	

	//Find multiples for multiple1 array -- will be the highest valued multiples if there are any
	for (int i = 6, j = 0; i >= 0; i--)
	{
		/*If a community hand is passed without five cards, don't count the 0s cards as multiples
		**An incomplete community hand would be passed for AI scoring (or any other purpose) before the showdown
		*/

		if (holder[i].value == 0)
			break;



		//If there are already values in the duplicate array
		if (j > 0)
		{
			if (multiple1[j].value == holder[i].value)		//Check to see if the current holder value is the same as the multiple value
			{
				/* Increase counter of how many multiple cards there are in the array 
				** (missing one number e.g. if j = 1, there are 2 multiple cards)
				** Also this traverses the array by one -- it is traversed here 
				** because the current spot is already occupied.
				*/
				
				j++;	


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

			if (holder[i].value == 0)
				break;

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

			else if (holder[i].value == holder[i - 1].value)
			{
				multiple2[j] = holder[i];

				j++;
				i--;

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

				if (holder[i].value == 0)
					break;

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

					j++;
					i--;

					multiple3[j] = holder[i];
					sizeMultiple3 += 2;
				}
			}
		}
	}
}



/*Organize the cards into their corresponding suits*/
void suitOrganizer(const Card holder[], Card suit[], int & sizeSuit, char charSuit)
{
	/* Find cards of the suit
	** Organize the suit array from lowest value to highest value
	** charSuit is the suit that is being looking for: 's' 'c' 'd' 'h'
	*/

	for (int i = 0, j = 0; i < 7; i++)
	{
		/*If a community hand is passed without five cards, don't count the 0s cards as part of the spades suit
		**An incomplete community hand would be passed for AI scoring (or any other purpose) before the showdown
		*/

		if (holder[i].value == 0)		//Position is 'empty' - 0s card
			break;


		if (holder[i].suit == charSuit)
		{
			suit[j] = holder[i];
			j++;						//Traverse the suit array
		}


		if (i == 6)
			sizeSuit = j;				//When the end of the holder array is reached, then set sizeSuit to j
	}

}



/* Rank the hand of the player once the community and player hand have 
** been combined and organized, suits have been organized, and multiples have been found.
** Ranker does the actual scoring/ranking of the hand.
*/
double ranker(const int & sizeSuit, const int & sizeMultiple1, const int & sizeMultiple2,
	const int & sizeMultiple3, const Card suit[], const Card multiple1[],
	const Card multiple2[], const Card multiple3[], const Card holder[])
{

	int highCard = 0;		//Keep track of the high card

	/***********ROYAL FLUSH AND STRAIGHT FLUSH CHECKER**********/
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

			else 											//A consecutive run was not found (or it was broken) - reset the run counter to 0
				run = 0;

			if (run == 4)									//There are five cards found already - check for what the score is
			{

				if (highCard == 14)							//High card is an Ace so its lowest must be a Jack - Royal Flush
					return 10.0;							//Royal Flush - nothing can beat it so the tenths place is zero


				else										//Highest card wasn't an ace so the ranking must be a Straight Flush
					return 9 + (double)highCard / 100;		//Return the score -- decimal corresponds to the highest card value in the run

			}
		}

	}

	/**********FOUR OF A KIND CHECKER**********/
	/* Since there are already four cards in a multiple (if it passes the if statement), 
	** set the highCard equal to one of the cards (doesn't matter) and return the score
	*/
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

	/* No need to check Multiple3 because it should not have four cards 
	** e.g. 4 4 3 3 2 2 2
	** Maximum it should have is only 3 cards
	*/

	/**********FULL HOUSE CHECKER**********/
	/* High card will be from the multiple with 3
	** If multiple1 and multiple2 have 3 cards, 
	** then the high card will be from multiple1
	*/

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

	/* Doesn't matter if sizeMultiple1 or sizeMultiple2 == 2 - for ranking purposes, only the triple cards matter 
	** If a tie is reached, kickers will be used to individually evaluate card values
	*/
	else if (sizeMultiple1 == 2 && sizeMultiple3 == 3)	
	{
		highCard = multiple3[0].value;
		return 7 + (double)highCard / 100;
	}




	/**********FLUSH CHECKER**********/
	/*If the array has five or more cards corresponding to the suit, it is already a flush. 
	** Take the card at the end of the array to be the high card
	*/
	if (sizeSuit >= 5)
	{
		highCard = suit[sizeSuit - 1].value;
		return 6 + (double)highCard / 100;
	}




	/**********SRAIGHT CHECKER**********/
	/*Need to check for a consecutive run of 5 cards - doesn't matter which suit*/
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

		if (run == 4)									//There are five cards found already - return it
			return 5 + (double)highCard / 100;

	}




	/**********THREE OF A KIND CHECKER**********/
	/*Return the highest multiple that contains three cards - will be from multiple1 or multiple2*/
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



	/**********TWO PAIR CHECKER**********/
	/*Return the highest two pairs of two - will be from multiple1 and multiple2*/
	if (sizeMultiple1 == 2 && sizeMultiple2 == 2)
	{
		highCard = multiple1[0].value;
		return 3 + (double)highCard / 100;
	}


	/* It is not necessary to check sizeMultiple3, even if it is occupied, 
	** because Multiple1 and Multiple2 have the highest valued cards.
	** If there are three cards in Multiple3, then a full house would have already been returned.
	** If there are three or four cards in multiple1, then a three of a kind or 
	** four of a kind would have already been returned.
	*/


	/* NOTE FOR OTHER STUFF: Check rankings with two pair in the event both players have similar hands
	** Player1 - 5, 6
	** Player2 - 6, 3
	** Community - 6, 7, 7, 2, 9
	** Who wins? Tie?
	** Other note: This issue has been dealt with by kicker cards
	*/


	/**********PAIR CHECKER**********/
	/*Return the highest pair of two will be from multiple1 array*/
	if (sizeMultiple1 == 2)
	{
		highCard = multiple1[0].value;
		return 2 + (double)highCard / 100;
	}

	/*It is not necessary to check multiple2 and multiple3 because multiple1 will have the highest valued pair if there is a pair */



	/**********HIGH CARD CHECKER**********/
	/*Return the highest card in the holder array*/
	highCard = holder[6].value;				//It's the highest card
	return 1 + (double)highCard / 100;
}



/*Score function - calls other functions to score the hand*/
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


	Card * holder = new Card[7];	//Will combine handCommunity and handPlayer into one array of 7 cards
	Card * spades = new Card[7];	//Contain all the spade cards 
	Card * clubs = new Card[7];		//Contain all the clubs cards
	Card * diamonds = new Card[7];	//Contain all the diamonds cards
	Card * hearts = new Card[7];	//Contain all the hearts cards
									//All above are ordered lowest to highest


									//Keep track of multiples (e.g. check to see if a four of a kind, full house, etc. is possible)
									//It is only possible to have a maximum of 3 multiple sets  (e.g. 2d 2s 3d 3s 4d 4s 5s -- 5s is not a multiple because there is no other 5)
									//Sizes are four because there are only four cards of one value
									//Ordered from highest to lowesr
	Card * multiple1 = new Card[4];
	Card * multiple2 = new Card[4];
	Card * multiple3 = new Card[4];

	//Keep track of sizes
	int sizeSpades = 0, sizeClubs = 0, sizeDiamonds = 0, sizeHearts = 0;
	int sizeMultiple1 = 0, sizeMultiple2 = 0, sizeMultiple3 = 0;


	//Defaulting all created array values to 0s
	defaultArray(holder, 7);
	defaultArray(spades, 7);
	defaultArray(clubs, 7);
	defaultArray(diamonds, 7);
	defaultArray(hearts, 7);

	defaultArray(multiple1, 4);
	defaultArray(multiple2, 4);
	defaultArray(multiple3, 4);


	//Combining cards of the community and player into holder
	combiner(holder, handCommunity, handPlayer);

	//Organize holder from lowest value to highest
	organizeLowToHigh(holder);


	//Check for multiples of a card value - order the multiples from highest to lowest
	multipleChecker(holder, multiple1, multiple2, multiple3, sizeMultiple1, sizeMultiple2, sizeMultiple3);

	//Organize all of the cards into their respective suits - order from lowest to highest
	suitOrganizer(holder, spades, sizeSpades, 's');
	suitOrganizer(holder, clubs, sizeClubs, 'c');
	suitOrganizer(holder, diamonds, sizeDiamonds, 'd');
	suitOrganizer(holder, hearts, sizeHearts, 'h');

	//Retrieve scores using different suits and compare them - return the highest score
	double spadesScore = ranker(sizeSpades, sizeMultiple1, sizeMultiple2, sizeMultiple3, spades, multiple1, multiple2, multiple3, holder);
	double clubsScore = ranker(sizeClubs, sizeMultiple1, sizeMultiple2, sizeMultiple3, clubs, multiple1, multiple2, multiple3, holder);
	double diamondsScore = ranker(sizeDiamonds, sizeMultiple1, sizeMultiple2, sizeMultiple3, diamonds, multiple1, multiple2, multiple3, holder);
	double heartsScore = ranker(sizeHearts, sizeMultiple1, sizeMultiple2, sizeMultiple3, hearts, multiple1, multiple2, multiple3, holder);



	//Compare the scores - return the one that is the highest score
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


}



/* In the event a tie is reached, kicker cards must be used
** If kicker cards are the same to that of another player, the pot is split
*/
Card* kicker(const Card handPlayer[], const Card handCommunity[], const int intScore, int decimal)
{
	//Create arrays
	Card * holder = new Card[7];
	Card * kicker = new Card[5];

	//Default arrays to 0s
	defaultArray(holder, 7);
	defaultArray(kicker, 5);

	//Combine the Community Hand and Player's Hand into the holder
	combiner(holder, handCommunity, handPlayer);

	//Organize holder array for low to high
	organizeLowToHigh(holder);

	/* The holder array is traversed from the end to beginning (highest values to lowest values.
	** Therefore it is not needed to take into account if the current holder value is the most 
	** optimal kicker card.
	*/


	switch (intScore)
	{
	case 8:
		/* Four of a kind
		** Example
		** Player: 9 8
		** Community: 12 12 12 12 13 
		** Kicker: 13 12 12 12 12
		*/

		for (int i = 6, j = 0; i >= 0; i--)
		{
			if (holder[i].value == decimal)		//If the decimal value (highest card of the score) equals the holder's current position
			{
				kicker[j] = holder[i];			
				j++;							//Traverse the kicker array
			}

			else if (holder[i].value != decimal && j == 0)	//Kicker array does not have any cards 
			{
				kicker[j] = holder[i];
				j++;
			}

			if (j == 5)			//Kicker is full
				return kicker;
		}
		break;

		/* NOTE: Actually a tie with a Four of a Kind should not be possible. Therefore, this case 8 is unecessary for the kicker.
		** Actually this case is necessary -- in case there is a four of a kind already in the community hand, 
		** then there needs to be a kicker (likely will be determined by players' hands).
		*/ 

	case 7:
		/* Full House
		** Example
		** Player: 3 6 
		** Community: 6 6 3 5 8
		** Kicker: 6 6 6 3 3
		** Kicker: 3 3 (6 is not needed, they have already been confirmed to be equal with another player)
		*/

		for (int i = 6, j = 0; i >= 0; i--)
		{
			if (holder[i].value != decimal && holder[i - 1].value == decimal)	//Current value does not equal the triple and current value equals the value behind it
			{
				kicker[j] = holder[i];

				j++;		//Traverse the kicker
				i--;		//Traverse the holder

				kicker[j] = holder[i];

				//Kicker array has two cards already - return it
				return kicker;
			}
		}

		break;

	case 6:
		/* Flush
		** Example
		** Player: 3 7
		** Community: 10 9 8 6 5
		** Kicker: 10 9 8 7 6
		*/

		for (int i = 6, j = 0; i >= 0; i--)
		{
			if (holder[i].value == decimal)
			{
				kicker[j] = holder[i];
				j++;
				decimal--;		//Decreasing the decimal by one to simpliy the code (instead of j++ and i-- continuously)
								
				/* e.g. Kicker wants: 10 9 8 7 6
				** decimal = 10;
				** kicker[0].value = 10;
				** j++; (j==1)
				** decimal--; (decimal = 9 --- it will retrieve the next card of this value, the value below the previous decimal)
				** Rinse and repeat
				*/
			}

			if (j == 5)			//Kicker has five cards
				return kicker;
		}

		break;

	case 4:
		/* Three of a kind
		** Example
		** Player: 7 5
		** Community: 7 7 6 3 2
		** Kicker: 7 7 7 6 5
		** Kicker: 6 5 (don't need 7 because it has already been confirmed to be equal with the triple of another player)
		*/

		for (int i = 6, j = 0; i >= 0; i--)
		{
			if (holder[i].value != decimal)		//Current position is not equal to the triple card
			{
				kicker[j] = holder[i];
				j++;
			}

			if (j == 2)			//Kicker has two cards
				return kicker;
		}

		break;

	case 3:
		/* Two pair
		** Example
		** Player: 7 5
		** Community: 7 6 5 4 10
		** Kicker: 7 7 5 5 10
		** Final Kicker: 5 5 10		(7 7 is not needed because they have been confirmed to be the same if the kicker function is called)
		** Compare the lower pair - if the same, compare the highest kicker card
		*/

		/* Kicker array is organized first with the second lower pair and the third
		** value (kicker[2]) will equal the highest single card outside of the two pair
		*/

		for (int i = 6, j = 0; i >= 0; i--)
		{

			//Current value does not equal the high double card and current value is the same as the value behind it
			if (holder[i].value != decimal && holder[i].value == holder[i - 1].value)	
			{
				kicker[j] = holder[i];
				j++;					//Traverse the kicker array
				i--;					//Traverse the holder array
				kicker[j] = holder[i];
			}

			//Current value does not equal high double card - will be the kicker card that is not part of the lower pair
			else if (holder[i].value != decimal && kicker[3].value == 0)		 
				kicker[2] = holder[i];	
		
			//If the kicker has three cards, return it
			if (kicker[0].value != 0 && kicker[1].value != 0 && kicker[2].value != 0)	
				return kicker;

		}
		break;

	case 2:
		/* One Pair
		** Example 
		** Player: 7 7
		** Community: 5 2 6 3 9
		** Kicker: 9 6 5 (7 does not matter because it has already been found to be equal to another player's pair)
		*/


		for (int i = 6, j = 0; i >= 0; i--)
		{
			if (holder[i].value != decimal)
			{
				kicker[j] = holder[i];
				j++;
			}

			//Kicker has three cards
			if (j == 3)				
				return kicker;
		}

	case 1:
		/* No Pair
		** Example
		** Player: 5 3
		** Community: 13 10 8 2 6
		** Kicker: 10 8 5 3 (13 does not matter because it has already been found equal to another player's high card)
		*/

		for (int i = 6, j = 0; i >= 0; i--)
		{
			if (holder[i].value != decimal)
			{
				kicker[j] = holder[i];
				j++;
			}

			//Kicker has four cards
			if (j == 4)			
				return kicker;
		}
		break;

	//This should not be reached (if it is reached, it means the intScore is not 8, 6, 4, 3, 2, or 1)
	default:
		std::cout << "Error - invalid intScore \n";
		return kicker;
	}

	//This should not be reached
	return kicker;
}



/*Compare the kickers of two players*/
int compareKickers(Card kicker1[], Card kicker2[])
{
	/* Return an int 
	** Return Values:
	** 1 - kicker1 has the wining hand
	** 2 - kicker2 has the winning hand
	** 3 - tie
	*/

	//Compare each card individually to another using a for loop

	for (int i = 0; i < 5; i++)
	{
		if (kicker1[i].value > kicker2[i].value)
		{
			//std::cout << "Player one wins the pot. \n";
			return 1;
		}

		else if (kicker1[1].value < kicker2[i].value)
		{
			//std::cout << "Player two wins the pot \n";
			return 2;
		}
	}

	//std::cout << "Tie has been reached. Pot is split. \n";
	return 3;
}



/* Display the score of a player's hand (Full House, Straight, etc.)
** Mostly used for debugging purposes, not in an actual game.
*/
void displayScore(const int & intRank, const int & decimal)
{
	//IntRank represents the overall ranking of the hand (e.g. Full House, Straight, etc.)
	//Decimal represents the high card (Ace, King, Queen, etc.)

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
}



/* Determine the winner between two players
** Mostly for debugging purposes - eventually becomes basis for determineVectorWinner
*/
void determineWinner(const Card handPlayer1[], const Card handPlayer2[], const Card handCommunity[],
	const double & rank1, const double & rank2, const int & intRank1, const int & intRank2,
	const int & decimal1, const int & decimal2)
{
	//Create kicker arrays
	Card * kicker1 = new Card[5];
	Card * kicker2 = new Card[5];

	//Default arrays to 0s
	defaultArray(kicker1, 5);
	defaultArray(kicker2, 5);

	//Hold return value from compareKickers
	int kickerValue;

	if (rank1 > rank2)
	{
		std::cout << "Player one wins the pot. \n";
	}

	else if (rank1 < rank2)
	{
		std::cout << "Player two wins the pot. \n";
	}


	else if (rank1 == rank2)
	{
		switch (intRank1)
		{
		case 10:		
			/* Royal Flush - In the very extremely unlikely event that a royal flush is present in the community cards (e.g. 14s 13s 12s 11 10s)
			** Might as well have won 100 lotteries
			*/

			std::cout << "Pot is split. \n";
			break;

		case 9:			
			/* Straight Flush - Must be a tie if two players have it 
			** e.g. same stuation as the royal flush were a straight flush is present in the communnity cards
			** Might as well have won 10 lotteries
			*/

			std::cout << "Pot is split. \n";
			break;

		case 8:			
			/* Two Four of a Kinds of the same value (in the event that there is a four of a kind present in the community cards)
			** Kicker will be one card
			** Might as well have won the lottery
			*/

			kicker1 = kicker(handPlayer1, handCommunity, intRank1, decimal1);
			kicker2 = kicker(handPlayer2, handCommunity, intRank2, decimal2);
			kickerValue = compareKickers(kicker1, kicker2);
			
			switch (kickerValue)
			{
			case 1:
				std::cout << "Player 1 wins. \n";
				break;

			case 2:
				std::cout << "Player 2 wins. \n";
				break;

			case 3:
				std::cout << "Pot is split. \n";
				break;
			}

			break;

		case 7:			
			/* Full House
			** Need to compare the two cards outside of the triple
			** Kicker will be two cards
			*/

			kicker1 = kicker(handPlayer1, handCommunity, intRank1, decimal1);
			kicker2 = kicker(handPlayer2, handCommunity, intRank2, decimal2);
			kickerValue = compareKickers(kicker1, kicker2);

			switch (kickerValue)
			{
			case 1:
				std::cout << "Player 1 wins. \n";
				break;

			case 2:
				std::cout << "Player 2 wins. \n";
				break;

			case 3:
				std::cout << "Pot is split. \n";
				break;
			}

			break;

		case 6:			
			/* Flush
			** Use kicker - compare the entire flush of one to another
			** Kicker will have five cards
			*/

			kicker1 = kicker(handPlayer1, handCommunity, intRank1, decimal1);
			kicker2 = kicker(handPlayer2, handCommunity, intRank2, decimal2);
			kickerValue = compareKickers(kicker1, kicker2);

			switch (kickerValue)
			{
			case 1:
				std::cout << "Player 1 wins. \n";
				break;

			case 2:
				std::cout << "Player 2 wins. \n";
				break;

			case 3:
				std::cout << "Pot is split. \n";
				break;
			}

			break;

		case 5:			
			/* Straight -- Has to be a tie if both players have the highest card (because a straight has to be a run)
			** Win half a lottery?
			*/

			std::cout << "Pot is split. \n";
			break;

		case 4:			
			/* Three of a kind
			** Kicker will have two cards
			*/

			kicker1 = kicker(handPlayer1, handCommunity, intRank1, decimal1);
			kicker2 = kicker(handPlayer2, handCommunity, intRank2, decimal2);
			kickerValue = compareKickers(kicker1, kicker2);

			switch (kickerValue)
			{
			case 1:
				std::cout << "Player 1 wins. \n";
				break;

			case 2:
				std::cout << "Player 2 wins. \n";
				break;

			case 3:
				std::cout << "Pot is split. \n";
				break;
			}


			break;

		case 3:			
			/* Two pair
			** Compare the second pair that is lower - if still a tie, use kicker - one card
			** Kicker will have three cards
			*/

			kicker1 = kicker(handPlayer1, handCommunity, intRank1, decimal2);
			kicker2 = kicker(handPlayer2, handCommunity, intRank2, decimal2);
			kickerValue = compareKickers(kicker1, kicker2);

			switch (kickerValue)
			{
			case 1:
				std::cout << "Player 1 wins. \n";
				break;

			case 2:
				std::cout << "Player 2 wins. \n";
				break;

			case 3:
				std::cout << "Pot is split. \n";
				break;
			}


			break;

		case 2:			
			/* One pair
			** Kicker will have three cards
			*/

			kicker1 = kicker(handPlayer1, handCommunity, intRank1, decimal2);
			kicker2 = kicker(handPlayer2, handCommunity, intRank2, decimal2);
			kickerValue = compareKickers(kicker1, kicker2);

			switch (kickerValue)
			{
			case 1:
				std::cout << "Player 1 wins. \n";
				break;

			case 2:
				std::cout << "Player 2 wins. \n";
				break;

			case 3:
				std::cout << "Pot is split. \n";
				break;
			}


			break;

		case 1:			
			/* No pair
			** Kicker will have four cards
			*/

			kicker1 = kicker(handPlayer1, handCommunity, intRank1, decimal2);
			kicker2 = kicker(handPlayer2, handCommunity, intRank2, decimal2);
			kickerValue = compareKickers(kicker1, kicker2);

			switch (kickerValue)
			{
			case 1:
				std::cout << "Player 1 wins. \n";
				break;

			case 2:
				std::cout << "Player 2 wins. \n";
				break;

			case 3:
				std::cout << "Pot is split. \n";
				break;
			}


			break;
		}
	}
}



/*Score a vector of player's hands*/
void playerScorer(std::vector<Player*> players, const Card handCommunity[])
{
	
	//Traverse the vector
	for (unsigned int i = 0; i < players.size(); i++)
	{
		//Set the score equal to 0 because the player is no longer in the game
		if (players[i]->playerHasFolded() == true)
		{
			players[i]->setScore(0);		
		}

		//If player has not folded, score the hand (+ .001 is in case of errors due to computer computations)
		else
			players[i]->setScore((score(players[i]->checkHand(), handCommunity)) + .001);	
	}

}



/*Determine winner (or if there is a tie) between all the players (instead of two - see determineWinner)*/
std::vector<Player*> determineWinnerVector(const std::vector<Player*> players, const Card handCommunity[])
{
	/* Function will go from the end of the vector to the beginning - assuming that the value at the end
	** of the vector is the highest value (say value[6]). If the value that it is compared to (the value behind the last value - say value[5])
	** is higher, then the highest value will be then be value[5]. Process continues until the end of the vector.
	*/

	/* 1 represents comments of a failure -- should I look at it again? -- error from 1.2 causes errors "cannot convert Player to Player *"
	** I was trying to convert the vector to an array, rearrange the array from lowest to highest score, then convert back to a vector (rearrange2).
	** Then I would traverse a score array (that contains the scores of the players and is organized from lowest to highest - so the same structure
	** as vector rearrange2. The for loop at the end (for determining the winner) would then start from the end of the score array (highest value)
	** and traverse to the beginning. If the end value (say score[6]) is greater than the previous (say score[5]), so score[6] > score[5], then
	** rearrange[6] would be pushed and returned - the for loop ends because there are no more values before score[6] that are greater.
	** However with the current setup (due to the error of conversion -- look at 1.2), this is not possible. Therefore, the score array will mimic
	** the normal positions of the original players vector, unorganized by score. Therefore, the for loop will have to traverse through every
	** point because any point can be higher than the previous.
	*/


	//std::vector<Player*> players2(players.begin(), players.end());	1

	//Convert vector to arrays
	//Player * rearrange = players2[0];									1.2


	//Order the players by score: lowest to highest
	//organizeLowToHigh(rearrange, players.size());


	//Convert rearrange array to rearrange2 vector
	//std::vector<Player*> rearrange2(rearrange, rearrange + players.size());	1


	//Initialize kicker arrays in case a tie is found
	Card * kicker1 = new Card[5];
	Card * kicker2 = new Card[5];


	//Default kicker arrays to 0s
	defaultArray(kicker1, 5);
	defaultArray(kicker2, 5);


	int intRank1;	//Keep track of the interger rank of a hand (e.g. 9 - Straight Flush)
	int decimal1;	//Keep track of the decimal value (int the form of an interger later) - (e.g. 9.05.... decimal1 = 5)

	int intRank2;
	int decimal2;

	int kickerValue;	/* Hold the value that is returned when comparing kickers
						** If kickerValue == 1 -- player of kicker1 is the winner between the two
						** kickerValue == 2 -- player of kicker2 is the winner between the two
						** kickerValue == 3 -- a tie between the players
						*/

	//Has the high value been pushed into the winner vector yet? Avoid duplicates in the vector with this boolean
	bool HighValueHasBeenPushed = false;

	//Hold the vector of winners
	std::vector<Player*> winners;

	//Create an array to hold the scores (for easier usage)
	double * scores = new double[players.size()];

	//Transfer the player scores to the array
	for (unsigned int i = 0; i < players.size(); i++)
	{
		scores[i] = players[i]->getScore();
	}

	

	//Organize the scores from low to high -- mirror rearrange2 setup
	//organizeLowToHigh(scores, players.size());		1 - don't need to reorganize with this new setup


	double highValueScore = scores[players.size() - 1];
	int highValuePosition = players.size() - 1;


	//i = players.size()-2 and not players.size()-1 because player.size()-1 is declared as the highValue (it will be compared with itself if i = player.size()-1)
	for (int i = players.size()-2; i >= 0; i++)
	{
		if (highValueScore < scores[i])
		{
			winners.empty();				//Empty the vector because there is a new high score

			winners.push_back(players[i]);	//Push the new score in
			highValueScore = scores[i];		//Set as the new high score

			HighValueHasBeenPushed = true;

			//Clear the arrays
			defaultArray(kicker1, 5);
			defaultArray(kicker2, 5);
		}

		else if (highValueScore == scores[i])
		{
			//Convert the double into an int to find the hand ranking
			intRank1 = (int)highValueScore;
			intRank2 = (int)scores[i];

			//Hold the double value of rank
			double intermed1 = intRank1;
			double intermed2 = intRank2;

			//Multiply double value by 100 to shift the decimal place by two to the right (get rid of decimal value)
			intermed1 *= 100;
			intermed2 *= 100;

			//Convert the shifted value to an interger
			decimal1 = (int)intermed1;
			decimal2 = (int)intermed2;

			//Find the remainder of the shifted value when divided by 100 (essentially finding the value after the decimal point
			decimal1 = decimal1 % 100;
			decimal2 = decimal2 % 100;




			//rearrange2 used to have players in its place
			//Rearrange2 is used because it contains the players organized from lowest to highest by score
			//Create the kickers
			kicker1 = kicker(players[highValuePosition]->checkHand(), handCommunity, intRank1, decimal1);	//Set equal to highValue
			kicker2 = kicker(players[i]->checkHand(), handCommunity, intRank2, decimal2);					//Set equal to the challenger of who will be the new high score


			//Compare the kickers
			kickerValue = compareKickers(kicker1, kicker2);


			//If kicker1 turns out to be the winner and the player of kicker1 has not been pushed yet
			if (kickerValue == 1 && HighValueHasBeenPushed == false)
			{
				//Push the highest value winner in
				winners.push_back(players[highValuePosition]);
				
				//It has been pushed
				HighValueHasBeenPushed = true;

				//Clear the array for the next round (because sometimes not all the array slots are used)
				defaultArray(kicker1, 5);
				defaultArray(kicker2, 5);
			}


			else if (kickerValue == 2)
			{
				winners.empty();				//Empty the vector because there is a new high score

				winners.push_back(players[i]);	//Push the new score in
				highValueScore = scores[i];			//Set as the new high score

				HighValueHasBeenPushed = true;
				
				//Clear the arrays
				defaultArray(kicker1, 5);
				defaultArray(kicker2, 5);
			}


			else if (kickerValue == 3)
			{
				//Push two players through to the winners spot because there is a tie


				//If the high value has already been pushed, don't push it -- it's already pissed
				if(!HighValueHasBeenPushed)
					winners.push_back(players[highValuePosition]);


				//Push the other because there's a tie
				winners.push_back(players[i]);


				//Clear the arrays
				defaultArray(kicker1, 5);
				defaultArray(kicker2, 5);
			}
		}


		/*else if (highValueScore > scores[i])
		{
			if(!HighValueHasBeenPushed)
				winners.push_back(players[highValuePosition]);

			return winners;
		}*/

	}

	return winners;

}



int main()
{
	//Testing with vectors stuff

	// constructors used in the same order as described above:
	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second(4, 100);                       // four ints with value 100
	std::vector<int> third(second.begin(), second.end());  // iterating through second
	std::vector<int> fourth(third);                       // a copy of third

	//Convert vector to arrays
	std::vector<Card> cards;
	
	Card test;
	test.value = 5;
	test.suit = 's';

	cards.push_back(test);

	Card * a = &cards[0];

	std::cout << a[0].value << std::endl;

	
	// the iterator constructor can also be used to construct from arrays:
	int myints[] = { 16,2,77,29 };
	std::vector<int> fifth(myints, myints + 4);

	std::cout << "The contents of fifth are:";
	for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//End of testing vector stuff





	//Creating hypothetical hands

	Player * John = new Player();
	Player * Jack = new Player();

	
	std::vector<Player*> players; 
	std::vector<double> scores;
	
	players.push_back(John);
	players.push_back(Jack);

	Card * handCommunity = new Card[5];
	Card * handPlayer1 = new Card[2];
	Card * handPlayer2 = new Card[2];

	
	//Default arrays to 0s (making sure that there is no extraneous data left from other programs)
	defaultArray(handCommunity, 5);
	defaultArray(handPlayer1, 2);
	defaultArray(handPlayer2, 2);

	handPlayer1[0].value = 14;
	handPlayer1[0].suit = 's';

	handPlayer1[1].value = 13;
	handPlayer1[1].suit = 's';

	handPlayer2[0].value = 3;
	handPlayer2[0].suit = 'd';

	handPlayer2[1].value = 2;
	handPlayer2[1].suit = 'd';

	handCommunity[0].value = 12;
	handCommunity[0].suit = 's';

	handCommunity[1].value = 11;
	handCommunity[1].suit = 's';

	handCommunity[2].value = 2;
	handCommunity[2].suit = 's';

	handCommunity[3].value = 3;
	handCommunity[3].suit = 'c';

	handCommunity[4].value = 3;
	handCommunity[4].suit = 'h';

	
	//Score the hand
	double rank1 = score(handPlayer1, handCommunity) + .001;	//Correction factor in case not scored properly (due to computer error)
																//e.g. a Straight - 6 5 4 3 2 - is score 4.0599999 

	double rank2 = score(handPlayer2, handCommunity) + .001; 

	//Convert the double into an int to find the hand ranking
	int intRank1 = (int)rank1;
	int intRank2 = (int)rank2;

	//Hold the double value of rank
	double intermed1 = rank1;
	double intermed2 = rank2;

	//Multiply double value by 100 to shift the decimal place by two to the right (get rid of decimal value)
	intermed1 *= 100;
	intermed2 *= 100;

	//Convert the shifted value to an interger
	int	decimal1 = (int)intermed1;
	int decimal2 = (int)intermed2;

	//Find the remainder of the shifted value when divided by 100 (essentially finding the value after the decimal point
	decimal1 = decimal1 % 100;
	decimal2 = decimal2 % 100;


	//Display scores for checking purposes
	displayScore(intRank1, decimal1);
	displayScore(intRank2, decimal2);

	//Determine the winner (or if there is a tie)
	determineWinner(handPlayer1, handPlayer2, handCommunity, rank1, rank2, intRank1, intRank2, decimal1, decimal2);


	//Prevent memory leaks
	delete[] handCommunity;
	delete[] handPlayer1;
	delete[] handPlayer2;
	


	delete John;
	delete Jack;

	return 0;
} 
