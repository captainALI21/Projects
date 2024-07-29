#include"Cell.h"

Cell::Cell(float x, float y) : isBomb(false), Count(0), isHidden(true), isFlag(false), box(Vector2f(20, 20)) {
	box.setFillColor(Color(174, 214, 241));
	box.setOutlineColor(Color(52, 152, 219));
	box.setOutlineThickness(2);
	box.setPosition(x, y);
	isAbleToBeMadeABomb = true;
}
int Cell::getCount() const {
	return Count;
}
bool Cell::setCount(int _Count) {
	Count = _Count;
	return true;
}
bool Cell::getIsBomb() {
	return isBomb;
}
bool Cell::isMistake() const {
	if (isBomb && !isHidden) {
		return true;
	}
	return false;
}
bool Cell::whenClicked() {
	if (isBomb) {
		return false;
	}
	revealCell();
	return true;
}
bool Cell::isFlagged() {
	return isFlag;
}
bool Cell::revealCell() {
	if (!isFlag) {
		if (isBomb) {
			return false;
		}
		else {
			box.setFillColor(Color(195, 195, 195));
			isHidden = false;
			return true;
		}
	}
	return true;
}
bool Cell::setBomb() {
	if (isBomb) {
		return false;
	}
	if (isAbleToBeMadeABomb) {
		return false;
	}
	isBomb = true;
	//box.setFillColor(Color(60, 60, 60));
	return true;
}
bool Cell::getisHidden() {
	return isHidden;
}
void Cell::setisAbleToBeMadeABomb() {
	isAbleToBeMadeABomb = false;
}
RectangleShape Cell::getRect() const {
	return box;
}
void Cell::flagCell() {
	if (isHidden) {
		if (!isFlag) {
			box.setFillColor(Color(231, 76, 60));
			isFlag = true;
		}
		else {
			box.setFillColor(Color(174, 214, 241));
			isFlag = false;
		}
	}
}