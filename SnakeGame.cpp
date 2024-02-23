#include <iostream>
#include <windows.h>
using namespace std;

// initalize variables

bool snakeGame;
enum game {MAIN,START};
game mode;
int menu = 0;
const int width = 25;
const int height = 25;
// User Variables
int x, y, spd = 1;
int tailX[100], tailY[100], tailLength;
//tail  coordinates
int firstposX, firstposY, secondposX, secondposY;
// Target Variables
int targetX, targetY;
// Game Variables
int score;
enum directions { STOP = 0, UP, DOWN, LEFT, RIGHT };
directions dir;

void game_Over() {
	tailLength = 0;
	score = 0;
	mode = MAIN;
}
void game_Setup() {
	snakeGame = true;
	mode = MAIN;
}

void main_Menu() {
	system("cls");
	cout << "Main Menu " << endl;
	if (menu == 0) {
		cout << ">> Play Game " << endl;
		cout << "Options " << endl;
		cout << "End Game!" << endl;
	}
	else if (menu == 1) {
		cout << "Play Game " << endl;
		cout << ">> Options " << endl;
		cout << "End Game!" << endl;
	}
	else if (menu == 2) {
		cout << "Play Game " << endl;
		cout << "Options " << endl;
		cout << ">> End Game!" << endl;
	}

	cout << "To Confirm, Press Enter!" << endl;

	if (GetAsyncKeyState(VK_RETURN)) {
		mode = START;
	}
	else if (GetAsyncKeyState('1')) {
		menu ++;
		Sleep(50);
	}
	else if (GetAsyncKeyState('2')) {
		menu--;
		Sleep(50);
	}

	if (menu <= -1) {
		menu = 2;
	}
	else if (menu >= 3) {
		menu = 0;
	}
}
	

void normal_Setup() {
	mode = START;
	dir = STOP;
	x = rand() % width;
	y = rand() % height;
	targetX = rand() % width;
	targetY = rand() % height;

	// Error when target and player are on top of each other

	while (x == targetX && y == targetY) {
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}
	score = 0;

}

void game_Window() {
	system("cls");

	// Top Border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;
	// Body
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "*";

			}
			else if (i == y && j == x) {
				cout << "S";
			}
			else if (i == targetY && j == targetX) {
				cout << "O";
			}
			else {
				bool tail = false;
				for (int k = 0; k < tailLength; k++) {
					if (j == tailX[k] && i == tailY[k]) {
						cout << "s";
						tail = true;
					}
				}
				if (!tail) {
					cout << " ";
				}
			}


		}
		cout << endl;
	}
	// Bottom border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;

	// Score
	cout << "Score: "<< score << endl;

	// controls
	cout << "Controls:" << endl << "A = Left" << endl << "W = Up" << endl << "S = down" << endl << "D = Right" << endl;
	
}

void game_Input() {
	if (mode == START) {
		if (GetAsyncKeyState('A') && dir != RIGHT) {
			dir = LEFT;
		}
		else if (GetAsyncKeyState('D') && dir != LEFT) {
			dir = RIGHT;
		}
		else if (GetAsyncKeyState('W') && dir != DOWN) {
			dir = UP;
		}
		else if (GetAsyncKeyState('S') && dir != UP) {
			dir = DOWN;
		}
	}
}

void game_Operations() {

	//tail
	firstposX = tailX[0];
	firstposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++) {
		secondposX = tailX[i];
		secondposY = tailY[i];
		tailX[i] = firstposX;
		tailY[i] = firstposY;
		firstposX = secondposX;
		firstposY = secondposY;

	}

	// move snake
	switch (dir) {
	case LEFT: 
		x -= spd;
		break;
	case UP:
		y -= spd;
		break;
	case DOWN:
		y += spd;
		break;
	case RIGHT:
		x += spd;
		break;
	}
	// Snake Border Hit
	if (x == 0 || x == width - 1 || y < 0 || y > height -1 ) {
		game_Over();
		
	}

	// restart
	


	// snake tail hit
	
	for (int i = 0; i < tailLength; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			game_Over();
		}
	}
	// Snake Hits Target
	if (x == targetX && y == targetY) {
		targetX = rand() % width;
		targetY = rand() % height;
		score++;
		tailLength++;
	}
}


int main() {
	if (mode == MAIN) {
		game_Setup();
	}
	while (snakeGame == true) {
		if (mode == MAIN) {
			main_Menu();
		}
		else if (mode == START) {
			normal_Setup();
			while (mode == START) {
				game_Window();
				game_Input();
				game_Operations();
				Sleep(60);
			}
		}
	}
	return 0;
}
