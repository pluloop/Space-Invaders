#include <SFML/Graphics.hpp>

#ifndef WINDOW_H
#define WINDOW_H

void clearDrawDisplay(sf::RenderWindow& window, sf::RectangleShape& player, sf::RectangleShape& playerBullet,
	std::vector<std::vector<sf::RectangleShape>>& targets, std::vector<std::vector<bool>>& targetIsHit,
	sf::Text& score, sf::RectangleShape& targetBullet, std::vector<sf::RectangleShape>& playerLives,
	sf::Texture playerTexture);

void closeWindow(sf::RenderWindow& window, sf::Event& evnt);

void loadFileSetTexture(sf::Texture& targetTexture, sf::RectangleShape& targetName, const std::string& file);

#endif