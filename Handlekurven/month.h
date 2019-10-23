#pragma once
#include "purchase.h"
class month
{
public:
	month();
	void addMoneySpent(double a);
	void addPurchase(purchase* a);
	void deletePurchase(int choice);
	void createMonthButton(int month, std::string monthName, sf::Font font);
	void updateMoneySpentText();
	void updatePurchaseTextPosition();
	sf::RectangleShape monthButton;
	sf::Text monthButtonText;
	sf::Text moneySpentText;
	std::vector<purchase*> purchaseMonthList;
	double moneySpent;
};

