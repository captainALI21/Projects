#include <iostream>
#include <time.h>
using namespace std;
int remaining_check(char arr[][50], int grid) {
	int count = 0;
	for (int a = 0; a < grid; a++) {
		for (int b = 0; b < grid; b++) {
			if (arr[a][b] == ' ') {
				count++;
			}
		}
	}
	return count;
}
bool connecting_check(char arr[][50], int grid, int player) {
	bool found = true;
	char player_char;
	if (player == 1) {
		player_char = 'X';
	}
	else {
		player_char = 'O';
	}
	for (int a = 0; a < grid; a++) {
		found = true;
		if (arr[a][a] != player_char) {
			found = false;
			break;
		}
	}
	if (found == true) {
		return true;
	}
	for (int a = 0; a < grid; a++) {
		found = true;
		if (arr[grid - a][a] != player_char) {
			found = false;
			break;
		}
	}
	if (found == true) {
		return true;
	}
	for (int a = 0; a < grid;a++) {
		found = true;
		for (int b = 0; b < grid; b++) {
			if (arr[a][b] != player_char) {
				found = false;
				break;
			}
		}
		if (found == true) {
			return true;
		}
	}
	for (int a = 0; a < grid; a++) {
		found = true;
		for (int b = 0; b < grid; b++) {
			if (arr[b][a] != player_char) {
				found = false;
				break;
			}
		}
		if (found == true) {
			return true;
		}
	}
	return false;
}
void grid_print(char arr[][50], int grid) {
	cout << grid << " X " << grid << " GRID:" << endl;
	char int_to_char;
	cout << "    ";
	for (int b = 0; b < grid; b++) {
		cout << " " << b + 1 << " ";
		if (b != grid - 1) {
			cout << " | ";
		}
	}
	cout << endl;
	cout << "  |-";
	for (int b = 0; b < grid; b++) {
		if (b == 0) {
			cout << "-----";
		}
		else if (b == grid - 1) {
			cout << "----";
		}
		else {
			cout << "------";
		}
	}
	cout << endl;
	for (int a = 0; a < grid; a++) {
		int_to_char = a + 65;
		cout << int_to_char << " | ";
		for (int b = 0; b < grid; b++) {
			cout << " ";
			cout << arr[a][b];
			cout << " ";
			if (b != grid - 1) {
				cout << " | ";
			}
		}
		cout << endl;
		if (a != grid - 1) {
			cout << "  | ";
		}
		if (a != grid - 1) {
			for (int b = 0; b < grid; b++) {
				if (b == 0) {
					cout << "----|";
				}
				else if (b == grid - 1) {
					cout << "----";
				}
				else {
					cout << "-----|";
				}
			}
		}
		cout << endl;
	}
}
bool valid_slot(char arr[][50], int row, int column) {
	if (arr[row][column] != ' ') {
		return false;
	}
	else {
		return true;
	}
}
void user_input(char arr[][50], int grid, int player) {
	int choice_col;
	char choice_row;
	int choice_row_int;
	char int_to_char;
	cout << "PLAYER " << player << endl;
    cout << endl;
	do {
		do {
			int_to_char = grid + 64;
			cout << "Enter the COLUMN of the element you wanna select( 1 to " << grid << " ): ";
			cin >> choice_col;
			cout << endl;
			if (choice_col < 1 || choice_col > grid) {
				cout << "INVALID INPUT/Enter again";
				cout << endl;
				cout << endl;
			}
		} while (choice_col < 1 || choice_col > grid);
		do {
		int_to_char = grid + 64;
		cout << "Enter the ROW of the element you wanna select(A/a--" << int_to_char << "/";
		cout << (int_to_char = int_to_char) << "): ";
		cin >> choice_row;
		cout << endl;
		if ((choice_row < 'A' || choice_row > 'A' + grid - 1) && (choice_row < 'a' || choice_row > 'a' + grid - 1)) {
			cout << "INVALID INPUT/Enter again";
			cout << endl;
			cout << endl;
		}
		}while ((choice_row < 'A' || choice_row > 'A' + grid - 1) && (choice_row < 'a' || choice_row > 'a' + grid - 1));
		if (choice_row > 'A' && choice_row < 'A' + grid - 1) {
			choice_row_int = choice_row - 64;
		}
		else {
			choice_row_int = choice_row - 96;
		}
		choice_row_int--;
		choice_col--;
		if (!valid_slot(arr, choice_row_int, choice_col)) {
			cout << "Element taken, Enter a new Element";
			cout << endl << endl;
		}
	} while (!valid_slot(arr, choice_row_int, choice_col));
	if (player == 1) {
		arr[choice_row_int][choice_col] = 'X';
	}
	else {
		arr[choice_row_int][choice_col] = 'O';
	}
}
int main() {
	char arr[50][50];
	int grid_size;
	cout << "TIC TAC TOE, A two player game" << endl;
	cout << "Enter the Grid size: ";
	cin >> grid_size;
	for (int a = 0; a < grid_size; a++) {
		for (int b = 0; b < grid_size; b++) {
			arr[a][b] = ' ';
		}
	}
	srand(time(NULL));
	int turn = rand();
	system("pause");
	do {
		if (connecting_check(arr, grid_size, 1)) {
			system("CLS");
			grid_print(arr,grid_size);
			cout << "PLAYER 1 has won";
			cout << endl;
			break;
		}
		else if (connecting_check(arr, grid_size, 2)) {
			system("CLS");
			grid_print(arr, grid_size);
			cout << "PLAYER 2 has won";
			cout << endl;
			break;
		}
		else if (remaining_check(arr, grid_size) == 0) {
			system("CLS");
			grid_print(arr, grid_size);
			cout << "DRAW";
			cout << endl;
			break;
		}
		turn = (turn % 2) + 1;
		system("CLS");
		grid_print(arr, grid_size);
		user_input(arr,grid_size,turn);
	} while (true);
}