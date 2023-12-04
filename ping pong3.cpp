#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

enum Move {STOP = 0, UP, DOWN}; // Перечисление для управления правой ракеткой
Move run;

enum Move1 {STOP1 = 0, UP1, DOWN1}; // Перечисление для управления левой ракеткой
Move1 run1;

enum Ball {STOP2 = 0, UPLEFT = 1, UPRIGHT = 2, DOWNLEFT = 3, DOWNRIGHT = 4}; // Перечисление для управления траектории мяча
Ball ran;

const int COL = 40; // Количество колонок в игровом поле. Можно свободно менять
const int ROW = 10; // Количество строк в игровом поле. Можно свободно менять

int x = COL - 2; // Координаты правой ракетки
int y = ROW / 2;

int xl = COL - COL + 1; // Координаты левой ракетки
int yl = ROW / 2;

int bx = COL / 2; // Координаты мяча
int by = ROW / 2;

int racketRX[3]{ x, x, x };
int racketRY[3]{ y + 1, y, y - 1 };

int racketLX[3]{ xl, xl, xl };
int racketLY[3]{ yl + 1, yl, yl - 1 };

int score1 = 0;
int score2 = 0;

bool gameOwer = false;

void Draw() 
{
	for (int i = 0; i < COL; i++) // Рисуем верхнюю границу поля
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < ROW; i++) { // Рисуем центр поля и управляемые обьекты
		for (int j = 0; j < COL; j++) {
			
			if (j == 0 || j == COL - 1) { // Боковые границы поля
				cout << "#";
			}	
			else if (bx == j && by == i) { // Мяч
				cout << "O";
			}
			else {
				bool yas = false;
				for (int k = 0; k < 3; k++) {
					if (racketRX[k] == j && racketRY[k] == i) { // Правая ракетка
						yas = true;
						cout << "[";
					}
					else if (racketLX[k] == j && racketLY[k] == i) { // Левая ракетка
						yas = true;
						cout << "]";
					}
				}
				if (yas == false) {
					cout << " "; // Пустота
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < COL; i++) //Нижняя граница поля
	{
		cout << "#";
	}
	cout << endl;

	cout << "Gamer 1 score: " << score1 << endl;
	cout << "Gamer 2 score: " << score2 << endl;
}

void Input() 
{
	if (_kbhit()) // Отслеживаем нажатые клавиши пользователем
	{
		switch (_getch()) // Задаем клавиши для управления ракетками
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

void Logik()
{
	if (bx == COL / 2 && by == ROW / 2 && ran == STOP2) { // Создаем варианты траектории движения мяча
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
	
	switch (ran) // Движение мяча по заданной траектории
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

	switch (run) // Управление правой ракеткой
	{
	case STOP:
		break;
	case UP:
		for (int i = 0; i < 3; i++) {
			racketRY[i]--;
		}
		break;
	case DOWN:
		for (int i = 0; i < 3; i++) {
			racketRY[i]++;
		}
		break;
	}

	switch (run1) // Управление левой ракеткой
	{
	case STOP1:
		break;
	case UP1:
		for (int i = 0; i < 3; i++) {
			racketLY[i]--;
		}
		break;
	case DOWN1:
		for (int i = 0; i < 3; i++) {
			racketLY[i]++;
		}
		break;
	}

	for (int i = 0; i < 3; i++) { // Остановка ракеток на границе поля
		if (racketLY[i] == 0 || racketLY[i] == ROW - 1) {
			run1 = STOP1;
		}
		else if (racketRY[i] == 0 || racketRY[i] == ROW - 1) {
			run = STOP;
		}
	}
}

int main() // Точка входа в программу
{
	while (gameOwer == false) { // Условие завершения игры
		Sleep(50); // Замедление движения всех элементов
		system("cls"); // Обновление консоли
		Draw(); // Функции отвечающие за игру
		Input();
		Logik();
	}
	return 0;
}