#include "screens.h"
#include "cart.h"

//sf::Font cScreen::defaultFont; //Vet ikke hvorfor jeg må ha den her :/

int main()
{
	std::vector<cScreen*> screens;
	int screenIndex = 0;

	sf::RenderWindow App(sf::VideoMode(1024, 622), "Handlekurven", sf::Style::Close);
	sf::Image icon;
	icon.loadFromFile("res/icon32.bmp");
	App.setIcon(32, 32, icon.getPixelsPtr());
	App.setFramerateLimit(60);
	
	//cScreen::defaultFont.loadFromFile("res/DroidSansMono.ttf");

	screen_0 s0;
	screens.push_back(&s0);
	screen_1 s1;
	screens.push_back(&s1);
	screen_2 s2;
	screens.push_back(&s2);

	cart c;
	c.load();

	while (screenIndex >= 0)
	{
		screenIndex = screens[screenIndex]->Run(App, c);
	}
	return EXIT_SUCCESS;
}
