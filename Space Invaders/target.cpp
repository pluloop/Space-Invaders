#include <SFML/Graphics.hpp>
#include "player.h"
#include <random>
#include <chrono>
#include <thread>
#include "window.h"

// assigns false to targetIsHit to allow target to be drawn and displayed
void setTargetsHitFalse(std::vector<std::vector<bool>>& targetIsHit)
{
	for (int i{ 0 }; i < 11; i++)
	{
		for (int j{ 0 }; j < 3; j++)
		{
			targetIsHit[i][j] = false;
		}
	}
}

// finding targets not hit for displaying
std::vector<sf::RectangleShape> findTargetsNotHit(std::vector<std::vector<bool>>& targetIsHit,
	std::vector<std::vector<sf::RectangleShape>>& targets)
{
	std::vector<sf::RectangleShape> targetsNotHit;

	for (int i{ 0 }; i < 11; i++)
	{
		if (targetIsHit[i][0] == false)
		{
			targetsNotHit.insert(targetsNotHit.begin(), targets[i][0]);
		}
	}

	return targetsNotHit;
}

// choose random target to shoot target bullet
void chooseRandomTarget(std::vector<sf::RectangleShape> targetsNotHit, sf::RectangleShape& targetBullet)
{
	std::mt19937 mt{std::random_device{}()};
	std::uniform_int_distribution randomIndex{ 0, static_cast<int>(targetsNotHit.size()) - 1};

	targetBullet.setPosition(targetsNotHit[randomIndex(mt)].getPosition().x + 5.0f,
		targetsNotHit[randomIndex(mt)].getPosition().y + 10.0f);
}

// to figure out if target bullet should be displayed or not
bool checkTargetBulletStatus(sf::RectangleShape& targetBullet, bool& targetBulletFired,
	sf::RectangleShape& player, std::vector<sf::RectangleShape>& playerLives)
{
	if (targetBullet.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		playerLives.pop_back(); // removes last element from vector
		return targetBulletFired = false;
	}

	else if (targetBullet.getPosition().y >= 600)
	{
		return targetBulletFired = false;
	}

	else
	{
		return targetBulletFired;
	}
}

// moves target once using move
void moveTargetsOnce(sf::RenderWindow& window, sf::RectangleShape& player, float xSpeed, float ySpeed,
	std::vector<std::vector<sf::RectangleShape>>& targets)
{
	for (int i{ 0 }; i < 11; i++)
	{
		for (int j{ 0 }; j < 3; j++)
		{
			targets[i][j].move(xSpeed, ySpeed);
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

// moves target in horizontal direction (x-axis) to make it harder for player to hit
void targetHorizontalMovement(sf::RenderWindow& window, sf::RectangleShape& player,
	bool& moveLeft, std::vector<std::vector<sf::RectangleShape>>& targets, float& speedOfTargets)
{
	if (moveLeft == false)
	{
		moveTargetsOnce(window, player, speedOfTargets, 0.0f, targets);
	}

	else if (moveLeft == true)
	{
		moveTargetsOnce(window, player, -speedOfTargets, 0.0f, targets);
	}
}

// moves target in vertical direction (y-axis) to bring target(s) closer to player
void targetVerticalMovement(sf::RenderWindow& window, sf::RectangleShape& player,
	bool& moveLeft, std::vector<std::vector<sf::RectangleShape>>& targets)
{
	if (moveLeft == false)
	{
		moveTargetsOnce(window, player, 0.0f, 2.5f, targets);

		moveLeft = true;
	}

	else if (moveLeft == true)
	{
		moveTargetsOnce(window, player, 0.0f, 2.5f, targets);

		moveLeft = false;
	}
}

// declared as to not call targetHorizontal / VerticialMovement multiple times
void moveTargetsAll(sf::RenderWindow& window, sf::RectangleShape& player,
	bool& moveLeft, std::vector<std::vector<sf::RectangleShape>>& targets, float& speedOfTargets)
{
	if (speedOfTargets <= 1.50f)
	{

		if ((targets[10][0].getPosition().x < 750 && targets[0][0].getPosition().x > 50) ||
			(targets[10][0].getPosition().x >= 750 && moveLeft == true) ||
			(targets[0][0].getPosition().x <= 50 && moveLeft == false))
		{
			targetHorizontalMovement(window, player, moveLeft, targets, speedOfTargets);
		}

		else if (targets[10][0].getPosition().x >= 750 || targets[0][0].getPosition().x <= 50)
		{
			targetVerticalMovement(window, player, moveLeft, targets);
		}
	}
	speedOfTargets += 0.00005f;
}

// fire bullet from target to challenge player
void fireTargetBullet(sf::RenderWindow& window, std::vector<std::vector<bool>>& targetIsHit,
	std::vector<std::vector<sf::RectangleShape>>& targets,
	sf::RectangleShape& targetBullet, sf::Texture& targetBulletTexture,
	sf::RectangleShape& player, sf::Text& displayScore, sf::Event& evnt,
	sf::RectangleShape& playerBullet, bool& moveLeft, sf::Vector2f& windowSize, sf::Vector2f& playerSize,
	sf::Texture& playerBulletTexture, int& score, std::vector<sf::RectangleShape>& targetsNotHit,
	float& speedOfTargets, std::vector<sf::RectangleShape>& playerLives, sf::Texture& playerTexture)
{
	chooseRandomTarget(targetsNotHit, targetBullet);

	bool targetBulletFired{ true };
	while (targetBulletFired)
	{
		closeWindow(window, evnt);

		movePlayer(player);

		firePlayerBullet(window, windowSize, player, playerSize, playerBulletTexture, targets,
			moveLeft, evnt, targetIsHit, displayScore, score, targetBullet, speedOfTargets, playerLives,
			playerTexture);

		targetBullet.move(0.0f, 5.0f);

		moveTargetsAll(window, player, moveLeft, targets, speedOfTargets);

		playerBullet.setPosition(player.getPosition().x + 15.0f, player.getPosition().y);

		clearDrawDisplay(window, player, player, targets, targetIsHit, displayScore, targetBullet, playerLives,
			playerTexture);

		checkTargetBulletStatus(targetBullet, targetBulletFired, player, playerLives);
	}
}

// make targets to give player a goal
std::vector<std::vector<sf::RectangleShape>> makeTargets(sf::Texture& greenTexture, sf::Texture& yellowTexture,
	sf::Texture& redTexture, std::string& greenTargetFile, std::string& yellowTargetFile, std::string& redTargetFile,
	float targetLength, float targetHeight)
{
	std::vector<std::vector<sf::RectangleShape>> targets(11, std::vector<sf::RectangleShape>(3));

	for (int j{ 0 }; j < 11; j++)
	{
		targets[j][0] = sf::RectangleShape{ sf::Vector2f(targetLength, targetHeight) };
		loadFileSetTexture(greenTexture, targets[j][0], greenTargetFile);
		targets[j][0].setPosition(120.0f + (55 * j), 80.0f);

		targets[j][1] = sf::RectangleShape{ sf::Vector2f(targetLength, targetHeight) };
		loadFileSetTexture(yellowTexture, targets[j][1], yellowTargetFile);
		targets[j][1].setPosition(120.0f + (55 * j), 120.0f);

		targets[j][2] = sf::RectangleShape{ sf::Vector2f(targetLength, targetHeight) };
		loadFileSetTexture(redTexture, targets[j][2], redTargetFile);
		targets[j][2].setPosition(120.0f + (55 * j), 160.0f);
	}

	return targets;
}

// set all targetIsHit to false and reposition targets to original coordinates to allow game to continue
// after all targets destroyed
void resetTargets(int& score, std::vector<std::vector<bool>>& targetIsHit, 
	std::vector<std::vector<sf::RectangleShape>>& targets)
{
	if (score % 330 == 0)
	{
		setTargetsHitFalse(targetIsHit);

		for (int j{ 0 }; j < 11; j++)
		{
			targets[j][0].setPosition(120.0f + (55 * j), 80.0f);
			targets[j][1].setPosition(120.0f + (55 * j), 120.0f);
			targets[j][2].setPosition(120.0f + (55 * j), 160.0f);
		}
	}
}

// draw target so user can see 
void drawTarget(std::vector<std::vector<bool>>& targetIsHit, std::vector<std::vector<sf::RectangleShape>>& targets,
	sf::RenderWindow& window, int& i, int& j)
{
	if (targetIsHit[i][j] == false)
	{
		window.draw(targets[i][j]);
	}

	else
	{
		targets[i][j].setPosition(static_cast<float>(targets[i][j].getPosition().x), -100.0f);
	}
}