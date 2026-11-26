#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Star {
	sf::CircleShape shape;
	sf::CircleShape glow;
	float speed;
	float twinkleTime;
	float twinkleSpeed;
};

class Menu
{
private:
	sf::Font font;
	sf::Text playText;
	sf::Text exitText;
	sf::Text titleText;
	sf::RectangleShape background;

	std::vector<Star> stars;

	float playScale = 1.f;
	float exitScale = 1.f;
	float titleScale = 1.f;
	bool titleGrowing = true;
public:
	Menu();
	/**
    * @brief Основные методы
	* @details Основные методы производящие главные процедуры класса.
	*/
	void Update(sf::RenderWindow& window, float deltaTime);
	int HandleEvent(sf::RenderWindow& window, const sf::Event& event);
	void Draw(sf::RenderWindow& window);
};

