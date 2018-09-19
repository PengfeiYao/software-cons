/*
 * Sale.h
 *
 *  Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#ifndef SALE_H
#define SALE_H
#define TAX 0.08;
#define DISCOUNTPRICE 0.15;
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;
enum sale_type{REGULAR, DISCOUNT, MAILORDER};
class Sale
{
public:
	Sale();

	vector<string> descriptions;	// List of item descriptions
	vector<float> prices;			// List of item prices
	int type;						// Member variable for sales type
	float tax;						// Member variable for tax
	float subtotal;					// Member variable for subtotal
	float totalamount;				// Member variable for total amount
	string receipt;					// Stores all above information of sale, including pa
	vector<string> ID;

	virtual void process_payment();
	void print_sale();
	virtual void print_payment();
	void formatReceipt();

	// Getters and setters
	float calculateSubtotal(vector<float> prices);
	void setSubtotal(float newsub);
	float getSubtotal();
	float calculateDiscount();
	float calculateTax();
	void setTax(float newtax);
	float getTotal();
	void setTotal(float newtotal);
	void getDescriptions();
	void setDescriptions(vector<string> inventory);
	void getPrices();
	void setPrices(vector<float> prices);
	int getType();
	void setType(int salestype);
	string getID();
};
#endif /* SALE_H_ */
