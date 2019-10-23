#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

class purchase
{
public:
	purchase(std::string name_, double cost_);
	purchase(std::string name_, double cost_, std::string timeOfPurchase_, int monthOfPurchase_, int dayOfPurchase_, int yearOfPurchase_);
	~purchase();
	void print();
	int getMonth();
	double getCost();
	void makePurchaseText();
	std::string name;
	std::string timeOfPurchase;
	int monthOfPurchase;
	int dayOfPurchase;
	int yearOfPurchase;
	double cost;
	sf::Text purchaseText;
};

