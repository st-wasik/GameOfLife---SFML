#include "GameOfLife.h"
#include "iostream"
#include "algorithm"
// possible defines: fullscreen, no_cell_outline
#define no_cell_outline
#define fullscreen

template <typename T> void zero(std::vector<std::vector<T>>& V)
{
	for (auto& x : V)
		for (auto& y : x)
		{
			y = 0;
		}
}

template <typename T> std::ostream& operator<<(std::ostream& stream, std::vector<std::vector<T>>& V)
{
	for (std::size_t i = 0; i < V[0].size(); i++)
	{
		stream << "X: ";
		for (std::size_t j = 0; j < V.size(); j++)
		{
			stream << V[j][i] << " ";
		}
		stream << std::endl << std::endl;
	}
	stream << std::string(1, '\n') << std::endl;
	return stream;
}

GameOfLife::GameOfLife() :
	blockSize{ 6 },
#ifdef fullscreen
	window{ sf::VideoMode(sf::VideoMode::getDesktopMode()), "GameOfLife", sf::Style::Fullscreen },
	height{ (const int)sf::VideoMode::getDesktopMode().width / blockSize }, width{ (const int)sf::VideoMode::getDesktopMode().height / blockSize },
#else
	window{ sf::VideoMode(blockSize*height, blockSize*width), "GameOfLife", sf::Style::Close },
	height{ 30 }, width{ 30 },
#endif
	gameRun{ false }, timeLimit{ 100 }, highlightCenter{ false },
	Yellow1{ 51, 51, 0 }, Yellow2{ 128, 128, 0 }, Yellow3{ 255, 255, 0 },
	surviveRule{ 2,3 }, reviveRule{ 3 }
{
	icon.loadFromFile("gol.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	resizeArrays();

	//set cells rectangles
	for (std::size_t i = 0; i < height; i++)
	{
		for (std::size_t j = 0; j < width; j++)
		{
			rectArray[i][j].setSize({ static_cast<float>(blockSize),static_cast<float>(blockSize) });
			rectArray[i][j].setPosition({ static_cast<float>(i*blockSize), static_cast<float>(j*blockSize) });
			rectArray[i][j].setOutlineColor(sf::Color(32, 32, 32));
#ifdef no_cell_outline
			rectArray[i][j].setOutlineThickness(0.0);
#else
			rectArray[i][j].setOutlineThickness(-0.5);
#endif

		}
	}
}

void GameOfLife::run()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
			{
				timeLimit += 100;
				if (timeLimit < 0)
				{
					timeLimit = 1;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
			{
				timeLimit -= 100;
				if (timeLimit < 0)
				{
					timeLimit = 1;
				}
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
			{
				gameRun = !gameRun;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				timeLimit = 0;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad0)
			{
				highlightCenter = true;
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Numpad0)
			{
				highlightCenter = false;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Multiply)
			{
				setRandomCells();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Divide)
			{
				zero(*currentArray);
				zero(*newArray);
			}
		}
		updateMouse();
		updateArrays();
		updateCellsColors();
		updateDisplay();
	}
}

void GameOfLife::setRandomCells()
{
	for (int i = 0; i < currentArray->size(); i++)
		for (int j = 0; j < currentArray[0].size(); j++)
		{
			if (rand() % 2 > 0) (*currentArray)[i][j] = false; else (*currentArray)[i][j] = true;
		}
}

void GameOfLife::setSurviveRule(std::vector<unsigned short> V)
{
	surviveRule = V;
}

void GameOfLife::setReviveRule(std::vector<unsigned short> V)
{
	reviveRule = V;
}

void GameOfLife::resizeArrays()
{
	arr1.resize(height);
	for (int i = 0; i < height; i++)
	{
		arr1[i].resize(width);
	}

	arr2.resize(height);
	for (int i = 0; i < height; i++)
	{
		arr2[i].resize(width);
	}

	ile.resize(height);
	for (int i = 0; i < height; i++)
	{
		ile[i].resize(width);
	}

	rectArray.resize(height);
	for (int i = 0; i < height; i++)
	{
		rectArray[i].resize(width);
	}
}

void GameOfLife::updateArrays()
{

	// update only after time..
	if (clock.getElapsedTime().asMilliseconds() > timeLimit && gameRun)
	{////////////////////////////// warunki itd.
		zero(ile);

		for (std::size_t i = 0; i < height; i++)
			for (std::size_t j = 0; j < width; j++)
			{
				// inform neighbors if current cell is alive
				if ((*currentArray)[i][j] != 0)
				{
					/*
					// --- --- ---
					//| A |   |   |
					// --- --- ---
					//|   | c |   |  c - current cell
					// --- --- ---
					//|   |   | Z |
					// --- --- ---
					*/

					int Ax, Ay, Zx, Zy;
					Ax = i - 1; Ay = j - 1;
					Zx = i + 1; Zy = j + 1;

					if (Ax < 0) Ax = 0;
					if (Ay < 0) Ay = 0;
					if (Zx >= height) Zx = height - 1;
					if (Zy >= width) Zy = width - 1;

					//inform neighbors that current cell is alive
					for (std::size_t x = Ax; x <= Zx; x++)
					{
						for (std::size_t y = Ay; y <= Zy; y++)
						{
							ile[x][y]++;
						}
					}
					ile[i][j]--;
				}
			}

		//survive or revive (or die)
		for (std::size_t i = 0; i < height; i++)
		{
			for (std::size_t j = 0; j < width; j++)
			{
				//survive
				if ((*currentArray)[i][j] == true)
				{
					//5678/35678
					if (std::any_of(surviveRule.begin(), surviveRule.end(), [&](short x) {return x == ile[i][j]; }))
					{
						(*newArray)[i][j] = true;
					}
					else
					{
						(*newArray)[i][j] = false;
					}
				}
				//revive
				else
				{
					if (std::any_of(reviveRule.begin(), reviveRule.end(), [&](short x) {return x == ile[i][j]; }))
					{
						(*newArray)[i][j] = true;
					}
					else
					{
						(*newArray)[i][j] = false;
					}
				}
			}
		}
		std::swap(newArray, currentArray);
		clock.restart();
	}
}

void GameOfLife::updateCellsColors()
{
	for (std::size_t i = 0; i < height; i++)
	{
		for (std::size_t j = 0; j < width; j++)
		{
			if ((*currentArray)[i][j]) rectArray[i][j].setFillColor(sf::Color::Yellow);
			else rectArray[i][j].setFillColor(sf::Color::Black);
		}
	}

	if (highlightCenter)
	{
		rectArray[height / 2][width / 2].setFillColor(sf::Color(128, 128, 128));
	}
	else
	{
		if ((*currentArray)[height / 2][width / 2]) rectArray[height / 2][width / 2].setFillColor(sf::Color::Yellow);
	}
}

void GameOfLife::updateDisplay()
{
	window.clear();
	for (auto& x : rectArray)
		for (auto& y : x)
		{
			window.draw(y);
		}
	window.display();
}

void GameOfLife::updateMouse()
{
	mouse = sf::Mouse::getPosition(window);
	// get the cell from coordinates
	int Ax = mouse.x / blockSize,
		Ay = mouse.y / blockSize;

	// set alive or dead
	if (Ax >= 0 && Ax < height && Ay >= 0 && Ay < width)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			(*currentArray)[Ax][Ay] = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			(*currentArray)[Ax][Ay] = false;
		}
	}
}

void GameOfLife::setRule(std::string rule)
{
	std::vector<unsigned short> revive, survive;
	if (rule.size() == 0) abort();

	while (rule[0] != '/' && rule.size())
	{
		survive.push_back(rule[0] - 48);
		rule.erase(rule.begin());
	}
	if (rule[0] == '/')
	{
		rule.erase(rule.begin());
	}
	while (rule.size())
	{
		revive.push_back(rule[0] - 48);
		rule.erase(rule.begin());
	}

	setReviveRule(revive);
	setSurviveRule(survive);
}