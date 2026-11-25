#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include <string>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Ball Game");
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Texture TextureBall;

	if(!backgroundTexture.loadFromFile("Images/space.png"))
		return -1;
	if(!TextureBall.loadFromFile("Images/ball.png"))
		return -1;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(1.f, 1.f);

	sf::Clock clock;

	Ball ball(17.5f, &TextureBall); // Создаем мяч с радиусом 25 пикселей

	//Players
	Paddle player1(30.f, 450.f, 15.f, 150.f,
		sf::Keyboard::W, sf::Keyboard::S);
	Paddle player2(1555.f, 450.f, 15.f, 150.f,
		sf::Keyboard::Up, sf::Keyboard::Down);

	bool gameOver = false;
	int scorePlayer1 = 0;
	int scorePlayer2 = 0;

	sf::Font font;

	if (!font.loadFromFile("Fonts/arialmt.ttf"))
		return -1;

	sf::Text scoreText1;
	sf::Text scoreText2;
	sf::Text winnerText;

	scoreText1.setFont(font);
	scoreText1.setCharacterSize(40);
	scoreText1.setFillColor(sf::Color::White);
	scoreText1.setPosition(700.f, 20.f);

	scoreText2.setFont(font);
	scoreText2.setCharacterSize(40);
	scoreText2.setFillColor(sf::Color::White);
	scoreText2.setPosition(900.f, 20.f);

	winnerText.setFont(font);
	winnerText.setCharacterSize(50);
	winnerText.setFillColor(sf::Color::Yellow);
	winnerText.setPosition(650.f, 380.f);

	while (window.isOpen()) {
		sf::Event event;

		float deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (gameOver &&
				event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::R)
			{
				scorePlayer1 = 0;
				scorePlayer2 = 0;

				gameOver = false;

				ball.Reset(window);

				player1.Reset();
				player2.Reset();

				winnerText.setString("");
			}
		}

		window.clear();
		//Прорисовка фона
		//window.draw(backgroundSprite);
		// 
		//Update
		if (!gameOver)
		{
			ball.Update(deltaTime, window);

			int goal = ball.CheckGoal(window);

			if (goal == 1)
			{
				scorePlayer1++;
				ball.Reset(window);
			}
			else if (goal == 2)
			{
				scorePlayer2++;
				ball.Reset(window);
			}

			if (scorePlayer1 >= 5)
			{
				gameOver = true;
				winnerText.setString("Player 1 Wins!");
			}
			else if(scorePlayer2 >= 5)
			{
				gameOver = true;
				winnerText.setString("Player 2 Wins!");
			}

			scoreText1.setString(std::to_string(scorePlayer1));
			scoreText2.setString(std::to_string(scorePlayer2));


			player1.Update(deltaTime, window);
			player2.Update(deltaTime, window);

			if (ball.CheckCollision(player1))
			{
				ball.HandleCollision(player1);
			}
			if (ball.CheckCollision(player2))
			{
				ball.HandleCollision(player2);
			}
		}

		//Draw
		ball.Draw(window);
		player1.Draw(window);
		player2.Draw(window);
		window.draw(scoreText1);
		window.draw(scoreText2);
		if (gameOver)
			window.draw(winnerText);

		window.display();
	}

	return 0;
}