#include "Grid.h"

Grid::Grid() {
	vector<Cell>temp;
    for (int j = 0; j < 15; j++) {
        temp.clear();
        for (int i = 0; i < 10; i++) {
            Cell box(static_cast<float>(42 + i * 30), static_cast<float>(42 + j * 30));
            temp.push_back(box);
        }
        Cells.push_back(temp);
    }
    isPaused = false;
    bombCount = 0;
    hiddenCells = 15 * 9;
    gameStarted = false;
    mistakeMade = false;
}
vector<vector<Cell>>& Grid::getCells() {
    return Cells;
}
void Grid::gameHasStarted(Vector2i mousePos) {
    Vector2i temp;
    double distance = 0;
    for (int i = 0; i < Cells.size(); i++) {
        for (int j = 0; j < Cells[i].size(); j++) {
            temp = static_cast<Vector2i>(Cells[i][j].getRect().getPosition());
            distance = sqrt(pow(temp.x - mousePos.x, 2) + pow(temp.y - mousePos.y, 2));
            if (distance > 100) {
                Cells[i][j].setisAbleToBeMadeABomb();
            }
        }
    }
    while (bombCount < 15) {
        if (Cells[rand() % 15][rand() % 10].setBomb()) {
            bombCount++;
        }
    }
    for (int a = 0; a < 15; a++) {
        for (int b = 0; b < 10; b++) {
            int counter = 0;
            if (!Cells[a][b].getIsBomb()) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (i != 0 || j != 0) {
                            int ni = a + i;
                            int nj = b + j;
                            if (ni >= 0 && nj >= 0 && ni < 15 && nj < 10) {
                                if (Cells[ni][nj].getIsBomb()) {
                                    counter++;
                                }
                            }
                        }
                    }
                }
            }
            Cells[a][b].setCount(counter);
        }
    }
    /*for (int a = 0; a < 15; a++) {
        for (int b = 0; b < 10; b++) {
            cout << Cells[a][b].getCount() << " ";
        }
        cout << endl;
    }*/
}
int Grid::mousePress(Vector2i mousePos, Event event) {
    if (!isPaused) {
        for (int i = 0; i < Cells.size(); i++) {
            for (int j = 0; j < Cells[i].size(); j++) {
                if (Cells[i][j].getRect().getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
                    if (!gameStarted) {
                        gameStarted = true;
                        gameHasStarted(mousePos);
                        return revealCells(i, j);
                    }
                    if (event.mouseButton.button == Mouse::Left) {
                        return revealCells(i, j);
                    }
                    else if (event.mouseButton.button == Mouse::Right) {
                        Cells[i][j].flagCell();
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
int Grid::revealCells(int i, int j) {
    if (i < 0 || i >= 15 || j < 0 || j >= 10) {
        return 0;
    }
    if (!Cells[i][j].getisHidden() || Cells[i][j].isFlagged()) {
        return 0;
    }
    if (!Cells[i][j].revealCell()) {
        mistakeMade = true;
        mistakeIsMade();
        return -1;
    }
    else {
        hiddenCells--;
        if (hiddenCells == 0) {
            return 2;
        }
    }
    if (Cells[i][j].getCount() == 0) {
        for (int a = -1; a <= 1; a++) {
            for (int b = -1; b <= 1; b++) {
                if (a != 0 || b != 0) {
                    revealCells(i + a, j + b);
                }
            }
        }
    }
    return 1;
}
void Grid::mistakeIsMade() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            if (Cells[i][j].getIsBomb()) {
                Cells[i][j].revealCell();
            }
        }
    }
}