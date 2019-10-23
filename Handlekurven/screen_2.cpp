#include "screen_2.h"

int screen_2::Run(sf::RenderWindow& app, cart& c)
{
	sf::Event event;
	bool running = true;

	sf::Texture backgroundImage;
	backgroundImage.loadFromFile("res/osloKylling2.png");

	sf::Sprite background;
	background.setTexture(backgroundImage);

	sf::Font font;
	font.loadFromFile("res/DroidSansMono.ttf");

	sf::Text nextButtonText;
	nextButtonText.setFont(font);
	nextButtonText.setString("Next");
	nextButtonText.setFillColor(sf::Color::Black);
	nextButtonText.setCharacterSize(30);
	nextButtonText.setPosition(740, 165);

	sf::Text prevButtonText;
	prevButtonText.setFont(font);
	prevButtonText.setString("Prev");
	prevButtonText.setFillColor(sf::Color::Black);
	prevButtonText.setCharacterSize(30);
	prevButtonText.setPosition(740, 315);

	sf::Text deleteButtonText;
	deleteButtonText.setFont(font);
	deleteButtonText.setString("Delete");
	deleteButtonText.setFillColor(sf::Color::Black);
	deleteButtonText.setPosition(720, 415);

	sf::Text backButtonText;
	backButtonText.setFont(font);
	backButtonText.setString("Back");
	backButtonText.setFillColor(sf::Color::Black);
	backButtonText.setPosition(738, 540);

	sf::RectangleShape nextButton;
	nextButton.setSize(sf::Vector2f(150, 75));
	nextButton.setFillColor(sf::Color(233, 239, 240));
	nextButton.setPosition(sf::Vector2f(700, 150));
	nextButton.setOutlineColor(sf::Color::Black);
	nextButton.setOutlineThickness(-1);
	bool showNextButton = false;

	sf::RectangleShape prevButton;
	prevButton.setSize(sf::Vector2f(150, 75));
	prevButton.setFillColor(sf::Color(233, 239, 240));
	prevButton.setPosition(sf::Vector2f(700, 300));
	prevButton.setOutlineColor(sf::Color::Black);
	prevButton.setOutlineThickness(-1);
	bool showPrevButton = false;

	sf::RectangleShape deleteButton;
	deleteButton.setSize(sf::Vector2f(150, 75));
	deleteButton.setFillColor(sf::Color(233, 239, 240));
	deleteButton.setPosition(sf::Vector2f(700, 400));
	deleteButton.setOutlineColor(sf::Color::Black);
	deleteButton.setOutlineThickness(-1);

	sf::RectangleShape box;
	box.setSize(sf::Vector2f(780, 400));
	box.setFillColor(sf::Color::White);
	box.setPosition(sf::Vector2f(130, 100));
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(-1);

	sf::RectangleShape backButton;
	backButton.setSize(sf::Vector2f(150, 70));
	backButton.setFillColor(sf::Color(233, 239, 240));
	backButton.setPosition(sf::Vector2f(700, 525));
	backButton.setOutlineColor(sf::Color::Black);
	backButton.setOutlineThickness(-1);

	float pageLimitF = 12.0; //Viktig med .0 ellers blir den ikke en float
	int pageLimit = 12;
	int pageNum = 0;
	int deleteIndex = -1; //En ulovlig verdi

	showNextButton = (c.months[c.monthToDisplay].purchaseMonthList.size() > pageLimit);

	for (int j = 0; j < c.months[c.monthToDisplay].purchaseMonthList.size(); j++)
	{
		c.months[c.monthToDisplay].purchaseMonthList[j]->purchaseText.setFont(font);
	}

	c.months[c.monthToDisplay].updateMoneySpentText();
	c.months[c.monthToDisplay].updatePurchaseTextPosition();

	while (running)
	{
		while (app.pollEvent(event))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(app);
			sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			switch (event.type)
			{
				case sf::Event::EventType::Closed:
				{
					c.save();
					app.close();
					return(-1);
					break;
				}
				case sf::Event::EventType::TextEntered:
				{
					if (event.text.unicode == 27)
					{
						return(1);
					}
				}
				case sf::Event::EventType::MouseMoved:
				{
					if (nextButton.getGlobalBounds().contains(mousePosF) && showNextButton == true)
					{
						setWhiteColor(nextButton);

					}
					else if (prevButton.getGlobalBounds().contains(mousePosF) && showPrevButton == true)
					{
						setWhiteColor(prevButton);
					}
					else if (deleteButton.getGlobalBounds().contains(mousePosF))
					{
						setWhiteColor(deleteButton);
					}
					else if (backButton.getGlobalBounds().contains(mousePosF))
					{
						setWhiteColor(backButton);
					}
					else
					{
						setDefaultColor(nextButton);
						setDefaultColor(prevButton);
						setDefaultColor(deleteButton);
						setDefaultColor(backButton);
					}
					break;
				}
				case sf::Event::EventType::MouseButtonPressed:
				{
					if (nextButton.getGlobalBounds().contains(mousePosF) && showNextButton == true)
					{
						std::cout << "Next button has been pressed" << std::endl;
						pageNum++;
						showPrevButton = true;
						showNextButton = ((c.months[c.monthToDisplay].purchaseMonthList.size() / pageLimitF) > (pageNum+1));
					}
					else if (prevButton.getGlobalBounds().contains(mousePosF) && showPrevButton == true)
					{
						std::cout << "Prev button has been pressed" << std::endl;
						pageNum--;
						showNextButton = ((c.months[c.monthToDisplay].purchaseMonthList.size() / pageLimitF) > (pageNum+1));
						if (pageNum == 0) showPrevButton = false;
					}
					else if (backButton.getGlobalBounds().contains(mousePosF))
					{
						return(1);
					}
					if (deleteButton.getGlobalBounds().contains(mousePosF))
					{
						std::cout << "delete button has been pressed" << std::endl;
						if (deleteIndex != -1) c.months[c.monthToDisplay].deletePurchase(deleteIndex);
						showNextButton = ((c.months[c.monthToDisplay].purchaseMonthList.size() / pageLimitF) > (pageNum + 1));
						c.months[c.monthToDisplay].updatePurchaseTextPosition();
						deleteIndex = -1;
						c.months[c.monthToDisplay].updateMoneySpentText();

						if (c.months[c.monthToDisplay].purchaseMonthList.size() % pageLimit == 0)
						{
							pageNum--;
							showNextButton = ((c.months[c.monthToDisplay].purchaseMonthList.size() / pageLimitF) > (pageNum + 1));
							if (pageNum == 0) showPrevButton = false;
						}
						if (pageNum == -1) return(1);
					}
					else
					{
						for (int j = 0; j < 12; j++)
						{
							if ((j + (pageNum*pageLimit) < (c.months[c.monthToDisplay].purchaseMonthList.size())
								&& c.months[c.monthToDisplay].purchaseMonthList[j + (pageNum*pageLimit)]->purchaseText.getGlobalBounds().contains(mousePosF)))
							{
								deleteIndex = (j + (pageNum*pageLimit));
								std::cout << "Text : " << deleteIndex << " has been toggled" << std::endl;

							}
						}
					}
				}

			}
		}
		app.clear();
		app.draw(background);
		app.draw(box);
		for (int j = 0; j < pageLimit; j++)
		{
			if ((j + (pageNum*pageLimit) < (c.months[c.monthToDisplay].purchaseMonthList.size())))
			{
				c.months[c.monthToDisplay].purchaseMonthList[j + (pageNum * pageLimit)]->purchaseText.setStyle(sf::Text::Regular);
				if (deleteIndex != -1)
				{
					c.months[c.monthToDisplay].purchaseMonthList[deleteIndex]->purchaseText.setStyle(sf::Text::Bold);
				}
				app.draw(c.months[c.monthToDisplay].purchaseMonthList[j + (pageNum * pageLimit)]->purchaseText);
			}
		}
		app.draw(c.months[c.monthToDisplay].moneySpentText);
		if (showNextButton)
		{
			app.draw(nextButton);
			app.draw(nextButtonText);
		}
		if (showPrevButton)
		{
			app.draw(prevButton);
			app.draw(prevButtonText);
		}
		app.draw(c.months[c.monthToDisplay].moneySpentText);
		app.draw(deleteButton);
		app.draw(deleteButtonText);
		app.draw(backButton);
		app.draw(backButtonText);
		app.display();
	}
	return EXIT_FAILURE;
}

