#include <SFML/Graphics.hpp>
#include <iostream>	
using namespace std;
using namespace sf;
#pragma once

class Cell {
private:
	bool isBomb;
	bool isAbleToBeMadeABomb;
	int Count;
	bool isHidden;
	bool isFlag;
	RectangleShape box;
public:
	Cell(float x, float y);
	int getCount() const;
	void setisAbleToBeMadeABomb();
	bool setCount(int _Count);
	bool isMistake() const;
	bool whenClicked();
	bool revealCell();
	void flagCell();
	bool setBomb();
	bool getisHidden();
	bool getIsBomb();
	bool isFlagged();
	RectangleShape getRect() const;
};