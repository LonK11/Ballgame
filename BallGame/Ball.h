#pragma once

#include <SFML/Graphics.hpp>

class Paddle;

class Ball
{
private:
	// Данные мяча
	sf::CircleShape ball;

	float speedX;
	float speedY;

public:
	// Конструктор
	Ball(float radius);

	// Методы для управления мячом
	void Update(float deltaTime, const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void HandleCollision(const Paddle& paddle);
	int CheckGoal(const sf::RenderWindow& window);

	//Проверка столкновения с игроком
	bool CheckCollision(const Paddle& paddle) const;
	//Возвращение мяча
	void Reset(const sf::RenderWindow& window);
};

