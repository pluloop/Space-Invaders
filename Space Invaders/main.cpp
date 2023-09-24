#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "player.h"
#include "target.h"
#include "window.h"

int main()
{
	// make window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invaders", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	// make player
	sf::Texture playerTexture;
	playerTexture.loadFromFile("player.png");
	sf::RectangleShape player {sf::Vector2f(40.0f, 30.0f)};
	player.setTexture(&playerTexture);

	// set player initial position
	sf::Vector2f playerSize {playerTexture.getSize()};
	sf::Vector2f windowSize {window.getSize()};
	player.setPosition((((windowSize.x - playerSize.x) / 2.0f) + 17.5f), 
		((windowSize.y - playerSize.y) / 2.0f) + 250.0f);
	
	// make targets
	sf::Texture greenTexture;
	sf::Texture yellowTexture;
	sf::Texture redTexture;
	std::string greenTargetFile{ "green.png" };
	std::string yellowTargetFile {"yellow.png"};
	std::string redTargetFile {"red.png"};
	std::vector<std::vector<sf::RectangleShape>> targets{ makeTargets(greenTexture, yellowTexture, redTexture,
		greenTargetFile, yellowTargetFile, redTargetFile, 35.0f, 25.0f) };

	// for target horizontal movement
	bool moveLeft{ false };

	// make player bullet
	sf::Texture playerBulletTexture;
	sf::RectangleShape playerBullet {sf::Vector2f(10.0f, 20.0f)};
	loadFileSetTexture(playerBulletTexture, playerBullet, "spr_bullet_strip.png");
	sf::Vector2u playerBulletTextureSize {playerBulletTexture.getSize()};
	playerBulletTextureSize.x /= 3;
	playerBulletTextureSize.y /= 1;
	playerBullet.setTextureRect(sf::IntRect(playerBulletTextureSize.x, playerBulletTextureSize.y * 0,
		playerBulletTextureSize.x, playerBulletTextureSize.y));

	// make target bullet
	sf::Texture targetBulletTexture;
	sf::RectangleShape targetBullet {sf::Vector2f(20.0f, 60.0f)};
	loadFileSetTexture(targetBulletTexture, targetBullet, "spr_bullet_strip02.png");
	sf::Vector2u targetBulletTextureSize {targetBulletTexture.getSize()};
	targetBulletTextureSize.x /= 3;
	targetBulletTextureSize.y /= 1;
	targetBullet.setTextureRect(sf::IntRect(targetBulletTextureSize.x * 0, targetBulletTextureSize.y * 0,
		targetBulletTextureSize.x, targetBulletTextureSize.y));

	// vector of bools for hit status of target for assignment later
	std::vector<std::vector<bool>> targetIsHit(11, std::vector<bool>(3));
	
	setTargetsHitFalse(targetIsHit);

	// display score
	int score{ 0 };
	sf::Font font;
	font.loadFromFile("OpenSans-Light.ttf");
	sf::Text displayScore;
	displayScore.setFont(font);
	displayScore.setString("Score: " + std::to_string(score));
	displayScore.setCharacterSize(24);
	displayScore.setFillColor(sf::Color::White);
	displayScore.setPosition(0.0f, 0.0f);

	float speedOfTargets{ 0.5 };

	// make icon for player lives
	std::vector<sf::RectangleShape> playerLives{sf::RectangleShape {sf::Vector2f(40.0f, 30.0f)},
		sf::RectangleShape {sf::Vector2f(40.0f, 30.0f)}, sf::RectangleShape {sf::Vector2f(40.0f, 30.0f)}};

	sf::Event evnt;
	while (window.isOpen() | window.pollEvent(evnt)) // bitwise '|' was intended
	{
		closeWindow(window, evnt);
		
		movePlayer(player);

		firePlayerBullet(window, windowSize, player, playerSize, playerBulletTexture, targets, 
			moveLeft,  evnt, targetIsHit, displayScore, score, targetBullet, speedOfTargets, playerLives,
			playerTexture);

		std::vector<sf::RectangleShape> targetsNotHit(findTargetsNotHit(targetIsHit, targets));
		fireTargetBullet(window, targetIsHit, targets, targetBullet, targetBulletTexture, player, displayScore,
		evnt, playerBullet, moveLeft, windowSize, playerSize, playerBulletTexture, score, targetsNotHit, 
			speedOfTargets, playerLives, playerTexture);

		moveTargetsAll(window, player, moveLeft, targets, speedOfTargets);

		playerBullet.setPosition(player.getPosition().x + 15.0f, player.getPosition().y);
		
		clearDrawDisplay(window, player, player, targets, targetIsHit, displayScore, targetBullet, playerLives,
			playerTexture);

		// end game if player lives equals zero
		if (static_cast<int>(playerLives.size()) == 0)
		{
			window.close();
		}

		resetTargets(score, targetIsHit, targets);
	}

	return 0;
}