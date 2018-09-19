/*
 * CashSale.h
 *
*Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#ifndef CASHSALE_H
#define CASHSALE_H
#include "Sale.h"
class CashSale : public Sale
{
public:
	CashSale(vector<string> & inventory, vector<float> & pricelist, vector<string> id);
	float cashreceived;		// Member variable for amount of cash received for payment
	float changegiven;		// Member variable for amount of change given
	void process_payment();
	void print_sale();
	void print_payment();
	void setCashReceived(float cashin);
	float getCashReceived();
	void setChangeGiven(float change);
	float getChangeGiven();
};
#endif
