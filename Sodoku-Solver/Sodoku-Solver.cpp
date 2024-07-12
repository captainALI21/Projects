#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void print(vector<vector<int>> Sodoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << Sodoku[i][j] << " ";
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
bool CheckSolvedBlock(vector<vector<int>> Sodoku, int Block) {
    vector<int>temp;
    int Row = (Block / 3) * 3;
    int Col = (Block % 3) * 3;
    for (int i = Row; i < Row + 3; i++) {
        for (int j = Col; j < Col + 3; j++) {
            temp.push_back(Sodoku[i][j]);
        }
    }
    if (CheckSolvedRow(temp)) {
        return true;
    }
    return false;
}
bool CheckSolvedColumn(vector<vector<int>> Sodoku, int Column) {
    vector<int>temp;
    for (int i = 0; i < 9; i++) {
        temp.push_back(Sodoku[i][Column]);
    }
    if (CheckSolvedRow(temp)) {
        return true;
    }
    return false;
}
bool CheckSolved(vector<vector<int>> Sodoku) {
    for (int i = 0; i < 9; i++) {
        if (!(CheckSolvedRow(Sodoku[i]) && CheckSolvedBlock(Sodoku, i) && CheckSolvedColumn(Sodoku, i))) {
            return false;
        }
    }
    return true;
}
int main() {
    ifstream reader("text.txt");
    vector<vector<int>> Sodoku(9, vector<int>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            reader >> Sodoku[i][j];
        }
    }
    cout << CheckSolved(Sodoku);
    reader.close();

    return 0;
}