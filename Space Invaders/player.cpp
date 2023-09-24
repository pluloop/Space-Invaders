#include <SFML/Graphics.hpp>
#include "window.h"
#include "target.h"
#include <chrono> // for std::chrono
#include <thread> // for std::this_thread

// moves player horizontally upon key input
void movePlayer(sf::RectangleShape& player)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		player.move(-5.0f, 0.0f);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		player.move(5.0f, 0.0f);
	}
}

// gets rid of player bullet and target if both collide to decide
bool playerBulletHitTarget(sf::RectangleShape& bullet, bool& bulletFiredStatus, 
	std::vector<std::vector<sf::RectangleShape>>& targets, std::vector<std::vector<bool>>& targetIsHit, int& score,
	int& i, int& j)
{
	if (bullet.getGlobalBounds().intersects(targets[i][j].getGlobalBounds()))
	{
		bulletFiredStatus = false;
		targetIsHit[i][j] = true;
		return score += 10;
	}
}

// gets rid of player bullet if hits target or out of bounds else bullet still fires 
// to decide whether player can shoot another bullet or not
bool checkPlayerBulletStatus(sf::RectangleShape& bullet, bool& bulletFiredStatus,
	std::vector<std::vector<sf::RectangleShape>>& targets, std::vector<std::vector<bool>>& targetIsHit, int& score)
{
	for (int i{ 0 }; i < 11; i++)
	{
		for (int j{ 0 }; j < 3; j++)
		{
			playerBulletHitTarget(bullet, bulletFiredStatus, targets, targetIsHit, score, i, j);
		}
	}

	if (bullet.getPosition().y <= 0)
	{
		return bulletFiredStatus = false;
	}

	else
	{
		return bulletFiredStatus;
	}
}

// fires player bullet upon key input to allow player to fight back against targets
void firePlayerBullet(sf::RenderWindow& window, sf::Vector2f& windowSize,
	sf::RectangleShape& player, sf::Vector2f& playerSize,
	sf::Texture& playerBulletTexture, std::vector<std::vector<sf::RectangleShape>>& targets,
	bool& moveLeft, sf::Event& evnt, std::vector<std::vector<bool>>& targetIsHit,
	sf::Text& displayScore, int& score, sf::RectangleShape& targetBullet, float& speedOfTargets,
	std::vector<sf::RectangleShape> playerLives, sf::Texture& playerTexture)
{
	bool playerBulletFired{ false };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		sf::RectangleShape playerBullet {sf::Vector2f(10.0f, 20.0f)};
		loadFileSetTexture(playerBulletTexture, playerBullet, "spr_bullet_strip.png");
		playerBullet.setPosition(player.getPosition().x + 15, player.getPosition().y);
		sf::Vector2u playerBulletTextureSize {playerBulletTexture.getSize()};
		playerBulletTextureSize.x /= 3;
		playerBulletTextureSize.y /= 1;
		playerBullet.setTextureRect(sf::IntRect(playerBulletTextureSize.x, playerBulletTextureSize.y * 0,
			playerBulletTextureSize.x, playerBulletTextureSize.y));

		playerBulletFired = true;
		while (playerBulletFired)
		{
			closeWindow(window, evnt);

			movePlayer(player);

			moveTargetsAll(window, player, moveLeft, targets, speedOfTargets);

			targetBullet.move(0.0f, 5.0f);
			playerBullet.move(0.0f, -15.0f);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			clearDrawDisplay(window, player, playerBullet, targets, targetIsHit, displayScore, targetBullet,
				playerLives, playerTexture);

			checkPlayerBulletStatus(playerBullet, playerBulletFired, targets, targetIsHit, score);

			displayScore.setString("Score: " + std::to_string(score));
		}

		playerBullet.setPosition(player.getPosition().x + 15, player.getPosition().y);
	}
}