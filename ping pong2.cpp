#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

enum Move {STOP = 0, UP, DOWN};
Move run;

enum Move1 {STOP1 = 0, UP1, DOWN1};
Move1 run1;

enum Ball {STOP2 = 0, UPLEFT = 1, UPRIGHT = 2, DOWNLEFT = 3, DOWNRIGHT = 4};
Ball ran;

const int COL = 50;
const int ROW = 20;

int x = COL - 2;
int y = ROW / 2;

int xl = COL - COL + 1;
int yl = ROW / 2;

int bx = COL / 2;
int by = ROW / 2;

void Draw() 
{
	for (int i = 0; i < COL; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			
			if (j == 0 || j == COL - 1) {
				cout << "#";
			}
				
			else if (x == j && y == i ) {
				cout << "[";
			}
			else if (xl == j && yl == i) {
				cout << "]";
			}
			else if (bx == j && by == i) {
				cout << "*";
			}

			else {
			
				cout << " ";
			}
			
		}
		cout << endl;
	}

	for (int i = 0; i < COL; i++)
	{
		cout << "#";
	}
	cout << endl;


}

void Input()
{
	if (_kbhit()) 
	{
		switch (_getch()) 
		{
		case 'w':
			run = UP;
			break;
		case 's':
			run = DOWN;
			break;
		case 'q':
			run1 = UP1;
			break;
		case 'a':
			run1 = DOWN1;
			break;
		case 'x':
			run = STOP;
			break;
		case 'z':
			run1 = STOP1;
		}
	}
}


void Runball() {

}

void Logik()
{
	if (bx == COL / 2 && by == ROW / 2 && ran == STOP2) {
		ran = UPRIGHT;
	}
	if (by == 0 && ran == UPRIGHT) {
		ran = DOWNRIGHT;
	}
	if (bx == x && ran == DOWNRIGHT) {
		ran = DOWNLEFT;
	}
	if (by == ROW && bx != COL - COL + 1 && ran == DOWNLEFT) {
		ran = UPLEFT;
	}
	if (by == 0 && ran == UPLEFT) {
		ran = DOWNLEFT;
	}
	if (by == ROW && bx == COL - COL + 1 && ran == DOWNLEFT) {
		ran = UPRIGHT;
	}
	if (by == ROW && ran == DOWNRIGHT) {
		ran = UPRIGHT;
	}
	if (bx == x && ran == UPRIGHT) {
		ran = UPLEFT;
	}
	if (bx == COL / 2 && by == ROW / 2 && ran == DOWNLEFT) {
		ran = DOWNLEFT;
	}
	if (bx == xl && ran == UPLEFT) {
		ran = UPRIGHT;
	}
	if (bx == xl && ran == DOWNLEFT) {
		ran = DOWNRIGHT;
	}
	
	switch (ran)
	{
	case UPLEFT:
		by--;
		bx--;
		break;
	case UPRIGHT:
		by--;
		bx++;
		break;
	case DOWNLEFT:
		by++;
		bx--;
		break;
	case DOWNRIGHT:
		by++;
		bx++;
		break;
	}


	switch (run)
	{
	case STOP:
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	switch (run1)
	{
	case UP1:
		yl--;
		break;
	case DOWN1:
		yl++;
		break;
	}

	if (y == 0 || y == ROW - 1) {
		run = STOP;
	}
	if (yl == 0 || yl == ROW - 1) {
		run1 = STOP1;
	}

}


int main() 
{
	while (true) {
		Sleep(200);
		system("cls");
		
		Draw();
		Input();
		Logik();
	}
	return 0;
}