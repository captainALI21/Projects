#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include<cmath>
#include "cell.h"
using namespace std;
using namespace sf;

class Cell;

class Grid {
private:
	vector<vector<Cell>> Cells;
	bool isPaused;
	int bombCount;
	bool gameStarted;
	int hiddenCells;
	bool mistakeMade;
public:
	Grid();
	vector<vector<Cell>>& getCells();
	void gameHasStarted(Vector2i mousePos);
	int mousePress(Vector2i mousePos, Event event);
	int revealCells(int i, int j);
	void mistakeIsMade();
};