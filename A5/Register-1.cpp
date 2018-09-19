/*
 * Register.cpp
 *
 *  Created on: 217/12/1
 *      Author: pengfeiyao
 *      email: pzy0006
 */

#include "Register.h"

	// Function: parameterless construction for Register
	Register::Register()
	{
		numberOfSales = 0;
		numberOfItems = 0;
		tempSubtotal = 0;
	}

	void Register::beginItemize()
	{
		cout << "\n\n\t***********************************************************************************" << endl;
		cout << "\t|				Welcome to Tiger Store!		  	          |" << endl;
		cout << "\t***********************************************************************************" << endl;
		cout << "Select an option: (1) Regular Cash, (2) Regular Check, (3) Regular Credit Card, (4) Contract Cash";
		cout << ", (5) Contract Check, (6) Contract Credit Card, (7) Print all sales, or (8) Quit :";
		numberOfSales++;
		//cout << "Enter payment(p) or print sales(s): ";
		switch (choseOption())
		{	// Enter payment
			case '1':
				addItems();
				handleSales(choseSale());
				handlePayment('c');
				break;
			case '2':
				addItems();
				handleSales(choseSale());
				handlePayment('k');
				break;
			case '3':
				addItems();
				handleSales(choseSale());
				handlePayment('d');
				break;
			case '4':
				addItems();
				handleSales(choseSale());
				handlePayment('c');
				break;
			case '5':
				addItems();
				handleSales(choseSale());
				handlePayment('k');
				break;
			case '6':
				addItems();
				handleSales(choseSale());
				handlePayment('d');
				break;
			case '7':
				printReceipts();
				break;
			case '8':
				quite();

				endGame();
				break;
			default:
				cout << "Invalid input." << endl;
				break;
		}
	}


	void Register::printReceipts()
	{
		vector<Sale*>::iterator s;
		int i = 0;
		for(s = saleslist.begin(); s < saleslist.end(); s++,i++)
		{
			cout << endl << "Sales #" << (i + 1) << ":" << endl;
			(*s)->print_sale();
		}
		cout << endl << "END" << endl;
	}

	void Register::handleSales(char selection)
	{
		switch (selection)
		{	// Regular
			case 'R':	cout << "Tax: $" << calculateTempTax() << endl << endl;
						cout << "Total amount: $" << tempSubtotal << endl << endl;
						itemPrices.push_back(REGULAR);
						break;
			// Discount
			case 'C':
				cout << endl << "Contractor ID: ";
				string id = "";
				cin >> id;
				cout << endl;
				cout << "Discount: $" << calculateTempDiscount() << endl << endl;
				cout << "Sub-Total: $" << tempSubtotal << endl << endl;
				cout << "Tax: $" << calculateTempTax() << endl << endl;
				cout << "Total amount: $" << tempSubtotal << endl << endl;
				ID.push_back(id);
				itemPrices.push_back(DISCOUNT);
				break;

		}

	}
	void Register::handlePayment(char pick)
	{
		switch	(pick)
		{	// Cash
			case 'c':	newCashSale(pick);
						break;
			// Check
			case 'k':	newCheckSale(pick);
						break;
			// Credit Card
			case 'd':	newCreditCardSale(pick);
						break;
		}
	}
	void Register::newCashSale(char type)
	{
		CashSale *temp = new CashSale(itemNames, itemPrices, ID);
		temp->process_payment();
		saleslist.push_back(temp);
	}
	void Register::newCheckSale(char type)
	{
		CheckSale *temp = new CheckSale(itemNames, itemPrices, ID);
		temp->process_payment();
		saleslist.push_back(temp);
	}
	void Register::newCreditCardSale(char type)
	{
		CreditCardSale *temp = new CreditCardSale(itemNames, itemPrices, ID);
		temp->process_payment();
		saleslist.push_back(temp);
	}
	void Register::addItems()
	{
		// Set numberOfItems to zero - new Sale object has begun
		numberOfItems = 0;
		// Clear both temporary vectors - new Sale object has begun
		itemNames.clear();
		itemPrices.clear();
		string itemName = "";
		float itemPrice = 0;
		while(true)
		{
			cout << "Enter item: ";
			while( getchar() != '\n')
			{
				continue;
			}
			getline(cin, itemName, '\n');
			cout << endl;
			if(itemName == "*")
			{
				// Stop itemization
				break;
			}
			numberOfItems++;
			cout << "Enter amount: $";
			itemPrice = 0;
			cin >> itemPrice;

			cout << endl;
			itemNames.push_back(itemName);
			itemPrices.push_back(itemPrice);
		}
		tempSubtotal = calculateTempSubtotal(itemPrices);
		cout.precision(2);
		cout << "Sub-total: $" << fixed << tempSubtotal << endl;
		cout << endl;
	}

	float Register::calculateTempSubtotal(vector<float> prices)
	{
		float sub = 0;
		for(int i = 0; i < numberOfItems; i++)
		{
			sub+= prices.at(i);
		}
		return sub;
	}

	char Register::choseOption()
	{
		string option;
		while(true)
		{
			option = "";
			cin >> option;
			if(option.length() >= 1 && option != "1" && option != "2" && option != "3"
					&& option != "4" && option != "5" && option != "5" && option != "6"
							&& option != "7" && option != "8")
			{
				cout << "Invalid response. Please type only a single character: '1,2,3,4,5,6,7,8'." << endl;
				cout << "Enter reponse: ";
			}
			else if(option == "1" || option == "2" || option == "3" || option == "4"
					|| option == "5" || option == "6" || option == "7" || option == "8")
			{
				return option.at(0);
			}
		}
	}

	char Register::choseSale()
	{
		//string sale;
		while(true)
		{
			sale = "";
			//getline(cin, sale, '\n');
			cin >> sale;
			//itemNames.push_back(sale);
			if(sale.length() >= 1 && sale.at(0) != 'C' && sale.at(0) != 'R')
			{
				cout << "Invalid response. Please re-chose your sale type as 'Regular sale and Contractor Sale.'" << endl;
				cout << "Enter response: ";
			}
			else if(sale.at(0) == 'R' || sale.at(0) == 'C')
			{
				return sale.at(0);
			}
		}
	}

	float Register::calculateTempDiscount()
	{
		float discount = tempSubtotal * DISCOUNTPRICE;
		// Update new subtotal
		tempSubtotal = tempSubtotal - (floorf(discount * 100 + 0.5) / (100));
		return floorf(discount * 100 + 0.5) / 100;
	}

	float Register::calculateTempTax()
	{
		float tax = tempSubtotal * TAX;
		tempSubtotal = tempSubtotal + (floorf(tax * 100 + 0.5) / (100));
		return floorf(tax * 100 + 0.5) / 100;
	}

	char Register::chosePayment()
	{
		string payment;
		while(true)
		{
			payment = "";
			cin >> payment;
			if(payment.length() >= 1 && payment != "c" && payment != "k" && payment != "d")
			{
				cout << "Invalid response. Please type only a single character: 'c' 'k' or 'd'." << endl;
				cout << "Enter reponse: ";
			}
			else if(payment == "c" || payment == "k" || payment == "d")
			{
				return payment.at(0);
			}
		}
	}
	void Register::quite() {
		cout << "Thank you for using this system." << endl;
		end = true;
	}
	bool Register::endGame() {
		//end = false;
		return end;
	}

