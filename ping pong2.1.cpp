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

const int COL = 50; // Количество колонок в игровом поле
const int ROW = 20; // Количество строк в игровом поле

int x = COL - 2; // Координаты правой ракетки
int y = ROW / 2;

int xl = COL - COL + 1; // Координаты левой ракетки
int yl = ROW / 2;

int bx = COL / 2; // Координаты мяча
int by = ROW / 2;

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
			else if (x == j && y == i ) { // Правая ракетка
				cout << "[";
			}
			else if (xl == j && yl == i) { // Левая ракетка
				cout << "]";
			}
			else if (bx == j && by == i) { // Мяч
				cout << "*";
			}
			else {
			
				cout << " "; // Пустота
			}
		}
		cout << endl;
	}

	for (int i = 0; i < COL; i++) //Нижняя граница поля
	{
		cout << "#";
	}
	cout << endl;
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
	
	switch (ran) // Переключение траектории движения мяча
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
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	switch (run1) // Управление левой ракеткой
	{
	case UP1:
		yl--;
		break;
	case DOWN1:
		yl++;
		break;
	}

	if (y == 0 || y == ROW - 1) { // Останавливаем ракетку на границе поля
		run = STOP;
	}
	if (yl == 0 || yl == ROW - 1) {
		run1 = STOP1;
	}
}

int main() // Точка входа в программу
{
	while (true) { // Пока бесконечный цикл
		Sleep(50); // Замедление движения всех элементов
		system("cls"); // Обновление консоли
		
		Draw(); // Функции отвечающие за игру
		Input();
		Logik();
	}
	return 0;
}