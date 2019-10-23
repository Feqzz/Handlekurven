#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cart.h"

class cScreen
{
public:
	virtual int Run(sf::RenderWindow& App, cart &c) = 0;
	void setDefaultColor(sf::RectangleShape& r);
	void setWhiteColor(sf::RectangleShape& r);
	//static sf::Font defaultFont;
};

