#include "screen_1.h"

int screen_1::Run(sf::RenderWindow& app, cart &c)
{
	sf::Event event;
	bool running = true;

	sf::Texture backgroundImage;
	backgroundImage.loadFromFile("res/osloKylling2.png");

	sf::Sprite background;
	background.setTexture(backgroundImage);

	sf::Font font;
	font.loadFromFile("res/DroidSansMono.ttf");

	c.makeAllMonthButtons(font);
	for (int i = 0; i < 12; i++)
	{
		c.months[i].monthButtonText.setFont(font);
		c.months[i].moneySpentText.setFont(font);
		if (c.months[i].moneySpent != 0) setDefaultColor(c.months[i].monthButton);
	}

	sf::Text backButtonText;
	backButtonText.setFont(font);
	backButtonText.setString("Back");
	backButtonText.setFillColor(sf::Color::Black);
	backButtonText.setPosition(738, 540);

	sf::RectangleShape backButton;
	backButton.setSize(sf::Vector2f(150, 70));
	backButton.setFillColor(sf::Color(233, 239, 240));
	backButton.setPosition(sf::Vector2f(700, 525));
	backButton.setOutlineColor(sf::Color::Black);
	backButton.setOutlineThickness(-1);

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
						return(0); //Goes to screen_0 (main menu)
					}
					break;
				}
				case sf::Event::EventType::MouseMoved:
				{
					if (backButton.getGlobalBounds().contains(mousePosF))
					{
						setWhiteColor(backButton);
					}
					else
					{
						setDefaultColor(backButton);
						for (int i = 0; i < 12; i++)
						{
							if (c.months[i].monthButton.getGlobalBounds().contains(mousePosF) && c.months[i].moneySpent != 0)
							{

								setWhiteColor(c.months[i].monthButton);
							}
							else
							{
								if (c.months[i].moneySpent != 0)
								{
									setDefaultColor(c.months[i].monthButton);
								}
							}
						}
					}
					break;
				}
				case sf::Event::EventType::MouseButtonPressed:
				{
					if (backButton.getGlobalBounds().contains(mousePosF))
					{
						return(0);
					}
					else
					{
						for (int i = 0; i < 12; i++)
						{
							if (c.months[i].monthButton.getGlobalBounds().contains(mousePosF) && c.months[i].moneySpent != 0)
							{
								std::cout << c.monthNames[i] << " has been pressed" << std::endl;
								c.monthToDisplay = i;
								return (2);
							}
						}
					}
					break;
				}
			}
		}
		app.clear();
		app.draw(background);
		for (int i = 0; i < 12; i++)
		{
			app.draw(c.months[i].monthButton);
			app.draw(c.months[i].monthButtonText);
		}
		app.draw(backButton);
		app.draw(backButtonText);
		app.display();
	}
	return (-1);
}