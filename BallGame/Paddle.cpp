#include "Paddle.h"

Paddle::Paddle(float x, float y, float width, float height,
	sf::Keyboard::Key up, sf::Keyboard::Key down)
	: speed(400.f), width(width), height(height),
	upKey(up), downKey(down)
{
	paddle.setSize(sf::Vector2f(width, height));
	paddle.setFillColor(sf::Color::White);
	paddle.setPosition(x, y);
}

void Paddle::Update(float deltaTime, const sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(upKey))
		paddle.move(0.f, -speed * deltaTime);
	if (sf::Keyboard::isKeyPressed(downKey))
		paddle.move(0.f, speed * deltaTime);

	if(paddle.getPosition().y < 0)
		paddle.setPosition(paddle.getPosition().x, 0.f);
	if(paddle.getPosition().y + height > window.getSize().y)
		paddle.setPosition(paddle.getPosition().x,
			window.getSize().y - height);
}

void Paddle::Draw(sf::RenderWindow& window)
{
	window.draw(paddle);
}

sf::FloatRect Paddle::GetBounds() const
{
	return paddle.getGlobalBounds();
}

void Paddle::Reset()
{
	paddle.setPosition(
		paddle.getPosition().x,
		250.f
	);
}