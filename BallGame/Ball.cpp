#include "Ball.h";
#include "Paddle.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

Ball::Ball(float radius, const sf::Texture* textureBall)
	: speedX(550.f), speedY(0.f)
{
	ball.setRadius(radius);
	ball.setPointCount(100); // Устанавливаем количество точек для сглаживания круга
	ball.setFillColor(sf::Color(245, 252, 255, 255));// Устанавливаем цвет мяча
	ball.setPosition(700.f - radius, 400.f - radius); // Центрируем мяч в окне
	//ball.setTexture(textureBall);
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
// Обновление traila
void Ball::UpdateTrail(float deltaTime)
{
	trailTimer += deltaTime;
	sf::Vector2f ballPosition(
		ball.getPosition().x + ball.getRadius(),
		ball.getPosition().y + ball.getRadius()
	);
	
	while(trailTimer >= trailInterval)
	{
		TrailParticle particle;
		particle.position = ballPosition;
		particle.radius = 16.f;
		particle.alpha = 130.f;
		particle.initialRadius = 16.f;

		trail.push_back(particle);

		trailTimer -= trailInterval;
	}

	// Удаление следа 
	for(auto it = trail.begin(); it != trail.end();)
	{
		it->alpha -= 250.f * deltaTime;
		if(it->ifCollisinParticle)
		{
			float damping = std::pow(0.96f, deltaTime * 60.f);

			it->position += it->velocity * deltaTime;
			it->velocity *= damping;
		}
		it->radius -= it->initialRadius * 2.f * deltaTime;

		if (it->alpha <= 0.f || it->radius <= 0.f)
			it = trail.erase(it);
		else
			++it;
	}
}
// Прорисовка следа
void Ball::Draw(sf::RenderWindow& window)
{
	// Прорисовка следа
	for (const auto& particle : trail)
	{
		sf::CircleShape glow(particle.radius * 1.3f);

		glow.setOrigin(
			particle.radius * 1.3f, 
			particle.radius * 1.3f);
		glow.setPosition(particle.position);

		glow.setFillColor(sf::Color(
			0, 200, 255,
			static_cast<sf::Uint8>(particle.alpha * 0.05f)
		));
		window.draw(glow, sf::BlendAdd);

		sf::CircleShape middleGlow(particle.radius * 1.2f);

		middleGlow.setOrigin(
			particle.radius * 1.2f, 
			particle.radius * 1.2f);
		middleGlow.setPosition(particle.position);

		middleGlow.setFillColor(sf::Color(
			0, 200, 255,
			static_cast<sf::Uint8>(particle.alpha * 0.1f)
		));
		window.draw(middleGlow, sf::BlendAdd);

		sf::CircleShape shape(particle.radius);


		shape.setOrigin(
			particle.radius,
			particle.radius);
		shape.setPosition(particle.position);

		shape.setFillColor(sf::Color(
			0, 200, 255,
			static_cast<sf::Uint8>(particle.alpha)
		));
		window.draw(shape);
	}

	sf::CircleShape ballGlow(ball.getRadius() * 2.f);

	ballGlow.setOrigin(
		ball.getRadius() * 2.f,
		ball.getRadius() * 2.f);

	ballGlow.setPosition(
		ball.getPosition().x + ball.getRadius(),
		ball.getPosition().y + ball.getRadius()
	);

	ballGlow.setFillColor(sf::Color(
		0, 200, 255,25
	));
	window.draw(ballGlow, sf::BlendAdd);

	sf::CircleShape innerGlow(ball.getRadius() * 1.6f);

	innerGlow.setOrigin(
		ball.getRadius() * 1.6f,
		ball.getRadius() * 1.6f
	);

	innerGlow.setPosition(
		ball.getPosition().x + ball.getRadius(),
		ball.getPosition().y + ball.getRadius()
	);

	innerGlow.setFillColor(sf::Color(
		0, 190, 255, 100
	));

	window.draw(innerGlow, sf::BlendAdd);

	window.draw(ball);

	sf::CircleShape coreGlow(ball.getRadius() * 0.75f);

	coreGlow.setOrigin(
		ball.getRadius() * 0.75f,
		ball.getRadius() * 0.75f
	);

	coreGlow.setPosition(
		ball.getPosition().x + ball.getRadius(),
		ball.getPosition().y + ball.getRadius()
	);

	coreGlow.setFillColor(sf::Color(
		150, 225, 255, 180
	));

	window.draw(coreGlow, sf::BlendAdd);
}

void Ball::CreateCollisionEffect()
{
	sf::Vector2f ballPosition(
		ball.getPosition().x + ball.getRadius(),
		ball.getPosition().y + ball.getRadius()
	);

	for (int i = 0; i < 8; i++)
	{
		TrailParticle particle;
		//
		float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.f;
		//
		float speed = 250.f + static_cast<float>(rand() % 251);

		particle.velocity.x = std::cos(angle) * speed;
		particle.velocity.y = std::sin(angle) * speed;
		
		particle.acceleration = sf::Vector2f(0.f, 0.f);

		particle.position = ballPosition;
		particle.radius = 8.f;
		particle.initialRadius = 8.f;
		particle.alpha = 200.f;

		particle.ifCollisinParticle = true;
		trail.push_back(particle);
	}
}

// Корректировка расчета направления столкновения
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
	CreateCollisionEffect();
	// Ускорение после попадания по игрокам
	float acceleration = 1.08f;
	float cuurentSpeed = std::sqrt(speedX * speedX + speedY * speedY);

	if (cuurentSpeed * acceleration <= maxSpeed)
	{
		speedX *= acceleration;
		speedY *= acceleration;
	}
	else
	{
		float scale = maxSpeed / cuurentSpeed;
		speedX *= scale;
		speedY *= scale;
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

	speedX = 550.f;
	speedY = 0.f;
}