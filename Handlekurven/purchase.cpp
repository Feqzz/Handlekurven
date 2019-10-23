#include "purchase.h"

purchase::purchase(std::string name_, double cost_)
	:name(name_), cost(cost_)
{
	time_t now = time(NULL);
	struct tm* test = gmtime(&now);
	char str[26];
	ctime_s(str, sizeof str, &now);
	timeOfPurchase = str;
	monthOfPurchase = test->tm_mon;
	dayOfPurchase = test->tm_mday;
	yearOfPurchase = test->tm_year;

	makePurchaseText();
}

purchase::purchase(std::string name_, double cost_, std::string timeOfPurchase_, int monthOfPurchase_, int dayOfPurchase_, int yearOfPurchase_)
	:name(name_), cost(cost_), timeOfPurchase(timeOfPurchase_), monthOfPurchase(monthOfPurchase_), dayOfPurchase(dayOfPurchase_), yearOfPurchase(yearOfPurchase_)
{
	makePurchaseText();
}

purchase::~purchase()
{
	std::cout << "Successfully deleted" << std::endl;
}

void purchase::print()
{
	int space = 13;
	std::cout << dayOfPurchase << "/" << monthOfPurchase + 1 << "/" << yearOfPurchase + 1900 << " --- " << name;
	if (dayOfPurchase < 10) space++;
	if (name.size() < space) for (int i = 0; i < (space - name.size()); i++) std::cout << " ";
	std::cout << " --- " << cost << "kr" << std::endl;
}

int purchase::getMonth()
{
	return monthOfPurchase;
}

double purchase::getCost()
{
	return cost;
}

void purchase::makePurchaseText()
{
	std::string printString;
	std::string costString;

	if (dayOfPurchase < 10) printString += "0";
	printString += std::to_string(dayOfPurchase);
	printString += "/";
	printString += std::to_string(monthOfPurchase + 1);
	printString += "/";
	printString += std::to_string(yearOfPurchase + 1900);
	printString += " - ";
	printString += name;
	costString = std::to_string(cost);
	costString.erase(costString.find_last_not_of('0') + 1, std::string::npos);
	costString.erase(costString.find_last_not_of('.') + 1, std::string::npos);
	costString += "kr";

	int totalStringSize = printString.size() + costString.size();
	for (int i = 0; i < (37 - totalStringSize); i++) printString += " ";

	printString += costString;
	

	purchaseText.setString(printString);
	purchaseText.setFillColor(sf::Color::Black);
	purchaseText.setCharacterSize(24);

}