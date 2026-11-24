#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
private:
	sf::RectangleShape paddle;

	float speed;
	float width;
	float height;
	// Кнопки управления
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	
public:
	Paddle(float x, float y, float width, float height,
			sf::Keyboard::Key up, sf::Keyboard::Key down);

	void Update(float deltaTime, const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	// Границы блока
	sf::FloatRect GetBounds() const;
	
	// Возвращение
	void Reset();
};

