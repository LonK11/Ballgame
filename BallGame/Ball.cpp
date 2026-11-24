#include "Ball.h"
#include "Paddle.h"
#include <algorithm>

Ball::Ball(float radius) 
	: speedX(200.f), speedY(150.f)
{
	ball.setRadius(radius);
	ball.setPointCount(100); // Устанавливаем количество точек для сглаживания круга
	ball.setFillColor(sf::Color::Blue);// Устанавливаем цвет мяча
	ball.setPosition(400.f - radius, 300.f - radius); // Центрируем мяч в окне
}

void Ball::Update(float deltaTime, const sf::RenderWindow& window)
{
	ball.move(speedX * deltaTime, speedY * deltaTime);
	// Взаимодействие с границами окна
	if (ball.getPosition().y < 0 || 
		ball.getPosition().y + ball.getRadius() * 2 >= window.getSize().y) {
		speedY = -speedY;
		if (ball.getPosition().y < 0) {
			ball.setPosition(ball.getPosition().x, 0);
		} else {
			ball.setPosition(ball.getPosition().x,
				window.getSize().y - ball.getRadius() * 2);
		}
	}
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(ball);
}

// корректировка расчета направления столкновения
void Ball::HandleCollision(const Paddle& paddle)
{
	sf::FloatRect ballBounds = ball.getGlobalBounds();
	sf::FloatRect paddleBounds = paddle.GetBounds();

	float ballCenterY = ballBounds.top + ballBounds.height / 2.f;
	float paddleCentrerY = paddleBounds.top + paddleBounds.height / 2.f;

	float hitPosition = (ballCenterY - paddleCentrerY) / (paddleBounds.height / 2.f);

	float overlapX = std::min(
		ballBounds.left + ballBounds.width,
		paddleBounds.left + paddleBounds.width)
		- std::max(ballBounds.left, paddleBounds.left);
	float overlapY = std::min(
		ballBounds.top + ballBounds.height,
		paddleBounds.top + paddleBounds.height)
		- std::max(ballBounds.top, paddleBounds.top);

	if (overlapX < overlapY)
	{
		speedX = -speedX;
		speedY = hitPosition * 400.f;

		if (ballBounds.left < paddleBounds.left)
			ball.move(-overlapX, 0.f);
		else
			ball.move(overlapX, 0.f);
	}
	else 
	{
		speedY = -speedY;
		if (ballBounds.top < paddleBounds.top)
			ball.move(0.f , -overlapY);
		else
			ball.move(0.f, overlapY);
	}

}

int Ball::CheckGoal(const sf::RenderWindow& window) {
	if (ball.getPosition().x + ball.getRadius() * 2 < 0)
		return 2;
	if (ball.getPosition().x > window.getSize().x)
		return 1;

	return 0;
}

// Проверка столкновения
bool Ball::CheckCollision(const Paddle& paddle) const
{
	return ball.getGlobalBounds().intersects(paddle.GetBounds());
}

// Обработка возврата
void Ball::Reset(const sf::RenderWindow& window)
{
	float radius = ball.getRadius();

	ball.setPosition(
		window.getSize().x / 2.f - radius,
		window.getSize().y / 2.f - radius
	);

	speedX = 200.f;
	speedY = 150.f;
}