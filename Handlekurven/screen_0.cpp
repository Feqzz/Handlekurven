#include "screen_0.h"

int screen_0::Run(sf::RenderWindow& app, cart &c)
{
	sf::Event event;
	bool running = true;

	sf::Texture backgroundImage;
	backgroundImage.loadFromFile("res/osloKylling2.png");

	sf::Sprite background;
	background.setTexture(backgroundImage);

	sf::Font font;
	font.loadFromFile("res/DroidSansMono.ttf");

	sf::String userInput;

	sf::Text userText;
	userText.setFont(font);
	userText.setFillColor(sf::Color::Black);
	userText.setPosition(sf::Vector2f(142, 166));
	userText.setCharacterSize(52);
	bool showUserText = true;

	sf::Text buttonOneText;
	buttonOneText.setFont(font);
	buttonOneText.setString("Add");
	buttonOneText.setFillColor(sf::Color::Black);
	buttonOneText.setPosition(295, 370);

	sf::Text buttonTwoText;
	buttonTwoText.setFont(font);
	buttonTwoText.setString("Show");
	buttonTwoText.setFillColor(sf::Color::Black);
	buttonTwoText.setPosition(675, 370);

	sf::Text errorText;
	errorText.setFont(font);
	errorText.setString("Could not add purchase");
	errorText.setFillColor(sf::Color(235, 91, 52));
	errorText.setCharacterSize(30);
	errorText.setPosition(142, 180);
	bool showErrorText = false;

	sf::Text addedText;
	addedText.setFont(font);
	addedText.setString("Successfully added purchase");
	addedText.setFillColor(sf::Color(68, 194, 97));
	addedText.setCharacterSize(30);
	addedText.setPosition(142, 180);
	bool showAddedText = false;

	sf::RectangleShape inputBox;
	inputBox.setSize(sf::Vector2f(776, 100));
	inputBox.setFillColor(sf::Color::White);
	inputBox.setPosition(sf::Vector2f(132, 150));
	inputBox.setOutlineColor(sf::Color::Black);
	inputBox.setOutlineThickness(-1);

	sf::RectangleShape buttonOne;
	buttonOne.setSize(sf::Vector2f(194, 80));
	buttonOne.setFillColor(sf::Color(233, 239, 240));
	buttonOne.setPosition(sf::Vector2f(229, 350));
	buttonOne.setOutlineColor(sf::Color::Black);
	buttonOne.setOutlineThickness(-1);

	sf::RectangleShape buttonTwo;
	buttonTwo.setSize(sf::Vector2f(194, 80));
	buttonTwo.setFillColor(sf::Color(233, 239, 240));
	buttonTwo.setPosition(sf::Vector2f(617, 350));
	buttonTwo.setOutlineColor(sf::Color::Black);
	buttonTwo.setOutlineThickness(-1);

	sf::Clock myClock;
	bool showCursor = false;

	int inputLimit = 23;

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
					showErrorText = showAddedText = false;
					if (event.text.unicode < 128 || event.text.unicode == 248 || event.text.unicode == 229
						|| event.text.unicode == 230 || event.text.unicode == 198 || event.text.unicode == 216
						|| event.text.unicode == 197) //זרו + ֶ״ֵ valid input
					{
						if (event.text.unicode == '\b')
						{
							if (userInput.getSize())
							{
								userInput.erase(userInput.getSize() - 1, 1);
							}
						}
						else if (event.text.unicode == 13)
						{
							std::cout << "Enter has been pressed!" << std::endl;
							c.addPurchase(userInput, showErrorText, showAddedText);
							userInput.clear();
							userText.setString(userInput);
						}
						else
						{
							if (userInput.getSize() < inputLimit) userInput += event.text.unicode;
							showUserText = true;
						}
						userText.setString(userInput);
						std::cout << userInput.getSize() << std::endl;
					}
					break;
				}
				case sf::Event::EventType::MouseMoved:
				{
					
					if (buttonOne.getGlobalBounds().contains(mousePosF))
					{
						setWhiteColor(buttonOne);
					}
					else if (buttonTwo.getGlobalBounds().contains(mousePosF))
					{
						setWhiteColor(buttonTwo);
					}
					else
					{
						setDefaultColor(buttonOne);
						setDefaultColor(buttonTwo);
					}
					break;
				}
				case sf::Event::EventType::MouseButtonPressed:
				{
					showErrorText = showAddedText = false;
					showUserText = true;
					if (buttonOne.getGlobalBounds().contains(mousePosF))
					{
						std::cout << "ButtonOne has been Clicked!" << std::endl;
						c.addPurchase(userInput, showErrorText, showAddedText);
						userInput.clear();
						userText.setString(userInput);
					}
					else if (buttonTwo.getGlobalBounds().contains(mousePosF))
					{
						std::cout << "ButtonTwo has been Clicked!" << std::endl;
						return(1); 
					}
				}

			}
		}
		if (myClock.getElapsedTime() >= sf::milliseconds(500))
		{
			myClock.restart();
			showCursor = !showCursor;
			if (showCursor) userText.setString(userInput + "_");
			else userText.setString(userInput);
		}
		app.clear();
		app.draw(background);
		app.draw(inputBox);
		app.draw(buttonOne);
		app.draw(buttonTwo);
		if (showUserText) app.draw(userText);
		app.draw(buttonOneText);
		app.draw(buttonTwoText);
		if (showErrorText)
		{
			app.draw(errorText);
			showUserText = false;
		}
		if (showAddedText)
		{
			app.draw(addedText);
			showUserText = false;
		}
		app.display();
	}
	return (-1);
}