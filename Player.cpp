/**
 * 	@file       header.h
 * 	@author(s)  Terry Thibault (tlt@cise.ufl.edu)
 * 		    Alexander Rumak (alexrumak.ufl.edu)
 		    Hugh Wu
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

/*********************************************************
 * @brief This function checks if the player has enough 
 * funds to make a bet. 
 ********************************************************/
bool Person::HasEnoughFunds(int bet)
{
	if (money < bet) return false;
	return true;
}

/*********************************************************
 * @brief This function will add money to the player money
 * in the event that they win a hand.
 ********************************************************/
void addMoney(int amount) 
{
	money += amount;
}

/*********************************************************
 * @brief This function is called by the table. Simply 
 * subtracts from the player cash and tells the table
 * how much to add to the pot. If the player does not have
 * enough money, they go all-in.
 ********************************************************/
int bet(int amount)
{
	if(HasEnoughFunds(amount))
	{
		money -= amount;
		return amount;
	}
	int temp = money;
	money = 0;
	return temp;
}

/*********************************************************
 * @brief This function's input is the largest previous 
 * bet. If the player does not have enough money to call,
 * they will go all-in. 
 ********************************************************/
void call(int prev_bet)
{
	if(HasEnoughFunds(prev_bet))
	{
		money -= amount;
		return;
	}
	money = 0;
	return;
}
/*********************************************************
 * @brief Returns a pointer to the player's hand.
 ********************************************************/
Card *checkHand() const
{
	return *hand;
}
/*********************************************************
 * @brief Gives the player their hand for the turn
 ********************************************************/
void Person::getHand(Card* givenHand){
	hand = givenHand;
}


