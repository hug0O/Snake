#include <iostream>
#include <conio.h>
#include <Windows.h>
bool gameOver;
const int width = 40;
const int height = 40;
int tailX[100], tailY[100];
int nTail = 0;
int x, y,fruitX, fruitY, score;
enum eDirection {STOP = 0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
void Setup() {
	gameOver = false;
	dir = STOP;
	x = (width / 2);
	y = (height / 2);
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
//##############
//#			   #						
//#	           #
//##############
// Ligne i Colonne j
void Draw() {
	system("cls");
	for (int i = 0; i < width+2;  i++) {
		std::cout << "#";
	}

	for (int i = 0; i < width; i++) {
		std::cout << std::endl;
		for (int j = 0; j < height; j++) {
			if (j == 0) {
				std::cout << "#";
			}
			if (i == y && j == x) {
				std::cout << "O";
			}
			else if (fruitX == j && fruitY == i) {
				std::cout << "F";
			}
			else {
				bool printSnake = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i) {
						std::cout << "o";
						printSnake = true;
					}
				}
				if (!printSnake) {
					std::cout << " ";
				}

			}
			if (j == height - 1) {
				std::cout << "#";
			}
		}
	}
	
	std::cout << std::endl;
	for (int i = 0; i < width + 2; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;
	std::cout << "x : " << x << " y : " << y << std::endl;
	std::cout << "fruitX : " << fruitX << " fruitY : " << fruitY << std::endl;
	std::cout << "Score : " << score;

}

/*
 z
qsd
*/
void Input() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	// Change la direction du snake
	if (_kbhit()) {
		switch (_getch()) {
			case 'q':
				dir = LEFT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'z':
				dir = UP;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic() {
	switch (dir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
	}

	// Touche la bordure du tableau de jeu
	if (x > width || x < 0 || y > height || y < 0) {
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	// Mange le fruit
	if (fruitX == x && fruitY == y) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(5);
	}
	return 0;
}