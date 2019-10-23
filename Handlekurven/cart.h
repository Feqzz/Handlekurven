#pragma once
#include "month.h"
class cart
{
public:
	cart();
	void addPurchase(sf::String s, bool& showErrorText, bool& showAddedText);
	int getCurrentYear();
	void save();
	void load();
	void makeAllMonthButtons(sf::Font font);
	month months[12];
	std::vector<std::string> monthNames = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun", "Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec" };
	int monthToDisplay;
	std::string fileName;
};

