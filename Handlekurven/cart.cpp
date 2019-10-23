#include "cart.h"

cart::cart()
{
	fileName = "purchases";
	fileName += std::to_string(getCurrentYear());
	fileName += ".txt";
}

void cart::addPurchase(sf::String s, bool& showErrorText, bool& showAddedText)
{
	int spaceIndex = s.find(' ');
	std::string purchaseString = s.substring(0, spaceIndex);
	std::string costString = s.substring(spaceIndex + 1);
	try
	{
		double cost = std::stod(costString.c_str());
		std::cout << purchaseString << cost << std::endl;
		purchase* p = new purchase(purchaseString, cost);
		months[p->getMonth()].addPurchase(p);
		showAddedText = true;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error failed to convert to double" << std::endl;
		showErrorText = true;
	}
}

int cart::getCurrentYear()
{
	time_t now = time(NULL);
	struct tm* test = gmtime(&now);
	return (test->tm_year + 1900);
}

void cart::save()
{
	std::ofstream myfile;
	myfile.open(fileName);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < months[i].purchaseMonthList.size(); j++)
		{
			myfile << months[i].purchaseMonthList[j]->name << ',' << months[i].purchaseMonthList[j]->cost <<
				',' << months[i].purchaseMonthList[j]->timeOfPurchase << ',' << months[i].purchaseMonthList[j]->monthOfPurchase <<
				',' << months[i].purchaseMonthList[j]->dayOfPurchase <<
				',' << months[i].purchaseMonthList[j]->yearOfPurchase << ',';
		}
	}
	myfile.close();
	std::cout << "Saved" << std::endl;
}

void cart::load()
{
	std::ifstream myfile(fileName);
	std::string name;
	std::string cost;
	std::string timeOfPurchase;
	std::string monthOfPurchase;
	std::string dayOfPurchase;
	std::string yearOfPurchase;
	getline(myfile, name, ',');
	getline(myfile, cost, ',');
	getline(myfile, timeOfPurchase, ',');
	getline(myfile, monthOfPurchase, ',');
	getline(myfile, dayOfPurchase, ',');
	getline(myfile, yearOfPurchase, ',');
	int times = 0;
	while (myfile)
	{
		months[atoi(monthOfPurchase.c_str())].purchaseMonthList.push_back(new purchase(name, std::stod(cost.c_str()), timeOfPurchase,
			atoi(monthOfPurchase.c_str()), atoi(dayOfPurchase.c_str()), atoi(yearOfPurchase.c_str())));
		months[atoi(monthOfPurchase.c_str())].addMoneySpent(std::stod(cost.c_str()));
		times++;

		getline(myfile, name, ',');
		getline(myfile, cost, ',');
		getline(myfile, timeOfPurchase, ',');
		getline(myfile, monthOfPurchase, ',');
		getline(myfile, dayOfPurchase, ',');
		getline(myfile, yearOfPurchase, ',');
	}
	myfile.close();
	std::cout << "Successfully loaded in " << times << " purchases from " << fileName << std::endl;
}

void cart::makeAllMonthButtons(sf::Font font)
{
	for (int i = 0; i < 12; i++)
	{
		months[i].createMonthButton(i, monthNames[i], font);
	}
}