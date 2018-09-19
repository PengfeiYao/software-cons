/*
 * CheckSale.cpp
 *
 *  Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#include "CheckSale.h"


CheckSale::CheckSale(vector<string> inventory, vector<float> pricelist, vector<string> id)
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


void CheckSale::process_payment()
{
	cout << endl << "Enter name on the check: ";
	while( getchar() != '\n' )
	{
		continue;
	}
	getline(cin, name, '\n');
	cout << endl << "Enter driver's license number: ";
	cin >> driverslicense;
	formatReceipt();
}


void CheckSale::print_sale()
{
	print_payment();
}


void CheckSale::print_payment()
{
	string tempReceipt = receipt;
	ostringstream oss(ostringstream::out);
	oss << "\nCHECK\t" << getName() << " " << getNumber();
	tempReceipt += oss.str();
	cout << tempReceipt;
}

void CheckSale::setName(string newname)
{
	name = newname;
}


string CheckSale::getName()
{
	return name;
}

void CheckSale::setNumber(string newnumber)
{
	driverslicense = newnumber;
}

string CheckSale::getNumber()
{
	return driverslicense;
}


