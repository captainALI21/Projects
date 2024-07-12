#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Print(vector<vector<int>> Grid) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << Grid[i][j] << " ";
            //if (j == 2 || j == 5 || j == 8) {
            //   cout << "  ";
            //}
        }
        cout << endl;
        //if (i == 2 || i == 5 || i == 8) {
        //    cout << endl;
        //}
    }
}
bool CheckSolvedRow(vector<int> row) {
    int Count;
    vector<int> temp = { 1,2,3,4,5,6,7,8,9 };
    for (int i = 0; i < 9; i++) {
        Count = static_cast<int>(count(row.begin(), row.end(), temp[i]));
        if (Count != 1) {
            return false;
        }
    }
    return true;
}
bool CheckSolvedBlock(vector<vector<int>> Grid, int Block) {
    vector<int>temp;
    int Row = (Block / 3) * 3;
    int Col = (Block % 3) * 3;
    for (int i = Row; i < Row + 3; i++) {
        for (int j = Col; j < Col + 3; j++) {
            temp.push_back(Grid[i][j]);
        }
    }
    if (CheckSolvedRow(temp)) {
        return true;
    }
    return false;
}
bool CheckSolvedColumn(vector<vector<int>> Grid, int Column) {
    vector<int>temp;
    for (int i = 0; i < 9; i++) {
        temp.push_back(Grid[i][Column]);
    }
    if (CheckSolvedRow(temp)) {
        return true;
    }
    return false;
}
bool CheckSolved(vector<vector<int>> Grid) {
    for (int i = 0; i < 9; i++) {
        if (!(CheckSolvedRow(Grid[i]) && CheckSolvedBlock(Grid, i) && CheckSolvedColumn(Grid, i))) {
            return false;
        }
    }
    return true;
}

bool isPresent(vector<vector<int>> Grid,int Num,  int i, int j) {
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
bool NotesMaker(vector<vector<vector<int>>>& Notes, const vector<vector<int>>& Grid) {
    vector<int> temp = { 1,2,3,4,5,6,7,8,9 };
    Notes = vector<vector<vector<int>>>(9, vector<vector<int>>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (Grid[i][j] == 0) {
                for (int k = 0; k < 9; k++) {
                    if (!isPresent(Grid, temp[k], i, j)) {
                        Notes[i][j].push_back(temp[k]);
                    }
                }
            }
        }
    }
    return true;
}
bool NumberInserter(vector<vector<vector<int>>>& Notes, vector<vector<int>>& Grid, int& Count) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (Grid[i][j] == 0) {
                if (Notes[i][j].size() == 1) {
                    Grid[i][j] = Notes[i][j][0];
                    Notes[i][j].clear();
                    Count--;
                }
            }
        }
    }
    return true;
}
bool SolveGrid(vector<vector<int>>& Grid) {
    if (CheckSolved(Grid)) {
        return true;
    }
    int Count = 0;
    for (int i = 0; i < 9; i++) {
        Count = Count + static_cast<int>(count(Grid[i].begin(), Grid[i].end(), 0));
    }
    vector<vector<vector<int>>>Notes(9, vector<vector<int>>(9));
    while (Count != 0) {
    //for (int a = 0; a < 2; a++) {
        NotesMaker(Notes, Grid);
        NumberInserter(Notes, Grid, Count);
    }
    return true;
}
int main() {
    ifstream reader("text.txt");
    vector<vector<int>> Grid(9, vector<int>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            reader >> Grid[i][j];
        }
    }
    cout << CheckSolved(Grid) << endl;
    Print(Grid);
    SolveGrid(Grid);
    cout << endl;
    Print(Grid);
    reader.close();
    return 0;
}