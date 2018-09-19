/*
 * CreditCardSale.cpp
 *
 *  Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#include "CreditCardSale.h"


CreditCardSale::CreditCardSale(vector<string> inventory, vector<float> pricelist, vector<string> id)
{
	descriptions.swap(inventory);
	prices.swap(pricelist);
	ID.swap(id);
	totalamount = 0;
	tax = 0;
	setType(prices.back());
	prices.pop_back();
	calculateSubtotal(prices);
}


void CreditCardSale::process_payment()
{
	// Enter name, credit card number and expiration date
	cout << "Enter name on the credit card: ";
	cout << endl << endl;
	while( getchar() != '\n' )
	{
		continue;
	}
	getline(cin, name, '\n');
	cout << "Enter credit card number: ";
	cin >> cardnumber;
	cout << endl << endl;
	cout << "Enter expiration date: ";
	cin >> expiration;
	formatReceipt();
}


void CreditCardSale::print_sale()
{
	print_payment();
}

void CreditCardSale::print_payment()
{
	string tempReceipt = receipt;
	ostringstream oss(ostringstream::out);
	oss << "\nCREDIT CARD\t" << name << " " << cardnumber << " " << expiration;
    oss << "\n";
	tempReceipt += oss.str();
	cout << tempReceipt;
}


void CreditCardSale::setName(string newname)
{
	name = newname;
}


string CreditCardSale::getName()
{
	return name;
}


void CreditCardSale::setExpiration(string newdate)
{
	expiration = newdate;
}


string CreditCardSale::getExpiration()
{
	return expiration;
}


void CreditCardSale::setCardNumber(string newnumber)
{
	cardnumber = newnumber;
}


string CreditCardSale::getCardNumber()
{
	return cardnumber;
}


