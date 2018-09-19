/*
 * CashSale.cpp
 *
 * Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#include "CashSale.h"


CashSale::CashSale(vector<string> & inventory, vector<float> & pricelist, vector<string> id)
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


void CashSale::process_payment()
{
	cout << "Amount received: $";
	cin >> cashreceived;
	//getline(cin, cashreceived);
	switch (getType())
	{
		case REGULAR:	calculateTax();
						setChangeGiven(cashreceived - getTotal());
						cout << endl << "Change: $" << getChangeGiven() << endl;
						break;
		case DISCOUNT:	calculateDiscount();
						calculateTax();
						setChangeGiven(cashreceived - getTotal());
						cout << endl << "Change: $" << getChangeGiven() << endl;
						break;

	}
	formatReceipt();
}


void CashSale::print_sale()
{
	print_payment();
}


void CashSale::print_payment()
{
	string tempReceipt = receipt;
	ostringstream oss(ostringstream::out);
	oss.precision(2);
	oss << "\nCASH";
	oss << "\nAmount received:\t$ " << fixed << getCashReceived();
	oss << "\nChange:\t$ " << fixed << getChangeGiven();
	tempReceipt += oss.str();
	cout << tempReceipt;
}


void CashSale::setCashReceived(float cashin)
{
	cashreceived = cashin;
}


float CashSale::getCashReceived()
{
	return cashreceived;
}


void CashSale::setChangeGiven(float change)
{
	changegiven = change;
}


float CashSale::getChangeGiven()
{
	return changegiven;
}


