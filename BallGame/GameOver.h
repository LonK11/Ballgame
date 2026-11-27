#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class GameOver
{
private:
	sf::Font font;
	sf::Text titleText;
	sf::Text winnerText;

	sf::RectangleShape overlay;
	sf::RectangleShape glow;
	sf::RectangleShape panel;
	sf::RectangleShape border;

	sf::RectangleShape restartButton;
	sf::Text restartText;
	float restartScale = 1.f;

	sf::RectangleShape menuButton;
	sf::Text menuText;
	float menuScale = 1.f;
public:
	GameOver();

	void SetWinner(const std::string& winner);
	void Update(sf::RenderWindow& window, float deltaTime);
	void Draw(sf::RenderWindow& window);

	int HandleEvent(sf::RenderWindow& window, sf::Event& event);
};

