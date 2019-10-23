#include "month.h"

month::month()
	:moneySpent(0)
{
}

void month::addMoneySpent(double a)
{
	moneySpent += a;
}

void month::addPurchase(purchase* a)
{
	purchaseMonthList.push_back(a);
	addMoneySpent(a->getCost());
	std::cout << "Successfully added" << std::endl;
}

void month::deletePurchase(int choice)
{
	purchase* purchaseToBeDeleted = purchaseMonthList[choice];
	moneySpent -= purchaseToBeDeleted->getCost();
	purchaseMonthList.erase(purchaseMonthList.begin() + choice);
	delete purchaseToBeDeleted;
}

void month::createMonthButton(int month, std::string monthName, sf::Font font)
{
	sf::RectangleShape button;
	button.setSize(sf::Vector2f(130, 100));
	if (!moneySpent)
	{
		button.setFillColor(sf::Color(199, 199, 199));
	}
	else
	{
		button.setFillColor(sf::Color(233, 239, 240));
	}

	sf::Text buttonText;
	buttonText.setString(monthName);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setPosition(0, 0);
	if (month < 6)
	{
		button.setPosition(sf::Vector2f(130 * (1 + month), 100));
		buttonText.setPosition((130 * (1 + month)) + 40, 130);
	}
	else
	{
		button.setPosition(sf::Vector2f(130 * (1 + month - 6), 200));
		buttonText.setPosition((130 * (1 + month - 6)) + 40, 230);
	}
	button.setOutlineColor(sf::Color::Black);
	button.setOutlineThickness(-1);

	sf::Text moneyText;
	moneyText.setFillColor(sf::Color::Black);
	moneyText.setPosition(138, 456);

	monthButton = button;
	monthButtonText = buttonText;
	moneySpentText = moneyText;
}

void month::updateMoneySpentText()
{
	std::string s = "Total spent: ";
	s += std::to_string(moneySpent);
	s.erase(s.find_last_not_of('0') + 1, std::string::npos);
	s.erase(s.find_last_not_of('.') + 1, std::string::npos);
	s += "kr";
	moneySpentText.setString(s);
}

void month::updatePurchaseTextPosition()
{
	for (int j = 0; j < purchaseMonthList.size(); j++)
	{
		purchaseMonthList[j]->purchaseText.setPosition(140, 110 + (j % 12 * 26));  //Modulo so the next page of lists starts with the upper position
	}
}
