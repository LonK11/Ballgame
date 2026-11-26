#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Paddle;

struct TrailParticle
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float radius;
	float alpha;
	float initialRadius;
	bool ifCollisinParticle = false;

};

class Ball
{
private:
	// Данные мяча
	sf::CircleShape ball;

	float speedX;
	float speedY;
	float maxSpeed = 1100.f;
	const sf::Texture* textureBall;
	std::vector<TrailParticle> trail;
	float trailTimer = 0.f;
	float trailInterval = 0.0025f;

public:
	// Конструктор
	Ball(float radius, const sf::Texture* textureBall);

	// Методы для управления мячом
	void Update(float deltaTime, const sf::RenderWindow& window);
	void UpdateTrail(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void HandleCollision(const Paddle& paddle);
	void CreateCollisionEffect();
	int CheckGoal(const sf::RenderWindow& window);

	//Проверка столкновения с игроком
	bool CheckCollision(const Paddle& paddle) const;
	//Возвращение мяча
	void Reset(const sf::RenderWindow& window);
};

