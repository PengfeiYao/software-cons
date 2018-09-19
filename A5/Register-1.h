/*
 * Register.h
 *
 *  Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#ifndef REGISTER_H
#define REGISTER_H
#define TAX  0.08;
#define DISCOUNTPRICE 0.15;
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "CashSale.h"
#include "CheckSale.h"
#include "CreditCardSale.h"
using namespace std;

class Register
{
public:
	Register();
	void beginItemize();
	void addItems();
	void enterItemName();
	void enterPrice();
	float calculateTempSubtotal(vector<float> prices);
	char choseOption();
	char choseSale();
	float calculateTempDiscount();
	void handleSales(char selection);
	float calculateTempTax();
	char chosePayment();
	void handlePayment(char pick);
	void newCashSale(char type);
	void newCheckSale(char type);
	void newCreditCardSale(char type);
	void printReceipts();
	void quite();
	bool endGame();
	bool end = false;
	vector<Sale *> saleslist;
	int numberOfSales;
	string sale;
	vector<string> itemNames;
	int numberOfItems;
	vector<float> itemPrices;
	float tempSubtotal;
	vector<string> ID; // discount ID
};
#endif
