#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <string>
using namespace std;
void goto_row_col(int rpos, int cpos){
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void system_pause() {
	int a = 0;
	goto_row_col(28,45);
	cout << "Game Paused";
	do {
		if (_kbhit()) {
			a = _getch();
		}
	} while (a != 27);
	goto_row_col(28, 45);
	cout << "           ";
}
void draw_center(int x,int y) {
	if (y == 51 || y == 50 || y == 49) {
		for (int a = 1; a <= x - 1; a++) {
			goto_row_col(a, 50);
			cout << "|";
		}
	}
}
void draw_boundaries(int X, int Y) {
	char ch = -37;
	for (int a = 0; a <= X; a++) {
		for (int b = 0; b <= Y; b++) {
			if (a == 0 || b == 0 || a == X || b == Y) {
				goto_row_col(a, b);
				cout << ch;
			}
		}
	}
	for (int a = 1; a <= X - 1; a++) {
		goto_row_col(a, 50);
		cout << "|";
	}
}
 int bounce_connect(int x, int x1, int x2, int y, int direction, int& p1_connect, int& p2_connect) {
	if (x == 1 || x == 23) {
		if (direction == 2) {
			return 8;
		}
		if (direction == 4) {
			return 6;
		}
		if (direction == 6) {
			return 4;
		}
		if (direction == 8) {
			return 2;
		}
		if (direction == 3) {
			if (y < 50) {
				return 8;
			}
			else {
				return 6;
			}
		}
		if (direction == 7) {
			if (y < 50) {
				return 2;
			}
			else {
				return 4;
			}
		}
	}
	if (y == 11) {
		if (x >= x1 && x <= (x1 + 1)) {
			p1_connect++;
			return 6;
		}
		if (x >= x1 + 2 && x <= (x1 + 3)) {
			p1_connect++;
			return 5;
		}
		if (x >= x1 + 4 && x <= (x1 + 5)) {
			p1_connect++;
			return 4;
		}
	}
	if (y == 89) {
		if (x >= x2 && x <= (x2 + 1)) {
			p2_connect++;
			return 8;
		}
		if (x >= x2 + 2 && x <= (x2 + 3)) {
			p2_connect++;
			return 1;
		}
		if (x >= x2 + 4 && x <= (x2 + 5)) {
			p2_connect++;
			return 2;
		}
	}
	return direction;
}
 int bounce(int x,int x1,int x2, int y, int direction) {
	if (x == 1 || x == 23) {
		if (direction == 2) {
			return 8;
		}
		if (direction == 4) {
			return 6;
		}
		if (direction == 6) {
			return 4;
		}
		if (direction == 8) {
			return 2;
		}
		if (direction == 3) {
			if (y < 50) {
				return 8;
			}
			else {
				return 6;
			}
		}
		if (direction == 7) {
			if (y < 50) {
				return 2;
			}
			else {
				return 4;
			}
		}
	}
	if (y == 11) {
		if (x >= x1 && x <= (x1 + 1)) {
			return 6;
		}
		if (x >= x1 + 2 && x <= (x1 + 3)) {
			return 5;
		}
		if (x >= x1 + 4 && x <= (x1 + 5)) {
			return 4;
		}
	}
	if (y == 89) {
		if (x >= x2 && x <= (x2 + 1)) {
			return 8;
		}
		if (x >= x2 + 2 && x <= (x2 + 3)) {
			return 1;
		}
		if (x >= x2 + 4 && x <= (x2 + 5)) {
			return 2;
		}
	}
	return direction;
}
void draw_ball(int x, int y, char ch) {
	goto_row_col(x, y);
	cout << ch;
	goto_row_col(28, 0);
}
void directional_movement(int& x, int& y, int direction) {
	if (direction == 1) {
		y--;
	}
	else if (direction == 2) {
		x++;
		y--;
	}
	else if (direction == 3) {
		x++;
	}
	else if (direction == 4) {
		x++;
		y++;
	}
	else if (direction == 5) {
		y++;
	}
	else if (direction == 6) {
		x--;
		y++;
	}
	else if (direction == 7) {
		x--;
	}
	else {
		x--;
		y--;
	}

}
void draw_bars(int x1,int x2, char ch) {
		for (int a = x1; a < x1 + 6; a++) {
			goto_row_col(a, 10);
			cout << ch;
			goto_row_col(28,0);
		}
		for (int a = x2; a < x2 + 6; a++) {
			goto_row_col(a, 90);
			cout << ch;
			goto_row_col(28,0);
		}
		goto_row_col(28, 0);
}
void bar_movement(int& x1,int& x2) {
	int a, b;
	char space = ' ', fill = -37;
	if (_kbhit()) {
		draw_bars(x1, x2, space);
		a = _getch();
		switch (a) {
		case 'w':
		case 'W':
			if (x1 >= 2) {
				x1--;
			}
			break;
		case 's':
		case 'S':
			if (x1 <= 17) {
				x1++;
			}
			break;
		case 224:
			b = _getch();
			switch (b) {
			case 72:
				if (x2 >= 2) {
					x2--;
				}
				break;
			case 80:
				if (x2 <= 17) {
					x2++;
				}
				break;
			}
			break;
		case 27:
			system_pause();
			break;
		}
		draw_bars(x1, x2, fill);
	}
}
void ai_bar_move(int x, int& x1, int& x2) {
	int a;
	char space = ' ', fill = -37;
	draw_bars(x1, x2, space);
	if (x >= 2 && x - 1 <= 18) {
		x2 = x - 1;
	}
	draw_bars(x1, x2, fill);
	if (_kbhit()) {
		draw_bars(x1, x2, space);
		a = _getch();
		switch (a) {
		case 'w':
		case 'W':
			if (x1 >= 2) {
				x1--;
			}
			break;
		case 's':
		case 'S':
			if (x1 <= 17) {
				x1++;
			}
			break;
		case 27:
			system_pause();
			break;
		}
		draw_bars(x1, x2, fill);
	}
}
void time_print(long long tim) {
	goto_row_col(27,40);
	cout << "                            ";
	long long limit;
	limit = tim - time(NULL);
	goto_row_col(27, 40);
	cout << "Remaining time : " << limit << "s";
}
 int score_game(int x,int y,int limit,int difficulty){ 
	int X, x1 = 9, x2 = 9, Y, score1 = 0, score2 = 0, direction;
	int p1_score_mul = 1, p2_score_mul = 1, p1_connect = 0, p2_connect = 0;
	char ball = 'O', fill = -37, space = ' ';
	while (score1 < limit && score2 < limit) {
		X = 12;
		Y = 50;
		do {
			direction = time(NULL) % 9;
		} while (direction == 9);
		draw_boundaries(x, y);
		draw_bars(x1, x2, fill);
		while (Y > 1 && Y < y-1) {
			goto_row_col(26, 15);
			cout << "Player 1 Score(" << p1_score_mul << "): " << score1;
			goto_row_col(26, 65);
			cout << "Player 2 Score(" << p2_score_mul << "): " << score2;
			bar_movement(x1, x2);
			direction = bounce_connect(X, x1, x2, Y, direction, p1_connect, p2_connect);
			directional_movement(X, Y, direction);
			draw_center(x, Y);
			draw_ball(X, Y, ball);
			if (difficulty == 4) {
				Sleep(75);
			}
			else if (difficulty == 3) {
				Sleep(70);
			}
			else if (difficulty == 2) {
				Sleep(65);
			}
			else {
				Sleep(60);
			}
			draw_ball(X, Y, space);
			if (p1_connect >= 0 && p1_connect <= 4) {
				p1_score_mul = 1;
			}
			else if (p1_connect >= 5 && p1_connect <= 9) {
				p1_score_mul = 2;
			}
			else {
				p1_score_mul = 3;
			}
			if (p2_connect >= 0 && p2_connect <= 4) {
				p2_score_mul = 1;
			}
			else if (p2_connect >= 5 && p2_connect <= 9) {
				p2_score_mul = 2;
			}
			else {
				p2_score_mul = 3;
			}
			if (Y == 1) {
				score2 = score2 + p2_score_mul;
				p1_connect = 0;
			}
			else if (Y == y - 1) {
				score1 = score1 + p1_score_mul;
				p2_connect = 0;
			}
		}
	}
	if (score1 == limit) {
		return 1;
	}
	if (score2 == limit) {
		return 2;
	}
	return 0;
}
 int time_game(int x, int y, int limit, int difficulty) {
	int X, x1 = 9, x2 = 9, Y, score1 = 0, score2 = 0, direction;
	int p1_score_mul = 1, p2_score_mul = 1, p1_connect = 0, p2_connect = 0;
	char ball = 'O', fill = -37, space = ' ';
	long long tim;
	tim = time(NULL) + limit;
	while (tim >= time(NULL)) {
		X = 12;
		Y = 50;
		do {
			direction = time(NULL) % 9;
		} while (direction == 9);
		draw_boundaries(x, y);
		draw_bars(x1, x2, fill);
		while ((Y > 0 && Y < y) && tim >= time(NULL)) {
			goto_row_col(26, 15);
			cout << "Player 1 Score(" << p1_score_mul << "): " << score1;
			goto_row_col(26, 65);
			cout << "Player 2 Score(" << p2_score_mul << "): " << score2;
			bar_movement(x1, x2);
			time_print(tim);
			direction = bounce_connect(X, x1, x2, Y, direction, p1_connect, p2_connect);
			directional_movement(X, Y, direction);
			draw_center(x, Y);
			draw_ball(X, Y, ball);
			if (difficulty == 4) {
				Sleep(75);
			}
			else if (difficulty == 3) {
				Sleep(70);
			}
			else if (difficulty == 2) {
				Sleep(65);
			}
			else {
				Sleep(60);
			}
			draw_ball(X, Y, space);
			if (p1_connect >= 0 && p1_connect <= 4) {
				p1_score_mul = 1;
			}
			else if (p1_connect >= 5 && p1_connect <= 9) {
				p1_score_mul = 2;
			}
			else {
				p1_score_mul = 3;
			}
			if (p2_connect >= 0 && p2_connect <= 4) {
				p2_score_mul = 1;
			}
			else if (p2_connect >= 5 && p2_connect <= 9) {
				p2_score_mul = 2;
			}
			else {
				p2_score_mul = 3;
			}
			if (Y == 1) {
				score2 = score2 + p2_score_mul;
				p1_connect = 0;
			}
			else if (Y == y - 1) {
				score1 = score1 + p1_score_mul;
				p2_connect = 0;
			}
		}
	}
	if (score1 == score2) {
		return 0;
	}
	else if (score1 > score2) {
		return 1;
	}
	else {
		return 2;
	}
}
 int ai_game(int x, int y, int limit) {
	int X, x1 = 9, x2 = 9, Y, score1 = 0, score2 = 0, direction;
	int p1_score_mul = 1, p2_score_mul = 1, p1_connect = 0, p2_connect = 0;
	char ball = 'O', fill = -37, space = ' ';
	while (score1 < limit && score2 < limit) {
		X = 12;
		Y = 50;
		do {
			direction = time(NULL) % 9;
		} while (direction == 9);
		draw_boundaries(x, y);
		draw_bars(x1, x2, fill);
		while (Y > 0 && Y < y) {
			goto_row_col(26, 15);
			cout << "Player 1 Score(" << p1_score_mul << "): " << score1;
			goto_row_col(26, 67);
			cout << "AI Score(" << p2_score_mul << "): " << score2;
			ai_bar_move(X, x1, x2);
			direction = bounce_connect(X, x1, x2, Y, direction, p1_connect, p2_connect);
			directional_movement(X, Y, direction);
			draw_center(x, Y);
			draw_ball(X, Y, ball);
			Sleep(50);
			draw_ball(X, Y, space);
			if (p1_connect >= 0 && p1_connect <= 4) {
				p1_score_mul = 1;
			}
			else if (p1_connect >= 5 && p1_connect <= 9) {
				p1_score_mul = 2;
			}
			else {
				p1_score_mul = 3;
			}
			if (p2_connect >= 0 && p2_connect <= 4) {
				p2_score_mul = 1;
			}
			else if (p2_connect >= 5 && p2_connect <= 9) {
				p2_score_mul = 2;
			}
			else {
				p2_score_mul = 3;
			}
			if (Y == 1) {
				score2 = score2 + p2_score_mul;
				p1_connect = 0;
			}
			else if (Y == y - 1) {
				score1 = score1 + p1_score_mul;
				p2_connect = 0;
			}
		}
	}
	if (score1 == limit) {
		return 1;
	}
	if (score2 == limit) {
		return 2;
	}
	return 0;
}
 int main() {
	 int y_max = 100, x_max = 24, limit, player_won = -1, game_choice = -1, difficulty;
	 string choice;
	 difficulty = -1;
	 game_choice = -1;
	 player_won = -1;
	 do {
		 system("CLS");
		 cout << "Ping Pong, A one v one game" << endl;
		 cout << endl;
		 cout << "Player 1 controls w/s " << endl;
		 cout << "Player 2 controls arrow up key/arrow down key" << endl;
		 cout << "Press ESC to Pause/Resume" << endl;
		 cout << "Score Multiplier increses after certain events" << endl;
		 cout << endl;
		 cout << "1: if you want to play a score based game" << endl;
		 cout << "2: if you want to play a time based game" << endl;
		 cout << "3: if you want to play againt a an AI(Impossible to win)" << endl;
		 cout << endl;
		 cout << "Choice:";
		 do {
			 while (true) {
				 if (_kbhit()) {
					 game_choice = _getch();
					 break;
				 }
			 }
		 } while (game_choice != '1' && game_choice != '2' && game_choice != '3');
		 system("CLS");
		 if (game_choice == '1') {
			 cout << "Enter the score limit of the game: ";
			 cin >> limit;
			 cout << endl;
			 cout << "1. legendary" << endl;
			 cout << "2. Hard" << endl;
			 cout << "3. Normal" << endl;
			 cout << "4. Easy" << endl;
			 cout << "Enter The difficulty: ";
			 cin >> difficulty;
			 system("CLS");
			 player_won = score_game(x_max, y_max, limit, difficulty);
			 system("CLS");
		 }
		 else if (game_choice == '2') {
			 cout << "Enter time in seconds" << endl;
			 cout << "Enter the time limit of the game: ";
			 cin >> limit;
			 cout << endl;
			 cout << "1. legendary" << endl;
			 cout << "2. Hard" << endl;
			 cout << "3. Normal" << endl;
			 cout << "4. Easy" << endl;
			 cout << "Enter The difficulty: ";
			 cin >> difficulty;
			 system("CLS");
			 player_won = time_game(x_max, y_max, limit, difficulty);
			 system("CLS");
		 }
		 else if (game_choice == '3') {
			 cout << "Enter the score limit of the game: ";
			 cin >> limit;
			 system("CLS");
			 player_won = ai_game(x_max, y_max, limit);
			 system("CLS");
		 }
		 if (player_won == 0) {
			 cout << "DRAW" << endl << endl << endl;
		 }
		 else {
			 cout << "PLAYER " << player_won << " has won the game" << endl << endl << endl;
		 }
		 cout << "Do you want to start again?(type Yes/No): ";
		 cin >> choice;
	 } while (choice[0] == 'y' || choice[0] == 'Y');
 }