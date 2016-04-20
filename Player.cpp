/**
 * 	@file       Player.cpp
 * 	@author(s)  Terry Thibault (tlt@cise.ufl.edu)
 * 				Alexander Rumak (alexrumak.ufl.edu)
 *				Hugh Wu	
 * 	@date       4/11/16
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

#include <string>
#include <vector>
#include "Player.h"
#include "Score.h"
#include <iostream>
#include <time.h>

/*********************************************************
* @brief Default constructor for Player; Will be overridden
* by children classes. Takes in the user's inputted name
* and money 
*********************************************************/
Player::Player(int money, std::string name){
	this->money = money;
	this->name = name;
	hasFolded = false;
	hasAllIn = false;
	currentScore = 0;
	hasLost = false;
	hand = new Card[2]; //To be destroyed in destructor
}

/*********************************************************
* @brief Returns the player's name
*********************************************************/
std::string Player::getName() {
	return name;
}


/*********************************************************
 * @brief This function checks if the player has enough 
 * funds to make a bet. 
 ********************************************************/
bool Player::HasEnoughFunds(int bet)
{
	if (money < bet) return false;
	return true;
}

/*********************************************************
 * @brief This function will add money to the player money
 * in the event that they win a hand.
 ********************************************************/
void Player::addMoney(int amount) 
{
	money += amount;
}

/*********************************************************
* @brief Returns the amount of money that the player has
*********************************************************/
int Player::getMoney() {
	return money;
}


/*********************************************************
 * @brief This function is called by the table. Simply 
 * subtracts from the player cash and tells the table
 * how much to add to the pot. If the player does not have
 * enough money, the program will loop for an amount that 
 * is equal to or less than their funds
 ********************************************************/
int Player::raise(int amount, int prev_bet)
{
	this->money -= (amount + prev_bet);
	return (amount + prev_bet);
	
}

/*********************************************************
 * @brief This function's input is the largest previous 
 * bet. If the player does not have enough money to call,
 * the player will go all-in.
 ********************************************************/
int Player::call(int prev_bet)
{
	this->money -= prev_bet;
	return prev_bet;
}

int Player::allIn() {
	int allMyMoney = money;
	this->money = 0;
	this->hasAllIn = true;

	return allMyMoney;
}

/*********************************************************
* @brief Returns true if the player has folded
*********************************************************/
bool Player::playerHasFolded() {
	return hasFolded;
}

/*********************************************************
* @brief Returns true if the player has fall-in'd
*********************************************************/
bool Player::playerAllIn() {
	return hasAllIn;
}

/*********************************************************
 * @brief Returns a pointer to the player's hand.
 ********************************************************/
Card* Player::checkHand() const
{
	return hand;
}

/*********************************************************
 * @brief Gives the player their hand for the turn
 ********************************************************/
void Player::giveHand(Card* givenHand){
	hand[0] = givenHand[0];
	hand[1] = givenHand[1];
}


/*********************************************************
* @brief Set the players hand to NULL; This means the player does not
* have a hand.
*********************************************************/
void Player::loseHand(){
	hand = NULL;
	return;
}

/*********************************************************
* @brief Sets the players score; Useful for Artifical
* intelligence but also needed to find winners.
*********************************************************/
void Player::setScore(double score){
	currentScore = score;
	return;
}

/*********************************************************
* @brief Returns the players score
*********************************************************/
double Player::getScore(){
	return currentScore;
}

/*********************************************************
* @brief Resets player values to their initial states
*********************************************************/
void Player::resetPlayer(){
	hasFolded = false;
	hasAllIn = false;
	currentScore = 0;
}

/*********************************************************
* @brief Forces the player to bet
********************************************************/
int Player::forceBet(int blindCost){
	
	if(money < blindCost){
		this->hasAllIn = true;
		int temp = money;
		this->money = 0;
		
		//GUI PLUG player has all ined
		
		return temp;
	}
	else{
		this->money -= blindCost;
		return blindCost;
	}
	
}

/*********************************************************
* @brief This function returns whether the player has lost
**********************************************************/
bool Player::playerHasLost(){
	return hasLost;
}

/*******************************************************
* @brief This function sets wen the player has lost
* (when the player has lost all their money)
**********************************************************/
void Player::playerLost(){
	this->hasLost = true;
}

/****************************************************
* @brief This checks if a given string is an integer
*****************************************************/
bool isInt(std::string input) 
{
	for(int i = 0; i < (int)input.length(); ++i)
	{
		if(!(isdigit(input[i])))
		{
			return false;
		}
	}
	return true;
}

/****************************************************
* @brief This turns a string into an integer
*****************************************************/
int stringToInt(std::string input)
{
	int number = 0;
	for(int i = 0; i < (int)input.length(); ++i)
	{
		number += pow(10,i)*(input.at(input.length() - 1 - i) - '0'); 
	}
	return number;
}

/*********************************************************
 * @brief Turn is the main mechanism by which the game is 
 * able to tell what the user's action is. 
 ********************************************************/
int Player::turn(int betToMatch, int currentContribution, int potSize, std::vector<Card> communityHand)
{
	//Give a list of possibile options
	std::cout << "The current bet is: " << betToMatch << ".\n";
	std::cout << "Your money: " << this->getMoney() << ".\n";
	std::cout << "The amount you currently have in the pot is: " << currentContribution << ".\n";
	std::cout << "The pot has: " << potSize << " dollars in it.\n";
	if ((int)communityHand.size() != 0) {
		std::cout << "The community cards: ";
		for (int i = 0; i < (int)communityHand.size(); ++i) {
			std::cout << communityHand[i].value << communityHand[i].suit << " ";
		}
	}
	
	std::cout << "\nYour hand: ";
	std::cout << hand[0].value << hand[0].suit << " " << hand[1].value << hand[1].suit << "\n"<< std::endl;
	
	//If the current bet is 0, checking is an option. Yes, calling and checking are the same in this situation.
	if(betToMatch == 0)
	{
		std::cout << "1. Check \n2. Raise \n3. All-In\n4. Fold \n";
		std::string input; 
		std::cin >> input;
		
		//If they didn't input a valid option, fail.
		if(!(input == "1" || input == "2" || input == "3" || input == "4"))
		{
			std::cout << "Invalid parameter. Please enter a valid option.\n";
			return turn(betToMatch, currentContribution, potSize, communityHand);
		}

		if(input == "1")
		{
			return 0;
		}
		
		else if(input == "2")
		{
			std::cout << "Raise amount: ";
			std::cin >> input;
			//Check to ensure it's really a number
			if(!isInt(input))
			{
				std::cout << "That's not a valid input. Please enter a number.";
				return turn(betToMatch, currentContribution, potSize, communityHand);		
			}
			//Convert to an int
			int intInput = stringToInt(input);
			// Cannot raise an amount 0 or less
			if (intInput <= 0){
				std::cout << "That's not a valid input. Please enter a number greater than 0.";
				return turn(betToMatch, currentContribution, potSize, communityHand);
			}
			
			if(this->HasEnoughFunds(intInput + betToMatch))
			{
				return raise(intInput, betToMatch);
			}
			std::cout << "You don't have enough money to do that. \n";
			return turn(betToMatch, currentContribution, potSize, communityHand);
		}

		else if(input == "3")
		{
			return allIn();
		}
		
		else // input has to be 4
		{
			this->hasFolded = true;
			std::cout << "Fold successful.\n";
			return 0;
		}
	}
	
	//Assuming betToMatch > 0. 
	else
	{
		std::cout << "1. Call \n2. Raise \n3. All-In\n4. Fold \n";
		std::string input;
		std::cin >> input;

		//Fail for invalid options
		if (!(input == "1" || input == "2" || input == "3" || input == "4"))
		{
			std::cout << "Invalid parameter. Please enter a valid option.\n";
			return turn(betToMatch, currentContribution, potSize, communityHand);
		}

		else if (input == "1")
		{
			if (this->HasEnoughFunds(betToMatch))
			{
				return call(betToMatch);
			}
			std::cout << "Not enough funds to perform that action.\n";
			return turn(betToMatch, currentContribution, potSize, communityHand);
		}

		else if (input == "2")
		{
			std::cout << "Raise amount: ";
			std::cin >> input;
			//Check to ensure it's really a number
			if(!isInt(input))
			{
				std::cout << "That's not a valid input. Please enter a number.";
				return turn(betToMatch, currentContribution, potSize, communityHand);		
			}
			//Convert to an int
			int intInput = stringToInt(input);
			// Cannot raise an amount 0 or less
			if (intInput <= 0){
				std::cout << "That's not a valid input. Please enter a number greater than 0.";
				return turn(betToMatch, currentContribution, potSize, communityHand);
			}
			if (this->HasEnoughFunds(intInput + betToMatch))
			{
				return raise(intInput, betToMatch);
			}
			std::cout << "You don't have enough money to do that. \n";
			return turn(betToMatch, currentContribution, potSize, communityHand);
		}

		else if (input == "3")
		{
			return allIn();
		}

		else if (input == "4")
		{
			this->hasFolded = true;
			std::cout << "Fold successful.\n";
			return 0;
		}
	}
}


/*********************************************************
* @brief The computer inheirits everything from the 
* player class but its methods are overridden so it does
* not take user input
**********************************************************/
Computer::Computer(int money, std::string name) : Player(money, name) {
	// Everytime a new computer player is created, their confidence levels are different
	// rand() % x + y gives a random integer from [y, y + x)
	confidence = rand() % 21 + 20;
}

/*******************************************************
* @brief This function deals with how the computer
* decides their actions.
**********************************************************/
int Computer::turn(int betToMatch, int currentContribution, int potSize, std::vector<Card> communityHand){
	//Seeding the random number generator
	srand(time(NULL));
	
	// This creates an array to pass into the score function defined in score.cpp
	Card* community = new Card[7];
	for (int c = 0; c < communityHand.size(); ++c) {
		community[c] = communityHand[c];
	}

	// This if block should only run when the community cards have not been dealt yet
	if (communityHand.size() == 0) {
		// If the computer gets a pair, then it will greatly increase their confidence
		if (hand[0].value == hand[1].value) {
			confidence += (rand() % 11 + 10) + (1.5 * hand[0].value);
		}
		// Otherwise if they get a high card (Jack or Higher), they get a smaller boost in confidence
		else if (hand[0].value > 10 || hand[1].value > 10){
			confidence += (rand() % 11 + 5) + hand[0].value + hand[1].value;
		}
		// Otherwise if they have matching suits, smaller boost in confidence
		else if (hand[0].suit == hand[1].suit) {
			confidence += (rand() % 6 + 5) + hand[0].value + hand[1].value;
		}
		// Otherwise their hand is pretty bad and should probably fold
		else {
			confidence += (rand() % 5 + 1) + hand[0].value + hand[1].value;
		}
	}

	// This loop will run after the computer has placed its first bet anad has access to community cards
	else {
		// This utilizes the score function
		// Returns a double x.y where x is the hand rank and y is the highest card value
		// Ex: 8.13 - Four of a Kind - Four Kings
		double handStrength = score(hand, community);
		// If the hand is at least a straight flush, confidence will be set to 85~100
		if (handStrength >= 9.0 ) { 
			confidence = (rand() % 16 + 85);
		}
		// If the hand is at least a straight, it'll get a fairly big boost to confidence
		else if (handStrength >= 5.0) {
			confidence = (rand() % 11 + 50) + (3 * handStrength);
		}
		// If the computer has at least a pair, then it'll gain a small amount of confidence
		else if (handStrength >= 2.0) {
			confidence = (rand() % 11 + 40) + (4 * handStrength);
		}
		// Otherwise, they only have a high card
		else {
			int highCardValue;
			// These two operations get the value of the numbers after the decimal of handStrength 
			highCardValue = (handStrength * 100);
			highCardValue = (highCardValue % 100);
			confidence = (rand() % 11 + 40) + (1.5 * highCardValue);
		}
	}
	return takeAction(confidence, betToMatch, currentContribution, potSize);
}

int Computer::takeAction(int confidence, int betToMatch, int currentContribution, int potSize) {
	// For a very high confidence, they will go all-in
	if (confidence >= 95) {
		return allIn();
	}

	// If their confidence is still high, they will opt to raise or call/check
	else if (confidence >= 75) {
		// If they have enough money, they will keep on betting
		if (money > betToMatch) {
			if ((rand() % 100 + 1) < confidence) {
				int amountToRaise = money - betToMatch;
				// cfactor returns a number from [confidence/10, confidence/10 + 5)
				// It is then divided by 10 again and that amount is used to get the raise amount
				double cfactor = (rand() % 11) + (confidence / 10);
				cfactor = cfactor / 100;
				amountToRaise = amountToRaise * cfactor;
				return raise(amountToRaise, betToMatch);
			}
			// If currentContribution is less than 5% ~ 10% of their total money, they will raise
			else if (currentContribution < (money / (rand() * 11 + 10))) {
				int amountToRaise = money - betToMatch;
				// cfactor returns a number from [confidence/10, confidence/10 + 5)
				// It is then divided by 10 again and that amount is used to get the raise amount
				double cfactor = (rand() % 11) + (confidence / 10);
				cfactor = cfactor / 100;
				amountToRaise = amountToRaise * cfactor;
				return raise(amountToRaise, betToMatch);
			}
			else if (betToMatch == 0) {
				return 0;
			}
			else {
				return call(betToMatch);
			}
		}
		// Else, if they don't have enough money to match the bet, there is a small chance they will
		// go all-in depending on pot size
		else {
			if (potSize > (2 * money)) {
				if ((rand() % 100 + 1) < (confidence / 8)) {
					return allIn();
				}
			}
			else {
				this->hasFolded = true;
				return 0;
			}
		}
	}

	// If their confidence is 40 or higher, they will usually call/check
	// Need to mess around with numbers
	else if (confidence >= 35){
		// If they have money to raise or check
		if (money > betToMatch) {
			// There is a confidence / 10 chance that the computer will raise
			if ((rand() % 100 + 1) < (confidence / 10)) {
				int amountToRaise = money - betToMatch;
				// cfactor returns a number from [confidence/10, confidence/10 + 5)
				// It is then divided by 10 again and that amount is used to get the raise amount
				double cfactor = (rand() % 5) + (confidence / 10);
				cfactor = cfactor / 100;
				amountToRaise = amountToRaise * cfactor;
				return raise(amountToRaise, betToMatch);
			}
			else if (betToMatch == 0) {
				return 0;
			}
			else if ((rand() % 100 + 1) < (confidence / 2)) {
				return call(betToMatch);
			}
			else {
				this->hasFolded = true;
				return 0;
			}
		}

		// If they don't have enough funds to do so, then they will check or fold
		else {
			if (potSize > (2 * money)) {
				if ((rand() % 100 + 1) < (confidence / 12)) {
					return allIn();
				}
			}
			else if (betToMatch == 0) {
				return 0;
			}
			else {
				this->hasFolded = true;
				return 0;
			}
		}
	}

	// Else, if they have a low confidence it will check if it can. Otherwise if will fold.
	else {
		// 1 in 1000 chance that it will all-in
		if ((rand() % 1000 + 1) == 1) {
			std::cout << "ALL IN HOMIE!!" << std::endl;
			return allIn();
		}
		else if (betToMatch == 0) {
			return 0;
		}
		else {
			this->hasFolded = true;
			return 0;
		}
	}
}

// Overridden function for computer that also resets their confidence
void Computer::resetPlayer() {
	hasFolded = false;
	hasAllIn = false;
	currentScore = 0;
	confidence = rand() % 21 + 5;
}

Player::~Player(){
	delete hand;
}

void Player::printHand(){
	std::cout << name << "'s hand is: ";
	std::cout << hand[0].value << hand[0].suit << " ";
	std::cout << hand[1].value << hand[1].suit << std::endl;;
}
