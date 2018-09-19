/*
 * CheckSale.h
 *
 *  Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#ifndef CHECKSALE_H
#define CHECKSALE_H
#include "Sale.h"
class CheckSale : public Sale
{
public:
	CheckSale(vector<string> inventory, vector<float> pricelist, vector<string> id);

	string name;			// Member variable for name on check
	string driverslicense;	// Member variable for driver's license number

	void process_payment();
	void print_sale();
	void print_payment();
	void setCashReceived(float cashin);
	float getCashReceived();
	void setChangeGiven(float change);
	float getChangeGiven();

	//Getters and setters
	void setName(string newname);
	string getName();
	void setNumber(string newnumber);
	string getNumber();
};
#endif
