#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<Windows.h>
using namespace std;

void Print(const vector<vector<int>>& Grid) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << Grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool CheckSolvedRow(const vector<int>& row) {
    vector<int> temp = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for (int num : temp) {
        if (count(row.begin(), row.end(), num) != 1) {
            return false;
        }
    }
    return true;
}
bool CheckSolvedBlock(const vector<vector<int>>& Grid, int Block) {
    vector<int> temp;
    int Row = (Block / 3) * 3;
    int Col = (Block % 3) * 3;
    for (int i = Row; i < Row + 3; i++) {
        for (int j = Col; j < Col + 3; j++) {
            temp.push_back(Grid[i][j]);
        }
    }
    return CheckSolvedRow(temp);
}
bool CheckSolvedColumn(const vector<vector<int>>& Grid, int Column) {
    vector<int> temp;
    for (int i = 0; i < 9; i++) {
        temp.push_back(Grid[i][Column]);
    }
    return CheckSolvedRow(temp);
}
bool CheckSolved(const vector<vector<int>>& Grid) {
    for (int i = 0; i < 9; i++) {
        if (!CheckSolvedRow(Grid[i]) || !CheckSolvedBlock(Grid, i) || !CheckSolvedColumn(Grid, i)) {
            return false;
        }
    }
    return true;
}

bool isPresent(const vector<vector<int>>& Grid, int Num, int i, int j) {
    for (int a = 0; a < 9; a++) {
        if (Grid[i][a] == Num || Grid[a][j] == Num) {
            return true;
        }
    }
    int Row = (i / 3) * 3;
    int Col = (j / 3) * 3;
    for (int a = Row; a < Row + 3; a++) {
        for (int b = Col; b < Col + 3; b++) {
            if (Grid[a][b] == Num) {
                return true;
            }
        }
    }
    return false;
}

bool findNextCell(const vector<vector<int>>& Grid, int& i, int& j) {
    for (int x = i; x < 9; x++) {
        for (int y = (x == i ? j : 0); y < 9; y++) {
            if (Grid[x][y] == 0) {
                i = x;
                j = y;
                return true;
            }
        }
    }
    return false;
}
bool solve(vector<vector<int>>& Grid) {
    int i = 0, j = 0;
    if (!findNextCell(Grid, i, j)) {
        return true;
    }
    for (int num = 1; num <= 9; num++) {
        if (!isPresent(Grid, num, i, j)) {
            Grid[i][j] = num;
            if (solve(Grid)) {
                return true;
            }
            Grid[i][j] = 0;
        }
    }
    return false;
}
int main() {
    ifstream reader("text.txt");
    vector<vector<int>> Grid(9, vector<int>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            reader >> Grid[i][j];
        }
    }
    reader.close();
    cout << "Initial Grid:" << endl;
    Print(Grid);
    if (solve(Grid)) {
        cout << "Solved Grid:" << endl;
        Print(Grid);
    }
    else {
        cout << "No solution exists." << endl;
    }
    return 0;
}