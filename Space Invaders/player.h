#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

void movePlayer(sf::RectangleShape& player);

bool playerBulletHitTarget(sf::RectangleShape& bullet, bool& bulletFiredStatus,
	std::vector<std::vector<sf::RectangleShape>>& targets, std::vector<std::vector<bool>>& targetIsHit, int& score,
	int& i, int& j);

bool checkPlayerBulletStatus(sf::RectangleShape& bullet, bool& bulletFiredStatus,
	std::vector<std::vector<sf::RectangleShape>>& targets, std::vector<std::vector<bool>>& targetIsHit, int& score);

void firePlayerBullet(sf::RenderWindow& window, sf::Vector2f& windowSize,
	sf::RectangleShape& player, sf::Vector2f& playerSize,
	sf::Texture& playerBulletTexture, std::vector<std::vector<sf::RectangleShape>>& targets,
	bool& moveLeft, sf::Event& evnt, std::vector<std::vector<bool>>& targetIsHit,
	sf::Text& displayScore, int& score, sf::RectangleShape& targetBullet, float& speedOfTargets,
	std::vector<sf::RectangleShape> playerLives, sf::Texture& playerTexture);

#endif