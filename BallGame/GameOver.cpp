#include "GameOver.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <string>

GameOver::GameOver()
{
	if (!font.loadFromFile("Fonts/arialmt.ttf"))
	{
		throw std::runtime_error("Не удалось загрузить шрифт меню");
	}

	overlay.setSize(sf::Vector2f(1600.f, 900.f));
	overlay.setFillColor(sf::Color(0, 0, 15, 150));

	glow.setSize(sf::Vector2f(600.f, 400.f));
	glow.setOrigin(300.f, 200.f);
	glow.setPosition(800.f, 450.f);
	glow.setFillColor(sf::Color::Transparent);
	glow.setOutlineThickness(8.f);
	glow.setOutlineColor(sf::Color(0, 220, 255, 35));

	panel.setSize(sf::Vector2f(600.f, 400.f));
	panel.setOrigin(300.f, 200.f);
	panel.setPosition(800.f, 450.f);
	panel.setFillColor(sf::Color(10, 15, 35, 230));

	border.setSize(sf::Vector2f(600.f, 400.f));
	border.setOrigin(300.f, 200.f);
	border.setPosition(800.f, 450.f);
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(2.f);
	border.setOutlineColor(sf::Color(0, 220, 255, 255));

	titleText.setFont(font);
	titleText.setString("GAME OVER");
	titleText.setCharacterSize(50);
	titleText.setFillColor(sf::Color(0 , 220,255));

	sf::FloatRect bounds = titleText.getLocalBounds();
	titleText.setOrigin(
		bounds.left + bounds.width / 2.f,
		bounds.top + bounds.height / 2.f
	);
	titleText.setPosition(800.f, 330.f);

	winnerText.setFont(font);
	winnerText.setCharacterSize(30);
	winnerText.setFillColor(sf::Color::White);
	winnerText.setPosition(800.f, 430.f);

	//Кнопки
	restartButton.setSize(sf::Vector2f(200.f, 55.f));
	restartButton.setOrigin(100.f, 27.5f);
	restartButton.setPosition(800.f, 510.f);
	restartButton.setFillColor(sf::Color(10, 40, 65, 230));
	restartButton.setOutlineThickness(1.5f);
	restartButton.setOutlineColor(sf::Color(0, 220, 255));

	restartText.setFont(font);
	restartText.setString("Restart");
	restartText.setCharacterSize(24);
	restartText.setFillColor(sf::Color::White);

	sf::FloatRect restartBounds = restartText.getLocalBounds();

	restartText.setOrigin(
		restartBounds.left + restartBounds.width / 2.f,
		restartBounds.top + restartBounds.height / 2.f
	);

	restartText.setPosition(800.f, 510.f);

	menuButton.setSize(sf::Vector2f(200.f, 55.f));
	menuButton.setOrigin(100.f, 27.5f);
	menuButton.setPosition(800.f, 580.f);
	menuButton.setFillColor(sf::Color(10, 40, 65, 230));
	menuButton.setOutlineThickness(1.5f);
	menuButton.setOutlineColor(sf::Color(0, 220, 255));

	menuText.setFont(font);
	menuText.setString("Main menu");
	menuText.setCharacterSize(24);
	menuText.setFillColor(sf::Color::White);

	sf::FloatRect menuBounds = menuText.getLocalBounds();

	menuText.setOrigin(
		menuBounds.left + menuBounds.width / 2.f,
		menuBounds.top + menuBounds.height / 2.f
	);

	menuText.setPosition(800.f, 580.f);
}

void GameOver::SetWinner(const std::string& winner) {
	winnerText.setString(winner);

	sf::FloatRect bounds = winnerText.getLocalBounds();

	winnerText.setOrigin(
		bounds.left + bounds.width / 2.f,
		bounds.top + bounds.height / 2.f
	);
}

void GameOver::Update(sf::RenderWindow& window, float deltaTime) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (restartButton.getGlobalBounds().contains(
		static_cast<float>(mousePosition.x),
		static_cast<float>(mousePosition.y)))
	{
		restartButton.setFillColor(sf::Color(0, 100, 140, 230));
		restartText.setFillColor(sf::Color::Yellow);
		restartScale += 3.f * deltaTime;

		if (restartScale > 1.08f)
			restartScale = 1.08f;
	}
	else
	{
		restartButton.setFillColor(sf::Color(10, 40, 65, 230));
		restartText.setFillColor(sf::Color::White);
		restartScale -= 3.f * deltaTime;

		if (restartScale < 1.f)
			restartScale = 1.f;
	}

	if (menuButton.getGlobalBounds().contains(
		static_cast<float>(mousePosition.x),
		static_cast<float>(mousePosition.y)))
	{
		menuButton.setFillColor(sf::Color(0, 100, 140, 230));
		menuText.setFillColor(sf::Color::Yellow);
		menuScale += 3.f * deltaTime;

		if (menuScale > 1.08f)
			menuScale = 1.08f;
	}
	else
	{
		menuButton.setFillColor(sf::Color(10, 40, 65, 230));
		menuText.setFillColor(sf::Color::White);
		menuScale -= 3.f * deltaTime;

		if (menuScale < 1.f)
			menuScale = 1.f;
	}

	restartButton.setScale(restartScale, restartScale);
	restartText.setScale(restartScale, restartScale);
	menuButton.setScale(menuScale, menuScale);
	menuText.setScale(menuScale, menuScale);
}

int GameOver::HandleEvent(sf::RenderWindow& window, sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (restartButton.getGlobalBounds().contains(
			static_cast<float>(mousePosition.x),
			static_cast<float>(mousePosition.y)))
		{
			return 1;
		}
	}
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (menuButton.getGlobalBounds().contains(
			static_cast<float>(mousePosition.x),
			static_cast<float>(mousePosition.y)))
		{
			return 2;
		}
	}

	return 0;
}

void GameOver::Draw(sf::RenderWindow& window) {
	window.draw(overlay);
	window.draw(panel);
	window.draw(glow);
	window.draw(border);
	window.draw(titleText);
	window.draw(winnerText);
	window.draw(restartButton);
	window.draw(restartText);
	window.draw(menuButton);
	window.draw(menuText);
}