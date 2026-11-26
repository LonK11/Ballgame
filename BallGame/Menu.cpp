#include "Menu.h"
#include <stdexcept>
#include <cstdlib>
#include <cmath>
/**
* @brief Класс меню
* @details 
*/
Menu::Menu()
{
	background.setSize(sf::Vector2f(1600.f, 900.f));
	background.setFillColor(sf::Color(5, 5, 20));
	if (!font.loadFromFile("Fonts/arialmt.ttf"))
	{
		throw std::runtime_error("Не удалось загрузить шрифт меню");
	}
	for (int i = 0; i < 150; i++) {
		Star star;
		
		float radius = 0.5f + static_cast<float>(rand() % 25) / 10.f;
		star.shape.setRadius(radius);

		star.shape.setPosition(
			static_cast<float>(rand() % 1600),
			static_cast<float>(rand() % 900)
		);

		star.shape.setFillColor(sf::Color::White);
		star.shape.setOrigin(radius, radius);

		float glowRadius = radius * 3.f;

		star.glow.setRadius(glowRadius);
		star.glow.setFillColor(sf::Color(100, 160, 255, 20));
		star.glow.setOrigin(glowRadius, glowRadius);

		star.speed = 15.f + radius * 20.f;

		star.twinkleTime = static_cast<float>(rand() % 100) / 10.f;
		star.twinkleSpeed = 1.f + static_cast<float>(rand() % 30) / 10.f;

		stars.push_back(star);
	}

	// Текст для Play
	playText.setFont(font);
	playText.setString("Play");
	playText.setCharacterSize(50);
	sf::FloatRect playBouns = playText.getLocalBounds();
	playText.setOrigin(
		playBouns.left + playBouns.width / 2.f,
		playBouns.top + playBouns.height / 2.f
	);
	playText.setFillColor(sf::Color::White);
	// Текст для Exit
	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setCharacterSize(50);
	sf::FloatRect exitBouns = exitText.getLocalBounds();
	exitText.setOrigin(
		exitBouns.left + exitBouns.width / 2.f,
		exitBouns.top + exitBouns.height / 2.f
	);
	exitText.setFillColor(sf::Color::White);
	// Текст для Title
	titleText.setFont(font);
	titleText.setString("Space pong");
	titleText.setCharacterSize(80);
	sf::FloatRect titleBouns = titleText.getLocalBounds();
	titleText.setOrigin(
		titleBouns.left + titleBouns.width / 2.f,
		titleBouns.top + titleBouns.height / 2.f
	);
	titleText.setFillColor(sf::Color::White);

	// Установка текста в окне
	playText.setPosition(775.f, 525.f);
	exitText.setPosition(775.f, 625.f);
	titleText.setPosition(775.f, 270.f);
}
/**
* @brief Метод обновления 
* @details Метод занимается обновлением статуса или состояния обьектов
*/
void  Menu::Update(sf::RenderWindow& window, float deltaTime)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (playText.getGlobalBounds().contains(
		static_cast<float>(mousePosition.x),
		static_cast<float>(mousePosition.y)))
	{
		playText.setFillColor(sf::Color::Yellow);

		playScale += 3.f * deltaTime;

		if (playScale > 1.15f)
			playScale = 1.15f;
	}
	else
	{
		playText.setFillColor(sf::Color::White);

		playScale -= 3.f * deltaTime;

		if (playScale < 1.f)
			playScale = 1.f;
	}
	if (exitText.getGlobalBounds().contains(
		static_cast<float>(mousePosition.x),
		static_cast<float>(mousePosition.y)))
	{
		exitText.setFillColor(sf::Color::Yellow);

		exitScale += 3.f * deltaTime;

		if (exitScale > 1.15f)
			exitScale = 1.15f;
	}
	else
	{
		exitText.setFillColor(sf::Color::White);

		exitScale -= 3.f * deltaTime;

		if (exitScale < 1.f)
			exitScale = 1.f;
	}
	if (titleGrowing)
	{
		titleScale += 0.1f * deltaTime;

		if (titleScale >= 1.05f)
			titleGrowing = false;
	}
	else
	{
		titleScale -= 0.1f * deltaTime;

		if (titleScale <= 1.f)
			titleGrowing = true;
	}
	
	for (auto& star : stars)
	{
		star.shape.move(0.f, star.speed * deltaTime);

		if(star.shape.getPosition().y > 900)
		{
			star.shape.setPosition(
				static_cast<float>(rand() % 1600),
				-5.f
			);
		}
		star.glow.setPosition(star.shape.getPosition());

		star.twinkleTime += star.twinkleSpeed * deltaTime;
		float brightness = (std::sin(star.twinkleTime) + 1.f) / 2.f;
		sf::Uint8 alpha = static_cast<sf::Uint8>(15.f + brightness * 60.f);

		star.glow.setFillColor(sf::Color(100, 160, 255, alpha));
	}

	titleText.setScale(titleScale, titleScale);
	playText.setScale(playScale, playScale);
	exitText.setScale(exitScale, exitScale);
}
/**
* @brief Метод обработки нажатия
* @details Метод занимается определением статуса при нажатии определенной кнопки
*/
int Menu::HandleEvent(sf::RenderWindow& window, const sf::Event& event) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		if (playText.getGlobalBounds().contains(
			static_cast<float>(mousePosition.x),
			static_cast<float>(mousePosition.y)))
		{
			return 1;
		}

		if (exitText.getGlobalBounds().contains(
			static_cast<float>(mousePosition.x),
			static_cast<float>(mousePosition.y)))
		{
			return 2;
		}
	}

	return 0;
}
/**
* @brief Метод прорисовки
* @details Метод занимается прорисовкой прописанных элементов
*/
void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (const auto& star : stars)
	{
		window.draw(star.glow);
		window.draw(star.shape);
	}
	window.draw(playText);
	window.draw(exitText);
	window.draw(titleText);
}