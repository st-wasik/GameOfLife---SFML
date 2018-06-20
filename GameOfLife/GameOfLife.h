#pragma once
#include <vector>
#include <atomic>
#include <SFML/Graphics.hpp>

class GameOfLife
{
public:
	GameOfLife();
	void run();
	void setRandomCells();
	void setSurviveRule(std::vector<unsigned short> V);
	void setReviveRule(std::vector<unsigned short> V);
	void setRule(std::string rule);
private:
	sf::Image icon;
	const int blockSize, height, width;
	sf::RenderWindow window;

	std::vector< std::vector<bool>> arr1, arr2;
	std::vector< std::vector<short>> ile;
	std::vector< std::vector<bool>> *currentArray = &arr1, *newArray = &arr2;
	std::vector< std::vector<sf::RectangleShape>> rectArray;
	std::vector<unsigned short> surviveRule;
	std::vector<unsigned short> reviveRule;
	bool gameRun;
	bool highlightCenter;

	sf::Event event;
	sf::Clock clock;
	sf::Vector2i mouse;

	int timeLimit = 100;

	sf::Color Yellow1, Yellow2, Yellow3;

	void resizeArrays();
	void updateArrays();
	void threadedUpdateArrays();
	void updateCellsColors();
	void updateDisplay();
	void updateMouse();
};