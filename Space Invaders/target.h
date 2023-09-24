#include <SFML/Graphics.hpp>

#ifndef TARGET_H
#define TARGET_H

void setTargetsHitFalse(std::vector<std::vector<bool>>& targetIsHit);

std::vector<sf::RectangleShape> findTargetsNotHit(std::vector<std::vector<bool>>& targetIsHit,
	std::vector<std::vector<sf::RectangleShape>>& targets);

void chooseRandomTarget(std::vector<sf::RectangleShape> targetsNotHit, sf::RectangleShape& targetBullet);

bool checkTargetBulletStatus(sf::RectangleShape& targetBullet, bool& targetBulletFired,
	sf::RectangleShape& player, std::vector<sf::RectangleShape>& playerLives);

void moveTargetsOnce(sf::RenderWindow& window, sf::RectangleShape& player, float xSpeed, float ySpeed,
	std::vector<std::vector<sf::RectangleShape>>& targets);

void targetHorizontalMovement(sf::RenderWindow& window, sf::RectangleShape& player,
	bool& moveLeft, std::vector<std::vector<sf::RectangleShape>>& targets, float& speedOfTargets);

void targetVerticalMovement(sf::RenderWindow& window, sf::RectangleShape& player,
	bool& moveLeft, std::vector<std::vector<sf::RectangleShape>>& targets);

void moveTargetsAll(sf::RenderWindow& window, sf::RectangleShape& player,
	bool& moveLeft, std::vector<std::vector<sf::RectangleShape>>& targets, float& speedOfTargets);

void fireTargetBullet(sf::RenderWindow& window, std::vector<std::vector<bool>>& targetIsHit,
	std::vector<std::vector<sf::RectangleShape>>& targets,
	sf::RectangleShape& targetBullet, sf::Texture& targetBulletTexture,
	sf::RectangleShape& player, sf::Text& displayScore, sf::Event& evnt,
	sf::RectangleShape& playerBullet, bool& moveLeft, sf::Vector2f& windowSize, sf::Vector2f& playerSize,
	sf::Texture& playerBulletTexture, int& score, std::vector<sf::RectangleShape>& targetsNotHit,
	float& speedOfTargets, std::vector<sf::RectangleShape>& playerLives, sf::Texture& playerTexture);

std::vector<std::vector<sf::RectangleShape>> makeTargets(sf::Texture& greenTexture, sf::Texture& yellowTexture,
	sf::Texture& redTexture, std::string& greenTargetFile, std::string& yellowTargetFile, std::string& redTargetFile,
	float targetLength, float targetHeight);

void resetTargets(int& score, std::vector<std::vector<bool>>& targetIsHit,
	std::vector<std::vector<sf::RectangleShape>>& targets);

void drawTarget(std::vector<std::vector<bool>>& targetIsHit, std::vector<std::vector<sf::RectangleShape>>& targets,
	sf::RenderWindow& window, int& i, int& j);

#endif