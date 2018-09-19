/*
 * CreditCardSale.h
 *
 *  Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#ifndef CREDITCARDSALE_H
#define CREDITCARDSALE_H
#include "Sale.h"
class CreditCardSale : public Sale
{
public:
	CreditCardSale(vector<string> inventory, vector<float> pricelist, vector<string> id);

	string name;		// Member variable for name on card
	string expiration;	// Member variable for expiration date on card
	string cardnumber;	// Member variable for card number

	void process_payment();
	void print_sale();
	void print_payment();

	// Getter and setters
	void setName(string);
	string getName();
	void setExpiration(string);
	string getExpiration();
	void setCardNumber(string);
	string getCardNumber();
};
#endif
