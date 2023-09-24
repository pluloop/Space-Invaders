#include <SFML/Graphics.hpp>
#include "target.h"

// clears window, draws everything, and displays everything
void clearDrawDisplay(sf::RenderWindow& window, sf::RectangleShape& player, sf::RectangleShape& playerBullet,
	std::vector<std::vector<sf::RectangleShape>>& targets, std::vector<std::vector<bool>>& targetIsHit,
	sf::Text& score, sf::RectangleShape& targetBullet, std::vector<sf::RectangleShape>& playerLives,
	sf::Texture playerTexture)
{
	window.clear();
	window.draw(player);
	window.draw(playerBullet);
	window.draw(score);
	window.draw(targetBullet);

	for (int j{ 0 }; j < playerLives.size(); j++)
	{
		playerLives[j].setTexture(&playerTexture);
		playerLives[j].setPosition(650.0 + (50.0f * j), 0.0f);
		window.draw(playerLives[j]);
	}

	for (int i{ 0 }; i < 11; i++)
	{
		for (int j{ 0 }; j < 3; j++)
		{
			drawTarget(targetIsHit, targets, window, i, j);
		}
	}
	window.display();
}

// closes window in the event of mouse input
void closeWindow(sf::RenderWindow& window, sf::Event& evnt)
{
	if (evnt.type == sf::Event::Closed)
	{
		window.close();
	}
}

// loads texture from file and sets texture to entity
void loadFileSetTexture(sf::Texture& targetTexture, sf::RectangleShape& targetName, const std::string& file)
{
	targetTexture.loadFromFile(file);
	targetName.setTexture(&targetTexture);
}